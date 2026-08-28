% makefile for building mxlpsolve for lpsolve VERSION 5.5
%
% Usage: Makefile({what {, debug {, wait}}})
%  what: '' or not provided: compile build all source code
%        else any combination of lpsolve.c, matlab.c hash.c
%  debug: 0 or not provided: no debug info
%         1: argument checking and print extra debug info.
%  wait: 1 or not provided: ask to press a key before starting compiling
%        0: immediately start compiling

function Makefile(what, debug, wait)

v = sscanf(version, '%d.%d');
%windir=getenv('windir');
%if isempty(windir) | length(windir) == 0
if ispc == 0
	lpsolvepath='../../..';
	objext='.o';
%	 libs=['-cxx -L' lpsolvepath '/lpsolve55 -llpsolve55 -lm'];
%        libs=['-cxx -L' lpsolvepath '/lpsolve55 -lm -ldl -llpsolve55']; % R2007a version ?
%        libs=['-cxx -L' lpsolvepath '/lpsolve55 -lm'];
        libs=['-cxx -L' lpsolvepath '/lpsolve55 -lm -ldl'];
        defs='';
else
	lpsolvepath='..\..\..';
	objext='.obj';
        defs='-D_WINDOWS -DWIN32';
        if (v(1) > 7) | (v(1) == 7 & v(2) >= 6)
                libs='';
                defs=[defs ' -DLPSOLVEAPIFROMLIB'];
        else
                if strcmp(computer, 'PCWIN64') == 0
                        libs='bin/win32/lp_explicit.lib';
                else
                        libs='bin/win64/lp_explicit.lib';
                end
        end
end

lpsolvelibpath='';

if nargin == 0 | isempty(what)
        what = 'lpsolve.c matlab.c hash.c';
end

if nargin < 2
        debug = 0;
end

if debug == 0
        debug = '';
else
        debug = ' -argcheck -DDEBUG'
end

if (v(1) > 7) | (v(1) == 7 & v(2) >= 3)
        SINCE73 = ' -largeArrayDims -DSINCE73';
else
        SINCE73 = '';
end

if nargin < 3
        wait = 1;
end

disp('Automatic compilation of Matlab MEX interface for lp_solve 5.5');
disp(' ');
disp(['We assume that lp_solve 5.5 is installed in: ' lpsolvepath]);
disp('If that is not correct path for lp_solve 5.5, modify this file accordingly.');
disp(' ');
disp('***************************************************************');
disp('*  Old version of MEX lp_solve files will be overwritten !!!  *');
disp('***************************************************************');
disp(' ');
if wait == 0
else
	disp('Press any key to continue');
	disp(' ');
	pause;
end
disp('Compiling in progress. Please wait...');

% compile lp that uses lp_solve 5.5
disp('compiling...');
eval(['mex' SINCE73 debug ' ' defs ' -DMATLAB -DINLINE=static -I' lpsolvepath ' ' lpsolvelibpath ' -c ' what]);
disp('linking...');
eval(['mex' SINCE73 ' lpsolve' objext ' matlab' objext ' hash' objext ' ' libs ' -output mxlpsolve']);

disp('Compiling finished.');
disp('You can now run ex and lpdemo on matlab command line to test.');
