//
// Copyright © Microsoft Corporation.  All Rights Reserved.
// This code released under the terms of the 
// Microsoft Public License (MS-PL, http://opensource.org/licenses/ms-pl.html.)
//
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.SolverFoundation.Services;
using LpSolveNativeInterface;

namespace SolverFoundation.Plugin.LpSolve
{
    public class LpSolveDirective : Directive
    {

        public lpsolve.lpsolve_anti_degen LpSolveAntiDegen { get; set; }
        public lpsolve.lpsolve_basiscrash LpSolveBasiscrash { get; set; }
        public int LpSolveBbDepthlimit { get; set; }
        public lpsolve.lpsolve_branch LpSolveBbFloorfirst { get; set; }
        public lpsolve.lpsolve_BBstrategies LpSolveBbRule { get; set; }
        public bool LpSolveBreakAtFirst { get; set; }
        public double LpSolveBreakAtValue { get; set; }
        public bool LpSolveDebug { get; set; }
        public double LpSolveEpsb { get; set; }
        public double LpSolveEpsd { get; set; }
        public double LpSolveEpsel { get; set; }
        public double LpSolveEpsint { get; set; }
        public double LpSolveEpsperturb { get; set; }
        public double LpSolveEpspivot { get; set; }
        public lpsolve.lpsolve_improves LpSolveImprove { get; set; }
        public double LpSolveInfinite { get; set; }
        public int LpSolveMaxpivot { get; set; }
        public double LpSolveMipGapAbs { get; set; }
        public double LpSolveMipGapRel { get; set; }
        public double LpSolveNegrange { get; set; }
        public double LpSolveObjBound { get; set; }
        public bool LpSolveObjInBasis { get; set; }
        public lpsolve.lpsolve_piv_rules LpSolvePivoting { get; set; }
        public lpsolve.lpsolve_presolve LpSolvePresolve { get; set; }
        public double LpSolveScalelimit { get; set; }
        public lpsolve.lpsolve_scales LpSolveScaling { get; set; }
        public lpsolve.lpsolve_simplextypes LpSolveSimplextype { get; set; }
        public int LpSolveSolutionlimit { get; set; }
        public bool LpSolveTrace { get; set; }

        public string LpSolveLogFile { get; set; }
        public bool GetSensitivity { get; set; }

        public LpSolveDirective()
            : base()
        {
#if true
            int lp = lpsolve.make_lp(0, 0);

            LpSolveAntiDegen = lpsolve.get_anti_degen(lp);
            LpSolveBasiscrash = lpsolve.get_basiscrash(lp);
            LpSolveBbDepthlimit = lpsolve.get_bb_depthlimit(lp);
            LpSolveBbFloorfirst = lpsolve.get_bb_floorfirst(lp);
            LpSolveBbRule = lpsolve.get_bb_rule(lp);
            LpSolveBreakAtFirst = lpsolve.is_break_at_first(lp) != 0; 
            LpSolveBreakAtValue = lpsolve.get_break_at_value(lp);
            LpSolveDebug = lpsolve.is_debug(lp) != 0;
            LpSolveEpsb = lpsolve.get_epsb(lp);
            LpSolveEpsd = lpsolve.get_epsd(lp);
            LpSolveEpsel = lpsolve.get_epsel(lp);
            LpSolveEpsint = lpsolve.get_epsint(lp);
            LpSolveEpsperturb = lpsolve.get_epsperturb(lp);
            LpSolveEpspivot = lpsolve.get_epspivot(lp);
            LpSolveImprove = lpsolve.get_improve(lp);
            LpSolveInfinite = lpsolve.get_infinite(lp);
            LpSolveMaxpivot = lpsolve.get_maxpivot(lp);
            LpSolveMipGapAbs = lpsolve.get_mip_gap(lp, 1);
            LpSolveMipGapRel = lpsolve.get_mip_gap(lp, 0);
            LpSolveNegrange = lpsolve.get_negrange(lp);
            LpSolveObjBound = lpsolve.get_obj_bound(lp);
            LpSolveObjInBasis = lpsolve.is_obj_in_basis(lp) != 0;
            LpSolvePivoting = lpsolve.get_pivoting(lp);
            LpSolvePresolve = lpsolve.get_presolve(lp);
            LpSolveScalelimit = lpsolve.get_scalelimit(lp);
            LpSolveScaling = lpsolve.get_scaling(lp);
            LpSolveSimplextype = lpsolve.get_simplextype(lp);
            LpSolveSolutionlimit = lpsolve.get_solutionlimit(lp);
            TimeLimit = lpsolve.get_timeout(lp) * 1000;
            LpSolveTrace = lpsolve.is_trace(lp) != 0;

            lpsolve.delete_lp(lp);

#elif true
            LpSolveSimplextype = lpsolve.lpsolve_simplextypes.SIMPLEX_DUAL_PRIMAL;
            LpSolvePivoting = lpsolve.lpsolve_piv_rules.PRICER_DEVEX |
                             lpsolve.lpsolve_piv_rules.PRICE_ADAPTIVE;
            LpSolveAntiDegen = lpsolve.lpsolve_anti_degen.ANTIDEGEN_INFEASIBLE |
                               lpsolve.lpsolve_anti_degen.ANTIDEGEN_STALLING |
                               lpsolve.lpsolve_anti_degen.ANTIDEGEN_FIXEDVARS;
            LpSolveBbRule = lpsolve.lpsolve_BBstrategies.NODE_DYNAMICMODE |
                                 lpsolve.lpsolve_BBstrategies.NODE_GREEDYMODE |
                                 lpsolve.lpsolve_BBstrategies.NODE_PSEUDONONINTSELECT |
                                 lpsolve.lpsolve_BBstrategies.NODE_RCOSTFIXING;
            LpSolvePresolve = lpsolve.lpsolve_presolve.PRESOLVE_NONE /* lpsolve.lpsolve_presolve.PRESOLVE_COLS | lpsolve.lpsolve_presolve.PRESOLVE_ROWS | lpsolve.lpsolve_presolve.PRESOLVE_LINDEP */;
            LpSolveBbFloorfirst = lpsolve.lpsolve_branch.BRANCH_AUTOMATIC;

            LpSolveMipGapAbs = 1e-11;
            LpSolveMipGapRel = 1e-11;

#else
            LpSolveSimplextype = lpsolve.lpsolve_simplextypes.SIMPLEX_PRIMAL_PRIMAL;
            LpSolvePivoting = lpsolve.lpsolve_piv_rules.PRICER_STEEPESTEDGE;
            LpSolveAntiDegen = lpsolve.lpsolve_anti_degen.ANTIDEGEN_RHSPERTURB;
            LpSolveBbRule = lpsolve.lpsolve_BBstrategies.NODE_DYNAMICMODE |
                                    lpsolve.lpsolve_BBstrategies.NODE_GREEDYMODE |
                                    lpsolve.lpsolve_BBstrategies.NODE_PSEUDONONINTSELECT;
            LpSolvePresolve = lpsolve.lpsolve_presolve.PRESOLVE_COLS |
                                 lpsolve.lpsolve_presolve.PRESOLVE_ROWS |
                                 lpsolve.lpsolve_presolve.PRESOLVE_LINDEP;
            LpSolveBbFloorfirst = lpsolve.lpsolve_branch.BRANCH_AUTOMATIC;
#endif
            GetSensitivity = false;
            //base.Arithmetic = Arithmetic.Double;
            //base.TimeLimit = 600000;
            //LpSolveLogFile = @"LpSolve.log";
        }

