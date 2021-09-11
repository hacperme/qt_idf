@echo off

set cur_dir=%~dp0

set CMAKE_PATH=%cur_dir%tools\cmake\cmake-3.21.2-windows-i386\bin
set MINGW_PATH=%cur_dir%tools\mingw730_32
set TOOLCHAIN_PATH=%cur_dir%tools\mingw730_32\bin
set PATH=%CMAKE_PATH%;%MINGW_PATH%;%TOOLCHAIN_PATH%
echo %PATH%

