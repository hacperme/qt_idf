@echo off

set cur_dir=%~dp0

set CMAKE_PATH=%cur_dir%tools\cmake\cmake-3.21.2-windows-i386\bin
set MINGW_PATH=%cur_dir%tools\mingw32
set TOOLCHAIN_PATH=%cur_dir%tools\mingw32\bin
set PYTHON_PATH=%cur_dir%tools\python-3.7.6rc1-embed-amd64
set PYTHON_SCRIPTS_PATH=%PYTHON_PATH%\Scripts
set PYTHON_LIB_PATH=%PYTHON_PATH%\Lib\site-packages
set PATH=%CMAKE_PATH%;%MINGW_PATH%;%TOOLCHAIN_PATH%;%PYTHON_PATH%;%PYTHON_SCRIPTS_PATH%;%PYTHON_LIB_PATH%
echo %PATH%

