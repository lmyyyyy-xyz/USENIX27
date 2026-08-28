#include <stdarg.h>

#include "lpsolvecaller.h"

void Printf(char *format, ...)
{
        va_list ap;
        static char buf[4096];

	va_start(ap, format);
	vsnprintf(buf, sizeof(buf), format, ap);
        octave_stdout << buf;
	va_end(ap);
}

int ErrMsgTxt(structlpsolvecaller *lpsolvecaller, char *str)
{
	error(str);
        exitnow(lpsolvecaller);

        return(0);
}

void setargs(structlpsolvecaller *lpsolvecaller, const octave_value_list &prhs, int nlhs)
{
        lpsolvecaller->prhs = prhs;
        lpsolvecaller->nrhs = prhs.length();
        lpsolvecaller->nlhs = nlhs;
}

/* Function to get a real scalar with error checking */

Double GetRealScalar(structlpsolvecaller *lpsolvecaller, int element)
{
        if (lpsolvecaller->prhs(element).is_real_scalar())
		return(lpsolvecaller->prhs(element).double_value());
        else
		ErrMsgTxt(lpsolvecaller, "Expecting a scalar argument.");
        return(0.0);
}

#define GetVector(lpsolvecaller, element, vec, cast, start, len, exactcount, ret) \
{ \
	int	i, j, m, n; \
        cast    *vec0; \
        Matrix  mat(lpsolvecaller->prhs(element).matrix_value()); \
 \
	m = GetM(lpsolvecaller, mat); \
	n = GetN(lpsolvecaller, mat); \
 \
	if ( !((m == 1) || (n == 1)) || \
             ((m == 1) && (((exactcount) && (len != n)) || ((!exactcount) && (n > len)))) || \
             ((n == 1) && (((exactcount) && (len != m)) || ((!exactcount) && (m > len)))) || \
	     !IsNumeric(lpsolvecaller->prhs(element)) || IsComplex(lpsolvecaller->prhs(element))) \
		ErrMsgTxt(lpsolvecaller, "invalid vector."); \
 \
        vec += start; \
        vec0 = vec; \
        for (i = 0; i < m; i++) \
                for (j = 0; j < n; j++, vec++) \
                        *vec = (cast) mat(i, j); \
 \
        ret = (int) (vec - vec0); \
}

/* Functions to get len elements from an octave vector.
   Elements are stored in indices
   start..start+n-1 */

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

/* Function to get max len elements from an octave vector.
   octave doesn't know sparse matrixes, so a matrix is converted to sparse */

int GetRealSparseVector(structlpsolvecaller *lpsolvecaller, Matrix &mat, Double *vec, int *index, int start, int len, int col)
{
	int	i, j, k, m, n, count = 0;
        double  a;

	m = GetM(lpsolvecaller, mat);
	n = GetN(lpsolvecaller, mat);

        if (  ((col == 0) && (((m != 1) && (n != 1)) || ((m == 1) && (n > len)) || ((n == 1) && (m > len)))) ||
              ((col != 0) && ((m > len) || (col > n))))
		ErrMsgTxt(lpsolvecaller, "invalid vector.");

        if ((((n == 1) || (col != 0)) && (m != len)) || ((col == 0) && (m == 1) && (n != len)))
                ErrMsgTxt(lpsolvecaller, "invalid vector.");

        if (col)
                n = col;
        k = 0;
        for (i = 0; (i < m) && (k < len); i++) {
                if (col)
                        j = col - 1;
                else
                        j = 0;
                for (; (j < n) && (k < len); j++, k++) {
                        if ((a = mat(i, j)) != 0.0) {
				*(vec++) = (Double) a;
                        	*(index++) = start + k;
                        	count++;
                        }
                }
        }
        return(count);
}

