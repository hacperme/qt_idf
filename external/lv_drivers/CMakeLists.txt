cmake_minimum_required(VERSION 3.5)

project(lv_drivers LANGUAGES C)

file(GLOB_RECURSE SOURCES ./*.c  display/*.c gtkdrv/*.c indev/*.c)

add_library(lv_drivers STATIC ${SOURCES})

set(SDL2_LIBS "-lmingw32" "${EXTERNAL_DIR}/SDL2/win32/lib/libSDL2main.a" 
    "${EXTERNAL_DIR}/SDL2/win32/lib/libSDL2.dll.a" 
    "${EXTERNAL_DIR}/SDL2/win32/lib/libSDL2.a"
    "-mwindows"
)


target_link_libraries(lv_drivers ${SDL2_LIBS})

target_compile_definitions(lv_drivers PUBLIC "-DLV_CONF_INCLUDE_SIMPLE" "-DLV_LVGL_H_INCLUDE_SIMPLE")

target_include_directories(lv_drivers PUBLIC
    ${EXTERNAL_DIR}/
    ${EXTERNAL_DIR}/lvgl
    ${EXTERNAL_DIR}/SDL2/win32/include
)
