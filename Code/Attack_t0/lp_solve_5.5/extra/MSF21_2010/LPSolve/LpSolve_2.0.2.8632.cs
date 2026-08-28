//
// Copyright © Microsoft Corporation.  All Rights Reserved.
// This code released under the terms of the 
// Microsoft Public License (MS-PL, http://opensource.org/licenses/ms-pl.html.)
//
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;
using Microsoft.SolverFoundation.Services;
using Microsoft.SolverFoundation.Common;
using LpSolveNativeInterface;
using System.Diagnostics;

namespace SolverFoundation.Plugin.LpSolve {
  [Serializable]
  public class LpSolverModelException : MsfException {
    public LpSolverModelException(string msg)
      : base(msg) {

    }
  }

  /// <summary>
  /// Solver will be one of the states
  /// </summary>
  public enum SolverState {
    Start = 0,
    Solving = 1,
    Solved = 2,
    Aborting = 3,
    Aborted = 4,
    Disposing = 5,
    Disposed = 6
  }

  /// <summary>
  /// Utilizes the SFS plug-in SDK and lpsolve55.cs to invoke the methods on unmanaged lpsolve DLL(lpsolve55.dll)
  /// Application is set to run in 32-bit mode 
  /// Allows unsafe code to be able to access some of the methods in lpsolve55.cs
  /// </summary>
  public class LpSolveSolver : ILinearSolver, ILinearSolution, ILinearSimplexStatistics {
    private LinearModel _modelSFS;
    private int _lp = -1;
    private ISolverEnvironment _solverContext;
    private Func<bool> _queryAbortFunc;
    private int _state;
    private int _solutionStatus;
    private lpsolve.ctrlcfunc _callback;

    public LpSolveSolver()
      : this(null, null) {
    }

    public LpSolveSolver(ISolverEnvironment context)
      : this(context, null) {
    }


    public LpSolveSolver(ISolverEnvironment context, LinearModel model) {
      if (model == null)
        _modelSFS = new LinearModel(null);
      else
        _modelSFS = model;
      _solverContext = context;
      _state = (int)SolverState.Start;
    }

    ~LpSolveSolver() {
      Shutdown();
    }

    public void Shutdown() {
      //Solve runs in a different thread than Shutdown, wait until Solve returns
      //SFS calls Shutdown() twice. If its already disposed, do not dispose again
      if ((SolverState)_state == SolverState.Disposed) {
        return;
      }
      //If Shutdown is called before Solving
      while (Interlocked.CompareExchange(ref _state, (int)SolverState.Disposing, (int)SolverState.Start) == (int)SolverState.Start) ;

      //If solve is called before shutdown, wait for the solve to finish
      if (_state != (int)SolverState.Disposing) {
        while (_state != (int)SolverState.Solved && _state != (int)SolverState.Aborted)
          Thread.Sleep(0);
      }
      _state = (int)SolverState.Disposing;
      if (_lp > -1) {
        lpsolve.delete_lp(_lp);
        _lp = -1;
      }
      _modelSFS = null;
      _state = (int)SolverState.Disposed;
    }

    #region ILinearModel Members

    public IEqualityComparer<object> KeyComparer {
      get { return _modelSFS.KeyComparer; }
    }

    public int KeyCount {
      get { return _modelSFS.KeyCount; }
    }

    public IEnumerable<object> Keys {
      get { return _modelSFS.Keys; }
    }

    public IEnumerable<int> Indices {
      get { return _modelSFS.Indices; }
    }

    public int IntegerIndexCount {
      get { return _modelSFS.IntegerIndexCount; }
    }

    public bool IsQuadraticModel { // REVIEW: lengliu: LP_SOLVE does not support quadratic models.
      get { return _modelSFS.IsQuadraticModel; }
    }

    public bool IsQuadraticVariable(int vidVar) {
      return _modelSFS.IsQuadraticVariable(vidVar);
    }

    public bool AddRow(object key, out int vid) {
      return _modelSFS.AddRow(key, out vid);
    }

    public bool AddRow(object key, SpecialOrderedSetType sos, out int vidRow) {
      throw new NotImplementedException();
    }

    public IEnumerable<int> GetSpecialOrderedSetTypeRowIndexes(SpecialOrderedSetType sosType) {
      throw new NotImplementedException();
    }

    public int RowCount {
      get { return _modelSFS.RowCount; }
    }

