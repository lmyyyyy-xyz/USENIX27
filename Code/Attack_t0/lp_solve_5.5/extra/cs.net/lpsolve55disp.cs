using System;
using System.Runtime.InteropServices;

namespace lpsolve55
{
    public enum lpsolve_constr_types
    {
        LE = 1,
        EQ = 3,
        GE = 2,
        FR = 0,
    }
    public enum lpsolve_scales
    {
        SCALE_EXTREME = 1,
        SCALE_RANGE = 2,
        SCALE_MEAN = 3,
        SCALE_GEOMETRIC = 4,
        SCALE_CURTISREID = 7,
        SCALE_QUADRATIC = 8,
        SCALE_LOGARITHMIC = 16,
        SCALE_USERWEIGHT = 31,
        SCALE_POWER2 = 32,
        SCALE_EQUILIBRATE = 64,
        SCALE_INTEGERS = 128,
        SCALE_DYNUPDATE = 256,
        SCALE_ROWSONLY = 512,
        SCALE_COLSONLY = 1024,
    }
    public enum lpsolve_improves
    {
        IMPROVE_NONE = 0,
        IMPROVE_SOLUTION = 1,
        IMPROVE_DUALFEAS = 2,
        IMPROVE_THETAGAP = 4,
        IMPROVE_BBSIMPLEX = 8,
        IMPROVE_DEFAULT = (IMPROVE_DUALFEAS + IMPROVE_THETAGAP),
        IMPROVE_INVERSE = (IMPROVE_SOLUTION + IMPROVE_THETAGAP)
    }
    public enum lpsolve_piv_rules
    {
        PRICER_FIRSTINDEX = 0,
        PRICER_DANTZIG = 1,
        PRICER_DEVEX = 2,
        PRICER_STEEPESTEDGE = 3,
        PRICE_PRIMALFALLBACK = 4,
        PRICE_MULTIPLE = 8,
        PRICE_PARTIAL = 16,
        PRICE_ADAPTIVE = 32,
        PRICE_HYBRID = 64,
        PRICE_RANDOMIZE = 128,
        PRICE_AUTOPARTIALCOLS = 256,
        PRICE_AUTOPARTIALROWS = 512,
        PRICE_LOOPLEFT = 1024,
        PRICE_LOOPALTERNATE = 2048,
        PRICE_AUTOPARTIAL = lpsolve_piv_rules.PRICE_AUTOPARTIALCOLS + lpsolve_piv_rules.PRICE_AUTOPARTIALROWS,
    }
    public enum lpsolve_presolve
    {
        PRESOLVE_NONE = 0,
        PRESOLVE_ROWS = 1,
        PRESOLVE_COLS = 2,
        PRESOLVE_LINDEP = 4,
        PRESOLVE_SOS = 32,
        PRESOLVE_REDUCEMIP = 64,
        PRESOLVE_KNAPSACK = 128,
        PRESOLVE_ELIMEQ2 = 256,
        PRESOLVE_IMPLIEDFREE = 512,
        PRESOLVE_REDUCEGCD = 1024,
        PRESOLVE_PROBEFIX = 2048,
        PRESOLVE_PROBEREDUCE = 4096,
        PRESOLVE_ROWDOMINATE = 8192,
        PRESOLVE_COLDOMINATE = 16384,
        PRESOLVE_MERGEROWS = 32768,
        PRESOLVE_IMPLIEDSLK = 65536,
        PRESOLVE_COLFIXDUAL = 131072,
        PRESOLVE_BOUNDS = 262144,
        PRESOLVE_DUALS = 524288,
        PRESOLVE_SENSDUALS = 1048576
    }
    public enum lpsolve_anti_degen
    {
        ANTIDEGEN_NONE = 0,
        ANTIDEGEN_FIXEDVARS = 1,
        ANTIDEGEN_COLUMNCHECK = 2,
        ANTIDEGEN_STALLING = 4,
        ANTIDEGEN_NUMFAILURE = 8,
        ANTIDEGEN_LOSTFEAS = 16,
        ANTIDEGEN_INFEASIBLE = 32,
        ANTIDEGEN_DYNAMIC = 64,
        ANTIDEGEN_DURINGBB = 128,
        ANTIDEGEN_RHSPERTURB = 256,
        ANTIDEGEN_BOUNDFLIP = 512
    }
    public enum lpsolve_basiscrash
    {
        CRASH_NOTHING = 0,
        CRASH_MOSTFEASIBLE = 2,
    }
    public enum lpsolve_simplextypes
    {
        SIMPLEX_PRIMAL_PRIMAL = 5,
        SIMPLEX_DUAL_PRIMAL = 6,
        SIMPLEX_PRIMAL_DUAL = 9,
        SIMPLEX_DUAL_DUAL = 10,
    }
    public enum lpsolve_BBstrategies
    {
        NODE_FIRSTSELECT = 0,
        NODE_GAPSELECT = 1,
        NODE_RANGESELECT = 2,
        NODE_FRACTIONSELECT = 3,
        NODE_PSEUDOCOSTSELECT = 4,
        NODE_PSEUDONONINTSELECT = 5,
        NODE_PSEUDORATIOSELECT = 6,
        NODE_USERSELECT = 7,
        NODE_WEIGHTREVERSEMODE = 8,
        NODE_BRANCHREVERSEMODE = 16,
        NODE_GREEDYMODE = 32,
        NODE_PSEUDOCOSTMODE = 64,
        NODE_DEPTHFIRSTMODE = 128,
        NODE_RANDOMIZEMODE = 256,
        NODE_GUBMODE = 512,
        NODE_DYNAMICMODE = 1024,
        NODE_RESTARTMODE = 2048,
        NODE_BREADTHFIRSTMODE = 4096,
        NODE_AUTOORDER = 8192,
        NODE_RCOSTFIXING = 16384,
        NODE_STRONGINIT = 32768
    }
    public enum lpsolve_return
    {
        NOMEMORY = -2,
        OPTIMAL = 0,
        SUBOPTIMAL = 1,
        INFEASIBLE = 2,
        UNBOUNDED = 3,
        DEGENERATE = 4,
        NUMFAILURE = 5,
        USERABORT = 6,
        TIMEOUT = 7,
        PRESOLVED = 9,
        PROCFAIL = 10,
        PROCBREAK = 11,
        FEASFOUND = 12,
        NOFEASFOUND = 13,
        ACCURACYERROR = 25,
    }
    public enum lpsolve_branch
    {
        BRANCH_CEILING = 0,
        BRANCH_FLOOR = 1,
        BRANCH_AUTOMATIC = 2,
        BRANCH_DEFAULT = 3,
    }

