#include <stdarg.h>

#include "lpsolvecaller.h"

#if defined _MSC_VER
# define vsnprintf _vsnprintf
#endif

lme_ref global_lme = NULL;

extern callerPrototype(drivername);

static lme_fn fn[] =
{
    {strdrivername, drivername, 0, maxnargin, 1, maxnargout}
};

lme_int32 InstallFn(lme_ref lme, lme_fn **fnarray)
{
    LMECB_DbgWriteStr("lpsolve extension: sqlpsolve");
    *fnarray = fn;
    return sizeof(fn) / sizeof(fn[0]);
}

void ShutdownFn(lme_ref lme)
{
    extern void ExitFcn(void);

    ExitFcn();
}

void CheckInterrupted(structlpsolvecaller *lpsolvecaller, short *interrupted)
{
        lme_ref lme = lpsolvecaller->lme;

        /* Printf("LMECB_CheckAbort() = %d\n", LMECB_CheckAbort()); */
        if (!LMECB_CheckAbort())
                *interrupted = TRUE;
}

void Printf(char *format, ...)
{
        va_list ap;
        static char buf[4096];
        lme_ref lme = global_lme;

        if (lme != NULL) {
    	    va_start(ap, format);
    	    vsnprintf(buf, sizeof(buf), format, ap);
            va_end(ap);
            /* LMECB_DbgWriteStr(buf); */
            LMECB_Write(1, buf, -1, 1);
        }
}

/* Function to get a real scalar with error checking */

Double GetRealScalar(structlpsolvecaller *lpsolvecaller, int element)
{
        lme_float64 *re, *im;
        lme_err status;
        lme_int32 m, n;
        lme_ref lme = lpsolvecaller->lme;

        status = LMECB_GetMatrix(element + 1, &m, &n, &re, &im);
        if (!status) {
                ErrMsgTxt(lpsolvecaller, "GetRealScalar: Unable to get value. Expecting a real scalar argument.");
        }
/*
{
 int i;

 Printf("%d: double[%d*%d]:", element, (int) m, (int) n);
 for (i = 0; i < m * n; i++)
   Printf(" %f", re[i]);
 Printf("\n");
}
*/
	if ((m == 1) && (n == 1) && (re != NULL) && (im == NULL)) {
		return((Double) *re);
	} else {
		ErrMsgTxt(lpsolvecaller, "GetRealScalar: Expecting a real scalar argument.");
	}
        return(0.0);
}

#define GetVector(lpsolvecaller, element, vec, cast, start, len, exactcount, ret) \
{ \
	int	k, count = 0; \
        lme_float64 *re, *im; \
        lme_err status; \
        lme_int32 m, n; \
        lme_ref lme = lpsolvecaller->lme; \
 \
        status = LMECB_GetMatrix(element + 1, &m, &n, &re, &im); \
        if (!status) { \
                ErrMsgTxt(lpsolvecaller, "GetVector: Unable to get value. Expecting a real vector argument."); \
        } \
 \
	if ( !((m == 1) || (n == 1)) || \
             ((m == 1) && (((exactcount) && (len != n)) || ((!exactcount) && (n > len)))) || \
             ((n == 1) && (((exactcount) && (len != m)) || ((!exactcount) && (m > len)))) || \
	     (re == NULL) || (im != NULL)) { \
		ErrMsgTxt(lpsolvecaller, "GetVector: invalid vector."); \
	} \
 \
        if (n == 1) \
                len = m; \
        else \
                len = n; \
/* Printf("%d: double[%d*%d]:", element, (int) m, (int) n); */ \
        vec += start; \
	for (k = 0; k < len; k++, re++, vec++) { \
		*vec = (cast) *re; \
/* Printf(" %f (%f)", (double) *vec, (double) *re); */ \
	} \
/* Printf("\n"); */ \
        count = len; \
 \
        ret = count; \
}

/* Functions to get len elements from a Sysquake vector. Matrix
   can be either full or sparse. Elements are stored in indices
   start..start+n-1  Errors out if the Sysquake vector is not length len */

