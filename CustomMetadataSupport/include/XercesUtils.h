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

void SerializeXercesDocument(xercesc::DOMDocument& document, xercesc::XMLFormatTarget& target);


class DarkDOMDocumentSerializer : public EBUSDK::MXFCustomMetadata::MXFFileDarkSerializer, public xercesc::XMLFormatTarget {
	xercesc::DOMDocument& doc;
	mxfpp::File *mxfFile;
	uint64_t size;
public:
	DarkDOMDocumentSerializer(xercesc::DOMDocument& document) : doc(document), size(0) {}

	uint64_t WriteToMXFFile(mxfpp::File *f) {
		mxfFile = f;
		
		SerializeXercesDocument(doc, *this);

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
