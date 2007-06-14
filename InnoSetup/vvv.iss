; -- vvv.iss --
; install script for vvv

#pragma option -v+
#pragma verboselevel 9

;#define Debug

#define AppName "VVV (Virtual Volumes View)"
#define ExeName "vvv.exe"
#define AppVersion "0.6"

[Setup]
AppId=VVV-fu-ku-jitsu
AppName={#AppName}
AppVerName={#AppName} version {#AppVersion}
DefaultDirName={pf}\{#AppName}
DefaultGroupName={#AppName}
UninstallDisplayIcon={app}\{#ExeName}
LicenseFile=License.txt
VersionInfoVersion={#AppVersion}
OutputDir=.
;OutputBaseFilename=VVV- + {#AppVersion} + -Setup
OutputBaseFilename=VVV-0.6-Setup

[Tasks]
Name: desktopicon; Description: {cm:CreateDesktopIcon}

[Files]
Source: ..\vc_msw\{#ExeName}; DestDir: {app}
Source: msvcr71.dll; DestDir: {app}
Source: fbclient.dll; DestDir: {app}
Source: firebird.msg; DestDir: {app}
Source: icudt30.dll; DestDir: {app}
Source: icuin30.dll; DestDir: {app}
Source: icuuc30.dll; DestDir: {app}
Source: instructions.html; DestDir: {app}
Source: License.txt; DestDir: {app}
Source: msvcp71.dll; DestDir: {app}
Source: intl\fbintl.dll; DestDir: {app}\intl
Source: intl\fbintl.conf; DestDir: {app}\intl
Source: ..\vvv-struct-update.fdb; DestDir: {app}
Source: ..\VVV.fbk; DestDir: {app}


[Icons]
Name: {commonprograms}\{#AppName}; Filename: {app}\{#ExeName}
Name: {commondesktop}\{#AppName}; Filename: {app}\{#ExeName}; Tasks: desktopicon

#ifdef Debug
  #expr SaveToFile(AddBackslash(SourcePath) + "Preprocessed.iss")
#endif
[InstallDelete]
Name: {app}\{#ExeName}; Type: filesandordirs; Tasks: 
