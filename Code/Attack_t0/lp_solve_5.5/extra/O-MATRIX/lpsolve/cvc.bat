@echo off

set lpsolvepath=..\..\..
rem set dllsrcpath=f:\omwin58\dll\SRC
set dllsrcpath=e:\omwin57\dll\SRC
set dllsrcpath=e:\omwin58\dll\SRC

set a=lpsolve.c omatrix.c hash.c
if "%1" == "" goto compile
set a=%1 %2 %3 %4 %5 %6 %7 %8 %9
:compile
cl /LD /MD /O2 /Zp8 /Gz /TP -D_WINDLL -DWIN32 -DOMATRIX -DNODEBUG -I%dllsrcpath% -I%lpsolvepath% -c %a%
if errorlevel 1 goto error
cl /LD /MD /O2 /Zp8 /Gz lpsolve.obj omatrix.obj hash.obj %lpsolvepath%\lpsolve55\bin\win32\lpsolve55.lib -o omlpsolve.dll
goto done
:error
echo COMPILE ERROR !!!!
:done
set a=
