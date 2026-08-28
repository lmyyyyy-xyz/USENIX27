#define LPSOLVE

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.SolverFoundation.Services;
//using Microsoft.SolverFoundation.Common;
//using Microsoft.SolverFoundation.Solvers;
using System.IO;
using SolverFoundation.Plugin.LpSolve;
#if !LPSOLVE
using SolverFoundation.Plugin.Lindo;
#endif
#if !LPSOLVE
using SolverFoundation.Plugin.Gurobi;
#endif
using Microsoft.SolverFoundation.Solvers;
using Microsoft.SolverFoundation.Common;

namespace ConsoleApplication1
{
    class Program
    {
        static void Example1()
        {
            // Create the model
            SolverContext context = SolverContext.GetContext();
            Model model = context.CreateModel();
            // Add a decision
            Decision x = new Decision(Domain.RealNonnegative, "x");
            model.AddDecisions(x);
            // Add a constraint
            model.AddConstraints("one", x == 1);

#if LPSOLVE
            LpSolveDirective simplex = new LpSolveDirective(); //simplex.GetSensitivity = true;
#else
            SimplexDirective simplex = new SimplexDirective(); //simplex.GetSensitivity = true;
#endif

            Solution sol = context.Solve(simplex);

            // Display the results
            Console.WriteLine("x: {0}", x);

            Report report = sol.GetReport();
            
            Console.WriteLine(report);

            using (StreamWriter sw = new StreamWriter("Example1.mps"))
            {
                context.SaveModel(FileFormat.FreeMPS, sw);
            }

        }

        static void Example2()
        {
            // Get the context and create a new model.
            SolverContext context = SolverContext.GetContext();
            Model model = context.CreateModel();
            // Create two decision variables representing the number of barrels to
            // purchase from two countries.
            // AddDecisions tells the model about the two variables.
            Decision vz = new Decision(Domain.RealNonnegative, "barrels_venezuela");
            Decision sa = new Decision(Domain.RealNonnegative, "barrels_saudiarabia");
            model.AddDecisions(vz, sa);
            // Adding five constraints. The first line defines the allowable range // for the two decision variables. The other constraints put
            // minimums on the total yield of three products.
            model.AddConstraints("limits",
            1 <= vz <= 9000,
            2 <= sa <= 6000,
            sa <= 6001,
            sa >= 3,
            6002 >= sa >= 4);
            model.AddConstraints("production",
            0.3 * sa + 0.4 * vz >= 2000,
            0.4 * sa + 0.2 * vz >= 1500 /*,
            0.2 * sa + 0.3 * vz <= 1449 */);
            // AddGoal states that we want to minimize the total cost subject to the
            // above constraints
            model.AddGoal("cost", GoalKind.Minimize, 20 * sa + 15 * vz);
            //model.AddGoal("cost", GoalKind.Maximize, -20 * sa - 15 * vz);

#if LPSOLVE
            LpSolveDirective simplex = new LpSolveDirective(); simplex.GetSensitivity = true;
#else
            // Solve the problem using the simplex solver
            //LindoSimplexDirective simplex = new LindoSimplexDirective();
            //GurobiDirective simplex = new GurobiDirective(); simplex.GetSensitivity = true;
            SimplexDirective simplex = new SimplexDirective(); simplex.GetSensitivity = true;
#endif
       
            Solution solution = context.Solve(  simplex  );
            // Report the solution values
            Report report = solution.GetReport();
            Console.WriteLine("vz: {0}, sa: {1}", vz, sa);
            Console.Write("{0}", report);

            LinearReport lpReport = report as LinearReport;
            object ShadowPrices = lpReport.GetAllShadowPrices();
            object ConstraintBoundsSensitivity = lpReport.GetAllConstraintBoundsSensitivity();

            using (StreamWriter sw = new StreamWriter("Example2.mps"))
            {
                context.SaveModel(FileFormat.FreeMPS, sw);
            }
        }

        static void _Example2()
        {
            // Get the context and create a new model.
            SolverContext context = SolverContext.GetContext();
            Model model = context.CreateModel();
            // Create two decision variables representing the number of barrels to
            // purchase from two countries.
            // AddDecisions tells the model about the two variables.
            Decision vz = new Decision(Domain.RealNonnegative, "barrels_venezuela");
            Decision sa = new Decision(Domain.RealNonnegative, "barrels_saudiarabia");
            model.AddDecisions(vz, sa);
            // Adding five constraints. The first line defines the allowable range // for the two decision variables. The other constraints put
            // minimums on the total yield of three products.
            model.AddConstraints("limits",
            0 <= vz <= 9000,
            0 <= sa <= 6000);
            model.AddConstraints("production",
            0.3 * sa + 0.4 * vz >= 2000,
            0.4 * sa + 0.2 * vz >= 1500,
            0.2 * sa + 0.3 * vz >= 500);
            // AddGoal states that we want to minimize the total cost subject to the
            // above constraints
            model.AddGoal("cost", GoalKind.Minimize,
            20 * sa + 15 * vz);


#if LPSOLVE           
            LpSolveDirective simplex = new LpSolveDirective();
#else
            // Solve the problem using the simplex solver
            SimplexDirective simplex = new SimplexDirective();
#endif
            Solution solution = context.Solve(simplex);
            // Report the solution values
            Report report = solution.GetReport();
            Console.WriteLine("vz: {0}, sa: {1}", vz, sa);
            Console.Write("{0}", report);

            using (StreamWriter sw = new StreamWriter("Example2.mps"))
            {
                context.SaveModel(FileFormat.FreeMPS, sw);
            }
        }

