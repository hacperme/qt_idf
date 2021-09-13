#include "lv_img_png_decoder.h"
#include "lv_img_jpeg_decoder.h"

#if USE_LV_IMG_PNG_DECODER

#include <stdio.h>
#include <stdbool.h>

#include "png.h"
#include "pngstruct.h"
#include "pnginfo.h"

#define LV_PNG_SIGNATURE_LEN 8

#define LOGE(fmt, ...) printf(fmt, ##__VA_ARGS__);
#define LOGW(fmt, ...) printf(fmt, ##__VA_ARGS__);
#define LOGI(fmt, ...) printf(fmt, ##__VA_ARGS__);
#define LOGD(fmt, ...) printf(fmt, ##__VA_ARGS__);


typedef struct
{
    lv_fs_file_t *f; //at the end of open(), it will be closed, set NULL.
    int read_pos;
    png_structp png_ptr;
    png_infop info_ptr;
    png_bytep row_buf;
    int pixel_size_png;
    int pixel_size_lv;
    int read_line_mode;
    int row_curr;
} lv_png_decoder_data_t;

/**********************
 *   STATIC FUNCTIONS
 **********************/
static png_voidp _png_malloc(png_structp ptr, png_alloc_size_t size)
{
    png_voidp p;
    (void)ptr;

    p = lv_mem_alloc(size);

    return p;
}

static void _png_free(png_structp ptr, png_voidp p)
{
    (void)ptr;

    lv_mem_free(p);
    return;
}

static void png_read_data_fn(png_structp ptr, png_bytep data,
                             png_size_t length)
{
    const uint8_t *p;
    lv_img_decoder_dsc_t *dsc = (lv_img_decoder_dsc_t *)ptr->io_ptr;
    if (!dsc)
        return;
    lv_png_decoder_data_t *user_data = dsc->user_data;
    if (!user_data)
        return;

    //file
    if (user_data->f)
    {
        uint32_t readbytes = 0;
        lv_fs_res_t res;

        res = lv_fs_seek(user_data->f, user_data->read_pos);
        if (res != LV_FS_RES_OK)
        {
            printf("png_read_data_fn png decoder lv_fs_seek failed\n");
            return;
        }

        res = lv_fs_read(user_data->f, data, length, &readbytes);
        if (res != LV_FS_RES_OK || length != readbytes)
        {
            printf("png_read_data_fn png decoder lv_fs_read failed\n");
        }
    }
    else if (dsc->src_type == LV_IMG_SRC_VARIABLE)
    {
        lv_img_dsc_t *img = (lv_img_dsc_t *)dsc->src;
        /* img->data is png data */
        p = img->data + user_data->read_pos;
        memcpy(data, p, length);
    }

    user_data->read_pos += length;
}

/**
 * Open a PNG image and return the decided image
 * @param src can be file name or pointer to a C array
 * @param style style of the image object (unused now but certain formats might use it)
 * @return pointer to the decoded image or  `LV_RES_INV` if failed
 */
