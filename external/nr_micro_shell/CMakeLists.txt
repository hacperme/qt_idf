cmake_minimum_required(VERSION 3.5)


project(nr_micro_shell LANGUAGES C)

set(nr_micro_shell_src  src/nr_micro_shell.c 
                        src/ansi.c
                        src/ansi_port.c
)


add_library(nr_micro_shell STATIC ${nr_micro_shell_src})

target_include_directories(nr_micro_shell PUBLIC
    ${EXTERNAL_DIR}/
    ${EXTERNAL_DIR}/nr_micro_shell/inc
)
