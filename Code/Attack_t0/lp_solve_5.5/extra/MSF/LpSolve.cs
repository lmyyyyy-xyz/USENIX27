#define MSF_2_0_3

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

namespace SolverFoundation.Plugin.LpSolve
{
    [Serializable]
    public class LpSolverModelException : MsfException
    {
        public LpSolverModelException(string msg)
            : base(msg)
        {

        }
    }

    /// <summary>
    /// Solver will be one of the states
    /// </summary>
    public enum SolverState
    {
        Start = 0,
        Solving = 1,
        Solved = 2,
        Aborting = 3,
        Aborted = 4,
        Disposing = 5,
        Disposed = 6
    }

    public delegate void LpSolveLogFunc(int lp, int userhandle, string buffer);
    public delegate void LpSolveMsgFunc(int lp, int userhandle, lpsolve.lpsolve_msgmask message);

    /// <summary>
    /// Utilizes the SFS plug-in SDK and lpsolve55.cs to invoke the methods on unmanaged lpsolve DLL(lpsolve55.dll)
    /// Application is set to run in 32-bit mode
    /// Allows unsafe code to be able to access some of the methods in lpsolve55.cs
    /// </summary>
    public class LpSolveSolver : ILinearSolver, ILinearSolution, ILinearSimplexStatistics
#if MSF_2_0_3
, IReportProvider, ISolverProperties, ILinearSolverSensitivityReport
#endif
    {
        private LinearModel _modelSFS;
        private int _lp = 0;
        private bool _GetSensitivity = false;
        private double _infinite = 1.0e30;
        private ISolverEnvironment _solverContext;
        private Func<bool> _queryAbortFunc = null;
        private int _state;
        private int _solutionStatus;
#if MSF_2_0_3
        private Action _solvingEventFunc;
        private lpsolve.logfunc _logfunc;
        private lpsolve.msgfunc _msgfunc;
        private LpSolveLogFunc _LpSolveLogFunc = null;
        private LpSolveMsgFunc _LpSolveMsgFunc = null;
#endif
        private lpsolve.ctrlcfunc _callback;
        protected Dictionary<int, int> _sfsToSolverVarIndex;
        protected Dictionary<int, int> _sfsToSolverRowMapping;
        //rowIds of SOS constraints
        protected List<int> _vidRowSOS1;
        protected List<int> _vidRowSOS2;

        public LpSolveSolver()
            : this(null, null)
        {
        }

        public LpSolveSolver(ISolverEnvironment context)
            : this(context, null)
        {
        }


        public LpSolveSolver(ISolverEnvironment context, LinearModel model)
        {
            if (model == null)
                _modelSFS = new LinearModel(null);
            else
                _modelSFS = model;
            _solverContext = context;
            _state = (int)SolverState.Start;
        }

        ~LpSolveSolver()
        {
            Shutdown();
        }

        public void Shutdown()
        {
            //Solve runs in a different thread than Shutdown, wait until Solve returns
            //SFS calls Shutdown() twice. If its already disposed, do not dispose again
            if ((SolverState)_state == SolverState.Disposed)
            {
                return;
            }
            //If Shutdown is called before Solving
            while (Interlocked.CompareExchange(ref _state, (int)SolverState.Disposing, (int)SolverState.Start) == (int)SolverState.Start) ;

            //If solve is called before shutdown, wait for the solve to finish
            if (_state != (int)SolverState.Disposing)
            {
                while (_state != (int)SolverState.Solved && _state != (int)SolverState.Aborted)
                    Thread.Sleep(0);
            }
            _state = (int)SolverState.Disposing;
            if (_lp != 0)
            {
                lpsolve.delete_lp(_lp);
                _lp = 0;
            }
            _modelSFS = null;
            _sfsToSolverRowMapping = null;
            _sfsToSolverVarIndex = null;
            _vidRowSOS1 = null;
            _vidRowSOS2 = null;
            _state = (int)SolverState.Disposed;
        }

        #region ILinearModel Members

        public IEqualityComparer<object> KeyComparer
        {
            get { return _modelSFS.KeyComparer; }
        }

        public int KeyCount
        {
            get { return _modelSFS.KeyCount; }
        }

        public IEnumerable<object> Keys
        {
            get { return _modelSFS.Keys; }
        }

        public IEnumerable<int> Indices
        {
            get { return _modelSFS.Indices; }
        }

        public int IntegerIndexCount
        {
            get { return _modelSFS.IntegerIndexCount; }
        }

        public bool IsQuadraticModel
        { // REVIEW: lengliu: LP_SOLVE does not support quadratic models.
            get { return _modelSFS.IsQuadraticModel; }
        }

        public bool IsQuadraticVariable(int vidVar)
        {
            return _modelSFS.IsQuadraticVariable(vidVar);
        }

        public bool AddRow(object key, out int vid)
        {
            return _modelSFS.AddRow(key, out vid);
        }

        public bool AddRow(object key, SpecialOrderedSetType sos, out int vidRow)
        {
            return _modelSFS.AddRow(key, sos, out vidRow);
        }

        public IEnumerable<int> GetSpecialOrderedSetTypeRowIndexes(SpecialOrderedSetType sosType)
        {
            return _modelSFS.GetSpecialOrderedSetTypeRowIndexes(sosType);
        }

        public int RowCount
        {
            get { return _modelSFS.RowCount; }
        }

        public IEnumerable<object> RowKeys
        {
            get { return _modelSFS.RowKeys; }
        }

        public IEnumerable<int> RowIndices
        {
            get { return _modelSFS.RowIndices; }
        }

        public bool AddVariable(object key, out int vid)
        {
            return _modelSFS.AddVariable(key, out vid);
        }

        public int VariableCount
        {
            get { return _modelSFS.VariableCount; }
        }

        public IEnumerable<object> VariableKeys
        {
            get { return _modelSFS.VariableKeys; }
        }

        public IEnumerable<int> VariableIndices
        {
            get { return _modelSFS.VariableIndices; }
        }

        public bool IsSpecialOrderedSet
        {
            get { return _modelSFS.IsSpecialOrderedSet; }
        }

        public bool IsRow(int vid)
        {
            return _modelSFS.IsRow(vid);
        }

        public bool TryGetIndexFromKey(object key, out int vid)
        {
            return _modelSFS.TryGetIndexFromKey(key, out vid);
        }

        public int GetIndexFromKey(object key)
        {
            return _modelSFS.GetIndexFromKey(key);
        }

        public object GetKeyFromIndex(int vid)
        {
            return _modelSFS.GetKeyFromIndex(vid);
        }

        public void SetBounds(int vid, Rational numLo, Rational numHi)
        {
            _modelSFS.SetBounds(vid, numLo, numHi);
        }

        public void SetLowerBound(int vid, Rational numLo)
        {
            _modelSFS.SetLowerBound(vid, numLo);
        }

        public void SetUpperBound(int vid, Rational numHi)
        {
            _modelSFS.SetUpperBound(vid, numHi);
        }

        public void GetBounds(int vid, out Rational numLo, out Rational numHi)
        {
            _modelSFS.GetBounds(vid, out numLo, out numHi);
        }

        public void SetValue(int vid, Rational num)
        {
            _modelSFS.SetValue(vid, num);
        }

        public Rational GetValue(int vid)
        {
            return _modelSFS.GetValue(vid);
        }

        public LinearValueState GetValueState(int vid)
        {
            return _modelSFS.GetValueState(vid);
        }

        public void SetIgnoreBounds(int vid, bool fIgnore)
        {
            _modelSFS.SetIgnoreBounds(vid, fIgnore);
        }

        public bool GetIgnoreBounds(int vid)
        {
            return _modelSFS.GetIgnoreBounds(vid);
        }

        public void SetBasic(int vid, bool fBasic)
        {
            _modelSFS.SetBasic(vid, fBasic);
        }

        public bool GetBasic(int vid)
        {
            return _modelSFS.GetBasic(vid);
        }

        public void SetIntegrality(int vid, bool fInteger)
        {
            _modelSFS.SetIntegrality(vid, fInteger);
        }

        public bool GetIntegrality(int vid)
        {
            return _modelSFS.GetIntegrality(vid);
        }

        public int CoefficientCount
        {
            get { return _modelSFS.CoefficientCount; }
        }

        public void SetCoefficient(int vidRow, int vidVar, Rational num)
        {
            _modelSFS.SetCoefficient(vidRow, vidVar, num);
        }

        public void SetCoefficient(int vidRow, Rational num, int vidVar1, int vidVar2)
        {
            throw new NotImplementedException();
        }

        public Rational GetCoefficient(int vidRow, int vidVar)
        {
            return _modelSFS.GetCoefficient(vidRow, vidVar);
        }

        public Rational GetCoefficient(int goalRow, int vidVar1, int vidVar2)
        {
            return _modelSFS.GetCoefficient(goalRow, vidVar1, vidVar2);
        }

        public int GetRowEntryCount(int vidRow)
        {
            return _modelSFS.GetRowEntryCount(vidRow);
        }

        public IEnumerable<LinearEntry> GetRowEntries(int vidRow)
        {
            return _modelSFS.GetRowEntries(vidRow);
        }

        public IEnumerable<QuadraticEntry> GetRowQuadraticEntries(int vidRow)
        {
            throw new NotImplementedException();
        }

        public int GetVariableEntryCount(int vid)
        {
            return _modelSFS.GetVariableEntryCount(vid);
        }

        public IEnumerable<LinearEntry> GetVariableEntries(int vid)
        {
            return _modelSFS.GetVariableEntries(vid);
        }

        public ILinearGoal AddGoal(int vid, int pri, bool fMinimize)
        {
            if (GoalCount == 1)
                throw new LpSolverModelException("There is already a goal added to the model. LpSolve allows only one goal per model");
            return _modelSFS.AddGoal(vid, pri, fMinimize);
        }

        public void ClearGoals()
        {
            _modelSFS.ClearGoals();
        }

        public bool RemoveGoal(int vid)
        {
            return _modelSFS.RemoveGoal(vid);
        }

        public int GoalCount
        {
            get { return _modelSFS.GoalCount; }
        }

        public IEnumerable<ILinearGoal> Goals
        {
            get { return _modelSFS.Goals; }
        }

        public bool IsGoal(int vid)
        {
            return _modelSFS.IsGoal(vid);
        }

        public bool IsGoal(int vid, out ILinearGoal goal)
        {
            return _modelSFS.IsGoal(vid, out goal);
        }

        public ILinearGoal GetGoalFromIndex(int vid)
        {
            return _modelSFS.GetGoalFromIndex(vid);
        }

        #endregion

        /// <summary>
        /// Populate model in LPSolve from the SFS LinearModel
        /// </summary>
        /// <returns></returns>
        private void LoadLpsolveModel()
        {
            if (VariableCount == 0)
                throw new LpSolverModelException("Model does not have any variables");

            //Create model with
            _lp = lpsolve.make_lp(0, VariableCount);
            if (_lp == 0)
                throw new LpSolverModelException("Could not create an lpsolve model");

            _infinite = LpSolveNativeInterface.lpsolve.get_infinite(_lp);

            lpsolve.set_add_rowmode(_lp, 1); // since the model is build row by row, a performance boost is given when add_rowmode is set on while building the model

            _sfsToSolverRowMapping = new Dictionary<int, int>(RowCount);
            _sfsToSolverVarIndex = new Dictionary<int, int>(VariableCount);

            int vindex = 0;
            Rational numLo;
            Rational numHi;
#if MSF_2_0_3
#else
            int vid;
#endif

            //Assign variable/column names
            //Assign bounds to the variables
            //Assign intergrality
            //Read from SFS LinearModel
#if MSF_2_0_3
            foreach (int vid in VariableIndices)
#else
            foreach (Object key in VariableKeys)
#endif
            {
                vindex++;

#if MSF_2_0_3
                //lpsolve.set_col_name(_lp, vindex, vid.ToString());
#else
                vid = GetIndexFromKey(key);
                //lpsolve.set_col_name(_lp, vindex, key.ToString());
#endif
                if (GetIntegrality(vid))
                    lpsolve.set_int(_lp, vindex, 1);

                //If bounds are set, assign bounds to the variables
                if (!GetIgnoreBounds(vid))
                {
                    GetBounds(vid, out numLo, out numHi);

                    if (numLo != Rational.NegativeInfinity && numHi != Rational.PositiveInfinity)
                    {
                        lpsolve.set_bounds(_lp, vindex, (double)numLo, (double)numHi);
                    }
                    else if (numLo != Rational.NegativeInfinity)
                    {
                        lpsolve.set_lowbo(_lp, vindex, (double)numLo);
                    }
                    else
                    {
                        lpsolve.set_unbounded(_lp, vindex);
                        if (numHi != Rational.PositiveInfinity)
                        {
                            lpsolve.set_upbo(_lp, vindex, (double)numHi);
                        }
                    }
                }
                else
                {
                    lpsolve.set_unbounded(_lp, vindex);
                }

                _sfsToSolverVarIndex[vid] = vindex;
            }

            //add objective and rows/constraints
            //Sort Rows and Variables by vid so that the order of columns is always same when accessing

            double[] row = new double[VariableIndices.Count()];
            int[] colno = new int[VariableIndices.Count()];
            double coeff;
            ILinearGoal goal;
            bool objective;
            int igoal = 0;
            int cindex;
            int rindex = 0;
            int SOS;
            int NSOS = 0;
            IEnumerable<LinearEntry> rowEntries;

            foreach (int r in RowIndices)
            {
                objective = IsGoal(r, out goal);
                cindex = 0;

                if (objective)
                    SOS = 0;
                else if (IsSOS1Row(r))
                    SOS = 1;
                else if (IsSOS2Row(r))
                    SOS = 2;
                else
                    SOS = 0;

                if (SOS != 0)
                {
                    rowEntries = GetRowEntries(r);
                    int[] sosvars = new int[rowEntries.Count()];
                    double[] weights = new double[rowEntries.Count()];

                    /*
                    foreach (LinearEntry entry in rowEntries)
                    {
                        vindex = 0;
                        foreach (Object key in VariableKeys)
                        {
                            vindex++;
                            vid = GetIndexFromKey(key);
                            if (vid == entry.Index)
                            {
                                weights[cindex] = entry.Value.GetSignedDouble();
                                sosvars[cindex++] = vindex;
                                break;
                            }
                        }

                        //sosvars[cindex++] = entry.Index;
                    }
                    */

                    foreach (LinearEntry entry in rowEntries)
                    {
                        if (_sfsToSolverVarIndex.ContainsKey(entry.Index))
                        {
                            vindex = _sfsToSolverVarIndex[entry.Index];
                            weights[cindex] = entry.Value.GetSignedDouble();
                            sosvars[cindex++] = vindex;
                            //sosvars[cindex++] = entry.Index;
                        }
                    }
                    cindex = lpsolve.add_SOS(_lp, null, SOS, ++NSOS, cindex, sosvars, weights);
                }
                else
                {
                    vindex = 0;
                    foreach (int c in VariableIndices)
                    {
                        cindex++;
                        coeff = GetCoefficient(r, c).ToDouble();
                        if (coeff != 0.0)
                        {
                            colno[vindex] = cindex;
                            row[vindex++] = coeff;
                        }
                    }

                    if (objective)
                    {
                        //Only one goal is allowed in LPSolve
                        if (++igoal == 1)
                        {
                            //objective function to be minimized/maximized
                            lpsolve.set_sense(_lp, (byte) (goal.Minimize ? 0 : 1));
                            lpsolve.set_obj_fnex(_lp, vindex, row, colno);
                        }
                    }
                    else
                    {                         
                        rindex++;
                        GetBounds(r, out numLo, out numHi);
                        if (numLo == numHi)
                        {
                            lpsolve.add_constraintex(_lp, vindex, row, colno, lpsolve.lpsolve_constr_types.EQ, numLo.ToDouble());
                        }
                        else
                        {
                            if (numLo != Rational.NegativeInfinity && numHi != Rational.PositiveInfinity)
                            {
                                lpsolve.add_constraintex(_lp, vindex, row, colno, lpsolve.lpsolve_constr_types.LE, numHi.ToDouble());
                                lpsolve.set_rh_range(_lp, rindex, (double)(numHi - numLo));
                            }
                            else if (numLo != Rational.NegativeInfinity)
                            {
                                lpsolve.add_constraintex(_lp, vindex, row, colno, lpsolve.lpsolve_constr_types.GE, numLo.ToDouble());
                            }
                            else if (numHi != Rational.PositiveInfinity)
                            {
                                lpsolve.add_constraintex(_lp, vindex, row, colno, lpsolve.lpsolve_constr_types.LE, numHi.ToDouble());
                            }
                        }

                        _sfsToSolverRowMapping[r] = rindex;

#if MSF_2_0_3
                        //lpsolve.set_row_name(_lp, rindex, r.ToString());
#else
                        //lpsolve.set_row_name(_lp, rindex, GetKeyFromIndex(r).ToString());
#endif
                    }
                }
            }

            lpsolve.set_add_rowmode(_lp, 0);
        }

        private void LoadLpSolveResults()
        {
            //Assign values to the variables/constraints/Goal
            List<int> varIds = VariableIndices.ToList();
            List<int> rowIds = RowIndices.ToList();
            int lpOrigRCount = lpsolve.get_Norig_rows(_lp);
            int lpOrigVCount = lpsolve.get_Norig_columns(_lp);
            int lpRowCount = lpsolve.get_Nrows(_lp);
            int index = lpRowCount;
            double value;
            double[] lpSol = new double[1 + lpOrigRCount + lpOrigVCount];

            if (lpsolve.get_primal_solution(_lp, lpSol) != 0)
            {
                foreach (int vid in varIds)
                {
                    value = lpSol[++index];
                    SetValue(vid, (Rational)value);
                }
            }

            index = 0;
            foreach (int vid in rowIds)
            {
                if (!IsGoal(vid))
                {
                    SetValue(vid, (Rational)lpSol[++index]);
                }
            }

            foreach (int vid in rowIds)
            {
                if (IsGoal(vid))
                {
                    value = lpsolve.get_objective(_lp);
                    SetValue(vid, (Rational)value);
                    break;
                }
            }
        }

        private int LpAbortFunc(int lp, int userhandle)
        {
            _state = (int)SolverState.Aborting;
            return (int)((_queryAbortFunc != null && _queryAbortFunc()) ? 1 : 0);
        }

#if MSF_2_0_3

        public virtual void LpSolveLogFunc(int lp, int userhandle, string buffer)
        {
            if (_LpSolveLogFunc != null)
                _LpSolveLogFunc(lp, userhandle, buffer);
        }


        public virtual void LpSolveMsgFunc(int lp, int userhandle, lpsolve.lpsolve_msgmask message)
        {
            if (_LpSolveMsgFunc != null)
                _LpSolveMsgFunc(lp, userhandle, message);
            if (_solvingEventFunc != null)
                _solvingEventFunc();
        }
#endif

        public ILinearSolution Solve(ISolverParameters param)
        {
            try
            {
                //If the PlugIn is shutting down or shutdown, stop solving
                //Remarks:a-pavans:This is not needed, but to avoid the CompareExchange and better readability
                if ((SolverState)_state == SolverState.Disposing || (SolverState)_state == SolverState.Disposed)
                    return this;

                //Initiaze the solver
                //If the current state is Start, then initialize the solver
                while (Interlocked.CompareExchange(ref _state, (int)SolverState.Solving, (int)SolverState.Start) == (int)SolverState.Start) ;
                //If the state is solving, start solving
                if ((SolverState)_state == SolverState.Solving)
                {
                    //_solverFinished.Reset();
                    LpSolveParams prms = param as LpSolveParams;
                    if (prms == null)
                        prms = new LpSolveParams();

                    _queryAbortFunc = prms.QueryAbort;
                    _callback = new lpsolve.ctrlcfunc(LpAbortFunc);

                    lpsolve.Init(".");
                    _GetSensitivity = prms._GetSensitivity;
                    LoadLpsolveModel();

                    lpsolve.set_anti_degen(_lp, prms._LpSolveAntiDegen);
                    lpsolve.set_basiscrash(_lp, prms._LpSolveBasiscrash);
                    lpsolve.set_bb_depthlimit(_lp, prms._LpSolveBbDepthlimit);
                    lpsolve.set_bb_floorfirst(_lp, prms._LpSolveBbFloorfirst);
                    lpsolve.set_bb_rule(_lp, prms._LpSolveBbRule);
                    lpsolve.set_break_at_first(_lp, (byte) (prms._LpSolveBreakAtFirst ? 1 : 0));
                    lpsolve.set_break_at_value(_lp, prms._LpSolveBreakAtValue);
                    lpsolve.set_debug(_lp, (byte) (prms._LpSolveDebug ? 1 : 0));
                    lpsolve.set_epsb(_lp, prms._LpSolveEpsb);
                    lpsolve.set_epsd(_lp, prms._LpSolveEpsd);
                    lpsolve.set_epsel(_lp, prms._LpSolveEpsel);
                    lpsolve.set_epsint(_lp, prms._LpSolveEpsint);
                    lpsolve.set_epsperturb(_lp, prms._LpSolveEpsperturb);
                    lpsolve.set_epspivot(_lp, prms._LpSolveEpspivot);
                    lpsolve.set_improve(_lp, prms._LpSolveImprove);
                    lpsolve.set_infinite(_lp, prms._LpSolveInfinite);
                    lpsolve.set_maxpivot(_lp, prms._LpSolveMaxpivot);
                    lpsolve.set_mip_gap(_lp, 1, prms._LpSolveMipGapAbs);
                    lpsolve.set_mip_gap(_lp, 0, prms._LpSolveMipGapRel);
                    lpsolve.set_negrange(_lp, prms._LpSolveNegrange);
                    if (prms._LpSolveObjBound < prms._LpSolveInfinite)
                        lpsolve.set_obj_bound(_lp, prms._LpSolveObjBound);
                    lpsolve.set_obj_in_basis(_lp, (byte) (prms._LpSolveObjInBasis ? 1 : 0));
                    lpsolve.set_pivoting(_lp, prms._LpSolvePivoting);
                    lpsolve.set_presolve(_lp, prms._LpSolvePresolve, prms._LpSolvePresolveMaxLoops);
                    lpsolve.set_scalelimit(_lp, prms._LpSolveScalelimit);
                    lpsolve.set_scaling(_lp, prms._LpSolveScaling);
                    lpsolve.set_simplextype(_lp, prms._LpSolveSimplextype);
                    lpsolve.set_solutionlimit(_lp, prms._LpSolveSolutionlimit);
                    lpsolve.set_timeout(_lp, prms._LpSolveTimeout);
                    lpsolve.set_trace(_lp, (byte) (prms._LpSolveTrace ? 1 : 0));

                    lpsolve.set_outputfile(_lp, prms._LpSolveLogFile);
                    lpsolve.put_abortfunc(_lp, _callback, 0);
#if MSF_2_0_3
                    _LpSolveLogFunc = prms._LpSolveLogFunc;
                    _LpSolveMsgFunc = prms._LpSolveMsgFunc;
                    _solvingEventFunc = prms.Solving;
                    _logfunc = new lpsolve.logfunc(LpSolveLogFunc);
                    lpsolve.put_logfunc(_lp, _logfunc, 0);
                    lpsolve.set_verbose(_lp, /* (_LpSolveLogFunc == null) ? 0 : */ prms._LpSolveVerbose);
                    _msgfunc = new lpsolve.msgfunc(LpSolveMsgFunc);
                    lpsolve.put_msgfunc(_lp, _msgfunc, 0, 1 + 8 + 16 + 32 + 128 + 512);
#endif
                    lpsolve.lpsolve_return lpReturn = lpsolve.solve(_lp);

#if DEBUG
                    //lpsolve.print_objective(_lp);
                    //lpsolve.print_solution(_lp, 1);
                    //lpsolve.print_constraints(_lp, 1);
                    //lpsolve.print_lp(_lp);
                    //lpsolve.print_debugdump(_lp, "debug.txt");
                    //lpsolve.write_lp(_lp, "model.lp");
                    //lpsolve.write_params(_lp, "model.par", "");
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
            catch (Exception ex)
            {
                //Remarks: a-pavans: Not sure what to do in case of exception
                _state = (int)SolverState.Aborted;
                throw;
            }
            return this;
        }

        #region ILinearSolution Members

        public LinearSolutionQuality SolutionQuality
        {
            get
            {
                if (_solutionStatus == (int)lpsolve.lpsolve_return.OPTIMAL)
                    return LinearSolutionQuality.Approximate;
                else
                    return LinearSolutionQuality.None;
            }
        }

        public LinearResult LpResult
        {
            get
            {
                lpsolve.lpsolve_return enumStatus = (lpsolve.lpsolve_return)_solutionStatus;
                lpsolve.lpsolve_simplextypes simplex = lpsolve.get_simplextype(_lp);
                if (simplex == lpsolve.lpsolve_simplextypes.SIMPLEX_PRIMAL_PRIMAL)
                {
                    switch (enumStatus)
                    {
                        case lpsolve.lpsolve_return.OPTIMAL:
                            return LinearResult.Optimal;
                        case lpsolve.lpsolve_return.INFEASIBLE:
                            return LinearResult.InfeasiblePrimal;
                        case lpsolve.lpsolve_return.UNBOUNDED:
                            return LinearResult.UnboundedPrimal;
                        case lpsolve.lpsolve_return.NOMEMORY:
                            return LinearResult.Invalid;
                        case lpsolve.lpsolve_return.TIMEOUT:
                            return LinearResult.Invalid;
                        default:
                            return LinearResult.Invalid;
                    };
                }
                else
                {
                    switch (enumStatus)
                    {
                        case lpsolve.lpsolve_return.OPTIMAL:
                            return LinearResult.Optimal;
                        case lpsolve.lpsolve_return.INFEASIBLE:
                            return LinearResult.InfeasibleOrUnbounded;
                        case lpsolve.lpsolve_return.UNBOUNDED:
                            return LinearResult.UnboundedDual;
                        case lpsolve.lpsolve_return.NOMEMORY:
                            return LinearResult.Invalid;
                        case lpsolve.lpsolve_return.TIMEOUT:
                            return LinearResult.Invalid;
                        default:
                            return LinearResult.Invalid;
                    }
                }
            }
        }

        public LinearResult MipResult
        {
            get
            {
                lpsolve.lpsolve_return enumStatus = (lpsolve.lpsolve_return)_solutionStatus;
                lpsolve.lpsolve_simplextypes simplex = lpsolve.get_simplextype(_lp);

                switch (enumStatus)
                {
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
                        return LinearResult.Invalid;
                    case lpsolve.lpsolve_return.TIMEOUT:
                        return LinearResult.Invalid;
                    default:
                        return LinearResult.Invalid;
                }
            }
        }

        public virtual LinearResult Result
        {
            get
            {
                if (_modelSFS.IsMipModel)
                    return MipResult;
                else
                    return LpResult;
            }
        }

        public int SolvedGoalCount
        {
            get
            {
                if (GoalCount == 0)
                    return 0;
                int solutionCount = lpsolve.get_solutioncount(_lp);
                if (solutionCount > 0)
                    return 1;
                else
                    return 0;
            }
        }

        public void GetSolvedGoal(int igoal, out object key, out int vid, out bool fMinimize, out bool fOptimal)
        {
            //Implemented only one goal right now, it will be the first one
            ILinearGoal goal = Goals.ElementAt(igoal);
            key = goal.Key;
            vid = goal.Index;
            fMinimize = goal.Minimize;
            fOptimal = _solutionStatus == (int)lpsolve.lpsolve_return.OPTIMAL;
        }

        public Rational MipBestBound
        {
            get
            {
                if (_modelSFS.IsMipModel)
                    return lpsolve.get_obj_bound(_lp);
                else
                    return Rational.Indeterminate;
            }
        }

        #endregion

        #region ILinearSimplexStatistics Members

        public int InnerIndexCount
        {
            get
            {
                int rows = lpsolve.get_Nrows(_lp);
                int cols = lpsolve.get_Ncolumns(_lp);
                return rows + cols;
            }
        }

        public int InnerIntegerIndexCount
        {
            get
            {
                int count = 0;
                int Ncolumns = lpsolve.get_Ncolumns(_lp);

                for (int i = 1; i <= Ncolumns; i++)
                {
                    if (lpsolve.is_int(_lp, i) != 0)
                        count++;
                }
                return count;
            }
        }

        public int InnerSlackCount
        {
            get
            {
                return lpsolve.get_Nrows(_lp);
            }
        }

        public int InnerRowCount
        {
            get
            {
                return lpsolve.get_Nrows(_lp);
            }
        }

        public int PivotCount
        {
            get
            {
                return lpsolve.get_maxpivot(_lp);
            }
        }

        public int PivotCountDegenerate
        {
            get { return 0; /*  throw new NotImplementedException(); */ }
        }

        public int PivotCountExact
        {
            get { return 0; /*  throw new NotImplementedException(); */ }
        }

        public int PivotCountExactPhaseOne
        {
            get { return 0; /*  throw new NotImplementedException(); */ }
        }

        public int PivotCountExactPhaseTwo
        {
            get { return 0; /*  throw new NotImplementedException(); */ }
        }

        public int PivotCountDouble
        {
            get { return 0; /*  throw new NotImplementedException(); */ }
        }

        public int PivotCountDoublePhaseOne
        {
            get { return 0; /* throw new NotImplementedException(); */ }
        }

        public int PivotCountDoublePhaseTwo
        {
            get { return 0; /*  throw new NotImplementedException(); */ }
        }

        public int FactorCount
        {
            get
            {
                return 0; /* throw new NotImplementedException(); */
            }
        }

        public int FactorCountExact
        {
            get { return 0; /*  throw new NotImplementedException(); */ }
        }

        public int FactorCountDouble
        {
            get { return 0; /*  throw new NotImplementedException(); */ }
        }

        public int BranchCount
        {
            get
            {
                return (int)lpsolve.get_total_nodes(_lp);
            }
        }

        public Rational Gap
        {
            get
            {
                return lpsolve.get_mip_gap(_lp, 1);
            }
        }

        public bool UseExact
        {
            get
            {
                return false;
            }
            set
            {
                if (value)
                {
                    throw new NotImplementedException();
                }
            }
        }

        public bool UseDouble
        {
            get
            {
                return true;
            }
            set
            {
            }
        }

        public Microsoft.SolverFoundation.Solvers.SimplexAlgorithmKind AlgorithmUsed
        {
            get
            {
                lpsolve.lpsolve_simplextypes simplex = lpsolve.get_simplextype(_lp);
                Microsoft.SolverFoundation.Solvers.SimplexAlgorithmKind algorithm = Microsoft.SolverFoundation.Solvers.SimplexAlgorithmKind.Dual;
                if (simplex == lpsolve.lpsolve_simplextypes.SIMPLEX_PRIMAL_PRIMAL || simplex == lpsolve.lpsolve_simplextypes.SIMPLEX_DUAL_PRIMAL)
                    algorithm = Microsoft.SolverFoundation.Solvers.SimplexAlgorithmKind.Primal;
                if (simplex == lpsolve.lpsolve_simplextypes.SIMPLEX_DUAL_DUAL || simplex == lpsolve.lpsolve_simplextypes.SIMPLEX_PRIMAL_DUAL)
                    algorithm = Microsoft.SolverFoundation.Solvers.SimplexAlgorithmKind.Dual;
                return algorithm;
            }
        }

        public Microsoft.SolverFoundation.Solvers.SimplexCosting CostingUsedExact
        {
            get
            {
                return Microsoft.SolverFoundation.Solvers.SimplexCosting.Default;
            }
            set
            {
            }
        }

        public Microsoft.SolverFoundation.Solvers.SimplexCosting CostingUsedDouble
        {
            get
            {
                return Microsoft.SolverFoundation.Solvers.SimplexCosting.Default;
            }
            set
            {
            }
        }

        #endregion

        protected bool IsSOS1Row(int vidRow)
        {
            if (_vidRowSOS1 == null)
            {
                IEnumerable<int> SOS1Rows = _modelSFS.GetSpecialOrderedSetTypeRowIndexes(SpecialOrderedSetType.SOS1).ToList<int>();
                if (SOS1Rows == null)
                    return false;
                _vidRowSOS1 = SOS1Rows.ToList<int>();
            }
            return _vidRowSOS1.Contains(vidRow);
        }

        protected bool IsSOS2Row(int vidRow)
        {
            if (_vidRowSOS2 == null)
            {
                IEnumerable<int> SOS2Rows = _modelSFS.GetSpecialOrderedSetTypeRowIndexes(SpecialOrderedSetType.SOS2).ToList<int>();
                if (SOS2Rows == null)
                    return false;
                _vidRowSOS2 = SOS2Rows.ToList<int>();
            }
            return _vidRowSOS2.Contains(vidRow);
        }

        /*
        protected int SOSRowCount
        {
            get
            {
                if (!IsSpecialOrderedSet)
                {
                    return 0;
                }
                else
                {
                    IEnumerable<int> SOS2Rows = _modelSFS.GetSpecialOrderedSetTypeRowIndexes(SpecialOrderedSetType.SOS2).ToList<int>();
                    IEnumerable<int> SOS1Rows = _modelSFS.GetSpecialOrderedSetTypeRowIndexes(SpecialOrderedSetType.SOS1).ToList<int>();

                    return SOS2Rows.Count() + SOS1Rows.Count();
                }
            }
        }
        */

        #region ILinearSolver Members

        /// <summary>
        /// Reports Infeasbility and Sensitivity
        /// </summary>
        /// <param name="reportType"></param>
        /// <returns></returns>
        public ILinearSolverReport GetReport(LinearSolverReportType reportType)
        {
#if MSF_2_0_3
            if (reportType == LinearSolverReportType.Sensitivity)
                if (((LpSolveSolver)this)._GetSensitivity)
                    return (ILinearSolverSensitivityReport)this;
                else
                    return null;
            //else if (reportType == LinearSolverReportType.Infeasibility)
            //    return (ILinearSolverInfeasibilityReport)this;
            else
                return null;


#else
            return new LpSolveMPReport();
#endif
        }

        public Rational GetSolutionValue(int goalIndex)
        {
            return GetValue(goalIndex);
        }

        ILinearSolution ILinearSolver.Solve(ISolverParameters parameters)
        {
            Solve(parameters);
            return this;
        }

        #endregion

#if MSF_2_0_3
        #region ISolverProperties Members

        public void SetProperty(string propertyName, int vid, object value)
        {
            if (propertyName == SolverProperties.VariableLowerBound)
            {
                _modelSFS.SetProperty(propertyName, vid, value);
            }
            else if (propertyName == SolverProperties.VariableUpperBound)
            {
                _modelSFS.SetProperty(propertyName, vid, value);
            }
            else
            {
                throw new NotSupportedException("Currently this property is not supported");
            }
        }

        public object GetProperty(string property, int vid)
        {
            if (property == SolverProperties.IterationCount)
            {
                long iterCount = LpSolveNativeInterface.lpsolve.get_total_iter(_lp);
                return iterCount;
            }
            else if (property == LpSolveProperties.ExploredNodeCount)
            {
                long nodeCount = LpSolveNativeInterface.lpsolve.get_total_nodes(_lp);
                return nodeCount;
            }

            else if (property == LpSolveProperties.GoalBound)
            {
                double objBound = LpSolveNativeInterface.lpsolve.get_obj_bound(_lp);
                return objBound;
            }
            else if (property == SolverProperties.GoalValue)
            {
                double objective = LpSolveNativeInterface.lpsolve.get_working_objective(_lp);
                return objective;
            }
            else if (property == SimplexProperties.PivotCount)
            {
                return LpSolveNativeInterface.lpsolve.get_maxpivot(_lp);
            }
            else if (property == LpSolveProperties.ElapsedTime)
            {
                double elapsed = LpSolveNativeInterface.lpsolve.time_elapsed(_lp);
                return elapsed;
            }
            else if (property == LpSolveProperties.PresolveLoops)
            {
                return LpSolveNativeInterface.lpsolve.get_presolveloops(_lp);
            }
            else if (property == SimplexProperties.MipGap)
            {
                return LpSolveNativeInterface.lpsolve.get_mip_gap(_lp, 1);
            }
            else if (property == SolverProperties.VariableLowerBound)
            {
                return _modelSFS.GetProperty(property, vid);
            }
            else if (property == SolverProperties.VariableUpperBound)
            {
                return _modelSFS.GetProperty(property, vid);
            }
            else if (property == SimplexProperties.MipGap)
            {
                return LpSolveNativeInterface.lpsolve.get_mip_gap(_lp, 1);
            }
            else
                throw new NotSupportedException("Currently this property is not supported");
        }

        #endregion

        #region IReportProvider Members

        public Report GetReport(SolverContext context, Solution solution, SolutionMapping solutionMapping)
        {
            LinearSolutionMapping lpSolutionMapping = solutionMapping as LinearSolutionMapping;

            if (lpSolutionMapping == null && solutionMapping != null)
                throw new ArgumentException("solutionMapping is not a LinearSolutionMapping", "solutionMapping");
            
            return new LpSolveReport(context, this, solution, lpSolutionMapping);
        }

        #endregion

        #region ILinearSolverInfeasibilityReport Members

        public IEnumerable<int> IrreducibleInfeasibleSet
        {
            get
            {
                return null;
            }
        }

        #endregion

        #region ILinearSolverSensitivityReport Members

        /// <summary>
        /// Write LPSolve parameters to a file
        /// </summary>
        /// <param name="filename"></param>
        /// <param name="options"></param>
        public void LpSolveWriteParams(string filename, string options)
        {
            lpsolve.write_params(_lp, filename, options);
        }

        /// <summary>
        /// Write LPSolve model in MPS format to a file
        /// </summary>
        /// <param name="filename"></param>
        /// <param name="free"></param>
        /// <returns></returns>
        public bool LpSolveWriteMPS(string filename, bool free)
        {
            int ret;

            if (free)
                ret = lpsolve.write_freemps(_lp, filename);
            else
                ret = lpsolve.write_mps(_lp, filename);

            return ret != 0;
        }

        /// <summary>
        /// Write LPSolve model in LP format to a file
        /// </summary>
        /// <param name="filename"></param>
        /// <returns></returns>
        public bool LpSolveWriteLp(string filename)
        {
            return lpsolve.write_lp(_lp, filename) != 0;
        }

        /// <summary>
        /// Write LPSolve model via an XLI to a file
        /// </summary>
        /// <param name="XLIname"></param>
        /// <param name="filename"></param>
        /// <param name="options"></param>
        /// <param name="results"></param>
        /// <returns></returns>
        public bool LpSolveWriteXLI(string XLIname, string filename, string options, bool results)
        {
            bool ret = false;

            if (lpsolve.set_XLI(_lp, XLIname) != 0)
                if (lpsolve.write_XLI(_lp, filename, options, (byte)(results ? 1 : 0)) != 0)
                    ret = true;

            return ret;
        }

        /// <summary>
        /// Write LPSolve debug dump to a file
        /// </summary>
        /// <param name="filename"></param>
        /// <returns></returns>
        public bool LpSolvePrintDebugDump(string filename)
        {
            return lpsolve.print_debugdump(_lp, filename) != 0;
        }

        public Rational GetDualValue(int id)
        {
            int index = -1;

            if (_sfsToSolverRowMapping.ContainsKey(id))
                index = _sfsToSolverRowMapping[id];
            else if (_sfsToSolverVarIndex.ContainsKey(id))
                index = _sfsToSolverVarIndex[id] + LpSolveNativeInterface.lpsolve.get_Nrows(_lp);
            if (index >= 0)
            {
                double value = LpSolveNativeInterface.lpsolve.get_var_dualresult(_lp, index);
                return value;
            }
            else
                return 0.0;
        }

        unsafe private LinearSolverSensitivityRange GetObjectiveCoefficientRangeUnsafe(int vid, out Rational fromvalue, out Rational tillvalue)
        {
            LinearSolverSensitivityRange range = new LinearSolverSensitivityRange();

            fromvalue = Rational.NegativeInfinity;
            tillvalue = Rational.PositiveInfinity;
            if (_sfsToSolverVarIndex.ContainsKey(vid))
            {
                int index = _sfsToSolverVarIndex[vid];
                double* lowers = null;
                double* uppers = null;
                double* objfromvalue = null;
                double* objtillvalue = null;

                LpSolveNativeInterface.lpsolve.get_ptr_sensitivity_objex(_lp, ref lowers, ref uppers, ref objfromvalue, ref objtillvalue);
                range.Current = LpSolveNativeInterface.lpsolve.get_mat(_lp, 0, index) /* LpSolveNativeInterface.lpsolve.get_var_primalresult(_lp, LpSolveNativeInterface.lpsolve.get_Norig_rows(_lp) + index) */;
                if ((lowers == null) || ((range.Lower = lowers[index - 1]) <= -_infinite))
                    range.Lower = Rational.NegativeInfinity;
                if ((lowers == null) || ((range.Upper = uppers[index - 1]) >= _infinite))
                    range.Upper = Rational.PositiveInfinity;
                if ((objfromvalue == null) || ((fromvalue = objfromvalue[index - 1]) <= -_infinite))
                    fromvalue = Rational.NegativeInfinity;
                if ((objtillvalue == null) || ((tillvalue = objtillvalue[index - 1]) >= _infinite))
                    tillvalue = Rational.PositiveInfinity;
            }
            return range;
        }

        public LinearSolverSensitivityRange GetObjectiveCoefficientRange(int vid)
        {
            Rational fromvalue;
            Rational tillvalue;

            return GetObjectiveCoefficientRangeUnsafe(vid, out fromvalue, out tillvalue);
        }

        public LinearSolverSensitivityRange GetObjectiveCoefficientRange(int vid, int pri)
        {
            return GetObjectiveCoefficientRange(vid);
        }

        unsafe private LinearSolverSensitivityRange GetVariableRangeUnsafe(int id)
        {
            LinearSolverSensitivityRange range = new LinearSolverSensitivityRange();
            int index = -1;
            bool IsVariable = false;

            if (_sfsToSolverRowMapping.ContainsKey(id))
            {
                index = _sfsToSolverRowMapping[id];
            }
            else if (_sfsToSolverVarIndex.ContainsKey(id))
            {
                index = _sfsToSolverVarIndex[id];
                IsVariable = true;
            }

            if (index >= 0)
            {
                double* duals = null;
                double* lowers = null;
                double* uppers = null;

                LpSolveNativeInterface.lpsolve.get_ptr_sensitivity_rhs(_lp, ref duals, ref lowers, ref uppers);

                if (duals != null)
                {
                    double sign = LpSolveNativeInterface.lpsolve.is_maxim(_lp) != 0 ? -1.0 : +1.0;

                    if (IsVariable)
                    {
                        double lowbo = LpSolveNativeInterface.lpsolve.get_lowbo(_lp, index);
                        double upbo = LpSolveNativeInterface.lpsolve.get_upbo(_lp, index);

                        index += LpSolveNativeInterface.lpsolve.get_Nrows(_lp);

                        if (duals[index - 1] * sign >= 0.0)
                        {
                            range.Current = lowbo;
                        }
                        else
                        {
                            range.Current = lowbo + upbo;
                        }
                    }
                    else
                    {
                        LpSolveNativeInterface.lpsolve.lpsolve_constr_types constr_type = LpSolveNativeInterface.lpsolve.get_constr_type(_lp, index);
                        double rh_range = LpSolveNativeInterface.lpsolve.get_rh_range(_lp, index);

                        range.Current = LpSolveNativeInterface.lpsolve.get_rh(_lp, index);
                        if (duals[index - 1] * sign >= 0.0)
                        {
                            if ((constr_type == lpsolve.lpsolve_constr_types.LE) && (rh_range < _infinite))
                                range.Current -= rh_range;
                        }
                        else
                        {
                            if ((constr_type == lpsolve.lpsolve_constr_types.GE) && (rh_range < _infinite))
                                range.Current += rh_range;
                        }
                    }
                }

                if ((lowers == null) || ((range.Lower = lowers[index - 1]) <= -_infinite))
                    range.Lower = Rational.NegativeInfinity;
                if ((lowers == null) || ((range.Upper = uppers[index - 1]) >= _infinite))
                    range.Upper = Rational.PositiveInfinity;
            }

            return range;
        }

        public LinearSolverSensitivityRange GetVariableRange(int id)
        {
            return GetVariableRangeUnsafe(id);
        }

        /* lpsolve additions */

        internal LinearSolverSensitivityRange? GetDecisionBoundsSensitivity(LinearSolutionMapping _solutionMapping, Decision decision, params object[] indexes)
        {
            int vid;
            LinearSolverSensitivityRange? VariableRange;

            if (_solutionMapping.TryGetVid(decision, indexes, out vid))
                VariableRange = GetVariableRangeUnsafe(vid);
            else
                VariableRange = null;

            return VariableRange;
        }

        internal Rational? GetDecisionShadowPrice(LinearSolutionMapping _solutionMapping, Decision decision, params object[] indexes)
        {
            int vid;
            Rational? DualValue;

            if (_solutionMapping.TryGetVid(decision, indexes, out vid))
                DualValue = GetDualValue(vid);
            else
                DualValue = null;

            return DualValue;
        }

        internal Rational GetGoalCoefficientSensitivity(LinearSolutionMapping _solutionMapping, Decision decision, params object[] indexes)
        {
            int vid;
            Rational fromvalue, tillvalue;

            if (_solutionMapping.TryGetVid(decision, indexes, out vid))
            {
                GetObjectiveCoefficientRangeUnsafe(vid, out fromvalue, out tillvalue);
                return fromvalue;
            }
            else
            {
                return Rational.NegativeInfinity;
            }
        }

        unsafe internal List<KeyValuePair<string, Rational>> GetAllConstraintValues(LinearSolutionMapping _solutionMapping)
        {
            List<KeyValuePair<string, Rational>> ConstraintValues = new List<KeyValuePair<string, Rational>>();
            ILinearGoal goal;
            double* constr = null;

            LpSolveNativeInterface.lpsolve.get_ptr_constraints(_lp, ref constr); 
            foreach (int r in RowIndices)
            {
                if (!IsGoal(r, out goal))
                {
                    Constraint constraint;
                    object[] indexes;
                    int component;
                    int index;

                    if (_solutionMapping.TryGetConstraint(r, out constraint, out indexes, out component))
                    {
                        if (_sfsToSolverRowMapping.ContainsKey(r))
                        {
                            index = _sfsToSolverRowMapping[r];
                            KeyValuePair<string, Rational> ConstraintValue = new KeyValuePair<string, Rational>(constraint.Name, constr[index - 1]);
                            ConstraintValues.Add(ConstraintValue);
                        }
                    }
                }
            }

            return ConstraintValues;
        }
        #endregion
#endif

    }

#if MSF_2_0_3
    public static class LpSolveProperties
    {
        public static string ElapsedTime = "ElapsedTime";
        public static string PresolveLoops = "PresolveLoops";
        public static string ExploredNodeCount = "NodeCount";
        public static string GoalBound = "GoalBound";
    }

    public class LpSolveReport : LinearReport
    {

        private LpSolveSolver _lpsolver;
        private LinearSolutionMapping _solutionMapping;

        public LpSolveReport(SolverContext context, ISolver solver, Solution solution, LinearSolutionMapping solutionMapping)
            : base(context, solver, solution, solutionMapping)
        {
            _lpsolver = (LpSolveSolver)solver;
            _solutionMapping = solutionMapping;            
        }

        public int Presolve_Loops
        {
            get
            {
                ValidateSolution();
                return Convert.ToInt32(_lpsolver.GetProperty(LpSolveProperties.PresolveLoops, -1));
            }
        }

        public int IterationCount
        {
            get
            {
                ValidateSolution();
                return Convert.ToInt32(_lpsolver.GetProperty(SolverProperties.IterationCount, -1));
            }
        }

        public int NodeCount
        {
            get
            {
                ValidateSolution();
                return Convert.ToInt32(_lpsolver.GetProperty(LpSolveProperties.ExploredNodeCount, -1));
            }
        }

        public int PivotCount
        {
            get
            {
                ValidateSolution();
                return Convert.ToInt32(_lpsolver.GetProperty(SimplexProperties.PivotCount, -1));
            }
        }

        protected override void GenerateReportSolverDetails(StringBuilder reportBuilder, IFormatProvider formatProvider)
        {
            reportBuilder.AppendLine(string.Format(formatProvider, "===SolverDetails===="));
            reportBuilder.AppendLine(string.Format(formatProvider, "Iteration Count:{0}", IterationCount));
            reportBuilder.AppendLine(string.Format(formatProvider, "Presolve loops:{0}", Presolve_Loops));
            if (base.SolverCapability == SolverCapability.LP)
            {
                reportBuilder.AppendLine(string.Format(formatProvider, "Pivot count:{0}", PivotCount));
            }
            if (base.SolverCapability == SolverCapability.MILP)
            {
                reportBuilder.AppendLine(string.Format(formatProvider, "Node Count:{0}", NodeCount));
            }
            reportBuilder.AppendLine(string.Format(formatProvider, "===Model details==="));
            reportBuilder.AppendLine(string.Format(formatProvider, "Variables:{0}", base.OriginalVariableCount));
            reportBuilder.AppendLine(string.Format(formatProvider, "Rows:{0}", base.OriginalRowCount));
            reportBuilder.AppendLine(string.Format(formatProvider, "Non-zeros:{0}", base.NonzeroCount));
            base.GenerateReportSolverDetails(reportBuilder, formatProvider);
        }

        /* lpsolve additions */

        /// <summary>
        /// Get the sensitivity range of a decision
        /// </summary>
        /// <param name="decision">The decision of interest</param>
        /// <param name="indexes"></param>
        /// <returns></returns>
        public LinearSolverSensitivityRange? GetDecisionBoundsSensitivity(Decision decision, params object[] indexes)
        {
            return _lpsolver.GetDecisionBoundsSensitivity(_solutionMapping, decision, indexes);
        }

        /// <summary>
        /// Get the shadow price of a decision
        /// </summary>
        /// <param name="decision">The decision of interest</param>
        /// <param name="indexes"></param>
        /// <returns></returns>
        public Rational? GetDecisionShadowPrice(Decision decision, params object[] indexes)
        {
            return _lpsolver.GetDecisionShadowPrice(_solutionMapping, decision, indexes);
        }

        /// <summary>
        /// Get goal sensitivity from value of a decision
        /// </summary>
        /// <param name="decision">The decision of interest</param>
        /// <param name="indexes"></param>
        /// <returns></returns>
        public Rational GetGoalCoefficientSensitivityFromValue(Decision decision, params object[] indexes)
        {
            return _lpsolver.GetGoalCoefficientSensitivity(_solutionMapping, decision, indexes);
        }

        /// <summary>
        /// Get actual values of all constraints
        /// </summary>
        /// <returns></returns>
        public List<KeyValuePair<string, Rational>> GetAllConstraintValues()
        {
            return _lpsolver.GetAllConstraintValues(_solutionMapping);
        }

        /// <summary>
        /// Write LPSolve parameters to a file
        /// </summary>
        /// <param name="filename"></param>
        /// <param name="options"></param>
        public void LpSolveWriteParams(string filename, string options)
        {
            _lpsolver.LpSolveWriteParams(filename, options);
        }

        /// <summary>
        /// Write LPSolve model in MPS format to a file
        /// </summary>
        /// <param name="filename"></param>
        /// <param name="free"></param>
        /// <returns></returns>
        public bool LpSolveWriteMPS(string filename, bool free)
        {
            return _lpsolver.LpSolveWriteMPS(filename, free);
        }

        /// <summary>
        /// Write LPSolve model in LP format to a file
        /// </summary>
        /// <param name="filename"></param>
        /// <returns></returns>
        public bool LpSolveWriteLp(string filename)
        {
            return _lpsolver.LpSolveWriteLp(filename);
        }

        /// <summary>
        /// Write LPSolve model via an XLI to a file
        /// </summary>
        /// <param name="XLIname"></param>
        /// <param name="filename"></param>
        /// <param name="options"></param>
        /// <param name="results"></param>
        /// <returns></returns>
        public bool LpSolveWriteXLI(string XLIname, string filename, string options, bool results)
        {
            return _lpsolver.LpSolveWriteXLI(XLIname, filename, options, results);
        }

        /// <summary>
        /// Write LPSolve debug dump to a file
        /// </summary>
        /// <param name="filename"></param>
        /// <returns></returns>
        public bool LpSolvePrintDebugDump(string filename)
        {
            return _lpsolver.LpSolvePrintDebugDump(filename);
        }
    }
#endif

    public class LpSolveMPReport : ILinearSolverReport
    {

    }

    public class LpSolveParams : ISolverParameters
#if MSF_2_0_3
, ISolverEvents
#endif
    {
        internal lpsolve.lpsolve_anti_degen _LpSolveAntiDegen;
        internal lpsolve.lpsolve_basiscrash _LpSolveBasiscrash;
        internal int _LpSolveBbDepthlimit;
        internal lpsolve.lpsolve_branch _LpSolveBbFloorfirst;
        internal lpsolve.lpsolve_BBstrategies _LpSolveBbRule;
        internal bool _LpSolveBreakAtFirst;
        internal double _LpSolveBreakAtValue;
        internal bool _LpSolveDebug;
        internal double _LpSolveEpsb;
        internal double _LpSolveEpsd;
        internal double _LpSolveEpsel;
        internal double _LpSolveEpsint;
        internal double _LpSolveEpsperturb;
        internal double _LpSolveEpspivot;
        internal lpsolve.lpsolve_improves _LpSolveImprove;
        internal double _LpSolveInfinite;
        internal int _LpSolveMaxpivot;
        internal double _LpSolveMipGapAbs;
        internal double _LpSolveMipGapRel;
        internal double _LpSolveNegrange;
        internal double _LpSolveObjBound;
        internal bool _LpSolveObjInBasis;
        internal lpsolve.lpsolve_piv_rules _LpSolvePivoting;
        internal lpsolve.lpsolve_presolve _LpSolvePresolve;
        internal int _LpSolvePresolveMaxLoops;
        internal double _LpSolveScalelimit;
        internal lpsolve.lpsolve_scales _LpSolveScaling;
        internal lpsolve.lpsolve_simplextypes _LpSolveSimplextype;
        internal int _LpSolveSolutionlimit;
        internal int _LpSolveTimeout;
        internal bool _LpSolveTrace;
        internal int _LpSolveVerbose;
        internal LpSolveLogFunc _LpSolveLogFunc;
        internal LpSolveMsgFunc _LpSolveMsgFunc;

        internal int TimeLimit;
        internal string _LpSolveLogFile;
        internal bool _GetSensitivity;
        private bool _fAbort;
        private Func<bool> _fnQueryAbort = null;

        //public bool GetSensitivity { get; set; }

        private void InitLpSolveParams(Directive directive)
        {
            LpSolveDirective lpDirective = directive as LpSolveDirective;

            if (lpDirective == null)
                lpDirective = new LpSolveDirective();

            _LpSolveAntiDegen = lpDirective.LpSolveAntiDegen;
            _LpSolveBasiscrash = lpDirective.LpSolveBasiscrash;
            _LpSolveBbDepthlimit = lpDirective.LpSolveBbDepthlimit;
            _LpSolveBbFloorfirst = lpDirective.LpSolveBbFloorfirst;
            _LpSolveBbRule = lpDirective.LpSolveBbRule;
            _LpSolveBreakAtFirst = lpDirective.LpSolveBreakAtFirst;
            _LpSolveBreakAtValue = lpDirective.LpSolveBreakAtValue;
            _LpSolveDebug = lpDirective.LpSolveDebug;
            _LpSolveEpsb = lpDirective.LpSolveEpsb;
            _LpSolveEpsd = lpDirective.LpSolveEpsd;
            _LpSolveEpsel = lpDirective.LpSolveEpsel;
            _LpSolveEpsint = lpDirective.LpSolveEpsint;
            _LpSolveEpsperturb = lpDirective.LpSolveEpsperturb;
            _LpSolveEpspivot = lpDirective.LpSolveEpspivot;
            _LpSolveImprove = lpDirective.LpSolveImprove;
            _LpSolveInfinite = lpDirective.LpSolveInfinite;
            _LpSolveMaxpivot = lpDirective.LpSolveMaxpivot;
            _LpSolveMipGapAbs = lpDirective.LpSolveMipGapAbs;
            _LpSolveMipGapRel = lpDirective.LpSolveMipGapRel;
            _LpSolveNegrange = lpDirective.LpSolveNegrange;
            _LpSolveObjBound = lpDirective.LpSolveObjBound;
            _LpSolveObjInBasis = lpDirective.LpSolveObjInBasis;
            _LpSolvePivoting = lpDirective.LpSolvePivoting;
            _LpSolvePresolve = lpDirective.LpSolvePresolve;
            _LpSolvePresolveMaxLoops = lpDirective.LpSolvePresolveMaxLoops;
            _LpSolveScalelimit = lpDirective.LpSolveScalelimit;
            _LpSolveScaling = lpDirective.LpSolveScaling;
            _LpSolveSimplextype = lpDirective.LpSolveSimplextype;
            _LpSolveSolutionlimit = lpDirective.LpSolveSolutionlimit;
            _LpSolveTimeout = lpDirective.LpSolveTimeout;
            _LpSolveTrace = lpDirective.LpSolveTrace;
            _LpSolveVerbose = lpDirective.LpSolveVerbose;
            _LpSolveLogFunc = lpDirective.LpSolveLogFunc;
            _LpSolveMsgFunc = lpDirective.LpSolveMsgFunc;

            TimeLimit = lpDirective.TimeLimit;
            _LpSolveLogFile = lpDirective.LpSolveLogFile;
            _GetSensitivity = lpDirective.GetSensitivity;
        }

        public LpSolveParams() : this((Func<bool>)null) { }

        /// <summary> construct a solver parameter object
        /// </summary>
        public LpSolveParams(Func<bool> fnQueryAbort)
        {
            InitLpSolveParams(null);
            _fnQueryAbort = fnQueryAbort;
        }

        /// <summary> copy constructor
        /// </summary>
        public LpSolveParams(LpSolveParams prms)
        {
            _LpSolveAntiDegen = prms._LpSolveAntiDegen;
            _LpSolveBasiscrash = prms._LpSolveBasiscrash;
            _LpSolveBbDepthlimit = prms._LpSolveBbDepthlimit;
            _LpSolveBbFloorfirst = prms._LpSolveBbFloorfirst;
            _LpSolveBbRule = prms._LpSolveBbRule;
            _LpSolveBreakAtFirst = prms._LpSolveBreakAtFirst;
            _LpSolveBreakAtValue = prms._LpSolveBreakAtValue;
            _LpSolveDebug = prms._LpSolveDebug;
            _LpSolveEpsb = prms._LpSolveEpsb;
            _LpSolveEpsd = prms._LpSolveEpsd;
            _LpSolveEpsel = prms._LpSolveEpsel;
            _LpSolveEpsint = prms._LpSolveEpsint;
            _LpSolveEpsperturb = prms._LpSolveEpsperturb;
            _LpSolveEpspivot = prms._LpSolveEpspivot;
            _LpSolveImprove = prms._LpSolveImprove;
            _LpSolveInfinite = prms._LpSolveInfinite;
            _LpSolveMaxpivot = prms._LpSolveMaxpivot;
            _LpSolveMipGapAbs = prms._LpSolveMipGapAbs;
            _LpSolveMipGapRel = prms._LpSolveMipGapRel;
            _LpSolveNegrange = prms._LpSolveNegrange;
            _LpSolveObjBound = prms._LpSolveObjBound;
            _LpSolveObjInBasis = prms._LpSolveObjInBasis;
            _LpSolvePivoting = prms._LpSolvePivoting;
            _LpSolvePresolve = prms._LpSolvePresolve;
            _LpSolvePresolveMaxLoops = prms._LpSolvePresolveMaxLoops;
            _LpSolveScalelimit = prms._LpSolveScalelimit;
            _LpSolveScaling = prms._LpSolveScaling;
            _LpSolveSimplextype = prms._LpSolveSimplextype;
            _LpSolveSolutionlimit = prms._LpSolveSolutionlimit;
            _LpSolveTimeout = prms._LpSolveTimeout;

            TimeLimit = prms.TimeLimit;
            _LpSolveTrace = prms._LpSolveTrace;
            _LpSolveVerbose = prms._LpSolveVerbose;
            _LpSolveLogFunc = prms._LpSolveLogFunc;
            _LpSolveMsgFunc = prms._LpSolveMsgFunc;

            _fAbort = prms._fAbort;
            _fnQueryAbort = prms._fnQueryAbort;
            _LpSolveLogFile = prms._LpSolveLogFile;
            _GetSensitivity = prms._GetSensitivity;
        }

        public LpSolveParams(Directive directive)
        {
            InitLpSolveParams(directive);
        }

        public Func<bool> QueryAbort
        {
            get
            {
                return _fnQueryAbort;
            }
            set
            {
                _fnQueryAbort = value;
            }
        }

#if MSF_2_0_3

        #region ISolverEvents Members

        public Action Solving
        {
            get;
            set;
        }

        #endregion
#endif
    }
}
