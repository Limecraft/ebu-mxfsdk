def xmlDictionary = new XmlParser().parse(args[0])

def key_ns_ebucore_1 = 'urn:ebu:metadata-schema:smpteclass13/groups/ebucore_2013'
def namespaces = [
	//'http:://www.smpte-ra.org/schemas/434/2006/groups/class13/ebucore/2013': 'key_ns_ebucore_1'
	(key_ns_ebucore_1): 'key_ns_ebucore_1'
]

def nameMap = [
'ebucoreMainFramework' : 'ebucoreMainFramework',
'ebucorePartFramework' : 'ebucorePartFramework',
'ebucoreMetadataSchemeInformation':'ebucoreMetadataSchemeInformation',
/* List mainly generated using AWK:
	awk '{t=$2; gsub(/ebucore/, "", t); print "\x27"$2"\x27:\x27" tolower(substr(t, 1, 1))substr(t, 2)"\x27," }' < tmp.txt > tmpout.txt
 */
'ebucoreEntity':'entity',
'ebucoreContact':'contact',
'ebucoreContactDetails':'details',
'ebucoreAddress':'address',
'ebucoreRegion':'region',
'ebucoreCompoundName':'compoundName',
'ebucoreRole':'role',
'ebucoreCountry':'country',
'ebucoreTextualAnnotation':'textualAnnotation',
'ebucoreBasicLink':'basicLink',
'ebucoreTypeGroup':'typeGroup',
'ebucoreOrganisation':'organisation',
'ebucoreOrganisationDepartment':'organisationDepartment',
'ebucoreCoreMetadata':'coreMetadata',
'ebucoreIdentifier':'identifier',
'ebucoreTitle':'title',
'ebucoreAlternativeTitle':'alternativeTitle',
'ebucoreFormatGroup':'formatGroup',
'ebucoreStatusGroup':'statusGroup',
'ebucoreSubject':'subject',
'ebucoreDescription':'description',
'ebucoreDate':'date',
'ebucoreDateType':'dateType',
'ebucoreType':'type',
'ebucoreObjectType':'objectType',
'ebucoreGenre':'genre',
'ebucoreTargetAudience':'targetAudience',
'ebucoreLanguage':'language',
'ebucoreCoverage':'coverage',
'ebucoreSpatial':'spatial',
'ebucoreLocation':'location',
'ebucoreCoordinates':'coordinates',
'ebucoreTemporal':'temporal',
'ebucorePeriodOfTime':'periodOfTime',
'ebucoreRights':'rights',
'ebucoreVersion':'version',
'ebucoreRating':'rating',
'ebucorePublicationHistoryEvent':'publicationHistoryEvent',
'ebucorePublicationHistory':'publicationHistory',
'ebucorePublicationChannel':'publicationChannel',
'ebucorePublicationMedium':'publicationMedium',
'ebucorePublicationService':'publicationService',
'ebucoreCustomRelation':'customRelation',
'ebucoreBasicRelation':'basicRelation',
'ebucorePartMetadata':'partMetadata',
'ebucoreFormat':'format',
'ebucoreVideoFormat':'videoFormat',
'ebucoreImageFormat':'imageFormat',
'ebucoreAudioFormat':'audioFormat',
'ebucoreTrack':'track',
'ebucoreDataFormat':'dataFormat',
'ebucoreCaptioning':'captioning',
'ebucoreSubtitling':'subtitling',
'ebucoreAncillaryData':'ancillaryData',
'ebucoreSigningFormat':'signingFormat',
'ebucoreTechnicalAttributeString':'technicalAttributeString',
'ebucoreTechnicalAttributeInt8':'technicalAttributeInt8',
'ebucoreTechnicalAttributeInt16':'technicalAttributeInt16',
'ebucoreTechnicalAttributeInt32':'technicalAttributeInt32',
'ebucoreTechnicalAttributeInt64':'technicalAttributeInt64',
'ebucoreTechnicalAttributeUInt8':'technicalAttributeUInt8',
'ebucoreTechnicalAttributeUInt16':'technicalAttributeUInt16',
'ebucoreTechnicalAttributeUInt32':'technicalAttributeUInt32',
'ebucoreTechnicalAttributeUInt64':'technicalAttributeUInt64',
'ebucoreTechnicalAttributeFloat':'technicalAttributeFloat',
'ebucoreTechnicalAttributeRational':'technicalAttributeRational',
'ebucoreTechnicalAttributeAnyURI':'technicalAttributeAnyURI',
'ebucoreTechnicalAttributeBoolean':'technicalAttributeBoolean',
'ebucoreDimension':'dimension',
'ebucoreWidth':'width',
'ebucoreHeight':'height',
'ebucorePackageInfo':'packageInfo',
'ebucoreMedium':'medium',
'ebucoreCodec':'codec',
'ebucoreRational':'rational',
'ebucoreAspectRatio':'aspectRatio'
]

