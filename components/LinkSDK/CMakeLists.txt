message("LinkSDK")

sdk_generate_library()
file(GLOB_RECURSE SOURCES portfiles/*.c
    core/*.c
    components/*.c
    external/*.c)
sdk_library_add_sources(${SOURCES})
sdk_add_include_directories(
    core
    core/utils
    core/sysdep
    external/libdeflate
    external/nopoll/include
    components/bootstrap
    components/compress
    components/data-model
    components/devinfo
    components/diag
    components/dynreg
    components/dynreg-mqtt
    components/logpost
    components/mqtt_upload
    components/ntp
    components/ota
    components/remote-access
    components/remote-access/tunnel
    components/remote-access/tunnel/src
    components/remote-access/tunnel_switch
    components/shadow
    components/subdev
    components/task)

    sdk_add_link_libraries(ws2_32)