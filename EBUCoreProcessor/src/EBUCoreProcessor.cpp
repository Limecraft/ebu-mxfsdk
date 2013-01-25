
#define __STDC_FORMAT_MACROS
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iterator>
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

#include <EBUCore_1_4/EBUCoreProcessor_1_4.h>
#include <EBUCore_1_4/metadata/EBUCoreDMS++.h>
#include <MXFCustomMetadata.h>
#include <EBUCoreProcessor.h>
#include <XercesUtils.h>

#include <xercesc/util/TransService.hpp>

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

EBUCoreProcessor* GetEBUCoreProcessor(const std::vector<mxfUL>& descriptiveMetadataSchemes) {
	EBUCoreProcessor *processor = NULL;
	// loop through the vector and find the first matching scheme
	for (std::vector<mxfUL>::const_iterator it=descriptiveMetadataSchemes.begin(); it!=descriptiveMetadataSchemes.end();it++) {
		if (mxf_equals_ul(&*it, &EBUCore_1_4::EBUCoreProcessor::DMScheme)) {
			processor = new EBUCore_1_4::EBUCoreProcessor();
		}
		if (processor != NULL) break;
	}
	return processor;
}

EBUCoreProcessor* GetDefaultEBUCoreProcessor() {
	return new EBUCore_1_4::EBUCoreProcessor();
}

/*void RegisterMetadataExtensionsforEBUCore(mxfpp::DataModel *data_model)
{
	// register the extensions for EBUCore version 1.5
	EBUSDK::EBUCore::EBUCore_1_4::RegisterMetadataExtensionsforEBUCore(data_model);	
}*/

MetadataKind ExtractEBUCoreMetadata(
							EBUCoreProcessor *processor,
							HeaderMetadata *headerMetadata,
							Partition *partition,
							File *mxfFile,
							const char* metadataLocation,
							xercesc::DOMDocument** outputDocument,
							MetadataOutput outputFashion,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...));

