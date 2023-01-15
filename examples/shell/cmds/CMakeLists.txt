message("cmds")

sdk_generate_library()
file(GLOB_RECURSE SOURCES ./*.c)
sdk_library_add_sources(${SOURCES})
# if(CONFIG_LVGL) 
# sdk_add_compile_definitions("-DLV_CONF_INCLUDE_SIMPLE" "-DLV_LVGL_H_INCLUDE_SIMPLE")
# endif()

sdk_add_include_directories(inc Smart_Gadget)