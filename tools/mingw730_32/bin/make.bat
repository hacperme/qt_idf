@echo off

set cur_dir=%~dp0

set MAKE_EXC=%cur_dir%mingw32-make.exe

set parm_num=0
for %%a in (%*) do set /a parm_num+=1
if %parm_num% EQU 0 (
  call %MAKE_EXC%
) else (
   call %MAKE_EXC% %*
 )
