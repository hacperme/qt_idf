#include "lv_lib_barcode.h"

#ifdef USE_LV_BARCODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "code128.h"

#define LOGE(fmt, ...) printf(fmt, ##__VA_ARGS__);
#define LOGW(fmt, ...) printf(fmt, ##__VA_ARGS__);
#define LOGI(fmt, ...) printf(fmt, ##__VA_ARGS__);
#define LOGD(fmt, ...) printf(fmt, ##__VA_ARGS__);

static lv_signal_cb_t ancestor_signal = NULL;

static void lv_barcode_set_px(lv_obj_t *canvas, int x, int y, int pix_width, lv_color_t c)
{
    int x1, x2, y1, y2;

    x1 = x * pix_width;
    y1 = y * pix_width;

    x2 = x1 + pix_width;
    y2 = y1 + pix_width;

    for (int j = y1; j < y2; j++)
    {
        for (int i = x1; i < x2; i++)
        {
            lv_canvas_set_px(canvas, i, j, c);
        }
    }
}

static lv_res_t barcode_canvas_signal(lv_obj_t *canvas, lv_signal_t sign, void *param)
{
    lv_res_t res;

    /* Include the ancient signal function */
    res = ancestor_signal(canvas, sign, param);
    if (res != LV_RES_OK)
        return res;

    if (sign == LV_SIGNAL_CLEANUP)
    {
        lv_canvas_ext_t *ext = lv_obj_get_ext_attr(canvas);
        if (ext->dsc.data)
            lv_mem_free(ext->dsc.data);
        ext->dsc.data = NULL;
    }

    return res;
}

/**
 * Create a barcode object
 * @param par pointer to an object, it will be the parent of the new qrcode
 * @param height the barcode height to be shown
 * @param data the input string to be encoded
 * @return pointer to the new barcode object
 */
lv_obj_t *lv_barcode_create(lv_obj_t *par, int height, const char *data)
{
    lv_obj_t *canvas = NULL;
    size_t barcode_length;
    char *barcode_data = NULL;
    uint8_t *img_buf = NULL;
    size_t img_size = 0;
    int buf_width;
    lv_color_t c_bg;

    if (par == NULL)
    {
        par = lv_scr_act();
    }

    barcode_length = code128_estimate_len(data);

    barcode_data = (char *)lv_mem_alloc(barcode_length);

    barcode_length = code128_encode_gs1(data, barcode_data, barcode_length);

    LOGD("barcode_length = %d \n", barcode_length);

    if (barcode_length == 0)
    {
        LOGE("code128_encode_gs1 encode\n");
        goto err;
    }

    buf_width = barcode_length * LV_BARCODE_PIX_WIDTH;

    img_size = LV_CANVAS_BUF_SIZE_INDEXED_1BIT(buf_width, height);

    LOGD("img_size = %d, width = %d, height = %d, buf_width = %d \n",
         img_size,
         height,
         buf_width);

    img_buf = lv_mem_alloc(img_size);
    if (!img_buf)
    {
        LOGE("lv_mem_alloc failed\n");
        goto err;
    }

    canvas = lv_canvas_create(par, NULL);
    if (!canvas)
    {
        LOGE("lv_canvas_create failed\n");
        goto err;
    }

    lv_canvas_set_buffer(canvas, img_buf, buf_width, height, LV_IMG_CF_INDEXED_1BIT);
    lv_canvas_set_palette(canvas, 0, LV_COLOR_BLACK);
    lv_canvas_set_palette(canvas, 1, LV_COLOR_WHITE);

    c_bg.full = 1;

#if LV_VERSION_CHECK(7, 0, 0)
    lv_canvas_fill_bg(canvas, c_bg, LV_OPA_COVER);
#else
    lv_canvas_fill_bg(canvas, c_bg);
#endif

    c_bg.full = 0;

    int x = 0;
    for (int i = 0; i < barcode_length; i++)
    {
        if (barcode_data[i])
        {
            for (int j = 0; j < height; j++)
            {
                lv_barcode_set_px(canvas, i, j, LV_BARCODE_PIX_WIDTH, c_bg);
            }
        }
    }

    if (ancestor_signal == NULL)
        ancestor_signal = lv_obj_get_signal_cb(canvas);
    /*The signal and design functions are not copied so set them here*/
    lv_obj_set_signal_cb(canvas, barcode_canvas_signal);

    if (barcode_data)
    {
        lv_mem_free(barcode_data);
    }

    return canvas;

err:

    if (canvas)
    {
        lv_obj_del(canvas);
    }
    if (img_buf)
    {
        lv_mem_free(img_buf);
    }

    if (barcode_data)
    {
        lv_mem_free(barcode_data);
    }
    return NULL;
}

#endif
