#include "lv_img_jpeg_decoder.h"

#if USE_LV_IMG_JPEG_DECODER

#include <stdio.h>
#include <stdbool.h>
#include <setjmp.h>

#include "jpeglib.h"

#define LOGE(fmt, ...) printf(fmt, ##__VA_ARGS__);
#define LOGW(fmt, ...) printf(fmt, ##__VA_ARGS__);
#define LOGI(fmt, ...) printf(fmt, ##__VA_ARGS__);
#define LOGD(fmt, ...) printf(fmt, ##__VA_ARGS__);


typedef struct
{
    lv_fs_file_t *f; //at the end of open(), it will be closed, set NULL.
    uint8_t *data_buf;
    struct jpeg_decompress_struct *jpeg_info;
} lv_jpeg_decoder_data_t;

typedef struct
{
    struct jpeg_error_mgr pub; /* "public" fields */
    jmp_buf setjmp_buffer;     /* for return to caller */
} lv_jpeg_error_manager_t;

static lv_jpeg_error_manager_t jerr;

static uint8_t *jpeg_read_file(const char *path, uint32_t *size)
{
    lv_fs_file_t file;
    uint32_t file_size = *size;

    lv_fs_res_t res = lv_fs_open(&file, path, LV_FS_MODE_RD);
    if (res == LV_FS_RES_OK)
    {
        if (file_size == 0)
        {
            if (LV_FS_RES_OK != lv_fs_size(&file, &file_size))
            {
                LOGE("[%s]: lv_fs_size failed\n", __func__);
                goto err;
            }
        }

        if (file_size <= 0)
        {
            LOGE("[%s]: lv_fs_size get size=%d wrong\n", __func__, file_size);
            goto err;
        }

        uint32_t br = 0;
        uint8_t *buf = lv_mem_alloc(file_size);
        if (buf == NULL)
        {
            LOGE("[%s] No memory !!!\n", __func__);
            goto err;
        }
        memset(buf, 0, file_size);
        res = lv_fs_read(&file, buf, file_size, &br);
        *size = file_size;
        lv_fs_close(&file);
        return buf;
    }
    else
    {
        LOGE("[%s] error,path = %s,errno = %d !!!\n", __func__, path, res);
        return NULL;
    }

err:
    lv_fs_close(&file);
    return NULL;
}

static bool jpeg_decoder_check_type(const void *src)
{
    const lv_img_dsc_t *img_src = (const lv_img_dsc_t *)src;

    /* img_src->data is file path */
    if (img_src->header.reserved == 1)
    {
        const char *fn = (const char *)img_src->data;
        if (!strcmp(lv_fs_get_ext(fn), "jpg"))
        {
            return true;
        }
    }
    else
    {
        if ((img_src->data_size) >= 2)
        {
            if ((img_src->data[0] == 0xff) && (img_src->data[1] == 0xd8))
            {
                return true;
            }
        }
    }
    return false;
}

/*jpeg_finish_decompress, can make exit, so jpeg_error_exit also will be invoked by normal finish, then go to err_jmp.*/
static void jpeg_error_exit(j_common_ptr cinfo)
{
    /* cinfo->err actually points to a jerr struct */
    lv_jpeg_error_manager_t *custom_err = (lv_jpeg_error_manager_t *)cinfo->err;
    //LOGE("[%s]jpeg decoder exit!!\n", __func__);
    (*cinfo->err->output_message)(cinfo);
    /* Jump to the setjmp point */
    longjmp(custom_err->setjmp_buffer, 1);
}

/**
 * Open a JPEG image and return the decided image
 * @param src can be file name or pointer to a C array
 * @param style style of the image object (unused now but certain formats might use it)
 * @return pointer to the decoded image or  `LV_RES_INV` if failed
 */
