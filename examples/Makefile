SDK_DEMO_PATH = .

SDK_BASE ?= ${SDK_DEMO_PATH}/..

export SDK_BASE

CROSS_COMPILE ?=
#cmake definition config
cmake_definition+= -DCROSS_COMPILE=${CROSS_COMPILE}
cmake_definition+= -DCONFIG_NR_MICRO_SHELL=y
cmake_definition+= -DCONFIG_CJSON=y
cmake_definition+= -DCONFIG_LVGL=y
cmake_definition+= -DCONFIG_SDL2=y

include $(SDK_BASE)/project.build

