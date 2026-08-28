@echo off

rem glpk is needed to compile this library. See at ftp://prep.ai.mit.edu/pub/gnu/glpk/

rem Tested with glpk 4.2 and 4.7

rem Location where glpk is located.
set glpkdir=\glpk

set glpk1=%glpkdir%\src\glplib4.c
if exist %glpkdir%\src\glprng.c set glpk1=%glpkdir%\src\glprng.c
set glpk=%glpkdir%\src\glpavl.c %glpkdir%\src\glpdmp.c %glpkdir%\src\glplib1a.c %glpkdir%\src\glplib2.c %glpkdir%\src\glplib3.c %glpk1% %glpkdir%\src\glpmpl1.c %glpkdir%\src\glpmpl2.c %glpkdir%\src\glpmpl3.c %glpkdir%\src\glpmpl4.c

set c=gcc

REM determine platform (win32/win64)
echo main(){printf("SET PLATFORM=win%%d\n", (int) (sizeof(void *)*8));}>platform.c
%c% platform.c -o platform.exe
del platform.c
platform.exe >platform.bat
del platform.exe
call platform.bat
del platform.bat

if not exist bin\%PLATFORM%\*.* md bin\%PLATFORM%

set src=lp_MathProg.c xli_MathProg.c %glpk%

%c% -DINLINE=static -I.. -I../.. -I../../colamd -I%glpkdir%\include -s -O3 -shared -mno-cygwin -enable-stdcall-fixup -D_WINDLL -D_USRDLL -DWIN32 %src% ../lp_XLI.def -o bin\%PLATFORM%\xli_MathProg.dll

%c% -DINLINE=static -I.. -I../.. -I../../colamd -I%glpkdir%\include -s -O3 -shared -D_WINDLL -D_USRDLL -DWIN32 %src% ../lp_XLI.def -o bin\%PLATFORM%\libxli_MathProg.so

%c% -DINLINE=static -I.. -I../.. -I../../colamd -I%glpkdir%\include -s -O3 -c %src%
ar rv bin\%PLATFORM%\libxli_MathProg.a *.o

if exist *.o del *.o

set PLATFORM=
