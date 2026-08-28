from lpsolve55 import *

lp = lpsolve('make_lp', 0, 4)
lpsolve('set_verbose', lp, IMPORTANT)
lpsolve('set_obj_fn', lp, [1, 3, 6.24, 0.1])
lpsolve('add_constraint', lp, [0, 78.26, 0, 2.9], GE, 92.3)
lpsolve('add_constraint', lp, [0.24, 0, 11.31, 0], LE, 14.8)
lpsolve('add_constraint', lp, [12.68, 0, 0.08, 0.9], GE, 4)
lpsolve('set_lowbo', lp, 1, 28.6)
lpsolve('set_lowbo', lp, 4, 18)
lpsolve('set_upbo', lp, 4, 48.98)
lpsolve('set_verbose', lp, 0)
lpsolve('set_int', lp, [1, 1, 1, 1])
def abortfunc(lp, userhandle): print("abortfunc(%d, %s)" % (lp, userhandle)); return 0

lpsolve('put_abortfunc', lp, abortfunc, "extra")
lpsolve('solve', lp)
lpsolve('delete_lp', lp)
