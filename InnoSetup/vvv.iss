; -- vvv.iss --
; install script for vvv

#pragma option -v+
#pragma verboselevel 9

;#define Debug

#define AppName "VVV (Virtual Volumes View)"
#define ExeName "vvv.exe"
#define AppVersion "0.9"

[Setup]
AppId=VVV-fu-ku-jitsu
AppName={#AppName}
AppVerName={#AppName} version {#AppVersion}
DefaultDirName={pf}\{#AppName}
DefaultGroupName={#AppName}
UninstallDisplayIcon={app}\{#ExeName}
LicenseFile=License.txt
VersionInfoVersion={#AppVersion}
ChangesAssociations=yes
OutputDir=.
;OutputBaseFilename=VVV- + {#AppVersion} + -Setup
OutputBaseFilename=VVV-0.9-Setup

[Tasks]
Name: desktopicon; Description: {cm:CreateDesktopIcon}

[Files]
Source: ..\vc_mswu\{#ExeName}; DestDir: {app}; Tasks: 
Source: msvcr71.dll; DestDir: {app}; Flags: replacesameversion; Tasks: 
Source: fbclient.dll; DestDir: {app}; Flags: replacesameversion
Source: firebird.msg; DestDir: {app}; Flags: replacesameversion
Source: icudt30.dll; DestDir: {app}; Flags: replacesameversion
Source: icuin30.dll; DestDir: {app}; Flags: replacesameversion
Source: icuuc30.dll; DestDir: {app}; Flags: replacesameversion
Source: License.txt; DestDir: {app}
Source: msvcp71.dll; DestDir: {app}; Flags: replacesameversion
Source: intl\fbintl.dll; DestDir: {app}\intl; Flags: replacesameversion
Source: intl\fbintl.conf; DestDir: {app}\intl; Flags: replacesameversion
Source: ..\vvv-struct-update.fdb; DestDir: {app}; Attribs: readonly; Flags: overwritereadonly uninsremovereadonly
Source: ..\VVV.fbk; DestDir: {app}
Source: ..\help\en\vvv.chm; DestDir: {app}
Source: ..\translations\it\vvv.mo; DestDir: {app}\languages\it


[Icons]
Name: {commonprograms}\{#AppName}; Filename: {app}\{#ExeName}
Name: {commondesktop}\{#AppName}; Filename: {app}\{#ExeName}; Tasks: desktopicon

[Registry]
Root: HKCR; Subkey: .vvv; ValueType: string; ValueName: ; ValueData: vvvapp; Flags: uninsdeletevalue
Root: HKCR; Subkey: vvvapp; ValueType: string; ValueName: ; ValueData: {#AppName}; Flags: uninsdeletekey
Root: HKCR; Subkey: vvvapp\DefaultIcon; ValueType: string; ValueName: ; ValueData: {app}\{#ExeName},0
Root: HKCR; Subkey: vvvapp\shell\open\command; ValueType: string; ValueName: ; ValueData: """{app}\{#ExeName}"" ""%1"""
Root: HKCU; Subkey: Software\VVV; Flags: uninsdeletekey

[Languages]
Name: en; MessagesFile: compiler:Default.isl
Name: it; MessagesFile: compiler:Languages\Italian.isl

#ifdef Debug
  #expr SaveToFile(AddBackslash(SourcePath) + "Preprocessed.iss")
#endif

