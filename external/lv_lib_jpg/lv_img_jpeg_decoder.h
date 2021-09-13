#ifndef _LV_IMG_JPEG_DECODER_H_
#define _LV_IMG_JPEG_DECODER_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "lv_conf.h"

#if USE_LV_IMG_JPEG_DECODER

#include "lvgl/lvgl.h"

typedef struct {
    uint8_t r; /* lowest byte */
    uint8_t g;
    uint8_t b;
}__attribute__((packed))lv_color_rgb888_t;


void lv_jpeg_decoder_init(void);

void lv_color_rgb888_to_16(lv_color_rgb888_t *in, lv_color16_t *out, int px_cnt);

lv_res_t lv_jpeg_get_img_dsc(const void *data_buf, uint32_t data_size, lv_img_dsc_t *img_dsc);

#endif /* USE_LV_IMG_JPEG_DECODER */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _LV_IMG_JPEG_DECODER_H_ */

