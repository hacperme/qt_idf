cmake_minimum_required(VERSION 3.5)

project(mbedtls LANGUAGES C)

option(USE_STATIC_MBEDTLS_LIBRARY "Build mbed TLS static library." ON)
option(USE_SHARED_MBEDTLS_LIBRARY "Build mbed TLS shared library." OFF)
option(LINK_WITH_PTHREAD "Explicitly link mbed TLS library to pthread." OFF)

set(MBEDTLS_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(src_crypto
    library/aes.c
    library/asn1parse.c
    library/base64.c
    library/bignum.c
    library/cipher.c
    library/cipher_wrap.c
    library/ctr_drbg.c
    library/entropy.c
    library/entropy_poll.c
    library/error.c
    library/md.c
    library/md_wrap.c
    library/oid.c
    library/pem.c
    library/pk.c
    library/pk_wrap.c
    library/pkparse.c
    library/platform.c
    library/rsa.c
    library/sha1.c
    library/sha256.c
    library/timing.c
)

set(src_x509
    library/x509.c
    library/x509_crt.c
)

set(src_tls
    library/debug.c
    library/net_sockets.c
    library/ssl_ciphersuites.c
    library/ssl_cli.c
    library/ssl_cookie.c
    library/ssl_tls.c
)

if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-declarations -Wmissing-prototypes")
endif(CMAKE_COMPILER_IS_GNUCC)

if(CMAKE_COMPILER_IS_CLANG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-declarations -Wmissing-prototypes -Wdocumentation -Wno-documentation-deprecated-sync -Wunreachable-code")
endif(CMAKE_COMPILER_IS_CLANG)

if(UNSAFE_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-error")
    set(CMAKE_C_FLAGS_ASAN "${CMAKE_C_FLAGS_ASAN} -Wno-error")
    set(CMAKE_C_FLAGS_ASANDBG "${CMAKE_C_FLAGS_ASANDBG} -Wno-error")
endif(UNSAFE_BUILD)

if(WIN32)
    set(libs ${libs} ws2_32)
endif(WIN32)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(CMAKE_C_ARCHIVE_CREATE   "<CMAKE_AR> Scr <TARGET> <LINK_FLAGS> <OBJECTS>")
    SET(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> Scr <TARGET> <LINK_FLAGS> <OBJECTS>")
    SET(CMAKE_C_ARCHIVE_FINISH   "<CMAKE_RANLIB> -no_warning_for_no_symbols -c <TARGET>")
    SET(CMAKE_CXX_ARCHIVE_FINISH "<CMAKE_RANLIB> -no_warning_for_no_symbols -c <TARGET>")
endif()

if(HAIKU)
    set(libs ${libs} network)
endif(HAIKU)

if(USE_PKCS11_HELPER_LIBRARY)
    set(libs ${libs} pkcs11-helper)
endif(USE_PKCS11_HELPER_LIBRARY)

if(ENABLE_ZLIB_SUPPORT)
    set(libs ${libs} ${ZLIB_LIBRARIES})
endif(ENABLE_ZLIB_SUPPORT)

if(LINK_WITH_PTHREAD)
    set(libs ${libs} pthread)
endif()

if (NOT USE_STATIC_MBEDTLS_LIBRARY AND NOT USE_SHARED_MBEDTLS_LIBRARY)
    message(FATAL_ERROR "Need to choose static or shared mbedtls build!")
endif(NOT USE_STATIC_MBEDTLS_LIBRARY AND NOT USE_SHARED_MBEDTLS_LIBRARY)

if(USE_STATIC_MBEDTLS_LIBRARY AND USE_SHARED_MBEDTLS_LIBRARY)
    set(mbedtls_static_target "mbedtls_static")
    set(mbedx509_static_target "mbedx509_static")
elseif(USE_STATIC_MBEDTLS_LIBRARY)
    set(mbedtls_static_target "mbedtls")
    set(mbedx509_static_target "mbedx509")
endif()

if(USE_STATIC_MBEDTLS_LIBRARY)

    add_library(${mbedx509_static_target} STATIC ${src_x509})
    set_target_properties(${mbedx509_static_target} PROPERTIES OUTPUT_NAME mbedx509)
    target_link_libraries(${mbedx509_static_target} ${libs})
    target_include_directories(${mbedx509_static_target}
        PUBLIC ${MBEDTLS_DIR}/include/
        )
    add_library(${mbedtls_static_target} STATIC ${src_tls} ${src_crypto})
    set_target_properties(${mbedtls_static_target} PROPERTIES OUTPUT_NAME mbedtls)
    target_link_libraries(${mbedtls_static_target} ${libs} ${mbedx509_static_target})
    target_include_directories(${mbedtls_static_target}
        PUBLIC ${MBEDTLS_DIR}/include/
        )

endif(USE_STATIC_MBEDTLS_LIBRARY)

if(USE_SHARED_MBEDTLS_LIBRARY)

    add_library(mbedx509 SHARED ${src_x509})
    set_target_properties(mbedx509 PROPERTIES VERSION 2.19.1 SOVERSION 1)
    target_link_libraries(mbedx509 ${libs})
    target_include_directories(mbedx509
        PUBLIC ${MBEDTLS_DIR}/include/
        )
    add_library(mbedtls SHARED ${src_tls} ${src_crypto})
    set_target_properties(mbedtls PROPERTIES VERSION 2.19.1 SOVERSION 13)
    target_link_libraries(mbedtls ${libs} mbedx509)
    target_include_directories(mbedtls
        PUBLIC ${MBEDTLS_DIR}/include/
        )
endif(USE_SHARED_MBEDTLS_LIBRARY)



