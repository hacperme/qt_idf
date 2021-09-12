@echo off

set cur_dir=%~dp0

set "build_dir=build\"

set parm_num=0
for %%a in (%*) do set /a parm_num+=1
if %parm_num% EQU 0 (
  set CONFIG_FILE=%cur_dir%scripts\cmake\toolchain_windows_x86_mingw_gcc.cmake
) else (
  set CONFIG_FILENAME=%1
  set CONFIG_FILE=%cur_dir%scripts\cmake\%1
 )

echo %CONFIG_FILE%

if not exist %CONFIG_FILE% (
	echo "config file is not exist"
	goto BYEBYE
)

if not exist %cur_dir%%build_dir% (md %cur_dir%%build_dir%)


cd %cur_dir%%build_dir%

if exist %cur_dir%%build_dir%CMakeCache.txt (del CMakeCache.txt)


cmake -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=%CONFIG_FILE% .. -Wdev

if %errorlevel% neq 0 (
  echo "errors occurred....."
  cd ../
	goto BYEBYE
)

:BYEBYE