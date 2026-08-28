#!/bin/bash
set -e

. $(dirname "$0")/check_env_vars.sh
requiredEnvVars=("LPSOLVE_WORKSPACE" "LPSOLVE_VERSION" "LPSOLVE_SOURCE_ROOT_FOLDER")
assertEnvironmentVariablesAreNotEmpty "${requiredEnvVars[@]}"

cd ${LPSOLVE_WORKSPACE}
tar -czf ${LPSOLVE_WORKSPACE}/lp_solve_${LPSOLVE_VERSION}_AMPL_source.tar.gz \
    --transform "s,^extra/man,extra/AMPL/solvers/lpsolve," \
    --transform "s,^,${LPSOLVE_SOURCE_ROOT_FOLDER}/," \
    --exclude-vcs-ignores \
    extra/AMPL/solvers \
    extra/man/AMPL.htm
