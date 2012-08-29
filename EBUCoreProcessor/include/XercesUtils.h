
#include <xercesc/sax/InputSource.hpp>
#include <xercesc/util/BinInputStream.hpp>
#include <xercesc/sax/InputSource.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMLSParser.hpp>
#include <xercesc/dom/DOMLSSerializer.hpp>
#include <xercesc/dom/DOMLSOutput.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>

#include <libMXF++/MXF.h>

using namespace xercesc;

class KLVInputSourceStream : public BinInputStream {
	mxfpp::File* _mxfFile;
	int64_t _length, _pos;
public:
	KLVInputSourceStream(mxfpp::File *mxfFile, int64_t length) : _mxfFile(mxfFile), _length(length), _pos(0) {}

	virtual XMLFilePos curPos () const				{	return _pos;	}
	virtual const XMLCh* getContentType () const	{	return 0;		}
	virtual XMLSize_t readBytes (XMLByte* const buf, const XMLSize_t size) {
		uint64_t read = size < (_length-_pos) ? size : (_length-_pos);
		read = _mxfFile->read(buf, read);
		_pos += read;
		return read;
	}
};

class KLVInputSource : public InputSource {
	mxfpp::File* _mxfFile;
	int64_t _length;
public:
	KLVInputSource(mxfpp::File *mxfFile, int64_t length) : _mxfFile(mxfFile), _length(length) {}

	virtual BinInputStream* makeStream () const
	{
		return new KLVInputSourceStream(_mxfFile, _length);
	}
};

class PlainDOMErrorHandler : public DOMErrorHandler {
	bool handleError (const DOMError &domError) {
		// do nothing??
		return false;	// stop processing on errors
	}
};

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

class DarkDOMDocumentSerializer : public EBUCore::MXFFileDarkSerializer, public xercesc::XMLFormatTarget {
	xercesc::DOMDocument& doc;
	mxfpp::File *mxfFile;
	uint64_t size;
public:
	DarkDOMDocumentSerializer(xercesc::DOMDocument& document) : doc(document), size(0) {}

	uint64_t WriteToMXFFile(mxfpp::File *f) {
		mxfFile = f;
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
		outp->setByteStream(this);

		// serialize the DOMNode to a UTF-16 string
		writer->write(&doc, outp);

		// release the memory
		outp->release();
		writer->release();

		return size;
	}

	void writeChars(const XMLByte* const toWrite, const XMLSize_t count, xercesc::XMLFormatter* const formatter) {
		mxfFile->write((const unsigned char*)toWrite, count);
		size += count;
	}

	virtual ~DarkDOMDocumentSerializer() {
		size = 0;
	}
};
