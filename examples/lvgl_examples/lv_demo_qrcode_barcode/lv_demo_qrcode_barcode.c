#include "lv_ex_conf.h"

#if LV_USE_DEMO_QRCODE_BARCODE
#include "lv_demo_qrcode_barcode.h"
#include "lvgl/lvgl.h"
#include "lv_qrcode.h"

#include "lvgl/lvgl.h"
#include "lv_qrcode.h"
#include "lv_lib_barcode.h"

void lv_demo_qrcode_barcode(void)
{
    lv_obj_t *cont = NULL;
    lv_obj_t *qrcode = NULL;
    lv_obj_t *barcode = NULL, *label = NULL;
    const char *data = "[FNC1] 00 12345678 0000000001";

    cont = lv_cont_create(lv_scr_act(), NULL);
    lv_obj_set_auto_realign(cont, true);
    lv_obj_align_origo(cont, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_cont_set_fit(cont, LV_FIT_TIGHT);
    lv_cont_set_layout(cont, LV_LAYOUT_COLUMN_MID);

    barcode = lv_barcode_create(cont, 40, data);

    qrcode = lv_qrcode_create(cont, data, 0, 0, 4);

    lv_obj_align(barcode, cont, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align(qrcode, barcode, LV_ALIGN_OUT_BOTTOM_MID, 0, 8);
}

#endif