    public IEnumerable<object> RowKeys {
      get { return _modelSFS.RowKeys; }
    }

    public IEnumerable<int> RowIndices {
      get { return _modelSFS.RowIndices; }
    }

    public bool AddVariable(object key, out int vid) {
      return _modelSFS.AddVariable(key, out vid);
    }

    public int VariableCount {
      get { return _modelSFS.VariableCount; }
    }

    public IEnumerable<object> VariableKeys {
      get { return _modelSFS.VariableKeys; }
    }

    public IEnumerable<int> VariableIndices {
      get { return _modelSFS.VariableIndices; }
    }

    public bool IsSpecialOrderedSet {
      get { throw new NotImplementedException(); }
    }

    public bool IsRow(int vid) {
      return _modelSFS.IsRow(vid);
    }

    public bool TryGetIndexFromKey(object key, out int vid) {
      return _modelSFS.TryGetIndexFromKey(key, out vid);
    }

    public int GetIndexFromKey(object key) {
      return _modelSFS.GetIndexFromKey(key);
    }

    public object GetKeyFromIndex(int vid) {
      return _modelSFS.GetKeyFromIndex(vid);
    }

    public void SetBounds(int vid, Rational numLo, Rational numHi) {
      _modelSFS.SetBounds(vid, numLo, numHi);
    }

    public void SetLowerBound(int vid, Rational numLo) {
      _modelSFS.SetLowerBound(vid, numLo);
    }

    public void SetUpperBound(int vid, Rational numHi) {
      _modelSFS.SetUpperBound(vid, numHi);
    }

    public void GetBounds(int vid, out Rational numLo, out Rational numHi) {
      _modelSFS.GetBounds(vid, out numLo, out numHi);
    }

    public void SetValue(int vid, Rational num) {
      _modelSFS.SetValue(vid, num);
    }

    public Rational GetValue(int vid) {
      return _modelSFS.GetValue(vid);
    }

    public LinearValueState GetValueState(int vid) {
      return _modelSFS.GetValueState(vid);
    }

    public void SetIgnoreBounds(int vid, bool fIgnore) {
      _modelSFS.SetIgnoreBounds(vid, fIgnore);
    }

    public bool GetIgnoreBounds(int vid) {
      return _modelSFS.GetIgnoreBounds(vid);
    }

    public void SetBasic(int vid, bool fBasic) {
      _modelSFS.SetBasic(vid, fBasic);
    }

    public bool GetBasic(int vid) {
      return _modelSFS.GetBasic(vid);
    }

    public void SetIntegrality(int vid, bool fInteger) {
      _modelSFS.SetIntegrality(vid, fInteger);
    }

    public bool GetIntegrality(int vid) {
      return _modelSFS.GetIntegrality(vid);
    }

    public int CoefficientCount {
      get { return _modelSFS.CoefficientCount; }
    }

    public void SetCoefficient(int vidRow, int vidVar, Rational num) {
      _modelSFS.SetCoefficient(vidRow, vidVar, num);
    }

    public void SetCoefficient(int vidRow, Rational num, int vidVar1, int vidVar2) {
      throw new NotImplementedException();
    }

    public Rational GetCoefficient(int vidRow, int vidVar) {
      return _modelSFS.GetCoefficient(vidRow, vidVar);
    }

    public Rational GetCoefficient(int goalRow, int vidVar1, int vidVar2) {
      return _modelSFS.GetCoefficient(goalRow, vidVar1, vidVar2);
    }

    public int GetRowEntryCount(int vidRow) {
      return _modelSFS.GetRowEntryCount(vidRow);
    }

    public IEnumerable<LinearEntry> GetRowEntries(int vidRow) {
      return _modelSFS.GetRowEntries(vidRow);
    }

    public IEnumerable<QuadraticEntry> GetRowQuadraticEntries(int vidRow) {
      throw new NotImplementedException();
    }

    public int GetVariableEntryCount(int vid) {
      return _modelSFS.GetVariableEntryCount(vid);
    }

    public IEnumerable<LinearEntry> GetVariableEntries(int vid) {
      return _modelSFS.GetVariableEntries(vid);
    }

    public ILinearGoal AddGoal(int vid, int pri, bool fMinimize) {
      if (GoalCount == 1)
        throw new LpSolverModelException("There is already a goal added to the model. LpSolve allows only one goal per model");
      return _modelSFS.AddGoal(vid, pri, fMinimize);
    }

