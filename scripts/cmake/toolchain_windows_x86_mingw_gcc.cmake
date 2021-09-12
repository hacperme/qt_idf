cmake_minimum_required(VERSION 3.10)

set(CMAKE_SYSTEM_NAME Windows)

if(DEFINED ENV{TOOLCHAIN_PATH})
  set(TOOLCHAIN_PATH $ENV{TOOLCHAIN_PATH})
else()
  message(FATAL_ERROR "Please set environment variable \"TOOLCHAIN_PATH\" first.")
endif()

find_program(CMAKE_C_COMPILER NAMES gcc)

find_program(CMAKE_CXX_COMPILER NAMES g++)
