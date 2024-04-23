message("utils")

sdk_generate_library()
file(GLOB_RECURSE SOURCES src/*.c)
sdk_library_add_sources(${SOURCES})
sdk_add_include_directories(inc)

sdk_add_link_options(
        -Wl,--wrap=malloc
        -Wl,--wrap=_malloc_r
        -Wl,--wrap=free
        -Wl,--wrap=calloc
        -Wl,--wrap=realloc
        -Wl,--wrap=_free_r
        -Wl,--wrap=_realloc_r
)
