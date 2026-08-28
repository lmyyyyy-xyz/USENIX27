@echo off

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

set src=xli_LINDO.c lp_LINDO.c lp_rlnd1.c lp_wlnd1.c yacc_read1.c lp_Hash1.c ../../lp_utils.c

%c% -DINLINE=static -I.. -I../.. -I../../shared -s -O3 -shared -mno-cygwin -enable-stdcall-fixup -D_WINDLL -D_USRDLL -DWIN32 -DYY_NEVER_INTERACTIVE %src% ../lp_XLI.def -o bin\%PLATFORM%\xli_LINDO.dll

%c% -DINLINE=static -I.. -I../.. -I../../shared -s -O3 -shared -D_WINDLL -D_USRDLL -DWIN32 -DYY_NEVER_INTERACTIVE %src% ../lp_XLI.def -o bin\%PLATFORM%\libxli_LINDO.so

%c% -DINLINE=static -I.. -I../.. -I../../shared -s -O3 -c -DYY_NEVER_INTERACTIVE %src%
ar rv bin\%PLATFORM%\libxli_LINDO.a *.o

if exist *.o del *.o

set PLATFORM=
