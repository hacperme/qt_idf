message("lv_drivers")

sdk_generate_library()

file(GLOB_RECURSE SOURCES ./*.c  display/*.c gtkdrv/*.c indev/*.c)
sdk_library_add_sources(${SOURCES})
sdk_add_compile_definitions("-DLV_CONF_INCLUDE_SIMPLE" "-DLV_LVGL_H_INCLUDE_SIMPLE")
sdk_add_include_directories(. display gtkdrv indev win32drv)
