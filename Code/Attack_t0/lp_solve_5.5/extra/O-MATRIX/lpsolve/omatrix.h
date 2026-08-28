#include "dll.h"

#include "lp_lib.h"

#define quotechar "\""
#define ErrMsgTxt(lpsolvecaller, str) (lpsolvecaller)->error("omlpsolve", str)
#define drivername omlpsolve
#define strdrivername "omlpsolve"
#define caller "O-Matrix"
#define IsNumeric(pm) (((pm)->type == INT_mat) || ((pm)->type == REAL_mat) || ((pm)->type == DOUBLE_mat))
#define IsComplex(pm) ((pm)->type == COMPLEX_mat)
#define IsSparse(pm) FALSE
#define GetM(lpsolvecaller, pm) (pm)->nr
#define GetN(lpsolvecaller, pm) (pm)->nc
#define GetpMatrix(lpsolvecaller, element) (lpsolvecaller)->direct(((lpsolvecaller)->prhs + element))
#define GetPr(pm) (pm)->adr
#define adrElement address
/* #define GetPr(pm) ((pm)->type == INT_mat ? (pm)->adr.i : (pm)->type == REAL_mat ? (pm)->adr.r : (pm)->type == DOUBLE_mat ? (pm)->adr.d) */
#define matCalloc calloc
#define matFree free

#define MatrixEl matrix
#define pMatrix MatrixEl *
#define rMatrix pMatrix
#define strArray char **

#define putlogfunc put_logfunc
#define putabortfunc put_abortfunc

#define init_lpsolve_lib() TRUE
#define exit_lpsolve_lib()

#define callerPrototype(callername) DLLPrototype(callername)

#define publicargs(lpsolve) setargs(&((lpsolve)->lpsolvecaller), narg, nret, ret, arg, direct, allocate, free_mat, error, prText)

#define registerExitFcn(lpsolve)

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
        pMatrix (__cdecl *direct)     (pMatrix);
        void    (__cdecl *allocate)   (pMatrix);
        void    (__cdecl *free_mat)   (pMatrix);
        void    (__cdecl *error)      (char *, char *);
} structlpsolvecaller;

extern void    (__cdecl *prText)     (char *, char *);

#define Double double
#define Long   int

extern void setargs(structlpsolvecaller *lpsolvecaller, int narg, int nret, pMatrix ret, pMatrix arg, pMatrix (__cdecl *direct) (pMatrix ), void (__cdecl *allocate) (pMatrix ), void (__cdecl *free_mat) (pMatrix ), void (__cdecl *error) (char *, char *), void (__cdecl *prText0) (char *, char *));
extern void Printf(char *format, ...);
#define CreateDoubleSparseMatrix CreateDoubleMatrix
#define SetDoubleMatrix(mat, m, n, plhs, element, freemat)
#define SetLongMatrix(mat, m, n, plhs, element, freemat)
