cmake_minimum_required(VERSION 3.5)

project(lv_lib_png LANGUAGES C)

set(lv_png_decoder_src lv_img_png_decoder.c)

set(libpng_src  libpng/png.c 
                libpng/pngerror.c 
                libpng/pngget.c 
                libpng/pngmem.c 
                libpng/pngpread.c 
                libpng/pngread.c 
                libpng/pngrio.c 
                libpng/pngrtran.c 
                libpng/pngrutil.c 
                libpng/pngset.c 
                libpng/pngtrans.c 
                libpng/pngwio.c 
                libpng/pngwrite.c 
                libpng/pngwtran.c 
                libpng/pngwutil.c 
        )

set(zlib_src    zlib/adler32.c 
                zlib/compress.c 
                zlib/crc32.c 
                zlib/deflate.c 
                zlib/infback.c 
                zlib/inffast.c 
                zlib/inflate.c 
                zlib/inftrees.c 
                zlib/trees.c 
                zlib/uncompr.c 
                zlib/zutil.c 
            )
 
add_library(zlib STATIC ${zlib_src})

add_library(libpng STATIC ${libpng_src})
target_link_libraries(libpng PRIVATE zlib)

add_library(lv_lib_png STATIC ${lv_png_decoder_src})
target_link_libraries(lv_lib_png PRIVATE libpng)



target_include_directories(lv_lib_png PUBLIC
    ${EXTERNAL_DIR}/
    ${EXTERNAL_DIR}/lv_lib_png
    ${EXTERNAL_DIR}/lv_lib_png/libpng
    ${EXTERNAL_DIR}/lv_lib_png/zlib
    ${EXTERNAL_DIR}/lv_lib_jpg
)
