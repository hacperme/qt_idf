cmake_minimum_required(VERSION 3.5)

project(iotkit_wrappers LANGUAGES C)

if (WIN32)
    set(iotkit_wrappers_sources
        os/windows/HAL_OS_win.c
        os/windows/HAL_AWSS_win.c
        os/windows/HAL_FS_win.c
        os/windows/HAL_KV_win.c
        os/windows/HAL_TCP_win.c
        os/windows/HAL_UART_win.c
        os/windows/HAL_UDP_win.c
        tls/HAL_TLS_mbedtls.c
       )
endif (WIN32)

add_library(iotkit_wrappers STATIC ${iotkit_wrappers_sources})

target_link_libraries(iotkit_wrappers mbedtls iphlpapi)

target_include_directories(iotkit_wrappers PRIVATE
    ${EXTERNAL_DIR}/iotkit-embedded/src/infra
    ${EXTERNAL_DIR}/iotkit-embedded/wrappers
)
