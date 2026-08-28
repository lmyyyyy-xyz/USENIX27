#include "LME_Ext.h"

#include "lp_lib.h"

#define quotechar "'"
#define ErrMsgTxt(lpsolvecaller, str) { lme_ref lme = (lpsolvecaller)->lme; /* LMECB_DbgWriteStr(str); */ LMECB_Write(1, str, -1, 1); LMECB_Write(1, "\n", 1, 1); exitnow(lpsolvecaller); }
#define drivername sqlpsolve
#define strdrivername "sqlpsolve"
#define caller "SysQuake"
#define GetM(lpsolvecaller, mat) mat->m
#define GetN(lpsolvecaller, mat) mat->n
#define matCalloc calloc
#define matFree free

#define maxnargout 10
#define maxnargin  10

#define MatrixEl struct structargout
#define pMatrix MatrixEl *
#define rMatrix pMatrix
#define strArray pMatrix

#define putlogfunc put_logfunc
#define putabortfunc put_abortfunc

#define init_lpsolve_lib() TRUE
#define exit_lpsolve_lib()

#define callerPrototype(callername) lme_err callername(lme_ref lme, lme_int32 nargin, lme_int32 nargout)

#define typevardouble  1
#define typevarstring  2
#define typevarunicode 3

struct structargout {
  int typevar;
  int m;
  int n;
  void *argout;
};

#define publicargs(lpsolve) \
        extern lme_ref global_lme; \
        \
        global_lme = lme; \
/* Printf("nargin = %d, nargout = %d\n", nargin, nargout); */ \
        (lpsolve)->lpsolvecaller.lme = lme; \
        (lpsolve)->lpsolvecaller.nlhs = nargout; \
        (lpsolve)->lpsolvecaller.nrhs = nargin; \
        (lpsolve)->lpsolvecaller.argout = (struct structargout *) calloc(1 + nargout, sizeof(struct structargout));

#define registerExitFcn(lpsolve)

#define ExitcallerPrototype(lpsolve) \
  if ((lpsolve)->lpsolvecaller.argout != NULL) { \
    int i; \
    struct structargout *argout = (lpsolve)->lpsolvecaller.argout; \
    nargout = (lpsolve)->lpsolvecaller.nlhs; \
    \
    setargout(&(lpsolve)->lpsolvecaller); \
    \
    for (i = 0; i < nargout; i++) \
      if (argout[i].argout != NULL) { \
        if (argout[i].typevar == typevarstring) { \
          int j; \
          char **str = (char **) argout[i].argout; \
          \
          for (j = argout[i].n - 1; j >= 0; j--) \
            matFree(str[j]); \
        } \
        matFree(argout[i].argout); \
      } \
    matFree(argout); \
  } \
  return(1);

#define BEGIN_INTERRUPT_IMMEDIATELY_IN_FOREIGN_CODE
#define END_INTERRUPT_IMMEDIATELY_IN_FOREIGN_CODE


typedef struct
{
        jmp_buf exit_mark;
        lme_ref lme;
        lme_int32 nlhs;
        lme_int32 nrhs;
        struct structargout *argout;
} structlpsolvecaller;

#define Double double
#define Long Double

#define CreateLongMatrix CreateDoubleMatrix
#define CreateDoubleSparseMatrix CreateDoubleMatrix
#define SetDoubleMatrix(lpsolvecaller, mat, m, n, element, freemat)
#define SetLongMatrix SetDoubleMatrix

extern void Printf(char *format, ...);
extern void setargout(structlpsolvecaller *lpsolvecaller);
extern struct structargout *GetpMatrix(structlpsolvecaller *lpsolvecaller, int element);

#undef CheckInterrupted
