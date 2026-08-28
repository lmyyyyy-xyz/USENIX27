@echo off

REM ---------------------------------------------------------------------------------------------------------------------
REM batch file to compile this demo with FreePascal

REM The FreePascal environment can be found at:
REM http://sourceforge.net/projects/freepascal/

REM For DOS/Windows, run install.exe to install the FreePascal environment

REM Note that the lpsolve55 dll or lpsolve55.so library must be in the path for this demo to work.
REM ---------------------------------------------------------------------------------------------------------------------

set IDE=

REM alternatively, you can also also use the IDE:
rem set IDE=y


if "%IDE%" == "" ppc386 demo.dpr
if not "%IDE%" == "" fp demo.dpr

REM the result is demo.exe
