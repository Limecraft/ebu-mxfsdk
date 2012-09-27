set PATH=c:\code\Java\groovy-1.8.6\bin;%PATH%
cmd /C groovy dictconvert.groovy ebucore_mxflib_dict.xml > ..\include\metadata\ebucore_extensions_data_model.h
cmd /C groovy declarereferences.groovy ebucore_mxflib_dict.xml > ..\..\tools\gen_ebucore_classes\ebucore_declare_references.inc
pause