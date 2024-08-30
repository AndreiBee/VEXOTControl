# Define package name
$repository_name = "VEXOTControl"

Write-Output "PowerShell script started at $(Get-Date)" >> "D:\Projects\RIGAKU\$repository_name\log.txt"

# Define major and minor version
$major_version = "1"  # Replace with actual major version
$minor_version = "10" # Replace with actual minor version

# Define paths
$release_folder = "D:\Projects\RIGAKU\$repository_name\bin\x64\Release"
$opencv_folder = "$env:OPENCV_LATEST\bin"
$ximc_folder = "$env:XIMC\win64"
$ketek_folder = "$env:KETEK1226\lib"
$other_files_folder = "D:\Projects\RIGAKU\$repository_name\$repository_name"

# Step 1: Copy opencv_world4100.dll file
Write-Output "Copying opencv_world4100.dll file into $release_folder" >> "D:\Projects\RIGAKU\$repository_name\log.txt"
Copy-Item -Path "$opencv_folder\opencv_world4100.dll" -Destination "$release_folder\opencv_world4100.dll" -Force

# Step 1: Copy XIMC files
Write-Output "Copying XIMC files into $release_folder" >> "D:\Projects\RIGAKU\$repository_name\log.txt"
Copy-Item -Path "$ximc_folder\bindy.dll" -Destination "$release_folder\bindy.dll" -Force
Copy-Item -Path "$ximc_folder\libximc.dll" -Destination "$release_folder\libximc.dll" -Force
Copy-Item -Path "$ximc_folder\xiwrapper.dll" -Destination "$release_folder\xiwrapper.dll" -Force
Copy-Item -Path "$ximc_folder\keyfile.sqlite" -Destination "$release_folder\keyfile.sqlite" -Force

# Step 2: Copy Ketek files
Write-Output "Copying Ketek files into $release_folder" >> "D:\Projects\RIGAKU\$repository_name\log.txt"
Copy-Item -Path "$ketek_folder\handel.dll" -Destination "$release_folder\handel.dll" -Force
Copy-Item -Path "$ketek_folder\xia_usb2.dll" -Destination "$release_folder\xia_usb2.dll" -Force
Copy-Item -Path "$ketek_folder\xw.dll" -Destination "$release_folder\xw.dll" -Force

# Step 3: Copy Other files
Write-Output "Copying other files into $release_folder" >> "D:\Projects\RIGAKU\$repository_name\log.txt"
Copy-Item -Path "$other_files_folder\KETEK.ini" -Destination "$release_folder\KETEK.ini" -Force
Copy-Item -Path "$other_files_folder\table.txt" -Destination "$release_folder\table.txt" -Force

# Step 6: Preparing name for the output archive
$commit_number = git rev-list --count HEAD  # Get the total number of commits in the repository
$archive_name = "${repository_name}_v${major_version}.${minor_version}.${commit_number}.7z"
$archive_path = "$release_folder\$archive_name"

# Step 7: Specify files to include in the archive
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

# Step 8: Create the 7z archive
Write-Output "Creating 7z archive - $archive_name" >> "D:\Projects\RIGAKU\$repository_name\log.txt"
& "C:\Program Files\7-Zip\7z.exe" a -t7z $archive_path $files_to_archive

# Step 10: Retrieve the latest commit message
$commit_message = git log -1 --pretty=%B

# Step 11: Define release notes with checksum
$tag_name = "v$major_version.$minor_version.$commit_number"
$release_notes = @"
## Release Notes for $archive_name

### Commit Message
- $commit_message

### Download Links
- [Download ${repository_name}_v${major_version}.${minor_version}.${commit_number}.7z](https://github.com/AndreiBee/$repository_name/releases/download/$tag_name/$archive_name)
"@

# Step 12: Upload to GitHub
Write-Output "Uploading 7z archive to GitHub" >> "D:\Projects\RIGAKU\$repository_name\log.txt"
gh release create $tag_name $archive_path --title "Release $tag_name" --notes "$release_notes"

# Step 13: Log
Write-Output "PowerShell script completed at $(Get-Date)" >> "D:\Projects\RIGAKU\$repository_name\log.txt"
