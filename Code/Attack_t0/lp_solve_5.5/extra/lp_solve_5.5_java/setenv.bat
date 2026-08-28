@echo off

set JAVA_HOME=d:\j2sdk1.4.2_16
if exist "C:\Program Files\Java\jdk1.6.0_11\*.*" set JAVA_HOME=C:\Program Files\Java\jdk1.6.0_11
set LPSOLVE_DIR=d:\lp_solve\lp_solve_5.5
if exist "z:\lp_solve\lp_solve_5.5\*.*" set LPSOLVE_DIR=z:\lp_solve\lp_solve_5.5

set c=cl

REM determine platform (win32/win64)
echo main(){printf("SET PLATFORM=win%%d\n", (int) (sizeof(void *)*8));}>platform.c
%c% /nologo platform.c /Feplatform.exe
del platform.c
platform.exe >platform.bat
del platform.exe
call platform.bat
del platform.bat

call addpath %LPSOLVE_DIR%\extra\lp_solve_5.5_java\lib\%PLATFORM%
call addpath %LPSOLVE_DIR%\lpsolve55\bin\%PLATFORM%
call addpath %LPSOLVE_DIR%

call addpath %JAVA_HOME%\bin

