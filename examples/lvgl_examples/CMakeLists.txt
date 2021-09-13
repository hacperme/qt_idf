cmake_minimum_required(VERSION 3.5)

project(lvgl_example LANGUAGES C)


add_executable(lvgl_example example_lvgl.c)



target_link_libraries(lvgl_example ${SDL2_LIBS} lv_drivers lvgl)

target_include_directories(lvgl_example PRIVATE
    ${EXTERNAL_DIR}/lvgl
    ${EXTERNAL_DIR}/lv_lib_jpg

)