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
		 *	EBU MXF SDK namespace for EBUCore 1.4-specific functionality.
		 */
		namespace EBUCore_1_4 {

			/**
			*	EBUCoreProcessor implementation for EBUCore version 1.5.
			*/
			class EBUCoreProcessor : public EBUSDK::EBUCore::EBUCoreProcessor {
			public:
				static const mxfUL DMScheme;// = { 0x06, 0x0E, 0x2B, 0x34, 0x01, 0x01, 0x01, 0x05, 0x0D, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00 };

				const mxfUL* GetDescriptiveMetadataScheme();
				const mxfKey* GetDarkMetadataSetKey();
				void RegisterMetadataExtensions(mxfpp::DataModel *data_model);
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

		} // namespace EBUCore_1_4

	} // namespace EBUCore

} // namespace EBUSDK
