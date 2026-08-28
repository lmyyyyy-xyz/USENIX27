#include <mex.h> 
static int direct_gateway(char *fname,void F(void)) { F();return 0;};
extern Gatefunc mex_mexscilab;
static GenericTable Tab[]={
  {mex_gateway,mex_mexscilab,"sclpsolve"},
};
 
int C2F(sclpsolve)()
{
  Rhs = Max(0, Rhs);
  (*(Tab[Fin-1].f))(Tab[Fin-1].name,Tab[Fin-1].F);
  return 0;
}
