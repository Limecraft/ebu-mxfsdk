
#include <libMXF++/MXF.h>

mxfpp::DMFramework* Process(std::string location);
mxfpp::DMFramework* Process(std::string location, mxfpp::HeaderMetadata *destination);
void ReadAndSerializeEBUCore(mxfpp::HeaderMetadata *file_reader, const char* outputfilename);
void RegisterMetadataExtensionsforEBUCore(mxfpp::DataModel *data_model);
