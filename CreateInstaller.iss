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

[Run]
Filename: "{app}\VEXOTControl.exe"; Description: "{cm:LaunchProgram,VEXOTControl}"; Flags: nowait postinstall skipifsilent

[InstallDelete]
Type: files; Name: "{app}\*.*"

[UninstallDelete]
Type: filesandordirs; Name: "{app}\src"
Type: filesandordirs; Name: "{app}"

[Code]
function IsAppInstalled: Boolean;
var
  InstallPath: string;
begin
  // Define the installation path based on DefaultDirName
  InstallPath := ExpandConstant('{localappdata}\Programs\VEXOTControl\VEXOTControl.exe');
  
  // Check if VEXOTControl.exe exists in the installation directory
  if FileExists(InstallPath) then
  begin
    Result := True;  // Application is installed
  end
  else
  begin
    Result := False; // Application is not installed
  end;
end;

procedure InitializeWizard;
var
  ResultCode: Integer;  // Declare the ResultCode variable
begin
  // Check if the application is already installed by looking for VEXOTControl.exe
  if IsAppInstalled then
  begin
    MsgBox('Previous installation detected. Uninstalling...', mbInformation, MB_OK);
    // Uninstall the existing application silently
    if Exec(ExpandConstant('{localappdata}\Programs\VEXOTControl\unins000.exe'), '/VERYSILENT /SUPPRESSMSGBOXES /NORESTART', '', SW_HIDE, ewWaitUntilTerminated, ResultCode) then
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
