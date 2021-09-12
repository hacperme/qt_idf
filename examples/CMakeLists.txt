
if(CONFIG_BUILD_EXAMPLES_ENABLE)
    if(CONFIG_BUILD_LINKIT_EXAMPLES_ENABLE)
    add_subdirectory(linkit_examples linkit_examples)
    endif()

    if(CONFIG_BUILD_LVGL_EXAMPLES_ENABLE)
    add_subdirectory(lvgl_examples lvgl_examples)
    endif()
endif()