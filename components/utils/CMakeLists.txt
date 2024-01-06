message("utils")

sdk_generate_library()
file(GLOB_RECURSE SOURCES src/*.c)
sdk_library_add_sources(${SOURCES})
sdk_add_include_directories(inc)