[Setup]
AppId={{GUID-1234-5678-ABCD-1234567890AB}}
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

[Dirs]
Name: "{localappdata}\Programs"; Permissions: users-full

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
Source: "D:\Projects\RIGAKU\VEXOTControl\VEXOTControl\src\img\logo.ico"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\VEXOTControl"; Filename: "{app}\VEXOTControl.exe"; IconFilename: "{app}\logo.ico"
Name: "{commondesktop}\VEXOTControl"; Filename: "{app}\VEXOTControl.exe"; IconFilename: "{app}\logo.ico"
Name: "{commonprograms}\VEXOTControl"; Filename: "{app}\VEXOTControl.exe"; IconFilename: "{app}\logo.ico"
Name: "{commonstartup}\VEXOTControl"; Filename: "{app}\VEXOTControl.exe"; IconFilename: "{app}\logo.ico"

[Registry]
Root: HKCU; Subkey: "SOFTWARE\RITE\VEXOTControl"; ValueType: string; ValueName: "InstallPath"; ValueData: "{app}"; Flags: createvalueifdoesntexist uninsdeletekey

[Run]
Filename: "{app}\VEXOTControl.exe"; Description: "{cm:LaunchProgram,VEXOTControl}"; Flags: nowait postinstall skipifsilent

[InstallDelete]
Type: files; Name: "{app}\*.*"

[UninstallDelete]
Type: filesandordirs; Name: "{app}\src"
Type: filesandordirs; Name: "{app}"

[Code]
function GetInstallPath: string;
var
  InstallPath: string;
begin
  // Initialize result to empty string
  Result := '';

  // Read the installation path from the registry
  if RegQueryStringValue(HKCU, 'SOFTWARE\RITE\VEXOTControl', 'InstallPath', InstallPath) then
  begin
    Result := InstallPath;
  end;
end;

procedure CurStepChanged(CurStep: TSetupStep);
var
  InstallPath: string;
  ResultCode: Integer;
begin
  if CurStep = ssInstall then
  begin
    InstallPath := GetInstallPath;

    // Check if the application is already installed
    if InstallPath <> '' then
    begin
      // MsgBox('Previous installation detected. Uninstalling...', mbInformation, MB_OK);

      // Construct the path to unins000.exe
      InstallPath := ExpandConstant(InstallPath + '\unins000.exe');

      // Uninstall the existing application silently
      if Exec(InstallPath, '/VERYSILENT /SUPPRESSMSGBOXES /NORESTART', '', SW_HIDE, ewWaitUntilTerminated, ResultCode) then
      begin
        if ResultCode <> 0 then
        begin
          MsgBox('Error during uninstallation. Error code: ' + IntToStr(ResultCode), mbError, MB_OK);
        end;
      end
      else
      begin
        MsgBox('Failed to execute uninstallation process.', mbError, MB_OK);
      end;
    end;
  end;
end;
