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

set a=lpsolve.c freemat.c hash.c
if "%1" == "" goto compile
set a=%1 %2 %3 %4 %5 %6 %7 %8 %9
:compile
cl /LD /MD /O2 /Zp8 /Gz -D_WINDLL -DWIN32 -DFREEMAT -DNODEBUG -I%lpsolvepath% -c %a%
if errorlevel 1 goto error
cl /LD /MD /O2 /Zp8 /Gz lpsolve.obj freemat.obj hash.obj user32.lib %lpsolvepath%\lpsolve55\bin\%PLATFORM%\lpsolve55.lib -o bin\%PLATFORM%\fmlpsolve.dll
goto done
:error
echo COMPILE ERROR !!!!
:done
set a=