        static void Example3()
        {
            System.Configuration.ConfigurationManager.GetSection("MsfConfig");

            SolverContext context = SolverContext.GetContext();
            Model model = context.CreateModel();
            Decision COLONE = new Decision(Domain.RealRange(28.6, Rational.PositiveInfinity), "COLONE");
            //COLONE.
            Decision COLTWO = new Decision(Domain.RealNonnegative, "COLTWO");
            Decision COLTHREE = new Decision(Domain.RealNonnegative, "COLTHREE");
            Decision COLFOUR = new Decision(Domain.RealRange(18.0, 48.98), "COLFOUR");
            model.AddDecisions(COLONE, COLTWO, COLTHREE, COLFOUR);

            model.AddConstraints("THISROW",
            +78.26 * COLTWO + 2.9 * COLFOUR >= 92.3);

            model.AddConstraints("THATROW",
            +0.24 * COLONE + 11.31 * COLTHREE <= 14.8);

            model.AddConstraints("LASTROW",
            +12.68 * COLONE + 0.08 * COLTHREE + 0.9 * COLFOUR >= 4);

            model.AddGoal("cost", GoalKind.Minimize, COLONE + 3 * COLTWO + 6.24 * COLTHREE + 0.1 * COLFOUR);

#if LPSOLVE
            LpSolveDirective simplex = new LpSolveDirective(); simplex.GetSensitivity = true;
#else
            SimplexDirective simplex = new SimplexDirective(); simplex.GetSensitivity = true;
            //LindoSimplexDirective simplex = new LindoSimplexDirective();
            //GurobiDirective simplex = new GurobiDirective(); simplex.GetSensitivity = true;            
#endif
            
            Solution solution = context.Solve(simplex);
            Report report = solution.GetReport();
            //Console.Write("{0}", report);
             
            LinearReport lpReport = report as LinearReport;

            LpSolveReport lpLpSolveReport = report as LpSolveReport;

            //lpLpSolveReport.GetAllVariablesSensitivity();

            object ShadowPrices = lpReport.GetAllShadowPrices();
            var ConstraintBoundsSensitivity = lpReport.GetAllConstraintBoundsSensitivity();

            Console.WriteLine("Decisions");
            foreach (Decision d in solution.Decisions)
                Console.WriteLine("Name: " + d.Name + ", Description: " + d.Description + ", Value: " + d.ToDouble());
                       

            Console.WriteLine("GetAllShadowPrices:");
            foreach (KeyValuePair<string, Rational> o in lpReport.GetAllShadowPrices())
                Console.WriteLine("Key: " + o.Key + ", Value: " + o.Value.ToDouble().ToString());

            Console.WriteLine("GetAllConstraintBoundsSensitivity:");
            foreach (KeyValuePair<string, LinearSolverSensitivityRange> o in lpReport.GetAllConstraintBoundsSensitivity())
                Console.WriteLine("Key: " + o.Key + ", Current: " + o.Value.Current.ToDouble().ToString()  + ", Value.Lower: " + o.Value.Lower.ToDouble().ToString() + ", Value.Upper: " + o.Value.Upper.ToDouble().ToString());

            Console.WriteLine("GetGoalCoefficientSensitivity + GetGoalCoefficientSensitivityFromValue:");
            foreach (Decision d in solution.Decisions)
            {
                LinearSolverSensitivityRange? o = lpReport.GetGoalCoefficientSensitivity(d);
                Rational FromValue;
#if LPSOLVE
                FromValue = lpLpSolveReport.GetGoalCoefficientSensitivityFromValue(d);                
#else
                FromValue = Rational.NegativeInfinity;
#endif
                Console.WriteLine("Name: " + d.Name + ", Current: " + o.Value.Current.ToDouble().ToString() + ", Lower: " + o.Value.Lower.ToDouble().ToString() + ", Upper: " + o.Value.Upper.ToDouble().ToString() + ", FromValue: " + FromValue.ToDouble().ToString());
            }

#if LPSOLVE
            Console.WriteLine("GetDecisionBoundsSensitivity:");
            foreach (Decision d in solution.Decisions)
            {
                LinearSolverSensitivityRange? o = lpLpSolveReport.GetDecisionBoundsSensitivity(d);
                Console.WriteLine("Name: " + d.Name + ", Current: " + o.Value.Current.ToDouble().ToString() + ", Lower: " + o.Value.Lower.ToDouble().ToString() + ", Upper: " + o.Value.Upper.ToDouble().ToString());
            }

            Console.WriteLine("GetDecisionShadowPrice:");
            foreach (Decision d in solution.Decisions)
            {
                Rational? o = lpLpSolveReport.GetDecisionShadowPrice(d);
                Console.WriteLine("Name: " + d.Name + ", Value: " + o.Value.ToDouble().ToString());
            }

            Console.WriteLine("GetAllConstraintValues:");
            foreach (KeyValuePair<string, Rational> o in lpLpSolveReport.GetAllConstraintValues())
                Console.WriteLine("Key: " + o.Key + ", Value: " + o.Value.ToDouble().ToString());
#endif

            

            bool x;
            
            x = lpReport.IsSensitivityAvailable;
            x = lpReport.IsInfeasibilityAvailable;

            using (StreamWriter sw = new StreamWriter("Example3.mps"))
            {
                context.SaveModel(FileFormat.FreeMPS, sw);
            }

#if LPSOLVE
            lpLpSolveReport.LpSolveWriteLp("Example3.lp");
            lpLpSolveReport.LpSolveWriteMPS("Example3'.mps", true);
#endif
        }