    public void ClearGoals() {
      _modelSFS.ClearGoals();
    }

    public bool RemoveGoal(int vid) {
      return _modelSFS.RemoveGoal(vid);
    }

    public int GoalCount {
      get { return _modelSFS.GoalCount; }
    }

    public IEnumerable<ILinearGoal> Goals {
      get { return _modelSFS.Goals; }
    }

    public bool IsGoal(int vid) {
      return _modelSFS.IsGoal(vid);
    }

    public bool IsGoal(int vid, out ILinearGoal goal) {
      return _modelSFS.IsGoal(vid, out goal);
    }

    public ILinearGoal GetGoalFromIndex(int vid) {
      return _modelSFS.GetGoalFromIndex(vid);
    }

    #endregion

    /// <summary>
    /// Populate model in LPSolve from the SFS LinearModel 
    /// </summary>
    /// <returns></returns>
    private void LoadLpsolveModel() {
      if (VariableCount == 0)
        throw new LpSolverModelException("Model does not have any variables");

      //Create model with 
      _lp = lpsolve.make_lp(0, VariableCount);

      int vindex = 0;
      int rindex = 1;
      Rational numLo;
      Rational numHi;
      int vid;

      //Assign variable/column names
      //Assign bounds to the variables
      //Assign intergrality
      //Read from SFS LinearModel
      foreach (Object key in VariableKeys) {
        vindex++;
        lpsolve.set_col_name(_lp, vindex, key.ToString());
        vid = GetIndexFromKey(key);

        if (GetIntegrality(vid))
          lpsolve.set_int(_lp, vindex, true);

        //If bouns are set, assign bounds to the variables
        if (!GetIgnoreBounds(vid)) {
          GetBounds(vid, out numLo, out numHi);

          if (numLo != Rational.NegativeInfinity && numHi != Rational.PositiveInfinity) {
            lpsolve.set_bounds(_lp, vindex, (double)numLo, (double)numHi);
          }
          else if (numLo != Rational.NegativeInfinity) {
            lpsolve.set_lowbo(_lp, vindex, (double)numLo);
          }
          else if (numHi != Rational.PositiveInfinity) {
            lpsolve.set_upbo(_lp, vindex, (double)numHi);
            lpsolve.set_lowbo(_lp, vindex, double.NegativeInfinity);
          }
          else {
            lpsolve.set_lowbo(_lp, vindex, double.NegativeInfinity);
            lpsolve.set_upbo(_lp, vindex, double.PositiveInfinity);
          }
        }
        else {
          lpsolve.set_unbounded(_lp, vindex);
        }
      }

      //add rows/constraints
      //Sort Rows and Variables by vid so that the order of columns is always same when accessing

      double[] row = new double[VariableIndices.Count() + 1];
      double coeff;

      foreach (int r in RowIndices) {
        vindex = 1;
        if (!IsGoal(r)) {
          foreach (int c in VariableIndices) {
            coeff = GetCoefficient(r, c).ToDouble();
            row[vindex++] = coeff;
          }
          GetBounds(r, out numLo, out numHi);
          if (numLo == numHi) {
            lpsolve.add_constraint(_lp, row, lpsolve.lpsolve_constr_types.EQ, numLo.ToDouble());
          }
          else {
            if (numLo != Rational.NegativeInfinity && numHi != Rational.PositiveInfinity) {
              lpsolve.add_constraint(_lp, row, lpsolve.lpsolve_constr_types.LE, numHi.ToDouble());
              lpsolve.set_rh_range(_lp, rindex, (double)(numHi - numLo));
            }
            else if (numLo != Rational.NegativeInfinity) {
              lpsolve.add_constraint(_lp, row, lpsolve.lpsolve_constr_types.GE, numLo.ToDouble());
            }
            else if (numHi != Rational.PositiveInfinity) {
              lpsolve.add_constraint(_lp, row, lpsolve.lpsolve_constr_types.LE, numHi.ToDouble());
            }
          }

          lpsolve.set_row_name(_lp, rindex, GetKeyFromIndex(r).ToString());
          rindex++;
        }
      }

      //Goals/objectives--First row in LPSolve is goal
      //Only one goal is allowed in LPSolve
      foreach (int r in RowIndices) {
        vindex = 1;
        ILinearGoal goal;
        if (IsGoal(r, out goal)) {
          foreach (int c in VariableIndices) {
            coeff = GetCoefficient(r, c).ToDouble();
            row[vindex++] = coeff;
          }
          //objective function to be minimized/maximized
          if (goal.Minimize)
            lpsolve.set_minim(_lp);
          else
            lpsolve.set_maxim(_lp);

          lpsolve.set_obj_fn(_lp, row);
          break;
        }
      }
    }

