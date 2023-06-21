message("dlg")

sdk_generate_library()
file(GLOB_RECURSE SOURCES src/dlg/*.c)
# sdk_add_compile_definitions("-DLG_STATIC")
sdk_library_add_sources(${SOURCES})
sdk_add_include_directories(include)