        static void _Example3()
        {
#if LPSOLVE
            LpSolveSolver solver = new LpSolveSolver();
#else
            //SimplexSolver solver = new SimplexSolver();
            GurobiSolver solver = new GurobiSolver();
#endif
            int COLONE, COLTWO, COLTHREE, COLFOUR;
            solver.AddVariable("COLONE", out COLONE); solver.SetBounds(COLONE, 28.6, Rational.PositiveInfinity);
            solver.AddVariable("COLTWO", out COLTWO); solver.SetBounds(COLTWO, 0.0, Rational.PositiveInfinity);
            solver.AddVariable("COLTHREE", out COLTHREE); solver.SetBounds(COLTHREE, 0.0, Rational.PositiveInfinity);
            solver.AddVariable("COLFOUR", out COLFOUR); solver.SetBounds(COLFOUR, 18.0, 48.98);

            int THISROW, THATROW, LASTROW, goal;
            solver.AddRow("THISROW", out THISROW); solver.SetBounds(THISROW, 92.3, Rational.PositiveInfinity); solver.SetCoefficient(THISROW, COLTWO, 78.26); solver.SetCoefficient(THISROW, COLFOUR, 2.9);
            solver.AddRow("THATROW", out THATROW); solver.SetBounds(THATROW, Rational.NegativeInfinity, 14.8); solver.SetCoefficient(THATROW, COLONE, 0.24); solver.SetCoefficient(THATROW, COLTHREE, 11.31);
            solver.AddRow("LASTROW", out LASTROW); solver.SetBounds(LASTROW, 4.0, Rational.PositiveInfinity); solver.SetCoefficient(LASTROW, COLONE, 12.68); solver.SetCoefficient(LASTROW, COLTHREE, 0.08); solver.SetCoefficient(LASTROW, COLFOUR, 0.9);

            solver.AddRow("goal", out goal); solver.SetCoefficient(goal, COLONE, 1.0); solver.SetCoefficient(goal, COLTWO, 3.0); solver.SetCoefficient(goal, COLTHREE, 6.24); solver.SetCoefficient(goal, COLFOUR, 0.1);
            solver.AddGoal(goal, 1, true);

#if LPSOLVE
            LpSolveDirective simplex = new LpSolveDirective(); simplex.GetSensitivity = true; ; simplex.LpSolveVerbose = 4; LpSolveParams parameter = new LpSolveParams(simplex);
#else
            //SimplexSolverParams parameter = new SimplexSolverParams(); parameter.GetSensitivityReport = true;
            //SimplexSolverParams parameter = new DemoSimplexSolverParams(); parameter.GetSensitivityReport = true;
            GurobiParams parameter = new GurobiParams();
#endif
            ILinearSolution solution = solver.Solve(parameter);

#if LPSOLVE
            solver.LpSolveWriteLp("con");
#endif
            
            ILinearSolverReport report = solver.GetReport(LinearSolverReportType.Sensitivity);

            ILinearSolverSensitivityReport sensitivityreport = report as ILinearSolverSensitivityReport;

            

            double Value;

            Console.WriteLine("GetValue:");
            foreach (int vid in solver.VariableIndices)
            {
                Value = solver.GetValue(vid).ToDouble();
                Console.WriteLine(solver.GetKeyFromIndex(vid) + ": Value: " + Value.ToString());
            }

#if LPSOLVE
            Console.WriteLine("GetDualValue:");
            foreach (int rid in solver.RowIndices)
            {
                if (!solver.IsGoal(rid))
                {
                    Value = solver.GetDualValue(rid).ToDouble();
                    Console.WriteLine(solver.GetKeyFromIndex(rid) + ": Value: " + Value.ToString());
                }
            }
            foreach (int vid in solver.VariableIndices)
            {
                Value = solver.GetDualValue(vid).ToDouble();
                Console.WriteLine(solver.GetKeyFromIndex(vid) + ": Value: " + Value.ToString());
            }

#endif

            LinearSolverSensitivityRange x;

#if LPSOLVE
            Console.WriteLine("Variable GetVariableRange:");
            foreach (int vid in solver.VariableIndices)
            {
                x = solver.GetVariableRange(vid);
                Console.WriteLine(solver.GetKeyFromIndex(vid) + ": Current: " + x.Current.ToDouble().ToString() + ", Lower: " + x.Lower.ToDouble().ToString() + ", Upper: " + x.Upper.ToDouble().ToString());
            }
#endif

#if LPSOLVE
            Console.WriteLine("RHS GetVariableRange:");
            foreach (int rid in solver.RowIndices)
            {
                if (!solver.IsGoal(rid))
                {
                    x = solver.GetVariableRange(rid);
                    Console.WriteLine(solver.GetKeyFromIndex(rid) + ": Current: " + x.Current.ToDouble().ToString() + ", Lower: " + x.Lower.ToDouble().ToString() + ", Upper: " + x.Upper.ToDouble().ToString());
                }
            }
#endif

            Console.WriteLine("GetObjectiveCoefficientRange:");
            foreach (int vid in solver.VariableIndices)
            {
                x = solver.GetObjectiveCoefficientRange(vid);
                Console.WriteLine(solver.GetKeyFromIndex(vid) + ": Current: " + x.Current.ToDouble().ToString() + ", Lower: " + x.Lower.ToDouble().ToString() + ", Upper: " + x.Upper.ToDouble().ToString());
            }

            

            solution = null;

#if false
            Solution solution = context.Solve(simplex);
            Report report = solution.GetReport();
            Console.Write("{0}", report);

            LinearReport lpReport = report as LinearReport;
            object ShadowPrices = lpReport.GetAllShadowPrices();
            object ConstraintBoundsSensitivity = lpReport.GetAllConstraintBoundsSensitivity();

            Console.WriteLine("Decisions");
            foreach (Decision d in solution.Decisions)
                Console.WriteLine("Name: " + d.Name + ", Description: " + d.Description);

            Console.WriteLine("GetAllShadowPrices:");
            foreach (KeyValuePair<string, Rational> o in lpReport.GetAllShadowPrices())
                Console.WriteLine("Key: " + o.Key + ", Value: " + o.Value.ToDouble().ToString());

            Console.WriteLine("GetAllConstraintBoundsSensitivity:");
            foreach (KeyValuePair<string, LinearSolverSensitivityRange> o in lpReport.GetAllConstraintBoundsSensitivity())
                Console.WriteLine("Key: " + o.Key + ", Current: " + o.Value.Current.ToDouble().ToString() + ", Value.Lower: " + o.Value.Lower.ToDouble().ToString() + ", Value.Upper: " + o.Value.Upper.ToDouble().ToString());

            object[] indexes = new object[0];
            Console.WriteLine("GetGoalCoefficientSensitivity:");
            foreach (Decision d in solution.Decisions)
            {
                LinearSolverSensitivityRange? o = lpReport.GetGoalCoefficientSensitivity(d, indexes);
                Console.WriteLine("Name: " + d.Name + ", Current: " + o.Value.Current.ToDouble().ToString() + ", Lower: " + o.Value.Lower.ToDouble().ToString() + ", Upper: " + o.Value.Upper.ToDouble().ToString());
            }


            bool x;

            x = lpReport.IsSensitivityAvailable;
            x = lpReport.IsInfeasibilityAvailable;

            using (StreamWriter sw = new StreamWriter("Example3.mps"))
            {
                context.SaveModel(FileFormat.FreeMPS, sw);
            }
#endif
        }

