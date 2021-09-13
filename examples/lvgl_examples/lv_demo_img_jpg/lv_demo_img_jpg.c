#include "lv_ex_conf.h"

#if LV_USE_DEMO_IMG_JPG
#include "lv_demo_img_jpg.h"
#include "lvgl/lvgl.h"
#include "example_testorigjpg.h"
#include "lv_img_jpeg_decoder.h"

void lv_demo_img_jpg(void)
{
    extern const raw_jpg_img_dsc_t test_jpg;
    LV_IMG_DECLARE(test_jpg_img); /*Declare the image file.*/
    static lv_img_dsc_t raw_jpg_img;

    lv_obj_t *img_obj1 = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(img_obj1, &test_jpg_img);

    lv_obj_t *img_obj2 = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(img_obj2, "P:Snipaste_2021-02-10_13-32-37.jpg");
    lv_obj_align(img_obj2, img_obj1, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *img_obj3 = lv_img_create(lv_scr_act(), NULL);
    lv_jpeg_get_img_dsc(test_jpg.data, test_jpg.size, &raw_jpg_img);
    lv_img_set_src(img_obj3, &raw_jpg_img);
    lv_obj_align(img_obj3, img_obj1, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
}

#endif
