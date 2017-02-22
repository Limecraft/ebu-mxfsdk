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
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/util/TransService.hpp>

#include <sstream>
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


class DarkDOMDocumentSerializer : public xercesc::XMLFormatTarget, public EBUSDK::MXFCustomMetadata::RP2057::MXFFileDarkXMLSerializer {
	xercesc::DOMDocument& doc;
	mxfpp::File *mxfFile;
	uint64_t size;
    bool writeToStringStream;
    std::stringstream sstream;
public:
	DarkDOMDocumentSerializer(xercesc::DOMDocument& document) : 
      doc(document), size(0), mxfFile(NULL), writeToStringStream(false) {}

	uint64_t WriteToMXFFile(mxfpp::File *f) {
		mxfFile = f;
        size = 0;
		
		SerializeXercesDocument(doc, *this);

        mxfFile = NULL;

		return size;
	}

	void writeChars(const XMLByte* const toWrite, const XMLSize_t count, xercesc::XMLFormatter* const formatter) {
        if (mxfFile!=NULL)
		    mxfFile->write((const unsigned char*)toWrite, count);
        else if (writeToStringStream)
            sstream.write((const char*)toWrite, count);
		size += count;
	}

	virtual ~DarkDOMDocumentSerializer() {
		size = 0;
	}

    uint64_t ProbeSize() {
        mxfpp::File *t_mxfFile = mxfFile;
        size = 0;

        SerializeXercesDocument(doc, *this);

        return size;
    }

    std::string GetData() {

        size = 0;
        writeToStringStream = true;
        // reset the string stream
        sstream.str( std::string() );
        sstream.clear();
		
		SerializeXercesDocument(doc, *this);

        mxfFile = NULL;

        return sstream.str();

    }

    bmx::TextEncoding GetTextEncoding() {
        return bmx::UTF8;
    }

    bmx::ByteOrder GetByteOrder() {
        return bmx::BMX_BYTE_ORIENTED;
    }

    std::string GetLanguageCode() {
        XMLCh* xml_ns = XMLString::transcode("http://www.w3.org/XML/1998/namespace");
        XMLCh* xml_lang = XMLString::transcode("lang");

        xercesc::DOMElement* e = doc.getDocumentElement();
        const XMLCh* lang = e->getAttributeNS(xml_ns, xml_lang);

        XMLString::release(&xml_ns); XMLString::release(&xml_lang);
        if (lang != NULL) {
            xercesc::TranscodeToStr trans_lang(lang, "UTF-8");
            return std::string((char*)trans_lang.str());
        }
        return "";
    }

    std::string GetNamespace() {
        xercesc::DOMElement* e = doc.getDocumentElement();
        const XMLCh* ns = e->getNamespaceURI();
        if (ns != NULL) {
            xercesc::TranscodeToStr trans_ns(ns, "UTF-8");
            return std::string((char*)trans_ns.str());
        }
        return "";
    }

};

}
}

#endif
