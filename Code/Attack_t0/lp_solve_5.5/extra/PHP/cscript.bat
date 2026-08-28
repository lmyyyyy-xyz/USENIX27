rem this batch file is only needed if build according to book 'Extending and Embedding PHP' By Sara Golemon
rem first run buildconf.bat which creates configure.js
cscript /nologo configure.js --without-xml --without-wddx --without-simplexml --without-dom --without-libxml --disable-zlib --without-sqlite --disable-odbc --disable-cgi --enable-cli --without-iconv --enable-phplpsolve55=shared --with-phplpsolve55path="z:\lp_solve_5.5"
