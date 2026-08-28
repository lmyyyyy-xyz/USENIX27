@echo off

set c=cl

REM determine platform (win32/win64)
echo #include "stdio.h">platform.c
echo void main(){printf("SET PLATFORM=win%%d\n", (int) (sizeof(void *)*8));}>>platform.c
%c% /nologo platform.c /Feplatform.exe
del platform.c
platform.exe >platform.bat
del platform.exe
call platform.bat
del platform.bat

if not exist bin\%PLATFORM%\*.* md bin\%PLATFORM%

set lpsolvepath=..\..
set Sysquakepath=C:\Program Files\SysquakePro\ExtCode

set a=lpsolve.c Sysquake.c hash.c
if "%1" == "" goto compile
set a=%1 %2 %3 %4 %5 %6 %7 %8 %9
:compile
cl /LD /MD /O2 /Zp8 /Gd -D_WINDLL -DWIN32 -DSYSQUAKE -DNODEBUG -I%lpsolvepath% -I"%Sysquakepath%" -c %a%
if errorlevel 1 goto error
cl /LD /MD /O2 /Zp8 /Gd lpsolve.obj Sysquake.obj hash.obj %lpsolvepath%\lpsolve55\bin\%PLATFORM%\lpsolve55.lib -o bin\%PLATFORM%\sqlpsolveext.dll
goto done
:error
echo COMPILE ERROR !!!!
:done
set a=
