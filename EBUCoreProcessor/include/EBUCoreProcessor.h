
#include <libMXF++/MXF.h>

#include <xercesc/dom/DOMDocument.hpp>

namespace EBUCore
{
	mxfpp::Identification* GenerateEBUCoreIdentificationSet(mxfpp::HeaderMetadata *destination);
	mxfpp::DMFramework* Process(const char* location);
	mxfpp::DMFramework* Process(const char* location, mxfpp::HeaderMetadata *destination, mxfpp::Identification *identificationToAppend = NULL);
	void ReadAndSerializeEBUCore(mxfpp::HeaderMetadata *file_reader, const char* outputfilename);
	void RegisterMetadataExtensionsforEBUCore(mxfpp::DataModel *data_model);
	void RegisterFrameworkObjectFactoriesforEBUCore(mxfpp::HeaderMetadata *metadata);
	void InsertEBUCoreFramework(mxfpp::HeaderMetadata *header_metadata, mxfpp::DMFramework *framework, mxfpp::Identification *identificationToAppend = NULL);

	uint64_t BufferIndex(mxfpp::File* mFile, mxfpp::Partition* partition, bmx::ByteArray& index_bytes, uint32_t* index_length);
	uint64_t WriteMetadataToMemoryFile(mxfpp::File* mFile, MXFMemoryFile **destMemFile, mxfpp::HeaderMetadata *mHeaderMetadata, uint64_t metadata_read_position, mxfpp::Partition* metadataDestitionPartition, mxfpp::Partition* metadataSourcePartition);
	uint64_t WriteMetadataToFile(mxfpp::File* mFile, mxfpp::HeaderMetadata *mHeaderMetadata, uint64_t metadata_read_position, uint64_t metadata_write_position, bool shiftFileBytesIfNeeded, mxfpp::Partition* metadataDestitionPartition, mxfpp::Partition* metadataSourcePartition);
	
	int64_t FindLastPartitionFill(mxfpp::File* mFile, mxfpp::Partition* partition, int64_t* partitionSectionOffset, int64_t *extractedFileSize = NULL);
	void ShiftBytesInFile(mxfpp::File* mFile, int64_t shiftPosition, int64_t shiftOffset);
	
	/*void EmbedEBUCoreMetadata(	std::auto_ptr<ebuCore_2011::ebuCoreMainType> metadata, 
							const char* mxfLocation, 
							void (*progress_callback)(float progress, std::string& message, std::string& function),
							bool optNoIdentification = false);*/
	void EmbedEBUCoreMetadata(	const char* metadataLocation, 
							const char* mxfLocation, 
							void (*progress_callback)(float progress, std::string& message, std::string& function),
							bool optNoIdentification = false);
	void EmbedEBUCoreMetadata(	xercesc::DOMDocument& metadataDocument, 
							const char* mxfLocation, 
							void (*progress_callback)(float progress, std::string& message, std::string& function),
							bool optNoIdentification = false);
}