[Setup]
AppName=VEXOTControl
AppVersion={#Major}.{#Minor}.{#Build}
AppVerName=VEXOTControl - {#Major}.{#Minor}.{#Build}
AppPublisher=Rigaku Innovative Technologies Europe
VersionInfoCompany=Rigaku Innovative Technologies Europe
DefaultDirName={localappdata}\Programs\VEXOTControl
DefaultGroupName=VEXOTControl
OutputBaseFilename=VEXOTControlInstaller_v{#Major}.{#Minor}.{#Build}
OutputDir=D:\Projects\RIGAKU\VEXOTControl\bin\x64\Release
Compression=lzma
SolidCompression=yes
WizardStyle=modern
DisableWelcomePage=no
SetupIconFile=D:\Projects\RIGAKU\VEXOTControl\VEXOTControl\src\img\logo.ico
DisableDirPage=no
UninstallDisplayIcon={app}\VEXOTControl.exe

[Files]
Source: "D:\Projects\RIGAKU\VEXOTControl\bin\x64\Release\src\*"; DestDir: "{app}\src"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\Projects\RIGAKU\VEXOTControl\bin\x64\Release\bindy.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Projects\RIGAKU\VEXOTControl\bin\x64\Release\handel.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Projects\RIGAKU\VEXOTControl\bin\x64\Release\libximc.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Projects\RIGAKU\VEXOTControl\bin\x64\Release\opencv_world4100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Projects\RIGAKU\VEXOTControl\bin\x64\Release\xia_usb2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Projects\RIGAKU\VEXOTControl\bin\x64\Release\xiwrapper.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Projects\RIGAKU\VEXOTControl\bin\x64\Release\xw.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Projects\RIGAKU\VEXOTControl\bin\x64\Release\VEXOTControl.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Projects\RIGAKU\VEXOTControl\bin\x64\Release\KETEK.ini"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Projects\RIGAKU\VEXOTControl\bin\x64\Release\keyfile.sqlite"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Projects\RIGAKU\VEXOTControl\bin\x64\Release\table.txt"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\VEXOTControl"; Filename: "{app}\VEXOTControl.exe"; IconFilename: "{app}\VEXOTControl.ico"
Name: "{commondesktop}\VEXOTControl"; Filename: "{app}\VEXOTControl.exe"; IconFilename: "{app}\VEXOTControl.ico"

[Run]
Filename: "{app}\VEXOTControl.exe"; Description: "{cm:LaunchProgram,VEXOTControl}"; Flags: nowait postinstall skipifsilent
