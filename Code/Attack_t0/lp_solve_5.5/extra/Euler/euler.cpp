#include <stdarg.h>

#include "lpsolvecaller.h"

#if defined _MSC_VER
# define vsnprintf _vsnprintf
#endif

static void (*output) (char *s) = NULL;
static void (*output1) (char *s,...) = NULL;
static int (*wait_key) (int *scan) = NULL;
static int (*test_key) () = NULL;

#if defined WIN32
BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
        if (ul_reason_for_call == DLL_PROCESS_DETACH) {
                extern void ExitFcn(void);

                ExitFcn();
        }
        return(TRUE);
}
#endif

extern "C" __declspec(dllexport) void init (
	void (*foutput) (char *),
	void (*foutput1) (char *, ...),
	int (*fwait_key) (int *),
	int (*ftest_key) ())
{
        output=foutput;
        output1=foutput1;
        wait_key=fwait_key;
        test_key=ftest_key;
}

void CheckInterrupted(structlpsolvecaller *lpsolvecaller, short *interrupted)
{
        if (test_key != NULL) {
                /* Printf("test_key() = %d\n", test_key()); */
                if (test_key()==escape)
                        *interrupted = TRUE;
        }
}

void Printf(char *format, ...)
{
        va_list ap;
        static char buf[4096];

	va_start(ap, format);
        vsnprintf(buf, sizeof(buf), format, ap);
        va_end(ap);
        if (output != NULL)
                output(buf);
        else
                showmsg(buf, MB_ICONINFORMATION);
}


/* Function to get a real scalar with error checking */

Double GetRealScalar(structlpsolvecaller *lpsolvecaller, int element)
{
        rMatrix mat = GetpMatrix(lpsolvecaller, element);
        char OK = TRUE;
        header *hd;
        Double a = 0;

        if (mat->type == s_real) {
                a = *realof(mat);
	}
        else
                OK = FALSE;

        if (!OK) {
		ErrMsgTxt(lpsolvecaller, "GetRealScalar: Expecting a scalar argument.");
                /*
                sprintf(buf, "Expecting a scalar argument. %d %d %d", GetM(lpsolvecaller, mat), GetN(lpsolvecaller, mat), mat->argtype);
                ErrMsgTxt(lpsolvecaller, buf);
                */
        }

        return(a);
}


#define GetVector(lpsolvecaller, element, vec, cast, start, len, exactcount, ret) \
{ \
	int	k, m, n, count = 0; \
        double *pdouble; \
        rMatrix pm = GetpMatrix(lpsolvecaller, element); \
 \
        if (pm->type == s_real) { \
                m = 1; \
                n = 1; \
	} \
        else { \
	        m = GetM(lpsolvecaller, pm); \
	        n = GetN(lpsolvecaller, pm); \
        } \
 \
	if ( !((m == 1) || (n == 1)) || \
             ((m == 1) && (((exactcount) && (len != n)) || ((!exactcount) && (n > len)))) || \
             ((n == 1) && (((exactcount) && (len != m)) || ((!exactcount) && (m > len)))) || \
	     !((pm->type == s_real) || (pm->type == s_matrix)) ) { \
		ErrMsgTxt(lpsolvecaller, "GetVector: invalid vector."); \
	} \
 \
        if (n == 1) \
                len = m; \
        else \
                len = n; \
        vec += start; \
 \
        if (pm->type == s_real) { \
                pdouble = realof(pm); \
        } \
        else { \
                pdouble = matrixof(pm); \
        } \
        \
        for (k = 0; k < len; k++, pdouble++, vec++) { \
	  	*vec = (cast) *pdouble; \
  	} \
 \
        count = len; \
 \
        ret = count; \
}

/* Functions to get len elements from a Euler vector. */

int GetIntVector(structlpsolvecaller *lpsolvecaller, int element, int *vec, int start, int len, int exactcount)
{
        int ret;

        GetVector(lpsolvecaller, element, vec, int, start, len, exactcount, ret)

        return(ret);
}

int GetRealVector(structlpsolvecaller *lpsolvecaller, int element, Double *vec, int start, int len, int exactcount)
{
        int ret;

        GetVector(lpsolvecaller, element, vec, Double, start, len, exactcount, ret)

        return(ret);
}

/* Function to get max len elements from a Euler vector.
   Euler doesn't know to pase sparse matrixes, so a matrix is converted to sparse */

int GetRealSparseVector(structlpsolvecaller *lpsolvecaller, int element, Double *vec, int *index, int start, int len, int col)
{
	int	k, m, n, count = 0, step;
        double *pdouble;
        rMatrix pm = GetpMatrix(lpsolvecaller, element);

	m = GetM(lpsolvecaller, pm);
	n = GetN(lpsolvecaller, pm);

	if (  ((col == 0) && (((m != 1) && (n != 1)) || ((m == 1) && (n > len)) || ((n == 1) && (m > len)))) ||
              ((col != 0) && ((m > len) || (col > n))) ||
              (pm->type != s_matrix)  ) {
/* Printf("1: m=%d, n=%d, col=%d, len=%d, IsNumeric=%d, IsComplex=%d\n", m,n,col,len,IsNumeric(pm),IsComplex(pm)); */
		ErrMsgTxt(lpsolvecaller, "GetRealSparseVector: invalid vector.");
	}

        if ((((n == 1) || (col != 0)) && (m != len)) || ((col == 0) && (m == 1) && (n != len))) {
/* Printf("2: m=%d, n=%d, col=%d, len=%d\n", m,n,col,len); */
                ErrMsgTxt(lpsolvecaller, "GetRealSparseVector: invalid vector.");
        }

        pdouble = matrixof(pm);

        if ((m == 1) || (n == 1))
                step = 1;
        else
                step = n;
        if (col)
                pdouble += col - 1;
        for (k = 0; k < len; k++, pdouble += step) {
                if (*pdouble) {
			*(vec++) = *pdouble;
                	*(index++) = start + k;
                	count++;
                }
	}

        return(count);
}