    public enum lpsolve_msgmask
    {
        MSG_PRESOLVE = 1,
        MSG_LPFEASIBLE = 8,
        MSG_LPOPTIMAL = 16,
        MSG_MILPEQUAL = 32,
        MSG_MILPFEASIBLE = 128,
        MSG_MILPBETTER = 512,
    }
    public delegate bool ctrlcfunc(int userhandle);
    public delegate void logfunc(int userhandle, string buf);
    public delegate void msgfunc(int userhandle, lpsolve_msgmask message);





    public class lpsolve : IDisposable
    {
        private IntPtr m_lp;
        private bool disposed = false;

        static lpsolve()
        {
            lpsolveInner.Init();
        }

        public lpsolve(int nRow, int nCol)
        {
            m_lp = lpsolveInner.make_lp(nRow, nCol);

        }

        public lpsolve(lpsolve lp)
        {
            m_lp = lpsolveInner.copy_lp(lp.m_lp);

        }

        // Implement IDisposable.
        // Do not make this method virtual.
        // A derived class should not be able to override this method.
        public void Dispose()
        {
            Dispose(true);
            // This object will be cleaned up by the Dispose method.
            // Therefore, you should call GC.SupressFinalize to
            // take this object off the finalization queue
            // and prevent finalization code for this object
            // from executing a second time.
            GC.SuppressFinalize(this);
        }

        // Dispose(bool disposing) executes in two distinct scenarios.
        // If disposing equals true, the method has been called directly
        // or indirectly by a user's code. Managed and unmanaged resources
        // can be disposed.
        // If disposing equals false, the method has been called by the
        // runtime from inside the finalizer and you should not reference
        // other objects. Only unmanaged resources can be disposed.
        private void Dispose(bool disposing)
        {
            // Check to see if Dispose has already been called.
            if (!this.disposed)
            {
                // If disposing equals true, dispose all managed
                // and unmanaged resources.
                if (disposing)
                {
                    // Dispose managed resources.
                }

                // Call the appropriate methods to clean up
                // unmanaged resources here.
                // If disposing is false,
                // only the following code is executed.
                if (IntPtr.Zero != m_lp)
                {
                    lpsolveInner.delete_lp(m_lp);
                }
                m_lp = IntPtr.Zero;

                // Note disposing has been done.
                disposed = true;

            }
        }

        // Use C# destructor syntax for finalization code.
        // This destructor will run only if the Dispose method
        // does not get called.
        // It gives your base class the opportunity to finalize.
        // Do not provide destructors in types derived from this class.
        ~lpsolve()
        {
            // Do not re-create Dispose clean-up code here.
            // Calling Dispose(false) is optimal in terms of
            // readability and maintainability.
            Dispose(false);
        }

