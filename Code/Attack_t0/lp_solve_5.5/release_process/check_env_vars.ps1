function Assert-EnvironmentVariablesAreNotEmpty {
    param (
        [string[]]$VariableNames
    )

    $results = @()

    foreach ($varName in $VariableNames) {
        $envVar = Get-ChildItem Env:$varName -ErrorAction SilentlyContinue

        if ($envVar -and ($envVar.Value -ne "") ) {
            # Variable exists
        } else {
            $results += $varName
        }
    }

    if ($results.Count -gt 0) {
        throw "The following expected environment variables are missing: $results"
    }
}
