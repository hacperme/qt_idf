project(lvgl LANGUAGES C)

file(GLOB_RECURSE SOURCES src/*.c)

add_library(lvgl STATIC ${SOURCES})

target_compile_definitions(lvgl PUBLIC "-DLV_CONF_INCLUDE_SIMPLE")

if(CONFIG_LV_DRIVERS_ENABLE)
    target_link_libraries(lvgl  lv_drivers)
endif()

if(CONFIG_LV_DRIVERS_ENABLE)
    target_link_libraries(lvgl  lv_fs_if)
endif()
