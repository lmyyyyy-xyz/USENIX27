	        O-Matrix interface for lp_solve version 5.5
		===========================================

Compile and build omlpsolve:
----------------------------

0. Under Windows, a precompiled driver is provided. So you don't have
   to compile the dll yourself if you don't make changes to the driver source.
   You can skip to the next section in this case.

1. Under Windows, the Microsoft Visual C/C++ compiler must be installed
   and the environment variables must be active do that when a command prompt
   is opened, the cl and nmake commands can be executed.

2. Go to directory lp_solve_5.5\extra\O-Matrix\lpsolve

3. To compile and build omlpsolve, enter the following command:
      cvc

Load the omlpsolve driver in the O-Matrix memory space:
-------------------------------------------------------

1. Under Windows, make sure that the lpsolve55.dll file is somewhere in the path.
   This dll is part of the lp_solve distribution. The lastest version of this dll
   can be found on the lp_solve yahoo site
   http://groups.yahoo.com/group/lp_solve/files/Version5.5/
   in the archive lp_solve_5.5_dev.zip

2. A precompiled O-Matrix driver is provided for Windows (omlpsolve.dll) in this archive.

3. Start O-Matrix

4. Enter the following command in O-Matrix:
      O> dll <path>\omlpsolve.dll, omlpsolve
   This can also be added in autoexec.oms to automatically load the omlpsolve driver.


Note that O-Matrix version 5.8 or above is strongly recommended. Lower versions (at least 5.7) should
work with this driver, but these versions don't have the ability to print information on the command window.
For example default while a solve is done, information is printed to the command window. This will
only be visible from version 5.8 or above.

Also see O-Matrix.htm for a more detailed description and examples.

Peter Notebaert
lpsolve@peno.be
