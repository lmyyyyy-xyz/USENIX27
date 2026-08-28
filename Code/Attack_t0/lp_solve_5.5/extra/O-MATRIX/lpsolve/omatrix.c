#include "lpsolvecaller.h"

#if defined _MSC_VER
# define vsnprintf _vsnprintf
#endif

void    (__cdecl *prText)     (char *, char *);

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
        if (ul_reason_for_call == DLL_PROCESS_DETACH) {
                extern void ExitFcn();

                ExitFcn();
                prText = NULL;
        }
        return(TRUE);
}

void Printf(char *format, ...)
{
        va_list ap;
        static char buf[4096];

        if (prText != NULL) {
        	va_start(ap, format);
        	vsnprintf(buf, sizeof(buf), format, ap);
                va_end(ap);
        	prText("command", buf);
        }
#if 0
        else if (nrhs < 1) {
                char *ptr;

        	va_start(ap, format);
        	vsnprintf(buf, sizeof(buf), format, ap);
                va_end(ap);
                strcat(buf, "\nNo printing capability to command window available.\nYou need to upgrade to version 5.8 for this feature.");
                ptr = buf;
                CreateString(&ptr, 1, plhs, 0);
        }
#endif
}

void setargs(structlpsolvecaller *lpsolvecaller, int narg, int nret, pMatrix ret, pMatrix arg, pMatrix (__cdecl *direct) (pMatrix), void (__cdecl *allocate) (pMatrix), void (__cdecl *free_mat) (pMatrix), void (__cdecl *error) (char *, char *), void (__cdecl *prText0) (char *, char *))
{
        lpsolvecaller->nrhs = narg;
        lpsolvecaller->nlhs = nret;
        lpsolvecaller->plhs = ret;
        lpsolvecaller->prhs = arg;
        lpsolvecaller->direct = direct;
        lpsolvecaller->allocate = allocate;
        lpsolvecaller->free_mat = free_mat;
        lpsolvecaller->error = error;

        if ((unsigned long) prText0 > 0x1000)
        	prText = prText0;
        else
                prText = NULL;
}

/* Function to get a real scalar with error checking */

Double GetRealScalar(structlpsolvecaller *lpsolvecaller, int element)
{
        rMatrix mat = GetpMatrix(lpsolvecaller, element);
        char OK = TRUE;
        Double a;

        if ((GetM(lpsolvecaller, mat) == 1) && (GetN(lpsolvecaller, mat) == 1)) {
            	switch (mat->type) {
                case INT_mat:
                        a = (Double) mat->adr.i[0];
                        break;
                case REAL_mat:
                        a = (Double) mat->adr.r[0];
                        break;
                case DOUBLE_mat:
                        a = (Double) mat->adr.d[0];
                        break;
                default:
                        OK = FALSE;
                        break;
                }
	}
        else
                OK = FALSE;

        if (!OK) {
		ErrMsgTxt(lpsolvecaller, "Expecting a scalar argument.");
                /*
                sprintf(buf, "Expecting a scalar argument. %d %d %d", GetM(lpsolvecaller, mat), GetN(lpsolvecaller, mat), mat->type);
                ErrMsgTxt(lpsolvecaller, buf);
                */
        }

        return(a);
}


#define GetVector(lpsolvecaller, element, vec, cast, start, len, exactcount, ret) \
{ \
	int	k, m, n, count = 0; \
	int	*pri; \
        float   *prr; \
        double	*prd; \
        rMatrix pm = GetpMatrix(lpsolvecaller, element); \
 \
	m = GetM(lpsolvecaller, pm); \
	n = GetN(lpsolvecaller, pm); \
 \
	if ( !((m == 1) || (n == 1)) || \
             ((m == 1) && (((exactcount) && (len != n)) || ((!exactcount) && (n > len)))) || \
             ((n == 1) && (((exactcount) && (len != m)) || ((!exactcount) && (m > len)))) || \
	     !IsNumeric(pm) || IsComplex(pm)) { \
		ErrMsgTxt(lpsolvecaller, "invalid vector."); \
	} \
 \
        if (n == 1) \
                len = m; \
        else \
                len = n; \
        vec += start; \
 \
        switch (pm->type) { \
        case INT_mat: \
                pri = pm->adr.i; \
                for (k = 0; k < len; k++, pri++, vec++) { \
		  	*vec = (cast) *pri; \
	  	} \
          	break; \
        case REAL_mat: \
                prr = pm->adr.r; \
                for (k = 0; k < len; k++, prr++, vec++) { \
		  	*vec = (cast) *prr; \
	  	} \
          	break; \
        case DOUBLE_mat: \
                prd = pm->adr.d; \
                for (k = 0; k < len; k++, prd++, vec++) { \
		  	*vec = (cast) *prd; \
	  	} \
          	break; \
        } \
 \
        count = len; \
 \
        ret = count; \
}

/* Functions to get len elements from a O-rMatrix vector. */

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


/* Function to get max len elements from a O-rMatrix vector.
   O-rMatrix doesn't know sparse matrixes, so a matrix is converted to sparse */

