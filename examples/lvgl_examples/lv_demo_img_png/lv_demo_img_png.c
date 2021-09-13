#include "lv_ex_conf.h"

#if LV_USE_DEMO_IMG_PNG
#include "lv_demo_img_png.h"
#include "lvgl/lvgl.h"
#include "testorigpng.h"
#include "lv_img_png_decoder.h"

void lv_demo_img_png(void)
{
    extern const raw_png_img_dsc_t test_png;
    static lv_img_dsc_t raw_png_img;
    LV_IMG_DECLARE(sn_pc); /*Declare the image file.*/

    lv_obj_t *img_obj1 = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(img_obj1, "P:icon_sunny.png");

    lv_obj_t *img_obj2 = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(img_obj2, &sn_pc);
    lv_obj_align(img_obj2, img_obj1, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

    lv_obj_t *img_obj3 = lv_img_create(lv_scr_act(), NULL);
    lv_png_get_img_dsc(test_png.data, test_png.size, &raw_png_img);
    lv_img_set_src(img_obj3, &raw_png_img);
    lv_obj_align(img_obj3, img_obj2, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
}

#endif
