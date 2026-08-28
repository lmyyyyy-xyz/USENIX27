#!/bin/bash
set -e

. $(dirname "$0")/check_env_vars.sh
requiredEnvVars=("LPSOLVE_WORKSPACE" "LPSOLVE_VERSION" "LPSOLVE_SOURCE_ROOT_FOLDER")
assertEnvironmentVariablesAreNotEmpty "${requiredEnvVars[@]}"

cd ${LPSOLVE_WORKSPACE}
tar -czf ${LPSOLVE_WORKSPACE}/lp_solve_${LPSOLVE_VERSION}_octave_source.tar.gz \
    --transform "s,^extra/man/octave.htm,extra/octave/lpsolve/Octave.htm," \
    --transform "s,^,${LPSOLVE_SOURCE_ROOT_FOLDER}/," \
    --exclude-vcs-ignores \
    extra/octave \
    extra/man/octave.htm