static lv_res_t jpeg_decoder_open(lv_img_decoder_t *decoder, lv_img_decoder_dsc_t *dsc)
{
    (void)decoder;
    lv_fs_file_t f;
    const char *fn = NULL;
    lv_fs_res_t ret;
    uint32_t data_size;
    uint8_t *rgb888_buf = NULL;
    uint8_t *out_buffer_p = NULL;
    struct jpeg_decompress_struct *jpeg_info = NULL;
    lv_jpeg_decoder_data_t *user_data = NULL;

    /*allocat user_data*/
    if (dsc->user_data == NULL)
    {
        dsc->user_data = lv_mem_alloc(sizeof(lv_jpeg_decoder_data_t));
        if (!dsc->user_data)
        {
            LOGE("[%s]: out of memory", __func__);
            goto err;
        }
        memset(dsc->user_data, 0, sizeof(lv_jpeg_decoder_data_t));
    }
    user_data = dsc->user_data;

    /*If it's a JPG file...*/
    /*A JPG file, not support Zoom in, show original size*/

    if (dsc->src_type == LV_IMG_SRC_FILE)
    {
        fn = (char *)dsc->src;

        /*Support only "*.jpg" files*/
        if (strcmp(lv_fs_get_ext(fn), "jpg"))
        {
            LOGE("[%s]: file %s is not .jpg\n", __func__, fn);
            goto err;
        }

        ret = lv_fs_open(&f, fn, LV_FS_MODE_RD);
        if (ret != LV_FS_RES_OK)
        {
            LOGE("[%s]: lv_fs_open failed\n", __func__);
            goto err;
        }
        user_data->f = lv_mem_alloc(sizeof(f));
        if (!user_data->f)
        {
            LOGE("[%s]: out of memory", __func__);
            goto err;
        }
        memcpy(user_data->f, &f, sizeof(f));
    }
    else if (dsc->src_type == LV_IMG_SRC_VARIABLE)
    {
        lv_img_dsc_t *img = (lv_img_dsc_t *)dsc->src;
        if (img->header.cf != LV_IMG_CF_RAW)
        {
            LOGE("[%s] img->header.cf=%d\n", __func__, img->header.cf);
            goto err;
        }

        /* img->data is file path, support jpg zoom in */
        if (dsc->header.reserved == 1)
        {
            fn = (const char *)img->data;

            /*Support only "*.jpg" files*/
            if (strcmp(lv_fs_get_ext(fn), "jpg"))
            {
                LOGE("[%s]: file %s is not .jpg\n", __func__, fn);
                goto err;
            }

            ret = lv_fs_open(&f, fn, LV_FS_MODE_RD);
            if (ret != LV_FS_RES_OK)
            {
                LOGE("[%s]: lv_fs_open failed\n", __func__);
                goto err;
            }
            user_data->f = lv_mem_alloc(sizeof(f));
            if (!user_data->f)
            {
                LOGE("[%s]: out of memory", __func__);
                goto err;
            }
            memcpy(user_data->f, &f, sizeof(f));
        }
    }
    else
    {
        LOGE("[%s]: not support src_type\n", __func__);
        goto err;
    }

    //from file
    if (user_data->f)
    {
        ret = lv_fs_size(user_data->f, &data_size);
        if (ret != LV_FS_RES_OK)
        {
            LOGE("[%s]: lv_fs_size failed\n", __func__);
            goto err;
        }

        uint32_t br = 0;
        user_data->data_buf = lv_mem_alloc(data_size);
        if (!user_data->data_buf)
        {
            LOGE("[%s] No memory !!!\n", __func__);
            goto err;
        }
        memset(user_data->data_buf, 0, data_size);

        ret = lv_fs_read(user_data->f, user_data->data_buf, data_size, &br);
        if (ret != LV_FS_RES_OK || data_size != br)
        {
            LOGE("[%s]: lv_fs_open failed\n", __func__);
            goto err;
        }
    }
    else
    {
        lv_img_dsc_t *img = (lv_img_dsc_t *)dsc->src;
        user_data->data_buf = (uint8_t *)img->data;
        data_size = img->data_size;
    }

    if (!user_data->jpeg_info)
    {
        user_data->jpeg_info = lv_mem_alloc(sizeof(struct jpeg_decompress_struct));
        if (!user_data->jpeg_info)
        {
            LOGE("[%s]: out of memory", __func__);
            goto err;
        }
        memset(user_data->jpeg_info, 0, sizeof(struct jpeg_decompress_struct));
    }
    jpeg_info = user_data->jpeg_info;

    memset(&jerr, 0, sizeof(lv_jpeg_error_manager_t));
    jpeg_create_decompress(jpeg_info);
    jpeg_info->err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = jpeg_error_exit;
    /* Establish the setjmp return context for my_error_exit to use. */
    if (setjmp(jerr.setjmp_buffer))
    {
        /* If we get here, the JPEG code has signaled an error. */
        LOGE("[%s]: JPEG code has signaled an error\n", __func__);
        goto err_jmp; //to finished
    }

    jpeg_mem_src(jpeg_info, user_data->data_buf, data_size);

    if (jpeg_read_header(jpeg_info, TRUE) == -1)
    {
        LOGE("[%s]: read header err !!\n", __func__);
        goto err;
    }
    if ((jpeg_start_decompress(jpeg_info) == false))
    {
        LOGE("[%s]: decompress failed !!\n", __func__);
        goto err;
    }

    uint32_t out_buffer_size = jpeg_info->image_width * jpeg_info->image_height * jpeg_info->num_components;
    rgb888_buf = lv_mem_alloc(out_buffer_size);
    if (!rgb888_buf)
    {
        LOGE("[%s]: no enough memory!!\n", __func__);
        goto err;
    }

    while (jpeg_info->output_scanline < jpeg_info->output_height)
    {
        JSAMPROW out_str = (JSAMPROW)(rgb888_buf +
                                      jpeg_info->output_scanline * jpeg_info->image_width * jpeg_info->num_components);
        if ((jpeg_read_scanlines(jpeg_info, &out_str, 1) != 1))
        {
            LOGE("lv_img_decoder_open_jpeg: scan line failed!!\n");
            goto err;
        }
    }

    out_buffer_p = rgb888_buf;

#if LV_COLOR_DEPTH == 16
    lv_color_rgb888_to_16((lv_color_rgb888_t *)rgb888_buf,
                          (lv_color16_t *)out_buffer_p,
                          jpeg_info->image_width * jpeg_info->image_height);

#endif

    dsc->img_data = out_buffer_p;

    //close fd
    if (user_data->f)
    {
        lv_mem_free(user_data->data_buf);
        user_data->data_buf = NULL;
        lv_fs_close(user_data->f);
        lv_mem_free(user_data->f);
        user_data->f = NULL;
    }

    return LV_RES_OK;

err:
    if (user_data && user_data->jpeg_info && user_data->jpeg_info->global_state != 0)
    {
        //jpeg_finish_decompress, make error exit, so jpeg_error_exit will be invoked, then go to err_jmp.
        jpeg_finish_decompress(user_data->jpeg_info);
    }
err_jmp:
    if (rgb888_buf)
    {
        lv_mem_free((void *)rgb888_buf);
        rgb888_buf = NULL;
    }

    if (out_buffer_p)
    {
        lv_mem_free((void *)out_buffer_p);
        out_buffer_p = NULL;
    }

    if (dsc->user_data)
    {
        if (user_data->f)
        {
            lv_mem_free(user_data->data_buf);
            user_data->data_buf = NULL;

            lv_fs_close(user_data->f);
            lv_mem_free(user_data->f);
        }

        if (user_data->jpeg_info)
        {
            jpeg_destroy_decompress(user_data->jpeg_info);
            lv_mem_free(user_data->jpeg_info);
        }

        lv_mem_free(dsc->user_data);
        dsc->user_data = NULL;
    }

    return LV_RES_INV;
}

