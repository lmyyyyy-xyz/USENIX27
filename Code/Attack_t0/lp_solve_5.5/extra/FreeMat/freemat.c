#include <stdarg.h>

#include "lpsolvecaller.h"

#if defined _MSC_VER
# define vsnprintf _vsnprintf
#endif

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

void Printf(char *format, ...)
{
        va_list ap;
        static char buf[4096];

	va_start(ap, format);
	vsnprintf(buf, sizeof(buf), format, ap);
        va_end(ap);
        showmsg(buf, MB_ICONINFORMATION);
}


/* Function to get a real scalar with error checking */

Double GetRealScalar(structlpsolvecaller *lpsolvecaller, int element)
{
        rMatrix mat = GetpMatrix(lpsolvecaller, element);
        char OK = TRUE;
        Double a;

        if ((GetM(lpsolvecaller, mat) == 1) && (GetN(lpsolvecaller, mat) == 1)) {
            	switch (mat->argtype) {
                case arguint8:
                        a = (Double) *((unsigned char *) mat->ptr);
                        break;
                case argint8:
                        a = (Double) *((signed char *) mat->ptr);
                        break;
                case arguint16:
                        a = (Double) *((unsigned short *) mat->ptr);
                        break;
                case argint16:
                        a = (Double) *((signed short *) mat->ptr);
                        break;
                case arguint32:
                        a = (Double) *((unsigned int *) mat->ptr);
                        break;
                case argint32:
                        a = (Double) *((signed int *) mat->ptr);
                        break;
                case argfloat:
                        a = (Double) *((float *) mat->ptr);
                        break;
                case argdouble:
                        a = (Double) *((double *) mat->ptr);
                        break;
                default:
                        OK = FALSE;
                        break;
                }
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
        rMatrix pm = GetpMatrix(lpsolvecaller, element); \
 \
	m = GetM(lpsolvecaller, pm); \
	n = GetN(lpsolvecaller, pm); \
 \
	if ( !((m == 1) || (n == 1)) || \
             ((m == 1) && (((exactcount) && (len != n)) || ((!exactcount) && (n > len)))) || \
             ((n == 1) && (((exactcount) && (len != m)) || ((!exactcount) && (m > len)))) || \
	     !IsNumeric(pm) || IsComplex(pm)) { \
		ErrMsgTxt(lpsolvecaller, "GetVector: invalid vector."); \
	} \
 \
        if (n == 1) \
                len = m; \
        else \
                len = n; \
        vec += start; \
 \
    	switch (pm->argtype) { \
        case arguint8: \
            { \
                unsigned char *puint8 = (unsigned char *) pm->ptr; \
                \
                for (k = 0; k < len; k++, puint8++, vec++) { \
		  	*vec = (cast) *puint8; \
	  	} \
            } \
            break; \
        case argint8: \
            { \
                signed char *pint8 = (signed char *) pm->ptr; \
                \
                for (k = 0; k < len; k++, pint8++, vec++) { \
		  	*vec = (cast) *pint8; \
	  	} \
            } \
            break; \
        case arguint16: \
            { \
                unsigned short *puint16 = (unsigned short *) pm->ptr; \
                \
                for (k = 0; k < len; k++, puint16++, vec++) { \
		  	*vec = (cast) *puint16; \
	  	} \
            } \
            break; \
        case argint16: \
            { \
                signed short *pint16 = (signed short *) pm->ptr; \
                \
                for (k = 0; k < len; k++, pint16++, vec++) { \
		  	*vec = (cast) *pint16; \
	  	} \
            } \
            break; \
        case arguint32: \
            { \
                unsigned int *puint32 = (unsigned int *) pm->ptr; \
                \
                for (k = 0; k < len; k++, puint32++, vec++) { \
		  	*vec = (cast) *puint32; \
	  	} \
            } \
            break; \
        case argint32: \
            { \
                signed int *pint32 = (signed int *) pm->ptr; \
                \
                for (k = 0; k < len; k++, pint32++, vec++) { \
		  	*vec = (cast) *pint32; \
	  	} \
            } \
            break; \
        case argfloat: \
            { \
                float *pfloat = (float *) pm->ptr; \
                \
                for (k = 0; k < len; k++, pfloat++, vec++) { \
		  	*vec = (cast) *pfloat; \
	  	} \
            } \
            break; \
        case argdouble: \
            { \
                double *pdouble = (double *) pm->ptr; \
                \
                for (k = 0; k < len; k++, pdouble++, vec++) { \
		  	*vec = (cast) *pdouble; \
	  	} \
            } \
            break; \
        } \
 \
        count = len; \
 \
        ret = count; \
}

/* Functions to get len elements from a FreeMat vector. */

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


/* Function to get max len elements from a FreeMat vector.
   FreeMat doesn't know to pase sparse matrixes, so a matrix is converted to sparse */

int GetRealSparseVector(structlpsolvecaller *lpsolvecaller, int element, Double *vec, int *index, int start, int len, int col)
{
	int	j, k, k1, m, n, start1, count = 0;
        rMatrix pm = GetpMatrix(lpsolvecaller, element);

	m = GetM(lpsolvecaller, pm);
	n = GetN(lpsolvecaller, pm);

	if (  ((col == 0) && (((m != 1) && (n != 1)) || ((m == 1) && (n > len)) || ((n == 1) && (m > len)))) ||
              ((col != 0) && ((m > len) || (col > n))) ||
	      !IsNumeric(pm) ||
              IsComplex(pm)  ) {
/* Printf("1: m=%d, n=%d, col=%d, len=%d, IsNumeric=%d, IsComplex=%d\n", m,n,col,len,IsNumeric(pm),IsComplex(pm)); */
		ErrMsgTxt(lpsolvecaller, "GetRealSparseVector: invalid vector.");
	}

        if ((((n == 1) || (col != 0)) && (m != len)) || ((col == 0) && (m == 1) && (n != len))) {
/* Printf("2: m=%d, n=%d, col=%d, len=%d\n", m,n,col,len); */
                ErrMsgTxt(lpsolvecaller, "GetRealSparseVector: invalid vector.");
        }

    	switch (pm->argtype) {
        case arguint8:
            {
                unsigned char *puint8 = (unsigned char *) pm->ptr;

                if (col)
                	puint8 += (col - 1) * m;
                for (k = 0; k < len; k++, puint8++) {
                        if (*puint8) {
				*(vec++) = (Double) *puint8;
                		*(index++) = start + k;
                		count++;
                        }
	  	}
            }
            break;
        case argint8:
            {
                signed char *pint8 = (signed char *) pm->ptr;

                if (col)
                	pint8 += (col - 1) * m;
                for (k = 0; k < len; k++, pint8++) {
                        if (*pint8) {
				*(vec++) = (Double) *pint8;
                		*(index++) = start + k;
                		count++;
                        }
	  	}
            }
            break;
        case arguint16:
            {
                unsigned short *puint16 = (unsigned short *) pm->ptr;

                if (col)
                	puint16 += (col - 1) * m;
                for (k = 0; k < len; k++, puint16++) {
                        if (*puint16) {
				*(vec++) = (Double) *puint16;
                		*(index++) = start + k;
                		count++;
                        }
	  	}
            }
            break;
        case argint16:
            {
                signed short *pint16 = (signed short *) pm->ptr;

                if (col)
                	pint16 += (col - 1) * m;
                for (k = 0; k < len; k++, pint16++) {
                        if (*pint16) {
				*(vec++) = (Double) *pint16;
                		*(index++) = start + k;
                		count++;
                        }
	  	}
            }
            break;
        case arguint32:
            {
                unsigned int *puint32 = (unsigned int *) pm->ptr;

                if (col)
                	puint32 += (col - 1) * m;
                for (k = 0; k < len; k++, puint32++) {
                        if (*puint32) {
				*(vec++) = (Double) *puint32;
                		*(index++) = start + k;
                		count++;
                        }
	  	}
            }
            break;
        case argint32:
            {
                signed int *pint32 = (signed int *) pm->ptr;

                if (col)
                	pint32 += (col - 1) * m;
                for (k = 0; k < len; k++, pint32++) {
                        if (*pint32) {
				*(vec++) = (Double) *pint32;
                		*(index++) = start + k;
                		count++;
                        }
	  	}
            }
            break;
        case argfloat:
            {
                float *pfloat = (float *) pm->ptr;

                if (col)
                	pfloat += (col - 1) * m;
                for (k = 0; k < len; k++, pfloat++) {
                        if (*pfloat) {
				*(vec++) = (Double) *pfloat;
                		*(index++) = start + k;
                		count++;
                        }
	  	}
            }
            break;
        case argdouble:
            {
                double *pdouble = (double *) pm->ptr;

                if (col)
                	pdouble += (col - 1) * m;
                for (k = 0; k < len; k++, pdouble++) {
                        if (*pdouble) {
				*(vec++) = (Double) *pdouble;
                		*(index++) = start + k;
                		count++;
                        }
	  	}
            }
            break;
        }

        return(count);
}

int GetString(structlpsolvecaller *lpsolvecaller, pMatrix ppm, int element, char *buf, int size, int ShowError)
{
        rMatrix x_in = GetpMatrix(lpsolvecaller, element);
        int l;

        if (x_in == NULL)
                ErrMsgTxt(lpsolvecaller, "GetString: Unexistent argument.");

        if (ppm != NULL)
                ErrMsgTxt(lpsolvecaller, "GetString: Invalid vector.");

        if (x_in->argtype != argstring) {
                if(ShowError)
                	ErrMsgTxt(lpsolvecaller, "GetString: Expecting a character element.");
                return(FALSE);
        }
        if ((x_in->m != 1) || (x_in->n != 1))
                ErrMsgTxt(lpsolvecaller, "GetString: Expecting a single row string.");
        l = (int) strlen((char *) x_in->arg.string);
        if (l < size)
                size = l;
        else
                size--;
        memcpy(buf, (char *) x_in->arg.string, size);
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

#define CreateMatrix(lpsolvecaller, m, n, element, cast) \
        (cast *) malloc(m * n * sizeof(cast))

#define SetMatrix(lpsolvecaller, mat, m, n, element, freemat, cast) \
  if ((element < lpsolvecaller->nlhs) && (mat != NULL)) { \
	int	k, m0, n0, len; \
        rMatrix pm = GetpMatrix(lpsolvecaller, lpsolvecaller->nrhs + element); \
        cast *vec = mat; \
  \
/* Printf("element = %d, lpsolvecaller->nrhs = %d, pm = %x\n", element, lpsolvecaller->nrhs, pm); */ \
	m0 = GetM(lpsolvecaller, pm); \
	n0 = GetN(lpsolvecaller, pm); \
/* Printf("m = %d, m0 = %d, n = %d, n0 = %d\n", m, m0, n, n0); */ \
  \
	if ( !(((m == m0) && (n == n0)) || ((m == n0) && (n == m0))) || \
	     !IsNumeric(pm) || IsComplex(pm)) { \
		ErrMsgTxt(lpsolvecaller, "SetMatrix: invalid vector."); \
	} \
  \
        len = m * n;\
  \
    	switch (pm->argtype) { \
        case arguint8: \
            { \
                unsigned char *puint8 = (unsigned char *) pm->ptr; \
                \
                for (k = 0; k < len; k++, puint8++, vec++) { \
		  	*puint8 = (unsigned char) *vec; \
	  	} \
            } \
            break; \
        case argint8: \
            { \
                signed char *pint8 = (signed char *) pm->ptr; \
                \
                for (k = 0; k < len; k++, pint8++, vec++) { \
		  	*pint8 = (signed char) *vec; \
	  	} \
            } \
            break; \
        case arguint16: \
            { \
                unsigned short *puint16 = (unsigned short *) pm->ptr; \
                \
                for (k = 0; k < len; k++, puint16++, vec++) { \
		  	*puint16 = (unsigned short) *vec; \
	  	} \
            } \
            break; \
        case argint16: \
            { \
                signed short *pint16 = (signed short *) pm->ptr; \
                \
                for (k = 0; k < len; k++, pint16++, vec++) { \
		  	*pint16 = (signed short) *vec; \
	  	} \
            } \
            break; \
        case arguint32: \
            { \
                unsigned int *puint32 = (unsigned int *) pm->ptr; \
                \
                for (k = 0; k < len; k++, puint32++, vec++) { \
		  	*puint32 = (unsigned int) *vec; \
	  	} \
            } \
            break; \
        case argint32: \
            { \
                signed int *pint32 = (signed int *) pm->ptr; \
                \
                for (k = 0; k < len; k++, pint32++, vec++) { \
		  	*pint32 = (signed int) *vec; \
	  	} \
            } \
            break; \
        case argfloat: \
            { \
                float *pfloat = (float *) pm->ptr; \
                \
                for (k = 0; k < len; k++, pfloat++, vec++) { \
		  	*pfloat = (float) *vec; \
	  	} \
            } \
            break; \
        case argdouble: \
            { \
                double *pdouble = (double *) pm->ptr; \
                \
                for (k = 0; k < len; k++, pdouble++, vec++) { \
		  	*pdouble = (double) *vec; \
	  	} \
            } \
            break; \
        } \
  \
  } \
  if (freemat) \
	free(mat);

double *CreateDoubleMatrix(structlpsolvecaller *lpsolvecaller, int m, int n, int element)
{
        return(CreateMatrix(lpsolvecaller, m, n, element, double));
}

double *CreateDoubleSparseMatrix(structlpsolvecaller *lpsolvecaller, int m, int n, int element)
{
        return(CreateDoubleMatrix(lpsolvecaller, m, n, element));
}

void SetDoubleMatrix(structlpsolvecaller *lpsolvecaller, double *mat, int m, int n, int element, int freemat)
{
        SetMatrix(lpsolvecaller, mat, m, n, element, freemat, double);
}

long *CreateLongMatrix(structlpsolvecaller *lpsolvecaller, int m, int n, int element)
{
        return(CreateMatrix(lpsolvecaller, m, n, element, long));
}

void SetLongMatrix(structlpsolvecaller *lpsolvecaller, long *mat, int m, int n, int element, int freemat)
{
        SetMatrix(lpsolvecaller, mat, m, n, element, freemat, long);
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

void CreateString(structlpsolvecaller *lpsolvecaller, char **str, int m, int element)
{
        rMatrix x_in = GetpMatrix(lpsolvecaller, lpsolvecaller->nrhs + element);
        int l0, l;
        char *ptr;

        if (m != 1)
                ErrMsgTxt(lpsolvecaller, "CreateString: Invalid string size.");

        if (x_in == NULL)
                ErrMsgTxt(lpsolvecaller, "CreateString: Unexistent argument.");

        if (x_in->argtype != argstring) {
        	ErrMsgTxt(lpsolvecaller, "CreateString: Expecting a character element.");
        }
        if ((x_in->m != 1) || (x_in->n != 1))
                ErrMsgTxt(lpsolvecaller, "CreateString: Expecting a single row string.");

        l0 = strlen(str[0]);
        ptr = (char *) x_in->arg.string;
        l = (int) strlen(ptr);
        if (l0 < l)
                l = l0;
/* Printf("l = %d, l0 = %d, str[0] = %s\n", l, l0, str[0]); */
        memcpy(ptr, str[0], l);
        ptr[l] = 0;
}
