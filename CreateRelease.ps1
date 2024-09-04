# Define package name
$repository_name = "VEXOTControl"
Write-Output "-------------------------------------- [$(Get-Date)] --------------------------------------" >> "D:\Projects\RIGAKU\$repository_name\log.txt"
Write-Output "PowerShell script started at [$(Get-Date)]" >> "D:\Projects\RIGAKU\$repository_name\log.txt"

# Define Inno Setup parameters
$inno_setup_script = "D:\Projects\RIGAKU\$repository_name\CreateInstaller.iss"
# Copy Inno Setup script
$inno_setup_script_temp = "D:\Projects\RIGAKU\$repository_name\CreateInstallerTemp.iss"
Copy-Item -Path "$inno_setup_script" -Destination "$inno_setup_script_temp" -Force

# Define major and minor version
$major_version = "1"  # Replace with actual major version
$minor_version = "10" # Replace with actual minor version

# Define paths
$release_folder = "D:\Projects\RIGAKU\$repository_name\bin\x64\Release"
$opencv_folder = "$env:OPENCV_LATEST\bin"
$ximc_folder = "$env:XIMC\win64"
$ketek_folder = "$env:KETEK1226\lib"
$other_files_folder = "D:\Projects\RIGAKU\$repository_name\$repository_name"

# Copy opencv_world4100.dll file
Write-Output "Copying opencv_world4100.dll file into $release_folder [$(Get-Date)]" >> "D:\Projects\RIGAKU\$repository_name\log.txt"
Copy-Item -Path "$opencv_folder\opencv_world4100.dll" -Destination "$release_folder\opencv_world4100.dll" -Force

# Copy XIMC files
Write-Output "Copying XIMC files into $release_folder [$(Get-Date)]" >> "D:\Projects\RIGAKU\$repository_name\log.txt"
Copy-Item -Path "$ximc_folder\bindy.dll" -Destination "$release_folder\bindy.dll" -Force
Copy-Item -Path "$ximc_folder\libximc.dll" -Destination "$release_folder\libximc.dll" -Force
Copy-Item -Path "$ximc_folder\xiwrapper.dll" -Destination "$release_folder\xiwrapper.dll" -Force
Copy-Item -Path "$ximc_folder\keyfile.sqlite" -Destination "$release_folder\keyfile.sqlite" -Force

# Copy Ketek files
Write-Output "Copying Ketek files into $release_folder [$(Get-Date)]" >> "D:\Projects\RIGAKU\$repository_name\log.txt"
Copy-Item -Path "$ketek_folder\handel.dll" -Destination "$release_folder\handel.dll" -Force
Copy-Item -Path "$ketek_folder\xia_usb2.dll" -Destination "$release_folder\xia_usb2.dll" -Force
Copy-Item -Path "$ketek_folder\xw.dll" -Destination "$release_folder\xw.dll" -Force

# Copy Other files
Write-Output "Copying other files into $release_folder [$(Get-Date)]" >> "D:\Projects\RIGAKU\$repository_name\log.txt"
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
Write-Output "Creating 7z archive - $archive_name [$(Get-Date)]" >> "D:\Projects\RIGAKU\$repository_name\log.txt"
& "C:\Program Files\7-Zip\7z.exe" a -t7z $archive_path $files_to_archive

# Retrieve the latest commit message
$commit_message = git log -1 --pretty=%B

# Define release notes with checksum
$tag_name = "v$major_version.$minor_version.$commit_number"

# Replace placeholders in the Inno Setup script
(Get-Content $inno_setup_script_temp) -replace "{#Major}", $major_version -replace "{#Minor}", $minor_version -replace "{#Build}", $commit_number | Set-Content $inno_setup_script_temp

# Run Inno Setup to generate the installer
Write-Output "Running Inno Setup to generate the installer [$(Get-Date)]" >> "D:\Projects\RIGAKU\$repository_name\log.txt"
& "C:\Program Files (x86)\Inno Setup 6\ISCC.exe" $inno_setup_script_temp

# Remove the Temp Inno file
Remove-Item -Path "$inno_setup_script_temp"

# Define the path of the generated installer
$installer_path = "D:\Projects\RIGAKU\${repository_name}\bin\x64\Release\${repository_name}Installer_v$build_version.exe"
$fileHash = (Get-FileHash -Algorithm SHA256 -Path $installer_path).Hash
Write-Output "SHA256: [$fileHash]" >> "D:\Projects\RIGAKU\$repository_name\log.txt"

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

# Create a manifest file
$manifest_file = "D:\Projects\RIGAKU\$repository_name\RITE.$repository_name.yml"
# Check if the directory exists before creating it
$manifest_file_directory = "D:\Projects\RIGAKU\$repository_name\manifests\RITE\$repository_name\${major_version}.${minor_version}.${commit_number}"
if (-Not (Test-Path -Path $manifest_file_directory)) {
    New-Item -Path $manifest_file_directory -ItemType Directory
} else {
    Write-Host "Directory $manifest_file_directory already exists."
}
#New-Item -Path "D:\Projects\RIGAKU\$repository_name\manifests\RITE\$repository_name\" -Name "${major_version}.${minor_version}.${commit_number}" -ItemType "directory"
$manifest_file_temp = "D:\Projects\RIGAKU\$repository_name\manifests\RITE\$repository_name\${major_version}.${minor_version}.${commit_number}\RITE.$repository_name.yml"
Copy-Item -Path "$manifest_file" -Destination "$manifest_file_temp" -Force
(Get-Content $manifest_file_temp) -replace "{#Major}", $major_version -replace "{#Minor}", $minor_version -replace "{#Build}", $commit_number -replace "{#Hash256}", $fileHash | Set-Content $manifest_file_temp
#git add $manifest_file_temp
#git commit --amend --no-edit

# Upload to GitHub
Write-Output "Upload $archive_name and ${repository_name}Installer_v$build_version.exe to GitHub [$(Get-Date)]" >> "D:\Projects\RIGAKU\$repository_name\log.txt"
gh release create $tag_name $installer_path $archive_path --title "Release $tag_name" --notes "$release_notes"

# Upload to OneDrive
Write-Output "Upload $archive_name and ${repository_name}Installer_v$build_version.exe to OneDrive [$(Get-Date)]" >> "D:\Projects\RIGAKU\$repository_name\log.txt"
Copy-Item -Path "$installer_path" -Destination "C:\Users\andrei.pchalavodau\OneDrive - Rigaku Americas Holding\EXPORT\VEXOTControl\${repository_name}Installer_v$build_version.exe" -Force
Copy-Item -Path "$archive_path" -Destination "C:\Users\andrei.pchalavodau\OneDrive - Rigaku Americas Holding\EXPORT\VEXOTControl\${repository_name}_v${major_version}.${minor_version}.${commit_number}.7z" -Force

# Log
Write-Output "PowerShell script completed at [$(Get-Date)]" >> "D:\Projects\RIGAKU\$repository_name\log.txt"
