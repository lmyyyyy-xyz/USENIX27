import lpsolve.LpSolve;
import lpsolve.LpSolveException;


/**
 * @author Administrator
 *
 */
public class Perf {

	private static void doWork() throws LpSolveException {
		LpSolve problem = LpSolve.makeLp(3, 4);
		problem.strAddConstraint("3 2 2 1", LpSolve.LE, 4);
		problem.strAddConstraint("0 4 3 1", LpSolve.GE, 3);
		problem.strSetObjFn("2 3 -2 3");
		problem.setMaxim();
		problem.setInt(4, true);
		problem.setLowbo(2, 2);
		problem.setUpbo(4, 5.3);
		problem.setRowName(1, "speed");
		problem.setColName(2, "money");
		problem.setVerbose(LpSolve.IMPORTANT);
		problem.solve();
		problem.deleteLp();
	}
	
	public static void main(String[] args) {
		
		System.out.println("START");
		
		long start = System.currentTimeMillis();
		try {
			for (int i = 0; i < 100000; i++) {
				doWork();
			}
		} 
		catch (LpSolveException e) {
			e.printStackTrace();
		}
		long finish = System.currentTimeMillis();
		
		System.out.println("Duration = " + (finish - start) + " ms");
		
	}
}
