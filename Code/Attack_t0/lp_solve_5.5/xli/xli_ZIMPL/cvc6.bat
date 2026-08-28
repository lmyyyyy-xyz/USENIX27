@echo off

rem zimpl is needed to compile this library. See at http://www.zib.de/koch/zimpl/

set ZIMPL_MAJORVERSION=2
set ZIMPL_MINORVERSION=06

rem Location where zimpl is located.
set zimpldir=.\zimpl.2.06
rem set zlib=\zlib-1.2.1
set zlib=\zlib-1.2.3
set gmp=\gmp-4.1.4

set zimpl=%zimpldir%\src\bound.c %zimpldir%\src\code.c %zimpldir%\src\conname.c %zimpldir%\src\define.c %zimpldir%\src\elem.c %zimpldir%\src\entry.c %zimpldir%\src\gmpmisc.c %zimpldir%\src\hash.c %zimpldir%\src\heap.c %zimpldir%\src\metaio.c %zimpldir%\src\idxset.c %zimpldir%\src\inst.c %zimpldir%\src\iread.c %zimpldir%\src\list.c %zimpldir%\src\load.c %zimpldir%\src\local.c %zimpldir%\src\mmlparse.c %zimpldir%\src\mmlscan.c %zimpldir%\src\mshell.c %zimpldir%\src\numbgmp.c %zimpldir%\src\prog.c %zimpldir%\src\rathumwrite.c %zimpldir%\src\ratlpfwrite.c %zimpldir%\src\ratlpstore.c %zimpldir%\src\ratmpswrite.c %zimpldir%\src\ratmstwrite.c %zimpldir%\src\ratordwrite.c %zimpldir%\src\ratpresolve.c %zimpldir%\src\ratsoswrite.c %zimpldir%\src\rdefpar.c %zimpldir%\src\set4.c %zimpldir%\src\setempty.c %zimpldir%\src\setlist.c %zimpldir%\src\setmulti.c %zimpldir%\src\setprod.c %zimpldir%\src\setpseudo.c %zimpldir%\src\setrange.c %zimpldir%\src\source.c %zimpldir%\src\stmt.c %zimpldir%\src\symbol.c %zimpldir%\src\term.c %zimpldir%\src\tuple.c %zimpldir%\src\vinst.c %zimpldir%\src\xlpglue.c %zimpldir%\src\zimpllib.c
if exist %zimpldir%\src\strstore.c set zimpl=%zimpl% %zimpldir%\src\strstore.c
if exist %zimpldir%\src\strstore2.c set zimpl=%zimpl% %zimpldir%\src\strstore2.c
if exist %zimpldir%\src\ratrlpwrite.c set zimpl=%zimpl% %zimpldir%\src\ratrlpwrite.c
if exist %zimpldir%\src\random.c set zimpl=%zimpl% %zimpldir%\src\random.c
if exist %zimpldir%\src\blkmem.c set zimpl=%zimpl% %zimpldir%\src\blkmem.c

set zimpl=%zimpl% -Iextra extra/extra.c extra/regerror.c extra/finite.c
set zimpl=%zimpl% -I\C\REGEXP2\lib \C\REGEXP2\lib\regex.c \C\REGEXP2\lib\regexp.c

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

set src=..\..\shared\commonlib.c lp_ZIMPL.c xli_ZIMPL.c %zimpl%

rem %c% -I.. -I../.. -I../../shared -I%zlib% -I%gmp% -I%zimpldir%\src /LD /MT /Zp8 /Gz -DNDEBUG -D_WINDLL -D_USRDLL -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -DWIN32 -DRoleIsExternalLanguageEngine -D"LANGUAGE_ACTIVE=LANGUAGE_ZIMPL" -DZLIB_DLL -D"ZEXPORT=__cdecl" "-Dinline=_inline" %src% ../lp_XLI.def %gmp%\release\gmp.lib %zlib%\zlib.lib -o bin\%PLATFORM%\xli_ZIMPL.dll

%c% -DVERSION="""%ZIMPL_MAJORVERSION%.%ZIMPL_MINORVERSION%""" -DZIMPL_MAJORVERSION=%ZIMPL_MAJORVERSION% -DZIMPL_MINORVERSION=%ZIMPL_MINORVERSION% -I.. -I../.. -I../../shared -I%zlib% -I%gmp% -I%zimpldir%\src /LD /MT /Zp8 /Gz -DNDEBUG -D_WINDLL -D_USRDLL -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -DWIN32 -DRoleIsExternalLanguageEngine -D"LANGUAGE_ACTIVE=LANGUAGE_ZIMPL" -DZLIB_DLL -D"ZEXPORT=__cdecl" "-Dinline=_inline" "-DSTDC_HEADERS=1" "-DHAVE_STRING_H=1" -DREGEX_MALLOC "-DANSI_PROTOTYPES=1" %src% ../lp_XLI.def %gmp%\release\gmp.lib %zlib%\zdll.lib -o bin\%PLATFORM%\xli_ZIMPL.dll

if exist *.obj del *.obj
:done
set PLATFORM=
