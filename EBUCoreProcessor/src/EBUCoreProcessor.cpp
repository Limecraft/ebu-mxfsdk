
#include <iostream>
#include <fstream>
#include <memory>

#include <bmx/BMXException.h>
#include <bmx/Logging.h>

#include "EBUCoreMapping.h"
#include "EBUCoreProcessor.h"

#include <xercesc/util/TransService.hpp>

using namespace ebuCore_2011;
using namespace mxfpp;
using namespace bmx;

namespace EBUCore {

// {DAE59218-AF8D-47D4-A216-B6C648EA548C}
static const mxfUUID ProductUID = 
{ 0xda, 0xe5, 0x92, 0x18, 0xaf, 0x8d, 0x47, 0xd4, 0xa2, 0x16, 0xb6, 0xc6, 0x48, 0xea, 0x54, 0x8c };
static const mxfProductVersion EBU_SDK_PRODUCT_VERSION = {0, 1, 0, 0, 0};

Identification* GenerateEBUCoreIdentificationSet(mxfpp::HeaderMetadata *destination) {
	mxfUUID GenerationUID;
	mxfTimestamp GenerationTime;
	mxf_generate_uuid(&GenerationUID);
	mxf_get_timestamp_now(&GenerationTime);

	Identification* newId = new Identification(destination);
	destination->getPreface()->appendIdentifications(newId);
	newId->initialise("EBU", "EBUCore SDK", "0.1", ProductUID);
	newId->setProductVersion(EBU_SDK_PRODUCT_VERSION);
	newId->setModificationDate(GenerationTime);
	newId->setThisGenerationUID(GenerationUID);
	newId->setGenerationUID(GenerationUID);
	return newId;
}

DMFramework* Process(const char* location, HeaderMetadata *destination, Identification* identificationToAppend) {
	std::ifstream input(location);
	std::auto_ptr<ebuCoreMainType> ebuCoreMainElementPtr (ebuCoreMain (input, xml_schema::flags::dont_validate | xml_schema::flags::keep_dom));

	// Generate a new Generation UID if necessary, and provide to each mapping function
	GenerationUIDAppender *appender = NULL;
	if (identificationToAppend != NULL) {
		appender = new GenerationUIDAppender(identificationToAppend->getThisGenerationUID());
	}
	ebucoreMainFramework *framework = new ebucoreMainFramework(destination);
	appender->Modify(framework);
	framework->setdocumentId(location);	// use the file location as document id

	ebucoreCoreMetadata *core = new ebucoreCoreMetadata(destination);
	appender->Modify(core);
	if (appender != NULL)
		mapCoreMetadata(ebuCoreMainElementPtr->coreMetadata(), core, appender);
	else
		mapCoreMetadata(ebuCoreMainElementPtr->coreMetadata(), core);

	ebucoreMetadataSchemeInformation *info = new ebucoreMetadataSchemeInformation(destination);
	appender->Modify(info);
	if (appender != NULL)
		mapMetadataSchemeInformation(*ebuCoreMainElementPtr, info, appender);
	else
		mapMetadataSchemeInformation(*ebuCoreMainElementPtr, info);

	framework->setcoreMetadata(core);
	framework->setmetadataSchemeInformation(info);

	std::cout << framework->getdocumentId();

	if (appender!=NULL)
		delete appender;

	return framework;
}

void RegisterMetadataExtensionsforEBUCore(mxfpp::DataModel *data_model)
{
	EBUCore::RegisterExtensions(data_model);	
}

DMFramework* Process(const char* location) {

	DataModel *mDataModel = new DataModel();
	RegisterMetadataExtensionsforEBUCore(mDataModel);

	HeaderMetadata *md = new HeaderMetadata(mDataModel);

	return Process(location, md);
}

void InsertFramework(HeaderMetadata *header_metadata, uint32_t track_id, std::string track_name, DMFramework *framework, ObjectModifier *mod = NULL)
{
    BMX_ASSERT(header_metadata);

    MaterialPackage *material_package = header_metadata->getPreface()->findMaterialPackage();
    BMX_ASSERT(material_package);

    // Preface - ContentStorage - Package - DM Track
    StaticTrack *dm_track = new StaticTrack(header_metadata);
	if (mod!=NULL) mod->Modify(dm_track);
    material_package->appendTracks(dm_track);
    dm_track->setTrackName(track_name);
    dm_track->setTrackID(track_id);
    dm_track->setTrackNumber(0);

    // Preface - ContentStorage - Package - DM Track - Sequence
    Sequence *sequence = new Sequence(header_metadata);
	if (mod!=NULL) mod->Modify(sequence);
    dm_track->setSequence(sequence);
    sequence->setDataDefinition(MXF_DDEF_L(DescriptiveMetadata));

    // Preface - ContentStorage - Package - DM Track - Sequence - DMSegment
    DMSegment *dm_segment = new DMSegment(header_metadata);
	if (mod!=NULL) mod->Modify(dm_segment);
    sequence->appendStructuralComponents(dm_segment);
    dm_segment->setDataDefinition(MXF_DDEF_L(DescriptiveMetadata));

    // move the framework set after the dm degment set
    mxf_remove_set(header_metadata->getCHeaderMetadata(), framework->getCMetadataSet());
    BMX_CHECK(mxf_add_set(header_metadata->getCHeaderMetadata(), framework->getCMetadataSet()));

    // Preface - ContentStorage - Package - DM Track - Sequence - DMSegment - DMFramework
    dm_segment->setDMFramework(framework);
}

void AppendDMSLabel(HeaderMetadata *header_metadata, mxfUL scheme_label)
{
    BMX_ASSERT(header_metadata);
	Preface *preface = header_metadata->getPreface();

    std::vector<mxfUL> dm_schemes = preface->getDMSchemes();
    size_t i;
    for (i = 0; i < dm_schemes.size(); i++) {
        if (mxf_equals_ul(&dm_schemes[i], &scheme_label))
            break;
    }
	try {
		if (i >= dm_schemes.size())
			preface->appendDMSchemes(scheme_label);
	} catch (const MXFException &ex) {
		// oops, cannot append, maybe something wrong with the array as read from the file
		// try and create a new DMSchemes array if empty now
		if (dm_schemes.size() == 0) {
			preface->setDMSchemes(std::vector<mxfUL>());
			preface->appendDMSchemes(scheme_label);
		}
	}
}

void RegisterFrameworkObjectFactoriesforEBUCore(mxfpp::HeaderMetadata *metadata) {
	EBUCore::RegisterFrameworkObjectFactory(metadata);
}

void InsertEBUCoreFramework(HeaderMetadata *header_metadata, DMFramework *framework, Identification *identificationToAppend) {

	BMX_ASSERT(header_metadata != NULL);

	// Append the EBU Core DMS label to the Preface
	AppendDMSLabel(header_metadata, MXF_DM_L(EBUCoreDescriptiveScheme));
	// Insert the framework

	GenerationUIDAppender *appender = NULL;
	if (identificationToAppend != NULL) {
		appender = new GenerationUIDAppender(identificationToAppend->getThisGenerationUID());
	}

    InsertFramework(header_metadata, 10001, "EBU_Core", framework, appender);

	if (appender!=NULL)
		delete appender;
}

static std::vector<DMFramework*> ebu_get_static_frameworks(MaterialPackage *mp)
{
    std::vector<DMFramework*> frameworks;

    // expect to find Static DM Track -> Sequence -> DM Segment -> DM Framework

    std::vector<GenericTrack*> tracks = mp->getTracks();
    size_t i;
    for (i = 0; i < tracks.size(); i++) {
        StaticTrack *st = dynamic_cast<StaticTrack*>(tracks[i]);
        if (!st)
            continue;

        StructuralComponent *sc = st->getSequence();
        if (!sc || sc->getDataDefinition() != MXF_DDEF_L(DescriptiveMetadata))
            continue;

        Sequence *seq = dynamic_cast<Sequence*>(sc);
        DMSegment *seg = dynamic_cast<DMSegment*>(sc);
        if (!seq && !seg)
            continue;

        if (seq) {
            std::vector<StructuralComponent*> scs = seq->getStructuralComponents();
            if (scs.size() != 1)
                continue;

            seg = dynamic_cast<DMSegment*>(scs[0]);
            if (!seg)
                continue;
        }

        if (!seg->haveDMFramework())
            continue;

        DMFramework *framework = seg->getDMFrameworkLight();
        if (framework)
            frameworks.push_back(framework);
    }

    return frameworks;
}

void ReadAndSerializeEBUCore(HeaderMetadata *metadata, const char* outputfilename) {

	MaterialPackage *mp = metadata->getPreface()->findMaterialPackage();
	if (!mp) {
        return;
    }

	ebucoreMainFramework *ebucore = NULL;
	std::vector<DMFramework*> static_frameworks = ebu_get_static_frameworks(mp);
	size_t i;
    for (i = 0; i < static_frameworks.size(); i++) {
		ebucoreMainFramework *p = dynamic_cast<ebucoreMainFramework*>(static_frameworks[i]);
        if (p) {
			ebucore = p;
			break;
		}
    }

	if (ebucore) {

		titleType::title_type dc_title("Berlin Wall 50th");
		titleType title(dc_title);

		ebuCoreMainType::coreMetadata_type main;
		//main.title().push_back(title);

		mapCoreMetadata(ebucore->getcoreMetadata(), main);

		// map the EBU Core KLV framework to the XSD-derived counterpart
		ebuCoreMainType ebuCoreMainElement(main);
		//ebuCoreMainElement.schema(ebuCoreMainElement.schema_default_value());
		//ebuCoreMainElement.version(ebuCoreMainElement.version_default_value());
		//ebuCoreMainElement.version("1.3");

		std::auto_ptr<entityType> p( new entityType() );
		ebucoreMetadataSchemeInformation *info = ebucore->getmetadataSchemeInformation();
		mapEntity(info->getebucoreMetadataProvider(), *(p.get()));
		ebuCoreMainElement.metadataProvider(p);

		xml_schema::namespace_infomap map;
		map[""].name = "urn:ebu:metadata-schema:ebuCore_2011";
		map["dc"].name = "http://purl.org/dc/elements/1.1/";

		// open a file output stream
		std::ofstream out(outputfilename);
		ebuCoreMain (out, ebuCoreMainElement, map);
		out.close();
	}

}

} // namespace EBUCore
