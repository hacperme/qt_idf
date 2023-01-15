message("lvgl_examples")

sdk_generate_library(lvgl_examples)
file(GLOB_RECURSE SOURCES ./*.c)
sdk_library_add_sources(${SOURCES})
# sdk_add_compile_definitions("-DLV_CONF_INCLUDE_SIMPLE")
sdk_add_include_directories(.)