        public override string ToString()
        {
            //return this.GetType().FullName;
            StringBuilder sb = new StringBuilder();
            sb.Append("LpSolve(");

            sb.Append("SolveAntiDegen:"); sb.Append(LpSolveAntiDegen.ToString());
            sb.Append(",SolveBasiscrash:"); sb.Append(LpSolveBasiscrash.ToString());
            sb.Append(",SolveBbDepthlimit:"); sb.Append(LpSolveBbDepthlimit.ToString());
            sb.Append(",SolveBbFloorfirst:"); sb.Append(LpSolveBbFloorfirst.ToString());
            sb.Append(",SolveBbRule:"); sb.Append(LpSolveBbRule.ToString());
            sb.Append(",SolveBreakAtFirst:"); sb.Append(LpSolveBreakAtFirst.ToString());
            sb.Append(",SolveBreakAtValue:"); sb.Append(LpSolveBreakAtValue.ToString());
            sb.Append(",SolveDebug:"); sb.Append(LpSolveDebug.ToString());
            sb.Append(",SolveEpsb:"); sb.Append(LpSolveEpsb.ToString());
            sb.Append(",SolveEpsd:"); sb.Append(LpSolveEpsd.ToString());
            sb.Append(",SolveEpsel:"); sb.Append(LpSolveEpsel.ToString());
            sb.Append(",SolveEpsint:"); sb.Append(LpSolveEpsint.ToString());
            sb.Append(",SolveEpsperturb:"); sb.Append(LpSolveEpsperturb.ToString());
            sb.Append(",SolveEpspivot:"); sb.Append(LpSolveEpspivot.ToString());
            sb.Append(",SolveImprove:"); sb.Append(LpSolveImprove.ToString());
            sb.Append(",SolveInfinite:"); sb.Append(LpSolveInfinite.ToString());
            sb.Append(",SolveMaxpivot:"); sb.Append(LpSolveMaxpivot.ToString());
            sb.Append(",SolveMipGapAbs:"); sb.Append(LpSolveMipGapAbs.ToString());
            sb.Append(",SolveMipGapRel:"); sb.Append(LpSolveMipGapRel.ToString());
            sb.Append(",SolveNegrange:"); sb.Append(LpSolveNegrange.ToString());
            sb.Append(",SolveObjBound:"); sb.Append(LpSolveObjBound.ToString());
            sb.Append(",SolveObjInBasis:"); sb.Append(LpSolveObjInBasis.ToString());
            sb.Append(",SolvePivoting:"); sb.Append(LpSolvePivoting.ToString());
            sb.Append(",SolvePresolve:"); sb.Append(LpSolvePresolve.ToString());
            sb.Append(",SolveScalelimit:"); sb.Append(LpSolveScalelimit.ToString());
            sb.Append(",SolveScaling:"); sb.Append(LpSolveScaling.ToString());
            sb.Append(",SolveSimplextype:"); sb.Append(LpSolveSimplextype.ToString());
            sb.Append(",SolveSolutionlimit:"); sb.Append(LpSolveSolutionlimit.ToString());
            sb.Append(",SolveTrace:"); sb.Append(LpSolveTrace.ToString());

            sb.Append(",TimeLimit (ms):"); sb.Append(TimeLimit.ToString());
            sb.Append(",GetSensitivity:"); sb.Append(GetSensitivity.ToString());
            sb.Append(")");
            return sb.ToString();
        }
    }
}