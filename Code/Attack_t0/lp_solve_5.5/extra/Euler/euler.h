#include <stdlib.h>
#include <stdarg.h>

#if defined WIN32
#include <windows.h>
#endif

#include "lp_lib.h"

#include "dlldef.h"

#define quotechar "\""
#if defined WIN32
# define showmsg(str, icon) MessageBox((HWND) NULL, (LPCSTR) str, (LPCSTR) strdrivername, (UINT) icon)
#else
# define showmsg(msg, icon) { int ret; char buffer[4096], *ptr; sprintf(buffer, "xmessage -button ok -default ok -center '%s'", msg); /* for (ptr = buffer; *ptr; ptr++) if (*ptr == '\n') *ptr = ' '; */ { FILE *fp = fopen("msg.txt","a+"); fprintf(fp, "%s", buffer); fclose(fp); } ret = system(buffer); }
#endif
#define ErrMsgTxt(lpsolvecaller, str) { int i; /* Printf("%s\n", str); */ strcpy((lpsolvecaller)->ram, str); (lpsolvecaller)->newram = (lpsolvecaller)->ram; for (i = ((lpsolvecaller)->nargout ? (lpsolvecaller)->nargout - 1 : 0); i >= 0; i--) { if ((lpsolvecaller)->argout[i].argout == NULL) (lpsolvecaller)->argout[i].argout = (void *) calloc(1, 1); (lpsolvecaller)->argout[i].typevar = typevarundef; } exitnow(lpsolvecaller); }
#define drivername eulpsolve
#define strdrivername "eulpsolve"
#define caller "Euler"
#define GetM(lpsolvecaller, pm) dimsof(pm)->r
#define GetN(lpsolvecaller, pm) dimsof(pm)->c
#define GetpMatrix(lpsolvecaller, element) (lpsolvecaller)->p[element]
#define IsComplex(pm) FALSE
#define IsNumeric(pm) (((pm)->argtype == arguint8) || ((pm)->argtype == argint8) || ((pm)->argtype == arguint16) || ((pm)->argtype == argint16) || ((pm)->argtype == arguint32) || ((pm)->argtype == argint32) || ((pm)->argtype == argfloat) || ((pm)->argtype == argdouble))
#define GetPr(pm) (pm)->ptr
#define adrElement address
#define matCalloc calloc
#define matFree free

#define MatrixEl header
#define pMatrix MatrixEl *
#define rMatrix pMatrix
#define strArray char **

#define putlogfunc put_logfunc
#define putabortfunc put_abortfunc

#define init_lpsolve_lib() TRUE
#define exit_lpsolve_lib()

#if !defined WIN32
#define __declspec(dllexport)
#endif

#define callerPrototype(callername) extern "C" __declspec(dllexport) char *callername(header *p[], int np, char *newram, char *ramend)

#define typevarundef   0
#define typevardouble  1
#define typevarstring  2

struct structargout {
  int typevar;
  int m;
  int n;
  void *argout;
};

#if !defined FORTIFY
#  define Fortify_EnterScope()
#  define Fortify_LeaveScope()
#endif

#define publicargs(lpsolve) \
  Fortify_EnterScope(); \
  (lpsolve)->lpsolvecaller.nlhs = 10; \
  (lpsolve)->lpsolvecaller.nrhs = np; \
  (lpsolve)->lpsolvecaller.p = p; \
  (lpsolve)->lpsolvecaller.ram = newram; \
  (lpsolve)->lpsolvecaller.newram = newram; \
  (lpsolve)->lpsolvecaller.ramend = ramend; \
  (lpsolve)->lpsolvecaller.nargout = 0; \
  (lpsolve)->lpsolvecaller.argout = (struct structargout *) calloc(1 + (lpsolve)->lpsolvecaller.nlhs, sizeof(struct structargout));

#define registerExitFcn(lpsolve)

#define ExitcallerPrototype(lpsolve) \
  setargout(&(lpsolve)->lpsolvecaller); \
  Fortify_LeaveScope(); \
  return((lpsolve)->lpsolvecaller.newram);

#define BEGIN_INTERRUPT_IMMEDIATELY_IN_FOREIGN_CODE
#define END_INTERRUPT_IMMEDIATELY_IN_FOREIGN_CODE

typedef struct
{
        jmp_buf exit_mark;
        int nlhs;
        int nrhs;
        header **p;
        char *ram;
	char *newram;
        char *ramend;
        int nargout;
        struct structargout *argout;
} structlpsolvecaller;

#define Double double
#define Long   Double

#define CreateLongMatrix CreateDoubleMatrix
#define CreateDoubleSparseMatrix CreateDoubleMatrix
#define SetDoubleMatrix(lpsolvecaller, mat, m, n, element, freemat)
#define SetLongMatrix SetDoubleMatrix

extern void Printf(char *format, ...);
extern void setargout(structlpsolvecaller *lpsolvecaller);

#undef CheckInterrupted