// write out each of the namespaces
namespaces.each { k, v ->
	println 'XMLCh ' + v + '[] = {' + k.getChars().collect{ c -> '\'' + c + '\''}.join(',') + ',\'\\0\'};';
}

def localKeys = [:]

xmlDictionary.findAll{ it.'@type' == 'localSet' }.each {
	
	localSet ->

		def name = nameMap[localSet.name()]
		def keyName = 'key_' + localSet.'@key'.split().join('')
		println 'const mxfKey ' + keyName + ' = {' + localSet.'@key'.split().collect { it -> '0x' + it }.join(',') + '};'
		println 'const XMLCh ' + keyName + '_name[] = {' + name.getChars().collect{ c -> '\'' + c + '\''}.join(',') 	+ ',\'\\0\'};';
		
		localKeys[keyName] = keyName + '_name'
		
		//println 'st434dict.insert(std::pair<const mxfKey, st434info*>('
		//	println '\t' + keyName + ','
			//println '\tnew st434info(L"' + localSet.name() + '", L"http:://www.smpte-ra.org/schemas/434/2006/groups/class13/ebucore/2012")'
		//	println '\tnew st434info(/* ' + localSet.name() + ' */ ' + keyName + '_name, /* ' + key_ns_ebucore_1 + ' */ ' + namespaces[(key_ns_ebucore_1)] + ')'
		//println '));'
		
		// localSet.each { localSetElem ->
			// def elemKeyName = 'key_' + localSetElem.'@globalKey'.split().join('')
			// println 'mxfKey ' + elemKeyName + ' = {' + localSetElem.'@globalKey'.split().collect { it -> '0x' + it }.join(',') + '};'
			// println 'XMLCh ' + elemKeyName + '_name[] = {' + localSetElem.name().getChars().collect{ c -> '\'' + c + '\''}.join(',') 	+ ',\'\\0\'};';
			
			// println 'st434dict.insert(std::pair<mxfKey, st434info*>('
				// println '\t' + elemKeyName + ','
				////println '\tnew st434info(L"' + localSetElem.name() + '", L"http:://www.smpte-ra.org/schemas/434/2006/groups/class13/ebucore/2012")'
				// println '\tnew st434info(/* ' + localSetElem.name() + ' */ ' + elemKeyName + '_name, /* ' + "http:://www.smpte-ra.org/schemas/434/2006/groups/class13/ebucore/2012" + ' */ ' + namespaces["http:://www.smpte-ra.org/schemas/434/2006/groups/class13/ebucore/2012"] + ')'
			// println '));'		
		
		// }		
}

if (localKeys.size() > 0) {
	def arrayName = 'arr_ebucore_elems'

	println 'const void* ' + arrayName + '[][2] = {'
	println localKeys.collect { k, v ->
		'{ &' + k + ', ' + v + ' }'
	}.join(', \n')
	println '};'
			
	println "for (int i=0; i<${localKeys.size()};i++) {"
		println '\tst434dict.insert(std::pair<const mxfKey, st434info*>('
		println '\t*(const mxfKey*)' + arrayName + '[i][0], '
		println '\tnew st434info((const XMLCh*)' + arrayName + '[i][1], key_ns_ebucore_1)'
		println '));'
	println '}'
}