int GetString(structlpsolvecaller *lpsolvecaller, pMatrix ppm, int element, char *buf, int size, int ShowError)
{
        rMatrix x_in = GetpMatrix(lpsolvecaller, element);
        char *ptr;
        int l;

        if (x_in == NULL)
                ErrMsgTxt(lpsolvecaller, "GetString: Unexistent argument.");

        if (ppm != NULL)
                ErrMsgTxt(lpsolvecaller, "GetString: Invalid vector.");

        if (x_in->type != s_string) {
                if(ShowError)
                	ErrMsgTxt(lpsolvecaller, "GetString: Expecting a character element.");
                return(FALSE);
        }

        ptr = stringof(x_in);
        l = (int) strlen(ptr);
        if (l < size)
                size = l;
        else
                size--;
        memcpy(buf, ptr, size);
        buf[size] = 0;

        return(TRUE);
}

strArray GetCellCharItems(structlpsolvecaller *lpsolvecaller, int element, int len, int ShowError)
{
        return(NULL);
}

void GetCellString(structlpsolvecaller *lpsolvecaller, char **pa, int element, char *buf, int len)
{
        strncpy(buf, pa[element], len);
}

void FreeCellCharItems(strArray pa, int len)
{
}

double *CreateDoubleMatrix(structlpsolvecaller *lpsolvecaller, int m, int n, int element)
{
        double *ptr;
        struct structargout *argout = lpsolvecaller->argout;

        argout[element].typevar = typevardouble;
        argout[element].m = m;
        argout[element].n = n;
        if (m == 0)
                m = 1;
        if (n == 0)
                n = 1;
        ptr = (double *) malloc(m * n * sizeof(double));
        argout[element].argout = (void *) ptr;
        if (element >= lpsolvecaller->nargout)
                lpsolvecaller->nargout = element + 1;
        return(ptr);
}

void SetColumnDoubleSparseMatrix(structlpsolvecaller *lpsolvecaller, int element, int m, int n, double *mat, int column, double *arry, int *index, int size, int *nz)
{
        double *sr = mat + (column - 1) * m, a;
        int ii, i, j = -1;

        for (i = 0; (i < size); i++) {
                a = arry[i];
                if (a) {
                        if (index == NULL)
                                ii = i;
                        else
                                ii = index[i] - 1;

                        while (++j < ii)
                                sr[j] = 0.0;

                        sr[ii] = a;
                }
        }

        while (++j < m)
                sr[j] = 0.0;

        *nz += m;
}

void CreateString(structlpsolvecaller *lpsolvecaller, char **str, int n, int element)
{
        struct structargout *argout = lpsolvecaller->argout;
        char **str1;
        int i;

        str1 = (char **) matCalloc(n, sizeof(*str1));
        for (i = 0; i < n; i++)
                str1[i] = strdup(str[i]);
        argout[element].typevar = typevarstring;
        argout[element].m = 1;
        argout[element].n = n;
        argout[element].argout = (void *) str1;
        if (element >= lpsolvecaller->nargout)
                lpsolvecaller->nargout = element + 1;

}

void setargout(structlpsolvecaller *lpsolvecaller)
{
        struct structargout *argout = lpsolvecaller->argout;
        int i, j, k, m, n, m1, n1, nargout;
        header *hd;
        double *re, *ptrd, *ptrd1;
        char **str;
        int len;
        char hadarg = TRUE /* FALSE */;

        if (argout != NULL) {
          nargout = lpsolvecaller->nargout;
          if (nargout == 0)
                  nargout = 1;
          for (k = 0; k < nargout; k++) {
            if (argout[k].argout != NULL) {
              hadarg = TRUE;
              switch (argout[k].typevar) {
              case typevardouble:
                m = argout[k].m;
                n = argout[k].n;
                hd = new_matrix(m, n, lpsolvecaller->newram, lpsolvecaller->ramend);
        	if (hd != NULL) {
                  re = matrixof(hd);
                  ptrd = (double *) argout[k].argout;
                  if ((m == 1) || (n == 1)) {
                          m1 = 1;
                          if (m == 1)
                                  n1 = n;
                          else
                                  n1 = m;
                  }
                  else {
                          m1 = m;
                          n1 = n;
                  }
                  for (i = 0; i < m1; i++)
                          for (ptrd1 = ptrd + i, j = 0; j < n1; j++, ptrd1 += m1)
                                  *(re++) = *ptrd1;
                }
                break;
              case typevarstring:
                n1 = argout[k].n;
                str = (char **) argout[k].argout;
                if (n1 == 1)
                  new_string(*str, lpsolvecaller->newram, lpsolvecaller->ramend);
                else
                  new_string("", lpsolvecaller->newram, lpsolvecaller->ramend);
                break;
              }
              free(argout[k].argout);
            }
            else if (hadarg) {
              /* new_real(0.0, lpsolvecaller->newram, lpsolvecaller->ramend); */
              hd = new_matrix(0, 0, lpsolvecaller->newram, lpsolvecaller->ramend);
            }
          }
          free(argout);
        }
}
