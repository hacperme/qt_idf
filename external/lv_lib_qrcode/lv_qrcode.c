#include "lv_qrcode.h"

#ifdef USE_LV_QRCODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qrencode.h"
#include "qrspec.h"

#define LOGE(fmt, ...) printf(fmt, ##__VA_ARGS__);
#define LOGW(fmt, ...) printf(fmt, ##__VA_ARGS__);
#define LOGI(fmt, ...) printf(fmt, ##__VA_ARGS__);
#define LOGD(fmt, ...) printf(fmt, ##__VA_ARGS__);

static lv_signal_cb_t ancestor_signal = NULL;

static void lv_qrcode_set_px(lv_obj_t *canvas, int x, int y, int pix_width, lv_color_t c)
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

static lv_res_t qrcode_canvas_signal(lv_obj_t *canvas, lv_signal_t sign, void *param)
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

lv_obj_t *lv_qrcode_create(lv_obj_t *par, const char *str, int px, int py, int scale)
{
    int pix_width, buf_width, buf_size, qr_w, idx;
    int version;
    unsigned char *qr_data;
    lv_obj_t *canvas;
    uint8_t *img_buf;
    QRcode *qrcode;
    lv_color_t c_bg;

    if (par == NULL)
    {
        par = lv_scr_act();
    }

    version = QRspec_getMinimumVersion(strlen(str), QR_ECLEVEL_L);

    qrcode = QRcode_encodeString(str, version, QR_ECLEVEL_L, QR_MODE_8, 1);
    if (!qrcode)
    {
        LOGE("QRcode_encodeString failed\n");
        return NULL;
    }

    qr_w = qrcode->width;

    pix_width = LV_QRCODE_PIX_WIDTH * scale;
    buf_width = qr_w * pix_width;

    buf_size = LV_CANVAS_BUF_SIZE_INDEXED_1BIT(buf_width, buf_width);

    img_buf = lv_mem_alloc(buf_size);
    if (!img_buf)
    {
        LOGE("lv_mem_alloc failed\n");
        goto err1;
    }

    canvas = lv_canvas_create(par, NULL);
    if (!canvas)
    {
        LOGE("lv_canvas_create failed\n");
        goto err2;
    }

    lv_canvas_set_buffer(canvas, img_buf, buf_width, buf_width, LV_IMG_CF_INDEXED_1BIT);
    lv_canvas_set_palette(canvas, 0, LV_COLOR_BLACK);
    lv_canvas_set_palette(canvas, 1, LV_COLOR_WHITE);

    c_bg.full = 0;

#if LV_VERSION_CHECK(7, 0, 0)
    lv_canvas_fill_bg(canvas, c_bg, LV_OPA_COVER);
#else
    lv_canvas_fill_bg(canvas, c_bg);
#endif

    c_bg.full = 1;

    lv_obj_set_pos(canvas, px, py);
    if (ancestor_signal == NULL)
        ancestor_signal = lv_obj_get_signal_cb(canvas);
    /*The signal and design functions are not copied so set them here*/
    lv_obj_set_signal_cb(canvas, qrcode_canvas_signal);

    qr_data = qrcode->data;
    for (int y = 0; y < qr_w; y++)
    {
        for (int x = 0; x < qr_w; x++)
        {
            idx = y * qr_w + x;
            if ((qr_data[idx] & 0x1) == 0) /* white pix */
            {
                lv_qrcode_set_px(canvas, x, y, pix_width, c_bg);
            }
        }
    }

    QRcode_free(qrcode);

    return canvas;
err2:
    lv_mem_free(img_buf);
err1:
    QRcode_free(qrcode);
    LOGE("qrcode_gen failed\n");
    return NULL;
}

#endif
