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

namespace SolverFoundation.Plugin.LpSolve {
  public class LpSolveDirective : Directive {

    public lpsolve.lpsolve_simplextypes LpSolveSimplextype {
      get;
      set;
    }

    public lpsolve.lpsolve_piv_rules LpSolvePivoting {
      get;
      set;
    }

    public lpsolve.lpsolve_anti_degen LpSolveAntiDegen {
      get;
      set;
    }

    public lpsolve.lpsolve_presolve LpSolvePresolve {
      get;
      set;
    }

    public lpsolve.lpsolve_BBstrategies LpSolveBbRule {
      get;
      set;
    }

    public lpsolve.lpsolve_branch LpSolveBbFloorfirst {
      get;
      set;
    }

    public double LpSolveMipGapAbs {
      get;
      set;
    }

    public string LpSolveLogFile {
      get;
      set;
    }

    public LpSolveDirective()
      : base() {
      LpSolveSimplextype = lpsolve.lpsolve_simplextypes.SIMPLEX_PRIMAL_PRIMAL;
      LpSolvePivoting = lpsolve.lpsolve_piv_rules.PRICER_STEEPESTEDGE;
      LpSolveAntiDegen = lpsolve.lpsolve_anti_degen.ANTIDEGEN_RHSPERTURB;
      LpSolveBbRule = lpsolve.lpsolve_BBstrategies.NODE_DYNAMICMODE |
                            lpsolve.lpsolve_BBstrategies.NODE_GREEDYMODE |
                            lpsolve.lpsolve_BBstrategies.NODE_PSEUDONONINTSELECT;
      LpSolvePresolve = lpsolve.lpsolve_presolve.PRESOLVE_COLS | lpsolve.lpsolve_presolve.PRESOLVE_ROWS | lpsolve.lpsolve_presolve.PRESOLVE_LINDEP;
      LpSolveBbFloorfirst = lpsolve.lpsolve_branch.BRANCH_AUTOMATIC;
      LpSolveMipGapAbs = 0.001;
      //base.TimeLimit = 600000;
      //LpSolveLogFile = @"LpSolve.log";
    }

    public override string ToString() {
      //return this.GetType().FullName;
      StringBuilder sb = new StringBuilder();
      sb.Append("LpSolve(");
      sb.Append("Algorithm:");
      sb.Append(LpSolveSimplextype.ToString());
      sb.Append(",");
      sb.Append("Pricing:");
      sb.Append(LpSolvePivoting.ToString());
      sb.Append(",");
      sb.Append("Degen:");
      sb.Append(LpSolveAntiDegen.ToString());
      sb.Append(",");
      sb.Append("Presolve:");
      sb.Append(LpSolvePresolve.ToString());
      sb.Append(",");
      sb.Append("Branch:");
      sb.Append(LpSolveBbFloorfirst.ToString());
      sb.Append(",");
      sb.Append("Mip:");
      sb.Append(LpSolveMipGapAbs.ToString());
      sb.Append(",");
      sb.Append("TimeLimit (ms):");
      sb.Append(TimeLimit.ToString());
      sb.Append(")");
      return sb.ToString();
    }
  }
}
