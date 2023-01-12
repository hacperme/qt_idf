cmake_minimum_required(VERSION 3.5)

project(example_shell LANGUAGES C)


add_executable(example_shell example_shell.c
                             cmd/cmds.c
)

target_link_libraries(example_shell PRIVATE nr_micro_shell)

# target_include_directories(nr_micro_shell PRIVATE

# )
