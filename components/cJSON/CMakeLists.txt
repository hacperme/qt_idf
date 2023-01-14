message("cJSON")

sdk_generate_library()
sdk_library_add_sources(cJSON.c
                        cJSON_Utils.c)

sdk_add_include_directories(.)