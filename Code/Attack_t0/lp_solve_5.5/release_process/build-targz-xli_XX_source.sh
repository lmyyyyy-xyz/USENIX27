#!/bin/bash
set -e

. $(dirname "$0")/check_env_vars.sh
requiredEnvVars=("LPSOLVE_WORKSPACE" "LPSOLVE_VERSION" "LPSOLVE_SOURCE_ROOT_FOLDER")
assertEnvironmentVariablesAreNotEmpty "${requiredEnvVars[@]}"

cd ${LPSOLVE_WORKSPACE}

for folder in xli_CPLEX xli_LINDO xli_LPFML xli_MathProg xli_MPS xli_XPRESS ;
do
    echo "Packaging lp_solve_${LPSOLVE_VERSION}_${folder}_source.tar.gz"
    tar -czf ${LPSOLVE_WORKSPACE}/lp_solve_${LPSOLVE_VERSION}_${folder}_source.tar.gz \
        --transform "s,^,${LPSOLVE_SOURCE_ROOT_FOLDER}/," \
        --exclude-vcs-ignores \
        xli/${folder} \
        xli/*.*
done

echo "Packaging lp_solve_${LPSOLVE_VERSION}_xli_DIMACS_source.tar.gz"
tar -czf ${LPSOLVE_WORKSPACE}/lp_solve_${LPSOLVE_VERSION}_xli_DIMACS_source.tar.gz \
    --transform "s,^extra/man,xli/xli_DIMACS," \
    --transform "s,^,${LPSOLVE_SOURCE_ROOT_FOLDER}/," \
    --exclude-vcs-ignores \
    xli/xli_DIMACS \
    xli/*.* \
    extra/man/DIMACS_*.htm \
    extra/man/dimacs_*.gif
