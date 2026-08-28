. $PSScriptRoot/check_env_vars.ps1
$requiredEnvVars = @("LPSOLVE_WORKSPACE", "LPSOLVE_VERSION", "LPSOLVE_PLATFORM", "LPSOLVE_GLPK_DIR_4_13", "LPSOLVE_GLPK_DIR_4_44")
# Needed by xli_MathProg's cvc8NOmsvcrt.bat
# $requiredEnvVars += "LPSOLVE_MYSQL_CONNECTOR_C_DIR"
Assert-EnvironmentVariablesAreNotEmpty $requiredEnvVars

$zipContentFolder = Join-Path ${env:Temp} "exe_${env:LPSOLVE_VERSION}_zip_content"
if (Test-Path -LiteralPath $zipContentFolder) {
    Remove-Item -LiteralPath $zipContentFolder -Verbose -Recurse -Force
}
New-Item -ItemType Directory -Path $zipContentFolder

echo "Building lp_solve.exe for platform ${env:LPSOLVE_PLATFORM}"
cd ${env:LPSOLVE_WORKSPACE}/lp_solve
./cvc8.bat
cp ${env:LPSOLVE_WORKSPACE}/lp_solve/bin/${env:LPSOLVE_PLATFORM}/lp_solve.exe $zipContentFolder

# TODO: we currently have version conflicts on the GLPK library used by bfp_GLPK (4.13) and xli_MathProg (4.44)
${env:glpkdir} = ${env:LPSOLVE_GLPK_DIR_4_13}
$bfpFolders = "bfp_etaPFI", "bfp_LUSOL", "bfp_GLPK"
foreach ($bfpFolder in $bfpFolders) {
    echo "Building $bfpFolder.dll for platform $env:LPSOLVE_PLATFORM"
    cd ${env:LPSOLVE_WORKSPACE}/bfp/$bfpFolder
    ./cvc8NOmsvcrt.bat
    cp ${env:LPSOLVE_WORKSPACE}/bfp/$bfpFolder/bin/${env:LPSOLVE_PLATFORM}/$bfpFolder.dll $zipContentFolder
}

${env:glpkdir} = ${env:LPSOLVE_GLPK_DIR_4_44}
$xliFolders = "xli_CPLEX", "xli_DIMACS", "xli_LINDO", "xli_MPS", "xli_XPRESS", "xli_MathProg"
if ( $env:LPSOLVE_PLATFORM -eq "win32" ) {
    # issues building them for now
    # $xliFolders += "xli_LPFML", "xli_ZIMPL"
}
foreach ($xliFolder in $xliFolders) {
    echo "Building $xliFolder.dll for platform $env:LPSOLVE_PLATFORM"
    cd ${env:LPSOLVE_WORKSPACE}/xli/$xliFolder
    ./cvc8NOmsvcrt.bat
    cp ${env:LPSOLVE_WORKSPACE}/xli/$xliFolder/bin/${env:LPSOLVE_PLATFORM}/$xliFolder.dll $zipContentFolder
}

cp ${env:LPSOLVE_WORKSPACE}/release_process/contents_exe_${env:LPSOLVE_PLATFORM}.txt $zipContentFolder/contents.txt

$zipPath = "${env:LPSOLVE_WORKSPACE}/lp_solve_${env:LPSOLVE_VERSION}_exe_${env:LPSOLVE_PLATFORM}.zip"

cd $zipContentFolder
echo "Packaging files from ${PWD} into ${zipPath}"
7z a -tzip -bso0 -bsp0 $zipPath *
