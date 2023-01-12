
if(CONFIG_BUILD_EXAMPLES_ENABLE)
    if(CONFIG_BUILD_LINKIT_EXAMPLES_ENABLE)
    add_subdirectory(linkit_examples)
    endif()

    if(CONFIG_BUILD_LVGL_EXAMPLES_ENABLE)
    add_subdirectory(lvgl_examples)
    endif()

    if(CONFIG_BUILD_LIBWEBSOCKET_EXAMPLES_ENABLE)
    add_subdirectory(libwebsocket_examples)
    endif()

    if(CONFIG_BUILD_SHELL_EXAMPLES_ENABLE)
    add_subdirectory(shell)
    endif()
endif()
