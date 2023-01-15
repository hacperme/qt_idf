message("SDL2")

# sdk_generate_library()
# sdk_library_add_sources(src/ansi.c 
#                         src/ansi_port.c
#                         src/nr_micro_shell.c)

set(SDL2_LIB_PATH "i686-w64-mingw32")

# set(SDL2_LIBS "-lmingw32" "${CMAKE_CURRENT_SOURCE_DIR}/${SDL2_LIB_PATH}/lib/libSDL2main.a" 
#     "${CMAKE_CURRENT_SOURCE_DIR}/${SDL2_LIB_PATH}/lib/libSDL2.dll.a" 
#     "${CMAKE_CURRENT_SOURCE_DIR}/${SDL2_LIB_PATH}/lib/libSDL2.a"
#     "-mwindows"
# )

set(SDL2_LIBS "-lmingw32"
    "${CMAKE_CURRENT_SOURCE_DIR}/${SDL2_LIB_PATH}/lib/libSDL2main.a" 
    "${CMAKE_CURRENT_SOURCE_DIR}/${SDL2_LIB_PATH}/lib/libSDL2.dll.a" 
    "${CMAKE_CURRENT_SOURCE_DIR}/${SDL2_LIB_PATH}/lib/libSDL2.a"
)


sdk_add_link_libraries(${SDL2_LIBS})

sdk_add_include_directories(${SDL2_LIB_PATH}/include)

add_custom_target(copy_SDL2_dll ALL DEPENDS ${EXECUTABLE_OUTPUT_PATH}/SDL2.dll)
add_custom_command(OUTPUT ${EXECUTABLE_OUTPUT_PATH}/SDL2.dll
                   COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${SDL2_LIB_PATH}/bin/SDL2.dll
                                                    ${EXECUTABLE_OUTPUT_PATH}/SDL2.dll
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${SDL2_LIB_PATH}/bin/SDL2.dll)

# include(cmake/sdl2-config.cmake)
# include(cmake/sdl2-config-version.cmake)