int GetIntVector(structlpsolvecaller *lpsolvecaller, int element, int *vec, int start, int len, int exactcount)
{
        int ret;

        GetVector(lpsolvecaller, element, vec, int, start, len, exactcount, ret);

        return(ret);
}

int GetRealVector(structlpsolvecaller *lpsolvecaller, int element, Double *vec, int start, int len, int exactcount)
{
        int ret;

        GetVector(lpsolvecaller, element, vec, Double, start, len, exactcount, ret);

        return(ret);
}


/* Function to get max len elements from a Sysquake sparse vector. Matrix
   can be either full or sparse. Elements are stored in indices
   start..start+n-1  Errors out if the Sysquake vector is longer than length len */

int GetRealSparseVector(structlpsolvecaller *lpsolvecaller, int element, Double *vec, int *index, int start, int len, int col)
{
	int	k, count = 0, step;
        lme_float64 *re, *im;
        lme_err status;
        lme_int32 m, n;
        lme_ref lme = lpsolvecaller->lme;

        status = LMECB_GetMatrix(element + 1, &m, &n, &re, &im);
        if (!status) {
                ErrMsgTxt(lpsolvecaller, "GetRealSparseVector: Unable to get value. Expecting a real vector argument.");
        }

	if (  ((col == 0) && (((m != 1) && (n != 1)) || ((m == 1) && (n > len)) || ((n == 1) && (m > len)))) ||
              ((col != 0) && ((m > len) || (col > n))) ||
	      (re == NULL) ||
              (im != NULL)  ) {
		ErrMsgTxt(lpsolvecaller, "GetRealSparseVector: invalid vector.");
	}

        if ((((n == 1) || (col != 0)) && (m != len)) || ((col == 0) && (m == 1) && (n != len)))
                ErrMsgTxt(lpsolvecaller, "GetRealSparseVector: invalid vector.");

        if ((m == 1) || (n == 1))
                step = 1;
        else
                step = n;
        if (col)
                re += col - 1;
/* Printf("%d: double[%d*%d]:", element, (int) m, (int) n); */
        for (k = 0; k < len; k++, re += step) {
                if (*re) {
			*(vec++) = *re;
                	*(index++) = start + k;
/* Printf(" %d: %f (%f)", start + k, (double) vec[-1], (double) *re); */
                	count++;
                }
	}
/* Printf("\n"); */

        return(count);
}

int GetString(structlpsolvecaller *lpsolvecaller, pMatrix ppm, int element, char *buf, int size, int ShowError)
{
        lme_string8 str;
	lme_int32 l;
        lme_err status;
        lme_ref lme = lpsolvecaller->lme;

        status = LMECB_GetString(element + 1, &str, &l);
        if (!status) {
                if (ShowError)
                        ErrMsgTxt(lpsolvecaller, "GetString: Unable to get value. Expecting a string argument.");
                return(FALSE);
        }

        if (l < size)
                size = l;
        else
                size--;
        memcpy(buf, (char *) str, size);
        buf[size] = 0;

        return(TRUE);
}

strArray GetCellCharItems(structlpsolvecaller *lpsolvecaller, int element, int len, int ShowError)
{
        lme_ref lme = lpsolvecaller->lme;
        lme_err ret;
        lme_object o;
        lme_int32 status, i, j, len1, ndims, size[k_lme_max_ndims], nbytes, type;
        lme_object el;
        pMatrix pa0 = NULL;
        pMatrix pa;
        unsigned short *data;

        if ((!LMECB_GetObject(element + 1, &o)) || (o.objtype != k_lme_obj_list) || (!LMECB_ObjectLength(&o, &len1))) {
                if (ShowError)
                        ErrMsgTxt(lpsolvecaller, "Expecting a cell argument.");
        }
        else {
                if (len1 != len) {
                        ErrMsgTxt(lpsolvecaller, "invalid vector.");
                }
                else {
                        pa = pa0 = (pMatrix) matCalloc(len, sizeof(*pa));
                        for (i = 1; i <= len; i++) {
                                if ((!LMECB_GetElementFromListObject(&o, i, &el)) ||
                                    (!LMECB_ObjectToArray(&el, &ndims, size, &nbytes, &type, (void **)&data)) ||
                                    (type != k_lme_type_char) ||
                                    (nbytes != sizeof(*data)))
                                        break;
                                pa->typevar = typevarunicode;
                                pa->m = 1;
                                for (pa->n = size[0], j = 1; j < ndims; j++)
          			    pa->n *= size[j];
                                pa->argout = (void *) data;
                                pa++;
                        }
                        if (i < len) {
                                matFree(pa0);
                                pa0 = NULL;
                        	ErrMsgTxt(lpsolvecaller, "Expecting a character cell element.");
                        }
                }
        }
        return(pa0);
}

