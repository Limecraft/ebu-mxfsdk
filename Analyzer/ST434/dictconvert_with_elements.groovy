def xmlDictionary = new XmlParser().parse(args[0])

def targetNameSpace = args[1]
def targetNameSpaceVar = args[2]
def namespaces = [
	(targetNameSpace) : targetNameSpaceVar
]

// write out each of the namespaces
namespaces.each { k, v ->
	println 'XMLCh ' + v + '[] = {' + k.getChars().collect{ c -> '\'' + c + '\''}.join(',') + ',\'\\0\'};';
}

xmlDictionary.findAll{ it.'@type' == 'localSet' }.each {
	localSet ->

		def name = localSet.name()
		def keyName = 'key_' + localSet.'@key'.split().join('')
		println 'mxfKey ' + keyName + ' = {' + localSet.'@key'.split().collect { it -> '0x' + it }.join(',') + '};'
		println 'XMLCh ' + keyName + '_name[] = {' + name.getChars().collect{ c -> '\'' + c + '\''}.join(',') 	+ ',\'\\0\'};';
		
		println 'st434dict.insert(std::pair<mxfKey, st434info*>('
			println '\t' + keyName + ','
			println '\tnew st434info(/* ' + localSet.name() + ' */ ' + keyName + '_name, /* ' + targetNameSpace + ' */ ' + namespaces[targetNameSpace] + ')'
		println '));'
		
		localSet.each { localSetElem ->
			def elemKeyName = 'key_' + localSetElem.'@globalKey'.split().join('')
			println 'mxfKey ' + elemKeyName + ' = {' + localSetElem.'@globalKey'.split().collect { it -> '0x' + it }.join(',') + '};'
			println 'XMLCh ' + elemKeyName + '_name[] = {' + localSetElem.name().getChars().collect{ c -> '\'' + c + '\''}.join(',') 	+ ',\'\\0\'};';
			
			println 'st434dict.insert(std::pair<mxfKey, st434info*>('
				println '\t' + elemKeyName + ','
				println '\tnew st434info(/* ' + localSetElem.name() + ' */ ' + elemKeyName + '_name, /* ' + targetNameSpace + ' */ ' + namespaces[targetNameSpace] + ')'
			println '));'		
		
		}
}

