. $PSScriptRoot/check_env_vars.ps1
$requiredEnvVars = @("LPSOLVE_WORKSPACE")
Assert-EnvironmentVariablesAreNotEmpty $requiredEnvVars

cd ${env:LPSOLVE_WORKSPACE}/extra/man
./gen.bat
cp *.chm ${env:LPSOLVE_WORKSPACE}
