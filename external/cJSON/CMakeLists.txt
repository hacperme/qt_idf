cmake_minimum_required(VERSION 3.5)

if(CONFIG_CJSON_ENABLE)
project(cJSON LANGUAGES C)

    set(cJSON_sources
        cJSON.c
        cJSON_Utils.c
       )

add_library(cJSON STATIC ${cJSON_sources})
endif()
