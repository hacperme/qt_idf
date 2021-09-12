project(lvgl LANGUAGES C)

file(GLOB_RECURSE SOURCES src/*.c)
add_library(lvgl STATIC ${SOURCES})
target_compile_definitions(lvgl PUBLIC "-DLV_CONF_INCLUDE_SIMPLE")
