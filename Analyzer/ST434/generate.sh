find ../../../../EBU-SDK/ST434/groups ../../../../EBU-SDK/ST434/dictionary -type f | xargs java -cp "guava-14.0.1.jar;./bin" Convert st434 > ../src/group_declarations.inc
echo ../../../../EBU-SDK/Mapping/20130219_ST434_ebucore14_REV7_namespace2013_smpteversions_doc/dictionary/class13_ebucore_extension_dictionary.xsd | xargs java -cp "guava-14.0.1.jar;./bin" Convert ebucore_elements >> ../src/group_declarations.inc
java -cp "guava-14.0.1.jar;./bin" Dictconvert ../../EBUCoreProcessor/dictionary/ebucore_mxflib_dict.xml >> ../src/group_declarations.inc
java -cp "guava-14.0.1.jar;./bin" Dictconvert_with_elements ../../ebu-bmx/src/as11/as11_mxflib_dict.xml "urn:dpp:metadata:as11" key_ns_as11_1 > ../src/group_declarations_as11.inc