static void jpeg_decoder_close(lv_img_decoder_t *decoder, lv_img_decoder_dsc_t *dsc)
{
    (void)decoder; /*Unused*/

    LOGD("[%s] +++\n", __func__);

    lv_jpeg_decoder_data_t *user_data = (lv_jpeg_decoder_data_t *)dsc->user_data;
    if (NULL == user_data)
    {
        return;
    }

    struct jpeg_decompress_struct *jpeg_info = user_data->jpeg_info;
    if (user_data)
    {
        if (user_data->f)
        {
            lv_mem_free(user_data->data_buf);
            user_data->data_buf = NULL;
        }

        if (jpeg_info && jpeg_info->global_state != 0)
        {
            jpeg_finish_decompress(jpeg_info);
            jpeg_destroy_decompress(jpeg_info);
            jpeg_info = NULL;
        }

        if (dsc->img_data != NULL)
        {
            lv_mem_free((void *)dsc->img_data);
            dsc->img_data = NULL;
        }

        if (user_data->f)
        {
            lv_fs_close(user_data->f);
            lv_mem_free(user_data->f);
        }

        lv_mem_free(user_data);
        dsc->user_data = NULL;
    }
}

/**
 * Decode `len` pixels starting from the given `x`, `y` coordinates and store them in `buf`.
 * Required only if the "open" function can't return with the whole decoded pixel array.
 * @param decoder pointer to the decoder the function associated with
 * @param dsc pointer to decoder descriptor
 * @param x start x coordinate
 * @param y start y coordinate
 * @param len number of pixels to decode
 * @param buf a buffer to store the decoded pixels
 * @return LV_RES_OK: ok; LV_RES_INV: failed
 */
