message("nr_micro_shell")

sdk_generate_library()
sdk_library_add_sources(src/ansi.c 
                        src/ansi_port.c
                        src/nr_micro_shell.c)

sdk_add_include_directories(inc)