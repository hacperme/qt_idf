
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