
!define PRODUCT_NAME "EBU MXF SDK Binaries"
!define VERSION "1.0.0a-4" ;@VERSION@
!define PRODUCT_VERSION "1.0" ;@VERSION@
!define PRODUCT_GROUP "EBU"
!define PRODUCT_PUBLISHER "EBU Technical"
!define PRODUCT_WEB_SITE "http://tech.ebu.ch/"
!define PRODUCT_DIR_REGKEY "Software\EBU\MXFSDK"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_ID "{337C8AF5-71C6-4BEB-BBDD-873498892431}"

!ifdef NSIS_LZMA_COMPRESS_WHOLE
SetCompressor lzma
!else
SetCompressor /SOLID lzma
!endif

;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

!addincludedir NSIS\helpers
!addincludedir NSIS\UAC
!addplugindir NSIS\UAC\Ansi
!addplugindir NSIS\nsisunz\Release
!include UAC.nsh
!include EnvVarUpdate.nsh

!macro UACInit thing
uac_tryagain:
!insertmacro UAC_RunElevated
${Switch} $0
${Case} 0
	${IfThen} $1 = 1 ${|} Quit ${|} ;we are the outer process, the inner process has done its work, we are done
	${IfThen} $3 <> 0 ${|} ${Break} ${|} ;we are admin, let the show go on
	${If} $1 = 3 ;RunAs completed successfully, but with a non-admin user
		MessageBox mb_YesNo|mb_IconExclamation|mb_TopMost|mb_SetForeground "This ${thing} requires admin privileges, try again" /SD IDNO IDYES uac_tryagain IDNO 0
	${EndIf}
	;fall-through and die
${Case} 1223
	MessageBox mb_IconStop|mb_TopMost|mb_SetForeground "This ${thing} requires admin privileges, aborting!"
	Quit
${Case} 1062
	MessageBox mb_IconStop|mb_TopMost|mb_SetForeground "Logon service not running, aborting!"
	Quit
${Default}
	MessageBox mb_IconStop|mb_TopMost|mb_SetForeground "Unable to elevate , error $0"
	Quit
${EndSwitch}

SetShellVarContext all
!macroend

  
;--------------------------------
;General

  ;Name and file
	Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
	OutFile ebu-mxfsdk-bin-${VERSION}.exe

  ;Default installation folder
  ;InstallDir "$PROGRAMFILES\EBU\MXFSDK"
  InstallDir "$DOCUMENTS\EBU-MXFSDK-Binaries"
 
  ;Get installation folder from registry if available
  InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""

  ;Request application privileges for Windows Vista
  RequestExecutionLevel user

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !define MUI_HEADERIMAGE
  !define MUI_HEADERIMAGE_BITMAP "resources\EBU_logo_2013.bmp"
  !define MUI_HEADERIMAGE_UNBITMAP "resources\EBU_logo_2013.bmp"
  !define MUI_WELCOMEFINISHPAGE_BITMAP "resources\EBU_logo_large_2013.bmp"

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "..\..\LICENSE.txt"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_PAGE_FINISH

  !insertmacro MUI_UNPAGE_WELCOME
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH

;--------------------------------
;Languages

  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "MXFSDK" SecMXFSDK

  SetOutPath "$INSTDIR"
  
  CreateDirectory "$INSTDIR\bin"
  File "/oname=bin\ebu2mxf.exe" "..\..\bin\ebu2mxf.exe"
  File "/oname=bin\mxf2ebu.exe" "..\..\bin\mxf2ebu.exe"
  File "/oname=bin\raw2bmx.exe" "..\..\bin\raw2bmx.exe"
  File "/oname=bin\mxfanalyzer.exe" "..\..\bin\mxfanalyzer.exe"
  File "/oname=bin\xerces-c_3_1.dll" "..\..\msvc_build\dependencies\xerces-c-3.1.1-x86-windows-vc-10.0\bin\xerces-c_3_1.dll"

  CreateDirectory "$INSTDIR\doc"
  File "/oname=doc\EBU MXF SDK.pdf" "..\..\doc\EBU MXF SDK.pdf"

  File "/oname=vcredist_x86.exe" "..\..\msvc_build\installer\resources\vcredist_x86.exe"
    
  ; Install Visual C++ redist
  DetailPrint "Installing Microsoft Visual C++ Runtime dependencies..."
  ExecWait '"$INSTDIR\vcredist_x86.exe" /q'
  Delete "$INSTDIR\vcredist_x86.exe"
  
  ; Create some shortcuts
  CreateShortCut "$INSTDIR\MXFSDK Documentation.lnk" "$INSTDIR\doc\EBU MXF SDK.pdf"
  
  CreateDirectory "$SMPROGRAMS\${PRODUCT_NAME}"
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\MXFSDK Documentation.lnk" "$INSTDIR\doc\EBU MXF SDK.pdf"
  
  ; Write bin directory to path
  ${EnvVarUpdate} $0 "PATH" "A" "HKLM" "$INSTDIR\bin" 
  
  ;Store installation folder
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" $INSTDIR

SectionEnd

Section -Post

  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" \
    "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" \
    "UninstallString" "$INSTDIR\uninstall.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" \
    "InstallLocation" "$INSTDIR"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" \
    "DisplayIcon" "$INSTDIR\vlc.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" \
    "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" \
    "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" \
    "Publisher" "${PRODUCT_PUBLISHER}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" \
    "VersionMajor"  "@VERSION_MAJOR@"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" \
    "VersionMinor" "@VERSION_MINOR@"

SectionEnd

Function .onInit

	!insertmacro UACInit "installer"


FunctionEnd

;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecSDK ${LANG_ENGLISH} "Files for the EBU MXF SDK."

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecMXFSDK} $(DESC_SecSDK)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section


Section "Uninstall"

  ;ADD YOUR OWN FILES HERE...

  Delete "$INSTDIR\Uninstall.exe"

  RMDir /r "$SMPROGRAMS\${PRODUCT_NAME}"
  
  Delete "$INSTDIR\MXFSDK Documentation.lnk"
  
  Delete "$INSTDIR\bin\ebu2mxf.exe"
  Delete "$INSTDIR\bin\mxf2ebu.exe"
  Delete "$INSTDIR\bin\raw2bmx.exe"
  Delete "$INSTDIR\bin\mxfanalyzer.exe"
  Delete "$INSTDIR\bin\xerces-c_3_1.dll"

  Delete "$INSTDIR\doc\EBU MXF SDK.pdf"
  
  RMDir "$INSTDIR\bin"
  RMDir "$INSTDIR\doc"
  RMDir "$INSTDIR"

  ; Remove bin directory from path
  ${un.EnvVarUpdate} $0 "PATH" "R" "HKLM" "$INSTDIR\bin" 
  
  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"

SectionEnd

Function un.onInit
	!insertmacro UACInit "Uninstaller"
FunctionEnd
