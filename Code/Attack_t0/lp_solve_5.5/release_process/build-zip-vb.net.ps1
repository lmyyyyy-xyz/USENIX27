. $PSScriptRoot/check_env_vars.ps1
$requiredEnvVars = @("LPSOLVE_WORKSPACE", "LPSOLVE_VERSION")
Assert-EnvironmentVariablesAreNotEmpty $requiredEnvVars

$zipPath = "${env:LPSOLVE_WORKSPACE}/lp_solve_${env:LPSOLVE_VERSION}_vb.net.zip"

cd ${env:LPSOLVE_WORKSPACE}/extra/VB.NET
echo "Packaging files from ${PWD} into ${zipPath}"
7z a -tzip -bso0 -bsp0 $zipPath `
    * `
    '-x!app.config'
