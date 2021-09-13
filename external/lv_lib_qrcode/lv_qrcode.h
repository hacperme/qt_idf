#ifndef LV_QRCODE_H
#define LV_QRCODE_H

#ifdef __cplusplus
extern "C" {
#endif
#include "lv_conf.h"

#ifdef USE_LV_QRCODE

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
 * Create a qrcode object
 * @param par pointer to an object, it will be the parent of the new qrcode
 * @param cid the address of the string which end of '\0', it is the input data for the qrcode encoder
 * @param px x coordinate of the point to set
 * @param py y coordinate of the point to set
 * @param scale the scale of the original qrcode size
 * @return pointer to the new qrcode object
 */
lv_obj_t *lv_qrcode_create(lv_obj_t * par, const char *str, int px, int py, int scale);

#endif /* USE_LV_QRCODE */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_QRCODE_H */

