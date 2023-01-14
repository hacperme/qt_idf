message("cmds")

sdk_generate_library()
sdk_library_add_sources(cmds.c)

sdk_add_include_directories(inc)