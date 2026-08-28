#!/bin/bash
function assertEnvironmentVariablesAreNotEmpty() {
    local variableNames=("$@")
    local missingVariables=()
    for variableName in "${variableNames[@]}"; do
        if [ "${!variableName}" == "" ]; then
            missingVariables+=($variableName)
        fi
    done

    if [ ${#missingVariables[@]}  -gt 0 ]; then
        >&2 echo "The following expected environment variables are missing: ${missingVariables[@]}"
        exit 1
    fi
}
