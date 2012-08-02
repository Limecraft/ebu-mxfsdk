
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

DMFramework* Process(std::auto_ptr<ebuCoreMainType> metadata, const char* metadataLocation, HeaderMetadata *destination, Identification* identificationToAppend) {

	// Generate a new Generation UID if necessary, and provide to each mapping function
	GenerationUIDAppender *appender = NULL;
	if (identificationToAppend != NULL) {
		appender = new GenerationUIDAppender(identificationToAppend->getThisGenerationUID());
	}
	ebucoreMainFramework *framework = new ebucoreMainFramework(destination);
	appender->Modify(framework);
	framework->setdocumentId(metadataLocation);	// use the file location as document id

	ebucoreCoreMetadata *core = new ebucoreCoreMetadata(destination);
	appender->Modify(core);
	if (appender != NULL)
		mapCoreMetadata(metadata->coreMetadata(), core, appender);
	else
		mapCoreMetadata(metadata->coreMetadata(), core);

	ebucoreMetadataSchemeInformation *info = new ebucoreMetadataSchemeInformation(destination);
	appender->Modify(info);
	if (appender != NULL)
		mapMetadataSchemeInformation(*metadata, info, appender);
	else
		mapMetadataSchemeInformation(*metadata, info);

	framework->setcoreMetadata(core);
	framework->setmetadataSchemeInformation(info);

	std::cout << framework->getdocumentId();

	if (appender!=NULL)
		delete appender;

	return framework;
}

DMFramework* Process(const char* location, HeaderMetadata *destination, Identification* identificationToAppend) {
	std::ifstream input(location);
	std::auto_ptr<ebuCoreMainType> ebuCoreMainElementPtr (ebuCoreMain (input, xml_schema::flags::dont_validate | xml_schema::flags::keep_dom));
	return Process(ebuCoreMainElementPtr, location, destination, identificationToAppend);
}

void RegisterMetadataExtensionsforEBUCore(mxfpp::DataModel *data_model)
{
	EBUCore::RegisterExtensions(data_model);	
}

Partition* FindPreferredMetadataPartition(const std::vector<Partition*>& partitions, Partition** headerPartition, Partition** footerPartition) {

	Partition *metadata_partition = NULL, *header = NULL, *footer = NULL;

	size_t i;
	for (i = partitions.size(); i > 0 ; i--) {
		Partition *p = partitions[i-1];
		if (mxf_is_header_partition_pack(p->getKey()))
			header = p;
		else if (mxf_is_footer_partition_pack(p->getKey()))
			footer = p;
	}
	if (		footer!=NULL && 
				mxf_partition_is_closed(footer->getKey()) && 
				footer->getHeaderByteCount() > 0)
		metadata_partition = footer;
	else if (	header != NULL && 
				mxf_partition_is_closed(header->getKey()) &&
				header->getHeaderByteCount() > 0)
		metadata_partition = header;
	else {
		log_warn("No metadata found in any of the closed header and footer partitions.");

		// there is no closed header or footer partition with metadata
		// find closed metadata in any of the body partitions 
		// (header metadata might have gone lost in transit)
		for (i = partitions.size(); i > 0 ; i--) {
			Partition *p = partitions[i-1];
			if (	mxf_is_body_partition_pack(p->getKey()) &&
					mxf_partition_is_closed(p->getKey()) && 
					p->getHeaderByteCount() > 0) {
				metadata_partition = p;
				break;	// use the last partition in the file as metadata, as it should be the most complete...
			}
		}

		// is there still no metadata? Try to find metadata in open partitions
		if (metadata_partition == NULL) {
			log_warn("No metadata found in any of the closed body partitions either.");

			for (i = partitions.size(); i > 0 ; i--) {
				Partition *p = partitions[i-1];
				if (	!mxf_partition_is_closed(p->getKey()) && 
						p->getHeaderByteCount() > 0) {
					metadata_partition = p;
					break;	// use the last partition in the file as metadata, as it should be the most complete...
				}
			}
		}
	}

	if (headerPartition!=NULL)
		*headerPartition = header;
	if (footerPartition!=NULL)
		*footerPartition = footer;
	return metadata_partition;
}

