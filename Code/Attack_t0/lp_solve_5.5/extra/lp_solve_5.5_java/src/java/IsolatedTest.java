/*
 This is a java wrapper for the lp_solve optimization library.
 
 Copyright (C) 2004  Juergen Ebert (juergen.ebert@web.de)

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

import java.io.File;

import lpsolve.*;
import junit.framework.TestCase;
import junit.framework.TestSuite;

/**
 * JUnit tests for methods of the LpSolve class.
 * 
 * @author Juergen Ebert
 */
public class IsolatedTest extends TestCase {

	public IsolatedTest(String name) {
		super(name);
	}

	public static void main(String[] args) {
		junit.textui.TestRunner.run(suite());
	}

	public static TestSuite suite() {
		return new TestSuite(IsolatedTest.class);
	}

	public void testReadWriteFreeMps() throws Exception {
		LpSolve problem = LpSolve.makeLp(0, 4);
		problem.strAddConstraint("3 2 2 1", LpSolve.LE, 4);
		problem.strAddConstraint("0 4 3 1", LpSolve.GE, 3);
		problem.strSetObjFn("2 3 -2 3");

		String filename = "testmodel.mps";
		File file = new File(filename);
		if (file.exists())
			file.delete();

		problem.writeFreeMps(filename);
		assertTrue(file.exists());
		problem.deleteLp();

		problem = LpSolve.readFreeMps(filename, LpSolve.NORMAL);
		assertEquals(2, problem.getNrows());
		assertEquals(4, problem.getNcolumns());
		double[] objFn = problem.getPtrRow(0);
		assertEquals(4 + 1, objFn.length);
		assertEquals(2, objFn[1], 0.0);
		assertEquals(3, objFn[2], 0.0);
		assertEquals(-2, objFn[3], 0.0);
		assertEquals(3, objFn[4], 0.0);
		problem.deleteLp();
		if (file.exists())
			file.delete();
	}

	public void testProb() throws Exception {
		LpSolve problem = LpSolve.readLp("c:\\tmp\\api\\prob.lp",
				LpSolve.NORMAL, "ApiExample");
		problem.setScaling(LpSolve.SCALE_INTEGERS);
		problem.setBbFloorfirst(LpSolve.BRANCH_CEILING);
		problem.setBbRule(LpSolve.NODE_DEPTHFIRSTMODE);
		problem.setPivoting(LpSolve.PRICER_DANTZIG | LpSolve.PRICE_MULTIPLE);
		problem.printLp();
		problem.solve();
		problem.printObjective();
		problem.printSolution(1);
	}

}