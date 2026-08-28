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

if "%PLATFORM%" == "win32" goto ok1
echo.
echo This batch file is intended for 32 bit compilation with MS Visual C 6
echo For newer versions use cvc8*.bat
goto done
:ok1

if not exist bin\%PLATFORM%\*.* md bin\%PLATFORM%

set src=../../shared/commonlib.c \FML\src\FMLHandler.cpp FMLLPSOLVEParser.cpp FMLLPSOLVEToXML.cpp \fml\src\FMLLPToXML.cpp \fml\src\FMLParser.cpp lp_LPFML.c xli_LPFML.c

%c% -I\FML\xalan\include\src -I\FML\coin\include -I\FML\xerces\include -I\FML\include -I. -I.. -I..\.. -I..\..\shared /LD /MD /Zp8 /Gd /TP /GX -D_WINDLL -D_USRDLL -DWIN32 -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -DRoleIsExternalLanguageEngine -DLANGUAGE_ACTIVE=LANGUAGE_LPFML %src% -o bin\%PLATFORM%\xli_LPFML.dll /link /IGNORE:4089 /DEF:../lp_XLI.def \Fml\xerces\lib\xerces-c_2.lib \Fml\xalan\lib\Xalan-C_1.lib

if exist *.obj del *.obj
:done
set PLATFORM=