        public bool add_column(double[] column)
        {
            return lpsolveInner.add_column(m_lp, column);
        }
        public bool add_columnex(int count, double[] column, int[] rowno)
        {
            return lpsolveInner.add_columnex(m_lp, count, column, rowno);
        }
        public bool add_constraint(double[] row, lpsolve_constr_types constr_type, double rh)
        {
            return lpsolveInner.add_constraint(m_lp, row, constr_type, rh);
        }
        public bool add_constraintex(int count, double[] row, int[] colno, lpsolve_constr_types constr_type, double rh)
        {
            return lpsolveInner.add_constraintex(m_lp, count, row, colno, constr_type, rh);
        }
        public bool add_lag_con(double[] row, lpsolve_constr_types con_type, double rhs)
        {
            return lpsolveInner.add_lag_con(m_lp, row, con_type, rhs);
        }
        public int add_SOS(string name, int sostype, int priority, int count, int[] sosvars, double[] weights)
        {
            return lpsolveInner.add_SOS(m_lp, name, sostype, priority, count, sosvars, weights);
        }
        public int column_in_lp(double[] column)
        {
            return lpsolveInner.column_in_lp(m_lp, column);
        }
        public void default_basis()
        {
            lpsolveInner.default_basis(m_lp);
        }
        public bool del_column(int column)
        {
            return lpsolveInner.del_column(m_lp, column);
        }
        public bool del_constraint(int del_row)
        {
            return lpsolveInner.del_constraint(m_lp, del_row);
        }
        private bool dualize_lp()
        {
            return lpsolveInner.dualize_lp(m_lp);
        }
        public lpsolve_anti_degen get_anti_degen()
        {
            return lpsolveInner.get_anti_degen(m_lp);
        }
        public bool get_basis(int[] bascolumn, bool nonbasic)
        {
            return lpsolveInner.get_basis(m_lp, bascolumn, nonbasic);
        }
        public lpsolve_basiscrash get_basiscrash()
        {
            return lpsolveInner.get_basiscrash(m_lp);
        }
        public int get_bb_depthlimit()
        {
            return lpsolveInner.get_bb_depthlimit(m_lp);
        }
        public lpsolve_branch get_bb_floorfirst()
        {
            return lpsolveInner.get_bb_floorfirst(m_lp);
        }
        public lpsolve_BBstrategies get_bb_rule()
        {
            return lpsolveInner.get_bb_rule(m_lp);
        }
        public bool get_bounds_tighter()
        {
            return lpsolveInner.get_bounds_tighter(m_lp);
        }
        public double get_break_at_value()
        {
            return lpsolveInner.get_break_at_value(m_lp);
        }
        public string get_col_name(int column)
        {
            return lpsolveInner.get_col_name(m_lp, column);
        }
        public bool get_column(int col_nr, double[] column)
        {
            return lpsolveInner.get_column(m_lp, col_nr, column);
        }
        public int get_columnex(int col_nr, double[] column, int[] nzrow)
        {
            return lpsolveInner.get_columnex(m_lp, col_nr, column, nzrow);
        }
        public lpsolve_constr_types get_constr_type(int row)
        {
            return lpsolveInner.get_constr_type(m_lp, row);
        }
        public double get_constr_value(int row, int count, double[] primsolution, int[] nzindex)
        {
            return lpsolveInner.get_constr_value(m_lp, row, count, primsolution, nzindex);
        }
        public bool get_constraints(double[] constr)
        {
            return lpsolveInner.get_constraints(m_lp, constr);
        }
        public bool get_dual_solution(double[] rc)
        {
            return lpsolveInner.get_dual_solution(m_lp, rc);
        }
        public double get_epsb()
        {
            return lpsolveInner.get_epsb(m_lp);
        }
        public double get_epsd()
        {
            return lpsolveInner.get_epsd(m_lp);
        }
        public double get_epsel()
        {
            return lpsolveInner.get_epsel(m_lp);
        }
        public double get_epsint()
        {
            return lpsolveInner.get_epsint(m_lp);
        }
        public double get_epsperturb()
        {
            return lpsolveInner.get_epsperturb(m_lp);
        }
        public double get_epspivot()
        {
            return lpsolveInner.get_epspivot(m_lp);
        }
        public lpsolve_improves get_improve()
        {
            return lpsolveInner.get_improve(m_lp);
        }
        public double get_infinite()
        {
            return lpsolveInner.get_infinite(m_lp);
        }
        public bool get_lambda(double[] lambda)
        {
            return lpsolveInner.get_lambda(m_lp, lambda);
        }
        public double get_lowbo(int column)
        {
            return lpsolveInner.get_lowbo(m_lp, column);
        }
        public int get_lp_index(int orig_index)
        {
            return lpsolveInner.get_lp_index(m_lp, orig_index);
        }
        public string get_lp_name()
        {
            return lpsolveInner.get_lp_name(m_lp);
        }
        public int get_Lrows()
        {
            return lpsolveInner.get_Lrows(m_lp);
        }
        public double get_mat(int row, int column)
        {
            return lpsolveInner.get_mat(m_lp, row, column);
        }
        public int get_max_level()
        {
            return lpsolveInner.get_max_level(m_lp);
        }
        public int get_maxpivot()
        {
            return lpsolveInner.get_maxpivot(m_lp);
        }
        public double get_mip_gap(bool absolute)
        {
            return lpsolveInner.get_mip_gap(m_lp, absolute);
        }
        public int get_Ncolumns()
        {
            return lpsolveInner.get_Ncolumns(m_lp);
        }
        public double get_negrange()
        {
            return lpsolveInner.get_negrange(m_lp);
        }
        public int get_nameindex(string name, bool isrow)
        {
            return lpsolveInner.get_nameindex(m_lp, name, isrow);
        }
        public int get_nonzeros()
        {
            return lpsolveInner.get_nonzeros(m_lp);
        }
        public int get_Norig_columns()
        {
            return lpsolveInner.get_Norig_columns(m_lp);
        }
        public int get_Norig_rows()
        {
            return lpsolveInner.get_Norig_rows(m_lp);
        }
        public int get_Nrows()
        {
            return lpsolveInner.get_Nrows(m_lp);
        }
        public double get_obj_bound()
        {
            return lpsolveInner.get_obj_bound(m_lp);
        }
        public double get_objective()
        {
            return lpsolveInner.get_objective(m_lp);
        }
        public int get_orig_index(IntPtr lp_index)
        {
            return lpsolveInner.get_orig_index(m_lp, lp_index);
        }
        public string get_origcol_name(int column)
        {
            return lpsolveInner.get_origcol_name(m_lp, column);
        }
        public string get_origrow_name(int row)
        {
            return lpsolveInner.get_origrow_name(m_lp, row);
        }
        public lpsolve_piv_rules get_pivoting()
        {
            return lpsolveInner.get_pivoting(m_lp);
        }
        public lpsolve_presolve get_presolve()
        {
            return lpsolveInner.get_presolve(m_lp);
        }
        public int get_presolveloops()
        {
            return lpsolveInner.get_presolveloops(m_lp);
        }
        public bool get_primal_solution(double[] pv)
        {
            return lpsolveInner.get_primal_solution(m_lp, pv);
        }
        public int get_print_sol()
        {
            return lpsolveInner.get_print_sol(m_lp);
        }
        public bool get_PseudoCosts(double[] clower, double[] cupper, int[] updatelimit)
        {
            return lpsolveInner.get_PseudoCosts(m_lp, clower, cupper, updatelimit);
        }
        public double get_rh(int row)
        {
            return lpsolveInner.get_rh(m_lp, row);
        }
        public double get_rh_range(int row)
        {
            return lpsolveInner.get_rh_range(m_lp, row);
        }
        public bool get_row(int row_nr, double[] row)
        {
            return lpsolveInner.get_row(m_lp, row_nr, row);
        }
        public int get_rowex(int row_nr, double[] row, int[] colno)
        {
            return lpsolveInner.get_rowex(m_lp, row_nr, row, colno);
        }
        public string get_row_name(int row)
        {
            return lpsolveInner.get_row_name(m_lp, row);
        }
        public double get_scalelimit()
        {
            return lpsolveInner.get_scalelimit(m_lp);
        }
        public lpsolve_scales get_scaling()
        {
            return lpsolveInner.get_scaling(m_lp);
        }
        public bool get_sensitivity_obj(double[] objfrom, double[] objtill)
        {
            return lpsolveInner.get_sensitivity_obj(m_lp, objfrom, objtill);
        }
        public bool get_sensitivity_objex(double[] objfrom, double[] objtill, double[] objfromvalue, double[] objtillvalue)
        {
            return lpsolveInner.get_sensitivity_objex(m_lp, objfrom, objtill, objfromvalue, objtillvalue);
        }
        public bool get_sensitivity_rhs(double[] duals, double[] dualsfrom, double[] dualstill)
        {
            return lpsolveInner.get_sensitivity_rhs(m_lp, duals, dualsfrom, dualstill);
        }
        public lpsolve_simplextypes get_simplextype()
        {
            return lpsolveInner.get_simplextype(m_lp);
        }
        public int get_solutioncount()
        {
            return lpsolveInner.get_solutioncount(m_lp);
        }
        public int get_solutionlimit()
        {
            return lpsolveInner.get_solutionlimit(m_lp);
        }
        public int get_status()
        {
            return lpsolveInner.get_status(m_lp);
        }
        public string get_statustext(int statuscode)
        {
            return lpsolveInner.get_statustext(m_lp, statuscode);
        }
        public int get_timeout()
        {
            return lpsolveInner.get_timeout(m_lp);
        }
        public long get_total_iter()
        {
            return lpsolveInner.get_total_iter(m_lp);
        }
        public long get_total_nodes()
        {
            return lpsolveInner.get_total_nodes(m_lp);
        }
        public double get_upbo(int column)
        {
            return lpsolveInner.get_upbo(m_lp, column);
        }
        public lpsolve_branch get_var_branch(int column)
        {
            return lpsolveInner.get_var_branch(m_lp, column);
        }
        public double get_var_dualresult(int index)
        {
            return lpsolveInner.get_var_dualresult(m_lp, index);
        }
        public double get_var_primalresult(int index)
        {
            return lpsolveInner.get_var_primalresult(m_lp, index);
        }
        public int get_var_priority(int column)
        {
            return lpsolveInner.get_var_priority(m_lp, column);
        }
        public bool get_variables(double[] var)
        {
            return lpsolveInner.get_variables(m_lp, var);
        }
        public int get_verbose()
        {
            return lpsolveInner.get_verbose(m_lp);
        }
        public double get_working_objective()
        {
            return lpsolveInner.get_working_objective(m_lp);
        }
        public bool guess_basis(double[] guessvector, int[] basisvector)
        {
            return lpsolveInner.guess_basis(m_lp, guessvector, basisvector);
        }
        public bool has_BFP()
        {
            return lpsolveInner.has_BFP(m_lp);
        }
        public bool has_XLI()
        {
            return lpsolveInner.has_XLI(m_lp);
        }
        public bool is_add_rowmode()
        {
            return lpsolveInner.is_add_rowmode(m_lp);
        }
        public bool is_anti_degen(lpsolve_anti_degen testmask)
        {
            return lpsolveInner.is_anti_degen(m_lp, testmask);
        }
        public bool is_binary(int column)
        {
            return lpsolveInner.is_binary(m_lp, column);
        }
        public bool is_break_at_first()
        {
            return lpsolveInner.is_break_at_first(m_lp);
        }
        public bool is_constr_type(int row, int mask)
        {
            return lpsolveInner.is_constr_type(m_lp, row, mask);
        }
        public bool is_debug()
        {
            return lpsolveInner.is_debug(m_lp);
        }
        public bool is_feasible(double[] values, double threshold)
        {
            return lpsolveInner.is_feasible(m_lp, values, threshold);
        }
        public bool is_infinite(double value)
        {
            return lpsolveInner.is_infinite(m_lp, value);
        }
        public bool is_int(int column)
        {
            return lpsolveInner.is_int(m_lp, column);
        }
        public bool is_integerscaling()
        {
            return lpsolveInner.is_integerscaling(m_lp);
        }
        public bool is_lag_trace()
        {
            return lpsolveInner.is_lag_trace(m_lp);
        }
        public bool is_maxim()
        {
            return lpsolveInner.is_maxim(m_lp);
        }
        public bool is_nativeBFP()
        {
            return lpsolveInner.is_nativeBFP(m_lp);
        }
        public bool is_nativeXLI()
        {
            return lpsolveInner.is_nativeXLI(m_lp);
        }
        public bool is_negative(int column)
        {
            return lpsolveInner.is_negative(m_lp, column);
        }
        public bool is_piv_mode(lpsolve_piv_rules testmask)
        {
            return lpsolveInner.is_piv_mode(m_lp, testmask);
        }
        public bool is_piv_rule(lpsolve_piv_rules rule)
        {
            return lpsolveInner.is_piv_rule(m_lp, rule);
        }
        public bool is_presolve(lpsolve_presolve testmask)
        {
            return lpsolveInner.is_presolve(m_lp, testmask);
        }
        public bool is_scalemode(lpsolve_scales testmask)
        {
            return lpsolveInner.is_scalemode(m_lp, testmask);
        }
        public bool is_scaletype(lpsolve_scales scaletype)
        {
            return lpsolveInner.is_scaletype(m_lp, scaletype);
        }
        public bool is_semicont(int column)
        {
            return lpsolveInner.is_semicont(m_lp, column);
        }
        public bool is_SOS_var(int column)
        {
            return lpsolveInner.is_SOS_var(m_lp, column);
        }
        public bool is_trace()
        {
            return lpsolveInner.is_trace(m_lp);
        }
        public bool is_unbounded(int column)
        {
            return lpsolveInner.is_unbounded(m_lp, column);
        }
        public bool is_use_names(bool isrow)
        {
            return lpsolveInner.is_use_names(m_lp, isrow);
        }
        public static void lp_solve_version(ref int majorversion, ref int minorversion, ref int release, ref int build)
        {
            lpsolveInner.lp_solve_version(ref majorversion, ref minorversion, ref release, ref build);
        }