    private void LoadLpSolveResults() {
      //Assign values to the variables/constraints/Goal
      List<int> varIds = VariableIndices.ToList();
      List<int> rowIds = RowIndices.ToList();
      int lpOrigRCount = lpsolve.get_Norig_rows(_lp);
      int lpOrigVCount = lpsolve.get_Norig_columns(_lp);
      int lpRowCount = lpsolve.get_Nrows(_lp);
      int index = GoalCount + lpRowCount;
      double value;
      //Debug.Assert(GoalCount == 1);
      double[] lpSol = new double[GoalCount + lpOrigRCount + lpOrigVCount];
      if (lpsolve.get_primal_solution(_lp, ref lpSol[0])) {
        foreach (int vid in varIds) {
          value = lpSol[index];
          SetValue(vid, (Rational)value);
          index++;
        }
      }

      index = GoalCount;
      foreach (int vid in rowIds) {
        if (!IsGoal(vid)) {
          SetValue(vid, (Rational)lpSol[index]);
          index++;
        }
      }

      value = 0.0;
      foreach (int vid in rowIds) {
        if (IsGoal(vid)) {
          value = lpsolve.get_objective(_lp);
          SetValue(vid, (Rational)value);
          break;
        }
      }
    }

    private bool LpAbortFunc(int lp, int userhandle) {
      _state = (int)SolverState.Aborting;
      return _queryAbortFunc();
    }

    public ILinearSolution Solve(ISolverParameters param) {
      try {
        //If the PlugIn is shutting down or shutdown, stop solving
        //Remarks:a-pavans:This is not needed, but to avoid the CompareExchange and better readability
        if ((SolverState)_state == SolverState.Disposing || (SolverState)_state == SolverState.Disposed)
          return this;

        //Initiaze the solver
        //If the current state is Start, then initialize the solver
        while (Interlocked.CompareExchange(ref _state, (int)SolverState.Solving, (int)SolverState.Start) == (int)SolverState.Start) ;
        //If the state is solving, start solving
        if ((SolverState)_state == SolverState.Solving) {
          //_solverFinished.Reset();
          LpSolveParams prms = param as LpSolveParams;
          if (prms == null)
            prms = new LpSolveParams();

          _queryAbortFunc = prms.QueryAbort;
          _callback = new lpsolve.ctrlcfunc(LpAbortFunc);
          lpsolve.Init(".");
          LoadLpsolveModel();
          lpsolve.set_simplextype(_lp, prms._lpsolveAlgorithm);
          lpsolve.set_pivoting(_lp, prms._lpsolvePricing);
          lpsolve.set_presolve(_lp, prms._lpsolvePresolve, lpsolve.get_presolveloops(_lp));
          lpsolve.set_bb_floorfirst(_lp, prms._lpsolveBranch);
          lpsolve.set_bb_rule(_lp, prms._lpsolveBranchBound);
          lpsolve.set_anti_degen(_lp, prms._lpsolveAntiDegen);
          lpsolve.set_mip_gap(_lp, false, prms._lpsolveMipGap);
          lpsolve.set_outputfile(_lp, prms._lpsolveLogFile);
          lpsolve.put_abortfunc(_lp, _callback, 0);
          lpsolve.lpsolve_return lpReturn = lpsolve.solve(_lp);

#if DEBUG
                  lpsolve.print_objective(_lp);
                  lpsolve.print_solution(_lp, 1);
                  lpsolve.print_constraints(_lp, 1);
                  lpsolve.print_lp(_lp);
                  lpsolve.print_debugdump(_lp, "debug.txt");
#endif
          LoadLpSolveResults();
        }
        _solutionStatus = lpsolve.get_status(_lp);
        //Only Solve thread will be active here, dont need CompareExchange
        //If aborted by the callback, set the status to aborted
        if ((SolverState)_state == SolverState.Aborting)
          _state = (int)SolverState.Aborted;
        //Solve has been done
        else if ((SolverState)_state == SolverState.Solving)
          _state = (int)SolverState.Solved;
      }
      catch (Exception) {
        //Remarks: a-pavans: Not sure what to do in case of exception
        _state = (int)SolverState.Aborted;
        throw;
      }
      return this;
    }