        class BreakPoint
        {
            public int PointID
            {
                get;
                set;
            }

            public int SupplierID
            {
                get;
                set;
            }

            public int BR
            {
                get;
                set;
            }

            public double CBR
            {
                get;
                set;
            }

            public double Cost
            {
                get;
                set;
            }

            public BreakPoint(int pointID, int suppID, int br, double cbr, double cost)
            {
                PointID = pointID;
                SupplierID = suppID;
                BR = br;
                CBR = cbr;
                Cost = cost;
            }
        }

        class MaxSupplierQty
        {
            public int SupplierID
            {
                get;
                set;
            }

            public double Qty
            {
                get;
                set;
            }

            public MaxSupplierQty(int suppID, double qty)
            {
                SupplierID = suppID;
                Qty = qty;
            }
        }

        static void Example4()
        {
#if false
            BreakPoint[] _points = { new BreakPoint(0,1,0,0,0),new BreakPoint(1,1,100,920,9.2), new BreakPoint(2, 1, 200, 1820 ,9), new BreakPoint(3, 1, 1000, 7420 ,7),
                               new BreakPoint(0,2,0,0,0),new BreakPoint(1,2,50,450,9), new BreakPoint(2, 2, 250, 2150 ,8.5), new BreakPoint(3, 2, 2000, 16685 ,8.3),
                               new BreakPoint(0,3,0,0,0),new BreakPoint(1,3,100,1100,11), new BreakPoint(2, 3, 300, 2800 ,8.5), new BreakPoint(3, 3, 4000, 30570 ,7.5)
                             };
#else
            BreakPoint[] _points = { new BreakPoint(1,1,100,920,9.2), new BreakPoint(2, 1, 200, 1820 ,9), new BreakPoint(3, 1, 1000, 7420 ,7),
                               new BreakPoint(1,2,50,450,9), new BreakPoint(2, 2, 250, 2150 ,8.5), new BreakPoint(3, 2, 2000, 16685 ,8.3),
                               new BreakPoint(1,3,100,1100,11), new BreakPoint(2, 3, 300, 2800 ,8.5), new BreakPoint(3, 3, 4000, 30570 ,7.5)
                             };
#endif
            IEnumerable<BreakPoint> _enPoints = _points.AsEnumerable();

            MaxSupplierQty[] _maxQuantities = {new MaxSupplierQty(1,40),
                                         new MaxSupplierQty(2,35),
                                         new MaxSupplierQty(3,40)
                                        };

            double MinimumQuantity = 600;
            SolverContext context = SolverContext.GetContext();
            Model model = context.CreateModel();
            Set sSuppliers = new Set(Domain.IntegerNonnegative, "Suppliers");
            Set sBreakPoints = new Set(Domain.IntegerNonnegative, "BreakPoints");

            Decision buy = new Decision(Domain.RealNonnegative, "Buy", sSuppliers);
            Decision weight = new Decision(Domain.RealNonnegative, "Weights", sSuppliers, sBreakPoints);
            model.AddDecisions(buy, weight);

            Parameter MaxPercentage = new Parameter(Domain.RealNonnegative, "MaxPercent", sSuppliers);
            MaxPercentage.SetBinding(_maxQuantities.AsEnumerable(), "Qty", "SupplierID");

            Parameter BR = new Parameter(Domain.IntegerNonnegative, "Quantities", sSuppliers, sBreakPoints);
            BR.SetBinding(_enPoints, "BR", "SupplierID", "PointID");

#if false
            Parameter Cost = new Parameter(Domain.RealNonnegative, "pCost", sSuppliers, sBreakPoints);
            Cost.SetBinding(_enPoints, "Cost", "SupplierID", "PointID");
#endif

            Parameter CBR = new Parameter(Domain.RealNonnegative, "Costatbreakpoint", sSuppliers, sBreakPoints);
            CBR.SetBinding(_enPoints, "CBR", "SupplierID", "PointID");

#if false
            model.AddParameters(MaxPercentage, BR, Cost, CBR);
#else
            model.AddParameters(MaxPercentage, BR, CBR);
#endif

            model.AddGoal("CostGoal", GoalKind.Minimize, Model.Sum(Model.ForEach(sSuppliers, supp => Model.ForEach(sBreakPoints, point => CBR[supp, point] * weight[supp, point]))));
            model.AddConstraint("RefernceRow", Model.ForEach(sSuppliers, supp => Model.Sos2(buy[supp] == Model.Sum(Model.ForEach(sBreakPoints, point => BR[supp, point] * weight[supp, point])))));
            model.AddConstraint("MinQuantity", Model.Sum(Model.ForEach(sSuppliers, supp => buy[supp])) >= MinimumQuantity);
#if false
#else
            model.AddConstraint("MaxSupply", Model.ForEach(sSuppliers, supp => buy[supp] <= MaxPercentage[supp] * MinimumQuantity / 100));
#endif

#if LPSOLVE
            LpSolveDirective simplex = new LpSolveDirective(); //simplex.GetSensitivity = true;
#else
            SimplexDirective simplex = new SimplexDirective(); simplex.GetSensitivity = true;

            //LindoSimplexDirective simplex = new LindoSimplexDirective();
            //GurobiDirective simplex = new GurobiDirective(); simplex.GetSensitivity = true;            
#endif
            Solution sol = context.Solve(simplex);
            Report report = sol.GetReport();
            Console.WriteLine(report);
        }

