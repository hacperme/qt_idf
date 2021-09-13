cmake_minimum_required(VERSION 3.5)

project(qt_idf LANGUAGES C)

get_filename_component(EXTERNAL_DIR "external" REALPATH)

set(OBJS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/output)
set (LIBRARY_OUTPUT_PATH ${OBJS_PATH}/libs)
set (EXECUTABLE_OUTPUT_PATH ${OBJS_PATH}/bin)

set(ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")

include(${ROOT_DIR}/scripts/boards/project_config.cmake)

set(qt_idf_sources
    main.c
   )

add_subdirectory(${EXTERNAL_DIR})
add_subdirectory(examples)

add_executable(qt_idf ${qt_idf_sources})


