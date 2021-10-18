cmake_minimum_required(VERSION 3.5)

project(libwebsocket_example LANGUAGES C)


add_executable(libwebsocket_example example_libwebsocket.c)

target_link_libraries(libwebsocket_example PRIVATE libwebsocket)