int GetRealSparseVector(structlpsolvecaller *lpsolvecaller, int element, Double *vec, int *index, int start, int len, int col)
{
	int	j, k, k1, m, n, start1, count = 0;
	int	*pri;
        float   *prr;
        double	*prd;
        rMatrix mat = GetpMatrix(lpsolvecaller, element);

	m = GetM(lpsolvecaller, mat);
	n = GetN(lpsolvecaller, mat);

	if (  ((col == 0) && (((m != 1) && (n != 1)) || ((m == 1) && (n > len)) || ((n == 1) && (m > len)))) ||
              ((col != 0) && ((m > len) || (col > n))) ||
	      !IsNumeric(mat) ||
              IsComplex(mat)  ) {
/* Printf("1: m=%d, n=%d, col=%d, len=%d, IsNumeric=%d, IsComplex=%d\n", m,n,col,len,IsNumeric(mat),IsComplex(mat)); */
		ErrMsgTxt(lpsolvecaller, "invalid vector.");
	}

        if ((((n == 1) || (col != 0)) && (m != len)) || ((col == 0) && (m == 1) && (n != len))) {
/* Printf("2: m=%d, n=%d, col=%d, len=%d\n", m,n,col,len); */
                ErrMsgTxt(lpsolvecaller, "invalid vector.");
        }

        switch (mat->type) {
        case INT_mat:
                pri = mat->adr.i;
                if (col)
                	pri += (col - 1) * m;
                for (k = 0; k < len; k++, pri++) {
                        if (*pri) {
				*(vec++) = (Double) *pri;
                		*(index++) = start + k;
                		count++;
                        }
	  	}
          	break;
        case REAL_mat:
                prr = mat->adr.r;
                if (col)
                	prr += (col - 1) * m;
                for (k = 0; k < len; k++, prr++) {
                        if (*prr) {
				*(vec++) = (Double) *prr;
                		*(index++) = start + k;
                		count++;
                        }
	  	}
          	break;
        case DOUBLE_mat:
                prd = mat->adr.d;
                if (col)
                	prd += (col - 1) * m;
                for (k = 0; k < len; k++, prd++) {
                        if (*prd) {
				*(vec++) = (Double) *prd;
                		*(index++) = start + k;
                		count++;
                        }
	  	}
          	break;
        }

        return(count);
}

int GetString(structlpsolvecaller *lpsolvecaller, pMatrix ppm, int element, char *buf, int size, int ShowError)
{
        rMatrix x_in = GetpMatrix(lpsolvecaller, element);

        if (ppm != NULL)
                ErrMsgTxt(lpsolvecaller, "Invalid vector.");

        if (x_in->type != CHAR_mat) {
                if(ShowError)
                	ErrMsgTxt(lpsolvecaller, "Expecting a character element.");
                return(FALSE);
        }
        if (x_in->nr != 1)
                ErrMsgTxt(lpsolvecaller, "Expecting a single row string.");
        if (x_in->nc < size)
                size = x_in->nc;
        else
                size--;
        memcpy(buf, (char *) x_in->adr.c, size);
        buf[size] = 0;
        return(TRUE);
}

strArray GetCellCharItems(structlpsolvecaller *lpsolvecaller, int element, int len, int ShowError)
{
        int m, n, i, j, k;
        rMatrix x_in = GetpMatrix(lpsolvecaller, element);
        char **pa0, **pa, *str, *c;

        if (x_in->type != CHAR_mat) {
                if (ShowError)
                        ErrMsgTxt(lpsolvecaller, "Expecting a character element.");
                return(NULL);
        }
        m = GetM(lpsolvecaller, x_in);
        n = GetN(lpsolvecaller, x_in);
        if (!(m == len))
                ErrMsgTxt(lpsolvecaller, "invalid vector.");

        str = (char *) matCalloc(n + 1, sizeof(*str));

        pa = pa0 = (char **) matCalloc(len, sizeof(*pa));
        c = (char *) x_in->adr.c;
        for (i = 0; i < len; i++, c++) {
                for (k = -1, j = 0; j < n; j++)
                        if (!isspace(str[j] = c[j * m]))
                                k = j;
                str[k + 1] = 0;
                *(pa++) = strdup(str);
        }
        matFree(str);
        return(pa0);
}

void GetCellString(structlpsolvecaller *lpsolvecaller, char **pa, int element, char *buf, int len)
{
        strncpy(buf, pa[element], len);
}

void FreeCellCharItems(strArray pa, int len)
{
        int i;

        for (i = 0; i < len; i++)
                free(pa[i]);
	matFree(pa);
}


Double *CreateDoubleMatrix(structlpsolvecaller *lpsolvecaller, int m, int n, int element)
{
        pMatrix plhs = lpsolvecaller->plhs + element;

        lpsolvecaller->free_mat(plhs);
        plhs->nr   = m;
        plhs->nc   = n;
        plhs->type = DOUBLE_mat;
        lpsolvecaller->allocate(plhs);
        return(plhs->adr.d);
}

Long *CreateLongMatrix(structlpsolvecaller *lpsolvecaller, int m, int n, int element)
{
        pMatrix plhs = lpsolvecaller->plhs + element;

        lpsolvecaller->free_mat(plhs);
        plhs->nr   = m;
        plhs->nc   = n;
        plhs->type = INT_mat;
        lpsolvecaller->allocate(plhs);
        return(plhs->adr.i);
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
        pMatrix plhs = lpsolvecaller->plhs + element;
        int i, j, l0, l = 0;
        char *ptr, *str0;

        for (i = 0; i < m; i++) {
        	l0 = strlen(str[i]);
                if (l0 > l)
                        l = l0;
        }
        lpsolvecaller->free_mat(plhs);
        plhs->nr   = m;
        plhs->nc   = l;
        plhs->type = CHAR_mat;
        lpsolvecaller->allocate(plhs);
        ptr = (char *) plhs->adr.c;
        memset(ptr, ' ', m * l);
        for (i = 0; i < m; i++, ptr++) {

                str0 = str[i];
                l0 = strlen(str0);
                for (j = 0; j < l0; j++)
        		ptr[j * m] = str0[j];
        }
}
