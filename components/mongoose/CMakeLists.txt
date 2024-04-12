message("MICROECC")

sdk_generate_library()
# file(GLOB_RECURSE SOURCES src/*.c)
sdk_library_add_sources(mongoose.c)
sdk_add_compile_definitions("-DMG_TLS=MG_TLS_MBED")
sdk_add_include_directories(../mongoose)