        public class BreakPoint2
        {

            public BreakPoint2(int id, double rCord, double fCord)
            {
                ID = id;
                rCoordinate = rCord;
                fCoordinate = fCord;
            }

            public int ID
            {
                get;
                set;
            }
            public double rCoordinate
            {
                get;
                set;
            }
            public double fCoordinate
            {
                get;
                set;
            }
        }

        static void Example5() // C#\SOS2\Approx example
        {
            BreakPoint2[] _breakPoints = new BreakPoint2[5];
            _breakPoints[0] = new BreakPoint2(1, 1, 2);
            _breakPoints[1] = new BreakPoint2(2, 2.2, 3.2);
            _breakPoints[2] = new BreakPoint2(3, 3.4, 1.4);
            _breakPoints[3] = new BreakPoint2(4, 4.8, 2.5);
            _breakPoints[4] = new BreakPoint2(5, 6.5, 0.8);

            SolverContext context = SolverContext.GetContext();
            Model model = context.CreateModel();
            Set sBreaks = new Set(Domain.Integer, "Breaks");

            Decision x = new Decision(Domain.Real, "x");
            Decision y = new Decision(Domain.RealNonnegative, "y", sBreaks);
            y.SetBinding(_breakPoints.AsEnumerable(), "ID");
            model.AddDecisions(x, y);

            Parameter paramRCoord = new Parameter(Domain.RealNonnegative, "RCoordinate", sBreaks);
            Parameter paramFCoord = new Parameter(Domain.RealNonnegative, "FCoordinate", sBreaks);
            paramRCoord.SetBinding(_breakPoints.AsEnumerable(), "rCoordinate", "ID");
            paramFCoord.SetBinding(_breakPoints.AsEnumerable(), "fCoordinate", "ID");
            model.AddParameters(paramFCoord, paramRCoord);

            model.AddConstraint("ReferenceRow", Model.Sos2(x == Model.Sum(Model.ForEach(sBreaks, point => y[point] * paramRCoord[point]))));
            model.AddGoal("f", GoalKind.Minimize, Model.Sum(Model.ForEach(sBreaks, point => y[point] * paramFCoord[point])));

#if LPSOLVE
            LpSolveDirective simplex = new LpSolveDirective(); simplex.GetSensitivity = true;
#else
            SimplexDirective simplex = new SimplexDirective(); simplex.GetSensitivity = true;

            //LindoSimplexDirective simplex = new LindoSimplexDirective();
            //GurobiDirective simplex = new GurobiDirective(); simplex.GetSensitivity = true;            
#endif
            Solution sol = context.Solve(simplex);
            Report report = sol.GetReport();
            Console.WriteLine(report);
        }

