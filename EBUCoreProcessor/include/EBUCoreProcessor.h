
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

	uint64_t BufferIndex(mxfpp::File* mFile, mxfpp::Partition* partition, bmx::ByteArray& index_bytes);
	
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