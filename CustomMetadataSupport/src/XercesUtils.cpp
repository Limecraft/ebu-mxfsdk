/*
 *	Copyright 2012-2013 European Broadcasting Union and Limecraft, NV.
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *	   http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *	See the License for the specific language governing permissions and
 *	limitations under the License.
 *
 */
 
#include <MXFCustomMetadata.h>
#include <XercesUtils.h>

namespace EBUSDK {
	namespace Utils {

DOMLSParser* ObtainParser(DOMErrorHandler& errHandler) {

	const XMLCh ls_id [] = {chLatin_L, chLatin_S, chNull};

	// Get an implementation of the Load-Store (LS) interface.
	//
	DOMImplementation* impl(DOMImplementationRegistry::getDOMImplementation (ls_id));

	DOMLSParser *parser (impl->createLSParser (DOMImplementationLS::MODE_SYNCHRONOUS, 0));

	DOMConfiguration* conf (parser->getDomConfig ());

	// Discard comment nodes in the document.
	//
	conf->setParameter (XMLUni::fgDOMComments, false);

	// Enable datatype normalization.
	//
	conf->setParameter (XMLUni::fgDOMDatatypeNormalization, true);

	// Do not create EntityReference nodes in the DOM tree. No
	// EntityReference nodes will be created, only the nodes
	// corresponding to their fully expanded substitution text
	// will be created.
	//
	conf->setParameter (XMLUni::fgDOMEntities, false);

	// Perform namespace processing.
	//
	conf->setParameter (XMLUni::fgDOMNamespaces, true);

	// Do not include ignorable whitespace in the DOM tree.
	//
	conf->setParameter (XMLUni::fgDOMElementContentWhitespace, false);

	// Enable/Disable validation.
	//
	conf->setParameter (XMLUni::fgDOMValidate, false);
	conf->setParameter (XMLUni::fgXercesSchema, false);
	conf->setParameter (XMLUni::fgXercesSchemaFullChecking, false);

	// Xerces-C++ 3.1.0 is the first version with working multi import
	// support.
	//
#if _XERCES_VERSION >= 30100
	conf->setParameter (XMLUni::fgXercesHandleMultipleImports, true);
#endif

	// We will release the DOM document ourselves.
	//
	conf->setParameter (XMLUni::fgXercesUserAdoptsDOMDocument, true);

	// Set error handler.
	//
	conf->setParameter (XMLUni::fgDOMErrorHandler, &errHandler);

	return parser;
}

DOMDocument* ParseXercesDocument(const XMLCh* location) {

	PlainDOMErrorHandler errHandler;
	std::auto_ptr<DOMLSParser> parser ( ObtainParser(errHandler) );	
	
	try {
		return parser->parseURI(location);
	} catch (...) {
		return NULL;
	}
}

DOMDocument* ParseXercesDocument(InputSource& input) {

	PlainDOMErrorHandler errHandler;
	std::auto_ptr<DOMLSParser> parser ( ObtainParser(errHandler) );	

	try {
		Wrapper4InputSource wrap(&input, false /* don't adopt the source, it will be deleted upstream */);
		return parser->parse(&wrap);
	} catch (...) {
		return NULL;
	}
}

void SerializeXercesDocument(xercesc::DOMDocument& document, xercesc::XMLFormatTarget& target) {

	// call into xerces for serialization
	// cf. http://xerces.apache.org/xerces-c/program-dom-3.html#DOMLSSerializer

	static const XMLCh gLS[] = { chLatin_L, chLatin_S, chNull };
	DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(gLS);

	// construct the DOMWriter
	DOMLSSerializer *writer = ((DOMImplementationLS*)impl)->createLSSerializer();

    // optionally you can set some features on this serializer
    if (writer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTDiscardDefaultContent, true))
        writer->getDomConfig()->setParameter(XMLUni::fgDOMWRTDiscardDefaultContent, true);

    if (writer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true))
            writer->getDomConfig()->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);

	// prepare output
	DOMLSOutput *outp = ((DOMImplementationLS*)impl)->createLSOutput();
	outp->setByteStream(&target);

	// serialize the DOMNode to a UTF-16 string
	writer->write(&document, outp);

	// release the memory
	outp->release();
	writer->release();

}


}
}

