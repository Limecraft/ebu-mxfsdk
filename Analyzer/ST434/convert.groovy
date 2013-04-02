
def keys = [:]
def ns_xs = new groovy.xml.Namespace('http://www.w3.org/2001/XMLSchema')

// collect all namespace declarations used and aggregate the unique ones

def namespaces = [:]

def i = 1
args.tail().each { arg ->
	def xmlSchema = new XmlParser().parse(arg)
	namespaces[xmlSchema.'@targetNamespace'] = 'key_ns_' + args.head() + '_' + (i++)
}

// write out each of the namespaces
namespaces.each { k, v ->
	println 'XMLCh ' + v + '[] = {' + k.getChars().collect{ c -> '\'' + c + '\''}.join(',') + ',\'\\0\'};';
}

i = 0
args.tail().each { arg ->	

	def xmlSchema = new XmlParser().parse(arg)
	//println xmlSchema
		
	//def namespaceDecls = xmlSchema.attributes //.findAll { k, v ->
	//	k.contains('xmlns:')
	//}//.collectEntries { k,v -> [v,k] }
	
	//println namespaceDecls
	def localKeys = [:]
	
	// typesMap generated with: cat input.txt | sed -e "s/.*(//" | sed -e "s/\(.*\),\(.*\),.*,.*/\2 : \"\1\",/"
	xmlSchema[ns_xs.element].each { e ->
		def keyElem = e[ns_xs.annotation][ns_xs.appinfo].find { 
			ai -> ai.'@source' == 'http://www.smpte-ra.org/schemas/434/Dictionary/ElementUL' || ai.'@source' == 'http://www.smpte-ra.org/schemas/434/Groups/Key' || ai.'@source' == 'urn:ebu:metadata-schema:smpteclass13/properties/ebucore_2012/ElementUL'
		}
		if (keyElem != null) {
			def key = keyElem.text().trim()
			keyName = 'key_' + key.replace('.', '')
			// only if the keyname is not yet represented
			if (!keys.containsKey(keyName)) {
				keys[keyName] = keyName
				localKeys[keyName] = keyName + '_name'
				key = '{0x' + key.replace('.', ',0x') + '}'
					println 'const mxfKey ' + keyName + ' = ' + key + ';';
					println 'const XMLCh ' + keyName + '_name[] = {' + e.'@name'.getChars().collect{ c -> '\'' + c + '\''}.join(',') 	+ ',\'\\0\'};';
				//println 'st434dict.insert(std::pair<const mxfKey, st434info*>('
					//println '\t' + keyName + ','
					//println '\tnew st434info(L"' + e.'@name' + '", L"' + xmlSchema.'@targetNamespace' + '")'
					//println '\tnew st434info(/* ' + e.'@name' + ' */ ' + keyName + '_name, /* ' + xmlSchema.'@targetNamespace' + ' */ ' + namespaces[xmlSchema.'@targetNamespace'] + ')'
				//println '));'
			} else {
				println '// Skipped duplicate: ' + e.'@name'
			}
		} else
		{
			println '// No UL found for element: ' + e.'@name'
		}
	}
	if (localKeys.size() > 0) {
		def arrayName = 'arr_st434_elems_' + namespaces[xmlSchema.'@targetNamespace'] + '_' + (i++)
	
		println 'const void* ' + arrayName + '[][2] = {'
		println localKeys.collect { k, v ->
			'{ &' + k + ', ' + v + ' }'
		}.join(', \n')
		println '};'
				
		println "for (int i=0; i<${localKeys.size()};i++) {"
			println '\tst434dict.insert(std::pair<const mxfKey, st434info*>('
			println '\t*(const mxfKey*)' + arrayName + '[i][0], '
			println '\tnew st434info((const XMLCh*)' + arrayName + '[i][1], ' + namespaces[xmlSchema.'@targetNamespace'] + ')'
			println '));'
		println '}'
	}

}

