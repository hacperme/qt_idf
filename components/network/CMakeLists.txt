message("network")

sdk_generate_library()
file(GLOB_RECURSE SOURCES src/*.c)
sdk_library_add_sources(${SOURCES})
sdk_add_include_directories(inc)

if(CONFIG_MBEDTLS_DYNAMIC_BUFFER)
    sdk_add_link_options(
        -Wl,--wrap=mbedtls_ssl_write_client_hello
        -Wl,--wrap=mbedtls_ssl_handshake_client_step
        -Wl,--wrap=mbedtls_ssl_handshake_server_step
        -Wl,--wrap=mbedtls_ssl_read
        -Wl,--wrap=mbedtls_ssl_write
        -Wl,--wrap=mbedtls_ssl_session_reset
        -Wl,--wrap=mbedtls_ssl_free
        -Wl,--wrap=mbedtls_ssl_setup
        -Wl,--wrap=mbedtls_ssl_send_alert_message
        -Wl,--wrap=mbedtls_ssl_close_notify
)

endif()