void InnerEmbedEBUCoreMetadata(	
							xercesc::DOMDocument* metadataDocument, 
							const char* metadataLocation,
							const char* mxfLocation,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
							MetadataKind optWaytoWrite,
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

		std::auto_ptr<DataModel> mDataModel ( new DataModel() );
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
	    // / 1b. Locate any existing EBUCore DMScheme declarations, 
		/*		 this determine the version of EBUCoreProcessor to use	 */
		// ///////////
		EBUCoreProcessor* processor = GetEBUCoreProcessor(mHeaderMetadata->getPreface()->getDMSchemes());
		if (processor != NULL) {
			// we have a processor, which means that a DM Scheme for EBUCore was present,
			// we should now reload the header metadata with this in mind!
			processor->RegisterMetadataExtensions(&*mDataModel);
			
			// reset
			mHeaderMetadata = std::auto_ptr<HeaderMetadata>(new HeaderMetadata(&*mDataModel));
			processor->RegisterFrameworkObjectFactories(&*mHeaderMetadata);

			mFile->seek(metadata_partition->getThisPartition(), SEEK_SET);
			mFile->readKL(&key, &llen, &len);
			mFile->skip(len);
			mFile->readNextNonFillerKL(&key, &llen, &len);
			mHeaderMetadata->read(&*mFile, metadata_partition, &key, llen, len);
		}

		// ///////////////////////////////////////
	    // / 1c. Locate any existing EBUCore metadata in the header metadata partition.
		/*		 If existing metadata is found, the new metadata is serialized 
				in the same fashion, overwriting what was present before */
		// ///////////
		MetadataKind existingKind = ExtractEBUCoreMetadata(processor, &*mHeaderMetadata, metadata_partition, &*mFile, NULL, NULL, DONT_SERIALIZE, progress_callback);
		if (existingKind != NONE) {
			// there is metadata, override the way in which we are writing metadata!
			if (optWaytoWrite != existingKind) {
				progress_callback(0.0f, INFO, "EmbedEBUCoreMetadata", "Due to existing metadata, overriding metadata serializetion mode to %s", 
					existingKind == KLV_ENCODED ? "KLV-encoded" : (existingKind == SIDECAR ? "side-car" : "dark metadata" ) );
			}

			optWaytoWrite = existingKind;
		} else {
			// there is no current metadata, allocate a default processor for it
			processor = GetDefaultEBUCoreProcessor();

			processor->RegisterMetadataExtensions(&*mDataModel);
			//processor->RegisterFrameworkObjectFactoriesforEBUCore(&*mHeaderMetadata);
		}

		// ///////////////////////////////////////
		// / 2. Insert the EBU Core metadata into the header metadata
		// ///////////
		progress_callback(0.4f, INFO, "EmbedEBUCoreMetadata", "Embedding EBUCore metadata in MXF metadata");

		// prepare a vector of dark metadata keys that is to be ignored (i.e., discarded) 
		// when metadata is (re)written to the file
		std::vector<const mxfKey*> ignoredDarkKeys;

		// prepare a pointer to the serializer of dark metadata
		std::auto_ptr<MXFFileDarkSerializer> ser(NULL);


		if (optWaytoWrite != DARK && optWaytoWrite != NONE) {
			// ///////////////////////////////////////
			// / 3. Do a KLV-encoded serialization of (part of) the metadata.
			// ///////////

			Identification* id = optNoIdentification ? NULL : EBUCore::GenerateEBUCoreIdentificationSet(&*mHeaderMetadata);
			// choose between sidecar serialization or fully fledged KLV-encoded metadata

			// process the EBUCore metadata
			std::vector<EventInput> eventFrameworks;
			DMFramework *framework = NULL;
			if (optWaytoWrite == SIDECAR) {
				framework = processor->GenerateSideCarFramework(metadataLocation, &*mHeaderMetadata, id);
			} else {
				framework = processor->Process(metadataDocument, metadataLocation, &*mHeaderMetadata, eventFrameworks, id); 
			}

			// remove any previously present EBUCore metadata
			RemoveEBUCoreFrameworks(&*mHeaderMetadata);

			// insert the static track DM framework
			EBUCore::InsertEBUCoreFramework(&*mHeaderMetadata, processor->GetDescriptiveMetadataScheme(), framework, id);
			// insert the event track DM frameworks on the timeline, if any
			if (eventFrameworks.size() > 0) {
				EBUCore::InsertEBUCoreEventFrameworks(&*mHeaderMetadata, eventFrameworks, id);
			}

			ignoredDarkKeys.push_back(&keyEBUCoreDarkMetadata);

		} else {
			// ///////////////////////////////////////
			// / 3. Create a Serializer for our dark metadata
			// ///////////
			ser.reset( (metadataDocument != NULL) ? 
				static_cast<MXFFileDarkSerializer*>(new DarkDOMDocumentSerializer(*metadataDocument)) : 
				static_cast<MXFFileDarkSerializer*>(new DarkFileSerializer(metadataLocation)) 
			);
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

			uint64_t headerMetadataSize = (optWaytoWrite == DARK) ?
				WriteDarkMetadataToFile(	&*mFile, 
											*ser, 
											&keyEBUCoreDarkMetadata, 
											pos_start_metadata, pos_write_start_metadata, false, footerPartition, metadata_partition) :
				WriteMetadataToFile(		&*mFile, 
											&*mHeaderMetadata, 
											pos_start_metadata, pos_write_start_metadata, false, footerPartition, metadata_partition, 
											ignoredDarkKeys);

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
			uint64_t headerMetadataSize = (optWaytoWrite == DARK) ?
				WriteDarkMetadataToFile(	&*mFile, 
											*ser, 
											&keyEBUCoreDarkMetadata, 
											pos_start_metadata, pos_start_metadata, true, headerPartition, metadata_partition) :
				WriteMetadataToFile(		&*mFile, 
											&*mHeaderMetadata, 
											pos_start_metadata, pos_start_metadata, true, headerPartition, metadata_partition, 
											ignoredDarkKeys);

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

	InnerEmbedEBUCoreMetadata(NULL, metadataLocation, mxfLocation, progress_callback, optWaytoWrite, optNoIdentification, optForceHeader);	

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

	InnerEmbedEBUCoreMetadata(&metadataDocument, metadataLocation, mxfLocation, progress_callback, optWaytoWrite, optNoIdentification, optForceHeader);

}

void RegisterFrameworkObjectFactoriesforEBUCore(mxfpp::HeaderMetadata *metadata) {
	EBUCore::EBUCore_1_4::RegisterFrameworkObjectFactory(metadata);
}

void InsertEBUCoreFramework(HeaderMetadata *header_metadata, const mxfUL *dmSchemeLabel, DMFramework *framework, Identification *identificationToAppend) {

	BMX_ASSERT(header_metadata != NULL);

	// Append the EBU Core DMS label to the Preface
	AppendDMSLabel(header_metadata, *dmSchemeLabel);

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
				// this is an EBU track, remove it, first from the low-level metadata, then from the material package object by updating the reference vector
				RemoveMetadataSetTree(header_metadata, *it);
				it = trks.erase(it);
			} else it++;
		} else it++;
	}

	// reassign the new tracks list to the package
	material_package->setTracks(trks);
}

