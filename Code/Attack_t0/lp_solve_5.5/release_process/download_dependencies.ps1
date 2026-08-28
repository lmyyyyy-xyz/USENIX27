# Requires to have 7z.exe in PATH
function Download-GLPK {
    param (
        [string]$Version,
        [string]$Destination
    )

    $tempFolder = [System.IO.Path]::GetTempFileName()
    Remove-Item $tempFolder
    New-Item -ItemType Directory -Path $tempFolder
    $tarGzPath    = Join-Path $tempFolder "glpk-$Version.tar.gz"
    $tarPath      = Join-Path $tempFolder "glpk-$Version.tar"
    $untarredPath = Join-Path $tempFolder "glpk-$Version"

    New-Item -ItemType Directory -Path $Destination
    Invoke-WebRequest -Uri https://slackware.cs.utah.edu/pub/gnu/glpk/glpk-$Version.tar.gz -OutFile $tarGzPath
    7z x $tarGzPath -o"$tempFolder" # creates file at $tarPath
    7z x -aoa -ttar -spe $tarPath -o"$untarredPath"
    Move-Item -Path $untarredPath\* -Destination $Destination

    # Cleanup
    rm $tempFolder -Recurse
}

function Download-MySQLConnectorC {
    param (
        [string]$Version,
        [string]$Destination,
        [bool]$Is32Bit = $false
    )

    $arch = if ($Is32Bit) { "win32" } else { "winx64" }
    $zipFileWithoutExtension = "mysql-connector-c-noinstall-$Version-$arch"
    $url = "https://cdn.mysql.com/archives/mysql-connector-c/$zipFileWithoutExtension.zip"

    $tempFolder = [System.IO.Path]::GetTempFileName()
    Remove-Item $tempFolder
    New-Item -ItemType Directory -Path $tempFolder
    $zipPath      = Join-Path $tempFolder "$zipFileWithoutExtension.zip"
    $unzippedPath = Join-Path $tempFolder $zipFileWithoutExtension

    New-Item -ItemType Directory -Path $Destination
    Invoke-WebRequest -Uri $url -OutFile $zipPath
    7z x $zipPath -o"$tempFolder" # creates file at $unzippedPath
    Move-Item -Path $unzippedPath\* -Destination $Destination

    # Cleanup
    rm $tempFolder -Recurse
}