static lv_res_t jpeg_decoder_read_line(lv_img_decoder_t *decoder, lv_img_decoder_dsc_t *dsc, lv_coord_t x,
                                       lv_coord_t y, lv_coord_t len, uint8_t *buf)
{
    (void)decoder; /*Unused*/

    LOGD("[%s]: %d, %d, %d \n", __func__, x, y, len);
    lv_jpeg_decoder_data_t *user_data = dsc->user_data;

    if (dsc->header.cf != LV_IMG_CF_RAW)
    {
        LOGE("[%s]: not support header.cf\n", __func__);
        goto err;
    }

    if (!user_data)
    {
        LOGE("[%s]: failed for empty user_data\n", __func__);
        goto err;
    }

    struct jpeg_decompress_struct *jpeg_info = user_data->jpeg_info;
    if (!jpeg_info)
    {
        LOGE("[%s]: failed for empty jpeg_info\n", __func__);
        goto err;
    }

    /* Establish the setjmp return context for my_error_exit to use. */
    if (setjmp(jerr.setjmp_buffer))
    {
        /* If we get here, the JPEG code has signaled an error. */
        LOGE("[%s]: JPEG code has signaled an error\n", __func__);
        goto err_jmp;
    }

    if (jpeg_info->global_state == 0)
    {
        LOGE("[%s] error: Please open jpeg first!! \n", __func__);
        goto err;
    }

    if (y < jpeg_info->output_scanline)
    {
        LOGE("[%s] error: jpeg lib not support read from back to front!! \n", __func__);
        goto err;
    }

    if (!buf || x >= jpeg_info->image_width || y >= jpeg_info->image_height)
    {
        LOGE("[%s] error: Error: lv_img_decoder_read_line_jpeg param is error!! \n", __func__);
        goto err;
    }

    if (x != 0)
    {
        JDIMENSION width = len;
        JDIMENSION offset = x;
        jpeg_crop_scanline(jpeg_info, &offset, &width);
    }

    if (y > jpeg_info->output_scanline)
    {
        jpeg_skip_scanlines(jpeg_info, (y - jpeg_info->output_scanline));
    }

    if (jpeg_read_scanlines(jpeg_info, (JSAMPARRAY)buf, 1) != 1)
    {
        LOGE("[%s]: scan line failed!!\n", __func__);
        goto err;
    }
#if LV_COLOR_DEPTH == 16
    lv_color_rgb888_to_16((lv_color_rgb888_t *)buf, (lv_color16_t *)buf, len);
#endif

    return LV_RES_OK;

err:
    if (user_data && user_data->jpeg_info && user_data->jpeg_info->global_state != 0)
    {
        //jpeg_finish_decompress, make error exit, so jpeg_error_exit will be invoked, then go to err_jmp.
        jpeg_finish_decompress(user_data->jpeg_info);
    }

err_jmp:
    if (dsc->user_data)
    {
        if (user_data->f)
        {
            lv_mem_free(user_data->data_buf);
            user_data->data_buf = NULL;

            lv_fs_close(user_data->f);
            lv_mem_free(user_data->f);
        }

        if (user_data->jpeg_info)
        {
            jpeg_destroy_decompress(user_data->jpeg_info);
            lv_mem_free(user_data->jpeg_info);
        }

        lv_mem_free(dsc->user_data);
        dsc->user_data = NULL;
    }

    return LV_RES_INV;
}

/**
 * Get info about a JPEG image
 * @param src can be file name or pointer to a C array
 * @param header store the info here
 * @return LV_RES_OK: no error; LV_RES_INV: can't get the info
 */