        //public IntPtr make_lp(int rows, int columns)
        //{
        //    return lpsolveInner.make_lp(rows, columns);
        //}

        public IntPtr resize_lp(int rows, int columns)
        {
            return lpsolveInner.resize_lp(m_lp, rows, columns);
        }
        public void print_constraints(int columns)
        {
            lpsolveInner.print_constraints(m_lp, columns);
        }
        public bool print_debugdump(string filename)
        {
            return lpsolveInner.print_debugdump(m_lp, filename);
        }
        public void print_duals()
        {
            lpsolveInner.print_duals(m_lp);
        }
        public void print_lp()
        {
            lpsolveInner.print_lp(m_lp);
        }
        public void print_objective()
        {
            lpsolveInner.print_objective(m_lp);
        }
        public void print_scales()
        {
            lpsolveInner.print_scales(m_lp);
        }
        public void print_solution(int columns)
        {
            lpsolveInner.print_solution(m_lp, columns);
        }
        public void print_str(string str)
        {
            lpsolveInner.print_str(m_lp, str);
        }
        public void print_tableau()
        {
            lpsolveInner.print_tableau(m_lp);
        }

        public void put_abortfunc(ctrlcfunc newctrlc, int ctrlchandle)
        {
            lpsolveInner.put_abortfunc(m_lp, newctrlc, ctrlchandle);
        }

        public void put_logfunc(logfunc newlog, int loghandle)
        {
            lpsolveInner.put_logfunc(m_lp, newlog, loghandle);
        }

