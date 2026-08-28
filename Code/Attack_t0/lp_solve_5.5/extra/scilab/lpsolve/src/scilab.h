#include "mex.h"

#undef Top
#undef REAL

#include "lp_lib.h"

#define quotechar "'"
#define ErrMsgTxt(lpsolvecaller, str) mexErrMsgTxt(str)
#define drivername sclpsolve
#define strdrivername "sclpsolve"
#define caller "scilab"
#define IsNumeric mxIsNumeric
#define IsComplex mxIsComplex
#define IsSparse mxIsSparse
#define GetM(lpsolvecaller, mat) mxGetM(mat)
#define GetN(lpsolvecaller, mat) mxGetN(mat)
#define GetpMatrix(lpsolvecaller, element) (lpsolvecaller)->prhs[element]
#define GetPr mxGetPr
#define matCalloc calloc /* mxCalloc */
#define matRealloc realloc  /* mxRealloc */
#define matFree free /* mxFree */
#define GetCellString(lpsolvecaller, ppm, element, buf, size) GetString(lpsolvecaller, ppm, element, buf, size, TRUE)

#define MatrixEl mxArray *
#define pMatrix MatrixEl *
#define rMatrix MatrixEl
#define strArray pMatrix

#define putlogfunc put_logfunc
#define putabortfunc put_abortfunc

#define init_lpsolve_lib() TRUE
#define exit_lpsolve_lib()

#define callerPrototype(callername) void callername(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])

#define publicargs(lpsolve) \
        (lpsolve)->lpsolvecaller.plhs = (pMatrix) plhs; \
        (lpsolve)->lpsolvecaller.prhs = (pMatrix) prhs; \
        (lpsolve)->lpsolvecaller.nlhs = nlhs; \
        (lpsolve)->lpsolvecaller.nrhs = nrhs;

#define registerExitFcn(lpsolve) if (mexAtExit(ExitFcn)) ErrMsgTxt(&lpsolve->lpsolvecaller, "Failed to register exit function.\n")

#define ExitcallerPrototype(lpsolve) return

#define BEGIN_INTERRUPT_IMMEDIATELY_IN_FOREIGN_CODE
#define END_INTERRUPT_IMMEDIATELY_IN_FOREIGN_CODE


typedef struct
{
        jmp_buf exit_mark;
        int nlhs;
        int nrhs;
        pMatrix plhs;
        pMatrix prhs;
} structlpsolvecaller;

#define Double double
#define Long Double

extern void Printf(char *format, ...);
#define CreateLongMatrix CreateDoubleMatrix
#define SetDoubleMatrix(lpsolvecaller, mat, m, n, element, freemat)
#define SetLongMatrix SetDoubleMatrix