int GetRealSparseVector(structlpsolvecaller *lpsolvecaller, int element, Double *vec, int *index, int start, int len, int col)
{
        Matrix  mat;

	if (!IsNumeric(lpsolvecaller->prhs(element)) ||
             IsComplex(lpsolvecaller->prhs(element))  )
		ErrMsgTxt(lpsolvecaller, "invalid vector.");
        mat = lpsolvecaller->prhs(element).matrix_value();
        return(GetRealSparseVector(lpsolvecaller, mat, vec, index, start, len, col));
}

int GetRealSparseVector2(structlpsolvecaller *lpsolvecaller, rMatrix mat, int element, Double *vec, int *index, int start, int len, int col)
{
        return(GetRealSparseVector(lpsolvecaller, element, vec, index, start, len, col));
}

int GetString(structlpsolvecaller *lpsolvecaller, pMatrix ppm, int element, char *buf, int size, int ShowError)
{
        if (ppm != NULL) {
                ErrMsgTxt(lpsolvecaller, "invalid vector.");
        }

	if ((!lpsolvecaller->prhs(element).is_string()) || (lpsolvecaller->prhs(element).rows() > 1)) {
                if (ShowError)
                	ErrMsgTxt(lpsolvecaller, "Expecting a character element.");
                return(FALSE);
        }
        std::string str = lpsolvecaller->prhs(element).string_value();
        int l = str.length();
        if (l >= size)
                l = size - 1;
        if (l >= 0) {
                strncpy(buf, &(str[0]), l);
                buf[l] = 0;
        }
        return(TRUE);
}

strArray GetCellCharItems(structlpsolvecaller *lpsolvecaller, int element, int len, int ShowError)
{
        int m, n, i, k, l;
        Cell pm;
        strArray pa;
        strArray pa0;

        if (!lpsolvecaller->prhs(element).is_cell()) {
                if (ShowError)
                        ErrMsgTxt(lpsolvecaller, "Expecting a cell argument.");
                return(NULL);
        }

        pm = lpsolvecaller->prhs(element).cell_value();

        m = GetM(lpsolvecaller, pm);
        n = GetN(lpsolvecaller, pm);
        if (!(((m == 1) && (n == len)) || ((n == 1) && (m == len))))
                ErrMsgTxt(lpsolvecaller, "invalid cell dimension.");
        pa = pa0 = (strArray) matCalloc(len, sizeof(*pa));
        for (i = 0; i < len; i++) {
                if (m == 1) {
                        k = 0;
                        l = i;
                }
                else {
                        k = i;
                        l = 0;
                }
                if (!pm(k, l).is_string())
                        break;
                std::string str = pm(k, l).string_value();
                int l = str.length();
                *pa = (char *) matCalloc(l + 1, sizeof(char));
                strncpy(*pa, &(str[0]), l);
                (*pa)[l] = 0;
                pa++;
        }
        if (i < len) {
                for (--i; i >= 0; i--)
                        matFree(pa0[i]);
                matFree(pa0);
        	ErrMsgTxt(lpsolvecaller, "Expecting a character cell element.");
        }
        return(pa0);
}


void FreeCellCharItems(strArray pa, int len)
{
        int i;

        for (i = 0; i < len; i++)
        	matFree(pa[i]);
	matFree(pa);
}


double *CreateDoubleMatrix(structlpsolvecaller *lpsolvecaller, int m, int n, int element)
{
        return((double *) malloc(m * n * sizeof(double)));
}

void SetDoubleMatrix(structlpsolvecaller *lpsolvecaller, double *mat, int m, int n, int element, int freemat)
{
        if (mat != NULL) {
                double *mat0 = mat;
                Matrix Mat(m, n);
                int i, j;

                for (j = 0; j < n; j++)
                        for (i = 0; i < m; i++)
                                Mat(i, j) = *(mat++);
                if (freemat)
                        free(mat0);
                lpsolvecaller->plhs(element) = Mat;
        }
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
        if (n == 1) {
                lpsolvecaller->plhs(element) = *str;
        }
        else {
                int i;
                Cell cellout(1, n);

                for (i = 0; i < n; i++)
                        cellout(0, i) = str[i];
                lpsolvecaller->plhs(element) = cellout;
        }
}
