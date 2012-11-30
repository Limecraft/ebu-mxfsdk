..\..\msvc_build\dependencies\xsd-3.3.0-i686-windows\bin\xsd.exe cxx-tree --generate-serialization --root-element ebuCoreMain --namespace-map http://purl.org/dc/elements/1.1/=dc EBU_CORE_20120817.xsd simpledc20021212.xsd
move /y *.hxx ..\include\xsd
move /y *.cxx ..\src\xsd
pause
