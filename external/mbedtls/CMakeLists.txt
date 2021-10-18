project(mbedtls LANGUAGES C)

file(GLOB_RECURSE SOURCES *.c)

add_library(mbedtls STATIC ${SOURCES})

target_link_libraries(mbedtls  -lws2_32)

target_include_directories(mbedtls PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)
