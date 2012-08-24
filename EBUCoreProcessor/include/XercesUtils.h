
#include <xercesc/sax/InputSource.hpp>
#include <xercesc/util/BinInputStream.hpp>
#include <xercesc/sax/InputSource.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>

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

DOMDocument* ParseXercesDocument(InputSource& input) {
	XercesDOMParser* parser = new XercesDOMParser();
	parser->setValidationScheme(XercesDOMParser::Val_Never);
	parser->setValidationSchemaFullChecking(false);
	parser->setDoSchema(false);
	parser->setDoNamespaces(true);    // optional

	ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
    parser->setErrorHandler(errHandler);

	DOMDocument* out = NULL;

	try {
		parser->parse(input);
		out = parser->getDocument();
	} catch (...) {}

	delete parser;
	delete errHandler;

	return out;
}

/*class DarkDOMDocumentSerializer : public MXFFileDarkSerializer, xercesc::XMLFormatTarget {
	xercesc::DOMDocument& doc;
	mxfpp::File *mxfFile;
public:
	DarkDOMDocumentSerializer(xercesc::DOMDocument& document ) : doc(document) {}
	void WriteToMXFFile(File *f) {
		mxfFile = f;
		// call into xerces for serialization
		// cf. http://www.ibm.com/developerworks/xml/library/x-serial.html
	}
	void writeChars(const XMLByte* toWrite, const unsigned int count, xercesc::XMLFormatter* const formatter) {

	}
};*/