        public void put_msgfunc(msgfunc newmsg, int msghandle, int mask)
        {
            lpsolveInner.put_msgfunc(m_lp, newmsg, msghandle, mask);
        }
        public bool read_basis(string filename, string info)
        {
            return lpsolveInner.read_basis(m_lp, filename, info);
        }
        public static int read_freeMPS(string filename, int options)
        {
            return lpsolveInner.read_freeMPS(filename, options);
        }
        public static int read_LP(string filename, int verbose, string lp_name)
        {
            return lpsolveInner.read_LP(filename, verbose, lp_name);
        }
        public static int read_MPS(string filename, int options)
        {
            return lpsolveInner.read_MPS(filename, options);
        }
        public static int read_XLI(string xliname, string modelname, string dataname, string options, int verbose)
        {
            return lpsolveInner.read_XLI(xliname, modelname, dataname, options, verbose);
        }
        public bool read_params(string filename, string options)
        {
            return lpsolveInner.read_params(m_lp, filename, options);
        }
        public void reset_basis()
        {
            lpsolveInner.reset_basis(m_lp);
        }
        public void reset_params()
        {
            lpsolveInner.reset_params(m_lp);
        }
        public bool set_add_rowmode(bool turnon)
        {
            return lpsolveInner.set_add_rowmode(m_lp, turnon);
        }
        public void set_anti_degen(lpsolve_anti_degen anti_degen)
        {
            lpsolveInner.set_anti_degen(m_lp, anti_degen);
        }
        public bool set_basis(int[] bascolumn, bool nonbasic)
        {
            return lpsolveInner.set_basis(m_lp, bascolumn, nonbasic);
        }
        public void set_basiscrash(lpsolve_basiscrash mode)
        {
            lpsolveInner.set_basiscrash(m_lp, mode);
        }
        public void set_basisvar(int basisPos, int enteringCol)
        {
            lpsolveInner.set_basisvar(m_lp, basisPos, enteringCol);
        }
        public void set_bb_depthlimit(int bb_maxlevel)
        {
            lpsolveInner.set_bb_depthlimit(m_lp, bb_maxlevel);
        }
        public void set_bb_floorfirst(lpsolve_branch bb_floorfirst)
        {
            lpsolveInner.set_bb_floorfirst(m_lp, bb_floorfirst);
        }
        public void set_bb_rule(lpsolve_BBstrategies bb_rule)
        {
            lpsolveInner.set_bb_rule(m_lp, bb_rule);
        }
        public bool set_BFP(string filename)
        {
            return lpsolveInner.set_BFP(m_lp, filename);
        }
        public bool set_binary(int column, bool must_be_bin)
        {
            return lpsolveInner.set_binary(m_lp, column, must_be_bin);
        }
        public bool set_bounds(int column, double lower, double upper)
        {
            return lpsolveInner.set_bounds(m_lp, column, lower, upper);
        }
        public void set_bounds_tighter(bool tighten)
        {
            lpsolveInner.set_bounds_tighter(m_lp, tighten);
        }
        public void set_break_at_first(bool break_at_first)
        {
            lpsolveInner.set_break_at_first(m_lp, break_at_first);
        }
        public void set_break_at_value(double break_at_value)
        {
            lpsolveInner.set_break_at_value(m_lp, break_at_value);
        }
        public bool set_col_name(int column, string new_name)
        {
            return lpsolveInner.set_col_name(m_lp, column, new_name);
        }
        public bool set_column(int col_no, double[] column)
        {
            return lpsolveInner.set_column(m_lp, col_no, column);
        }
        public bool set_columnex(int col_no, int count, double[] column, int[] rowno)
        {
            return lpsolveInner.set_columnex(m_lp, col_no, count, column, rowno);
        }
        public bool set_constr_type(int row, lpsolve_constr_types con_type)
        {
            return lpsolveInner.set_constr_type(m_lp, row, con_type);
        }
        public void set_debug(bool debug)
        {
            lpsolveInner.set_debug(m_lp, debug);
        }
        public void set_epsb(double epsb)
        {
            lpsolveInner.set_epsb(m_lp, epsb);
        }
        public void set_epsd(double epsd)
        {
            lpsolveInner.set_epsd(m_lp, epsd);
        }
        public void set_epsel(double epsel)
        {
            lpsolveInner.set_epsel(m_lp, epsel);
        }
        public void set_epsint(double epsint)
        {
            lpsolveInner.set_epsint(m_lp, epsint);
        }
        public bool set_epslevel(int level)
        {
            return lpsolveInner.set_epslevel(m_lp, level);
        }
        public void set_epsperturb(double epsperturb)
        {
            lpsolveInner.set_epsperturb(m_lp, epsperturb);
        }
        public void set_epspivot(double epspivot)
        {
            lpsolveInner.set_epspivot(m_lp, epspivot);
        }
        public void set_improve(lpsolve_improves improve)
        {
            lpsolveInner.set_improve(m_lp, improve);
        }
        public void set_infinite(double infinite)
        {
            lpsolveInner.set_infinite(m_lp, infinite);
        }
        public bool set_int(int column, bool must_be_int)
        {
            return lpsolveInner.set_int(m_lp, column, must_be_int);
        }
        public void set_lag_trace(bool lag_trace)
        {
            lpsolveInner.set_lag_trace(m_lp, lag_trace);
        }
        public bool set_lowbo(int column, double value)
        {
            return lpsolveInner.set_lowbo(m_lp, column, value);
        }
        public bool set_lp_name(string lpname)
        {
            return lpsolveInner.set_lp_name(m_lp, lpname);
        }
        public bool set_mat(int row, int column, double value)
        {
            return lpsolveInner.set_mat(m_lp, row, column, value);
        }
        public void set_maxim()
        {
            lpsolveInner.set_maxim(m_lp);
        }
        public void set_maxpivot(int max_num_inv)
        {
            lpsolveInner.set_maxpivot(m_lp, max_num_inv);
        }
        public void set_minim()
        {
            lpsolveInner.set_minim(m_lp);
        }
        public void set_mip_gap(bool absolute, double mip_gap)
        {
            lpsolveInner.set_mip_gap(m_lp, absolute, mip_gap);
        }
        public void set_negrange(double negrange)
        {
            lpsolveInner.set_negrange(m_lp, negrange);
        }
        public bool set_obj(int Column, double Value)
        {
            return lpsolveInner.set_obj(m_lp, Column, Value);
        }
        public void set_obj_bound(double obj_bound)
        {
            lpsolveInner.set_obj_bound(m_lp, obj_bound);
        }
        public bool set_obj_fn(double[] row)
        {
            return lpsolveInner.set_obj_fn(m_lp, row);
        }
        public bool set_obj_fnex(int count, double[] row, int[] colno)
        {
            return lpsolveInner.set_obj_fnex(m_lp, count, row, colno);
        }
        public bool set_outputfile(string filename)
        {
            return lpsolveInner.set_outputfile(m_lp, filename);
        }
        public void set_pivoting(lpsolve_piv_rules piv_rule)
        {
            lpsolveInner.set_pivoting(m_lp, piv_rule);
        }
        public void set_preferdual(bool dodual)
        {
            lpsolveInner.set_preferdual(m_lp, dodual);
        }
        public void set_presolve(lpsolve_presolve do_presolve, int maxloops)
        {
            lpsolveInner.set_presolve(m_lp, do_presolve, maxloops);
        }
        public void set_print_sol(int print_sol)
        {
            lpsolveInner.set_print_sol(m_lp, print_sol);
        }
        public bool set_PseudoCosts(double[] clower, double[] cupper, int[] updatelimit)
        {
            return lpsolveInner.set_PseudoCosts(m_lp, clower, cupper, updatelimit);
        }
        public bool set_rh(int row, double value)
        {
            return lpsolveInner.set_rh(m_lp, row, value);
        }
        public bool set_rh_range(int row, double deltavalue)
        {
            return lpsolveInner.set_rh_range(m_lp, row, deltavalue);
        }
        public void set_rh_vec(double[] rh)
        {
            lpsolveInner.set_rh_vec(m_lp, rh);
        }
        public bool set_row(int row_no, double[] row)
        {
            return lpsolveInner.set_row(m_lp, row_no, row);
        }
        public bool set_row_name(int row, string new_name)
        {
            return lpsolveInner.set_row_name(m_lp, row, new_name);
        }
        public bool set_rowex(int row_no, int count, double[] row, int[] colno)
        {
            return lpsolveInner.set_rowex(m_lp, row_no, count, row, colno);
        }
        public void set_scalelimit(double scalelimit)
        {
            lpsolveInner.set_scalelimit(m_lp, scalelimit);
        }
        public void set_scaling(lpsolve_scales scalemode)
        {
            lpsolveInner.set_scaling(m_lp, scalemode);
        }
        public bool set_semicont(int column, bool must_be_sc)
        {
            return lpsolveInner.set_semicont(m_lp, column, must_be_sc);
        }
        public void set_sense(bool maximize)
        {
            lpsolveInner.set_sense(m_lp, maximize);
        }
        public void set_simplextype(lpsolve_simplextypes simplextype)
        {
            lpsolveInner.set_simplextype(m_lp, simplextype);
        }
        public void set_solutionlimit(int limit)
        {
            lpsolveInner.set_solutionlimit(m_lp, limit);
        }
        public void set_timeout(int sectimeout)
        {
            lpsolveInner.set_timeout(m_lp, sectimeout);
        }
        public void set_trace(bool trace)
        {
            lpsolveInner.set_trace(m_lp, trace);
        }
        public bool set_unbounded(int column)
        {
            return lpsolveInner.set_unbounded(m_lp, column);
        }
        public bool set_upbo(int column, double value)
        {
            return lpsolveInner.set_upbo(m_lp, column, value);
        }
        public void set_use_names(bool isrow, bool use_names)
        {
            lpsolveInner.set_use_names(m_lp, isrow, use_names);
        }
        public bool set_var_branch(int column, lpsolve_branch branch_mode)
        {
            return lpsolveInner.set_var_branch(m_lp, column, branch_mode);
        }
        public bool set_var_weights(double[] weights)
        {
            return lpsolveInner.set_var_weights(m_lp, weights);
        }
        public void set_verbose(int verbose)
        {
            lpsolveInner.set_verbose(m_lp, verbose);
        }
        public bool set_XLI(string filename)
        {
            return lpsolveInner.set_XLI(m_lp, filename);
        }
        public lpsolve_return solve()
        {
            return lpsolveInner.solve(m_lp);
        }
        public bool str_add_column(string col_string)
        {
            return lpsolveInner.str_add_column(m_lp, col_string);
        }
        public bool str_add_constraint(string row_string, lpsolve_constr_types constr_type, double rh)
        {
            return lpsolveInner.str_add_constraint(m_lp, row_string, constr_type, rh);
        }
        public bool str_add_lag_con(string row_string, lpsolve_constr_types con_type, double rhs)
        {
            return lpsolveInner.str_add_lag_con(m_lp, row_string, con_type, rhs);
        }
        public bool str_set_obj_fn(string row_string)
        {
            return lpsolveInner.str_set_obj_fn(m_lp, row_string);
        }
        public bool str_set_rh_vec(string rh_string)
        {
            return lpsolveInner.str_set_rh_vec(m_lp, rh_string);
        }
        public double time_elapsed()
        {
            return lpsolveInner.time_elapsed(m_lp);
        }
        public void unscale()
        {
            lpsolveInner.unscale(m_lp);
        }
        public bool write_basis(string filename)
        {
            return lpsolveInner.write_basis(m_lp, filename);
        }
        public bool write_freemps(string filename)
        {
            return lpsolveInner.write_freemps(m_lp, filename);
        }
        public bool write_lp(string filename)
        {
            return lpsolveInner.write_lp(m_lp, filename);
        }
        public bool write_mps(string filename)
        {
            return lpsolveInner.write_mps(m_lp, filename);
        }
        public bool write_XLI(string filename, string options, bool results)
        {
            return lpsolveInner.write_XLI(m_lp, filename, options, results);
        }
        public bool write_params(string filename, string options)
        {
            return lpsolveInner.write_params(m_lp, filename, options);
        }
    }

