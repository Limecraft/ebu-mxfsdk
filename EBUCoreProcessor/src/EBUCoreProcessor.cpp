
#include <iostream>
#include <fstream>
#include <memory>

#include <bmx/BMXException.h>
#include <bmx/Logging.h>
#include <bmx/ByteArray.h>

#include "EBUCoreMapping.h"
#include "EBUCoreProcessor.h"

#include <xercesc/util/TransService.hpp>

using namespace ebuCore_2011;
using namespace mxfpp;
using namespace bmx;

namespace EBUCore {

static const uint32_t MEMORY_WRITE_CHUNK_SIZE   = 8192;

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

void EmbedEBUCoreMetadata(	std::auto_ptr<ebuCoreMainType> metadata, 
							const char* mxfLocation, 
							void (*progress_callback)(float progress, std::string& message, std::string& function),
							bool optNoIdentification) {
	
}

void EmbedEBUCoreMetadata(	const char* metadataLocation, 
							const char* mxfLocation, 
							void (*progress_callback)(float progress, std::string& message, std::string& function),
							bool optNoIdentification) {
	std::ifstream input(metadataLocation);
	std::auto_ptr<ebuCoreMainType> ebuCoreMainElementPtr (ebuCoreMain (input, xml_schema::flags::dont_validate | xml_schema::flags::keep_dom));
	EmbedEBUCoreMetadata(ebuCoreMainElementPtr, mxfLocation, progress_callback, optNoIdentification);	
}

void EmbedEBUCoreMetadata(	xercesc::DOMDocument& metadataDocument, 
							const char* mxfLocation, 
							void (*progress_callback)(float progress, std::string& message, std::string& function),
							bool optNoIdentification) {
	std::auto_ptr<ebuCoreMainType> ebuCoreMainElementPtr (ebuCoreMain (metadataDocument, xml_schema::flags::dont_validate | xml_schema::flags::keep_dom));
	EmbedEBUCoreMetadata(ebuCoreMainElementPtr, mxfLocation, progress_callback, optNoIdentification);	
}

uint64_t BufferIndex(File* mFile, Partition* partition, bmx::ByteArray& index_bytes, uint32_t* index_length) {
	*index_length = partition->getIndexByteCount();
	std::cout << "Footer Partition index size: " << partition->getIndexByteCount() << std::endl;

	// skip to the end of the header metadata: Partition Pack + Header Byte Count
	mxfKey foot_key;
	uint8_t foot_llen;
	uint64_t foot_len;
	mFile->seek(partition->getThisPartition(), SEEK_SET);
	mFile->readKL(&foot_key, &foot_llen, &foot_len);
	mFile->skip(foot_len);

	// there can be a filler after the partition pack, skip it
	mFile->readNextNonFillerKL(&foot_key, &foot_llen, &foot_len); // check for EOF now in case no more KLVs found??
	// record the current (- keylength and lenlength) as begin position for metadata to write
	uint64_t pos_write_start_metadata = mFile->tell() - mxfKey_extlen - foot_llen;

	// we are now in the next KLV, is it header metadata?
	if (partition->getHeaderByteCount() > 0) {
		// it is, skip past it (per 377M, this should include any fillers following the header metadata!)
		mFile->skip(partition->getHeaderByteCount() - mxfKey_extlen - foot_llen);
	} else {
		// there is no header metadata, which means that we have skipped too far, 
		// we're in the first index segment now, attempt to seek backward
		mFile->seek(- mxfKey_extlen - foot_llen, SEEK_CUR);
	}

	// read the index segments into a byte buffer for later relocation
	if (index_bytes.GetSize() < *index_length)
		index_bytes.Grow(*index_length);
	uint32_t br = mFile->read(index_bytes.GetBytes(), *index_length);
	index_bytes.SetSize(*index_length);
	std::cout << "bytes read: " << br << std::endl;
	
	return pos_write_start_metadata;
}

uint64_t WriteMetadataToMemoryFile(File* mFile, MXFMemoryFile **destMemFile, HeaderMetadata *mHeaderMetadata, uint64_t metadata_read_position, Partition* metadataDestitionPartition, Partition* metadataSourcePartition) {
	mxfKey key;
	uint8_t llen;
	uint64_t len;

	// cache this in case we are writing to the source partition
	uint64_t oriSourceHeaderByteCount = metadataSourcePartition->getHeaderByteCount();

	// we write the metadata to a buffer memory file first, 
	// write 1) the in-mem metadata structure, 2) then dark/unknown sets
	MXFMemoryFile *cMemFile;
	mxf_mem_file_open_new(MEMORY_WRITE_CHUNK_SIZE, /* virtual pos: don't use an offset unless req, otherwise confusing */ 0, &cMemFile);
	MXFFile *mxfMemFile = mxf_mem_file_get_file(cMemFile);
	// temporarily wrap the the memory file for use by the libMXF++ classe
	File memFile(mxfMemFile);

	// write the header metadata into the file
	uint64_t footerThisPartition = metadataDestitionPartition->getThisPartition();
	metadataDestitionPartition->setThisPartition(0);	// temporarily override so that internals don't get confused 
														// (need to put this back at the end anyway)
	KAGFillerWriter reserve_filler_writer(metadataDestitionPartition);
	mHeaderMetadata->write(&memFile, metadataDestitionPartition, NULL);
	uint64_t mHeaderMetadataEndPos = memFile.tell();  // need this position when we re-write the header metadata */
	metadataDestitionPartition->setThisPartition(footerThisPartition);

	// loop back to the beginning of the metadata and find elements that were skipped,
	// because, they were dark, append these to the end of the header metadata
	uint8_t *KLVBuffer = new uint8_t[64*1024];

	mFile->seek(metadata_read_position, SEEK_SET);
	uint64_t count = 0;
	int i = 0;
	while (count < oriSourceHeaderByteCount)
	{
		mFile->readKL(&key, &llen, &len);
		printf("Count: %lx ", count + 512);

		count += mxfKey_extlen + llen;
		count += mFile->read(KLVBuffer, len);

		// is a set with this key in the final header metadata? no, then append it
		MXFList *setList = NULL;
		if (mxf_find_set_by_key(mHeaderMetadata->getCHeaderMetadata(), &key, &setList)) {
			if (mxf_get_list_length(setList) == 0 && 
				!mxf_is_primer_pack(&key) && /* don't include any primer pack or fillers */
				!mxf_is_filler(&key)) {
				mxf_print_key(&key);
				// no errors and the list is empty, append the KLV to the memory file
				mxf_write_kl(mxfMemFile, &key, len);
				mxf_file_write(mxfMemFile, KLVBuffer, len);
				i++;
			} else printf("\n");
			mxf_free_list(&setList);
		}
	}
	std::cout << "Rogue KLVS: " << i << std::endl;

	// fill the appended metadata up to the KAG
	reserve_filler_writer.write(&memFile);

	// how many bytes have we written to the memoryfile?
	uint64_t memFileSize = mxf_file_tell(mxfMemFile);

	// set output
	*destMemFile = cMemFile;

	// bit of a hack to make sure the memFile isn't closed yet...
	memFile.swapCFile(NULL);

	return memFileSize;
}

uint64_t WriteMetadataToFile(File* mFile, HeaderMetadata *mHeaderMetadata, uint64_t metadata_read_position, uint64_t metadata_write_position, bool shiftFileBytesIfNeeded, Partition* metadataDestitionPartition, Partition* metadataSourcePartition) {
	MXFMemoryFile *cMemFile;

	// record the original metadata size
	uint64_t oriMetadataSize = metadataSourcePartition->getHeaderByteCount();

	// how many bytes have we written to the memoryfile?
	uint64_t memFileSize = WriteMetadataToMemoryFile(mFile, &cMemFile, mHeaderMetadata, metadata_read_position, metadataDestitionPartition, metadataSourcePartition);

	// shift if required
	if (shiftFileBytesIfNeeded && memFileSize > oriMetadataSize) {
		ShiftBytesInFile(mFile, metadata_write_position, memFileSize - oriMetadataSize);
	}

	// write the memory file to the physical file
	// seek back to the serialization position for the header metadata
	mFile->seek(metadata_write_position, SEEK_SET);
	mFile->setMemoryFile(cMemFile);
	mFile->closeMemoryFile();

	return memFileSize;
}


void ShiftBytesInFile(mxfpp::File* mFile, int64_t shiftPosition, int64_t shiftOffset) {
	// allocate ourselves a buffer for copying
#define BUFFER_SIZE	(32*1024)
#define MAX(a,b)	((a) > (b) ? (a) : (b))
	uint8_t *buffer = new uint8_t[BUFFER_SIZE];
	// move to the back of the file
	mFile->seek(0, SEEK_END);
	// how far are we in the file?
	int64_t eof = mFile->tell();
	int64_t bufferPos = eof - BUFFER_SIZE;

	uint64_t readFromBuffer = MAX(0, BUFFER_SIZE - MAX(0, shiftPosition - bufferPos));
	while(readFromBuffer > 0) {
		// fill our buffer to the extent we need to read
		mFile->seek(bufferPos + (BUFFER_SIZE - readFromBuffer), SEEK_SET);
		mFile->read(buffer, readFromBuffer);
		// then write to a position shiftPosition further
		mFile->seek(bufferPos + (BUFFER_SIZE - readFromBuffer) + shiftOffset, SEEK_SET);
		mFile->write(buffer, readFromBuffer);

		bufferPos -= BUFFER_SIZE;
		readFromBuffer = MAX(0, BUFFER_SIZE - MAX(0, shiftPosition - bufferPos));
	}

	delete buffer;
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
