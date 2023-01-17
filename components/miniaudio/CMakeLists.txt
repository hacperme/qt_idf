message("miniaudio")

sdk_generate_library(miniaudio)
sdk_library_add_sources(miniaudio.c)

sdk_add_include_directories(.)