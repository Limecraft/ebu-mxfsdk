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

#include <iterator>
#include <iostream>
#include <fstream>
#include <memory>

#include <bmx/BMXException.h>
#include <bmx/Logging.h>
#include <bmx/ByteArray.h>
#include <bmx/mxf_reader/MXFFileReader.h>
#include <bmx/writer_helper/XMLWriterHelper.h>

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
#include <xercesc/framework/MemBufInputSource.hpp>

using namespace mxfpp;
using namespace bmx;

using namespace EBUSDK::MXFCustomMetadata;
using namespace EBUSDK::MXFCustomMetadata::RP2057;
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

void WriteByteArrayContentsToFile(const char* file, mxfpp::ByteArray& buf) {
	std::ofstream out(file, std::ofstream::out | std::ifstream::binary);
	if (!out.fail()) {
        out.write((const char*)buf.data, buf.length);
	}
	out.close();
}

class DarkFileXMLSerializer : public DarkFileSerializer, public virtual MXFFileDarkXMLSerializer {
    XMLWriterHelper mXMLWriterHelper;
    const char* filename;
    bool extractedInfo;
public:
	
    DarkFileXMLSerializer(const char* metadataLocation) : DarkFileSerializer(metadataLocation), extractedInfo(false), filename(metadataLocation) {}
    virtual ~DarkFileXMLSerializer() {}

    bmx::TextEncoding GetTextEncoding() {
        if (!extractedInfo) {
            mXMLWriterHelper.ExtractInfo(this->filename);
            extractedInfo = true;
        }
        return mXMLWriterHelper.GetTextEncoding();
    }

    bmx::ByteOrder GetByteOrder() {
        if (!extractedInfo) {
            mXMLWriterHelper.ExtractInfo(this->filename);
            extractedInfo = true;
        }
        return mXMLWriterHelper.GetByteOrder();
    }

    std::string GetLanguageCode() {
        if (!extractedInfo) {
            mXMLWriterHelper.ExtractInfo(this->filename);
            extractedInfo = true;
        }
        return mXMLWriterHelper.GetLanguageCode();
    }

    std::string GetNamespace() {
        if (!extractedInfo) {
            mXMLWriterHelper.ExtractInfo(this->filename);
            extractedInfo = true;
        }
        return mXMLWriterHelper.GetNamespace();    
    }

    std::string GetData() {
        std::stringstream ss;

        uint64_t size = 0;
	    std::streamsize read=0;
	    char buffer[4096];
	    while (in) {
		    in.read(buffer, 4096); read = in.gcount();
		    if (read > 0) {
			    ss.write((const char*)buffer, read);
			    size += read;
		    }
	    }
        return ss.str();
    }

    uint64_t WriteToMXFFile(File *f) {
        return DarkFileSerializer::WriteToMXFFile(f);
    }

    virtual uint64_t ProbeSize() { 
        return DarkFileSerializer::ProbeSize();
    }

};

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

EBUCoreProcessor* GetEBUCoreProcessor(const EBUCoreProcessors version) {
	switch (version) {
	case EBUCORE_1_4:
		return new EBUCore_1_4::EBUCoreProcessor();
	}
	return NULL;
}

bool IsSupportedEBUCoreMetadataScheme(const mxfUL* label) {
	if (mxf_equals_ul(label,  &EBUCore_1_4::EBUCoreProcessor::DMScheme))
		return true;
	return false;
}

void EnumerateSupportedEBUCoreDarkSetKeys(std::vector<const mxfKey*>& darkSetKeys) {
	darkSetKeys.push_back(&EBUCore_1_4::EBUCoreProcessor::DMScheme);
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
                            const std::vector<Partition*> &partitions,
							File *mxfFile,
							const char* metadataLocation,
							xercesc::DOMDocument** outputDocument,
							MetadataOutput outputFashion,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
                            const mxfKey *customDarkMetadataKey,
                            const mxfUL *rp2057XMLSchemeId);

