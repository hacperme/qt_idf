
if(CONFIG_CJSON_ENABLE)
add_subdirectory(${EXTERNAL_DIR}/cJSON cJSON)
endif()

if(CONFIG_MBEDTLS_ENABLE)
add_subdirectory(${EXTERNAL_DIR}/mbedtls mbedtls)
endif()


if(CONFIG_IOTKIT_ENABLE)
add_subdirectory(${EXTERNAL_DIR}/iotkit-embedded iotkit_sdk)
add_subdirectory(${EXTERNAL_DIR}/iotkit-embedded/wrappers iotkit_wrappers)
endif()

if(CONFIG_LVGL_ENABLE)
add_subdirectory(${EXTERNAL_DIR}/lvgl lvgl)
endif()

if(CONFIG_SDL2_ENABLE)
add_subdirectory(${EXTERNAL_DIR}/SDL2 SDL2)
endif()

if(CONFIG_LV_DRIVERS_ENABLE)
add_subdirectory(${EXTERNAL_DIR}/lv_drivers lv_drivers)
endif()

if(CONFIG_LV_FS_IF_ENABLE)
add_subdirectory(${EXTERNAL_DIR}/lv_fs_if lv_fs_if)
endif()

if(CONFIG_LV_LIB_JPG_ENABLE)
add_subdirectory(${EXTERNAL_DIR}/lv_lib_jpg lv_lib_jpg)
endif()
