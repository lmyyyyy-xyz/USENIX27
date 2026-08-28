@echo off
:: https://stackoverflow.com/a/39040033/197371
:: exit code 1 is success exit code 0 is failure
hhc.exe lp_solve.hhp
if not errorlevel 1 exit /B 1