        private static void LpSolveLogFunc(int lp, int userhandle, string buffer)
        {
            Console.Write("{0}", buffer);
        }

        private static void LpSolveMsgFunc(int lp, int userhandle, LpSolveNativeInterface.lpsolve.lpsolve_msgmask message)
        {
            Console.Write("{0}\n", message);
        }

        static void Example7()
        {
            SolverContext context = SolverContext.GetContext();
            Model model = context.CreateModel();
            Decision COLONE = new Decision(Domain.RealRange(28.6, Rational.PositiveInfinity), "COLONE");
            Decision COLTWO = new Decision(Domain.RealNonnegative, "COLTWO");
            Decision COLTHREE = new Decision(Domain.RealNonnegative, "COLTHREE");
            Decision COLFOUR = new Decision(Domain.IntegerRange(18.0, 48.98), "COLFOUR");
            model.AddDecisions(COLONE, COLTWO, COLTHREE, COLFOUR);

            model.AddConstraints("THISROW",
            +78.26 * COLTWO + 2.9 * COLFOUR >= 92.3);

            model.AddConstraints("THATROW",
            +0.24 * COLONE + 11.31 * COLTHREE <= 14.8);

            model.AddConstraints("LASTROW",
            +12.68 * COLONE + 0.08 * COLTHREE + 0.9 * COLFOUR >= 4);

#if true
            Constraint extrarow = model.AddConstraints("EXTRAROW", +78.26 * COLTWO + 2.9 * COLFOUR >= 92.4);
#endif

            model.AddGoal("cost", GoalKind.Minimize, COLONE + 3 * COLTWO + 6.24 * COLTHREE + 0.1 * COLFOUR);

#if LPSOLVE
            LpSolveDirective simplex = new LpSolveDirective(); simplex.LpSolveMsgFunc = LpSolveMsgFunc; simplex.LpSolveVerbose = 4; simplex.LpSolveLogFunc = LpSolveLogFunc;
#else
            SimplexDirective simplex = new SimplexDirective(); simplex.GetSensitivity = true;
            //LindoSimplexDirective simplex = new LindoSimplexDirective();
            //GurobiDirective simplex = new GurobiDirective(); simplex.GetSensitivity = true;            
#endif

            
           
            Solution solution = context.Solve(simplex);

            Report report = solution.GetReport();

            long t = report.SolveTime;
            
            Console.Write("{0}", report);
           
            solution = null;

            LinearReport lpReport = report as LinearReport;
            object ShadowPrices = lpReport.GetAllShadowPrices();
            object ConstraintBoundsSensitivity = lpReport.GetAllConstraintBoundsSensitivity();

#if true
            model.RemoveConstraint(extrarow);

            solution = context.Solve(simplex);
            report = solution.GetReport();
            Console.Write("{0}", report);
            solution = null;
#endif

            //context.PropagateDecisions();

            using (StreamWriter sw = new StreamWriter("Example7.mps"))
            {
                context.SaveModel(FileFormat.FreeMPS, sw);
            }

        }

#if LPSOLVE
        public class DemoLpSolveParams : LpSolveParams
        {
        }
#else
        public class DemoSimplexSolverParams : SimplexSolverParams
        {
            public override bool NotifyStartPivot(int threadIndex,
            ILinearSimplexStatistics stat,
            ISimplexPivotInformation spi)
            {
                Console.WriteLine("Starting pivot.");
                Console.WriteLine("determinant {0} approximate cost {1} scale {2}",
                spi.Determinant, spi.ApproxCost, spi.Scale);
                return true;
            }
            public override bool NotifyEndPivot(int threadIndex,
            ILinearSimplexStatistics stat,
            ISimplexPivotInformation spi)
            {
                Console.WriteLine("Ending pivot.");
                return true;
            }
        }
#endif        

        private class MyLpSolveSolver : LpSolveSolver
        {
            public override void LpSolveLogFunc(int lp, int userhandle, string buffer)
            {
                base.LpSolveLogFunc(lp, userhandle, buffer);
                Console.Write("{0}", buffer);
            }

