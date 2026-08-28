from lpsolve55 import *

lp = lpsolve('make_lp', 0, 4)
lpsolve('set_obj_fn', lp, [1, 3, 6.24, 0.1])
lpsolve('add_constraint', lp, [0, 78.26, 0, 2.9], GE, 92.3)
lpsolve('add_constraint', lp, [0.24, 0, 11.31, 0], LE, 14.8)
lpsolve('add_constraint', lp, [12.68, 0, 0.08, 0.9], GE, 4)
lpsolve('set_lowbo', lp, 1, 28.6)
lpsolve('set_lowbo', lp, 4, 18)
lpsolve('set_upbo', lp, 4, 48.98)
lpsolve('set_int', lp, [1, 1, 1, 1])

def abortfunc(lp, userhandle): print("abortfunc(%d, %s)" % (lp, userhandle)); return 0
lpsolve('put_abortfunc', lp, abortfunc, "abortfunc")

def logfunc(lp, userhandle, buf): print("logfunc(%d, %s, %s)" % (lp, userhandle, buf)); return 0
lpsolve('put_logfunc', lp, logfunc, "logfunc")

def msgfunc(lp, userhandle, message): print("msgfunc(%d, %s %d)" % (lp, userhandle, message)); return 0
lpsolve('put_msgfunc', lp, msgfunc, "msgfunc", 1023)

def branchfunc(lp, branchhandle, column): print("branchfunc(%d, %s, %d)" % (lp, branchhandle, column)); return 0
lpsolve('put_bb_branchfunc', lp, branchfunc, "branchfunc")

def nodefunc(lp, nodehandle, vartype): print("nodefunc(%d, %s, %d)" % (lp, nodehandle, vartype)); return -1
lpsolve('put_bb_nodefunc', lp, nodefunc, "nodefunc")

lpsolve('solve', lp)
lpsolve('delete_lp', lp)
