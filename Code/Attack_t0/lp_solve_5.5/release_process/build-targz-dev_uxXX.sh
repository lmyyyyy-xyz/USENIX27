#!/bin/bash
set -e

. $(dirname "$0")/check_env_vars.sh
requiredEnvVars=("LPSOLVE_WORKSPACE" "LPSOLVE_VERSION" "LPSOLVE_PLATFORM")
assertEnvironmentVariablesAreNotEmpty "${requiredEnvVars[@]}"

TAR_CONTENT_FOLDER=output/dev_${LPSOLVE_PLATFORM}
mkdir -p $TAR_CONTENT_FOLDER
TAR_CONTENT_FOLDER=$( realpath $TAR_CONTENT_FOLDER )

echo "Building lpsolve55 library for platform ${LPSOLVE_PLATFORM}"
cd lpsolve55
sh ccc
cp ${LPSOLVE_WORKSPACE}/lpsolve55/bin/${LPSOLVE_PLATFORM}/* $TAR_CONTENT_FOLDER

echo "Packaging lpsolve55 library for platform ${LPSOLVE_PLATFORM}"
cd ${LPSOLVE_WORKSPACE}
cp lp_Hash.h lp_lib.h lp_matrix.h lp_mipbb.h lp_SOS.h lp_types.h lp_utils.h $TAR_CONTENT_FOLDER
cd $TAR_CONTENT_FOLDER
tar -czf ${LPSOLVE_WORKSPACE}/lp_solve_${LPSOLVE_VERSION}_dev_${LPSOLVE_PLATFORM}.tar.gz *
