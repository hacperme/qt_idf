#ifndef LV_LIB_BARCODE_H
#define LV_LIB_BARCODE_H

#ifdef __cplusplus
extern "C" {
#endif
#include "lv_conf.h"

#ifdef USE_LV_BARCODE

#include "lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a barcode object
 * @param par pointer to an object, it will be the parent of the new qrcode
 * @param height the barcode height to be shown
 * @param data the input string to be encoded
 * @return pointer to the new barcode object
 */
lv_obj_t *lv_barcode_create(lv_obj_t * par, int height, const char *data);

#endif /* USE_LV_BARCODE */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_LIB_BARCODE_H */

