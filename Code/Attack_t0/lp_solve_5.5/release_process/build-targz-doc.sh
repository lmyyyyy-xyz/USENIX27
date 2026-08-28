#!/bin/bash
set -e

. $(dirname "$0")/check_env_vars.sh
requiredEnvVars=("LPSOLVE_WORKSPACE" "LPSOLVE_VERSION")
assertEnvironmentVariablesAreNotEmpty "${requiredEnvVars[@]}"

cd ${LPSOLVE_WORKSPACE}
cd extra/man
tar -czf ${LPSOLVE_WORKSPACE}/lp_solve_${LPSOLVE_VERSION}_doc.tar.gz \
    --exclude-vcs-ignores \
    --exclude=arv \
    --exclude=Win32 \
    --exclude=*.bat \
    --exclude=BuildLog.htm \
    --exclude=HTMLHelp.* \
    --exclude=lp_solve.hh* \
    --exclude=man.* \
    --exclude=man0.* \
    *
