cmake_minimum_required(VERSION 3.5)

if(CONFIG_LV_FS_IF_ENABLE)
project(lv_fs_if LANGUAGES C)

file(GLOB_RECURSE SOURCES ./*.c)

add_library(lv_fs_if STATIC ${SOURCES})

target_include_directories(lv_fs_if PUBLIC
    ${EXTERNAL_DIR}/
)

endif()
