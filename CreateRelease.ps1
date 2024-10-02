# Define package name
$repository_name = "VEXOTControl"
$path_to_repository = "D:\Projects\RIGAKU\$repository_name"
Write-Output "-------------------------------------- [$(Get-Date)] --------------------------------------" >> "${path_to_repository}\log.txt"
Write-Output "PowerShell script started at [$(Get-Date)]" >> "${path_to_repository}\log.txt"

Write-Output "Start building the $repository_name in Release mode [$(Get-Date)]" >> "${path_to_repository}\log.txt"
# Set the path to your solution file
$solutionPath = "${path_to_repository}\$repository_name.sln"

# Set the path to MSBuild (you might need to adjust this depending on your VS installation)
$msbuildPath = "C:\Program Files\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe"

# Specify the build configuration (Release) and platform (e.g., x64, x86)
$buildConfiguration = "Release"
$platform = "x64"

# Build the solution using MSBuild
& $msbuildPath $solutionPath `
    /p:Configuration=$buildConfiguration `
    /p:Platform=$platform `
    /t:Build
	
Write-Output "Finished building the $repository_name in Release mode [$(Get-Date)]" >> "${path_to_repository}\log.txt"

# Define Inno Setup parameters
$inno_setup_script = "${path_to_repository}\CreateInstaller.iss"
# Copy Inno Setup script
$inno_setup_script_temp = "${path_to_repository}\CreateInstallerTemp.iss"
Copy-Item -Path "$inno_setup_script" -Destination "$inno_setup_script_temp" -Force

# Define major and minor version
$major_version = "1"  # Replace with actual major version
$minor_version = "10" # Replace with actual minor version

# Define paths
$release_folder = "${path_to_repository}\bin\x64\Release"
$opencv_folder = "$env:OPENCV_LATEST\bin"
$ximc_folder = "$env:XIMC_LATEST\win64"
$ketek_folder = "$env:KETEK_LATEST\lib"
$other_files_folder = "${path_to_repository}\$repository_name"

# Remove all Installers and 7z archives (previous versions)
# Get all .exe files except Project.exe
Get-ChildItem -Path $release_folder -Filter *.exe | Where-Object { $_.Name -ne "$repository_name.exe" } | Remove-Item

# Get all .7z files except About.7z
Get-ChildItem -Path $release_folder -Filter *.7z | Where-Object { $_.Name -ne "About.7z" } | Remove-Item

# Copy opencv_world4100.dll file
Write-Output "Copying opencv_world4100.dll file into $release_folder [$(Get-Date)]" >> "${path_to_repository}\log.txt"
Copy-Item -Path "$opencv_folder\opencv_world4100.dll" -Destination "$release_folder\opencv_world4100.dll" -Force

# Copy XIMC files
Write-Output "Copying XIMC files into $release_folder [$(Get-Date)]" >> "${path_to_repository}\log.txt"
Copy-Item -Path "$ximc_folder\bindy.dll" -Destination "$release_folder\bindy.dll" -Force
Copy-Item -Path "$ximc_folder\libximc.dll" -Destination "$release_folder\libximc.dll" -Force
Copy-Item -Path "$ximc_folder\xiwrapper.dll" -Destination "$release_folder\xiwrapper.dll" -Force
Copy-Item -Path "$other_files_folder\keyfile.sqlite" -Destination "$release_folder\keyfile.sqlite" -Force

# Copy Ketek files
Write-Output "Copying Ketek files into $release_folder [$(Get-Date)]" >> "${path_to_repository}\log.txt"
Copy-Item -Path "$ketek_folder\handel.dll" -Destination "$release_folder\handel.dll" -Force
Copy-Item -Path "$ketek_folder\xia_usb2.dll" -Destination "$release_folder\xia_usb2.dll" -Force
Copy-Item -Path "$ketek_folder\xw.dll" -Destination "$release_folder\xw.dll" -Force

# Copy Other files
Write-Output "Copying other files into $release_folder [$(Get-Date)]" >> "${path_to_repository}\log.txt"
Copy-Item -Path "$other_files_folder\KETEK.ini" -Destination "$release_folder\KETEK.ini" -Force
Copy-Item -Path "$other_files_folder\table.txt" -Destination "$release_folder\table.txt" -Force

# Preparing name for the output archive
$commit_number = git rev-list --count HEAD  # Get the total number of commits in the repository
$build_version = "$major_version.$minor_version.$commit_number"
$archive_name = "${repository_name}_v${major_version}.${minor_version}.${commit_number}.7z"
$archive_path = "$release_folder\$archive_name"

# Specify files to include in the archive
$files_to_archive = @(
    "$release_folder\src",
    "$release_folder\bindy.dll",
	"$release_folder\handel.dll",
	"$release_folder\libximc.dll",
	"$release_folder\opencv_world4100.dll",
	"$release_folder\xia_usb2.dll",
    "$release_folder\xiwrapper.dll",
	"$release_folder\xw.dll", 
    "$release_folder\$repository_name.exe",
	"$release_folder\KETEK.ini",
	"$release_folder\keyfile.sqlite",
	"$release_folder\table.txt"
)

# Create the 7z archive
Write-Output "Creating 7z archive - $archive_name [$(Get-Date)]" >> "${path_to_repository}\log.txt"
& "C:\Program Files\7-Zip\7z.exe" a -t7z $archive_path $files_to_archive

# Retrieve the latest commit message
$commit_message = git log -1 --pretty=%B

# Define release notes with checksum
$tag_name = "v$major_version.$minor_version.$commit_number"

# Replace placeholders in the Inno Setup script
(Get-Content $inno_setup_script_temp) -replace "{#Major}", $major_version -replace "{#Minor}", $minor_version -replace "{#Build}", $commit_number -replace "{#RepoName}", $repository_name | Set-Content $inno_setup_script_temp

# Run Inno Setup to generate the installer
Write-Output "Running Inno Setup to generate the installer [$(Get-Date)]" >> "${path_to_repository}\log.txt"
& "C:\Program Files (x86)\Inno Setup 6\ISCC.exe" $inno_setup_script_temp

# Remove the Temp Inno file
Remove-Item -Path "$inno_setup_script_temp"

# Define the path of the generated installer
$installer_path = "${path_to_repository}\bin\x64\Release\${repository_name}Installer_v$build_version.exe"
$fileHash = (Get-FileHash -Algorithm SHA256 -Path $installer_path).Hash
Write-Output "SHA256: [$fileHash]" >> "${path_to_repository}\log.txt"

$release_notes = @"
## Release Notes for ${repository_name}_v${major_version}.${minor_version}.${commit_number}

### Commit Message
- $commit_message

### Download Links
- [Download ${repository_name}Installer_v$build_version.exe](https://github.com/AndreiBee/${repository_name}/releases/download/$tag_name/${repository_name}Installer_v${build_version}.exe)
- [Download ${repository_name}_v${major_version}.${minor_version}.${commit_number}.7z](https://github.com/AndreiBee/$repository_name/releases/download/$tag_name/$archive_name)

### SHA256
```
$fileHash
```
"@

# Upload to GitHub
Write-Output "Upload $archive_name and ${repository_name}Installer_v$build_version.exe to GitHub [$(Get-Date)]" >> "${path_to_repository}\log.txt"
gh release create $tag_name $installer_path $archive_path --title "Release $tag_name" --notes "$release_notes"

# Upload to OneDrive
Write-Output "Upload $archive_name and ${repository_name}Installer_v$build_version.exe to OneDrive [$(Get-Date)]" >> "${path_to_repository}\log.txt"
Copy-Item -Path "$installer_path" -Destination "C:\Users\Andrej Pcelovodov\OneDrive - Rigaku Americas Holding\EXPORT\VEXOTControl\${repository_name}Installer_v$build_version.exe" -Force
Copy-Item -Path "$archive_path" -Destination "C:\Users\Andrej Pcelovodov\OneDrive - Rigaku Americas Holding\EXPORT\VEXOTControl\${repository_name}_v${major_version}.${minor_version}.${commit_number}.7z" -Force

# Log
Write-Output "PowerShell script completed at [$(Get-Date)]" >> "${path_to_repository}\log.txt"
