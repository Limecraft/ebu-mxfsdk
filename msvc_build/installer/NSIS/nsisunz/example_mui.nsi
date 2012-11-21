; Example script for nsisunz
; Written by Saivert
; Homepage: http://members.tripod.com/files_saivert/
;
; Dependencies:
; - nsisunz.dll Plug-in
; - InstallOptions.dll Plug-in
; - zippage.ini (InstallOptions INI file)

!addplugindir ".\Release"

!include "MUI.nsh"

OutFile "nsisunz_testmui.exe"
Name "NSIS Unzip plug-in test"
Caption "NSIS Unzip plug-in test"
ShowInstDetails show
CompletedText "Extracted!"

; Installer pages
Page custom onZipPageShow onZipPageLeave " "
!define MUI_PAGE_HEADER_TEXT "Extracting"
!define MUI_PAGE_HEADER_SUBTEXT "Extracting files"
!define MUI_INSTFILESPAGE_FINISHHEADER_TEXT "Extracted"
!define MUI_INSTFILESPAGE_FINISHHEADER_SUBTEXT "Thes files has been extracted"
!define MUI_INSTFILESPAGE_ABORTHEADER_TEXT "Extraction aborted"
!define MUI_INSTFILESPAGE_ABORTHEADER_SUBTEXT "The extraction process was aborted"
!insertmacro MUI_PAGE_INSTFILES

!insertmacro MUI_LANGUAGE "English"

; Localized strings for use with nsisunz
; The '%f' in the string is replaced with the filename on run-time.
; "%c" and "%u" is replaced with compressed size and uncompressed size
; respectively.
LangString nsisunz_text ${LANG_ENGLISH} "Extract: %f (%c -> %u)"

Function .onInit
  InitPluginsDir
  !insertmacro MUI_INSTALLOPTIONS_EXTRACT "zippage.ini"
FunctionEnd

Function onZipPageShow
  !insertmacro MUI_HEADER_TEXT "Unzip" "Select ZIP file and destination folder"

  ; Remove icon (so we get away with one INI file for both scripts)
  !insertmacro MUI_INSTALLOPTIONS_WRITE "zippage.ini" "Field 1" "Type" ""
  !insertmacro MUI_INSTALLOPTIONS_WRITE "zippage.ini" "Field 2" "Left" "0"


  !insertmacro MUI_INSTALLOPTIONS_DISPLAY "zippage.ini"
FunctionEnd

Function onZipPageLeave
; $R0 = zip filename $R1 = dest. folder

  !insertmacro MUI_INSTALLOPTIONS_READ $R0 "zippage.ini" "Field 4" "State"
  !insertmacro MUI_INSTALLOPTIONS_READ $R1 "zippage.ini" "Field 6" "State"

  ; Remove trailing backslash if any
  StrCpy $0 $R1 1 -1
  StrCmp "$0" "\" 0 notneeded
    StrCpy $R1 $R1 -1
  notneeded:

  IfFileExists $R0 checkdir
    MessageBox MB_ICONEXCLAMATION|MB_OK 'The file "$R0" does not exist!'
    Abort ;return to page
  checkdir:
  IfFileExists $R1\*.* unzip
    MessageBox MB_ICONEXCLAMATION|MB_YESNO 'The folder "$R1" does not exist!$\r$\nDo you wish to create it?' IDNO skipcreate
    CreateDirectory $R1
    Goto unzip
    skipcreate:
    Abort ;return to page

  unzip:
; Just fall of the end, so the sections can be executed
FunctionEnd

Section -pre
  DetailPrint "ZIP file: $R0"
  DetailPrint "Dest. folder: $R1"
SectionEnd

Section
; Check if the checkbox is checked and if it is, then don't extract paths
  ReadINIStr $R2 "$PLUGINSDIR\zippage.ini" "Field 7" "State"
  StrCmp $R2 "1" 0 usepaths
    nsisunz::UnzipToLog /text "$(nsisunz_text)" /noextractpath $R0 $R1
    Goto check
  usepaths:
  nsisunz::UnzipToLog /text "$(nsisunz_text)" $R0 $R1

  check:
; Always check for errors. Everything else than "success" means an error.
  Pop $0
  StrCmp $0 "success" ok
    Abort "$0"
  ok:
SectionEnd