    public static class lpsolveInner
    {
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool add_column(IntPtr lp, double[] column);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool add_columnex(IntPtr lp, int count, double[] column, int[] rowno);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool add_constraint(IntPtr lp, double[] row, lpsolve_constr_types constr_type, double rh);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool add_constraintex(IntPtr lp, int count, double[] row, int[] colno, lpsolve_constr_types constr_type, double rh);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool add_lag_con(IntPtr lp, double[] row, lpsolve_constr_types con_type, double rhs);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int add_SOS(IntPtr lp, string name, int sostype, int priority, int count, int[] sosvars, double[] weights);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int column_in_lp(IntPtr lp, double[] column);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern IntPtr copy_lp(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void default_basis(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool del_column(IntPtr lp, int column);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool del_constraint(IntPtr lp, int del_row);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void delete_lp(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool dualize_lp(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_anti_degen get_anti_degen(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool get_basis(IntPtr lp, int[] bascolumn, bool nonbasic);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_basiscrash get_basiscrash(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_bb_depthlimit(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_branch get_bb_floorfirst(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_BBstrategies get_bb_rule(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool get_bounds_tighter(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_break_at_value(IntPtr lp);
        //[DllImport("lpsolve55.dll", SetLastError=true)] public static extern string get_col_name(IntPtr lp, int column);
        [DllImport("lpsolve55.dll", EntryPoint = "get_col_name", SetLastError = true)]
        private static extern IntPtr get_col_name_c(IntPtr lp, int column);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool get_column(IntPtr lp, int col_nr, double[] column);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_columnex(IntPtr lp, int col_nr, double[] column, int[] nzrow);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_constr_types get_constr_type(IntPtr lp, int row);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_constr_value(IntPtr lp, int row, int count, double[] primsolution, int[] nzindex);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool get_constraints(IntPtr lp, double[] constr);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool get_dual_solution(IntPtr lp, double[] rc);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_epsb(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_epsd(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_epsel(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_epsint(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_epsperturb(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_epspivot(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_improves get_improve(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_infinite(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool get_lambda(IntPtr lp, double[] lambda);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_lowbo(IntPtr lp, int column);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_lp_index(IntPtr lp, int orig_index);
        //[DllImport("lpsolve55.dll", SetLastError=true)] public static extern string get_lp_name(IntPtr lp);
        [DllImport("lpsolve55.dll", EntryPoint = "get_lp_name", SetLastError = true)]
        private static extern IntPtr get_lp_name_c(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_Lrows(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_mat(IntPtr lp, int row, int column);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_max_level(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_maxpivot(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_mip_gap(IntPtr lp, bool absolute);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_Ncolumns(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_negrange(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_nameindex(IntPtr lp, string name, bool isrow);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_nonzeros(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_Norig_columns(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_Norig_rows(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_Nrows(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_obj_bound(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_objective(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_orig_index(IntPtr lp, IntPtr lp_index);
        //[DllImport("lpsolve55.dll", SetLastError=true)] public static extern string get_origcol_name(IntPtr lp, int column);
        [DllImport("lpsolve55.dll", EntryPoint = "get_origcol_name", SetLastError = true)]
        private static extern IntPtr get_origcol_name_c(IntPtr lp, int column);
        //[DllImport("lpsolve55.dll", SetLastError=true)] public static extern string get_origrow_name(IntPtr lp, int row);
        [DllImport("lpsolve55.dll", EntryPoint = "get_origrow_name", SetLastError = true)]
        private static extern IntPtr get_origrow_name_c(IntPtr lp, int row);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_piv_rules get_pivoting(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_presolve get_presolve(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_presolveloops(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool get_primal_solution(IntPtr lp, double[] pv);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_print_sol(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool get_PseudoCosts(IntPtr lp, double[] clower, double[] cupper, int[] updatelimit);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_rh(IntPtr lp, int row);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_rh_range(IntPtr lp, int row);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool get_row(IntPtr lp, int row_nr, double[] row);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_rowex(IntPtr lp, int row_nr, double[] row, int[] colno);
        //[DllImport("lpsolve55.dll", SetLastError=true)] public static extern string get_row_name(IntPtr lp, int row);
        [DllImport("lpsolve55.dll", EntryPoint = "get_row_name", SetLastError = true)]
        private static extern IntPtr get_row_name_c(IntPtr lp, int row);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_scalelimit(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_scales get_scaling(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool get_sensitivity_obj(IntPtr lp, double[] objfrom, double[] objtill);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool get_sensitivity_objex(IntPtr lp, double[] objfrom, double[] objtill, double[] objfromvalue, double[] objtillvalue);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool get_sensitivity_rhs(IntPtr lp, double[] duals, double[] dualsfrom, double[] dualstill);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_simplextypes get_simplextype(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_solutioncount(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_solutionlimit(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_status(IntPtr lp);
        //[DllImport("lpsolve55.dll", SetLastError=true)] public static extern string get_statustext(IntPtr lp, int statuscode);
        [DllImport("lpsolve55.dll", EntryPoint = "get_statustext", SetLastError = true)]
        private static extern IntPtr get_statustext_c(IntPtr lp, int statuscode);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_timeout(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern long get_total_iter(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern long get_total_nodes(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_upbo(IntPtr lp, int column);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_branch get_var_branch(IntPtr lp, int column);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_var_dualresult(IntPtr lp, int index);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_var_primalresult(IntPtr lp, int index);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_var_priority(IntPtr lp, int column);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool get_variables(IntPtr lp, double[] var);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_verbose(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_working_objective(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool guess_basis(IntPtr lp, double[] guessvector, int[] basisvector);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool has_BFP(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool has_XLI(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_add_rowmode(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_anti_degen(IntPtr lp, lpsolve_anti_degen testmask);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_binary(IntPtr lp, int column);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_break_at_first(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_constr_type(IntPtr lp, int row, int mask);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_debug(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_feasible(IntPtr lp, double[] values, double threshold);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_infinite(IntPtr lp, double value);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_int(IntPtr lp, int column);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_integerscaling(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_lag_trace(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_maxim(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_nativeBFP(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_nativeXLI(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_negative(IntPtr lp, int column);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_piv_mode(IntPtr lp, lpsolve_piv_rules testmask);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_piv_rule(IntPtr lp, lpsolve_piv_rules rule);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_presolve(IntPtr lp, lpsolve_presolve testmask);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_scalemode(IntPtr lp, lpsolve_scales testmask);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_scaletype(IntPtr lp, lpsolve_scales scaletype);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_semicont(IntPtr lp, int column);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_SOS_var(IntPtr lp, int column);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_trace(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_unbounded(IntPtr lp, int column);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool is_use_names(IntPtr lp, bool isrow);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void lp_solve_version(ref int majorversion, ref int minorversion, ref int release, ref int build);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern IntPtr make_lp(int rows, int columns);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern IntPtr resize_lp(IntPtr lp, int rows, int columns);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void print_constraints(IntPtr lp, int columns);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool print_debugdump(IntPtr lp, string filename);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void print_duals(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void print_lp(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void print_objective(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void print_scales(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void print_solution(IntPtr lp, int columns);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void print_str(IntPtr lp, string str);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void print_tableau(IntPtr lp);
        //public  delegate bool ctrlcfunc( IntPtr lp,  int userhandle);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void put_abortfunc(IntPtr lp, ctrlcfunc newctrlc, int ctrlchandle);
        //public  delegate void logfunc( IntPtr lp,  int userhandle, string buf);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void put_logfunc(IntPtr lp, logfunc newlog, int loghandle);
        //public  delegate void msgfunc( IntPtr lp,  int userhandle, lpsolve_msgmask message);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void put_msgfunc(IntPtr lp, msgfunc newmsg, int msghandle, int mask);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool read_basis(IntPtr lp, string filename, string info);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int read_freeMPS(string filename, int options);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int read_LP(string filename, int verbose, string lp_name);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int read_MPS(string filename, int options);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int read_XLI(string xliname, string modelname, string dataname, string options, int verbose);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool read_params(IntPtr lp, string filename, string options);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void reset_basis(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void reset_params(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_add_rowmode(IntPtr lp, bool turnon);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_anti_degen(IntPtr lp, lpsolve_anti_degen anti_degen);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_basis(IntPtr lp, int[] bascolumn, bool nonbasic);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_basiscrash(IntPtr lp, lpsolve_basiscrash mode);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_basisvar(IntPtr lp, int basisPos, int enteringCol);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_bb_depthlimit(IntPtr lp, int bb_maxlevel);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_bb_floorfirst(IntPtr lp, lpsolve_branch bb_floorfirst);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_bb_rule(IntPtr lp, lpsolve_BBstrategies bb_rule);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_BFP(IntPtr lp, string filename);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_binary(IntPtr lp, int column, bool must_be_bin);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_bounds(IntPtr lp, int column, double lower, double upper);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_bounds_tighter(IntPtr lp, bool tighten);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_break_at_first(IntPtr lp, bool break_at_first);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_break_at_value(IntPtr lp, double break_at_value);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_col_name(IntPtr lp, int column, string new_name);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_column(IntPtr lp, int col_no, double[] column);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_columnex(IntPtr lp, int col_no, int count, double[] column, int[] rowno);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_constr_type(IntPtr lp, int row, lpsolve_constr_types con_type);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_debug(IntPtr lp, bool debug);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_epsb(IntPtr lp, double epsb);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_epsd(IntPtr lp, double epsd);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_epsel(IntPtr lp, double epsel);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_epsint(IntPtr lp, double epsint);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_epslevel(IntPtr lp, int level);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_epsperturb(IntPtr lp, double epsperturb);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_epspivot(IntPtr lp, double epspivot);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_improve(IntPtr lp, lpsolve_improves improve);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_infinite(IntPtr lp, double infinite);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_int(IntPtr lp, int column, bool must_be_int);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_lag_trace(IntPtr lp, bool lag_trace);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_lowbo(IntPtr lp, int column, double value);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_lp_name(IntPtr lp, string lpname);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_mat(IntPtr lp, int row, int column, double value);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_maxim(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_maxpivot(IntPtr lp, int max_num_inv);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_minim(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_mip_gap(IntPtr lp, bool absolute, double mip_gap);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_negrange(IntPtr lp, double negrange);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_obj(IntPtr lp, int Column, double Value);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_obj_bound(IntPtr lp, double obj_bound);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_obj_fn(IntPtr lp, double[] row);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_obj_fnex(IntPtr lp, int count, double[] row, int[] colno);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_outputfile(IntPtr lp, string filename);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_pivoting(IntPtr lp, lpsolve_piv_rules piv_rule);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_preferdual(IntPtr lp, bool dodual);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_presolve(IntPtr lp, lpsolve_presolve do_presolve, int maxloops);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_print_sol(IntPtr lp, int print_sol);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_PseudoCosts(IntPtr lp, double[] clower, double[] cupper, int[] updatelimit);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_rh(IntPtr lp, int row, double value);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_rh_range(IntPtr lp, int row, double deltavalue);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_rh_vec(IntPtr lp, double[] rh);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_row(IntPtr lp, int row_no, double[] row);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_row_name(IntPtr lp, int row, string new_name);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_rowex(IntPtr lp, int row_no, int count, double[] row, int[] colno);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_scalelimit(IntPtr lp, double scalelimit);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_scaling(IntPtr lp, lpsolve_scales scalemode);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_semicont(IntPtr lp, int column, bool must_be_sc);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_sense(IntPtr lp, bool maximize);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_simplextype(IntPtr lp, lpsolve_simplextypes simplextype);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_solutionlimit(IntPtr lp, int limit);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_timeout(IntPtr lp, int sectimeout);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_trace(IntPtr lp, bool trace);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_unbounded(IntPtr lp, int column);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_upbo(IntPtr lp, int column, double value);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_use_names(IntPtr lp, bool isrow, bool use_names);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_var_branch(IntPtr lp, int column, lpsolve_branch branch_mode);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_var_weights(IntPtr lp, double[] weights);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_verbose(IntPtr lp, int verbose);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool set_XLI(IntPtr lp, string filename);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_return solve(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool str_add_column(IntPtr lp, string col_string);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool str_add_constraint(IntPtr lp, string row_string, lpsolve_constr_types constr_type, double rh);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool str_add_lag_con(IntPtr lp, string row_string, lpsolve_constr_types con_type, double rhs);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool str_set_obj_fn(IntPtr lp, string row_string);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool str_set_rh_vec(IntPtr lp, string rh_string);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double time_elapsed(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void unscale(IntPtr lp);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool write_basis(IntPtr lp, string filename);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool write_freemps(IntPtr lp, string filename);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool write_lp(IntPtr lp, string filename);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool write_mps(IntPtr lp, string filename);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool write_XLI(IntPtr lp, string filename, string options, bool results);
        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern bool write_params(IntPtr lp, string filename, string options);

        public static string get_col_name(IntPtr lp, int column)
        {
            return (Marshal.PtrToStringAnsi(get_col_name_c(lp, column)));
        }

        public static string get_lp_name(IntPtr lp)
        {
            return (Marshal.PtrToStringAnsi(get_lp_name_c(lp)));
        }

        public static string get_origcol_name(IntPtr lp, int column)
        {
            return (Marshal.PtrToStringAnsi(get_origcol_name_c(lp, column)));
        }

        public static string get_origrow_name(IntPtr lp, int row)
        {
            return (Marshal.PtrToStringAnsi(get_origrow_name_c(lp, row)));
        }

        public static string get_row_name(IntPtr lp, int row)
        {
            return (Marshal.PtrToStringAnsi(get_row_name_c(lp, row)));
        }

        public static string get_statustext(IntPtr lp, int statuscode)
        {
            return (Marshal.PtrToStringAnsi(get_statustext_c(lp, statuscode)));
        }

        [DllImport("kernel32", SetLastError = true)]
        private static extern int SetEnvironmentVariableA(string lpName, string lpValue);
        [DllImport("kernel32", SetLastError = true)]
        private static extern int GetEnvironmentVariableA(string lpName, string lpBuffer, int nSize);

        private static bool SetEnvironmentVariable(string Name, string val)
        {
            return SetEnvironmentVariableA(Name, val) == 0 ? false : true;
        }

        private static string GetEnvironmentVariable(string Name)
        {
            return System.Environment.GetEnvironmentVariable(Name);
        }


        public static bool Init()
        {
            return Init("");
        }


        static bool bEnvChanged = false;

        public static bool Init(string dllPath)
        {
            string Path;
            string Buf;
            bool returnValue;

            if (dllPath.Length == 0)
            {
                dllPath = System.Environment.CurrentDirectory;
            }
            Buf = dllPath;
            if (Buf.Substring(Buf.Length - 1, 1) != "\\")
            {
                Buf += "\\";
            }
            Buf += "lpsolve55.dll";

            returnValue = System.IO.File.Exists(Buf);
            if (returnValue)
            {
                if (!bEnvChanged)
                {
                    bEnvChanged = true;
                    Path = GetEnvironmentVariable("PATH");
                    string PathS = Path.ToLower() + ";";
                    PathS.ToLower();
                    if (PathS.IndexOf(dllPath.ToLower() + ";") < 0)
                    {
                        SetEnvironmentVariable("PATH", dllPath + ";" + Path);
                    }
                }
            }
            return returnValue;
        } //Init
    }
}
