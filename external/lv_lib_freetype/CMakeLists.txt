cmake_minimum_required(VERSION 3.5)


project(lv_lib_freetype LANGUAGES C)

set(freetype_src    freetype/freetype/src/autofit/autofit.c 
                    freetype/freetype/src/base/ftbase.c 
                    freetype/freetype/src/base/ftbbox.c 
                    freetype/freetype/src/base/ftbdf.c 
                    freetype/freetype/src/base/ftbitmap.c 
                    freetype/freetype/src/base/ftcid.c 
                    freetype/freetype/src/base/ftdebug.c 
                    freetype/freetype/src/base/ftfstype.c 
                    freetype/freetype/src/base/ftgasp.c 
                    freetype/freetype/src/base/ftglyph.c 
                    freetype/freetype/src/base/ftgxval.c 
                    freetype/freetype/src/base/ftinit.c 
                    freetype/freetype/src/base/ftmm.c 
                    freetype/freetype/src/base/ftotval.c 
                    freetype/freetype/src/base/ftpatent.c 
                    freetype/freetype/src/base/ftpfr.c 
                    freetype/freetype/src/base/ftstroke.c 
                    freetype/freetype/src/base/ftsynth.c 
                    freetype/freetype/src/base/ftsystem.c 
                    freetype/freetype/src/base/fttype1.c 
                    freetype/freetype/src/base/ftwinfnt.c 
                    freetype/freetype/src/bdf/bdf.c 
                    freetype/freetype/src/bzip2/ftbzip2.c 
                    freetype/freetype/src/cache/ftcache.c 
                    freetype/freetype/src/cff/cff.c 
                    freetype/freetype/src/cid/type1cid.c 
                    freetype/freetype/src/dlg/dlg.c 
                    freetype/freetype/src/gzip/ftgzip.c 
                    freetype/freetype/src/lzw/ftlzw.c 
                    freetype/freetype/src/pcf/pcf.c 
                    freetype/freetype/src/pfr/pfr.c 
                    freetype/freetype/src/psaux/psaux.c 
                    freetype/freetype/src/pshinter/pshinter.c 
                    freetype/freetype/src/psnames/psnames.c 
                    freetype/freetype/src/raster/raster.c 
                    freetype/freetype/src/sdf/sdf.c 
                    freetype/freetype/src/sfnt/sfnt.c 
                    freetype/freetype/src/smooth/smooth.c 
                    freetype/freetype/src/svg/svg.c 
                    freetype/freetype/src/truetype/truetype.c 
                    freetype/freetype/src/type1/type1.c 
                    freetype/freetype/src/type42/type42.c 
                    freetype/freetype/src/winfonts/winfnt.c 
)

set(lv_lib_freetype_src lv_freetype.c)

add_library(freetype STATIC ${freetype_src})
target_compile_definitions(freetype PUBLIC 
    -DFT_CONFIG_CONFIG_H=<ftconfig.h>
    -DFT_CONFIG_MODULES_H=<ftmodule.h>
    -DFT_CONFIG_OPTIONS_H=<ftoption.h>
    -DFT2_BUILD_LIBRARY )

    target_include_directories(freetype PUBLIC
    freetype/freetype/include
    freetype/freetype/include/freetype 
    freetype/freetype/include/freetype/internal 
    freetype/freetype/include/freetype/internal/services 
    freetype/freetype/include/freetype/config 
    freetype/freetype/objs 
    freetype/freetype/devel 
    freetype/freetype/builds/unix 
)

add_library(lv_lib_freetype STATIC ${lv_lib_freetype_src})
target_link_libraries(lv_lib_freetype PRIVATE freetype)

target_include_directories(lv_lib_freetype PUBLIC
    ${EXTERNAL_DIR}/
    ${EXTERNAL_DIR}/lv_lib_freetype
)
