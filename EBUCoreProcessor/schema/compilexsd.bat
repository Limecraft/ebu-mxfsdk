..\..\msvc_build\dependencies\xsd-3.3.0-i686-windows\bin\xsd.exe cxx-tree ^
 --include-regex "@(.+)@xsd/$1@" ^
 --include-regex "@(.*EBU_CORE.*)@EBUCore_1_4/xsd/$1@" ^
 --generate-serialization --root-element ebuCoreMain --namespace-map http://purl.org/dc/elements/1.1/=dc EBU_CORE_20121219.xsd simpledc20021212.xsd
move /y EBU_CORE*.hxx ..\include\EBUCore_1_4\xsd
move /y *.hxx ..\include\xsd
move /y EBU_CORE*.cxx ..\src\EBUCore_1_4\xsd
move /y *.cxx ..\src\xsd
pause
