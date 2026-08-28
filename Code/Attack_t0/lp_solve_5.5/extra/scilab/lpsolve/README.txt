	        Scilab interface for lp_solve version 5.5
		=========================================

Compile and build sclpsolve:
----------------------------

1. Under Windows, the Microsoft Visual C/C++ compiler must be installed
   and the environment variables must be active do that when a command prompt
   is opened, the cl and nmake commands can be executed.
   Under Unix/Linux, the standard c compiler is used.

2. Edit the file Path.incl and change pathnames as needed.

3. Start scilab

4. Check under scilab that the current directory is the lpsolve directory.
   Use the scilab pwd command to show the current directory.
   With the chdir command, you can change the current directory.
   This current directory must be lp_solve_5.5/extra/scilab/lpsolve
   example: chdir('/lp_solve/lp_solve_5.5/extra/scilab/lpsolve')

5. To compile and build sclpsolve, enter the following command in scilab:
      -->exec builder.sce
   This should be done once to build the sclpsolve driver and to produce
   the file loader.sce.

Load the sclpsolve driver in the scilab memory space:
-----------------------------------------------------

1. Under Windows, make sure that the lpsolve55.dll file is somewhere in the path
   Under Unix/Linux, make sure that the liblpsolve55.so shared library is in /usr/lib
   or /lib so that Unix can find it.

2. A precompiled library is provided for Windows (sclpsolve.dll).
   For Unix/Linux, it is required that the sclpsolve driver is first build.
   That must be done only once. So if you haven't taken the steps yet
   to build the sclpsolve driver, then do this first as described at
   the beginning of this file.

3. Start scilab

4. Check under scilab that the current directory is the lpsolve directory.
   Use the scilab pwd command to show the current directory.
   With the chdir command, you can change the current directory.
   This current directory must be lp_solve_5.5/extra/scilab/lpsolve
   example: chdir('/lp_solve/lp_solve_5.5/extra/scilab/lpsolve')

5. Enter the following command in scilab:
      -->exec loader.sce


Also see Scilab.htm for a more detailed description and examples.

Peter Notebaert
lpsolve@peno.be
