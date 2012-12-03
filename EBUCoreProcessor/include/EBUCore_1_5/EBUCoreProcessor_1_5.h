
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

		/**
		 *	EBU MXF SDK namespace for EBUCore 1.5-specific functionality.
		 */
		namespace EBUCore_1_5 {

			/**
			*	Convenience function for locating KLV-encoded EBUCore metadata in the provided header metadata and serializing this metadata to file.

				@param metadata Parsed header metadata structure of the MXF file.
				@param outputfilename Location of the file to write the serialized metadata to.
			*/
			//void FindAndSerializeEBUCore(mxfpp::HeaderMetadata *metadata, const char* outputfilename);

			class EBUCoreProcessor : public EBUSDK::EBUCore::EBUCoreProcessor {
			public:

				static const mxfUL DMScheme;// = { 0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x05, 0x0D, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00 };

				const mxfUL* GetDescriptiveMetadataScheme();

				/**
				*	Registers the KLV EBUCore metadata extensions with a given MXF metadata data model. These extensions comprise the class structure and ULs associated with metadata sets.

					@param data_model The MXF metadata data model to which the extensions are to be appended.
				*/
				void RegisterMetadataExtensions(mxfpp::DataModel *data_model);

				/**
				*	Registers the KLV EBUCore metadata object factories with a given MXF header metadata structure.
					These object factories allow the MXF metadata processing code to locate appropriate custom metadata set 
					instantiation functions (factories) to call when encountering custom ULs in the metadata. 
					Essentially, when a metadata set with a registered UL is encountered in the MXF metadata, 
					the appropriate factory function will be called to create a metadata set of the correct type.\n
					<em>@b Note!</em> The factory functions must be registered with the empty metadata before actually parsing the MXF file header metadata.

					@param metadata The HeaderMetadata structure with which the factory functions must be registered.
				*/
				void RegisterFrameworkObjectFactories(mxfpp::HeaderMetadata *metadata);


				mxfpp::DMFramework* GenerateSideCarFramework(const char* metadataLocation, mxfpp::HeaderMetadata *destination, mxfpp::Identification* identificationToAppend);

				mxfpp::DMFramework* FindMetadataFramework(mxfpp::HeaderMetadata *metadata);
				bool FrameworkHasActualMetadata(mxfpp::DMFramework *fw);
				bool FrameworkRefersToExternalMetadata(mxfpp::DMFramework *fw);
				std::string GetFrameworkExternalMetadataLocation(mxfpp::DMFramework *fw);

				mxfpp::DMFramework* Process(xercesc::DOMDocument* metadataDocument, const char* metadataLocation, mxfpp::HeaderMetadata *destination, 
					std::vector<EBUSDK::MXFCustomMetadata::EventInput> &eventFrameworks, mxfpp::Identification* identificationToAppend);

				mxfpp::DMFramework* Process(const char* location, mxfpp::HeaderMetadata *destination, mxfpp::Identification* identificationToAppend);

				void ParseAndSerializeMetadata(	mxfpp::DMFramework *framework, 
													EBUSDK::EBUCore::MetadataOutput outputFashion, 
													const char* metadataLocation, 
													xercesc::DOMDocument** outputDocument, 
													void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...));
			};

		} // namespace EBUCore_1_5

	} // namespace EBUCore

} // namespace EBUSDK
