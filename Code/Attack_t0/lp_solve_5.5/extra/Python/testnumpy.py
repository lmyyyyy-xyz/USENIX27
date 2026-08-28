from numpy import *
from lpsolve55 import *
lp=lpsolve('make_lp', 0, 4);
c = array([1, 3, 6.24, 0.1])
ret = lpsolve('set_obj_fn', lp, c)
ret = lpsolve('write_lp', lp, 'a.lp')