. $PSScriptRoot/check_env_vars.ps1
$requiredEnvVars = @("LPSOLVE_WORKSPACE", "LPSOLVE_VERSION", "LPSOLVE_PLATFORM")
Assert-EnvironmentVariablesAreNotEmpty $requiredEnvVars

echo "Building lpsolve55 library for platform ${env:LPSOLVE_PLATFORM}"
cd ${env:LPSOLVE_WORKSPACE}/lpsolve55
./cvc8NOmsvcrt.bat

$zipPath = "${env:LPSOLVE_WORKSPACE}/lp_solve_${env:LPSOLVE_VERSION}_dev_${env:LPSOLVE_PLATFORM}.zip"

cd ${env:LPSOLVE_WORKSPACE}
echo "Packaging files from ${PWD} into ${zipPath}"
7z a -tzip -bso0 -bsp0 $zipPath `
    lp_Hash.h `
    lp_lib.h `
    lp_matrix.h `
    lp_mipbb.h `
    lp_SOS.h `
    lp_types.h `
    lp_utils.h

cd ${env:LPSOLVE_WORKSPACE}/lpsolve55/bin/${env:LPSOLVE_PLATFORM}
echo "Packaging files from ${PWD} into ${zipPath}"
7z a -tzip -bso0 -bsp0 $zipPath `
    * `
    '-x!lpsolve55.exp'