   #region ILinearSolution Members

    public LinearSolutionQuality SolutionQuality {
      get {
        if (_solutionStatus == (int)lpsolve.lpsolve_return.OPTIMAL)
          return LinearSolutionQuality.Approximate;
        else
          return LinearSolutionQuality.None;
      }
    }

    public LinearResult LpResult {
      get {
        lpsolve.lpsolve_return enumStatus = (lpsolve.lpsolve_return)_solutionStatus;
        lpsolve.lpsolve_simplextypes simplex = lpsolve.get_simplextype(_lp);
        if (simplex == lpsolve.lpsolve_simplextypes.SIMPLEX_PRIMAL_PRIMAL) {
          switch (enumStatus) {
          case lpsolve.lpsolve_return.OPTIMAL:
            return LinearResult.Optimal;
          case lpsolve.lpsolve_return.INFEASIBLE:
            return LinearResult.InfeasiblePrimal;
          case lpsolve.lpsolve_return.UNBOUNDED:
            return LinearResult.UnboundedPrimal;
          case lpsolve.lpsolve_return.NOMEMORY:
          case lpsolve.lpsolve_return.TIMEOUT:
            return LinearResult.Invalid;
          default:
            return LinearResult.Invalid;
          };
        }
        else {
          switch (enumStatus) {
          case lpsolve.lpsolve_return.OPTIMAL:
            return LinearResult.Optimal;
          case lpsolve.lpsolve_return.INFEASIBLE:
            return LinearResult.InfeasibleOrUnbounded;
          case lpsolve.lpsolve_return.UNBOUNDED:
            return LinearResult.UnboundedDual;
          case lpsolve.lpsolve_return.NOMEMORY:
          case lpsolve.lpsolve_return.TIMEOUT:
            return LinearResult.Invalid;
          default:
            return LinearResult.Invalid;
          };
        }
      }
    }

    public LinearResult MipResult {
      get {
        lpsolve.lpsolve_return enumStatus = (lpsolve.lpsolve_return)_solutionStatus;
        lpsolve.lpsolve_simplextypes simplex = lpsolve.get_simplextype(_lp);

        switch (enumStatus) {
        case lpsolve.lpsolve_return.OPTIMAL:
          return LinearResult.Optimal;
        case lpsolve.lpsolve_return.INFEASIBLE:
          if (simplex == lpsolve.lpsolve_simplextypes.SIMPLEX_PRIMAL_PRIMAL)
            return LinearResult.InfeasiblePrimal;
          else
            return LinearResult.InfeasibleOrUnbounded;
        case lpsolve.lpsolve_return.UNBOUNDED:
          return LinearResult.Invalid;
        case lpsolve.lpsolve_return.NOMEMORY:
        case lpsolve.lpsolve_return.TIMEOUT:
          return LinearResult.Invalid;
        default:
          return LinearResult.Invalid; ;
        };
      }
    }

    public virtual LinearResult Result {
      get {
        if (_modelSFS.IsMipModel)
          return MipResult;
        else
          return LpResult;
      }
    }

    public int SolvedGoalCount {
      get {
        if (GoalCount == 0)
          return 0;
        int solutionCount = lpsolve.get_solutioncount(_lp);
        if (solutionCount > 0)
          return 1;
        else
          return 0;
      }
    }

    public void GetSolvedGoal(int igoal, out object key, out int vid, out bool fMinimize, out bool fOptimal) {
      //Implemented only one goal right now, it will be the first one
      ILinearGoal goal = Goals.ElementAt(igoal);
      key = goal.Key;
      vid = goal.Index;
      fMinimize = goal.Minimize;
      fOptimal = _solutionStatus == (int)lpsolve.lpsolve_return.OPTIMAL;
    }

    public Rational MipBestBound {
      get {
        if (_modelSFS.IsMipModel)
          return lpsolve.get_obj_bound(_lp);
        else
          return Rational.Indeterminate;
      }
    }

    #endregion

    #region ILinearSimplexStatistics Members

    public int InnerIndexCount {
      get {
        int rows = lpsolve.get_Nrows(_lp);
        int cols = lpsolve.get_Ncolumns(_lp);
        return rows + cols;
      }
    }

