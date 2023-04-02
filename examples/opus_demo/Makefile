SDK_DEMO_PATH = .

SDK_BASE ?= ${SDK_DEMO_PATH}/../..

KCONFIG_CONFIG ?= ${SDK_DEMO_PATH}/proj.conf

export SDK_BASE
export KCONFIG_CONFIG

CROSS_COMPILE ?=
#cmake definition config
cmake_definition+= -DCROSS_COMPILE=${CROSS_COMPILE}

include $(SDK_BASE)/project.build

