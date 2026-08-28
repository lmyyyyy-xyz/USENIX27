@echo off

REM This batch file compiles the lpsolve libraries with the GNU gcc compiler under Windows

set c=gcc

set src=../bfp/lp_MDO.c ../commonlib.c ../myblas.c ../colamd/colamd.c ../lp_rlp.c ../lp_crash.c ../bfp/bfp_etaPFI/lp_etaPFI.c ../lp_Hash.c ../lp_lib.c ../lp_wlp.c ../lp_matrix.c ../lp_mipbb.c ../lp_MPS.c ../lp_presolve.c ../lp_price.c ../lp_pricePSE.c ../lp_report.c ../lp_scale.c ../lp_simplex.c ../lp_SOS.c ../lp_utils.c ../yacc_read.c

rem rc lpsolve.rc
%c% -I.. -I../bfp -I../bfp/bfp_etaPFI -I../colamd -s -O3 -shared -mno-cygwin -enable-stdcall-fixup -D_USRDLL -DWIN32 -DYY_NEVER_INTERACTIVE -DPARSER_LP %src% ..\lp_solve.def -o lpsolve55.dll

if exist *.o del *.o
%c% -I.. -I../bfp -I../bfp/bfp_etaPFI -I../colamd -s -O3 -c -DYY_NEVER_INTERACTIVE -DPARSER_LP %src%
ar rv liblpsolve51.a *.o

if exist *.o del *.o
