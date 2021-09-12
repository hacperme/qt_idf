
add_custom_target(copy_SDL2_dll ALL DEPENDS ${EXECUTABLE_OUTPUT_PATH}/SDL2.dll)
add_custom_command(OUTPUT ${EXECUTABLE_OUTPUT_PATH}/SDL2.dll
                   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/win32/lib/SDL2.dll
                                                    ${EXECUTABLE_OUTPUT_PATH}/SDL2.dll
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/win32/lib/SDL2.dll)