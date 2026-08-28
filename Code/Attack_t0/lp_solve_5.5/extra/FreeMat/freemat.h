#include <stdlib.h>
#include <stdarg.h>

#if defined WIN32
#include <windows.h>
#endif

#include "lp_lib.h"

#define quotechar "'"
#if defined WIN32
# define showmsg(str, icon) MessageBox((HWND) NULL, (LPCSTR) str, (LPCSTR) strdrivername, (UINT) icon)
#else
# define showmsg(msg, icon) { int ret; char buffer[4096]; sprintf(buffer, "xmessage -button ok -default ok -center '%s'", msg); ret = system(buffer); }
#endif
#define ErrMsgTxt(lpsolvecaller, str) { showmsg(str, MB_ICONSTOP); exitnow(lpsolvecaller); }
#define drivername fmlpsolve
#define strdrivername "fmlpsolve"
#define caller "FreeMat"
#define GetM(lpsolvecaller, pm) (pm)->m
#define GetN(lpsolvecaller, pm) (pm)->n
#define GetpMatrix(lpsolvecaller, element) (element < (lpsolvecaller)->nrhs ? (((lpsolvecaller)->args) + element + (lpsolvecaller)->nlhs) : element < (lpsolvecaller)->nlhs + (lpsolvecaller)->nrhs ? (((lpsolvecaller)->args) + element - (lpsolvecaller)->nrhs) : NULL)
#define IsComplex(pm) FALSE
#define IsNumeric(pm) (((pm)->argtype == arguint8) || ((pm)->argtype == argint8) || ((pm)->argtype == arguint16) || ((pm)->argtype == argint16) || ((pm)->argtype == arguint32) || ((pm)->argtype == argint32) || ((pm)->argtype == argfloat) || ((pm)->argtype == argdouble))
#define GetPr(pm) (pm)->ptr
#define adrElement address
#define matCalloc calloc
#define matFree free

#define MatrixEl struct argsstruct
#define pMatrix MatrixEl *
#define rMatrix pMatrix
#define strArray char **

#define putlogfunc put_logfunc
#define putabortfunc put_abortfunc

#define init_lpsolve_lib() TRUE
#define exit_lpsolve_lib()

#if !defined WIN32
#define __declspec(dllexport)
#define _cdecl
#endif

#define callerPrototype(callername) void __declspec(dllexport) _cdecl callername(int nargin, int nargout, char *function, ...)

#define argstring 1
#define arguint8  2
#define argint8   3
#define arguint16 4
#define argint16  5
#define arguint32 6
#define argint32  7
#define argfloat  8
#define argdouble 9

struct argsstruct {
 int argtype;
 int m;
 int n;
 union {
   unsigned char uint8;
   signed char int8;
   unsigned short uint16;
   signed short int16;
   unsigned int uint32;
   signed int int32;
   float f;
   double d;
   char *string;
 } arg;
 void *ptr;
};

#define vararray(format, Argtype, fmtype, value, ctype, ctype2) \
  if (strncmp(format, fmtype, sizeof(fmtype) - 1) == 0) { \
    int n, m; \
    \
    if (((format[sizeof(fmtype) - 1] == '[') || (format[sizeof(fmtype)] == '&')) && (strcmp(fmtype, "string"))) { \
      int i; \
      char *ptr; \
      ctype *pctype; \
      \
      if (format[sizeof(fmtype) - 1] == '[') { \
        n = strtol(format + sizeof(fmtype), &ptr, 10); \
      } \
      else { \
        n = 1; \
        ptr = format + sizeof(fmtype); \
      } \
      pctype = (ctype *) va_arg(argptr, ctype *); \
      if (*ptr == '*') { \
        m = n; \
        n = strtol(ptr + 1, &ptr, 10); \
      } \
      else { \
        m = 1; \
      } \
      \
      args[nargs].ptr = (void *) pctype; \
    } \
    else { \
      n = 1; \
      m = 1; \
      args[nargs].arg.value = (ctype) va_arg(argptr, ctype2); \
      args[nargs].ptr = &args[nargs].arg.value; \
    } \
    args[nargs].argtype = Argtype; \
    args[nargs].n = n; \
    args[nargs].m = m; \
    nargs++; \
  } \
  else

#if defined WIN32
# define va_arg_uchar  unsigned char
# define va_arg_schar  signed char
# define va_arg_ushort unsigned short
# define va_arg_sshort signed short
# define va_arg_float  float
#else
# define va_arg_uchar  unsigned int
# define va_arg_schar  signed int
# define va_arg_ushort unsigned int
# define va_arg_sshort signed int
# define va_arg_float  double
#endif

#define publicargs(lpsolve) \
{ \
  va_list argptr; \
  char *function1; \
  struct argsstruct *args; \
  int nargs; \
 \
  va_start( argptr, function ); \
 \
  nargs = 0; \
  function1 = function; \
  while( *function1 != '\0' ) { \
    nargs++; \
    while ((*function1) && (*function1 != ',')) \
      function1++; \
    if (*function1) \
      function1++; \
    while ((*function1) && (isspace(*function1))) \
      function1++; \
  } \
 \
  va_end( argptr ); \
 \
  args = calloc(nargs, sizeof(*args)); \
 \
  va_start( argptr, function ); \
 \
  nargs = 0; \
  function1 = function; \
  while( *function1 != '\0' ) { \
    vararray(function1, argstring, "string", string, char *, char *) \
    vararray(function1, arguint8, "uint8", uint8, unsigned char, va_arg_uchar) \
    vararray(function1, argint8, "int8", int8, signed char, va_arg_schar) \
    vararray(function1, arguint16, "uint16", uint16, unsigned short, va_arg_ushort) \
    vararray(function1, argint16, "int16", int16, signed short, va_arg_ushort) \
    vararray(function1, arguint32, "uint32", uint32, unsigned int, unsigned int) \
    vararray(function1, argint32, "int32", int32, signed int, signed int) \
    vararray(function1, argfloat, "float", f, float, va_arg_float) \
    vararray(function1, argdouble, "double", d, double, double) \
    ; \
    while ((*function1) && (*function1 != ',')) \
      function1++; \
    if (*function1) \
      function1++; \
    while ((*function1) && (isspace(*function1))) \
      function1++; \
  } \
 \
  va_end( argptr ); \
/* Printf("nargs = %d, nargin = %d, nargout = %d\n", nargs, nargin, nargout); */ \
  (lpsolve)->lpsolvecaller.nlhs = nargout; \
  (lpsolve)->lpsolvecaller.nrhs = nargin; \
  (lpsolve)->lpsolvecaller.args = args; \
}


#define registerExitFcn(lpsolve)

#define ExitcallerPrototype(lpsolve) \
  if ((lpsolve)->lpsolvecaller.args != NULL) { \
    free((lpsolve)->lpsolvecaller.args); \
    (lpsolve)->lpsolvecaller.args = NULL; \
  } \
  return

#define BEGIN_INTERRUPT_IMMEDIATELY_IN_FOREIGN_CODE
#define END_INTERRUPT_IMMEDIATELY_IN_FOREIGN_CODE

typedef struct
{
        jmp_buf exit_mark;
        int nlhs;
        int nrhs;
        struct argsstruct *args;
} structlpsolvecaller;

#define Double double
#define Long   long

extern void Printf(char *format, ...);
