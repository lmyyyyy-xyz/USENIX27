#include <octave/oct.h>
#include <octave/Cell.h>
#include <octave/quit.h>

/* Following define to solve a conflict between winnt.h (Windows) and the octave header files. */
#define Array Array_

#include "lp_lib.h"

#if defined driverVERSION

# define LPSOLVEAPIFROMLIB

# include "lp_explicit.h"

 static hlpsolve hlpsolve_ = NULL;
#endif

#define quotechar "'"
#define drivername      octlpsolve
#define strdrivername  "octlpsolve"
#define caller         "octave"

#define IsNumeric(pm) (pm.is_real_scalar() || pm.is_real_matrix())
#define IsComplex(pm) (pm.is_complex_matrix() || pm.is_complex_scalar())
#define GetM(lpsolvecaller, pm) pm.rows()
#define GetN(lpsolvecaller, pm) pm.cols()
#define GetpMatrix(lpsolvecaller, element) (((!IsNumeric((lpsolvecaller)->prhs(element)) || IsComplex((lpsolvecaller)->prhs(element))) ? ErrMsgTxt((lpsolvecaller), "invalid argument.") : 0), (lpsolvecaller)->prhs(element).matrix_value())
#define matCalloc calloc
#define matFree free
#define GetCellString(lpsolvecaller, pa, element, buf, bufsz) strncpy(buf, pa[element], bufsz)

#define pMatrix octave_value_list *
#define rMatrix Matrix
#define strArray char **

#define putlogfunc put_logfunc
#define putabortfunc put_abortfunc

#define init_lpsolve_lib() ((hlpsolve_ != NULL) || (((hlpsolve_ = open_lpsolve_lib(NULL)) != NULL) && init_lpsolve(hlpsolve_)))
#define exit_lpsolve_lib() { if (hlpsolve_ != NULL) close_lpsolve_lib(hlpsolve_); hlpsolve_ = NULL; }

#define callerPrototype(callername) DEFUN_DLD (callername, prhs, nlhs, "" strdrivername "  " caller " Interface version " driverVERSION "\n" \
"Usage: [ret1, ret2, ...] = " strdrivername "('functionname', arg1, arg2, ...)\n" \
"\n" \
"See Octave.htm for more information." \
)

#define publicargs(lpsolve) setargs(&((lpsolve)->lpsolvecaller), prhs, nlhs);
#define registerExitFcn(lpsolve)

#define ExitcallerPrototype(lpsolve) return((lpsolve)->lpsolvecaller.plhs)

typedef struct
{
        jmp_buf exit_mark;
        octave_value_list plhs;
        octave_value_list prhs;
        int nlhs;
        int nrhs;
} structlpsolvecaller;

#define Double double
#define Long Double

extern void setargs(structlpsolvecaller *lpsolvecaller, const octave_value_list &prhs, int nlhs);
extern void Printf(char *format, ...);

#define CreateLongMatrix CreateDoubleMatrix
#define SetLongMatrix SetDoubleMatrix
#define CreateDoubleSparseMatrix CreateDoubleMatrix
