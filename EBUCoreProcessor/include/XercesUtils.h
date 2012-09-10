
#ifndef __EBUSDK_XERCESUTILS_H__
#define __EBUSDK_XERCESUTILS_H__

#include <xercesc/sax/InputSource.hpp>
#include <xercesc/util/BinInputStream.hpp>
#include <xercesc/sax/InputSource.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
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

namespace EBUSDK {
	namespace Utils {

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

DOMLSParser* ObtainParser(DOMErrorHandler& errHandler);

DOMDocument* ParseXercesDocument(const XMLCh* location);
DOMDocument* ParseXercesDocument(InputSource& input);

class DarkDOMDocumentSerializer : public EBUSDK::MXFCustomMetadata::MXFFileDarkSerializer, public xercesc::XMLFormatTarget {
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

}
}

#endif