static lv_res_t png_decoder_open(lv_img_decoder_t *decoder, lv_img_decoder_dsc_t *dsc)
{
    /*Open the file if it's a file*/
    (void)decoder;
    png_bytepp row_pointers;
    unsigned width, height;
    png_bytep img_buf = NULL;
    uint8_t *img_buf_565 = NULL;

    lv_fs_file_t f;

    /*allocat user_data*/
    if (!dsc->user_data)
    {
        dsc->user_data = lv_mem_alloc(sizeof(lv_png_decoder_data_t));
        if (!dsc->user_data)
        {
            printf("[%s]: out of memory", __func__);
            goto err;
        }
        memset(dsc->user_data, 0, sizeof(lv_png_decoder_data_t));
    }
    lv_png_decoder_data_t *user_data = dsc->user_data;

    /*If it's a PNG file...*/
    /*A PNG file, not support Zoom in, show original size*/

    if (dsc->src_type == LV_IMG_SRC_FILE)
    {
        const char *fn = (char *)dsc->src;

        /*Support only "*.png" files*/
        if (strcmp(lv_fs_get_ext(fn), "png"))
        {
            printf("[%s]: file %s is not .png\n", __func__, fn);
            goto err;
        }

        lv_fs_res_t ret = lv_fs_open(&f, fn, LV_FS_MODE_RD);
        if (ret != LV_FS_RES_OK)
        {
            printf("[%s]: lv_fs_open failed\n", __func__);
            goto err;
        }
        user_data->f = lv_mem_alloc(sizeof(f));
        if (user_data->f == NULL)
        {
            printf("[%s]: out of memory", __func__);
            goto err;
        }
        memcpy(user_data->f, &f, sizeof(f));
    }
    else if (dsc->src_type == LV_IMG_SRC_VARIABLE)
    {
        lv_img_dsc_t *img = (lv_img_dsc_t *)dsc->src;
        /* img->data is file path, support png zoom in */
        if (dsc->header.reserved == 1)
        {
            const char *fn = (const char *)img->data;

            /*Support only "*.png" files*/
            if (strcmp(lv_fs_get_ext(fn), "png"))
            {
                printf("[%s]: file %s is not .png\n", __func__, fn);
                goto err;
            }

            lv_fs_res_t ret = lv_fs_open(&f, fn, LV_FS_MODE_RD);
            if (ret != LV_FS_RES_OK)
            {
                printf("[%s]: lv_fs_open failed\n", __func__);
                goto err;
            }
            user_data->f = lv_mem_alloc(sizeof(f));
            if (user_data->f == NULL)
            {
                printf("[%s]: out of memory", __func__);
                goto err;
            }
            memcpy(user_data->f, &f, sizeof(f));
        }
    }
    else
    {
        printf("[%s]: not support src_type\n", __func__);
        goto err;
    }

    user_data->read_pos = LV_PNG_SIGNATURE_LEN; //skip sig
    user_data->png_ptr = png_create_read_struct_2(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL, NULL, _png_malloc, _png_free);
    if (!user_data->png_ptr)
    {
        printf("png_create_read_struct_2 failed\n");
        goto err;
    }

    user_data->info_ptr = png_create_info_struct(user_data->png_ptr);
    if (!user_data->info_ptr)
    {
        printf("png_create_info_struct failed\n");
        png_destroy_read_struct(&user_data->png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        goto err;
    }

    if (setjmp(png_jmpbuf(user_data->png_ptr)))
    {
        printf("set jmp failed\n");
        png_destroy_read_struct(&user_data->png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        goto err;
    }

    png_set_read_fn(user_data->png_ptr, (png_voidp)dsc, png_read_data_fn);
    png_set_sig_bytes(user_data->png_ptr, LV_PNG_SIGNATURE_LEN);
    png_read_info(user_data->png_ptr, user_data->info_ptr);

    if (user_data->info_ptr->trans_alpha)
        dsc->header.cf = LV_IMG_CF_RAW_ALPHA;
    else
        dsc->header.cf = LV_IMG_CF_RAW;

    if (user_data->info_ptr->color_type == PNG_COLOR_TYPE_PALETTE)
    { /* PNG8 */
        png_set_palette_to_rgb(user_data->png_ptr);
    }

    if (dsc->header.cf == LV_IMG_CF_RAW_ALPHA)
    {
        user_data->pixel_size_png = 4; /*  RGBA888 */
        user_data->pixel_size_lv = 3;
    }
    else
    {
        user_data->pixel_size_png = 3; /*  RGB888 */
        user_data->pixel_size_lv = 2;
        png_set_strip_alpha(user_data->png_ptr);
    }

    width = user_data->info_ptr->width;
    height = user_data->info_ptr->height;

    row_pointers = _png_malloc(user_data->png_ptr, height * sizeof(png_bytep));
    img_buf = _png_malloc(user_data->png_ptr, width * height * user_data->pixel_size_png);

    //only no memeory, enter readline mode. normally is whole decoded mode which support cached.
    if ((!row_pointers) || (!img_buf))
    {
        //printf("no mem for open, try to readline\n");
        _png_free(user_data->png_ptr, row_pointers);
        _png_free(user_data->png_ptr, img_buf);
        img_buf = NULL;

        if ((dsc->header.w != width) || (dsc->header.h != height))
        {
            printf("no scale for readline, png decoder failed\n");
            png_destroy_read_struct(&user_data->png_ptr, &user_data->info_ptr, NULL);
            goto err;
        }

        user_data->row_buf = _png_malloc(user_data->png_ptr, (width * user_data->pixel_size_png));
        if (!user_data->row_buf)
        {
            printf("no mem for readline, png decoder failed\n");
            png_destroy_read_struct(&user_data->png_ptr, &user_data->info_ptr, NULL);
            goto err;
        }
        user_data->read_line_mode = 1;
        user_data->row_curr = 0;
        return LV_RES_OK;
    }

    //whole decoded to bitmap, saved to cache.
    for (int i = 0; i < height; i++)
    {
        row_pointers[i] = img_buf + i * width * user_data->pixel_size_png;
    }

    png_set_rows(user_data->png_ptr, user_data->info_ptr, row_pointers);
    png_read_image(user_data->png_ptr, row_pointers);
    png_read_end(user_data->png_ptr, user_data->info_ptr);

    img_buf_565 = img_buf;
    if (dsc->header.cf == LV_IMG_CF_RAW_ALPHA)
    {
        lv_color_rgba8888_to_16_alpha((lv_color_rgba8888_t *)img_buf, (lv_color16_alpha_t *)img_buf_565, width * height);
    }
    else
    {
        lv_color_rgb888_to_16((lv_color_rgb888_t *)img_buf, (lv_color16_t *)img_buf_565, width * height);
    }

    _png_free(user_data->png_ptr, row_pointers);
    png_destroy_read_struct(&user_data->png_ptr, &user_data->info_ptr, NULL);

   
    //total bit map saved in cache;
    dsc->img_data = img_buf_565;

    //close fd
    if (user_data->f)
    {
        lv_fs_close(user_data->f);
        lv_mem_free(user_data->f);
        user_data->f = NULL;
    }

    return LV_RES_OK;

err:
    if (dsc->user_data)
    {
        if (user_data->f)
        {
            lv_fs_close(user_data->f);
            lv_mem_free(user_data->f);
        }
        lv_mem_free(user_data);
        dsc->user_data = NULL;
    }
    return LV_RES_INV;
}

static void png_decoder_close(lv_img_decoder_t *decoder, lv_img_decoder_dsc_t *dsc)
{
    (void)decoder; /*Unused*/

    lv_png_decoder_data_t *user_data = (lv_png_decoder_data_t *)dsc->user_data;
    if (user_data)
    {
        if (user_data->f)
        {
            lv_fs_close(user_data->f);
            lv_mem_free(user_data->f);
        }

        if (user_data->read_line_mode)
        {
            user_data->read_line_mode = 0;
            png_read_end(user_data->png_ptr, user_data->info_ptr);
            _png_free(user_data->png_ptr, (png_voidp)user_data->row_buf);
            user_data->png_ptr = NULL;
            png_destroy_read_struct(&user_data->png_ptr, &user_data->info_ptr, NULL);
        }
        else if (dsc->img_data != NULL)
        {
            _png_free(NULL, (png_voidp)dsc->img_data);
            dsc->img_data = NULL;
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
static lv_res_t png_decoder_read_line(lv_img_decoder_t *decoder, lv_img_decoder_dsc_t *dsc, lv_coord_t x,
                                      lv_coord_t y, lv_coord_t len, uint8_t *buf)
{
    (void)decoder; /*Unused*/

    unsigned width;
    int i;
    width = dsc->header.w;

    lv_png_decoder_data_t *user_data = dsc->user_data;
    if (!user_data)
    {
        printf("png_decoder_read_line failed for empty user_data\n");
        return LV_RES_INV;
    }

    if (user_data->info_ptr->interlace_type != PNG_INTERLACE_NONE)
    {
        printf("error: readline does not support interlaced png\n");
        return LV_RES_INV;
    }

    if (!user_data->row_buf)
    {
        printf("error: no mem for readline\n");
        return LV_RES_INV;
    }

    for (i = user_data->row_curr; i <= y; i++)
    {
        png_read_row(user_data->png_ptr, user_data->row_buf, NULL);
        user_data->row_curr++;
    }

    if (dsc->header.cf == LV_IMG_CF_RAW_ALPHA)
    {
        lv_color_rgba8888_to_16_alpha((lv_color_rgba8888_t *)user_data->row_buf, (lv_color16_alpha_t *)user_data->row_buf, width);
    }
    else
    {
        lv_color_rgb888_to_16((lv_color_rgb888_t *)user_data->row_buf, (lv_color16_t *)user_data->row_buf, width);
    }

    memcpy(buf, user_data->row_buf + x, len * user_data->pixel_size_lv);

    return LV_RES_OK;
}

static bool png_decoder_check_type(const void *src)
{
    int ret = 0;
    const lv_img_dsc_t *img_src = (const lv_img_dsc_t *)src;

    /* img_src->data is file path */
    if (img_src->header.reserved == 1)
    {
        /* png in romfs or psram need has ext as ".png", so no need open file to verify signature here.
         * Suggest the file received from voice message saved in nvm add ext ".png" by code also.
         */
        const char *fn = (const char *)img_src->data;
        if (!strcmp(lv_fs_get_ext(fn), "png"))
        {
            return true;
        }
        else
        {
            //printf("the file path from img_src->data is not .png\n");
            return false;
        }
    }
    else
    {
        if ((img_src->data_size) >= LV_PNG_SIGNATURE_LEN)
        {
            ret = png_check_sig(img_src->data, LV_PNG_SIGNATURE_LEN);
        }
    }
    return (ret != 0);
}

/**
 * Get info about a PNG image
 * @param src can be file name or pointer to a C array
 * @param header store the info here
 * @return LV_RES_OK: no error; LV_RES_INV: can't get the info
 */
static lv_res_t png_decoder_info(struct _lv_img_decoder *decoder, const void *src, lv_img_header_t *header)
{
    (void)decoder;                                    /*Unused*/
    lv_img_src_t src_type = lv_img_src_get_type(src); /*Get the source type*/

    /*If it's a PNG file...*/
    /*A PNG file, not support Zoom in, show original size*/
    if (src_type == LV_IMG_SRC_FILE)
    {
        const char *fn = src;
        /*Support only "*.png" files*/
        if (strcmp(lv_fs_get_ext(fn), "png"))
            return LV_RES_INV;

        lv_fs_res_t ret;
        lv_fs_file_t f;
        ret = lv_fs_open(&f, fn, LV_FS_MODE_RD);
        if (ret != LV_FS_RES_OK)
        {
            printf("[%s]: lv_fs_open failed\n", __func__);
            return LV_RES_INV;
        }

        ret = lv_fs_seek(&f, 16);
        if (ret != LV_FS_RES_OK)
        {
            printf("[%s]: lv_fs_open failed\n", __func__);
            return LV_RES_INV;
        }

        uint32_t size[2];
        uint32_t br;
        ret = lv_fs_read(&f, (void *)size, 8, &br);
        if (ret != LV_FS_RES_OK || br != 8)
        {
            printf("[%s]: lv_fs_read failed\n", __func__);
            return LV_RES_INV;
        }

        lv_fs_close(&f);

        /*Save the data in the header*/
        header->always_zero = 0;
        header->cf = LV_IMG_CF_RAW_ALPHA;
        header->reserved = 1; //if reserved = 1. means file
        /*The width and height are stored in Big endian format so convert them to little endian*/
        header->w = (lv_coord_t)((size[0] & 0xff000000) >> 24) + ((size[0] & 0x00ff0000) >> 8);
        header->h = (lv_coord_t)((size[1] & 0xff000000) >> 24) + ((size[1] & 0x00ff0000) >> 8);

        return LV_RES_OK;
    }
    /*If it's a PNG file in a  C array...*/
    /* C array supports PNG zoom in:
     * the w and h from header of src is the target show size,
     * the w and h from info read from png binary is original size,
     * src->data can be png binary(header->reserved = 0) or png file(header->reserved = 1, in PSRAM or ROMFS),
     * header->cf = LV_IMG_CF_RAW_ALPHA;
     */
    else if (src_type == LV_IMG_SRC_VARIABLE)
    {
        if (!png_decoder_check_type(src))
            return LV_RES_INV;
        const lv_img_dsc_t *img_dsc = src;
        header->always_zero = 0;
        header->cf = img_dsc->header.cf; /*Save the color format*/
        header->reserved = img_dsc->header.reserved;
        header->w = img_dsc->header.w; /*Save the color width*/
        header->h = img_dsc->header.h; /*Save the color height*/
        return LV_RES_OK;
    }

    return LV_RES_INV; /*If didn't succeeded earlier then it's an error*/
}

void lv_color_rgba8888_to_16_alpha(lv_color_rgba8888_t *in, lv_color16_alpha_t *out, int px_cnt)
{
    for (int px = 0; px < px_cnt; px++)
    {
        out->c = LV_COLOR_MAKE(in->r, in->g, in->b);
        out->a = in->a;
        in++;
        out++;
    }
}

lv_res_t lv_png_get_img_dsc(const void *data_buf, uint32_t data_size, lv_img_dsc_t *img_dsc)
{
    uint32_t size[2];
    if (data_buf == NULL || img_dsc == NULL || (data_size < (16+8)))
    {
        LOGE("invaild input");
        goto  err;
    }

    memcpy(&size, data_buf + 16, 8);

    img_dsc->header.always_zero = 0;
    img_dsc->header.cf = LV_IMG_CF_RAW_ALPHA;
    img_dsc->header.reserved = 0; //if reserved = 1. means file

    /*The width and height are stored in Big endian format so convert them to little endian*/
    img_dsc->header.w = (lv_coord_t)((size[0] & 0xff000000) >> 24) + ((size[0] & 0x00ff0000) >> 8);
    img_dsc->header.h = (lv_coord_t)((size[1] & 0xff000000) >> 24) + ((size[1] & 0x00ff0000) >> 8);
    img_dsc->data = data_buf;
    img_dsc->data_size = data_size;

    return LV_RES_OK;

err:

    return LV_RES_INV;
}


/**
 * Register the PNG decoder functions in LittlevGL
 */
void lv_png_decoder_init(void)
{
    lv_img_decoder_t *dec = lv_img_decoder_create();
    lv_img_decoder_set_info_cb(dec, png_decoder_info);
    lv_img_decoder_set_open_cb(dec, png_decoder_open);
    lv_img_decoder_set_read_line_cb(dec, png_decoder_read_line);
    lv_img_decoder_set_close_cb(dec, png_decoder_close);
}


#endif /* USE_LV_IMG_PNG_DECODER */