static lv_res_t jpeg_decoder_info(struct _lv_img_decoder *decoder, const void *src, lv_img_header_t *header)
{
    (void)decoder;                                    /*Unused*/
    lv_img_src_t src_type = lv_img_src_get_type(src); /*Get the source type*/
    uint8_t *data_buf = NULL;
    lv_img_dsc_t img_info = {0};

    /*If it's a JPEG file...*/
    /*A JPEG file, not support Zoom in, show original size*/

    if (src_type == LV_IMG_SRC_FILE)
    {
        const char *fn = src;
        /*Support only "*.jpg" files*/
        if (strcmp(lv_fs_get_ext(fn), "jpg"))
        {
//            LOGE("[%s]: Support only \"*.jpg\" files\n", __func__);
            return LV_RES_INV;
        }

        uint32_t data_size = 0;
        data_buf = jpeg_read_file(fn, &data_size);
        if (data_buf == NULL)
        {
            LOGE("[%s]: failed for jpeg_read_file\n", __func__);
            goto err;
        }

        if (lv_jpeg_get_img_dsc(data_buf, data_size, &img_info) != LV_RES_OK)
        {
            LOGE("[%s]: failed for lv_jpeg_get_img_dsc\n", __func__);
            goto err;
        }

        lv_mem_free(data_buf);
        data_buf = NULL;

        /*Save the data in the header*/
        header->always_zero = 0;
        header->cf = LV_IMG_CF_RAW;
        header->reserved = 1; //if reserved = 1. means file
        header->w = img_info.header.w;
        header->h = img_info.header.h;

        return LV_RES_OK;
    }
    else if (src_type == LV_IMG_SRC_VARIABLE)
    {
        if (!jpeg_decoder_check_type(src))
        {
//            LOGE("[%s]: failed for jpeg_decoder_check_type\n", __func__);
            return LV_RES_INV;
        }

        const lv_img_dsc_t *img_dsc = src;
        header->always_zero = 0;
        header->cf = img_dsc->header.cf; /*Save the color format*/
        header->reserved = img_dsc->header.reserved;
        header->w = img_dsc->header.w; /*Save the color width*/
        header->h = img_dsc->header.h; /*Save the color height*/
        return LV_RES_OK;
    }

err:
    if (data_buf)
    {
        lv_mem_free(data_buf);
    }

    return LV_RES_INV;
}

void lv_color_rgb888_to_16(lv_color_rgb888_t *in, lv_color16_t *out, int px_cnt)
{
    for (int px = 0; px < px_cnt; px++)
    {
        *out = LV_COLOR_MAKE(in->r, in->g, in->b);
        in++;
        out++;
    }
}

lv_res_t lv_jpeg_get_img_dsc(const void *data_buf, uint32_t data_size, lv_img_dsc_t *img_dsc)
{
    if (data_buf == NULL || img_dsc == NULL)
    {
        LOGE("invaild input");
       goto err;
    }

    struct jpeg_decompress_struct jpeg_info;
    memset(&jpeg_info, 0, sizeof(struct jpeg_decompress_struct));
    memset(&jerr, 0, sizeof(lv_jpeg_error_manager_t));

    jpeg_create_decompress(&jpeg_info);

    jpeg_info.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = jpeg_error_exit;

    if (setjmp(jerr.setjmp_buffer))
    {
        LOGE("[%s]: JPEG code has signaled an error\n", __func__);
        jpeg_destroy_decompress(&jpeg_info);
        goto err;
    }

    jpeg_mem_src(&jpeg_info, data_buf, data_size);
    if (jpeg_read_header(&jpeg_info, TRUE) == -1)
    {
        LOGE("[%s]: this file is error!!\n", __func__);

        jpeg_destroy_decompress(&jpeg_info);

        goto err;
    }

    img_dsc->header.always_zero = 0;
    img_dsc->header.cf = LV_IMG_CF_RAW;
    img_dsc->header.reserved = 0; //if reserved = 1. means file
    img_dsc->header.w = jpeg_info.image_width;
    img_dsc->header.h = jpeg_info.image_height;
    img_dsc->data = data_buf;
    img_dsc->data_size = data_size;

    jpeg_destroy_decompress(&jpeg_info);

    return LV_RES_OK;

err:

    return LV_RES_INV;
}

/**
 * Register the JPEG decoder functions in LittlevGL
 */
void lv_jpeg_decoder_init(void)
{
    lv_img_decoder_t *dec = lv_img_decoder_create();
    lv_img_decoder_set_info_cb(dec, jpeg_decoder_info);
    lv_img_decoder_set_open_cb(dec, jpeg_decoder_open);
    lv_img_decoder_set_read_line_cb(dec, jpeg_decoder_read_line);
    lv_img_decoder_set_close_cb(dec, jpeg_decoder_close);
}



#endif /* USE_LV_IMG_JPEG_DECODER */