void InnerEmbedEBUCoreMetadata(	
							xercesc::DOMDocument* metadataDocument, 
							const char* metadataLocation,
							const char* mxfLocation,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
							MetadataKind optWaytoWrite,
							bool optNoIdentification, bool optForceHeader, const mxfKey *customDarkMetadataKey,
                            const RP2057EmbeddingOptions *optRP2057) {

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
		/*		 this determines the version of EBUCoreProcessor to use	 */
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
		MetadataKind existingKind = ExtractEBUCoreMetadata(processor, &*mHeaderMetadata, metadata_partition, partitions, 
            &*mFile, NULL, NULL, DONT_SERIALIZE, 
            progress_callback, customDarkMetadataKey, &optRP2057->scheme_id);
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
        
        // in case we do RP2057 metadata writing, it might have to be written to the a separate generic stream partition
        bool requireMetadataStreamPartition = false;
        uint32_t metadataStreamPartitionStreamID = 0;

        if (optWaytoWrite != DARK && optWaytoWrite != RP2057 && optWaytoWrite != NONE) {
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

			ignoredDarkKeys.push_back(processor->GetDarkMetadataSetKey());

		} else {
			// ///////////////////////////////////////
			// / 3. Decide on the way to serialize this 'dark' metadata, 
            // /     plain dark or using RP2057. In the case of RP2057, we need to 
            // /     add elements to the header metadata too.
            // /     In both cases, we create Serializers for our dark metadata.
			// ///////////
            if (optWaytoWrite == RP2057) {

                // Loop through the MXF partition a optain a free stream ID to use in case
                // we need to write a new partition
                uint32_t newStreamId = 0;
                for (int i = 0; i < partitions.size(); i++) {
                    Partition *p = partitions[i];
                    if (newStreamId <= p->getBodySID()) 
                        newStreamId = p->getBodySID() + 1;
                }
                metadataStreamPartitionStreamID = newStreamId;

                // Create XML-aware serializers because we will need XML-related info to put into the
                // RP2057 header metadata
			    ser.reset( (metadataDocument != NULL) ? 
				    static_cast<MXFFileDarkSerializer*>(new DarkDOMDocumentSerializer(*metadataDocument)) : 
				    static_cast<MXFFileDarkSerializer*>(new DarkFileXMLSerializer(metadataLocation)) 
			    );

                // And write the header metadata for this RP2057 metadata
                MXFFileDarkXMLSerializer *xml_serializer = dynamic_cast<MXFFileDarkXMLSerializer*>(&*ser);
                requireMetadataStreamPartition = 
                    RP2057::AddHeaderMetadata(&*mHeaderMetadata, 8001, metadataStreamPartitionStreamID, 
                        "application/xml", optRP2057->lang, *xml_serializer, optRP2057->scheme_id);

            } else {

			    ser.reset( (metadataDocument != NULL) ? 
				    static_cast<MXFFileDarkSerializer*>(new DarkDOMDocumentSerializer(*metadataDocument)) : 
				    static_cast<MXFFileDarkSerializer*>(new DarkFileSerializer(metadataLocation))
			    );

            }
		}

		// ///////////////////////////////////////
		// / 2. In order to avoid rewriting large portions of the file, we append our metadata
		// / to that of the footer partition (if already present, and new otherwise)
		// ///////////
		if (!optForceHeader) {

			// What does the footer partition look like? Are there index entries to move around?
			uint32_t index_length = 0;
			bmx::ByteArray index_bytes(index_length);
			uint64_t pos_write_start_metadata = BufferIndex(&*mFile, footerPartition, index_bytes, &index_length);

            // before we rewriting the footer partition with updated metadata, 
            // we need to put in a generic stream partition with metadata
            if (optWaytoWrite == RP2057 && requireMetadataStreamPartition) {
    			progress_callback(0.5, INFO, "EmbedEBUCoreMetadata", "Writing RP2057 metadata into generic stream partition");
                
                // Buffer the entire footer partition so that we can rewrite it at the end
                // Why? In case the source metadata partition is the footer partition, we need to
                // read dark metadata (which is not in memory but only in the file) in order
                // to copy it when updated metadata is rewritten.
                // If we would not do this, the generic stream partition would overwrite the 
                // footer partition metadata and there would be no way to recover this dark metadata...
    			uint32_t partition_length = 0;
	    		bmx::ByteArray partition_bytes(partition_length);
                BufferPartition(&*mFile, footerPartition, partition_bytes, &partition_length);

                // seek to the current footer partition, we'll put the generic partition there and then rewrite
                // the footer at a higher position
                mFile->seek(footerPartition->getThisPartition(), SEEK_SET);

                // write out a newly (inserted) generic stream partition
                Partition &stream_partition = mFile->insertPartition(partitions.size()-1); // Insert before the footer partition.
                stream_partition.setKey(&MXF_GS_PP_K(GenericStream));
                stream_partition.setBodySID(metadataStreamPartitionStreamID);
                stream_partition.write(&*mFile);

                MXFFileDarkXMLSerializer *xml_serializer = dynamic_cast<MXFFileDarkXMLSerializer*>(&*ser);
                RP2057::WriteStreamXMLData(*xml_serializer, &*mFile);

                // after the MXF metadata, write filler to align the next partition to the grid
                stream_partition.fillToKag(&*mFile);

                uint64_t streamPartitionLength = mFile->tell() - footerPartition->getThisPartition();

                // the new file offset is the new offset for the footer partition
                footerPartition->setThisPartition(footerPartition->getThisPartition() + streamPartitionLength);

                pos_write_start_metadata += streamPartitionLength;

                // and finish by writing the buffered partition back into its place
                mFile->seek(footerPartition->getThisPartition(), SEEK_SET);
                mFile->write(partition_bytes.GetBytes(), partition_bytes.GetSize());
            }   

            progress_callback(0.5, INFO, "EmbedEBUCoreMetadata", "Writing new metadata into footer partition");

			uint64_t headerMetadataSize = (optWaytoWrite == DARK) ?
				WriteDarkMetadataToFile(	&*mFile, 
											*ser, 
                                            customDarkMetadataKey != NULL ? customDarkMetadataKey : processor->GetDarkMetadataSetKey(),
											pos_start_metadata, pos_write_start_metadata, false, footerPartition, metadata_partition) :
				WriteMetadataToFile(		&*mFile, 
											&*mHeaderMetadata, 
											pos_start_metadata, pos_write_start_metadata, false, footerPartition, metadata_partition, 
											ignoredDarkKeys);

			if (index_length > 0) {
				progress_callback(0.75, DEBUG, "EmbedEBUCoreMetadata", "Rewriting footer partition index entries");

				// write the index tables back to the footer partition
				mFile->write(index_bytes.GetBytes(), index_bytes.GetSize());
			}

			progress_callback(0.8f, INFO, "EmbedEBUCoreMetadata", "Rewriting file Random Index Pack");

			mFile->writeRIP();

			progress_callback(0.9f, INFO, "EmbedEBUCoreMetadata", "Updating partition packs");

			// seek backwards and update footer partition pack
			footerPartition->setHeaderByteCount(/*footerPartition->getHeaderByteCount() + */ headerMetadataSize); // Add dark metadata elements to file
			RewritePartitionPack(&*mFile, footerPartition, true);

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
				RewritePartitionPack(&*mFile, p, true);
			}

		} else {
			// ///////////////////////////////////////
			// / 2a. Provide an override where the file is rewritten to accomodate updated metadata in the header partition?
			// / (This could become necessary when generated MXF files need 
			// / to be natively supported by playout/hardware-constrained machines)
			// ///////////
			progress_callback(0.5, INFO, "EmbedEBUCoreMetadata", "Forcing new metadata into header partition, shifting bytes where necessary");

			// where to write the metadata? find the proper position in the header partition
			mFile->seek(headerPartition->getThisPartition(), SEEK_SET);
			mFile->readKL(&key, &llen, &len);
			mFile->skip(len);
			mFile->readNextNonFillerKL(&key, &llen, &len);
			BMX_CHECK(mxf_is_header_metadata(&key));
			uint64_t pos_write_start_metadata =  mFile->tell() - mxfKey_extlen - llen;

			uint64_t oriMetadataSize = headerPartition->getHeaderByteCount();

			// Write metadata to the header partition, forcing a file bytes shift if required (likely)
			uint64_t headerMetadataSize = (optWaytoWrite == DARK) ?
				WriteDarkMetadataToFile(	&*mFile, 
											*ser, 
											customDarkMetadataKey != NULL ? customDarkMetadataKey : processor->GetDarkMetadataSetKey(), 
											pos_start_metadata, pos_write_start_metadata, true, headerPartition, metadata_partition) :
				WriteMetadataToFile(		&*mFile, 
											&*mHeaderMetadata, 
											pos_start_metadata, pos_write_start_metadata, true, headerPartition, metadata_partition, 
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
					// make sure we mark the header partition as closed and complete
					p->setKey(&MXF_PP_K(ClosedComplete, Header) );
				}
				if (p->getFooterPartition() > 0) {
					// only set if there was a valid value for the footer partition in the first place
					p->setFooterPartition(p->getFooterPartition() + fileOffset);
				}
				RewritePartitionPack(&*mFile, p, true);
				prevPartition = p->getThisPartition();
			}

            // after rewriting the header metadata and shifting file bytes down,
            // we need to put in a generic stream partition with metadata.
            // We'll place this one right before the footer partition, so that will be the only partition to rewrite
            if (optWaytoWrite == RP2057 && requireMetadataStreamPartition) {
    			progress_callback(0.5, INFO, "EmbedEBUCoreMetadata", "Writing RP2057 metadata into generic stream partition");
                
                // Buffer the entire footer partition so that we can rewrite it at the end
    			uint32_t partition_length = 0;
	    		bmx::ByteArray partition_bytes(partition_length);
                BufferPartition(&*mFile, footerPartition, partition_bytes, &partition_length);

                // seek to the current footer partition, we'll put the generic partition there and then rewrite
                // the footer at a higher position
                mFile->seek(footerPartition->getThisPartition(), SEEK_SET);

                // write out a newly (inserted) generic stream partition
                Partition &stream_partition = mFile->insertPartition(partitions.size()-1); // Insert before the footer partition.
                stream_partition.setKey(&MXF_GS_PP_K(GenericStream));
                stream_partition.setBodySID(metadataStreamPartitionStreamID);
                stream_partition.write(&*mFile);

                MXFFileDarkXMLSerializer *xml_serializer = dynamic_cast<MXFFileDarkXMLSerializer*>(&*ser);
                RP2057::WriteStreamXMLData(*xml_serializer, &*mFile);

                // after the MXF metadata, write filler to align the next partition to the grid
                stream_partition.fillToKag(&*mFile);

                uint64_t streamPartitionLength = mFile->tell() - footerPartition->getThisPartition();

                // the new file offset is the new offset for the footer partition
                footerPartition->setThisPartition(footerPartition->getThisPartition() + streamPartitionLength);

                pos_write_start_metadata += streamPartitionLength;

                // and finish by writing the buffered partition back into its place
                mFile->seek(footerPartition->getThisPartition(), SEEK_SET);
                mFile->write(partition_bytes.GetBytes(), partition_bytes.GetSize());

                // and rewrite the footer partition pack with an updated offset (is done later!)
                //mFile->seek(footerPartition->getThisPartition(), SEEK_SET);
                //RewritePartitionPack(&*mFile, footerPartition, true);
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
			RewritePartitionPack(&*mFile, footerPartition, true);
		}

        // clean-up through auto_ptr destruction
}

