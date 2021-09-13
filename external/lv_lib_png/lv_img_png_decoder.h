#ifndef LV_IMG_PNG_DECODER_H
#define LV_IMG_PNG_DECODER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"

#if USE_LV_IMG_PNG_DECODER

typedef union
{
    struct
    {
        uint8_t r; /* lowest byte */
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
    uint32_t full;
} lv_color_rgba8888_t;

typedef struct
{
    lv_color16_t c;
    uint8_t a;
} __attribute__((packed)) lv_color16_alpha_t;

void lv_color_rgba8888_to_16_alpha(lv_color_rgba8888_t *in, lv_color16_alpha_t *out, int px_cnt);

lv_res_t lv_png_get_img_dsc(const void *data_buf, uint32_t data_size, lv_img_dsc_t *img_dsc);

extern void lv_png_decoder_init(void);

#endif /* USE_LV_IMG_PNG_DECODER */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_IMG_PNG_DECODER_H */

