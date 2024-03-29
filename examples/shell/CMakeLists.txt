cmake_minimum_required(VERSION 3.15)

# file(READ proj.conf PROJ_CONFIG)
message("PROJ_CONFIG:")

set(SRC_CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/proj.conf)
set(TARGET_CONFIG ${CMAKE_CURRENT_BINARY_DIR}/proj.conf)
set(TOP_KCONFIG_CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/kconfig)
execute_process(
    COMMAND python $ENV{SDK_BASE}/tools/kconfig/genconfig.py ${TOP_KCONFIG_CONFIG} --config-out=${SRC_CONFIG}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

file(COPY ${SRC_CONFIG} DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})

set(TARGET_CMAKE ${CMAKE_CURRENT_BINARY_DIR}/proj.cmake)
execute_process(
    COMMAND python $ENV{SDK_BASE}/tools/kconfig/cmakeconfig.py ${TARGET_CONFIG} ${TARGET_CMAKE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

include(${TARGET_CMAKE})


message("example_shell start")

find_package(qt_idf_sdk REQUIRED HINTS $ENV{SDK_BASE})

# sdk_set_linker_script(template.ld)
sdk_add_subdirectory_if_exist(cmds)

sdk_set_main_file(main.c)

sdk_add_include_directories(.)

project(shell)

message("example_shell end")
