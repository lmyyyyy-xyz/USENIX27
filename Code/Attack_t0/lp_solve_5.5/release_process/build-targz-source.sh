#!/bin/bash
set -e

. $(dirname "$0")/check_env_vars.sh
requiredEnvVars=("LPSOLVE_WORKSPACE" "LPSOLVE_VERSION" "LPSOLVE_SOURCE_ROOT_FOLDER")
assertEnvironmentVariablesAreNotEmpty "${requiredEnvVars[@]}"

cd ${LPSOLVE_WORKSPACE}
tar -czf ${LPSOLVE_WORKSPACE}/lp_solve_${LPSOLVE_VERSION}_source.tar.gz \
    --transform "s,^,${LPSOLVE_SOURCE_ROOT_FOLDER}/," \
    --exclude-vcs \
    --exclude-vcs-ignores \
    --exclude=output \
    --exclude=xli \
    --exclude=extra \
    --exclude=.github \
    --exclude=bfp/bfp_etaPFI \
    --exclude=bfp/bfp_GLPK \
    *
