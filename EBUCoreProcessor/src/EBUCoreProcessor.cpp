
#define __STDC_FORMAT_MACROS
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#include <fstream>
#include <memory>

#include <bmx/BMXException.h>
#include <bmx/Logging.h>
#include <bmx/ByteArray.h>
#include <bmx/mxf_reader/MXFFileReader.h>

#if defined(_WIN32)
#include <mxf/mxf_win32_file.h>
#endif

// mediocre macro definition for MAX
#define MAX(a,b)	((a) > (b) ? (a) : (b))
#define MIN(a,b)	((a) < (b) ? (a) : (b))

#define THROW_RESULT(result) \
{ \
    log_warn("Open error '%s' near %s:%d\n", #result, __FILE__, __LINE__); \
    throw result; \
}

#if defined(_WIN32)
	int file_flags = MXF_WIN32_FLAG_SEQUENTIAL_SCAN;
#define MXF_OPEN_READ(fn, pf)   mxf_win32_file_open_read(fn, file_flags, pf)
#define MXF_OPEN_MODIFY(fn, pf)   mxf_win32_file_open_modify(fn, file_flags, pf)
#else
#define MXF_OPEN_READ(fn, pf)   mxf_disk_file_open_read(fn, pf)
#define MXF_OPEN_MODIFY(fn, pf)   mxf_disk_file_open_modify(fn, pf)
#endif

#include <EBUCoreMapping.h>
#include <MXFCustomMetadata.h>
#include <EBUCoreProcessor.h>
#include <XercesUtils.h>

#include <xercesc/util/TransService.hpp>

using namespace ebuCore_2012;
using namespace mxfpp;
using namespace bmx;

using namespace EBUSDK::MXFCustomMetadata;
using namespace EBUSDK::Utils;

namespace EBUSDK {
namespace EBUCore {

static const uint32_t MEMORY_WRITE_CHUNK_SIZE   = 8192;

void WriteKLVContentsToFile(const char* file, File* mxfFile, uint64_t length) {
	std::ofstream out(file, std::ofstream::out | std::ifstream::binary);
	if (!out.fail()) {
		uint64_t size = 0;
		std::streamsize read=0;
		unsigned char buffer[MEMORY_WRITE_CHUNK_SIZE];
		while (size < length) {
			read = MIN(MEMORY_WRITE_CHUNK_SIZE, length-size);
			if (read > 0) {
				read = mxfFile->read(buffer, read);
				out.write((const char*)buffer, read);
				size += read;
			}
		}
	}
	out.close();
}

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

DMFramework* GenerateSideCarFramework(const char* metadataLocation, HeaderMetadata *destination, Identification* identificationToAppend) {

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

DMFramework* Process(const char* location, HeaderMetadata *destination, Identification* identificationToAppend) {
	std::vector<EventInput> eventFrameworks;
	std::ifstream input(location);
	std::auto_ptr<ebuCoreMainType> ebuCoreMainElementPtr (ebuCoreMain (input, xml_schema::flags::dont_validate | xml_schema::flags::keep_dom));
	return Process(ebuCoreMainElementPtr, location, destination, eventFrameworks, identificationToAppend);
}

void RegisterMetadataExtensionsforEBUCore(mxfpp::DataModel *data_model)
{
	EBUSDK::EBUCore::RegisterExtensions(data_model);	
}


void EmbedEBUCoreMetadata(	std::auto_ptr<ebuCoreMainType> metadata, 
							const char* metadataLocation,
							const char* mxfLocation,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
							bool optEmbedAsSidecar,
							bool optNoIdentification, bool optForceHeader) {

		progress_callback(0.2f, INFO, "EmbedEBUCoreMetadata", "Opening MXF file %s", mxfLocation);

		std::auto_ptr<File> mFile( File::openModify(mxfLocation) );	// throws MXFException if open failed!

		std::auto_ptr<DataModel> mDataModel ( new DataModel() );
		EBUCore::RegisterMetadataExtensionsforEBUCore(&*mDataModel);

		// ///////////////////////////////////////
		// / 1. Open MXF File and locate all partitions, using the RIP
		// ///////////

		if (!mFile->readPartitions())
			throw BMXException("Failed to read all partitions. File may be incomplete or invalid");

	    const std::vector<Partition*> &partitions = mFile->getPartitions();

		// ///////////////////////////////////////
	    // / 1a. Locate the Metadata to use for extension
		/*		We prefer closed footer metadata when available (if the metadata 
				is repeated in the footer, it is likely to be more up-to-date than
				that in the header.																*/
		// ///////////
		progress_callback(0.25, INFO, "EmbedEBUCoreMetadata", "Locating preferred MXF metadata");

	    Partition *metadata_partition = NULL, *headerPartition = NULL, *footerPartition = NULL;

		metadata_partition = FindPreferredMetadataPartition(partitions, &headerPartition, &footerPartition);
		if (!metadata_partition)
			throw BMXException("No MXF suitable MXF metadata found");

		progress_callback(0.3f, INFO, "EmbedEBUCoreMetadata", "Reading and parsing MXF metadata");

		mxfKey key;
		uint8_t llen;
		uint64_t len;

		std::auto_ptr<HeaderMetadata> mHeaderMetadata ( new HeaderMetadata(&*mDataModel) );

		mFile->seek(metadata_partition->getThisPartition(), SEEK_SET);
		mFile->readKL(&key, &llen, &len);
		mFile->skip(len);
		mFile->readNextNonFillerKL(&key, &llen, &len);
		BMX_CHECK(mxf_is_header_metadata(&key));
		uint64_t pos_start_metadata =  mFile->tell() - mxfKey_extlen - llen;
		mHeaderMetadata->read(&*mFile, metadata_partition, &key, llen, len);

		uint64_t metadata_original_len_with_fill = metadata_partition->getHeaderByteCount();

		// ///////////////////////////////////////
		// / 2. Insert the EBU Core object tree into the header metadata
		// ///////////
		progress_callback(0.4f, INFO, "EmbedEBUCoreMetadata", "Embedding EBUCore metadata in MXF metadata");

		Identification* id = optNoIdentification ? NULL : EBUCore::GenerateEBUCoreIdentificationSet(&*mHeaderMetadata);
		// choose between sidecar serialization or fully fledged KLV-encoded metadata

		// process the EBUCore metadata
		std::vector<EventInput> eventFrameworks;
		DMFramework *framework = optEmbedAsSidecar ?
			EBUCore::GenerateSideCarFramework(metadataLocation, &*mHeaderMetadata, id) :
			EBUCore::Process(metadata, metadataLocation, &*mHeaderMetadata, eventFrameworks, id);

		// remove any previously present EBUCore metadata
		//RemoveEBUCoreFrameworks(&*mHeaderMetadata);

		// insert the static track DM framework
		EBUCore::InsertEBUCoreFramework(&*mHeaderMetadata, framework, id);
		// insert the event track DM frameworks on the timeline, if any
		if (eventFrameworks.size() > 0) {
			EBUCore::InsertEBUCoreEventFrameworks(&*mHeaderMetadata, eventFrameworks, id);
		}

		// ///////////////////////////////////////
		// / 2. In order to avoid rewriting large portions of the file, we append our metadata
		// / to that of the footer partition (if already present, and new otherwise)
		// ///////////
		if (!optForceHeader) {

			progress_callback(0.5, INFO, "EmbedEBUCoreMetadata", "Writing new metadata into footer partition");

			// What does the footer partition look like? Are there index entries to move around?
			uint32_t index_length = 0;
			bmx::ByteArray index_bytes(index_length);
			uint64_t pos_write_start_metadata = BufferIndex(&*mFile, footerPartition, index_bytes, &index_length);

			uint64_t headerMetadataSize = WriteMetadataToFile(&*mFile, &*mHeaderMetadata, pos_start_metadata, pos_write_start_metadata, false, footerPartition, metadata_partition);

			if (index_length > 0) {
				progress_callback(0.75, DEBUG, "EmbedEBUCoreMetadata", "Rewritng footer partition index entries");

				// write the index tables back to the footer partition
				mFile->write(index_bytes.GetBytes(), index_bytes.GetSize());
			}

			progress_callback(0.8f, INFO, "EmbedEBUCoreMetadata", "Rewriting file Random Index Pack");

			mFile->writeRIP();

			progress_callback(0.9f, INFO, "EmbedEBUCoreMetadata", "Updating partition packs");

			// seek backwards and update footer partition pack
			footerPartition->setHeaderByteCount(/*footerPartition->getHeaderByteCount() + */ headerMetadataSize); // Add dark metadata elements to file
			mFile->seek(footerPartition->getThisPartition(), SEEK_SET);
			footerPartition->write(&*mFile);

			// ///////////////////////////////////////
			// / 3. In case of in-place updates: properly update partition packs...
			/*		Header partition:
						Open -> Open (If the metadata in the header was open, leave open, there's more to come in the footer)
						Closed -> Open (Open closed metadata, the header metadata may no longer be used)
					Body partition:
						No metadata: Leave as is, there's no metadata to be found anyway
						Open -> Open (Leave as is, more to come later)
						Closed -> Open (Indicate that this is no longer a verbatim repitition of the header metadata)
					Footer partition:
						-> Open (if all other partitions were open, we append our EBU Core metadata and leave the partition/file open)
						-> Closed (in other cases, this will contain the finalized (with EBU Core) metadata)
						No metadata: Use metadata from the header partition as final and insert in this partition
			*/
			// ///////////
			for (size_t i = 0 ; i < partitions.size()-1; i++) {	// rewrite for all but the footer partition
				Partition *p = partitions[i];
				if (mxf_is_header_partition_pack(p->getKey())) {
					p->setKey( mxf_partition_is_complete(p->getKey()) ? &MXF_PP_K(OpenComplete, Header) : &MXF_PP_K(OpenIncomplete, Header) );
				}
				else if (mxf_is_body_partition_pack(p->getKey())) {
					p->setKey( mxf_partition_is_complete(p->getKey()) ? &MXF_PP_K(OpenComplete, Body) : &MXF_PP_K(OpenIncomplete, Body) );
				} 
				mFile->seek(p->getThisPartition(), SEEK_SET);
				p->write(&*mFile);
			}

		} else {
			// ///////////////////////////////////////
			// / 2a. Provide an override where the file is rewritten to accomodate updated metadata in the header partition?
			// / (This could become necessary when generated MXF files need 
			// / to be natively supported by playout/hardware-constrained machines)
			// ///////////
			progress_callback(0.5, INFO, "EmbedEBUCoreMetadata", "Forcing new metadata into header partition, shifting bytes where necessary");

			uint64_t oriMetadataSize = headerPartition->getHeaderByteCount();

			// Write metadata to the header partition, forcing a file bytes shift if required (likely)
			uint64_t headerMetadataSize = WriteMetadataToFile(&*mFile, &*mHeaderMetadata, pos_start_metadata, pos_start_metadata, true, headerPartition, metadata_partition);

			uint64_t fileOffset = headerMetadataSize - oriMetadataSize;

			progress_callback(0.8f, INFO, "EmbedEBUCoreMetadata", "Shifted file bytes after header partition by %" PRId64 " bytes", fileOffset);

			progress_callback(0.81f, INFO, "EmbedEBUCoreMetadata", "Updating partition pack offsets");
			
			// In this case, there's no further need for shifting the index bytes (been done already)
			// What we do have to do is update each of the partition packs with an updated offset
			uint64_t prevPartition = 0;
			for (size_t i = 0 ; i < partitions.size(); i++) {
				Partition *p = partitions[i];
				if (!mxf_is_header_partition_pack(p->getKey())) {
					p->setThisPartition(p->getThisPartition() + fileOffset);
					p->setPreviousPartition(prevPartition);
				} else if (mxf_is_header_partition_pack(p->getKey())) {
					// make sure this is updated also
					p->setHeaderByteCount(headerMetadataSize);
				}
				p->setFooterPartition(p->getFooterPartition() + fileOffset);
				mFile->seek(p->getThisPartition(), SEEK_SET);
				p->write(&*mFile);
				prevPartition = p->getThisPartition();
			}

			// Finish by re-writing the rip.
			// To be safe, we will overwrite the entire RIP of the previous file, 
			// by extending the filler if present, or by adding a new filler up until the next KAG.

			progress_callback(0.9f, INFO, "EmbedEBUCoreMetadata", "Rewriting file Random Index Pack");

			// find the offset in the footer partition from which the header and index starts
			int64_t eof, partitionSectionOffset;
			int64_t fillerWritePosition = FindLastPartitionFill(&*mFile, footerPartition, &partitionSectionOffset, &eof);

			// write the filler to the next KAG after the end of the file
			mFile->seek(fillerWritePosition, SEEK_SET);
			footerPartition->allocateSpaceToKag(&*mFile, eof - fillerWritePosition);

			if (footerPartition->getIndexByteCount() > 0)
				footerPartition->setIndexByteCount(mFile->tell() - partitionSectionOffset);
			else if (footerPartition->getHeaderByteCount() > 0)
				footerPartition->setHeaderByteCount(mFile->tell() - partitionSectionOffset);

			mFile->writeRIP();

			mFile->seek(footerPartition->getThisPartition(), SEEK_SET);
			footerPartition->write(&*mFile);
		}

        // clean-up through auto_ptr destruction
}

void EmbedDarkEBUCoreMetadata(	xercesc::DOMDocument *metadataDocument, 
							const char* metadataLocation,
							const char* mxfLocation, 
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
							bool optNoIdentification, bool optForceHeader) {

		progress_callback(0.2f, INFO, "EmbedEBUCoreMetadata", "Opening MXF file %s", mxfLocation);

		std::auto_ptr<File> mFile( File::openModify(mxfLocation) );	// throws MXFException if open failed!

		// ///////////////////////////////////////
		// / 1. Open MXF File and locate all partitions, using the RIP
		// ///////////

		if (!mFile->readPartitions())
			throw BMXException("Failed to read all partitions. File may be incomplete or invalid");

	    const std::vector<Partition*> &partitions = mFile->getPartitions();

		// ///////////////////////////////////////
	    // / 1a. Locate the Metadata to use for extension
		/*		We prefer closed footer metadata when available (if the metadata 
				is repeated in the footer, it is likely to be more up-to-date than
				that in the header.																*/
		// ///////////
		progress_callback(0.25, INFO, "EmbedEBUCoreMetadata", "Locating preferred MXF metadata");

	    Partition *metadata_partition = NULL, *headerPartition = NULL, *footerPartition = NULL;

		metadata_partition = FindPreferredMetadataPartition(partitions, &headerPartition, &footerPartition);
		if (!metadata_partition)
			throw BMXException("No MXF suitable MXF metadata found");

		progress_callback(0.3f, INFO, "EmbedEBUCoreMetadata", "Reading and parsing MXF metadata");

		mxfKey key;
		uint8_t llen;
		uint64_t len;

		mFile->seek(metadata_partition->getThisPartition(), SEEK_SET);
		mFile->readKL(&key, &llen, &len);
		mFile->skip(len);
		mFile->readNextNonFillerKL(&key, &llen, &len);
		BMX_CHECK(mxf_is_header_metadata(&key));
		uint64_t pos_start_metadata =  mFile->tell() - mxfKey_extlen - llen;

		uint64_t metadata_original_len_with_fill = metadata_partition->getHeaderByteCount();

		// ///////////////////////////////////////
		// / 3. Create a Serializer for our dark metadata
		// ///////////

		std::auto_ptr<MXFFileDarkSerializer> ser( (metadataDocument != NULL) ? 
			static_cast<MXFFileDarkSerializer*>(new DarkDOMDocumentSerializer(*metadataDocument)) : 
			static_cast<MXFFileDarkSerializer*>(new DarkFileSerializer(metadataLocation)) );

		// ///////////////////////////////////////
		// / 2. In order to avoid rewriting large portions of the file, we append our metadata
		// / to that of the footer partition (if already present, and new otherwise)
		// ///////////
		if (!optForceHeader) {

			progress_callback(0.5, INFO, "EmbedEBUCoreMetadata", "Writing new metadata into footer partition");

			// What does the footer partition look like? Are there index entries to move around?
			uint32_t index_length = 0;
			bmx::ByteArray index_bytes(index_length);
			uint64_t pos_write_start_metadata = BufferIndex(&*mFile, footerPartition, index_bytes, &index_length);

			uint64_t headerMetadataSize = WriteDarkMetadataToFile(&*mFile, *ser, &keyEBUCoreDarkMetadata, pos_start_metadata, pos_write_start_metadata, false, footerPartition, metadata_partition);

			if (index_length > 0) {
				progress_callback(0.75f, DEBUG, "EmbedEBUCoreMetadata", "Rewritng footer partition index entries");

				// write the index tables back to the footer partition
				mFile->write(index_bytes.GetBytes(), index_bytes.GetSize());
			}

			progress_callback(0.8f, INFO, "EmbedEBUCoreMetadata", "Rewriting file Random Index Pack");

			mFile->writeRIP();

			progress_callback(0.9f, INFO, "EmbedEBUCoreMetadata", "Updating partition packs");

			// seek backwards and update footer partition pack
			footerPartition->setHeaderByteCount(/*footerPartition->getHeaderByteCount() + */ headerMetadataSize); // Add dark metadata elements to file
			mFile->seek(footerPartition->getThisPartition(), SEEK_SET);
			footerPartition->write(&*mFile);

			// ///////////////////////////////////////
			// / 3. In case of in-place updates: properly update partition packs...
			/*		Header partition:
						Open -> Open (If the metadata in the header was open, leave open, there's more to come in the footer)
						Closed -> Open (Open closed metadata, the header metadata may no longer be used)
					Body partition:
						No metadata: Leave as is, there's no metadata to be found anyway
						Open -> Open (Leave as is, more to come later)
						Closed -> Open (Indicate that this is no longer a verbatim repitition of the header metadata)
					Footer partition:
						-> Open (if all other partitions were open, we append our EBU Core metadata and leave the partition/file open)
						-> Closed (in other cases, this will contain the finalized (with EBU Core) metadata)
						No metadata: Use metadata from the header partition as final and insert in this partition
			*/
			// ///////////
			for (size_t i = 0 ; i < partitions.size()-1; i++) {	// rewrite for all but the footer partition
				Partition *p = partitions[i];
				if (mxf_is_header_partition_pack(p->getKey())) {
					p->setKey( mxf_partition_is_complete(p->getKey()) ? &MXF_PP_K(OpenComplete, Header) : &MXF_PP_K(OpenIncomplete, Header) );
				}
				else if (mxf_is_body_partition_pack(p->getKey())) {
					p->setKey( mxf_partition_is_complete(p->getKey()) ? &MXF_PP_K(OpenComplete, Body) : &MXF_PP_K(OpenIncomplete, Body) );
				} 
				mFile->seek(p->getThisPartition(), SEEK_SET);
				p->write(&*mFile);
			}

		} else {
			// ///////////////////////////////////////
			// / 2a. Provide an override where the file is rewritten to accomodate updated metadata in the header partition?
			// / (This could become necessary when generated MXF files need 
			// / to be natively supported by playout/hardware-constrained machines)
			// ///////////
			progress_callback(0.5, INFO, "EmbedEBUCoreMetadata", "Forcing new metadata into header partition, shifting bytes where necessary");

			uint64_t oriMetadataSize = headerPartition->getHeaderByteCount();

			// Write metadata to the header partition, forcing a file bytes shift if required (likely)
			uint64_t headerMetadataSize = WriteDarkMetadataToFile(&*mFile, *ser, &keyEBUCoreDarkMetadata, pos_start_metadata, pos_start_metadata, true, headerPartition, metadata_partition);

			uint64_t fileOffset = headerMetadataSize - oriMetadataSize;

			progress_callback(0.8f, INFO, "EmbedEBUCoreMetadata", "Shifted file bytes after header partition by %" PRId64 " bytes", fileOffset);

			progress_callback(0.81f, INFO, "EmbedEBUCoreMetadata", "Updating partition pack offsets");
			
			// In this case, there's no further need for shifting the index bytes (been done already)
			// What we do have to do is update each of the partition packs with an updated offset
			uint64_t prevPartition = 0;
			for (size_t i = 0 ; i < partitions.size(); i++) {
				Partition *p = partitions[i];
				if (!mxf_is_header_partition_pack(p->getKey())) {
					p->setThisPartition(p->getThisPartition() + fileOffset);
					p->setPreviousPartition(prevPartition);
				} else if (mxf_is_header_partition_pack(p->getKey())) {
					// make sure this is updated also
					p->setHeaderByteCount(headerMetadataSize);
				}
				p->setFooterPartition(p->getFooterPartition() + fileOffset);
				mFile->seek(p->getThisPartition(), SEEK_SET);
				p->write(&*mFile);
				prevPartition = p->getThisPartition();
			}

			// Finish by re-writing the rip.
			// To be safe, we will overwrite the entire RIP of the previous file, 
			// by extending the filler if present, or by adding a new filler up until the next KAG.

			progress_callback(0.9f, INFO, "EmbedEBUCoreMetadata", "Rewriting file Random Index Pack");

			// find the offset in the footer partition from which the header and index starts
			int64_t eof, partitionSectionOffset;
			int64_t fillerWritePosition = FindLastPartitionFill(&*mFile, footerPartition, &partitionSectionOffset, &eof);

			// write the filler to the next KAG after the end of the file
			mFile->seek(fillerWritePosition, SEEK_SET);
			footerPartition->allocateSpaceToKag(&*mFile, eof - fillerWritePosition);

			if (footerPartition->getIndexByteCount() > 0)
				footerPartition->setIndexByteCount(mFile->tell() - partitionSectionOffset);
			else if (footerPartition->getHeaderByteCount() > 0)
				footerPartition->setHeaderByteCount(mFile->tell() - partitionSectionOffset);

			mFile->writeRIP();

			mFile->seek(footerPartition->getThisPartition(), SEEK_SET);
			footerPartition->write(&*mFile);
		}

        // clean-up through auto_ptr destruction
}


void EmbedEBUCoreMetadata(	const char* metadataLocation, 
							const char* mxfLocation, 
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
							MetadataKind optWaytoWrite,
							bool optNoIdentification, bool optForceHeader) {

	progress_callback(0.0f, INFO, "EmbedEBUCoreMetadata", "Writing EBUCore metadata to MXF file %s, in %s mode...", mxfLocation, 
		optWaytoWrite == KLV_ENCODED ? "KLV-encoded" : (optWaytoWrite == SIDECAR ? "side-car" : "dark metadata" ) );
	progress_callback(0.1f, INFO, "EmbedEBUCoreMetadata", "Reading EBUCore XML document from file %s", metadataLocation);

	std::ifstream input(metadataLocation);
	std::auto_ptr<ebuCoreMainType> ebuCoreMainElementPtr (ebuCoreMain (input, xml_schema::flags::dont_validate | xml_schema::flags::keep_dom));
	input.close();

	switch (optWaytoWrite) {
	case KLV_ENCODED:
		EmbedEBUCoreMetadata(ebuCoreMainElementPtr, metadataLocation, mxfLocation, progress_callback, false, optNoIdentification, optForceHeader);	
		break;
	case DARK:
		EmbedDarkEBUCoreMetadata(NULL, metadataLocation, mxfLocation, progress_callback, optNoIdentification, optForceHeader);
		break;
	case SIDECAR:
		EmbedEBUCoreMetadata(ebuCoreMainElementPtr, metadataLocation, mxfLocation, progress_callback, true, optNoIdentification, optForceHeader);
		break;
	}
}

void EmbedEBUCoreMetadata(	xercesc::DOMDocument& metadataDocument, 
							const char* metadataLocation,
							const char* mxfLocation, 
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
							MetadataKind optWaytoWrite,
							bool optNoIdentification, bool optForceHeader) {

	progress_callback(0.0f, INFO, "EmbedEBUCoreMetadata", "Writing EBUCore metadata to MXF file %s, in %s mode...", mxfLocation, 
		optWaytoWrite == KLV_ENCODED ? "KLV-encoded" : (optWaytoWrite == SIDECAR ? "side-car" : "dark metadata" ) );
	progress_callback(0.1f, INFO, "EmbedEBUCoreMetadata", "Reading EBUCore XML document from DOMDocument input");

	std::auto_ptr<ebuCoreMainType> ebuCoreMainElementPtr (ebuCoreMain (metadataDocument, xml_schema::flags::dont_validate | xml_schema::flags::keep_dom));
	switch (optWaytoWrite) {
	case KLV_ENCODED:
		EmbedEBUCoreMetadata(ebuCoreMainElementPtr, metadataLocation, mxfLocation, progress_callback, false, optNoIdentification, optForceHeader);
		break;
	case DARK:
		EmbedDarkEBUCoreMetadata(&metadataDocument, metadataLocation, mxfLocation, progress_callback, optNoIdentification, optForceHeader);
		break;
	case SIDECAR:
		EmbedEBUCoreMetadata(ebuCoreMainElementPtr, metadataLocation, mxfLocation, progress_callback, true, optNoIdentification, optForceHeader);
		break;
	}
}

void RegisterFrameworkObjectFactoriesforEBUCore(mxfpp::HeaderMetadata *metadata) {
	EBUCore::RegisterFrameworkObjectFactory(metadata);
}

void InsertEBUCoreFramework(HeaderMetadata *header_metadata, DMFramework *framework, Identification *identificationToAppend) {

	BMX_ASSERT(header_metadata != NULL);

	// Append the EBU Core DMS label to the Preface
	AppendDMSLabel(header_metadata, MXF_DM_L(EBUCoreDescriptiveScheme));

	GenerationUIDAppender *appender = NULL;
	if (identificationToAppend != NULL) {
		appender = new GenerationUIDAppender(identificationToAppend->getThisGenerationUID());
	}

    InsertFramework(header_metadata, 10001, "EBU_Core", framework, appender);

	if (appender!=NULL)
		delete appender;
}

void InsertEBUCoreEventFrameworks(HeaderMetadata *header_metadata, std::vector<EventInput>& eventFrameworks, Identification *identificationToAppend) {

	BMX_ASSERT(header_metadata != NULL);

	// Don't append the EBU Core DMS label to the Preface, as we assume the main framework has already been planted
	// AppendDMSLabel(header_metadata, MXF_DM_L(EBUCoreDescriptiveScheme));

	GenerationUIDAppender *appender = NULL;
	if (identificationToAppend != NULL) {
		appender = new GenerationUIDAppender(identificationToAppend->getThisGenerationUID());
	}

	InsertEventFrameworks(header_metadata, 10002, "EBU_Core_Parts", eventFrameworks, appender);

	if (appender!=NULL)
		delete appender;
}

void RemoveEBUCoreFrameworks(mxfpp::HeaderMetadata *header_metadata) {
	BMX_ASSERT(header_metadata);

    MaterialPackage *material_package = header_metadata->getPreface()->findMaterialPackage();
    BMX_ASSERT(material_package);

	std::vector<GenericTrack*> trks = material_package->getTracks();
	std::vector<GenericTrack*>::iterator it = trks.begin();
	while(it != trks.end()) {
		if (dynamic_cast<StaticTrack*>(*it) != NULL || dynamic_cast<EventTrack*>(*it) != NULL) {
			if ((*it)->getTrackName().compare("EBU_Core") == 0 || (*it)->getTrackName().compare("EBU_Core_Parts") == 0) {
				// this is an EBU track, remove it, first from the low-level metadata, then from the material package object
			    mxf_remove_set(header_metadata->getCHeaderMetadata(), (*it)->getCMetadataSet());
				it = trks.erase(it);
			} else it++;
		} else it++;
	}

	// reassign the new tracks list to the package
	material_package->setTracks(trks);
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

std::auto_ptr<ebuCoreMainType> ParseEBUCoreMetadata(ebucoreMainFramework *fw) {
	// assert that a coremetadata element is present!

	std::auto_ptr<ebuCoreMainType::coreMetadata_type> main( new ebuCoreMainType::coreMetadata_type() );
	mapCoreMetadata(fw->getcoreMetadata(), *main);

	// map the EBU Core KLV framework to the XSD-derived counterpart
	std::auto_ptr<ebuCoreMainType> ebuCoreMainElement( new ebuCoreMainType(main) );

	if (fw->havemetadataSchemeInformation()) {
		ebucoreMetadataSchemeInformation *info = fw->getmetadataSchemeInformation();
		if (info->haveebucoreMetadataProvider()) {
			std::auto_ptr<entityType> p( new entityType() );
			mapEntity(info->getebucoreMetadataProvider(), *(p.get()));
			ebuCoreMainElement->metadataProvider(p);
		}
	}
	
	return ebuCoreMainElement;
}

ebucoreMainFramework* FindEBUCoreMetadataFramework(HeaderMetadata *metadata) {

	MaterialPackage *mp = metadata->getPreface()->findMaterialPackage();
	if (!mp) {
		// throw an exception!
		return NULL;
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

	return ebucore;
}

std::auto_ptr<ebuCoreMainType> FindAndSerializeEBUCore(HeaderMetadata *metadata) {
	
	ebucoreMainFramework *fw = FindEBUCoreMetadataFramework(metadata);

	if (fw==NULL) {
		// throw an exception!
		return std::auto_ptr<ebuCoreMainType>(NULL);
	}
	
	return fw->havecoreMetadata() ? 
		ParseEBUCoreMetadata(fw) : 
		std::auto_ptr<ebuCoreMainType>(NULL);
}



void FindAndSerializeEBUCore(HeaderMetadata *metadata, const char* outputfilename) {
	
		std::auto_ptr<ebuCoreMainType> ebuCoreMainElement( FindAndSerializeEBUCore(metadata) );
	
		xml_schema::namespace_infomap map;
		map[""].name = "urn:ebu:metadata-schema:ebuCore_2012";
		map["dc"].name = "http://purl.org/dc/elements/1.1/";

		// open a file output stream
		std::ofstream out(outputfilename);
		ebuCoreMain (out, *ebuCoreMainElement, map);
		out.close();
}

enum MetadataOutput {
	SERIALIZE_TO_FILE,
	OUTPUT_AS_DOM_DOCUMENT
};

void ExtractEBUCoreMetadata(
							const char* mxfLocation,
							const char* metadataLocation,
							xercesc::DOMDocument** outputDocument,
							MetadataOutput outputFashion,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...)) {
	
	XMLPlatformUtils::Initialize();

	progress_callback(0.2f, INFO, "ExtractEBUCoreMetadata", "Opening MXF file %s", mxfLocation);

	std::auto_ptr<File> mFile( File::openRead(mxfLocation) );	// throws MXFException if open failed!

	std::auto_ptr<DataModel> mDataModel ( new DataModel() );
	EBUCore::RegisterMetadataExtensionsforEBUCore(&*mDataModel);

	// ///////////////////////////////////////
	// / 1. Open MXF File and locate all partitions, using the RIP
	// ///////////

	if (!mFile->readPartitions())
		throw BMXException("Failed to read all partitions. File may be incomplete or invalid");

	const std::vector<Partition*> &partitions = mFile->getPartitions();

	// ///////////////////////////////////////
	// / 1a. Locate the Metadata to use for extension
	/*		We prefer closed footer metadata when available (if the metadata 
			is repeated in the footer, it is likely to be more up-to-date than
			that in the header.																*/
	// ///////////
	progress_callback(0.25f, INFO, "ExtractEBUCoreMetadata", "Locating preferred MXF metadata");

	Partition *metadata_partition = NULL, *headerPartition = NULL, *footerPartition = NULL;

	metadata_partition = FindPreferredMetadataPartition(partitions, &headerPartition, &footerPartition);
	if (!metadata_partition)
		throw BMXException("No MXF suitable MXF metadata found");

	progress_callback(0.5f, INFO, "ExtractEBUCoreMetadata", "Reading and parsing MXF metadata");

	std::auto_ptr<HeaderMetadata> mHeaderMetadata ( new HeaderMetadata(&*mDataModel) );

	mxfKey key; uint8_t llen; uint64_t len;
	mFile->seek(metadata_partition->getThisPartition(), SEEK_SET);
	mFile->readKL(&key, &llen, &len);
	mFile->skip(len);
	mFile->readNextNonFillerKL(&key, &llen, &len);
	BMX_CHECK(mxf_is_header_metadata(&key));
	mHeaderMetadata->read(&*mFile, metadata_partition, &key, llen, len);

	// ///////////////////////////////////////
	// / 2a. Locate the KLV-coded EBUCore metadata in the MXF header metadata and serialize it to 
	// ///////////
	progress_callback(0.6f, INFO, "ExtractEBUCoreMetadata", "Locating and extracting EBUCore KLV metadata");

	EBUCore::RegisterFrameworkObjectFactoriesforEBUCore(&*mHeaderMetadata);

	std::auto_ptr<ebuCoreMainType> p;
	ebucoreMainFramework *fw = FindEBUCoreMetadataFramework(&*mHeaderMetadata);

	if (fw != NULL) {
		progress_callback(0.61f, INFO, "ExtractEBUCoreMetadata", "Found an ebucoreMainFramework on the MXF timeline");

		if (fw->havecoreMetadata()) {
			// there is a CoreMetadata object, enough to parse the KLV-encoded metadata
			p = ParseEBUCoreMetadata(fw);
		} else {
			progress_callback(0.62f, INFO, "ExtractEBUCoreMetadata", "No coreMetadata set is attached to the ebucoreMainFramework, attempting to locate a side-car metadata reference...");
		
			// ///////////////////////////////////////
			// / 2b. If there is no KLV-codec metadata beyond the framework, there could be a reference to a sidecar XML file
			// ///////////
			if (fw->havedocumentLocator()) {
				const std::string& loc = fw->getdocumentLocator();

				progress_callback(0.65f, INFO, "ExtractEBUCoreMetadata", "A side-car metadata reference (documentLocator) was found: %s", loc.c_str());

				//if (loc.size() > 0) {
					if (outputFashion == SERIALIZE_TO_FILE) {
						progress_callback(0.9f, INFO, "ExtractEBUCoreMetadata", "Writing side-car EBUCore metadata to XML file at %s\n", metadataLocation);

						std::ofstream out(metadataLocation, std::ofstream::out | std::ofstream::binary);
						std::ifstream in(loc.c_str(), std::ifstream::in | std::ifstream::binary);
						in >> std::noskipws;
						std::copy(std::istream_iterator<unsigned char>(in), std::istream_iterator<unsigned char>(), std::ostream_iterator<unsigned char>(out));

						in.close();
						out.close();
					} 
					else if (outputFashion == OUTPUT_AS_DOM_DOCUMENT) {
						progress_callback(0.9f, INFO, "ExtractEBUCoreMetadata", "Writing side-car EBUCore metadata to output Xerces-C DOM Document");
					
						xercesc::TranscodeFromStr location((const unsigned char*)loc.c_str(), loc.size(), "UTF-8");
						*outputDocument = ParseXercesDocument(location.str());
					}
				//}
				//else {
				//	// location too short!
				//}
			} else {
				// this is wrong, as there is no coremetadata, and no reference to a sidecar file!
			}
		}

		if (p.get() != NULL) {

			progress_callback(0.7f, INFO, "ExtractEBUCoreMetadata", "A coreMetadata set was attached to the ebucoreMainFramework, and was processed successfully");

			xml_schema::namespace_infomap map;
			map[""].name = "urn:ebu:metadata-schema:ebuCore_2012";
			map["dc"].name = "http://purl.org/dc/elements/1.1/";

			if (outputFashion == SERIALIZE_TO_FILE) {
				progress_callback(0.9f, INFO, "ExtractEBUCoreMetadata", "Writing EBUCore metadata to XML file at %s\n", metadataLocation);

				// open a file output stream
				std::ofstream out(metadataLocation);
				ebuCoreMain (out, *p, map);
				out.close();
			} 
			else if (outputFashion == OUTPUT_AS_DOM_DOCUMENT) {
				progress_callback(0.9f, INFO, "ExtractEBUCoreMetadata", "Writing EBUCore metadata to output Xerces-C DOM Document");
		
				::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > xml = ebuCoreMain(*p, map);
				// pass the DOM document to output
				*outputDocument = xml.get();
				xml.release();
			}

		} 
	}
	else {
		// ///////////////////////////////////////
		// / 2c. If there is no KLV-codec metadata, there could be embedded dark metadata,
		// /     find its key in the metadata
		// ///////////
		bool darkFound = false;
		progress_callback(0.61f, INFO, "ExtractEBUCoreMetadata", "No ebucoreMainFramework found on the MXF timeline, looking for dark metadata...");

		mFile->seek(metadata_partition->getThisPartition(), SEEK_SET);
		uint64_t count = 0, sourceHeaderByteCount = metadata_partition->getHeaderByteCount();
		while (count < sourceHeaderByteCount)
		{
			mFile->readKL(&key, &llen, &len);
			if (mxf_equals_key(&key, &keyEBUCoreDarkMetadata)) {
				darkFound = true;
				progress_callback(0.61f, INFO, "ExtractEBUCoreMetadata", "Located EBUCore dark metadata set at offset %" PRId64 "...", metadata_partition->getThisPartition() + count);

				// there is dark metadata, get it out
				if (outputFashion == SERIALIZE_TO_FILE) {
					progress_callback(0.9f, INFO, "ExtractEBUCoreMetadata", "Writing dark EBUCore metadata to XML file at %s", metadataLocation);

					WriteKLVContentsToFile(metadataLocation, &*mFile, len);
				} 
				else if (outputFashion == OUTPUT_AS_DOM_DOCUMENT) {
					progress_callback(0.9f, INFO, "ExtractEBUCoreMetadata", "Writing dark EBUCore metadata to output Xerces-C DOM Document");
					
					KLVInputSource inp(&*mFile, len);
					*outputDocument = ParseXercesDocument(inp);
				}
				// only do this once!
				break;
			} else {
				mFile->skip(len);
			}
			count += mxfKey_extlen + llen + len;
		}

		if (!darkFound)
			progress_callback(0.99f, INFO, "ExtractEBUCoreMetadata", "No dark metadata set found");
	}

	// ///////////////////////////////////////
	// / 3. We're done, close the MXF file.
	// ///////////
	// mxf file is closed through auto_ptr
}

xercesc::DOMDocument& ExtractEBUCoreMetadata(
							const char* mxfLocation,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...)) {

	xercesc::DOMDocument *doc;
	ExtractEBUCoreMetadata(mxfLocation, NULL, &doc, OUTPUT_AS_DOM_DOCUMENT, progress_callback);
	return *doc;

}
	
void ExtractEBUCoreMetadata(const char* mxfLocation,
							const char* metadataLocation,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...)) {

	ExtractEBUCoreMetadata(mxfLocation, metadataLocation, NULL, SERIALIZE_TO_FILE, progress_callback);

}

} // namespace EBUCore
} //namespace EBUSDK
