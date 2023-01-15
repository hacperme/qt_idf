message("lvgl")

sdk_generate_library()
file(GLOB_RECURSE SOURCES src/*.c)
sdk_library_add_sources(${SOURCES})
sdk_add_compile_definitions("-DLV_CONF_INCLUDE_SIMPLE")
sdk_add_include_directories(.)