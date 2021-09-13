cmake_minimum_required(VERSION 3.5)

project(lvgl_example LANGUAGES C)


add_executable(lvgl_example example_lvgl.c
                            lv_demo_img_jpg/lv_demo_img_jpg.c
                            lv_demo_img_jpg/test_jpg_img.c
                            lv_demo_img_png/lv_demo_img_png.c
                            lv_demo_img_png/sn_pc.c
                            lv_demo_img_png/testorigpng.c
                            lv_demo_qrcode/lv_demo_qrcode.c
)



target_link_libraries(lvgl_example  lvgl)

target_include_directories(lvgl_example PRIVATE
    ${EXTERNAL_DIR}/lvgl
    ${EXTERNAL_DIR}/lv_lib_jpg
    ${EXTERNAL_DIR}/lv_lib_jpg/libjpeg-turbo/example
    ${EXTERNAL_DIR}/lv_lib_png
    ${EXTERNAL_DIR}/lv_lib_qrcode
    
)