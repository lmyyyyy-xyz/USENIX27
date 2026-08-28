import lpsolve.*;

public class TestIt {

public static void main(String[] args) {
double[] x_1 = {1.5, 2.4};
double[] x_2 = {3.5, 2.67};
try {
double[] result = (min_search(x_1, x_2));
System.err.println("result is: " + result);
for(int i = 0; i < result.length; i++) {
System.err.println("result[" + i + "]=" + result[i]);
}
}
catch(Exception x) {
x.printStackTrace(System.err);
}
}

public static double[] min_search(double[] x_1, double[] x_2) throws
LpSolveException {

int dimension = x_1.length;
double[] minimum = new double[dimension] ;
double[] x = new double[dimension] ;
double[] loeser = new double[dimension + 1];
double theta;
double[] obj_funkt = new double[dimension + 2];
double[] constraints = new double[dimension + 2];

double[] anstieg = new double[dimension] ;
double epsilon = 0.00001,
abbruchbedingung;


LpSolve solver;

solver = LpSolve.makeLp(0, dimension + 1);

for(int i = 0; i < dimension; i++) {
obj_funkt[i+1] = 0;
// untere Grenze für Koordinate setzen
solver.setLowbo(i + 1, -1.0E10);
}
obj_funkt[dimension +1] = 1;

// Zielfunktion theta größer gleich Null
solver.setLowbo(dimension + 1, -1.0E10);

// Zielfunktion setzen
solver.setObjFn(obj_funkt) ;

// suche Minimum
solver.setMinim();
solver.setVerbose(LpSolve.IMPORTANT);

// x_1
anstieg = subgradient(x_1);
for(int i = 0; i < dimension; i++) {
constraints[i+1] = anstieg[i];
}
constraints[dimension+1] = -1.0;
System.err.println("First Time\n====================");
System.err.println("solver.getNColumns()=" + solver.getNcolumns());
System.err.println("constraints.length =" + constraints.length);
System.err.println("constraints[] is: " + constraints);
for(int i = 0; i < constraints.length; i++) {
System.err.println("constraints[" + i + "]=" + constraints[i]);
}
System.err.println("====================");
solver.addConstraint(constraints, LpSolve.LE,
vektor_produkt(anstieg, x_1) - abstandsfunktion(x_1));

// x_2
anstieg = subgradient(x_2);
for(int i = 0; i < dimension; i++) {
constraints[i+1] = anstieg[i];
}
constraints[dimension+ 1] = -1;
System.err.println("Second Time\n====================");
System.err.println("solver.getNColumns()=" + solver.getNcolumns());
System.err.println("constraints.length =" + constraints.length);
System.err.println("constraints[] is: " + constraints);
for(int i = 0; i < constraints.length; i++) {
System.err.println("constraints[" + i + "]=" + constraints[i]);
}
System.err.println("====================");
solver.addConstraint(constraints, LpSolve.LE,
vektor_produkt(anstieg, x_2) - abstandsfunktion(x_2));


// solve Problem
solver.solve();

loeser = solver.getPtrVariables();
for(int i = 0; i < dimension; i++) {
x[i] = loeser[i];
}
theta = loeser[dimension] ;

// search for Min
int count = 0;
do {
count++;
anstieg = subgradient(x);
System.err.println("dimension =" + dimension);
for(int i = 0; i < dimension; i++) {
constraints[i+1] = anstieg[i];
}
constraints[dimension+ 1] = -1;
System.err.println("Third Time\n====================");
System.err.println("solver.getNColumns()=" + solver.getNcolumns());
System.err.println("solver.getNRows()=" + solver.getNrows());
System.err.println("constraints.length =" + constraints.length);
System.err.println("constraints[] is: " + constraints);
for(int i = 0; i < constraints.length; i++) {
System.err.println("constraints[" + i + "]=" + constraints[i]);
}
System.err.println("====================");
solver.addConstraint(constraints, LpSolve.LE,
vektor_produkt(anstieg, x) - abstandsfunktion(x));
solver.setLpName("" + count);
//solver.writeLp("D:\\_tmp\\" + count + ".lp");
solver.writeLp(count + ".lp");
solver.solve();

loeser = solver.getPtrVariables();
for(int i = 0; i < dimension; i++) {
x[i] = loeser[i];
}
theta = loeser[dimension] ;
abbruchbedingung = (abstandsfunktion(x) -
theta)/(Math.abs(abstandsfunktion(x))+1);
System.err.println("count=" + count + " abbruchbedingung=" +
abbruchbedingung + " epsilon=" + epsilon);
System.err.flush();
}
while(abbruchbedingung > epsilon);

solver.deleteLp( );
return(x);
}

private static double[] subgradient(double[] x) {
return x;
}

private static double vektor_produkt(double[] a, double[] x) {
return 0.01;
}

private static double abstandsfunktion(double[] x) {
return 0.1;
}

}

