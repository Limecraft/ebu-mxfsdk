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
 
#define __STDC_FORMAT_MACROS
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#include <fstream>
#include <memory>
#include <time.h>

#include <bmx/BMXException.h>
#include <bmx/Logging.h>
#include <bmx/ByteArray.h>
#include <bmx/mxf_reader/MXFFileReader.h>

// mediocre macro definition for MAX
#define MAX(a,b)	((a) > (b) ? (a) : (b))
#define MIN(a,b)	((a) < (b) ? (a) : (b))

#define THROW_RESULT(result) \
{ \
    log_warn("Open error '%s' near %s:%d\n", #result, __FILE__, __LINE__); \
    throw result; \
}

#include <EBUCore_1_4/EBUCoreMapping.h>
#include <EBUCore_1_4/EBUCoreProcessor_1_4.h>
#include <MXFCustomMetadata.h>
#include <XercesUtils.h>

#include <xsd/cxx/xml/string.hxx>
namespace xml = xsd::cxx::xml;

#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/util/TransService.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMAttr.hpp>

using namespace ebuCore_2012;
using namespace mxfpp;
using namespace bmx;

using namespace EBUSDK::MXFCustomMetadata;
using namespace EBUSDK::Utils;

namespace EBUSDK {
namespace EBUCore {
namespace EBUCore_1_4 {

const mxfUL EBUCoreProcessor::DMScheme = { 0x06, 0x0E, 0x2B, 0x34, 0x02, 0x7F, 0x01, 0x0B, 0x0D, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 };

const mxfUL* EBUCoreProcessor::GetDescriptiveMetadataScheme() {
	return &DMScheme;
}

const mxfKey* EBUCoreProcessor::GetDarkMetadataSetKey() {
	return &DMScheme;
}

void EBUCoreProcessor::RegisterMetadataExtensions(mxfpp::DataModel *data_model) {
	RegisterExtensions(data_model);
}

void EBUCoreProcessor::RegisterFrameworkObjectFactories(mxfpp::HeaderMetadata *metadata) {
	RegisterFrameworkObjectFactory(metadata);
}

DMFramework* EBUCoreProcessor::GenerateSideCarFramework(const char* metadataLocation, HeaderMetadata *destination, Identification* identificationToAppend) {

	GenerationUIDAppender *appender = NULL;
	if (identificationToAppend != NULL) {
		appender = new GenerationUIDAppender(identificationToAppend->getThisGenerationUID());
	}
	ebucoreMainFramework *framework = new ebucoreMainFramework(destination);
	appender->Modify(framework);
	framework->setdocumentId(metadataLocation);	// use the file location as document id
	framework->setdocumentLocator(metadataLocation);

	if (appender!=NULL)
		delete appender;

	return framework;
}

DMFramework* Process(std::auto_ptr<ebuCoreMainType> metadata, const char* metadataLocation, HeaderMetadata *destination, 
											std::vector<EventInput> &eventFrameworks, Identification* identificationToAppend) {

	// Generate a new Generation UID if necessary, and provide to each mapping function
	GenerationUIDAppender *appender = NULL;
	if (identificationToAppend != NULL) {
		appender = new GenerationUIDAppender(identificationToAppend->getThisGenerationUID());
	}
	ebucoreMainFramework *framework = new ebucoreMainFramework(destination);
	if (appender!=NULL) appender->Modify(framework);
	framework->setdocumentId(metadataLocation);	// use the file location as document id

	std::vector<ebucorePartMetadata*> timelineParts;
	// get a basis for translating timecodes to edit units, use the editrate of the materialpackage
	mxfRational r = FindMaterialPackageEditRate(destination);
	// no usefull value, fill in something default
	if (r.numerator == -1 && r.denominator == 0) {
		r.numerator = 25; r.denominator = 1;
	}

	ebucoreCoreMetadata *core = new ebucoreCoreMetadata(destination);
	if (appender!=NULL) appender->Modify(core);
	if (appender != NULL)
		mapCoreMetadata(metadata->coreMetadata(), core, r, timelineParts, appender);
	else
		mapCoreMetadata(metadata->coreMetadata(), core, r, timelineParts);

	for (std::vector<ebucorePartMetadata*>::iterator it = timelineParts.begin(); it!=timelineParts.end(); it++) {
		EventInput in;
		ebucorePartFramework* fw = new ebucorePartFramework(destination);
		fw->setpartMetadata(*it);
		if (appender!=NULL) appender->Modify(fw);
		in.framework = fw;
		in.start = (*it)->getpartStartEditUnitNumber();
		in.duration = (*it)->getpartDurationEditUnitNumber();
		eventFrameworks.push_back( in );
	}

	ebucoreMetadataSchemeInformation *info = new ebucoreMetadataSchemeInformation(destination);
	if (appender!=NULL) appender->Modify(info);
	if (appender != NULL)
		mapMetadataSchemeInformation(*metadata, info, appender);
	else
		mapMetadataSchemeInformation(*metadata, info);

	framework->setcoreMetadata(core);
	framework->setmetadataSchemeInformation(info);

	if (appender!=NULL)
		delete appender;

	return framework;
}

DMFramework* EBUCoreProcessor::Process(xercesc::DOMDocument* metadataDocument, const char* metadataLocation, HeaderMetadata *destination, 
											std::vector<EventInput> &eventFrameworks, Identification* identificationToAppend) {
	std::auto_ptr<ebuCoreMainType> ebuCoreMainElementPtr(NULL);
	// actually parse the EBUCore metadata
	if (metadataDocument != NULL) {
		ebuCoreMainElementPtr = ebuCoreMain (*metadataDocument, xml_schema::flags::dont_validate | xml_schema::flags::keep_dom);
	} else {
		// use the file location to parse the metadata
		std::ifstream input(metadataLocation);
		ebuCoreMainElementPtr = ebuCoreMain (input, xml_schema::flags::dont_validate | xml_schema::flags::keep_dom);
		input.close();
	}
	return EBUCore::EBUCore_1_4::Process(ebuCoreMainElementPtr, metadataLocation, destination, eventFrameworks, identificationToAppend); 
}

DMFramework* EBUCoreProcessor::Process(const char* location, HeaderMetadata *destination, Identification* identificationToAppend) {
	std::vector<EventInput> eventFrameworks;
	std::ifstream input(location);
	std::auto_ptr<ebuCoreMainType> ebuCoreMainElementPtr (ebuCoreMain (input, xml_schema::flags::dont_validate | xml_schema::flags::keep_dom));
	return EBUCore::EBUCore_1_4::Process(ebuCoreMainElementPtr, location, destination, eventFrameworks, identificationToAppend);
}

void EBUCoreProcessor::ParseAndSerializeMetadata(	DMFramework *framework, 
										MetadataOutput outputFashion, 
										const char* metadataLocation, 
										xercesc::DOMDocument** outputDocument, 
										void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...)) {
	// assert that a coremetadata element is present!

	ebucoreMainFramework *fw = dynamic_cast<ebucoreMainFramework*>(framework);

	std::auto_ptr<ebuCoreMainType::coreMetadata_type> main( new ebuCoreMainType::coreMetadata_type() );
	mapCoreMetadata(fw->getcoreMetadata(), *main);

	// map the EBU Core KLV framework to the XSD-derived counterpart
	std::auto_ptr<ebuCoreMainType> ebuCoreMainElement( new ebuCoreMainType(main) );

	// Set global/top-level attributes of the ebuCoreMain element
	time_t now;
	::time(&now);
	tm* gmt_now = gmtime(&now);
	ebuCoreMainElement->dateLastModified( std::auto_ptr<ebuCoreMainType::dateLastModified_type>( 
		new ebuCoreMainType::dateLastModified_type( gmt_now->tm_year + 1900, gmt_now->tm_mon + 1, gmt_now->tm_mday, 0, 0) ) );
	if (fw->havedocumentId())
		ebuCoreMainElement->documentId(fw->getdocumentId());

	if (fw->havemetadataSchemeInformation()) {
		ebucoreMetadataSchemeInformation *info = fw->getmetadataSchemeInformation();
		if (info->haveebucoreMetadataProvider()) {
			std::auto_ptr<entityType> p( new entityType() );
			mapEntity(info->getebucoreMetadataProvider(), *(p.get()));
			ebuCoreMainElement->metadataProvider(p);
		}
	}

	progress_callback(0.7f, INFO, "ExtractEBUCoreMetadata", "A coreMetadata set was attached to the ebucoreMainFramework, and was processed successfully");

	xml_schema::namespace_infomap map;
	map[""].name = "urn:ebu:metadata-schema:ebuCore_2012";
	map["dc"].name = "http://purl.org/dc/elements/1.1/";

	// In any case, generate a DOMDocument which we'll return or use for serialization
	::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > xml = ebuCoreMain(*ebuCoreMainElement, map);

	// Do preparations to the DOM document directly that the schema prohibits
	DOMElement *e = xml->getDocumentElement();
	// Set version to fixed 1.4 for this processor
	e->setAttribute(xml::string("version").c_str(), xml::string("1.4").c_str());
	// Set schema if present in schemainformation
	if (fw->havemetadataSchemeInformation()) {
		ebucoreMetadataSchemeInformation *info = fw->getmetadataSchemeInformation();
		if (info->haveebucoreMetadataScheme()) {
			e->setAttribute(xml::string("schema").c_str(), xml::string(info->getebucoreMetadataScheme()).c_str());
		}
	}

	if (outputFashion == SERIALIZE_TO_FILE) {
		progress_callback(0.9f, INFO, "ExtractEBUCoreMetadata", "Writing EBUCore metadata to XML file at %s\n", metadataLocation);

		// open a file output stream
		LocalFileFormatTarget f(metadataLocation);
		SerializeXercesDocument(*xml, f);
	} 
	else if (outputFashion == OUTPUT_AS_DOM_DOCUMENT) {
		progress_callback(0.9f, INFO, "ExtractEBUCoreMetadata", "Writing EBUCore metadata to output Xerces-C DOM Document");
		
		// pass the DOM document to output
		*outputDocument = xml.get();
		xml.release();
	}
	
}

bool EBUCoreProcessor::FrameworkHasActualMetadata(DMFramework *fw) {
	ebucoreMainFramework *p = dynamic_cast<ebucoreMainFramework*>(fw);
	return (p) ? p->havecoreMetadata() : false;
}

bool EBUCoreProcessor::FrameworkRefersToExternalMetadata(DMFramework *fw) {
	ebucoreMainFramework *p = dynamic_cast<ebucoreMainFramework*>(fw);
	return (p) ? p->havedocumentLocator() : false;
}

std::string EBUCoreProcessor::GetFrameworkExternalMetadataLocation(DMFramework *fw) {
	ebucoreMainFramework *p = dynamic_cast<ebucoreMainFramework*>(fw);
	return p->getdocumentLocator();
}

DMFramework* EBUCoreProcessor::FindMetadataFramework(HeaderMetadata *metadata) {

	MaterialPackage *mp = metadata->getPreface()->findMaterialPackage();
	if (!mp) {
		// throw an exception!
		return NULL;
    }

	ebucoreMainFramework *ebucore = NULL;
	std::vector<DMFramework*> static_frameworks = GetStaticFrameworks(mp);
	size_t i;
    for (i = 0; i < static_frameworks.size(); i++) {
		ebucoreMainFramework *p = dynamic_cast<ebucoreMainFramework*>(static_frameworks[i]);
        if (p) {
			ebucore = p;
			break;
		}
    }

	return ebucore;
}

/*void FindAndSerializeEBUCore(HeaderMetadata *metadata, const char* outputfilename) {
	
	DMFramework *fw = FindEBUCoreMetadataFramework(metadata);

	if (fw != NULL && EBUCoreFrameworkHasActualMetadata(fw)) {
		ParseAndSerializeEBUCoreMetadata(fw, SERIALIZE_TO_FILE, outputfilename, NULL, NULL /* dangerous! *);
	}
}*/

} // namespace EBUCore_1_4
} // namespace EBUCore
} //namespace EBUSDK
