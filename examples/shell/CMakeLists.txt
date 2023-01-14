cmake_minimum_required(VERSION 3.15)

# file(READ proj.conf PROJ_CONFIG)
# message("PROJ_CONFIG:${PROJ_CONFIG}")

message("example_shell start")

find_package(qt_idf_sdk REQUIRED HINTS $ENV{SDK_BASE})

# sdk_set_linker_script(template.ld)
sdk_add_subdirectory_if_exist(cmds)

sdk_set_main_file(main.c)

project(shell)

message("example_shell end")
