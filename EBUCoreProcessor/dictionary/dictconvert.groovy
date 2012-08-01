def xmlDictionary = new XmlParser().parse(args[0])
def dynTypesMap = [:]
// typesMap generated with: cat input.txt | sed -e "s/.*(//" | sed -e "s/\(.*\),\(.*\),.*,.*/\2 : \"\1\",/"
def typesMap = [
	"Int8": "MXF_INT8_TYPE",
	"Int16" : "MXF_INT16_TYPE",
	"Int32" : "MXF_INT32_TYPE",
	"Int64" : "MXF_INT64_TYPE",
	"UInt8" : "MXF_UINT8_TYPE",
	"UInt16" : "MXF_UINT16_TYPE",
	"UInt32" : "MXF_UINT32_TYPE",
	"UInt64" : "MXF_UINT64_TYPE",
	"Raw" : "MXF_RAW_TYPE",
	"Rational": "MXF_RATIONAL_TYPE",
	"Timestamp": "MXF_TIMESTAMP_TYPE",
	"RGBALayoutComponent": "MXF_RGBALAYOUTCOMPONENT_TYPE",
	
    "UTF16String" : "MXF_UTF16STRING_TYPE",
	"UTF16StringArray" : "MXF_UTF16STRINGARRAY_TYPE",
	"Int8Array" : "MXF_INT8ARRAY_TYPE",
	"Int16Array" : "MXF_INT16ARRAY_TYPE",
	"Int32Array" : "MXF_INT32ARRAY_TYPE",
	"Int64Array" : "MXF_INT64ARRAY_TYPE",
	"UInt8Array" : "MXF_UINT8ARRAY_TYPE",
	"UInt16Array" : "MXF_UINT16ARRAY_TYPE",
	"UInt32Array" : "MXF_UINT32ARRAY_TYPE",
	"UInt64Array" : "MXF_UINT64ARRAY_TYPE",
	"ISO7String" : "MXF_ISO7STRING_TYPE",
	"Int8Batch" : "MXF_INT8BATCH_TYPE",
	"Int16Batch" : "MXF_INT16BATCH_TYPE",
	"Int32Batch" : "MXF_INT32BATCH_TYPE",
	"Int64Batch" : "MXF_INT64BATCH_TYPE",
	"UInt8Batch" : "MXF_UINT8BATCH_TYPE",
	"UInt16Batch" : "MXF_UINT16BATCH_TYPE",
	"UInt32Batch" : "MXF_UINT32BATCH_TYPE",
	"UInt64Batch" : "MXF_UINT64BATCH_TYPE",
	"AUIDArray" : "MXF_AUIDARRAY_TYPE",
	"ULArray" : "MXF_ULARRAY_TYPE",
	"ULBatch" : "MXF_ULBATCH_TYPE",
	"StrongRefArray" : "MXF_STRONGREFARRAY_TYPE",
	"StrongRefBatch" : "MXF_STRONGREFBATCH_TYPE",
	"WeakRefArray" : "MXF_WEAKREFARRAY_TYPE",
	"WeakRefBatch" : "MXF_WEAKREFBATCH_TYPE",
	"RationalArray" : "MXF_RATIONALARRAY_TYPE",
	"RGBALayout" : "MXF_RGBALAYOUT_TYPE",
	
	"VersionType" : "MXF_VERSIONTYPE_TYPE",
	"UTF16" : "MXF_UTF16_TYPE",
	"Boolean" : "MXF_BOOLEAN_TYPE",
	"ISO7" : "MXF_ISO7_TYPE",
	"Length" : "MXF_LENGTH_TYPE",
	"Position" : "MXF_POSITION_TYPE",
	"RGBACode" : "MXF_RGBACODE_TYPE",
	"Stream" : "MXF_STREAM_TYPE",
	"DataValue" : "MXF_DATAVALUE_TYPE",
	"Identifier" : "MXF_IDENTIFIER_TYPE",
	"Opaque" : "MXF_OPAQUE_TYPE",
	"UMID" : "MXF_UMID_TYPE",
	"UID" : "MXF_UID_TYPE",
	"UL" : "MXF_UL_TYPE",
	"UUID" : "MXF_UUID_TYPE",
	"AUID" : "MXF_AUID_TYPE",
	"PackageID" : "MXF_PACKAGEID_TYPE",
	"StrongRef" : "MXF_STRONGREF_TYPE",
	"WeakRef" : "MXF_WEAKREF_TYPE",
	"Orientation" : "MXF_ORIENTATION_TYPE",
	"CodedContentType" : "MXF_CODED_CONTENT_TYPE_TYPE"
]

println """
#if !defined (MXF_BASIC_TYPE_DEF)
#define MXF_BASIC_TYPE_DEF(typeId, name, size)
#endif
#if !defined (MXF_ARRAY_TYPE_DEF)
#define MXF_ARRAY_TYPE_DEF(typeId, name, elementTypeId, fixedSize)
#endif
#if !defined (MXF_COMPOUND_TYPE_DEF)
#define MXF_COMPOUND_TYPE_DEF(typeId, name)
#endif
#if !defined (MXF_COMPOUND_TYPE_MEMBER)
#define MXF_COMPOUND_TYPE_MEMBER(memberName, memberTypeId)
#endif
#if !defined (MXF_INTERPRETED_TYPE_DEF)
#define MXF_INTERPRETED_TYPE_DEF(typeId, name, interpretedTypeId, fixedSize)
#endif

#if !defined (MXF_LABEL)
#define MXF_LABEL(d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15)
#endif
#if !defined (MXF_SET_DEFINITION)
#define MXF_SET_DEFINITION(parentName, name, label)
#endif
#if !defined (MXF_ITEM_DEFINITION)
#define MXF_ITEM_DEFINITION(setName, name, label, localTag, typeId, isRequired)
#endif
"""

xmlDictionary.MXFTypes.Enumeration[0].each { type ->
		dynTypesMap[type.name()] = type
}

xmlDictionary.findAll{ it.'@type' == 'localSet' }.each {
	localSet ->
		println "MXF_SET_DEFINITION(" + (localSet.'@base' == "DM_Framework" ? "DMFramework" : localSet.'@base') + ", ${localSet.name()}, "
			println "\tMXF_LABEL(" + localSet.'@key'.split().collect { "0x" + it }.join(",") + ")"
		println ");"
		
		localSet.each { localSetElem ->
			println "\tMXF_ITEM_DEFINITION(" + localSet.name() + ", " + localSetElem.name() + ","
			println "\t\tMXF_LABEL(" + localSetElem.'@globalKey'.split().collect { "0x" + it }.join(",") + "),"
			println "\t\t0x0000,"
			// process the type
			def type = dynTypesMap.containsKey(localSetElem.'@type') ? dynTypesMap[localSetElem.'@type'].'@type' : localSetElem.'@type'
			println "\t\t" + typesMap[type] + ","
			println "\t\t" + (localSetElem.'@use' == "required" ? "1" : "0")
			println "\t);"
		}
}

println """
#undef MXF_BASIC_TYPE_DEF
#undef MXF_ARRAY_TYPE_DEF
#undef MXF_COMPOUND_TYPE_DEF
#undef MXF_COMPOUND_TYPE_MEMBER
#undef MXF_INTERPRETED_TYPE_DEF
#undef MXF_LABEL
#undef MXF_SET_DEFINITION
#undef MXF_ITEM_DEFINITION
"""
