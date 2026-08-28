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

set src=xli_Dimacs.c lp_Dimacs.c lp_network.c

if not exist bin\%PLATFORM%\*.* md bin\%PLATFORM%

%c% -I.. -I../.. -I../../shared /LD /MD /Zp8 /Gz -D_WINDLL -D_USRDLL -DWIN32 -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE %src% ../lp_XLI.def /Febin\%PLATFORM%\xli_DIMACS.dll
editbin /LARGEADDRESSAWARE bin\%PLATFORM%\xli_DIMACS.dll

rem http://msdn2.microsoft.com/en-us/library/ms235229.aspx
rem for vs2005 need to embed manifest in dll with manifest tool -  #2 on the next line does this.
mt /outputresource:"bin\%PLATFORM%\xli_DIMACS.dll;#2" /manifest "bin\%PLATFORM%\xli_DIMACS.dll.manifest"

if exist *.obj del *.obj
set PLATFORM=
