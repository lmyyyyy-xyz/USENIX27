@echo off

set DFORTIFY=
if "%1" == "FORTIFY" set DFORTIFY=-DFORTIFY

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
set Eulerpath=C:\Program Files\Euler\dll

set a=lpsolve.cpp hash.cpp euler.cpp fortify.cpp "%Eulerpath%\dlldef.cpp"
cl /LD /MD /O2 /Zp8 /Gd -D_WINDLL -DWIN32 -D_WINDOWS -DEULER -DNODEBUG -DANSI_PROTOTYPES=1 %DFORTIFY% -I%lpsolvepath% -I"%Eulerpath%" -c %a%
if errorlevel 1 goto error
cl /LD /MD /O2 /Zp8 /Gd lpsolve.obj hash.obj euler.obj dlldef.obj fortify.obj user32.lib %lpsolvepath%\lpsolve55\bin\%PLATFORM%\lpsolve55.lib -o bin\%PLATFORM%\eulpsolve.dll
goto done
:error
echo COMPILE ERROR !!!!
:done
set a=