            public override void LpSolveMsgFunc(int lp, int userhandle, LpSolveNativeInterface.lpsolve.lpsolve_msgmask message)
            {
                base.LpSolveMsgFunc(lp, userhandle, message);
                Console.Write("{0}", message);
            }
        }

        private class MyLpSolveParams : LpSolveParams
        {
            //public override 
        }

        /*
        private class MyLpSolveDirective : LpSolveDirective
        {
            
            public override void LpLogFunc(int lp, int userhandle, string buffer)
            {
                base.LpLogFunc(lp, userhandle, buffer);

                Console.Write("{0}", buffer);
            }
             
        }
        */

        static void Example8()
        {
#if LPSOLVE
            MyLpSolveSolver solver = new MyLpSolveSolver();
#else
            //SimplexSolver solver = new SimplexSolver();
            GurobiSolver solver = new GurobiSolver();
#endif
            // add variables with their lower and upper bounds
            int savid, vzvid;
            solver.AddVariable("Saudi Arabia", out savid);
            solver.SetBounds(savid, 0, 9000);
            solver.AddVariable("Venezuela", out vzvid);
            solver.SetBounds(vzvid, 0, 6000);
            solver.SetIntegrality(vzvid, true);
            // add constraints to model
            int c1rid, c2rid, c3rid, goalrid;
            solver.AddRow("constraint1", out c1rid);
            solver.AddRow("constraint2", out c2rid);
            solver.AddRow("constraint3", out c3rid);
            solver.AddRow("goal", out goalrid);
            // add coefficients to constraint rows
            solver.SetCoefficient(c1rid, savid, 0.3);
            solver.SetCoefficient(c1rid, vzvid, 0.4);
            solver.SetBounds(c1rid, 2000, Rational.PositiveInfinity);
            solver.SetCoefficient(c2rid, savid, 0.4);
            solver.SetCoefficient(c2rid, vzvid, 0.2);
            solver.SetBounds(c2rid, 1500, Rational.PositiveInfinity);
            solver.SetCoefficient(c3rid, savid, 0.2);
            solver.SetCoefficient(c3rid, vzvid, 0.3);
            solver.SetBounds(c3rid, 500, Rational.PositiveInfinity);
            // add objective (goal) to model and specify minimization (==true)
            solver.SetCoefficient(goalrid, savid, 20);
            solver.SetCoefficient(goalrid, vzvid, 15);
            solver.AddGoal(goalrid, 1, true);
            // solve the model
#if LPSOLVE
            //MyLpSolveDirective simplex = new MyLpSolveDirective(); simplex.GetSensitivity = true; simplex.LpSolveVerbose = 4; LpSolveParams parameter = new LpSolveParams(simplex);
            LpSolveDirective simplex = new LpSolveDirective(); simplex.GetSensitivity = true; ; simplex.LpSolveVerbose = 4; LpSolveParams parameter = new LpSolveParams(simplex);
#else
            //SimplexSolverParams parameter = new SimplexSolverParams(); parameter.GetSensitivityReport = true;
            //SimplexSolverParams parameter = new DemoSimplexSolverParams(); parameter.GetSensitivityReport = true;
            GurobiParams parameter = new GurobiParams();
#endif
            ILinearSolution solution = solver.Solve(parameter);
            Console.WriteLine("SA {0}, VZ {1}, C1 {2}, C2 {3}, C3 {4}, Goal {5}",
            solver.GetValue(savid).ToDouble(), solver.GetValue(vzvid).ToDouble(),
            solver.GetValue(c1rid).ToDouble(), solver.GetValue(c2rid).ToDouble(),
            solver.GetValue(c3rid).ToDouble(), solver.GetValue(goalrid).ToDouble());

            Console.WriteLine("{0}", solver.PivotCount);
            Console.WriteLine("{0}", solver.AlgorithmUsed);
#if LPSOLVE
            Console.WriteLine("{0}", solver.GetDualValue(2).ToDouble());
            solver.LpSolveWriteParams(@"d:\brol\params.par", "");
#endif
            //solver.

            ILinearSolverReport report = solver.GetReport(LinearSolverReportType.Sensitivity);
            
            Console.WriteLine("{0}", report);
            Report Report = report as Report;
            Console.WriteLine("{0}", Report);
            LinearReport lpReport = report as LinearReport;
            Console.WriteLine("{0}", lpReport);
#if !LPSOLVE
            GurobiReport gReport = report as GurobiReport;
            Console.WriteLine("{0}", gReport);
#endif
        }

