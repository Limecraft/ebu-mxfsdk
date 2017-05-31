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
#include <algorithm>

#include <bmx/BMXTypes.h>
#include <bmx/BMXException.h>
#include <bmx/Logging.h>
#include <bmx/ByteArray.h>

// mediocre macro definition for MAX
#define MAX(a,b)	((a) > (b) ? (a) : (b))
#define MIN(a,b)	((a) < (b) ? (a) : (b))

#define THROW_RESULT(result) \
{ \
    log_warn("Open error '%s' near %s:%d\n", #result, __FILE__, __LINE__); \
    throw result; \
}

#include <MXFCustomMetadata.h>
#include <XercesUtils.h>

using namespace mxfpp;
using namespace bmx;

namespace EBUSDK {
namespace MXFCustomMetadata {

DarkFileSerializer::DarkFileSerializer(const char* metadataLocation) {
	in.open(metadataLocation, std::ifstream::in | std::ifstream::binary | std::ifstream::ate);
    probe_size = in.tellg();
    // seek back to the front of the file!
    in.seekg(0);
}

uint64_t DarkFileSerializer::WriteToMXFFile(File *f) {
	uint64_t size = 0;
	std::streamsize read=0;
	char buffer[4096];
	while (in) {
		in.read(buffer, 4096); read = in.gcount();
		if (read > 0) {
			f->write((const unsigned char*)buffer, read);
			size += read;
		}
	}
	return size;
	//while (read = in.readsome(buffer, 4096) > 0 && !in.eof()) {
	//	f->write((const unsigned char*)buffer, read);
	//}
}

DarkFileSerializer::~DarkFileSerializer() {
	in.close();
}

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
	 if (	header != NULL && 
			mxf_partition_is_closed(header->getKey()) &&
			header->getHeaderByteCount() > 0)
		metadata_partition = header;
	else if (	footer!=NULL && 
				mxf_partition_is_closed(footer->getKey()) && 
				footer->getHeaderByteCount() > 0)
		metadata_partition = footer;
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

void RewritePartitionPack(mxfpp::File *mxfFile, mxfpp::Partition *partition, bool forceSimilar) {
	mxfFile->seek(partition->getThisPartition(), SEEK_SET);
	if (forceSimilar) {
		mxfKey key;
		uint8_t llen;
		uint64_t len;
		// try to get the original llen to make sure we duplicate the partition pack as much as possible
		mxfFile->readKL(&key, &llen, &len);
		
		// write the partition pack with the llength value
		uint8_t t_llen = mxfFile->getMinLLen();
		if (t_llen != llen)
			mxfFile->setMinLLen(llen);

		// seek back to the partition pack
		mxfFile->seek(partition->getThisPartition(), SEEK_SET);

		partition->write(mxfFile);

		// and reset
		mxfFile->setMinLLen(t_llen);
	} 
	else {
		partition->write(mxfFile);
	}
}

uint64_t BufferIndex(File* mFile, Partition* partition, bmx::ByteArray& index_bytes, uint32_t* index_length) {
	*index_length = partition->getIndexByteCount();
	//std::cout << "Footer Partition index size: " << partition->getIndexByteCount() << std::endl;

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
	//std::cout << "bytes read: " << br << std::endl;
	
	return pos_write_start_metadata;
}

uint64_t BufferPartition(mxfpp::File* mFile, mxfpp::Partition* partition, bmx::ByteArray& partition_bytes, uint32_t* partition_length) {

    uint64_t index_length = partition->getIndexByteCount();
    uint64_t header_length = partition->getHeaderByteCount();

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

    uint64_t partition_lead_in = pos_write_start_metadata - partition->getThisPartition();

    // what's the total size of what we need to copy?
    uint64_t bytes_to_copy = partition_lead_in + header_length + index_length;

	// read the partition elements into a byte buffer for later relocation
    if (partition_bytes.GetSize() < bytes_to_copy)
        partition_bytes.Grow(bytes_to_copy);

    // seek back to the beginning of the partition
    mFile->seek(partition->getThisPartition(), SEEK_SET);
    uint32_t br = mFile->read(partition_bytes.GetBytes(), bytes_to_copy);
    partition_bytes.SetSize(bytes_to_copy);
	//std::cout << "bytes read: " << br << std::endl;

    *partition_length = bytes_to_copy;
	
	return pos_write_start_metadata;
}

uint64_t CopyValueBetweenFiles(File& destFile, File& sourceFile, uint64_t size, uint8_t *buffer, int bufSize) {
	uint64_t totalRead=0, read=0, written=0;
	while (totalRead < size) {
		read = sourceFile.read(buffer, MIN(size-totalRead, bufSize) );
		if (read != MIN(size-totalRead, bufSize)) {
			// if these don't match, something went wrong, except!
			throw bmx::BMXException("Error reading %" PRId64 " bytes from MXF file", MIN(size-totalRead, bufSize));
		}
		written = destFile.write(buffer, read);
		if (written != read)
			// if these don't match, something went wrong, except!
			throw bmx::BMXException("Error writing %" PRId64 " bytes to MXF file", read);
		totalRead += read;
	}
	return size;
}

class FixedKeyComparer {
	const mxfKey *k;
public:
	FixedKeyComparer(const mxfKey *key) : k(key) { };
	bool operator()(const mxfKey *key) {
		return mxf_equals_key(k, key);
	}
};

uint64_t WriteMetadataToMemoryFile(File* mFile, MXFMemoryFile **destMemFile, HeaderMetadata *mHeaderMetadata, uint64_t metadata_read_position, uint64_t metadata_write_position, Partition* metadataDestinationPartition, Partition* metadataSourcePartition, std::vector<const mxfKey*>& darkElementKeysToIgnore) {
	mxfKey key;
	uint8_t llen;
	uint64_t len;

	// cache this in case we are writing to the source partition
	uint64_t oriSourceHeaderByteCount = metadataSourcePartition->getHeaderByteCount();
	uint64_t oriDestHeaderByteCount = metadataDestinationPartition->getHeaderByteCount();

	// we write the metadata to a buffer memory file first, 
	// write 1) the in-mem metadata structure, 2) then dark/unknown sets
	MXFMemoryFile *cMemFile;
	mxf_mem_file_open_new(MEMORY_WRITE_CHUNK_SIZE, /* virtual pos: use the write position offset such that the KAG can be correctly calculated */ metadata_write_position, &cMemFile);
	MXFFile *mxfMemFile = mxf_mem_file_get_file(cMemFile);
	// temporarily wrap the the memory file for use by the libMXF++ classe
	File memFile(mxfMemFile);

	// write the header metadata into the file
	uint64_t footerThisPartition = metadataDestinationPartition->getThisPartition();
	metadataDestinationPartition->setThisPartition(0);	// temporarily override so that internals don't get confused 
														// (need to put this back at the end anyway)

	mHeaderMetadata->write(&memFile, metadataDestinationPartition, NULL);
	uint64_t mHeaderMetadataEndPos = memFile.tell();  // need this position when we re-write the header metadata */
	metadataDestinationPartition->setThisPartition(footerThisPartition);

	// loop back to the beginning of the metadata and find elements that were skipped,
	// because, they were dark, append these to the end of the header metadata
#define COPY_BUFFER_SIZE 64*1024
	std::vector<uint8_t> KLVBuffer(COPY_BUFFER_SIZE);	// will auto-delete when going out of scope (even when exceptions are thrown)

	mFile->seek(metadata_read_position, SEEK_SET);
	uint64_t count = 0;
	while (count < oriSourceHeaderByteCount)
	{
		mFile->readKL(&key, &llen, &len);
		//printf("Count: %lx ", count + 512);

		count += mxfKey_extlen + llen;

		// is this a set we know about in our data model? no, then append it
		// all others that we know a definition of, we leave out of this as they should have been added
		// to the header metadata in the proper way (and may actually have been deleted)
		MXFList *setList = NULL;
		MXFSetDef *setDef = NULL;
		
        bool copied = false;
		if (!mxf_find_set_def(mHeaderMetadata->getCHeaderMetadata()->dataModel, &key, &setDef)) {
			if (!mxf_is_primer_pack(&key) && /* don't include any primer pack or fillers */
				!mxf_is_filler(&key)) {
				FixedKeyComparer f(&key);
				if (std::find_if(darkElementKeysToIgnore.begin(), darkElementKeysToIgnore.end(), f) == darkElementKeysToIgnore.end()) {
					mxf_print_key(&key);
					// no errors and the list is empty, append the KLV to the memory file
					mxf_write_kl(mxfMemFile, &key, len);
                    count += CopyValueBetweenFiles(memFile, *mFile, len, &KLVBuffer[0] /* provide address of first element */, COPY_BUFFER_SIZE);
                    //count += mFile->read(KLVBuffer, len);
					//mxf_file_write(mxfMemFile, KLVBuffer, len);
                    copied = true;
				}
			}
		}
        if (!copied) {
            // this KLV was not copied, skip that many bytes in the file    
            count += len;
			mFile->skip(len);
        }

	}

	uint64_t newHeaderMetadataSize = mxf_file_tell(mxfMemFile) - metadata_write_position;
	// fill the appended metadata up at least the initial size of the metadata and the then following KAG position
	KAGFillerWriter reserve_filler_writer(metadataDestinationPartition, MAX(0, ((int64_t)oriDestHeaderByteCount - (int64_t)newHeaderMetadataSize)));
	reserve_filler_writer.write(&memFile);

	// how many bytes have we written to the memoryfile? subtract the virtual metadata_write_position offset!
	uint64_t memFileSize = mxf_file_tell(mxfMemFile) - metadata_write_position;

	// set output
	*destMemFile = cMemFile;

	// bit of a hack to make sure the memFile isn't closed yet...
	memFile.swapCFile(NULL);

	return memFileSize;
}

uint64_t WriteDarkMetadataToMemoryFile(File* mFile, MXFMemoryFile **destMemFile, MXFFileDarkSerializer& metadata, const mxfKey *darkMetadataSetKey, uint64_t metadata_read_position, uint64_t metadata_write_position, Partition* metadataDestinationPartition, Partition* metadataSourcePartition) {
	mxfKey key;
	uint8_t llen;
	uint64_t len;

	// cache this in case we are writing to the source partition
	uint64_t oriSourceHeaderByteCount = metadataSourcePartition->getHeaderByteCount();
	uint64_t oriDestHeaderByteCount = metadataDestinationPartition->getHeaderByteCount();

	// we write the metadata to a buffer memory file first, 
	// write 1) the in-mem metadata structure, 2) then dark/unknown sets
	MXFMemoryFile *cMemFile;
	mxf_mem_file_open_new(MEMORY_WRITE_CHUNK_SIZE, /* virtual pos: use the write position offset such that the KAG can be correctly calculated */ metadata_write_position, &cMemFile);
	MXFFile *mxfMemFile = mxf_mem_file_get_file(cMemFile);
	// temporarily wrap the the memory file for use by the libMXF++ classe
	File memFile(mxfMemFile);
	
	// write the original header metadata into the memory file
	uint64_t footerThisPartition = metadataDestinationPartition->getThisPartition();
	metadataDestinationPartition->setThisPartition(0);	// temporarily override so that internals don't get confused 
														// (need to put this back at the end anyway)

	mFile->seek(metadata_read_position, SEEK_SET);

	// write each of the KLV packets in the original metadata, 
	// except for ones that match our dark metadata key, which we skip in order to replace old with new
	uint64_t behindLastNonFillerKLV = metadata_write_position;

#define COPY_BUFFER_SIZE 64*1024
	std::vector<uint8_t> KLVBuffer(COPY_BUFFER_SIZE);	// will auto-delete when going out of scope (even when exceptions are thrown)

	uint64_t count = 0, skipped = 0;
	while (count < oriSourceHeaderByteCount) {
		mFile->readKL(&key, &llen, &len);
		count += mxfKey_extlen + llen;

		if (mxf_equals_key(&key, darkMetadataSetKey)) {
			// skip this set from the copy operation, 
			// which effectively acts as a remove op.
			count += len;

			mFile->skip(len);
			skipped += mxfKey_extlen + llen + len;
		} else {
			// copy the KLV packet
			memFile.writeFixedKL(&key, llen, len);
			count += CopyValueBetweenFiles(memFile, *mFile, len, &KLVBuffer[0] /* provide address of first element */, COPY_BUFFER_SIZE);
		}
		if (!mxf_is_filler(&key)) {
			// record position of this non-filler KLV
			behindLastNonFillerKLV = metadata_write_position + count - skipped; // subtract all we have skipped in the destination memfile
		}

	}

	// we can now maneuver behind the last nonfiller element
	memFile.seek(behindLastNonFillerKLV, SEEK_SET);

	// write temporary key without valid length (which we don't know yet)
	memFile.writeFixedKL(darkMetadataSetKey, 4 /* use a fixed length of 4 bytes, this will fit 16MB of dark metadata */, 0);

	// now write the dark metadata
	uint64_t darkMetadataSize = metadata.WriteToMXFFile(&memFile);

	// fill the appended metadata up to the KAG
	uint64_t newHeaderMetadataSize = mxf_file_tell(mxfMemFile) - metadata_write_position;
	// fill the appended metadata up at least the initial size of the metadata and the then following KAG position
	KAGFillerWriter reserve_filler_writer(metadataDestinationPartition, MAX(0, ((int64_t)oriDestHeaderByteCount - (int64_t)newHeaderMetadataSize)));
	reserve_filler_writer.write(&memFile);

	// how many bytes have we written to the memoryfile? subtract the virtual metadata_write_position offset!
	uint64_t memFileSize = mxf_file_tell(mxfMemFile) - metadata_write_position;

	// rewrite dark metadata KL but now with a valid length
	memFile.seek(behindLastNonFillerKLV, SEEK_SET);
	memFile.writeFixedKL(darkMetadataSetKey, 4, darkMetadataSize);

	// and place this back to its original value
	metadataDestinationPartition->setThisPartition(footerThisPartition);

	// set output
	*destMemFile = cMemFile;

	// bit of a hack to make sure the memFile isn't closed yet...
	memFile.swapCFile(NULL);

	return memFileSize;
}

uint64_t WriteDarkMetadataToFile(File* mFile, MXFFileDarkSerializer& metadata, const mxfKey *darkMetadataSetKey, uint64_t metadata_read_position, uint64_t metadata_write_position, bool shiftFileBytesIfNeeded, Partition* metadataDestinationPartition, Partition* metadataSourcePartition) {
	MXFMemoryFile *cMemFile;

	// record the original metadata size
	uint64_t oriMetadataSize = metadataDestinationPartition->getHeaderByteCount();

	// how many bytes have we written to the memoryfile?
	uint64_t memFileSize = WriteDarkMetadataToMemoryFile(mFile, &cMemFile, metadata, darkMetadataSetKey, metadata_read_position, metadata_write_position, metadataDestinationPartition, metadataSourcePartition);

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

uint64_t WriteMetadataToFile(File* mFile, HeaderMetadata *mHeaderMetadata, uint64_t metadata_read_position, uint64_t metadata_write_position, bool shiftFileBytesIfNeeded, Partition* metadataDestinationPartition, Partition* metadataSourcePartition, std::vector<const mxfKey*>& darkElementKeysToIgnore) {
	MXFMemoryFile *cMemFile;

	// record the original metadata size
	uint64_t oriMetadataSize = metadataDestinationPartition->getHeaderByteCount();

	// how many bytes have we written to the memoryfile?
	uint64_t memFileSize = WriteMetadataToMemoryFile(mFile, &cMemFile, mHeaderMetadata, metadata_read_position, metadata_write_position, metadataDestinationPartition, metadataSourcePartition, darkElementKeysToIgnore);

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

void RemoveMetadataSetTree(MXFHeaderMetadata *header_metadata, MXFMetadataSet *set) {
	
	MXFSetDef *setDef;
	mxf_find_set_def(header_metadata->dataModel, &set->key, &setDef);

	//char key[48];
	//mxf_sprint_key(key, &set->key);
	//printf("Deleting item \"%s\" [%s]\n", setDef->name, key);

	// loop through the set and locate strongly referenced children
	MXFListIterator itemIter;
	mxf_initialise_list_iter(&itemIter, &set->items);
    while (mxf_next_list_iter_element(&itemIter))
    {
		MXFItemDef *itemDef;
		MXFMetadataItem *item = (MXFMetadataItem*)mxf_get_iter_element(&itemIter);

		// what is the definition of this item
		if (mxf_find_item_def_in_set_def(&item->key, setDef, &itemDef)) {
			// only if we know the definition
			MXFMetadataSet *referencedSet;
			if (itemDef->typeId == MXF_STRONGREF_TYPE) {
				// item is a single strong reference, follow it
				mxf_get_strongref_item(set, &item->key, &referencedSet);
				
				RemoveMetadataSetTree(header_metadata, referencedSet);

			} else if (itemDef->typeId == MXF_STRONGREFARRAY_TYPE || itemDef->typeId == MXF_STRONGREFBATCH_TYPE) {
				// loop through the array or batch of elements and follow each
				MXFArrayItemIterator arrayIter; uint8_t* _value; uint32_t _length;
		        mxf_initialise_array_item_iterator(set, &item->key, &arrayIter);
				while (mxf_next_array_item_element(&arrayIter, &_value, &_length) != 0)
				{
					MXFListIterator setsIter;
					mxf_initialise_sets_iter(header_metadata, &setsIter);

					if (mxf_get_strongref_s(header_metadata, &setsIter, _value, &referencedSet)) {

						RemoveMetadataSetTree(header_metadata, referencedSet);

					}
				}
			}
		}
 	}

	// done with references, delete ourselves
	mxf_remove_set(header_metadata, set);
}

void RemoveMetadataSetTree(HeaderMetadata *header_metadata, MetadataSet *startSet) {
	MXFHeaderMetadata *c_metadata = header_metadata->getCHeaderMetadata();
	MXFMetadataSet *c_set = startSet->getCMetadataSet();
	RemoveMetadataSetTree(c_metadata, c_set);
}

mxfRational FindMaterialPackageEditRate(HeaderMetadata *header_metadata) {
	Track *selectedTrack = NULL;
	MaterialPackage *material_package = header_metadata->getPreface()->findMaterialPackage();
	const std::vector<GenericTrack*>& tracks = material_package->getTracks();
	for (std::vector<GenericTrack*>::const_iterator it = tracks.begin(); it!=tracks.end(); it++) {
		// use only regular timeline tracks
		Track *tlTrk = dynamic_cast<Track*>(*it);
		if (tlTrk!=NULL) {
			// find the timeline component of this track
			StructuralComponent *comp = tlTrk->getSequence();
			if (comp->getDataDefinition() == MXF_DDEF_L(Timecode)) {
				// this is it, fetch editrate from the track
				selectedTrack = tlTrk;
				break;
			}
		}
	}
	if (selectedTrack == NULL) {
		for (std::vector<GenericTrack*>::const_iterator it = tracks.begin(); it!=tracks.end(); it++) {
			Track *tlTrk = dynamic_cast<Track*>(*it);
			if (tlTrk!=NULL) {
				if (tlTrk->getSequence()->getDataDefinition() == MXF_DDEF_L(Picture)) {
					selectedTrack = tlTrk;
					break;
				}
			}
		}
	}
	if (selectedTrack == NULL) {
		for (std::vector<GenericTrack*>::const_iterator it = tracks.begin(); it!=tracks.end(); it++) {
			Track *tlTrk = dynamic_cast<Track*>(*it);
			if (tlTrk!=NULL) {
				if (tlTrk->getSequence()->getDataDefinition() == MXF_DDEF_L(Sound)) {
					selectedTrack = tlTrk;
					break;
				}
			}
		}
	}

	mxfRational rate = {-1, 0};
	if (selectedTrack != NULL) rate = selectedTrack->getEditRate();
	return rate;
}

std::vector<DMFramework*> GetStaticFrameworks(MaterialPackage *mp)
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

void InsertFramework(HeaderMetadata *header_metadata, uint32_t track_id, std::string track_name, DMFramework *framework, ObjectModifier *mod)
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

void InsertEventFrameworks(HeaderMetadata *header_metadata, uint32_t track_id, std::string track_name, std::vector<EventInput> &frameworks, ObjectModifier *mod)
{
    BMX_ASSERT(header_metadata);

    MaterialPackage *material_package = header_metadata->getPreface()->findMaterialPackage();
    BMX_ASSERT(material_package);

    // Preface - ContentStorage - Package - DM Track
	EventTrack *dm_track = new EventTrack(header_metadata);
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

	for (std::vector<EventInput>::iterator it = frameworks.begin(); it != frameworks.end(); it++) {
		EventInput& ev = *it;
		// Preface - ContentStorage - Package - DM Track - Sequence - DMSegment
		DMSegment *dm_segment = new DMSegment(header_metadata);
		if (mod!=NULL) mod->Modify(dm_segment);
		sequence->appendStructuralComponents(dm_segment);
		dm_segment->setDataDefinition(MXF_DDEF_L(DescriptiveMetadata));
		dm_segment->setEventStartPosition(ev.start);
		dm_segment->setDuration(ev.duration);

		// move the framework set after the dm degment set
		mxf_remove_set(header_metadata->getCHeaderMetadata(), ev.framework->getCMetadataSet());
		BMX_CHECK(mxf_add_set(header_metadata->getCHeaderMetadata(), ev.framework->getCMetadataSet()));

		// Preface - ContentStorage - Package - DM Track - Sequence - DMSegment - DMFramework
		dm_segment->setDMFramework(ev.framework);
	}

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

namespace RP2057 {

    bool AddHeaderMetadata(HeaderMetadata *header_metadata, uint32_t track_id, uint32_t generic_stream_id,
        const char *mime_type, const char *xml_lang, MXFFileDarkXMLSerializer& xml_serializer, mxfUL metadata_scheme_id)
    {   
        bool mRequireStreamPartition = false;

        BMX_ASSERT(header_metadata);

        MaterialPackage *material_package = header_metadata->getPreface()->findMaterialPackage();
        BMX_ASSERT(material_package);

        int64_t data_size = xml_serializer.ProbeSize();

        std::string language_code = (xml_lang != NULL && strlen(xml_lang) != 0) ? xml_lang : xml_serializer.GetLanguageCode();
        if (language_code.empty()) language_code = "en";

        //if (!BMX_OPT_PROP_IS_SET(mLanguageCode))
        //    mLanguageCode = mXMLWriterHelper.GetLanguageCode();
        //if (!BMX_OPT_PROP_IS_SET(mNamespace))
        //    mNamespace = mXMLWriterHelper.GetNamespace();
        //if (!BMX_OPT_PROP_IS_SET(mTextEncoding))
        //    mTextEncoding = mXMLWriterHelper.GetTextEncoding();
        //if (text_encoding == UTF8)
        //    byte_order = BMX_BYTE_ORIENTED;
        //else if (!BMX_OPT_PROP_IS_SET(mByteOrder))
        //    mByteOrder = mXMLWriterHelper.GetByteOrder();
        //std::string text_data_description_str(text_data_description);

        if (xml_serializer.GetTextEncoding() == UTF16)
            data_size = (data_size >> 1) << 1;

        // Preface - ContentStorage - Package - DM Static Track
        StaticTrack *dm_track = new StaticTrack(header_metadata);
        material_package->appendTracks(dm_track);
        dm_track->setTrackID(track_id);
        dm_track->setTrackNumber(0);

        // Preface - ContentStorage - Package - DM Static Track - Sequence
        Sequence *dm_sequence = new Sequence(header_metadata);
        dm_track->setSequence(dm_sequence);
        dm_sequence->setDataDefinition(MXF_DDEF_L(DescriptiveMetadata));

        // Preface - ContentStorage - Package - DM Static Track - Sequence - DMSegment
        DMSegment *dm_segment = new DMSegment(header_metadata);
        dm_sequence->appendStructuralComponents(dm_segment);
        dm_segment->setDataDefinition(MXF_DDEF_L(DescriptiveMetadata));

        // Preface - ContentStorage - Package - DM Static Track - Sequence - DMSegment - TextBasedDMFramework
        TextBasedDMFramework *dm_framework = new TextBasedDMFramework(header_metadata);
        dm_segment->setDMFramework(dm_framework);

        // Preface - ContentStorage - Package - DM Static Track - Sequence - DMSegment - TextBasedDMFramework - TextBasedObject
        TextBasedObject *xml_obj;
        if (data_size < UINT16_MAX && xml_serializer.GetTextEncoding() == UTF8) {
            UTF8TextBasedSet *utf8_xml = new UTF8TextBasedSet(header_metadata);
            xml_obj = utf8_xml;
        } else if (data_size < UINT16_MAX && xml_serializer.GetTextEncoding() == UTF16) {
            UTF16TextBasedSet *utf16_xml = new UTF16TextBasedSet(header_metadata);
            xml_obj = utf16_xml;
        } else {
            GenericStreamTextBasedSet *stream_xml = new GenericStreamTextBasedSet(header_metadata);
            xml_obj = stream_xml;
        }
        dm_framework->setTextBasedObject(xml_obj);
        xml_obj->setTextBasedMetadataPayloadSchemaID(metadata_scheme_id);
        xml_obj->setTextMIMEMediaType(mime_type);
        xml_obj->setRFC5646TextLanguageCode(language_code);
        if (!xml_serializer.GetNamespace().empty())
            xml_obj->setTextDataDescription(xml_serializer.GetNamespace());

        if (dynamic_cast<UTF8TextBasedSet*>(xml_obj)) {
            UTF8TextBasedSet *utf8_xml = dynamic_cast<UTF8TextBasedSet*>(xml_obj);
            std::string data = xml_serializer.GetData();
            mxfpp::ByteArray utf8_bytes;
            utf8_bytes.data   = (uint8_t*)data.data();
            utf8_bytes.length = (uint16_t)data.length();
            utf8_xml->setUTF8TextData(utf8_bytes);
            mRequireStreamPartition = false;
        } else if (dynamic_cast<UTF16TextBasedSet*>(xml_obj)) {
            UTF16TextBasedSet *utf16_xml = dynamic_cast<UTF16TextBasedSet*>(xml_obj);
            std::string data = xml_serializer.GetData();
            mxfpp::ByteArray utf16_bytes;
            utf16_bytes.data   = (uint8_t*)data.data();
            utf16_bytes.length = (uint16_t)data.length();
            utf16_xml->setUTF16TextData(utf16_bytes);
            mRequireStreamPartition = false;
        } else {
            GenericStreamTextBasedSet *stream_xml = dynamic_cast<GenericStreamTextBasedSet*>(xml_obj);
            stream_xml->setGenericStreamSID(generic_stream_id);
            mRequireStreamPartition = true;
        }

        return mRequireStreamPartition;
    }

    TextBasedDMFramework *FindTextBasedDMFramework(mxfpp::HeaderMetadata *header_metadata, mxfUL xml_metadata_scheme_id, mxfpp::StaticTrack **static_track) {

        MaterialPackage *mp = header_metadata->getPreface()->findMaterialPackage();

        if (!mp)
            return NULL;

        // expect to find Static DM Track -> Sequence -> DM Segment -> DM Framework (a TextBasedDMFramework)
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
            if (framework) {

		        TextBasedDMFramework *fw = dynamic_cast<TextBasedDMFramework*>(framework);
                if (!fw)
                    continue;
                TextBasedObject *t = dynamic_cast<TextBasedObject*>(fw->getTextBasedObject());
                if (!t)
                    continue;

                mxfUL ul = t->getTextBasedMetadataPayloadSchemaID();
                if (mxf_equals_ul(&ul, &xml_metadata_scheme_id)) {
                    // this is a match!
                    if (static_track != NULL)
                        *static_track = st;
                    return fw;
                }
            }
        }

        return NULL;
    }

    void WriteStreamXMLData(MXFFileDarkXMLSerializer& xml_serializer, File *mxf_file)
    {
        uint8_t llen = mxf_get_llen(mxf_file->getCFile(), xml_serializer.ProbeSize());
        if (llen < 4)
            llen = 4;

        switch (xml_serializer.GetByteOrder())
        {
            case UNKNOWN_BYTE_ORDER:
                mxf_file->writeFixedKL(&MXF_EE_K(RP2057_ENDIAN_UNK), llen, xml_serializer.ProbeSize());
                break;
            case BMX_BYTE_ORIENTED:
                mxf_file->writeFixedKL(&MXF_EE_K(RP2057_BYTES), llen, xml_serializer.ProbeSize());
                break;
            case BMX_BIG_ENDIAN:
                mxf_file->writeFixedKL(&MXF_EE_K(RP2057_BE), llen, xml_serializer.ProbeSize());
                break;
            case BMX_LITTLE_ENDIAN:
                mxf_file->writeFixedKL(&MXF_EE_K(RP2057_LE), llen, xml_serializer.ProbeSize());
                break;
        }

        xml_serializer.WriteToMXFFile(mxf_file);
    }

    int64_t GetGenericStreamDataOffset(mxfpp::File* mFile, const std::vector<mxfpp::Partition*> &partitions, uint32_t generic_stream_id, int64_t *len, bmx::ByteOrder *byte_order) {

        mxfKey key;
        uint8_t llen;
        uint64_t klvlen;

        for (int i = 0; i < partitions.size(); i++) {
            if (partitions[i]->getBodySID() != generic_stream_id)
                continue;

            mFile->seek(partitions[i]->getThisPartition(), SEEK_SET);
            mFile->readKL(&key, &llen, &klvlen);
            mFile->skip(klvlen);

            bool have_gs_key = false;
            while (!mFile->eof())
            {
                mFile->readNextNonFillerKL(&key, &llen, &klvlen);

                if (mxf_is_partition_pack(&key)) {
                    break;
                } else if (mxf_is_header_metadata(&key)) {
                    if (partitions[i]->getHeaderByteCount() > mxfKey_extlen + llen + klvlen)
                        mFile->skip(partitions[i]->getHeaderByteCount() - (mxfKey_extlen + llen));
                    else
                        mFile->skip(klvlen);
                } else if (mxf_is_index_table_segment(&key)) {
                    if (partitions[i]->getIndexByteCount() > mxfKey_extlen + llen + klvlen)
                        mFile->skip(partitions[i]->getIndexByteCount() - (mxfKey_extlen + llen));
                    else
                        mFile->skip(klvlen);
                } else if (mxf_is_gs_data_element(&key)) {
                    if (key != MXF_EE_K(RP2057_LE) &&
                        key != MXF_EE_K(RP2057_BE) && // == MXF_EE_K(RP2057_BYTES)
                        key != MXF_EE_K(RP2057_ENDIAN_UNK))
                    {
                        BMX_EXCEPTION(("Generic stream essence element key is not a RP 2057 key"));
                    }
                    
                    // we found our data, return relevant info
                    ByteOrder _byte_order = UNKNOWN_BYTE_ORDER;
                    if (key == MXF_EE_K(RP2057_LE))
                        _byte_order = BMX_LITTLE_ENDIAN;
                    else if (key == MXF_EE_K(RP2057_BE)) // == MXF_EE_K(RP2057_BYTES)
                        _byte_order = BMX_BIG_ENDIAN;
                    
                    *byte_order = _byte_order;
                    *len = klvlen;
                    return mFile->tell();
                }
            }
        }

        *byte_order = UNKNOWN_BYTE_ORDER;
        *len = 0;
        return -1;
    }
}

} // namespace MXFCustomMetadata
} //namespace EBUSDK
