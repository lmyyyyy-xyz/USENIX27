. $PSScriptRoot/check_env_vars.ps1
$requiredEnvVars = @("LPSOLVE_WORKSPACE", "LPSOLVE_VERSION", "LPSOLVE_PLATFORM")
Assert-EnvironmentVariablesAreNotEmpty $requiredEnvVars

$zipPath = "${env:LPSOLVE_WORKSPACE}/lp_solve_${env:LPSOLVE_VERSION}_MATLAB_exe_${env:LPSOLVE_PLATFORM}.zip"

cd ${env:LPSOLVE_WORKSPACE}/extra/MATLAB/lpsolve
echo "Packaging files from ${PWD} into ${zipPath}"
7z a -tzip -bso0 -bsp0 $zipPath `
    *.m `
    changes `
    README.txt `
    '-x!Makefile.m'

cd ${env:LPSOLVE_WORKSPACE}/extra/man
echo "Packaging files from ${PWD} into ${zipPath}"
7z a -tzip -bso0 -bsp0 $zipPath `
    MATLAB.htm