void GetCellString(structlpsolvecaller *lpsolvecaller, strArray pa, int element, char *buf, int len)
{
        unsigned short *data;
        int i, n;

        data = (unsigned short *) pa[element].argout;
        n = pa[element].n;
        if (n >= len)
                n = len - 1;
        for (i = 0; i < n; i++)
                buf[i] = (char) data[i];
        buf[n] = 0;
}

void FreeCellCharItems(strArray pa, int len)
{
        if (pa != NULL)
        	matFree(pa);
}

double *CreateDoubleMatrix(structlpsolvecaller *lpsolvecaller, int m, int n, int element)
{
        double *ptr = (double *) malloc(m * n * sizeof(double));
        struct structargout *argout = lpsolvecaller->argout;

        argout[element].typevar = typevardouble;
        argout[element].m = m;
        argout[element].n = n;
        argout[element].argout = (void *) ptr;
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
}

void setargout(structlpsolvecaller *lpsolvecaller)
{
        struct structargout *argout = lpsolvecaller->argout;
        int i, j, k, m, n, m1, n1;
        lme_err status;
        lme_ref lme = lpsolvecaller->lme;
        lme_float64 *re;
        double *ptrd, *ptrd1;
        lme_string8 s;
        char **str;
        int len;
        char hadarg = TRUE /* FALSE */;

        for (k = ((lpsolvecaller->nlhs == 0) ? 0 : lpsolvecaller->nlhs - 1); k >= 0; k--) {
          if (argout[k].argout != NULL) {
            hadarg = TRUE;
            switch (argout[k].typevar) {
            case typevardouble:
              status = LMECB_PushMatrix(argout[k].m, argout[k].n, &re, NULL);
              if (status) {
                ptrd = (double *) argout[k].argout;
                m = argout[k].m;
                n = argout[k].n;
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
              if (n1 > 1) {
                status = LMECB_PushEmptyList();
              }
              else
                status = 1;
              for (j = 0; (status) && (j < n1); j++, str++) {
                len = strlen(*str);
                status = LMECB_StartPushString(len, &s);
        	if (status) {
          	  memcpy(s, *str, len);
          	  status = LMECB_EndPushString();
                  if ((status) && (n1 > 1)) {
                    status = LMECB_AddListElement();
                  }
                }
              }
              break;
            }
          }
          else if (hadarg) {
            double a = 0.0;

            re = &a;
            status = LMECB_PushMatrix(0, 0, &re, NULL);
          }
        }
}

struct structargout *GetpMatrix(structlpsolvecaller *lpsolvecaller, int element)
{
        lme_float64 *re, *im;
        lme_err status;
        lme_int32 m, n;
        lme_ref lme = lpsolvecaller->lme;
        static struct structargout argout;

        status = LMECB_GetMatrix(element + 1, &m, &n, &re, &im);
        if (!status) {
                ErrMsgTxt(lpsolvecaller, "GetpMatrix: Unable to get value. Expecting a matrix argument.");
        }
        if ((re == NULL) || (im != NULL)) {
                ErrMsgTxt(lpsolvecaller, "GetpMatrix: Expecting a real matrix argument.");
        }
        argout.typevar = typevardouble;
        argout.m = m;
        argout.n = n;
        argout.argout = (void *) re;

        return(&argout);
}
