. $PSScriptRoot/check_env_vars.ps1
$requiredEnvVars = @("LPSOLVE_WORKSPACE", "LPSOLVE_VERSION")
Assert-EnvironmentVariablesAreNotEmpty $requiredEnvVars

$zipPath = "${env:LPSOLVE_WORKSPACE}/lp_solve_${env:LPSOLVE_VERSION}_java.zip"

cd ${env:LPSOLVE_WORKSPACE}/extra

# TODO, this could probably be done with .gitattributes
echo "Fixing newlines of Unix scripts"
$scriptFiles=@("lp_solve_5.5_java/demo/build", "lp_solve_5.5_java/demo/run_demo", "lp_solve_5.5_java/demo/run_unittests", "lp_solve_5.5_java/src/java/lpsolve/build")
foreach ($f in $scriptFiles) {
    (Get-Content $f -Raw).Replace("`r`n","`n") | Set-Content $f -NoNewLine -Force
}

echo "Packaging files from ${PWD} into ${zipPath}"
7z a -tzip -bso0 -bsp0 -r $zipPath `
    lp_solve_5.5_java/demo `
    lp_solve_5.5_java/demo2 `
    lp_solve_5.5_java/docs `
    lp_solve_5.5_java/src `
    lp_solve_5.5_java/CHANGES.txt `
    lp_solve_5.5_java/LGPL `
    lp_solve_5.5_java/README.html `
    '-x!lp_solve_5.5_java/demo/*.class' `
    '-x!lp_solve_5.5_java/demo/*.log' `
    '-x!lp_solve_5.5_java/demo/lpsolve' `
    '-x!lp_solve_5.5_java/src/java/*.class' `
    '-x!model.lp'
