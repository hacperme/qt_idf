cmake_minimum_required(VERSION 3.5)

if(CONFIG_LV_LIB_BARCODE_ENABLE)

project(lv_lib_barcode LANGUAGES C)

set(code128_src code128/code128.c)

set(lv_lib_barcode_src lv_lib_barcode.c)

add_library(code128 STATIC ${code128_src})

add_library(lv_lib_barcode STATIC ${lv_lib_barcode_src})

target_link_libraries(lv_lib_barcode PRIVATE code128 lvgl)

target_include_directories(lv_lib_barcode PUBLIC
    ${EXTERNAL_DIR}/
    ${EXTERNAL_DIR}/lv_lib_barcode
    ${EXTERNAL_DIR}/lv_lib_barcode/code128
)

endif()

