import lpsolve.LpSolve;
import lpsolve.LpSolveException;

public class LpSolveDebug
{

static String fileName = "test.lp";
static int ncols = 60000;
static int nrows = 20000;

public static void main(String[] args) throws LpSolveException
{
long start, end;

//
// Try 1: fill the matrix using addColumnex and addConstraintex
//

lpsolve.LpSolve lp1 = lpsolve.LpSolve.makeLp(0, 0);

start = System.currentTimeMillis();
for(int i=1; i<ncols; i++) {
lp1.addColumnex(0, new double[] { 0.0 }, new int[] { 1 });
}
lp1.setAddRowmode(true);
for(int i=1; i<nrows-1; i++) {
lp1.addConstraintex(3, new double[]{ 1.23, 4.56 }, new int[]{ i, i+1 }, lpsolve.LpSolve.EQ, 1.23);
}
lp1.setAddRowmode(false);
end = System.currentTimeMillis();

System.out.println("Time for try 1: " + (end-start) + " ms");

//
// save the LP file
//

System.out.println("Writing lp to " + fileName);
lp1.writeLp(fileName);
System.out.println("...done");

//
// Try 2: read the same model from the LP file using readLp
//

start = System.currentTimeMillis();
LpSolve lp2 = LpSolve.readLp(fileName, 0, "toto");
end = System.currentTimeMillis();
System.out.println("Time for try 2: " + (end-start) + " ms");

}
}

