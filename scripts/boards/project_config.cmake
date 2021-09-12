set(PROJECT_CONFIG_FILE_OUT "${ROOT_DIR}/include/project_config.h")


set(PROJECT_CONFIG_FILE "${ROOT_DIR}/scripts/boards/project_default_config.h.in")

option(CONFIG_CJSON_ENABLE "CONFIG_CJSON_ENABLE" ON)
option(CONFIG_MBEDTLS_ENABLE "CONFIG_MBEDTLS_ENABLE" ON)
option(CONFIG_IOTKIT_ENABLE "CONFIG_IOTKIT_ENABLE" ON)

option(CONFIG_BUILD_EXAMPLES_ENABLE "CONFIG_BUILD_EXAMPLES_ENABLE" ON)
if(CONFIG_BUILD_EXAMPLES_ENABLE)
  option(CONFIG_BUILD_LINKIT_EXAMPLES_ENABLE "CONFIG_BUILD_LINKIT_EXAMPLES_ENABLE" ON)
endif()


if(CONFIG_IOTKIT_ENABLE)
  if(NOT CONFIG_MBEDTLS_ENABLE OR NOT CONFIG_CJSON_ENABLE)
  message(FATAL_ERROR "IOTKIT depends on CJSON and MBEDTLS")
  endif()
endif()

# option(FOO_ENABLE "Enable Foo" ON)
# if(FOO_ENABLE)
#   set(FOO_STRING "foo")
# endif()

configure_file(${PROJECT_CONFIG_FILE} ${PROJECT_CONFIG_FILE_OUT} @ONLY)

include_directories("${ROOT_DIR}/include/")