void EmbedEBUCoreMetadata(	std::auto_ptr<ebuCoreMainType> metadata, 
							const char* metadataLocation,
							const char* mxfLocation, 
							void (*progress_callback)(float progress, std::string& message, std::string& function),
							bool optNoIdentification, bool optForceHeader) {

        //MXFReader *reader;
        MXFFileReader *file_reader = 0;

        file_reader = new MXFFileReader();
		EBUCore::RegisterMetadataExtensionsforEBUCore(file_reader->GetDataModel());

		MXFFileReader::OpenResult result;
		MXFFile *mxf_file;
		if (MXF_OPEN_MODIFY(mxfLocation, &mxf_file)) {

			File *mFile = new File(mxf_file);
			DataModel *mDataModel = new DataModel();
			EBUCore::RegisterMetadataExtensionsforEBUCore(mDataModel);

			// ///////////////////////////////////////
		    // / 1. Open MXF File and locate all partitions, using the RIP
			// ///////////

			if (!mFile->readPartitions())
				log_warn("Failed to read all partitions. File may be incomplete or invalid\n");

	        const std::vector<Partition*> &partitions = mFile->getPartitions();

			// ///////////////////////////////////////
	        // / 1a. Locate the Metadata to use for extension
			/*		We prefer closed footer metadata when available (if the metadata 
					is repeated in the footer, it is likely to be more up-to-date than
					that in the header.																*/
		    // ///////////
	        Partition *metadata_partition = NULL, *headerPartition = NULL, *footerPartition = NULL;

			metadata_partition = FindPreferredMetadataPartition(partitions, &headerPartition, &footerPartition);
			if (!metadata_partition)
				THROW_RESULT(MXFFileReader::MXF_RESULT_NO_HEADER_METADATA);

			mxfKey key;
			uint8_t llen;
			uint64_t len;

			HeaderMetadata *mHeaderMetadata = new HeaderMetadata(mDataModel);

			mFile->seek(metadata_partition->getThisPartition(), SEEK_SET);
			mFile->readKL(&key, &llen, &len);
			mFile->skip(len);
			mFile->readNextNonFillerKL(&key, &llen, &len);
			BMX_CHECK(mxf_is_header_metadata(&key));
			uint64_t pos_start_metadata =  mFile->tell() - mxfKey_extlen - llen;
			mHeaderMetadata->read(mFile, metadata_partition, &key, llen, len);

			uint64_t metadata_original_len_with_fill = metadata_partition->getHeaderByteCount();

			// ///////////////////////////////////////
			// / 2. Insert the EBU Core object tree into the header metadata
			// ///////////
			Identification* id = EBUCore::GenerateEBUCoreIdentificationSet(mHeaderMetadata);
			DMFramework *framework = EBUCore::Process(metadata, metadataLocation, mHeaderMetadata, id);
			EBUCore::InsertEBUCoreFramework(mHeaderMetadata, framework, id);

			// ///////////////////////////////////////
			// / 2. In order to avoid rewriting large portions of the file, we append our metadata
			// / to that of the footer partition (if already present, and new otherwise)
			// ///////////
			if (!optForceHeader) {

				// What does the footer partition look like? Are there index entries to move around?
				uint32_t index_length = 0;
				bmx::ByteArray index_bytes(index_length);
				uint64_t pos_write_start_metadata = EBUCore::BufferIndex(mFile, footerPartition, index_bytes, &index_length);

				uint64_t headerMetadataSize = EBUCore::WriteMetadataToFile(mFile, mHeaderMetadata, pos_start_metadata, pos_write_start_metadata, false, footerPartition, metadata_partition);

				if (index_length > 0) {
					// write the index tables back to the footer partition
					mFile->write(index_bytes.GetBytes(), index_bytes.GetSize());
				}

				mFile->writeRIP();

				// seek backwards and update footer partition pack
				footerPartition->setHeaderByteCount(/*footerPartition->getHeaderByteCount() + */ headerMetadataSize); // Add dark metadata elements to file
				mFile->seek(footerPartition->getThisPartition(), SEEK_SET);
				footerPartition->write(mFile);

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
					p->write(mFile);
				}

			} else {
				// ///////////////////////////////////////
				// / 2a. Provide an override where the file is rewritten to accomodate updated metadata in the header partition?
				// / (This could become necessary when generated MXF files need 
				// / to be natively supported by playout/hardware-constrained machines)
				// ///////////

				uint64_t oriMetadataSize = headerPartition->getHeaderByteCount();

				// Write metadata to the header partition, forcing a file bytes shift if required (likely)
				uint64_t headerMetadataSize = EBUCore::WriteMetadataToFile(mFile, mHeaderMetadata, pos_start_metadata, pos_start_metadata, true, headerPartition, metadata_partition);
				
				uint64_t fileOffset = headerMetadataSize - oriMetadataSize;

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
					p->write(mFile);
					prevPartition = p->getThisPartition();
				}

				// Finish by re-writing the rip.
				// To be safe, we will overwrite the entire RIP of the previous file, 
				// by extending the filler if present, or by adding a new filler up until the next KAG.

				// find the offset in the footer partition from which the header and index starts
				int64_t eof, partitionSectionOffset;
				int64_t fillerWritePosition = EBUCore::FindLastPartitionFill(mFile, footerPartition, &partitionSectionOffset, &eof);

				// write the filler to the next KAG after the end of the file
				mFile->seek(fillerWritePosition, SEEK_SET);
				footerPartition->allocateSpaceToKag(mFile, eof - fillerWritePosition);

				if (footerPartition->getIndexByteCount() > 0)
					footerPartition->setIndexByteCount(mFile->tell() - partitionSectionOffset);
				else if (footerPartition->getHeaderByteCount() > 0)
					footerPartition->setHeaderByteCount(mFile->tell() - partitionSectionOffset);

				mFile->writeRIP();

				mFile->seek(footerPartition->getThisPartition(), SEEK_SET);
				footerPartition->write(mFile);
			}
			
			result = MXFFileReader::MXF_RESULT_SUCCESS;
		} else {
			result = MXFFileReader::MXF_RESULT_OPEN_FAIL;
		}
		if (result != MXFFileReader::MXF_RESULT_SUCCESS) {
			log_error("Failed to open MXF file '%s': %s\n", mxfLocation, MXFFileReader::ResultToString(result).c_str());
			delete file_reader;
			throw false;
		}
        //reader = file_reader;

        // clean-up
        delete file_reader;	
}

