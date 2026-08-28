#!/bin/bash
set -e

. $(dirname "$0")/check_env_vars.sh
requiredEnvVars=("LPSOLVE_WORKSPACE" "LPSOLVE_VERSION" "LPSOLVE_PLATFORM")
assertEnvironmentVariablesAreNotEmpty "${requiredEnvVars[@]}"

TAR_CONTENT_FOLDER=output/exe_${LPSOLVE_PLATFORM}
mkdir -p $TAR_CONTENT_FOLDER
TAR_CONTENT_FOLDER=$( realpath $TAR_CONTENT_FOLDER )

for folder in bfp/bfp_GLPK bfp/bfp_etaPFI bfp/bfp_LUSOL xli/xli_CPLEX xli/xli_LINDO xli/xli_MPS xli/xli_XPRESS lp_solve
do
    echo "Building $folder for platform ${LPSOLVE_PLATFORM}"
    cd ${LPSOLVE_WORKSPACE}/$folder
    sh ccc
    if [ "$folder" = "lp_solve" ]; then
        cp ${LPSOLVE_WORKSPACE}/$folder/bin/${LPSOLVE_PLATFORM}/lp_solve $TAR_CONTENT_FOLDER
    else
        cp ${LPSOLVE_WORKSPACE}/$folder/bin/${LPSOLVE_PLATFORM}/*.so $TAR_CONTENT_FOLDER
    fi
done

cp ${LPSOLVE_WORKSPACE}/release_process/contents_exe_${LPSOLVE_PLATFORM}.txt $TAR_CONTENT_FOLDER/contents.txt

cd $TAR_CONTENT_FOLDER
tar -czf ${LPSOLVE_WORKSPACE}/lp_solve_${LPSOLVE_VERSION}_exe_${LPSOLVE_PLATFORM}.tar.gz *
