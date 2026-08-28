using System;
using System.Runtime.InteropServices;
using System.Globalization;

namespace LpSolveNativeInterface
{
    public class lpsolve
    {
        internal lpsolve()
        {
        }

        public enum lpsolve_constr_types
        {
            LE = 1,
            EQ = 3,
            GE = 2,
            FR = 0,
        }
        [Flags]
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

        [Flags]
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

        [Flags]
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

        [Flags]
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

        [Flags]
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

        [Flags]
        public enum lpsolve_basiscrash
        {
            CRASH_NOTHING = 0,
            CRASH_MOSTFEASIBLE = 2,
        }

        [Flags]
        public enum lpsolve_simplextypes
        {
            SIMPLEX_PRIMAL_PRIMAL = 5,
            SIMPLEX_DUAL_PRIMAL = 6,
            SIMPLEX_PRIMAL_DUAL = 9,
            SIMPLEX_DUAL_DUAL = 10,
        }

        [Flags]
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
        }

        [Flags]
        public enum lpsolve_branch
        {
            BRANCH_CEILING = 0,
            BRANCH_FLOOR = 1,
            BRANCH_AUTOMATIC = 2,
        }

        [Flags]
        public enum lpsolve_msgmask
        {
            MSG_PRESOLVE = 1,
            MSG_LPFEASIBLE = 8,
            MSG_LPOPTIMAL = 16,
            MSG_MILPEQUAL = 32,
            MSG_MILPFEASIBLE = 128,
            MSG_MILPBETTER = 512,
        }

        #region Used

        public static bool Init()
        {
            return Init("");
        }

        static bool bEnvChanged = false;

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern int make_lp(int rows, int columns);

        [DllImport("lpsolve55.dll", SetLastError = true, CharSet = CharSet.Unicode)]
        internal static extern byte set_col_name(int lp, int column, string new_name);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern byte set_int(int lp, int column, byte must_be_int);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern byte set_bounds(int lp, int column, double lower, double upper);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern byte set_lowbo(int lp, int column, double value);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern byte set_upbo(int lp, int column, double value);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern byte set_unbounded(int lp, int column);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern byte add_constraint(int lp, double[] row, lpsolve_constr_types constr_type, double rh);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern byte set_rh_range(int lp, int row, double deltavalue);