void EmbedEBUCoreMetadata(	const char* metadataLocation, 
							const char* mxfLocation, 
							void (*progress_callback)(float progress, std::string& message, std::string& function),
							bool optNoIdentification, bool optForceHeader) {
	std::ifstream input(metadataLocation);
	std::auto_ptr<ebuCoreMainType> ebuCoreMainElementPtr (ebuCoreMain (input, xml_schema::flags::dont_validate | xml_schema::flags::keep_dom));
	EmbedEBUCoreMetadata(ebuCoreMainElementPtr, metadataLocation, mxfLocation, progress_callback, optNoIdentification, optForceHeader);	
}

void EmbedEBUCoreMetadata(	xercesc::DOMDocument& metadataDocument, 
							const char* metadataLocation,
							const char* mxfLocation, 
							void (*progress_callback)(float progress, std::string& message, std::string& function),
							bool optNoIdentification, bool optForceHeader) {
	std::auto_ptr<ebuCoreMainType> ebuCoreMainElementPtr (ebuCoreMain (metadataDocument, xml_schema::flags::dont_validate | xml_schema::flags::keep_dom));
	EmbedEBUCoreMetadata(ebuCoreMainElementPtr, metadataLocation, mxfLocation, progress_callback, optNoIdentification, optForceHeader);	
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

int64_t FindLastPartitionFill(mxfpp::File* mFile, mxfpp::Partition* partition, int64_t* partitionSectionOffset, int64_t *extractedFileSize) {
	mxfKey key;
	uint8_t llen;
	uint64_t len;

	// make sure we won't be seeking past the end of the file, so record its size
	int64_t eof = mFile->size();
	if (extractedFileSize != NULL)
		*extractedFileSize = eof;

	mFile->seek(partition->getThisPartition(), SEEK_SET);
	mFile->readKL(&key, &llen, &len);
	mFile->skip(len);
	// read all fillers from here
	bool wasFiller = true;
	while (wasFiller && mFile->tell() < eof) {
		mFile->readKL(&key, &llen, &len);
		if (!mxf_is_filler(&key)) {
			wasFiller = false;
			// rewind till before the KL
			mFile->seek(- mxfKey_extlen - llen, SEEK_CUR);
		} else {
			// skip the filler
			mFile->skip(len);
		}
	}
	int64_t behindPartitionPack = mFile->tell();
	int64_t fillerWritePosition = -1, fillerSeekLimit = -1, fillerSeekStartPosition = -1;;
				
	if (partition->getIndexByteCount() > 0) {
		// extend (or insert) index filler
		fillerSeekStartPosition = behindPartitionPack + partition->getHeaderByteCount();
		fillerSeekLimit = partition->getIndexByteCount();
	}
	else if (partition->getHeaderByteCount() > 0) {
		// extend (or insert) metadata filler
		fillerSeekStartPosition = behindPartitionPack;
		fillerSeekLimit = partition->getHeaderByteCount();
	} else {
		// extend (or insert) partition pack filler
		fillerSeekStartPosition = behindPartitionPack;
		fillerSeekLimit = 0;
	}

	// find the filler to extend section
	mFile->seek(fillerSeekStartPosition, SEEK_SET);
	// find the last filler in the bunch

	uint64_t lastFillerPos = -1;
	uint64_t count = 0;
	while (count < fillerSeekLimit)
	{
		mFile->readKL(&key, &llen, &len);
		if (mxf_is_filler(&key))
			lastFillerPos = behindPartitionPack + partition->getHeaderByteCount() + count;
		count += mxfKey_extlen + llen + len;
		mFile->skip(len);
	}
	
	*partitionSectionOffset = fillerSeekStartPosition;
	return (lastFillerPos == -1) ? (fillerSeekStartPosition + fillerSeekLimit) : (lastFillerPos);
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

std::auto_ptr<ebuCoreMainType> FindAndSerializeEBUCore(HeaderMetadata *metadata) {
	
	MaterialPackage *mp = metadata->getPreface()->findMaterialPackage();
	if (!mp) {
		// throw an exception!
		return std::auto_ptr<ebuCoreMainType>(NULL);
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

	if (ebucore==NULL) {
		// throw an exception!
		return std::auto_ptr<ebuCoreMainType>(NULL);
	}
	
	std::auto_ptr<ebuCoreMainType::coreMetadata_type> main( new ebuCoreMainType::coreMetadata_type() );
	mapCoreMetadata(ebucore->getcoreMetadata(), *main);

	// map the EBU Core KLV framework to the XSD-derived counterpart
	std::auto_ptr<ebuCoreMainType> ebuCoreMainElement( new ebuCoreMainType(main) );

	std::auto_ptr<entityType> p( new entityType() );
	ebucoreMetadataSchemeInformation *info = ebucore->getmetadataSchemeInformation();
	mapEntity(info->getebucoreMetadataProvider(), *(p.get()));
	ebuCoreMainElement->metadataProvider(p);

	return ebuCoreMainElement;
}

void FindAndSerializeEBUCore(HeaderMetadata *metadata, const char* outputfilename) {
	
		std::auto_ptr<ebuCoreMainType> ebuCoreMainElement( FindAndSerializeEBUCore(metadata) );
	
		xml_schema::namespace_infomap map;
		map[""].name = "urn:ebu:metadata-schema:ebuCore_2011";
		map["dc"].name = "http://purl.org/dc/elements/1.1/";

		// open a file output stream
		std::ofstream out(outputfilename);
		ebuCoreMain (out, *ebuCoreMainElement, map);
		out.close();
}

std::auto_ptr<ebuCoreMainType> ExtractEBUCoreMetadataXSD(
							const char* mxfLocation,
							void (*progress_callback)(float progress, std::string& message, std::string& function)) {

	MXFFileReader *file_reader = 0;

    file_reader = new MXFFileReader();
	EBUCore::RegisterMetadataExtensionsforEBUCore(file_reader->GetDataModel());

	MXFFileReader::OpenResult result;
	MXFFile *mxf_file;
	if (MXF_OPEN_READ(mxfLocation, &mxf_file)) {

		File *mFile = new File(mxf_file);
		DataModel *mDataModel = new DataModel();
		EBUCore::RegisterMetadataExtensionsforEBUCore(mDataModel);

		// ///////////////////////////////////////
		// / 1. Open MXF File and locate all partitions, using the RIP
		// ///////////

		if (!mFile->readPartitions())
			log_warn("Failed to read all partitions. File may be incomplete or invalid\n");

	    const std::vector<Partition*> &partitions = mFile->getPartitions();

		// ///////////////////////////////////////
	    // / 1a. Locate the Metadata to use for extension
		/*		We prefer closed footer metadata when available (if the metadata 
				is repeated in the footer, it is likely to be more up-to-date than
				that in the header.																*/
		// ///////////
	    Partition *metadata_partition = NULL, *headerPartition = NULL, *footerPartition = NULL;

		metadata_partition = FindPreferredMetadataPartition(partitions, &headerPartition, &footerPartition);
		if (!metadata_partition)
			THROW_RESULT(MXFFileReader::MXF_RESULT_NO_HEADER_METADATA);

		HeaderMetadata *mHeaderMetadata = new HeaderMetadata(mDataModel);

		mxfKey key; uint8_t llen; uint64_t len;
		mFile->seek(metadata_partition->getThisPartition(), SEEK_SET);
		mFile->readKL(&key, &llen, &len);
		mFile->skip(len);
		mFile->readNextNonFillerKL(&key, &llen, &len);
		BMX_CHECK(mxf_is_header_metadata(&key));
		mHeaderMetadata->read(mFile, metadata_partition, &key, llen, len);

		// ///////////////////////////////////////
		// / 2. Locate the EBUCore metadata in the MXF header metadata and serialize it to 
		// ///////////
		std::auto_ptr<ebuCoreMainType> p( FindAndSerializeEBUCore(mHeaderMetadata) );

		// ///////////////////////////////////////
		// / 3. We're done, close the MXF file.
		// ///////////
		delete file_reader;

		return p;
	}
}


xercesc::DOMDocument& ExtractEBUCoreMetadata(
							const char* mxfLocation,
							void (*progress_callback)(float progress, std::string& message, std::string& function)) {

	std::auto_ptr<ebuCoreMainType> p = ExtractEBUCoreMetadataXSD(mxfLocation, progress_callback);

	xml_schema::namespace_infomap map;
	map[""].name = "urn:ebu:metadata-schema:ebuCore_2011";
	map["dc"].name = "http://purl.org/dc/elements/1.1/";

	::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > xml = ebuCoreMain(*p, map);
	return *xml;

}
	
void ExtractEBUCoreMetadata(const char* mxfLocation,
							const char* metadataLocation,
							void (*progress_callback)(float progress, std::string& message, std::string& function)) {

	std::auto_ptr<ebuCoreMainType> p = ExtractEBUCoreMetadataXSD(mxfLocation, progress_callback);
	// open a file output stream
	std::ofstream out(metadataLocation);
	
	xml_schema::namespace_infomap map;
	map[""].name = "urn:ebu:metadata-schema:ebuCore_2011";
	map["dc"].name = "http://purl.org/dc/elements/1.1/";

	ebuCoreMain (out, *p, map);
	out.close();

}

} // namespace EBUCore