    public int InnerIntegerIndexCount {
      get {
        int count = 0;
        for (int i = 1; i <= lpsolve.get_Ncolumns(_lp); i++) {
          if (lpsolve.is_int(_lp, i))
            count++;
        }
        return count;
      }
    }

    public int InnerSlackCount {
      get {
        return lpsolve.get_Nrows(_lp);
      }
    }

    public int InnerRowCount {
      get {
        return lpsolve.get_Nrows(_lp);
      }
    }

    public int PivotCount {
      get {
        return lpsolve.get_maxpivot(_lp);
      }
    }

    public int PivotCountDegenerate {
      get { throw new NotImplementedException(); }
    }

    public int PivotCountExact {
      get { throw new NotImplementedException(); }
    }

    public int PivotCountExactPhaseOne {
      get { throw new NotImplementedException(); }
    }

    public int PivotCountExactPhaseTwo {
      get { throw new NotImplementedException(); }
    }

    public int PivotCountDouble {
      get { throw new NotImplementedException(); }
    }

    public int PivotCountDoublePhaseOne {
      get { throw new NotImplementedException(); }
    }

    public int PivotCountDoublePhaseTwo {
      get { throw new NotImplementedException(); }
    }

    public int FactorCount {
      get {
        throw new NotImplementedException();
      }
    }

    public int FactorCountExact {
      get { throw new NotImplementedException(); }
    }

    public int FactorCountDouble {
      get { throw new NotImplementedException(); }
    }

    public int BranchCount {
      get {
        return (int)lpsolve.get_total_nodes(_lp);
      }
    }

    public Rational Gap {
      get {
        return lpsolve.get_mip_gap(_lp, true);
      }
    }

    public bool UseExact {
      get {
        throw new NotImplementedException();
      }
    }

    public bool UseDouble {
      get {
        throw new NotImplementedException();
      }
    }

    public Microsoft.SolverFoundation.Solvers.SimplexAlgorithmKind AlgorithmUsed {
      get {
        lpsolve.lpsolve_simplextypes simplex = lpsolve.get_simplextype(_lp);
        Microsoft.SolverFoundation.Solvers.SimplexAlgorithmKind algorithm = Microsoft.SolverFoundation.Solvers.SimplexAlgorithmKind.Dual;
        if (simplex == lpsolve.lpsolve_simplextypes.SIMPLEX_PRIMAL_PRIMAL || simplex == lpsolve.lpsolve_simplextypes.SIMPLEX_DUAL_PRIMAL)
          algorithm = Microsoft.SolverFoundation.Solvers.SimplexAlgorithmKind.Primal;
        if (simplex == lpsolve.lpsolve_simplextypes.SIMPLEX_DUAL_DUAL || simplex == lpsolve.lpsolve_simplextypes.SIMPLEX_PRIMAL_DUAL)
          algorithm = Microsoft.SolverFoundation.Solvers.SimplexAlgorithmKind.Dual;
        return algorithm;
      }
    }

    public Microsoft.SolverFoundation.Solvers.SimplexCosting CostingUsedExact {
      get {
        throw new NotImplementedException();
      }
    }

    public Microsoft.SolverFoundation.Solvers.SimplexCosting CostingUsedDouble {
      get {
        throw new NotImplementedException();
      }
    }

    #endregion

    #region ILinearSolver Members


    public ILinearSolverReport GetReport(LinearSolverReportType reportType) {
      return new LpSolveReport();
    }

    public Rational GetSolutionValue(int goalIndex) {
      return GetValue(goalIndex);
    }

    ILinearSolution ILinearSolver.Solve(ISolverParameters parameters) {
      Solve(parameters);
      return this;
    }

    #endregion
  }

  public class LpSolveReport : ILinearSolverReport {

  }

  public class LpSolveParams : ISolverParameters {
    internal lpsolve.lpsolve_simplextypes _lpsolveAlgorithm;
    internal lpsolve.lpsolve_piv_rules _lpsolvePricing;
    internal lpsolve.lpsolve_anti_degen _lpsolveAntiDegen;
    internal lpsolve.lpsolve_presolve _lpsolvePresolve;
    internal lpsolve.lpsolve_BBstrategies _lpsolveBranchBound;
    internal lpsolve.lpsolve_branch _lpsolveBranch;
    internal double _lpsolveMipGap;
    internal string _lpsolveLogFile;
    internal int _lpsolveTimeout;
    private bool _fAbort;
    private Func<bool> _fnQueryAbort;

