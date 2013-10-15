#rm ../apps/analyzer/group_declarations.inc
find schemas/groups schemas/dictionary -type f -not -name '*ebucore*.xsd' | xargs groovy convert.groovy st434 > ../src/group_declarations.inc
echo schemas/dictionary/class13_ebucore_extension_dictionary.xsd | xargs groovy convert.groovy ebucore_elements >> ../src/group_declarations.inc
groovy dictconvert.groovy ../../EBUCoreProcessor/dictionary/ebucore_mxflib_dict.xml >> ../src/group_declarations.inc
#groovy dictconvert_with_elements.groovy ../../ebu-bmx/src/as11/as11_mxflib_dict.xml "urn:dpp:metadata:as11" key_ns_as11_1 > ../src/group_declarations_as11.inc
