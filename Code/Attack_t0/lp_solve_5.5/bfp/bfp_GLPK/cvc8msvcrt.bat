@echo off

rem glpk is needed to compile this library. See at ftp://prep.ai.mit.edu/pub/gnu/glpk/

rem Tested with glpk 4.2, 4.7, 4.8, 4.11, 4.13

rem Location where glpk is located.
set glpkdir=\glpk\glpk-4.13

set glpk1=%glpkdir%\src\glplib1a.c
set glpk2=%glpkdir%\src\glplib2.c
set glpk4=%glpkdir%\src\glplib4.c
if exist %glpkdir%\src\glprng.c set glpk4=%glpkdir%\src\glprng.c

set glpk=%glpkdir%\src\glpinv.c %glpk1% %glpk2% %glpk4% %glpkdir%\src\glpluf.c

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

set src=../../colamd/colamd.c ../../shared/commonlib.c bfp_GLPK.c lp_glpkLU.c ../../lp_utils.c %glpk%

if not exist bin\%PLATFORM%\*.* md bin\%PLATFORM%

%c% -I.. -I../.. -I../../colamd -I../../shared -I%glpkdir%\include /LD /MD /O2 /Zp8 /Gz -D_WINDLL -D_USRDLL -DWIN32 -DRoleIsExternalInvEngine -DINVERSE_ACTIVE=INVERSE_GLPKLU -D_CRT_SECURE_NO_DEPRECATE %src% /Febin\%PLATFORM%\bfp_GLPK.dll
editbin /LARGEADDRESSAWARE bin\%PLATFORM%\bfp_GLPK.dll

rem http://msdn2.microsoft.com/en-us/library/ms235229.aspx
rem for vs2005 need to embed manifest in dll with manifest tool -  #2 on the next line does this.
mt /outputresource:"bin\%PLATFORM%\bfp_GLPK.dll;#2" /manifest "bin\%PLATFORM%\bfp_GLPK.dll.manifest"

if exist *.obj del *.obj
set PLATFORM=
