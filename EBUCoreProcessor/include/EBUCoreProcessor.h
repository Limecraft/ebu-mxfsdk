
#include <libMXF++/MXF.h>

namespace EBUCore
{
	mxfpp::Identification* GenerateEBUCoreIdentificationSet(mxfpp::HeaderMetadata *destination);
	mxfpp::DMFramework* Process(const char* location);
	mxfpp::DMFramework* Process(const char* location, mxfpp::HeaderMetadata *destination, mxfpp::Identification *identificationToAppend = NULL);
	void ReadAndSerializeEBUCore(mxfpp::HeaderMetadata *file_reader, const char* outputfilename);
	void RegisterMetadataExtensionsforEBUCore(mxfpp::DataModel *data_model);
	void RegisterFrameworkObjectFactoriesforEBUCore(mxfpp::HeaderMetadata *metadata);
	void InsertEBUCoreFramework(mxfpp::HeaderMetadata *header_metadata, mxfpp::DMFramework *framework, mxfpp::Identification *identificationToAppend = NULL);
}