        [DllImport("lpsolve55.dll", SetLastError = true, CharSet = CharSet.Unicode)]
        internal static extern byte set_row_name(int lp, int row, string new_name);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern void set_minim(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern void set_maxim(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern void set_sense(int lp, byte maximize);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern byte set_obj_fn(int lp, double[] row);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern int add_SOS(int lp, string name, int sostype, int priority, int count, int[] sosvars, double[] weights);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern byte set_obj_fnex(int lp, int count, double[] row, int[] colno);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern int get_Norig_rows(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern int get_Norig_columns(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern int get_Nrows(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern byte get_primal_solution(int lp, double[] pv);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern double get_objective(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_obj_bound(int lp);

        internal delegate int ctrlcfunc(int lp, int userhandle);

        public static bool Init(string dllPath)
        {
            string Path;
            string Buf;
            bool returnValue;

            if (!string.IsNullOrEmpty(dllPath))
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
                    string PathS = Path.ToLower(CultureInfo.CurrentCulture) + ";";
                    PathS = PathS.ToLower(CultureInfo.CurrentCulture);
                    if (PathS.IndexOf(dllPath.ToLower(CultureInfo.CurrentCulture) + ";") < 0)
                    {
                        SetEnvironmentVariable("PATH", dllPath + ";" + Path);
                    }
                }
            }
            return returnValue;
        } //Init

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern void set_simplextype(int lp, lpsolve_simplextypes simplextype);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern void set_pivoting(int lp, lpsolve_piv_rules piv_rule);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern void set_presolve(int lp, lpsolve_presolve do_presolve, int maxloops);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern void set_bb_floorfirst(int lp, lpsolve_branch bb_floorfirst);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern void set_bb_rule(int lp, lpsolve_BBstrategies bb_rule);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern void set_add_rowmode(int lp, byte turnon);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern void set_obj_in_basis(int lp, byte obj_in_basis);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern void set_anti_degen(int lp, lpsolve_anti_degen anti_degen);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern void set_mip_gap(int lp, byte absolute, double mip_gap);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern byte set_outputfile(int lp, string filename);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern void put_abortfunc(int lp, ctrlcfunc newctrlc, int ctrlchandle);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern lpsolve_return solve(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern int get_status(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern lpsolve_simplextypes get_simplextype(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern int get_solutioncount(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern int get_Ncolumns(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern byte is_int(int lp, int column);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern int get_maxpivot(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern long get_total_nodes(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern double get_mip_gap(int lp, byte absolute);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern void delete_lp(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        internal static extern int get_presolveloops(int lp);

        [DllImport("kernel32", SetLastError = true, CharSet = CharSet.Unicode)]
        private static extern int SetEnvironmentVariableA(string lpName, string lpValue);

        [DllImport("kernel32", SetLastError = true, CharSet = CharSet.Unicode)]
        private static extern int GetEnvironmentVariableA(string lpName, string lpBuffer, int nSize);

        private static bool SetEnvironmentVariable(string Name, string val)
        {
            return SetEnvironmentVariableA(Name, val) == 0 ? false : true;
        }

        private static string GetEnvironmentVariable(string Name)
        {
            return System.Environment.GetEnvironmentVariable(Name);
        }

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern long get_total_iter(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void print_objective(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void print_solution(int lp, int columns);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void print_constraints(int lp, int columns);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void print_lp(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte print_debugdump(int lp, string filename);

        public delegate void logfunc(int lp, int userhandle, string buf);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void put_logfunc(int lp, logfunc newlog, int loghandle);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double time_elapsed(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_trace(int lp, byte trace);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_working_objective(int lp);

        public delegate void msgfunc(int lp, int userhandle, lpsolve_msgmask message);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void put_msgfunc(int lp, msgfunc newmsg, int msghandle, int mask);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_verbose(int lp, int verbose);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern  byte write_lp(int lp, string filename);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_var_primalresult(int lp, int index);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_var_dualresult(int lp, int index);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte get_sensitivity_obj(int lp, double[] objfrom, double[] objtill);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        unsafe public static extern byte get_ptr_sensitivity_obj(int lp, ref double* objfrom, ref double* objtill);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        unsafe public static extern byte get_ptr_sensitivity_objex(int lp, ref double* objfrom, ref double* objtill, ref double* objfromvalue, ref double* objtillvalue);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte get_sensitivity_rhs(int lp, double[] duals, double[] dualsfrom, double[] dualstill);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        unsafe public static extern byte get_ptr_sensitivity_rhs(int lp, ref double* duals, ref double* dualsfrom, ref double* dualstill);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_mat(int lp, int row, int column);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_rh(int lp, int row);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_rh_range(int lp, int row);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_constr_types get_constr_type(int lp, int row);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_infinite(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_maxim(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_timeout(int lp, long sectimeout);


        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte add_column(int lp, double[] column);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte add_columnex(int lp, int count, double[] column, int[] rowno);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte add_constraintex(int lp, int count, double[] row, int[] colno, lpsolve_constr_types constr_type, double rh);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte add_lag_con(int lp, double[] row, lpsolve_constr_types con_type, double rhs);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int column_in_lp(int lp, double[] column);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int copy_lp(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void default_basis(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte del_column(int lp, int column);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte del_constraint(int lp, int del_row);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte dualize_lp(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_anti_degen get_anti_degen(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte get_basis(int lp, int[] bascolumn, byte nonbasic);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_basiscrash get_basiscrash(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_bb_depthlimit(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_branch get_bb_floorfirst(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_BBstrategies get_bb_rule(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte get_bounds_tighter(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_break_at_value(int lp);

        //[DllImport("lpsolve55.dll", SetLastError=true)] public static extern string get_col_name(int lp, int column);

        [DllImport("lpsolve55.dll", EntryPoint = "get_col_name", SetLastError = true)]
        private unsafe static extern IntPtr get_col_name_c(int lp, int column);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte get_column(int lp, int col_nr, double[] column);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_columnex(int lp, int col_nr, double[] column, int[] nzrow);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_constr_value(int lp, int row, int count, double[] primsolution, int[] nzindex);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte get_constraints(int lp, double[] constr);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        unsafe public static extern byte get_ptr_constraints(int lp, ref double* constr);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte get_dual_solution(int lp, double[] rc);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_epsb(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_epsd(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_epsel(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_epsint(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_epsperturb(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_epspivot(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_improves get_improve(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte get_lambda(int lp, double[] lambda);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_lowbo(int lp, int column);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_lp_index(int lp, int orig_index);

        //[DllImport("lpsolve55.dll", SetLastError=true)] public static extern string get_lp_name(int lp);

        [DllImport("lpsolve55.dll", EntryPoint = "get_lp_name", SetLastError = true)]
        private unsafe static extern IntPtr get_lp_name_c(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_Lrows(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_max_level(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_negrange(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true, CharSet = CharSet.Unicode)]
        public static extern int get_nameindex(int lp, string name, byte isrow);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_nonzeros(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_orig_index(int lp, int lp_index);

        //[DllImport("lpsolve55.dll", SetLastError=true)] public static extern string get_origcol_name(int lp, int column);

        [DllImport("lpsolve55.dll", EntryPoint = "get_origcol_name", SetLastError = true)]
        private unsafe static extern IntPtr get_origcol_name_c(int lp, int column);

        //[DllImport("lpsolve55.dll", SetLastError=true)] public static extern string get_origrow_name(int lp, int row);

        [DllImport("lpsolve55.dll", EntryPoint = "get_origrow_name", SetLastError = true)]
        private unsafe static extern IntPtr get_origrow_name_c(int lp, int row);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_piv_rules get_pivoting(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_presolve get_presolve(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_print_sol(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte get_PseudoCosts(int lp, double[] clower, double[] cupper, int[] updatelimit);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte get_row(int lp, int row_nr, double[] row);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_rowex(int lp, int row_nr, double[] row, int[] colno);

        //[DllImport("lpsolve55.dll", SetLastError=true)] public static extern string get_row_name(int lp, int row);

        [DllImport("lpsolve55.dll", EntryPoint = "get_row_name", SetLastError = true)]
        private unsafe static extern IntPtr get_row_name_c(int lp, int row);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_scalelimit(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_scales get_scaling(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte get_sensitivity_objex(int lp, double[] objfrom, double[] objtill, double[] objfromvalue, double[] objtillvalue);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_solutionlimit(int lp);

        //[DllImport("lpsolve55.dll", SetLastError=true)] public static extern string get_statustext(int lp, int statuscode);

        [DllImport("lpsolve55.dll", EntryPoint = "get_statustext", SetLastError = true)]
        private unsafe static extern IntPtr get_statustext_c(int lp, int statuscode);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern long get_timeout(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern double get_upbo(int lp, int column);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern lpsolve_branch get_var_branch(int lp, int column);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_var_priority(int lp, int column);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte get_variables(int lp, double[] var);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int get_verbose(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte guess_basis(int lp, double[] guessvector, int[] basisvector);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte has_BFP(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte has_XLI(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_add_rowmode(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_anti_degen(int lp, lpsolve_scales testmask);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_binary(int lp, int column);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_break_at_first(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_constr_type(int lp, int row, int mask);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_debug(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_feasible(int lp, double[] values, double threshold);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_infinite(int lp, double value);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_integerscaling(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_lag_trace(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_nativeBFP(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_nativeXLI(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_negative(int lp, int column);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_obj_in_basis(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_piv_mode(int lp, lpsolve_scales testmask);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_piv_rule(int lp, lpsolve_piv_rules rule);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_presolve(int lp, lpsolve_scales testmask);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_scalemode(int lp, lpsolve_scales testmask);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_scaletype(int lp, lpsolve_scales scaletype);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_semicont(int lp, int column);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_SOS_var(int lp, int column);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_trace(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_unbounded(int lp, int column);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte is_use_names(int lp, byte isrow);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void lp_solve_version(ref int majorversion, ref int minorversion, ref int release, ref int build);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int resize_lp(int lp, int rows, int columns);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void print_duals(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void print_scales(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true, CharSet = CharSet.Unicode)]
        public static extern void print_str(int lp, string str);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void print_tableau(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte read_basis(int lp, string filename, string info);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int read_freeMPS(string filename, int verbose);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int read_LP(string filename, int verbose, string lp_name);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int read_MPS(string filename, int verbose);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern int read_XLI(string xliname, string modelname, string dataname, string options, int verbose);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte read_params(int lp, string filename, string options);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void reset_basis(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void reset_params(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte set_basis(int lp, int[] bascolumn, byte nonbasic);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_basiscrash(int lp, lpsolve_basiscrash mode);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_basisvar(int lp, int basisPos, int enteringCol);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_bb_depthlimit(int lp, int bb_maxlevel);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte set_BFP(int lp, string filename);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte set_binary(int lp, int column, byte must_be_bin);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_bounds_tighter(int lp, byte tighten);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_break_at_first(int lp, byte break_at_first);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_break_at_value(int lp, double break_at_value);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte set_column(int lp, int col_no, double[] column);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte set_columnex(int lp, int col_no, int count, double[] column, int[] rowno);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte set_constr_type(int lp, int row, lpsolve_constr_types con_type);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_debug(int lp, byte debug);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_epsb(int lp, double epsb);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_epsd(int lp, double epsd);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_epsel(int lp, double epsel);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_epsint(int lp, double epsint);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte set_epslevel(int lp, int level);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_epsperturb(int lp, double epsperturb);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_epspivot(int lp, double epspivot);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_improve(int lp, lpsolve_improves improve);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_infinite(int lp, double infinite);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_lag_trace(int lp, byte lag_trace);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte set_lp_name(int lp, string lpname);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte set_mat(int lp, int row, int column, double value);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_maxpivot(int lp, int max_num_inv);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_negrange(int lp, double negrange);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte set_obj(int lp, int Column, double Value);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_obj_bound(int lp, double obj_bound);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_preferdual(int lp, byte dodual);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_print_sol(int lp, int print_sol);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte set_PseudoCosts(int lp, double[] clower, double[] cupper, int[] updatelimit);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte set_rh(int lp, int row, double value);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_rh_vec(int lp, double[] rh);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte set_row(int lp, int row_no, double[] row);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte set_rowex(int lp, int row_no, int count, double[] row, int[] colno);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_scalelimit(int lp, double scalelimit);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_scaling(int lp, lpsolve_scales scalemode);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte set_semicont(int lp, int column, byte must_be_sc);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_solutionlimit(int lp, int limit);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void set_use_names(int lp, byte isrow, byte use_names);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte set_var_branch(int lp, int column, lpsolve_branch branch_mode);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte set_var_weights(int lp, double[] weights);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte set_XLI(int lp, string filename);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte str_add_column(int lp, string col_string);

        [DllImport("lpsolve55.dll", SetLastError = true, CharSet = CharSet.Unicode)]
        public static extern byte str_add_constraint(int lp, string row_string, lpsolve_constr_types constr_type, double rh);

        [DllImport("lpsolve55.dll", SetLastError = true, CharSet = CharSet.Unicode)]
        public static extern byte str_add_lag_con(int lp, string row_string, lpsolve_constr_types con_type, double rhs);

        [DllImport("lpsolve55.dll", SetLastError = true, CharSet = CharSet.Unicode)]
        public static extern byte str_set_obj_fn(int lp, string row_string);

        [DllImport("lpsolve55.dll", SetLastError = true, CharSet = CharSet.Unicode)]
        public static extern byte str_set_rh_vec(int lp, string rh_string);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern void unscale(int lp);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte write_basis(int lp, string filename);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte write_freemps(int lp, string filename);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte write_mps(int lp, string filename);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte write_XLI(int lp, string filename, string options, byte results);

        [DllImport("lpsolve55.dll", SetLastError = true)]
        public static extern byte write_params(int lp, string filename, string options);

        public static string get_col_name(int lp, int column)
        {
            return (Marshal.PtrToStringAnsi(get_col_name_c(lp, column)));
        }

        public string get_lp_name(int lp)
        {
            return (Marshal.PtrToStringAnsi(get_lp_name_c(lp)));
        }

        public string get_origcol_name(int lp, int column)
        {
            return (Marshal.PtrToStringAnsi(get_origcol_name_c(lp, column)));
        }

        public string get_origrow_name(int lp, int row)
        {
            return (Marshal.PtrToStringAnsi(get_origrow_name_c(lp, row)));
        }

        public string get_row_name(int lp, int row)
        {
            return (Marshal.PtrToStringAnsi(get_row_name_c(lp, row)));
        }

        public string get_statustext(int lp, int statuscode)
        {
            return (Marshal.PtrToStringAnsi(get_statustext_c(lp, statuscode)));
        }
#endregion
    }
}

