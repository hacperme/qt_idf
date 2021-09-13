cmake_minimum_required(VERSION 3.5)

project(lv_lib_jpg LANGUAGES C)

set(lv_jpg_decoder_src lv_img_jpeg_decoder.c)

set(libjpeg_src libjpeg-turbo/example/example_jpgdecode.c
        libjpeg-turbo/example/example_testorigjpg.c 
        libjpeg-turbo/jcapimin.c 
        libjpeg-turbo/jcapistd.c 
        libjpeg-turbo/jccoefct.c 
        libjpeg-turbo/jccolor.c 
        libjpeg-turbo/jcdctmgr.c 
        libjpeg-turbo/jchuff.c 
        libjpeg-turbo/jcinit.c 
        libjpeg-turbo/jcmainct.c 
        libjpeg-turbo/jcmarker.c 
        libjpeg-turbo/jcmaster.c 
        libjpeg-turbo/jcomapi.c 
        libjpeg-turbo/jcparam.c 
        libjpeg-turbo/jcphuff.c 
        libjpeg-turbo/jcprepct.c 
        libjpeg-turbo/jcsample.c 
        libjpeg-turbo/jctrans.c 
        libjpeg-turbo/jdapimin.c 
        libjpeg-turbo/jdapistd.c 
        libjpeg-turbo/jdatadst.c 
        libjpeg-turbo/jdatasrc.c 
        libjpeg-turbo/jdcoefct.c 
        libjpeg-turbo/jdcolor.c 
        libjpeg-turbo/jddctmgr.c 
        libjpeg-turbo/jdhuff.c 
        libjpeg-turbo/jdinput.c 
        libjpeg-turbo/jdmainct.c 
        libjpeg-turbo/jdmarker.c 
        libjpeg-turbo/jdmaster.c 
        libjpeg-turbo/jdmerge.c 
        libjpeg-turbo/jdphuff.c 
        libjpeg-turbo/jdpostct.c 
        libjpeg-turbo/jdsample.c 
        libjpeg-turbo/jdtrans.c 
        libjpeg-turbo/jerror.c 
        libjpeg-turbo/jfdctflt.c 
        libjpeg-turbo/jfdctfst.c 
        libjpeg-turbo/jfdctint.c 
        libjpeg-turbo/jidctflt.c 
        libjpeg-turbo/jidctfst.c 
        libjpeg-turbo/jidctint.c 
        libjpeg-turbo/jidctred.c 
        libjpeg-turbo/jquant1.c 
        libjpeg-turbo/jquant2.c 
        libjpeg-turbo/jutils.c 
        libjpeg-turbo/jmemmgr.c 
        libjpeg-turbo/jmemnobs.c 
        libjpeg-turbo/jdarith.c 
        libjpeg-turbo/jaricom.c 
        libjpeg-turbo/jsimd_none.c 
        libjpeg-turbo/jcarith.c
        )

add_library(libjpeg STATIC ${libjpeg_src})


add_library(lv_lib_jpg STATIC ${lv_jpg_decoder_src})

target_link_libraries(lv_lib_jpg PRIVATE libjpeg)



target_include_directories(lv_lib_jpg PUBLIC
    ${EXTERNAL_DIR}/
    ${EXTERNAL_DIR}/lv_lib_jpg
    ${EXTERNAL_DIR}/lv_lib_jpg/libjpeg-turbo
)
