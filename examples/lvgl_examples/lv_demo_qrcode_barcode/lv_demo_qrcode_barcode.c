#include "lv_ex_conf.h"

#if LV_USE_DEMO_QRCODE_BARCODE
#include "lv_demo_qrcode_barcode.h"
#include "lvgl/lvgl.h"
#include "lv_qrcode.h"

#include "lvgl/lvgl.h"
#include "lv_qrcode.h"
#include "lv_lib_barcode.h"
#include "lv_freetype.h"

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

  /*Init freetype library
   *Cache max 64 faces and 1 size*/
  lv_freetype_init(64, 1, 0);

  /*Create a font*/
  static lv_ft_info_t info;
  info.name = "D:/STCAIYUN.TTF";
  info.weight = 30;
  info.style = FT_FONT_STYLE_NORMAL;
  lv_ft_font_init(&info);

  /*Create style with the new font*/
  static lv_style_t style;
  lv_style_init(&style);
  lv_style_set_text_font(&style, LV_STATE_DEFAULT, info.font);

  /*Create a label with the new style*/
  label = lv_label_create(lv_scr_act(), NULL);
  lv_obj_add_style(label, LV_OBJ_PART_MAIN, &style);
  lv_label_set_text(label, "扫一扫");
  lv_obj_align(label, cont, LV_ALIGN_OUT_TOP_MID, 0, 0);
}

#endif
