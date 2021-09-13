cmake_minimum_required(VERSION 3.5)


project(lv_qrcode LANGUAGES C)

set(libqrcode_src   libqrencode/bitstream.c 
                    libqrencode/mask.c 
                    libqrencode/mmask.c 
                    libqrencode/mqrspec.c 
                    libqrencode/qrencode.c 
                    libqrencode/qrinput.c 
                    libqrencode/qrspec.c 
                    libqrencode/rsecc.c 
                    libqrencode/split.c 
)

set(lv_qrcode_src lv_qrcode.c)

add_library(libqrcode STATIC ${libqrcode_src})
target_compile_definitions(libqrcode PUBLIC "-DHAVE_CONFIG_H=1")

add_library(lv_qrcode STATIC ${lv_qrcode_src})
target_link_libraries(lv_qrcode PRIVATE libqrcode lvgl)

target_include_directories(lv_qrcode PUBLIC
    ${EXTERNAL_DIR}/
    ${EXTERNAL_DIR}/lv_lib_qrcode
    ${EXTERNAL_DIR}/lv_lib_qrcode/libqrencode
)
