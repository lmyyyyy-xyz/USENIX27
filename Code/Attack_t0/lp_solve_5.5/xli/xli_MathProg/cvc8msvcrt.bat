@echo off

rem glpk is needed to compile this library. See at ftp://prep.ai.mit.edu/pub/gnu/glpk/

rem Tested with glpk 4.44

rem Location where glpk is located.
set glpkdir=\glpk\glpk-4.44

set glpk=%glpkdir%\src\glpavl.c %glpkdir%\src\glpdmp.c %glpkdir%\src\glpenv01.c %glpkdir%\src\glpenv02.c %glpkdir%\src\glpenv03.c %glpkdir%\src\glpenv04.c %glpkdir%\src\glpenv05.c %glpkdir%\src\glpenv07.c %glpkdir%\src\glpenv08.c %glpkdir%\src\glplib01.c %glpkdir%\src\glplib02.c %glpkdir%\src\glplib03.c %glpkdir%\src\glpmpl01.c %glpkdir%\src\glpmpl02.c %glpkdir%\src\glpmpl03.c %glpkdir%\src\glpmpl04.c %glpkdir%\src\glpmpl05.c %glpkdir%\src\glpmpl06.c %glpkdir%\src\glprng01.c %glpkdir%\src\glprng02.c xli_glpsql.c

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

set src=lp_MathProg.c xli_MathProg.c ..\..\shared\commonlib.c %glpk%

%c% -I. -I.. -I../.. -I../../shared -I../../colamd -I%glpkdir%\include -I%glpkdir%\src -I"C:\Program Files\MySQL\MySQL Connector C 6.0.2\include" /LD /MD /Zp8 /Gz -D_WINDLL -D_USRDLL -D_CRT_SECURE_NO_DEPRECATE -DWIN32 -D__WOE__ -D_WINSOCKAPI_ -DHAVE_CONFIG_H %src% ../lp_XLI.def /Febin\%PLATFORM%\xli_MathProg.dll
editbin /LARGEADDRESSAWARE bin\%PLATFORM%\xli_MathProg.dll

rem http://msdn2.microsoft.com/en-us/library/ms235229.aspx
rem for vs2005 need to embed manifest in dll with manifest tool -  #2 on the next line does this.
mt /outputresource:"bin\%PLATFORM%\xli_MathProg.dll;#2" /manifest "bin\%PLATFORM%\xli_MathProg.dll.manifest"

if exist *.obj del *.obj
set PLATFORM=