        static void Example9()
        {
#if LPSOLVE
            LpSolveSolver solver = new LpSolveSolver();
#else
            SimplexSolver solver = new SimplexSolver();
#endif
            // data about the projects.
            double[] estimatedProfitOfProjectX = new double[] { 1, 1.8, 1.6, 0.8, 1.4 };
            double[] capitalRequiredForProjectX = new double[] { 6, 12, 10, 4, 8 };
            double availableCapital = 20;
            // decision variables.
            int[] chooseProjectX = new int[5];
            int goal;
            solver.AddRow("goal", out goal);
            solver.AddGoal(goal, 0, false /*maximize*/);
            int expenditure;
            solver.AddRow("expenditure", out expenditure);
            solver.SetBounds(expenditure, 0, availableCapital);
            for (int i = 0; i < 5; i++)
            {
                solver.AddVariable(string.Format("project{0}", i),
                out chooseProjectX[i]);
                solver.SetBounds(chooseProjectX[i], 0, 1);
                // we either choose or don't choose the project; no half way decisions.
                solver.SetIntegrality(chooseProjectX[i], true);
                solver.SetCoefficient(goal, chooseProjectX[i],
                estimatedProfitOfProjectX[i]);
                solver.SetCoefficient(expenditure, chooseProjectX[i],
                capitalRequiredForProjectX[i]);
            }
#if LPSOLVE
            LpSolveDirective simplex = new LpSolveDirective(); simplex.LpSolveReadParams(@"d:\brol\params.par", ""); simplex.GetSensitivity = true; simplex.LpSolveLogFunc = LpSolveLogFunc; simplex.LpSolveMsgFunc = LpSolveMsgFunc; LpSolveParams param = new LpSolveParams(simplex);
            //LpSolveDirective simplex = new LpSolveDirective(); simplex.GetSensitivity = true; LpSolveParams parameter = new DemoLpSolveParams(simplex);
#else
            SimplexSolverParams param = new SimplexSolverParams();
            param.MixedIntegerGenerateCuts = true;
#endif
            //solver.Solve(param);
            ILinearSolution solution = solver.Solve(param);

            ILinearSolverReport sensitivity = solver.GetReport(LinearSolverReportType.Sensitivity);
            
            Console.WriteLine(solver.MipResult);
            for (int i = 0; i < 5; i++)
            {
                Console.WriteLine("Project {0} is {1} selected.", i,
                solver.GetValue(chooseProjectX[i]) == 1 ? "" : "not ");
            }
            Console.WriteLine("The estimated total profit is: ${0}.",
            (double)solver.GetValue(goal).ToDouble());
            Console.WriteLine("The total expenditure is: ${0}.",
            solver.GetValue(expenditure).ToDouble());

#if LPSOLVE
            solver.LpSolveWriteParams(@"d:\brol\params.par", "");
            solver.LpSolveWriteLp(@"d:\brol\a.lp");
            solver.LpSolveWriteMPS(@"d:\brol\a.mps", true);
            solver.LpSolvePrintDebugDump(@"d:\brol\a.txt");
#endif
        }

        static void Example10()
        {
            SolverContext context = SolverContext.GetContext();
            Model model = context.CreateModel();

            Decision xs = new Decision(Domain.IntegerNonnegative, "Number_of_small_chess_boards");
            Decision xl = new Decision(Domain.IntegerNonnegative, "Number_of_large_chess_boards");
            model.AddDecisions(xs, xl);

            Constraint constraintBoxWood = model.AddConstraint("BoxWood", 1 * xs + 3 * xl <= 200);
            Constraint constraintLathe = model.AddConstraint("Lathe", 3 * xs + 2 * xl <= 160);

            model.AddGoal("Profit", GoalKind.Maximize, 5 * xs + 20 * xl);

#if LPSOLVE
            LpSolveDirective simplex = new LpSolveDirective(); //simplex.GetSensitivity = true;
#else
            SimplexDirective simplex = new SimplexDirective(); //simplex.GetSensitivity = true;
#endif

            Solution sol = context.Solve(simplex);
            Report report = sol.GetReport();
            Console.WriteLine(report);
        }

        // http://blogs.msdn.com/b/solverfoundation/

        static double function(double x)
        {
            return x + 1 / x;
        }

        static double derivative(double x)
        {
            return 1 - Math.Pow(x, -2);
        }

        static void Example11()
        {
            SolverContext context = SolverContext.GetContext();
            Model model = context.CreateModel();

            Decision t = new Decision(Domain.Real, "t");
            Decision x = new Decision(Domain.Real, "x");
            model.AddDecisions(t, x);
            model.AddGoal("goal", GoalKind.Minimize, t);

            int i = 0;
            for (double x_i = .1; x_i <= 4; x_i = x_i + .01)
            {
                model.AddConstraint("constraint_" + i++, derivative(x_i) * (x - x_i) + function(x_i) <= t);
            }

#if LPSOLVE
            LpSolveDirective simplex = new LpSolveDirective(); simplex.LpSolveMsgFunc = LpSolveMsgFunc; simplex.LpSolveVerbose = 4; simplex.LpSolveLogFunc = LpSolveLogFunc; //simplex.GetSensitivity = true;
#else
            SimplexDirective simplex = new SimplexDirective(); //simplex.GetSensitivity = true;
#endif

            Solution solution = context.Solve(simplex);
            Report report = solution.GetReport();
            Console.WriteLine(report);

            using (StreamWriter sw = new StreamWriter("Example11.mps"))
            {
                context.SaveModel(FileFormat.FreeMPS, sw);
            }

        }

        static void Main(string[] args)
        {
            Example3();
        }
    }
}