    public LpSolveParams() : this((Func<bool>)null) { }

    /// <summary> construct a solver parameter object
    /// </summary>
    public LpSolveParams(Func<bool> fnQueryAbort) {
      _lpsolveAlgorithm = lpsolve.lpsolve_simplextypes.SIMPLEX_PRIMAL_PRIMAL;
      _lpsolvePricing = lpsolve.lpsolve_piv_rules.PRICER_STEEPESTEDGE;
      _lpsolveAntiDegen = lpsolve.lpsolve_anti_degen.ANTIDEGEN_RHSPERTURB;
      _lpsolveBranchBound = lpsolve.lpsolve_BBstrategies.NODE_DYNAMICMODE |
                            lpsolve.lpsolve_BBstrategies.NODE_GREEDYMODE |
                            lpsolve.lpsolve_BBstrategies.NODE_PSEUDONONINTSELECT;
      _lpsolvePresolve = lpsolve.lpsolve_presolve.PRESOLVE_COLS |
                         lpsolve.lpsolve_presolve.PRESOLVE_ROWS |
                         lpsolve.lpsolve_presolve.PRESOLVE_LINDEP;
      _lpsolveBranch = lpsolve.lpsolve_branch.BRANCH_AUTOMATIC;
      _fnQueryAbort = fnQueryAbort;
      _lpsolveMipGap = 0.001;
      _lpsolveTimeout = 600;
      _lpsolveLogFile = @"LpSolve.log";
    }

    /// <summary> copy constructor 
    /// </summary>
    public LpSolveParams(LpSolveParams prms) {
      _lpsolveAlgorithm = prms._lpsolveAlgorithm;
      _lpsolvePricing = prms._lpsolvePricing;
      _lpsolveAntiDegen = prms._lpsolveAntiDegen;
      _lpsolveBranchBound = prms._lpsolveBranchBound;
      _lpsolvePresolve = prms._lpsolvePresolve;
      _lpsolveBranch = prms._lpsolveBranch;
      _fAbort = prms._fAbort;
      _fnQueryAbort = prms._fnQueryAbort;
      _lpsolveMipGap = prms._lpsolveMipGap;
      _lpsolveTimeout = prms._lpsolveTimeout;
      _lpsolveLogFile = prms._lpsolveLogFile;
    }

    public LpSolveParams(Directive directive) {
      LpSolveDirective lpDirective = directive as LpSolveDirective;
      if (lpDirective != null) {
        _lpsolveAlgorithm = lpDirective.LpSolveAlgorithm;
        _lpsolvePricing = lpDirective.LpSolvePricing;
        _lpsolvePresolve = lpDirective.LpSolvePresolve;
        _lpsolveBranch = lpDirective.LpSolveBranch;
        _lpsolveBranchBound = lpDirective.LpSolveBranchBound;
        _lpsolveAntiDegen = lpDirective.LpSolveAntiDegen;
        _lpsolveMipGap = lpDirective.LpSolveMipGap;
        _lpsolveTimeout = lpDirective.TimeLimit;
        _lpsolveLogFile = lpDirective.LpSolveLogFile;
      }
    }

    public Func<bool> QueryAbort {
      get {
        return _fnQueryAbort;
      }
      set {
        _fnQueryAbort = value;
      }
    }

    private void FillInSolverParams(Directive directive) {
      // REVIEW: need to parse the directive and generate appropriate LpSolverParams
      LpSolveDirective lpDirective = (LpSolveDirective)directive;
      if (lpDirective != null) {
        _lpsolveAlgorithm = lpDirective.LpSolveAlgorithm;
        _lpsolvePricing = lpDirective.LpSolvePricing;
        _lpsolvePresolve = lpDirective.LpSolvePresolve;
        _lpsolveBranch = lpDirective.LpSolveBranch;
        _lpsolveBranchBound = lpDirective.LpSolveBranchBound;
        _lpsolveAntiDegen = lpDirective.LpSolveAntiDegen;
        _lpsolveMipGap = lpDirective.LpSolveMipGap;
        _lpsolveTimeout = lpDirective.TimeLimit;
        _lpsolveLogFile = lpDirective.LpSolveLogFile;
      }
    }
  }
}