MetadataKind ExtractEBUCoreMetadata(
							EBUCoreProcessor *processor,
							HeaderMetadata *headerMetadata,
							Partition *partition,
							File *mxfFile,
							const char* metadataLocation,
							xercesc::DOMDocument** outputDocument,
							MetadataOutput outputFashion,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...)) {


	// ///////////////////////////////////////
	// / 2a. Locate the KLV-coded EBUCore metadata in the MXF header metadata and serialize it to 
	// ///////////
	progress_callback(0.6f, INFO, "ExtractEBUCoreMetadata", "Locating existing EBUCore KLV metadata");

	//std::auto_ptr<ebuCoreMainType> p;
	DMFramework *fw = (processor == NULL) ? NULL : processor->FindMetadataFramework(&*headerMetadata);

	if (fw != NULL) {
		progress_callback(0.61f, INFO, "ExtractEBUCoreMetadata", "Found an ebucoreMainFramework on the MXF timeline");

		if (processor->FrameworkHasActualMetadata(fw)) {
			// there is a CoreMetadata object, enough to parse the KLV-encoded metadata
			processor->ParseAndSerializeMetadata(fw, outputFashion, metadataLocation, outputDocument, progress_callback);
			return KLV_ENCODED;
		} else {
			progress_callback(0.62f, INFO, "ExtractEBUCoreMetadata", "No coreMetadata set is attached to the ebucoreMainFramework, attempting to locate a side-car metadata reference...");
		
			// ///////////////////////////////////////
			// / 2b. If there is no KLV-codec metadata beyond the framework, there could be a reference to a sidecar XML file
			// ///////////
			if (processor->FrameworkRefersToExternalMetadata(fw)) {
				const std::string& loc = processor->GetFrameworkExternalMetadataLocation(fw);

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

					return SIDECAR;
				//}
				//else {
				//	// location too short!
				//}
			} else {
				// this is wrong, as there is no coremetadata, and no reference to a sidecar file!
				return NONE;
			}
		}

		
	}
	else {
		// ///////////////////////////////////////
		// / 2c. If there is no KLV-codec metadata, there could be embedded dark metadata,
		// /     find its key in the metadata
		// ///////////
		mxfKey key; uint8_t llen; uint64_t len;

		bool darkFound = false;
		progress_callback(0.61f, INFO, "ExtractEBUCoreMetadata", "No ebucoreMainFramework found on the MXF timeline, looking for dark metadata...");

		mxfFile->seek(partition->getThisPartition(), SEEK_SET);
		uint64_t count = 0, sourceHeaderByteCount = partition->getHeaderByteCount();
		while (count < sourceHeaderByteCount)
		{
			mxfFile->readKL(&key, &llen, &len);
			if (mxf_equals_key(&key, &keyEBUCoreDarkMetadata)) {
				darkFound = true;
				progress_callback(0.61f, INFO, "ExtractEBUCoreMetadata", "Located EBUCore dark metadata set at offset %" PRId64 "...", partition->getThisPartition() + count);

				// there is dark metadata, get it out
				if (outputFashion == SERIALIZE_TO_FILE) {
					progress_callback(0.9f, INFO, "ExtractEBUCoreMetadata", "Writing dark EBUCore metadata to XML file at %s", metadataLocation);

					WriteKLVContentsToFile(metadataLocation, mxfFile, len);
				} 
				else if (outputFashion == OUTPUT_AS_DOM_DOCUMENT) {
					progress_callback(0.9f, INFO, "ExtractEBUCoreMetadata", "Writing dark EBUCore metadata to output Xerces-C DOM Document");
					
					KLVInputSource inp(mxfFile, len);
					*outputDocument = ParseXercesDocument(inp);
				}
				// only do this once!
				return DARK;
			} else {
				mxfFile->skip(len);
			}
			count += mxfKey_extlen + llen + len;
		}

		if (!darkFound)
			progress_callback(0.99f, INFO, "ExtractEBUCoreMetadata", "No dark metadata set found");

		return NONE;
	}

}

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
	// / 1b. Locate any existing EBUCore DMScheme declarations, 
	/*		 this determine the version of EBUCoreProcessor to use	 */
	// ///////////
	EBUCoreProcessor* processor = GetEBUCoreProcessor(mHeaderMetadata->getPreface()->getDMSchemes());
	if (processor != NULL) {
		// we have a processor, which means that a DM Scheme for EBUCore was present,
		// we should now reload the header metadata with this in mind!
		processor->RegisterMetadataExtensions(&*mDataModel);
			
		// reset
		mHeaderMetadata = std::auto_ptr<HeaderMetadata>(new HeaderMetadata(&*mDataModel));
		processor->RegisterFrameworkObjectFactories(&*mHeaderMetadata);

		mFile->seek(metadata_partition->getThisPartition(), SEEK_SET);
		mFile->readKL(&key, &llen, &len);
		mFile->skip(len);
		mFile->readNextNonFillerKL(&key, &llen, &len);
		mHeaderMetadata->read(&*mFile, metadata_partition, &key, llen, len);
	}

	ExtractEBUCoreMetadata(processor, &*mHeaderMetadata, metadata_partition, &*mFile, metadataLocation, outputDocument, outputFashion, progress_callback);

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