void EmbedEBUCoreMetadata(	const char* metadataLocation, 
							const char* mxfLocation, 
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
							MetadataKind optWaytoWrite,
							bool optNoIdentification, bool optForceHeader, const mxfKey *customDarkMetadataKey,
                            const RP2057EmbeddingOptions *optRP2057) {

	progress_callback(0.0f, INFO, "EmbedEBUCoreMetadata", "Writing EBUCore metadata to MXF file %s, in %s mode...", mxfLocation, 
		optWaytoWrite == KLV_ENCODED ? "KLV-encoded" : (optWaytoWrite == SIDECAR ? "side-car" : "dark metadata" ) );
	progress_callback(0.1f, INFO, "EmbedEBUCoreMetadata", "Reading EBUCore XML document from file %s", metadataLocation);

	InnerEmbedEBUCoreMetadata(NULL, metadataLocation, mxfLocation, progress_callback, optWaytoWrite, optNoIdentification, optForceHeader, 
        customDarkMetadataKey, optRP2057);	

}

void EmbedEBUCoreMetadata(	xercesc::DOMDocument& metadataDocument, 
							const char* metadataLocation,
							const char* mxfLocation, 
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
							MetadataKind optWaytoWrite,
							bool optNoIdentification, bool optForceHeader, const mxfKey *customDarkMetadataKey,
                            const RP2057EmbeddingOptions *optRP2057) {

	progress_callback(0.0f, INFO, "EmbedEBUCoreMetadata", "Writing EBUCore metadata to MXF file %s, in %s mode...", mxfLocation, 
		optWaytoWrite == KLV_ENCODED ? "KLV-encoded" : (optWaytoWrite == SIDECAR ? "side-car" : "dark metadata" ) );
	progress_callback(0.1f, INFO, "EmbedEBUCoreMetadata", "Reading EBUCore XML document from DOMDocument input");

	InnerEmbedEBUCoreMetadata(&metadataDocument, metadataLocation, mxfLocation, progress_callback, optWaytoWrite, optNoIdentification, optForceHeader, 
        customDarkMetadataKey, optRP2057);

}

