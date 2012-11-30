
#include <libMXF++/MXF.h>
#include <MXFCustomMetadata.h>
#include <EBUCoreProcessor.h>

#include <xercesc/dom/DOMDocument.hpp>

/**
*	EBU MXF SDK main namespace.
*/
namespace EBUSDK {

	/**
	 *	EBU MXF SDK namespace for EBUCore-specific functionality.
	 */
	namespace EBUCore {
		
		namespace EBUCore_1_5 {

	/**
	*	Convenience function for locating KLV-encoded EBUCore metadata in the provided header metadata and serializing this metadata to file.

		@param metadata Parsed header metadata structure of the MXF file.
		@param outputfilename Location of the file to write the serialized metadata to.
	*/
	void FindAndSerializeEBUCore(mxfpp::HeaderMetadata *metadata, const char* outputfilename);

	/**
	*	Registers the KLV EBUCore metadata extensions with a given MXF metadata data model. These extensions comprise the class structure and ULs associated with metadata sets.

		@param data_model The MXF metadata data model to which the extensions are to be appended.
	*/
	void RegisterMetadataExtensionsforEBUCore(mxfpp::DataModel *data_model);

	/**
	*	Registers the KLV EBUCore metadata object factories with a given MXF header metadata structure.
		These object factories allow the MXF metadata processing code to locate appropriate custom metadata set 
		instantiation functions (factories) to call when encountering custom ULs in the metadata. 
		Essentially, when a metadata set with a registered UL is encountered in the MXF metadata, 
		the appropriate factory function will be called to create a metadata set of the correct type.\n
		<em>@b Note!</em> The factory functions must be registered with the empty metadata before actually parsing the MXF file header metadata.

		@param metadata The HeaderMetadata structure with which the factory functions must be registered.
	*/
	void RegisterFrameworkObjectFactoriesforEBUCore(mxfpp::HeaderMetadata *metadata);


	mxfpp::DMFramework* GenerateSideCarFramework(const char* metadataLocation, mxfpp::HeaderMetadata *destination, mxfpp::Identification* identificationToAppend);

	mxfpp::DMFramework* FindEBUCoreMetadataFramework(mxfpp::HeaderMetadata *metadata);
	bool EBUCoreFrameworkHasActualMetadata(mxfpp::DMFramework *fw);
	bool EBUCoreFrameworkRefersToExternalMetadata(mxfpp::DMFramework *fw);
	std::string GetEBUCoreFrameworkExternalMetadataLocation(mxfpp::DMFramework *fw);

	mxfpp::DMFramework* Process(xercesc::DOMDocument* metadataDocument, const char* metadataLocation, mxfpp::HeaderMetadata *destination, 
		std::vector<EBUSDK::MXFCustomMetadata::EventInput> &eventFrameworks, mxfpp::Identification* identificationToAppend);


	void ParseAndSerializeEBUCoreMetadata(	mxfpp::DMFramework *framework, 
										EBUSDK::EBUCore::MetadataOutput outputFashion, 
										const char* metadataLocation, 
										xercesc::DOMDocument** outputDocument, 
										void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...));


		} // namespace EBUCore_1_5

	} // namespace EBUCore

} // namespace EBUSDK
