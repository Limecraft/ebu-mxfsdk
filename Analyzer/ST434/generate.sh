#rm ../apps/analyzer/group_declarations.inc
find schemas/groups schemas/dictionary -type f -not -name '*ebucore*.xsd' | xargs java -cp "bin;guava-14.0.1.jar" Convert st434 > ../src/group_declarations.inc
echo schemas/dictionary/class13_ebucore_extension_dictionary.xsd | xargs java -cp "bin;guava-14.0.1.jar" Convert ebucore_elements >> ../src/group_declarations.inc
java -cp "bin;guava-14.0.1.jar" Dictconvert ../../EBUCoreProcessor/dictionary/ebucore_mxflib_dict.xml >> ../src/group_declarations.inc
java -cp "bin;guava-14.0.1.jar" Dictconvert_with_elements ../../ebu-bmx/src/as11/as11_mxflib_dict.xml "urn:dpp:metadata:as11" key_ns_as11_1 > ../src/group_declarations_as11.inc