void RemoveEBUCoreMetadata(	const char* mxfLocation,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
							bool optNoIdentification, bool optForceHeader, const mxfKey *customDarkMetadataKey) {

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
		progress_callback(0.25, INFO, "RemoveEBUCoreMetadata", "Locating preferred MXF metadata");

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
		/*		 this determines the version of EBUCoreProcessor to use	 */
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
		// / 2. Remove the EBU Core metadata from the header metadata
		// ///////////
		progress_callback(0.4f, INFO, "RemoveEBUCoreMetadata", "Removing EBUCore metadata from MXF metadata");
		// prepare a vector of dark metadata keys that is to be ignored (i.e., discarded) 
		// when metadata is (re)written to the file
		std::vector<const mxfKey*> ignoredDarkKeys;
        if (customDarkMetadataKey!=NULL) {
            // Remove a specific key of dark metadata, leave all regular EBUCore keys intact
            ignoredDarkKeys.push_back(customDarkMetadataKey);
        } else {
		    EnumerateSupportedEBUCoreDarkSetKeys(ignoredDarkKeys);
        }

		// if there is a supported processor, assume that the extensions are loaded and we can remove the metadata
		if (processor != NULL) {

			// ///////////////////////////////////////
			// / 3. Do a KLV-encoded removate of the metadata.
			// ///////////
			Identification* id = optNoIdentification ? NULL : EBUCore::GenerateEBUCoreIdentificationSet(&*mHeaderMetadata);

			// remove any previously present EBUCore metadata
			RemoveEBUCoreFrameworks(&*mHeaderMetadata);
		}

		// ///////////////////////////////////////
		// / 4. In order to avoid rewriting large portions of the file, we append our metadata
		// / to that of the footer partition (if already present, and new otherwise)
		// ///////////
		if (!optForceHeader) {

			progress_callback(0.5, INFO, "EmbedEBUCoreMetadata", "Writing updated metadata into footer partition");

			// What does the footer partition look like? Are there index entries to move around?
			uint32_t index_length = 0;
			bmx::ByteArray index_bytes(index_length);
			uint64_t pos_write_start_metadata = BufferIndex(&*mFile, footerPartition, index_bytes, &index_length);

			// Write the stripped header metadata, ignoring any supported EBUCore dark keys
			uint64_t headerMetadataSize = WriteMetadataToFile(	 &*mFile, 
																 &*mHeaderMetadata, 
																 pos_start_metadata, pos_write_start_metadata, false, footerPartition, metadata_partition, 
																 ignoredDarkKeys);

			if (index_length > 0) {
				progress_callback(0.75, DEBUG, "RemoveEBUCoreMetadata", "Rewritng footer partition index entries");

				// write the index tables back to the footer partition
				mFile->write(index_bytes.GetBytes(), index_bytes.GetSize());
			}

			progress_callback(0.8f, INFO, "RemoveEBUCoreMetadata", "Rewriting file Random Index Pack");

			mFile->writeRIP();

			progress_callback(0.9f, INFO, "RemoveEBUCoreMetadata", "Updating partition packs");

			// seek backwards and update footer partition pack
			footerPartition->setHeaderByteCount(/*footerPartition->getHeaderByteCount() + */ headerMetadataSize); // Add dark metadata elements to file
			RewritePartitionPack(&*mFile, footerPartition, true);

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
				RewritePartitionPack(&*mFile, p, true);
			}

		} else {
			// ///////////////////////////////////////
			// / 2a. Provide an override where the file is rewritten to accomodate updated metadata in the header partition?
			// / (This could become necessary when generated MXF files need 
			// / to be natively supported by playout/hardware-constrained machines)
			// ///////////
			progress_callback(0.5, INFO, "RemoveEBUCoreMetadata", "Forcing new metadata into header partition, shifting bytes where necessary");

			uint64_t oriMetadataSize = headerPartition->getHeaderByteCount();

			// Write metadata to the header partition, forcing a file bytes shift if required (likely)
			uint64_t headerMetadataSize = WriteMetadataToFile(		&*mFile, 
																	&*mHeaderMetadata, 
																	pos_start_metadata, pos_start_metadata, true, headerPartition, metadata_partition, 
																	ignoredDarkKeys);

			uint64_t fileOffset = headerMetadataSize - oriMetadataSize;

			progress_callback(0.8f, INFO, "RemoveEBUCoreMetadata", "Shifted file bytes after header partition by %" PRId64 " bytes", fileOffset);

			progress_callback(0.81f, INFO, "RemoveEBUCoreMetadata", "Updating partition pack offsets");
			
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
				if (p->getFooterPartition() > 0) {
					// only set if there was a valid value for the footer partition in the first place
					p->setFooterPartition(p->getFooterPartition() + fileOffset);
				}
				RewritePartitionPack(&*mFile, p, true);
				prevPartition = p->getThisPartition();
			}

			// Finish by re-writing the rip.
			// To be safe, we will overwrite the entire RIP of the previous file, 
			// by extending the filler if present, or by adding a new filler up until the next KAG.

			progress_callback(0.9f, INFO, "RemoveEBUCoreMetadata", "Rewriting file Random Index Pack");

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

			RewritePartitionPack(&*mFile, footerPartition, true);
		}

        // clean-up through auto_ptr destruction
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
                            const std::vector<Partition*> &partitions,
							File *mxfFile,
							const char* metadataLocation,
							xercesc::DOMDocument** outputDocument,
							MetadataOutput outputFashion,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
                            const mxfKey *customDarkMetadataKey,
                            const mxfUL *rp2057XMLSchemeId) {


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
    else if (rp2057XMLSchemeId != NULL) {
        // ///////////////////////////////////////
		// / 2c. If there is no KLV-codec metadata, but there is a provided RP2057 Scheme ID,
		// /     we can try find our metadata there...
		// ///////////
        TextBasedObject *text_object = NULL;

        MaterialPackage *mp = headerMetadata->getPreface()->findMaterialPackage();
	    if (mp) {
            std::vector<DMFramework*> static_frameworks = GetStaticFrameworks(mp);
	        size_t i;
            for (i = 0; i < static_frameworks.size(); i++) {
		        TextBasedDMFramework *p = dynamic_cast<TextBasedDMFramework*>(static_frameworks[i]);
                if (!p)
                    continue;
                TextBasedObject *t = dynamic_cast<TextBasedObject*>(p->getTextBasedObject());
                if (!t)
                    continue;

                mxfUL ul = t->getTextBasedMetadataPayloadSchemaID();
                if (mxf_equals_ul(&ul, rp2057XMLSchemeId)) {
                    // this is a match!
                    text_object = t;
                    break;
                }
            }
        }

        if (text_object) {
            UTF8TextBasedSet *utf8_text        = dynamic_cast<UTF8TextBasedSet*>(text_object);
            UTF16TextBasedSet *utf16_text      = dynamic_cast<UTF16TextBasedSet*>(text_object);
            GenericStreamTextBasedSet *gs_text = dynamic_cast<GenericStreamTextBasedSet*>(text_object);

            if (utf8_text || utf16_text) {
                mxfpp::ByteArray byte_array;
                if (utf8_text)
                    byte_array = utf8_text->getUTF8TextData();
                else
                    byte_array = utf16_text->getUTF16TextData();
                if (byte_array.length > 0) {

                    if (outputFashion == SERIALIZE_TO_FILE) {
    					progress_callback(0.9f, INFO, "ExtractEBUCoreMetadata", "Writing RP-2057-embedded metadata from header metadata to XML file at %s", metadataLocation);
                       
					    WriteByteArrayContentsToFile(metadataLocation, byte_array);
				    } 
				    else if (outputFashion == OUTPUT_AS_DOM_DOCUMENT) {
					    progress_callback(0.9f, INFO, "ExtractEBUCoreMetadata", "Writing RP-2057-embedded metadata from header metadata to output Xerces-C DOM Document");
					
                        MemBufInputSource inp((const XMLByte*)byte_array.data, byte_array.length, "ByteArray buffer");
					    *outputDocument = ParseXercesDocument(inp);
                    }
                }
            } 
            else if (gs_text) {
                int64_t len;
                bmx::ByteOrder byte_order;
                // figure out where the relevant data is
                int64_t stream_offset = GetGenericStreamDataOffset(mxfFile, partitions, gs_text->getGenericStreamSID(), &len, &byte_order);

                // [TODO] Add error handling in case returned offset == -1.
                if (outputFashion == SERIALIZE_TO_FILE) {
					progress_callback(0.9f, INFO, "ExtractEBUCoreMetadata", "Writing RP-2057-embedded metadata from generic stream partition to XML file at %s", metadataLocation);

                    mxfFile->seek(stream_offset, SEEK_SET);
					WriteKLVContentsToFile(metadataLocation, mxfFile, len);
				} 
				else if (outputFashion == OUTPUT_AS_DOM_DOCUMENT) {
					progress_callback(0.9f, INFO, "ExtractEBUCoreMetadata", "Writing RP-2057-embedded metadata from generic stream partition to output Xerces-C DOM Document");
					
                    mxfFile->seek(stream_offset, SEEK_SET);
					KLVInputSource inp(mxfFile, len);
					*outputDocument = ParseXercesDocument(inp);
				}

            }
            return RP2057;
        }
    }
	else {
		// ///////////////////////////////////////
		// / 2d. If there is no KLV-codec metadata, there could be embedded dark metadata,
		// /     find its key in the metadata
		// ///////////
		mxfKey key; uint8_t llen; uint64_t len;

		bool darkFound = false;
		progress_callback(0.61f, INFO, "ExtractEBUCoreMetadata", "No ebucoreMainFramework found on the MXF timeline, looking for dark metadata...");

		std::vector<const mxfKey*> darkSetKeys;
        if (customDarkMetadataKey != NULL) {
            darkSetKeys.push_back(customDarkMetadataKey);
        }
        else {
		    if (processor != NULL)
			    darkSetKeys.push_back(processor->GetDarkMetadataSetKey());
		    else
			    EBUCore::EnumerateSupportedEBUCoreDarkSetKeys(darkSetKeys);
        }

		mxfFile->seek(partition->getThisPartition(), SEEK_SET);
		uint64_t count = 0, sourceHeaderByteCount = partition->getHeaderByteCount();
		while (count < sourceHeaderByteCount)
		{
			mxfFile->readKL(&key, &llen, &len);
			
			for (std::vector<const mxfKey*>::const_iterator it = darkSetKeys.begin(); it != darkSetKeys.end(); it++) {
				if (mxf_equals_key(&key, *it)) {
					darkFound = true;
					break;
				}
			}

			if (darkFound) {
				
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
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
                            const mxfKey *customDarkMetadataKey,
                            const mxfUL *rp2057XMLSchemeId) {
	
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

	ExtractEBUCoreMetadata(processor, &*mHeaderMetadata, metadata_partition, partitions, 
        &*mFile, metadataLocation, outputDocument, outputFashion, 
        progress_callback, customDarkMetadataKey, rp2057XMLSchemeId);

	// ///////////////////////////////////////
	// / 3. We're done, close the MXF file.
	// ///////////
	// mxf file is closed through auto_ptr
}

xercesc::DOMDocument& ExtractEBUCoreMetadata(
							const char* mxfLocation,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
                            const mxfKey *customDarkMetadataKey, const mxfUL *rp2057SchemeId) {

	xercesc::DOMDocument *doc;
	ExtractEBUCoreMetadata(mxfLocation, NULL, &doc, OUTPUT_AS_DOM_DOCUMENT, progress_callback, customDarkMetadataKey, rp2057SchemeId);
	return *doc;

}
	
void ExtractEBUCoreMetadata(const char* mxfLocation,
							const char* metadataLocation,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
                            const mxfKey *customDarkMetadataKey, const mxfUL *rp2057SchemeId) {

    ExtractEBUCoreMetadata(mxfLocation, metadataLocation, NULL, SERIALIZE_TO_FILE, progress_callback, customDarkMetadataKey, rp2057SchemeId);

}

} // namespace EBUCore
} //namespace EBUSDK
