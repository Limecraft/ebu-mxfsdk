def xmlDictionary = new XmlParser().parse(args[0])

def targetNameSpace = args[1]
def targetNameSpaceVar = args[2]
def namespaces = [
	(targetNameSpace) : targetNameSpaceVar
]

def localKeys = [:]

// write out each of the namespaces
namespaces.each { k, v ->
	println 'XMLCh ' + v + '[] = {' + k.getChars().collect{ c -> '\'' + c + '\''}.join(',') + ',\'\\0\'};';
}

xmlDictionary.findAll{ it.'@type' == 'localSet' }.each {
	localSet ->

		def name = localSet.name()
		def keyName = 'key_' + localSet.'@key'.split().join('')

		localKeys[keyName] = keyName + '_name'

		println 'mxfKey ' + keyName + ' = {' + localSet.'@key'.split().collect { it -> '0x' + it }.join(',') + '};'
		println 'XMLCh ' + keyName + '_name[] = {' + name.getChars().collect{ c -> '\'' + c + '\''}.join(',') 	+ ',\'\\0\'};';
		
		println 'st434dict.insert(std::pair<mxfKey, st434info*>('
			println '\t' + keyName + ','
			println '\tnew st434info(/* ' + localSet.name() + ' */ ' + keyName + '_name, /* ' + targetNameSpace + ' */ ' + namespaces[targetNameSpace] + ')'
		println '));'
		
		localSet.each { localSetElem ->
			def elemKeyName = 'key_' + localSetElem.'@globalKey'.split().join('')
			
			localKeys[elemKeyName] = elemKeyName + '_name'
			
			println 'mxfKey ' + elemKeyName + ' = {' + localSetElem.'@globalKey'.split().collect { it -> '0x' + it }.join(',') + '};'
			println 'XMLCh ' + elemKeyName + '_name[] = {' + localSetElem.name().getChars().collect{ c -> '\'' + c + '\''}.join(',') 	+ ',\'\\0\'};';
			
			//println 'st434dict.insert(std::pair<mxfKey, st434info*>('
			//	println '\t' + elemKeyName + ','
			//	println '\tnew st434info(/* ' + localSetElem.name() + ' */ ' + elemKeyName + '_name, /* ' + targetNameSpace + ' */ ' + namespaces[targetNameSpace] + ')'
			//println '));'		
		
		}
}

if (localKeys.size() > 0) {
	def arrayName = 'arr_' + targetNameSpaceVar

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

