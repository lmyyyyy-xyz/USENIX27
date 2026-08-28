#!/bin/bash
set -e

. $(dirname "$0")/check_env_vars.sh
requiredEnvVars=("LPSOLVE_WORKSPACE" "LPSOLVE_VERSION" "LPSOLVE_SOURCE_ROOT_FOLDER")
assertEnvironmentVariablesAreNotEmpty "${requiredEnvVars[@]}"

cd ${LPSOLVE_WORKSPACE}
for folder in Euler FreeMat PHP Python Sysquake ;
do
    echo "Packaging lp_solve_${LPSOLVE_VERSION}_${folder}_source.tar.gz"
    tar -czf ${LPSOLVE_WORKSPACE}/lp_solve_${LPSOLVE_VERSION}_${folder}_source.tar.gz \
        --transform "s,^extra/man,extra/${folder}," \
        --transform "s,^,${LPSOLVE_SOURCE_ROOT_FOLDER}/," \
        --exclude-vcs-ignores \
        extra/${folder} \
        extra/man/${folder}.htm
done
