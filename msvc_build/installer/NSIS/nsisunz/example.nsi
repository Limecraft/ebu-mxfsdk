; Example script for nsisunz
; Written by Saivert
; Homepage: http://members.tripod.com/files_saivert/
;
; Dependencies:
; - nsisunz.dll Plug-in
; - InstallOptions.dll Plug-in
; - zippage.ini (InstallOptions INI file)

!addplugindir ".\Release"

OutFile "nsisunz_test.exe"
Name "NSIS Unzip plug-in test"
Caption "NSIS Unzip plug-in test"
ShowInstDetails show
XPStyle on
CompletedText "Extracted!"
SubCaption 3 " - Extracting files"
SubCaption 4 " - Extracted"

LoadLanguageFile "${NSISDIR}\Contrib\Language files\english.nlf"

; Installer pages
Page custom onZipPageShow onZipPageLeave " - Select Zip file"
Page instfiles

; Localized strings for use with nsisunz
; The '%f' in the string is replaced with the filename on run-time.
; "%c", "%u", "%p" and "%p" is replaced with compressed size,
; uncompressed size, percent complete (with "%") and byte complete
; respectively.
LangString nsisunz_text ${LANG_ENGLISH} "Extract: %f (%c -> %b) [%p]"

Function .onInit
  InitPluginsDir
  File "/oname=$PLUGINSDIR\zippage.ini" "zippage.ini"
FunctionEnd

Function onZipPageShow
  ; Turn Text control into a button (HM NIS Edit v2.0b5 does not support "Button" type).
  WriteINIStr "$PLUGINSDIR\zippage.ini" "Field 12" "Type" "Button"
  WriteINIStr "$PLUGINSDIR\zippage.ini" "Field 12" "Flags" "NOTIFY"

  InstallOptions::dialog "$PLUGINSDIR\zippage.ini"
FunctionEnd

Function onZipPageLeave
; $R0 = zip filename $R1 = dest. folder

  ReadINIStr $R0 "$PLUGINSDIR\zippage.ini" "Field 4" "State"
  ReadINIStr $R1 "$PLUGINSDIR\zippage.ini" "Field 6" "State"

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

