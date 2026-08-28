@echo off
SET THEFILE=demo.exe
echo Linking %THEFILE%
c:\pp\bin\win32\ld.exe  -s   --base-file base.$$$ -o demo.exe link.res
if errorlevel 1 goto linkend
goto end
:asmend
echo An error occured while assembling %THEFILE%
goto end
:linkend
echo An error occured while linking %THEFILE%
:end
