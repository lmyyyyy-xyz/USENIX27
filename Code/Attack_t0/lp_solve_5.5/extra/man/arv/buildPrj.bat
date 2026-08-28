echo.>Project1.arv
dir ..\*.htm /b /on | replreg ".*" "..\\\0" >>Project1.arv
