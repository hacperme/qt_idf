cmake_minimum_required(VERSION 3.5)

project(qt_idf LANGUAGES C)

set(qt_idf_sources
    main.c
   )

set(OBJS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/output)

get_filename_component(EXTERNAL_DIR "external" REALPATH)
add_subdirectory(${EXTERNAL_DIR}/iotkit-embedded iotkit_sdk)
add_subdirectory(${EXTERNAL_DIR}/iotkit-embedded/wrappers iotkit_wrappers)
add_subdirectory(${EXTERNAL_DIR}/cJSON cJSON)
add_subdirectory(${EXTERNAL_DIR}/mbedtls mbedtls)

set (LIBRARY_OUTPUT_PATH ${OBJS_PATH}/libs)
set (EXECUTABLE_OUTPUT_PATH ${OBJS_PATH}/bin)

add_executable(qt_idf ${qt_idf_sources})

target_link_libraries(qt_idf iotkit_sdk)

target_include_directories(qt_idf PUBLIC
    ${EXTERNAL_DIR}/iotkit-embedded/src/infra
    ${EXTERNAL_DIR}/iotkit-embedded/wrappers
    ${EXTERNAL_DIR}/iotkit-embedded/src/mqtt
    ${EXTERNAL_DIR}/iotkit-embedded/src/atm
    ${EXTERNAL_DIR}/iotkit-embedded/src/coap
    ${EXTERNAL_DIR}/iotkit-embedded/src/coap/client
    ${EXTERNAL_DIR}/iotkit-embedded/src/coap/server
    ${EXTERNAL_DIR}/iotkit-embedded/src/coap/CoAPPacket
    ${EXTERNAL_DIR}/iotkit-embedded/src/dev_bind
    ${EXTERNAL_DIR}/iotkit-embedded/src/http
    ${EXTERNAL_DIR}/iotkit-embedded/src/dev_model
    ${EXTERNAL_DIR}/iotkit-embedded/src/dev_model/client
    ${EXTERNAL_DIR}/iotkit-embedded/src/dev_sign
    ${EXTERNAL_DIR}/iotkit-embedded/src/dynamic_register
    ${EXTERNAL_DIR}/iotkit-embedded/src/http
    ${EXTERNAL_DIR}/iotkit-embedded/src/http2
    ${EXTERNAL_DIR}/iotkit-embedded/src/ota
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/connectivity
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/dev_ap
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/frameworks
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/frameworks/aplist
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/frameworks/ieee80211
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/frameworks/utils
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/ht40
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/mcast_smartconfig
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/p2p
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/phone_ap
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/smartconfig
    ${EXTERNAL_DIR}/iotkit-embedded/src/wifi_provision/zero_config
    ${EXTERNAL_DIR}/cJSON

)
