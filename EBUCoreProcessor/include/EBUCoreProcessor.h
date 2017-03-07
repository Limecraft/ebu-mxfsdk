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
 
#ifndef __EBUSDK_EBUCOREPROCESSOR_H__
#define __EBUSDK_EBUCOREPROCESSOR_H__

#ifdef EXPORTING
#define DLLEXPORT __declspec(dllexport)
#elif IMPORTING
#define DLLEXPORT __declspec(dllimport)
#else
#define DLLEXPORT
#endif

#include <libMXF++/MXF.h>
#include <MXFCustomMetadata.h>

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
	*	Generates an MXF Identification metadata set that can be referred to by new and updated metdata sets in the MXF file.\n
		The following information is contained in the set:\n
		- Company Name: "EBU"
		- Product Name: "EBUCore SDK"
		- ProductUID: { 0xda, 0xe5, 0x92, 0x18, 0xaf, 0x8d, 0x47, 0xd4, 0xa2, 0x16, 0xb6, 0xc6, 0x48, 0xea, 0x54, 0x8c }

		@return Returns the generated Identification set.
		@param destination The HeaderMetadata structure to which the Identification set will be added.
	*/
	DLLEXPORT mxfpp::Identification* GenerateEBUCoreIdentificationSet(mxfpp::HeaderMetadata *destination);

	/**
	*	Parses EBUCore metadata in a file at __location__ and returns the resulting EBUCore MXF descriptive metadata framework of the type EBUCoreMainFramework.\n
		In case the optional Identification set is provided in the __identificationToAppend__ argument, 
		this Identification is referenced from all metadata sets generated during the parsing operation. 
		This allows external applications to track all metadata related to this particular parsing (and possibly subsequent MXF update) operation.

		@return Returns the parsed EBUCoreMainFramework set.
		@param location Location of the metadata file.
		@param destination The HeaderMetadata structure to which the EBUCoreMainFramework and its descending metadata sets will be added.
		@param identificationToAppend Optional Identification metadata set that will be referenced from each parsed metadata set.
	*/
	DLLEXPORT mxfpp::DMFramework* Process(const char* location, mxfpp::HeaderMetadata *destination, mxfpp::Identification *identificationToAppend = NULL);

	/**
	*	Convenience function for locating KLV-encoded EBUCore metadata in the provided header metadata and serializing this metadata to file.

		@param metadata Parsed header metadata structure of the MXF file.
		@param outputfilename Location of the file to write the serialized metadata to.
	*/
	DLLEXPORT void FindAndSerializeEBUCore(mxfpp::HeaderMetadata *metadata, const char* outputfilename);

	/**
	*	Inserts a given descriptive metadata framework set in the provided header metadata structure.\n
		This function first appends the EBUCore DMS scheme label to the metadata Preface set and then 
		adds a static DM track to the MXF timeline, from which the provided __framework__ is referenced.\n
		Currently, the DM track added is assigned a Track ID _10001_ and is given a Track Name _EBU_Core_.

		@param header_metadata The HeaderMetadata structure to which the framework and timeline elements are added.
		@param framework The DM framework set to be added to the MXF timeline.
		@param identificationToAppend Optional Identification metadata set that will be referenced from each metadata set created by this function.
	*/
	DLLEXPORT void InsertEBUCoreFramework(mxfpp::HeaderMetadata *header_metadata, const mxfUL *dmSchemeLabel, 
								mxfpp::DMFramework *framework, mxfpp::Identification *identificationToAppend = NULL);

	/**
	*	Inserts a given list of descriptive metadata frameworks in the provided header metadata structure.\n
		This function adds an Event DM track to the MXF timeline, from which the provided __eventFrameworks__ are weakly referenced.\n
		Currently, the DM track added is assigned a Track ID _10002_ and is given a Track Name _EBU_Core_Parts_.

		@param header_metadata The HeaderMetadata structure to which the framework and timeline elements are added.
		@param eventFrameworks The DM frameworks input set to be added to the MXF timeline. The EventInput structure's Start and 
		Duration fields are used to properly place the DM Segment on the timeline.
		@param identificationToAppend Optional Identification metadata set that will be referenced from each metadata set created by this function.
	*/
	DLLEXPORT void InsertEBUCoreEventFrameworks(mxfpp::HeaderMetadata *header_metadata, std::vector<MXFCustomMetadata::EventInput>& eventFrameworks, mxfpp::Identification *identificationToAppend = NULL);

	/**
	*	Removes EBUCore Descriptive Metadata frameworks from the given header metadata structure.\n
		This removes EBUCore frameworks from ant static or event tracks DM tracks on the MXF timeline, identified by the names _EBU_Core_ or _EBU_Core_Parts.

		@param header_metadata The HeaderMetadata structure from which the frameworks are removed.
	*/
	DLLEXPORT void RemoveEBUCoreFrameworks(mxfpp::HeaderMetadata *header_metadata);

	enum ProgressCallbackLevel {
		FATAL,
		ERROR,
		WARN,
		INFO,
		DEBUG,
		TRACE
	};

	/**
	*	Defines the ways of serializing metadata in MXF files.
	*/
	enum MetadataKind {
		/**	Metadata is encoded using full-featured KLV-encoded metadata element sets (recommended when applicable). */
		KLV_ENCODED,
		/** Metadata is encoded using a single KLV element in which the metadata is written as is. */
		DARK,
		/** A KLV-encoded metadata set is added to the the header metadata with a reference to an external file that contains the actual metadata. */
		SIDECAR,
        /** */
        RP2057,

		NONE
	};

    struct RP2057EmbeddingOptions {
        mxfUL scheme_id;
        const char *lang;
    };

	/**
	*	Embed EBUCore metadata into an MXF file.
		@return Has no return value, but throws an exception when irregularities occur. The caller is informed of any progress by means of the __progress_callback__ argument.
		@param metadataLocation The location of the EBUCore XML metadata document file. This file is parsed using the Xerces-C++ XML parser. 
		The document is assumed to conform to the EBUCore XML schema and is not explicitly validated.
		@param mxfLocation The location of the MXF file in which to embed the EBUCore metadata.
		@param progress_callback A function that is called with updated progress concerning the embedding process. 
		The function is called with the overall progress of the operation in __progress__,  a __message__ that describes the updated status, 
		and the name of the internal __function__ to which the progress update relates (which can be used for debugging purposes).
		@param optWaytoWrite Specifies the way in which the provided metadata will be serialized into the MXF file.
		@param optNoIdentification When true, forces the SDK not to write an additional MXF metadata Identification set to identify the SDK as source of metadata updates.
		@param optForceHeader When true, forces the SDK to write the EBUCore metadata into the header partition, potentially forcing a rewrite of the entire MXF file. 
		In normal operation, the SDK attempts to write the EBUCore metadata into the footer partition, marking the header (and potential body) partitions that contain metadata as
		open and incomplete. This way only the footer paritition and the (small) partition packs must be updated.
	*/
	DLLEXPORT void EmbedEBUCoreMetadata(	const char* metadataLocation, 
							const char* mxfLocation, 
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
							MetadataKind optWaytoWrite = KLV_ENCODED,
							bool optNoIdentification = false, bool optForceHeader = false, const mxfKey *customDarkMetadataKey = NULL,
                            const RP2057EmbeddingOptions *optRP2057 = NULL);

	/**
	*	Embed EBUCore metadata into an MXF file.\n
		This variant of __EmbedEBUCoreMetadata__ accepts a processed XML document, in the form of a Xerces-C++ XML DOM representation. 
		This function can hence be used when the caller wishes to manipulate the EBUCore metadata first, 
		before embedding it in the MXF file and without having to write changes to a physical XML file first.
		@return Has no return value, but throws an exception when irregularities occur. The caller is informed of any progress by means of the __progress_callback__ argument.
		@param metadataDocument A parsed EBUCore XML metadata document, in the form of the DOM representation generated by the Xerces-C++ XML parser. 
		The document is assumed to conform to the EBUCore XML schema and is not explicitly validated.
		@param metadataLocation The logical location of the metadata document, as it will be embedded in the KLV EBUCore metadata. 
		As in this form the __metadataDocument__ doesn't provide an indication of the physical source location of the document, 
		it is be provided separately here. When irrelevant, an empty string "" can be provided.
		@param mxfLocation The location of the MXF file in which to embed the EBUCore metadata.
		@param progress_callback A function that is called with updated progress concerning the embedding process. 
		The function is called with the overall progress of the operation in __progress__,  a __message__ that describes the updated status, 
		and the name of the internal __function__ to which the progress update relates (which can be used for debugging purposes).
		@param optWaytoWrite Specifies the way in which the provided metadata will be serialized into the MXF file.
		@param optNoIdentification When true, forces the SDK not to write an additional MXF metadata Identification set to identify the SDK as source of metadata updates.
		@param optForceHeader When true, forces the SDK to write the EBUCore metadata into the header partition, potentially forcing a rewrite of the entire MXF file. 
		In normal operation, the SDK attempts to write the EBUCore metadata into the footer partition, marking the header (and potential body) partitions that contain metadata as
		open and incomplete. This way only the footer paritition and the (small) partition packs must be updated.
	*/
	DLLEXPORT void EmbedEBUCoreMetadata(	xercesc::DOMDocument& metadataDocument, 
							const char* metadataLocation,
							const char* mxfLocation, 
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
							MetadataKind optWaytoWrite = KLV_ENCODED,
							bool optNoIdentification = false, bool optForceHeader = false, const mxfKey *customDarkMetadataKey = NULL,
                            const RP2057EmbeddingOptions *optRP2057 = NULL);

	/**
	*	Removes EBUCore metadata from an MXF file.\n

		@return Has no return value, but throws an exception when irregularities occur. The caller is informed of any progress by means of the __progress_callback__ argument.
		@param mxfLocation The location of the MXF file from which to remove the EBUCore metadata.
		@param progress_callback A function that is called with updated progress concerning the embedding process. 
		The function is called with the overall progress of the operation in __progress__,  a __message__ that describes the updated status, 
		and the name of the internal __function__ to which the progress update relates (which can be used for debugging purposes).
		@param optNoIdentification When true, forces the SDK not to write an additional MXF metadata Identification set to identify the SDK as source of metadata updates.
		@param optForceHeader When true, forces the SDK to remove the EBUCore metadata from the header partition, potentially forcing a rewrite of the entire MXF file. 
		In normal operation, the SDK attempts to remove the EBUCore metadata from the footer partition, marking the header (and potential body) partitions that contain metadata as
		open and incomplete. This way only the footer paritition and the (small) partition packs must be updated.
	*/

	DLLEXPORT void RemoveEBUCoreMetadata(	const char* mxfLocation,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
							bool optNoIdentification = false, bool optForceHeader = false, 
                            const mxfKey *customDarkMetadataKey = NULL, const mxfUL *rp2057SchemeId = NULL);


	/**
	*	Extract EBUCore metadata from an MXF file.\n
		The SDK consecutively tries to extract the metadata in three ways; from KLV-encoded EBUCore metadata sets, 
		from a sidecar file referenced by the MXF file's metadata, or as 'dark' metadata from a KLV set identified by the appropriate key.\n
		This variant of __ExtractEBUCoreMetadata__ returns a Xerces-C++ XML DOM data structure that can 
		be processed and transformed by the caller, before e.g., being written out to disk.
		@return Returns a reference to a Xerces-C++ XML DOM document representation that conforms to the EBUCore XML schema.
		@param mxfLocation The location of the MXF file in which to extract the EBUCore metadata.
		@param progress_callback A function that is called with updated progress concerning the embedding process. 
		The function is called with the overall progress of the operation in __progress__,  a __message__ that describes the updated status, 
		and the name of the internal __function__ to which the progress update relates (which can be used for debugging purposes).
	*/
	DLLEXPORT xercesc::DOMDocument& ExtractEBUCoreMetadata(
							const char* mxfLocation,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
                            const mxfKey *customDarkMetadataKey = NULL, const mxfUL *rp2057SchemeId = NULL);
	
	/**
	*	Extract EBUCore metadata from an MXF file.\n
		The SDK consecutively tries to extract the metadata in three ways; from KLV-encoded EBUCore metadata sets, 
		from a sidecar file referenced by the MXF file's metadata, or as 'dark' metadata from a KLV set identified by the appropriate key.\n
		@return Has no return value, but throws an exception when irregularities occur. The caller is informed of any progress by means of the __progress_callback__ argument.
		@param mxfLocation The location of the MXF file in which to extract the EBUCore metadata.
		@param metadataLocation The location of the EBUCore XML metadata document file destination. The XML document written conforms to the EBUCore XML schema.
		@param progress_callback A function that is called with updated progress concerning the embedding process. 
		The function is called with the overall progress of the operation in __progress__,  a __message__ that describes the updated status, 
		and the name of the internal __function__ to which the progress update relates (which can be used for debugging purposes).
	*/
	DLLEXPORT void ExtractEBUCoreMetadata(
							const char* mxfLocation,
							const char* metadataLocation,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...), 
                            const mxfKey *customDarkMetadataKey = NULL, const mxfUL *rp2057SchemeId = NULL);

	/**
	*	The way in which metadata should be serialized.
	*/
	enum MetadataOutput {
		/** Serialize to a file. */
		SERIALIZE_TO_FILE,
		/** Serialize to a new Xerces-C++ XML DOM document object. */
		OUTPUT_AS_DOM_DOCUMENT,
		/** Don't serialize. */
		DONT_SERIALIZE
	};

	/**
	*	Abstract class which represents a version of EBUCore processing capabilities. This class will be subclassed for each version of EBUCore.
	*/
	class EBUCoreProcessor {
	public:
		/**
		*	Returns the DM Scheme Universal Label associated with the version of EBUCore supported by this EBUCoreProcessor.

			@returns A pointer to the DM Scheme Universal Label.
		*/
		virtual const mxfUL* GetDescriptiveMetadataScheme() = 0;

		/**
		*	Returns the Dark Set serialization Universal Label associated with the version of EBUCore supported by this EBUCoreProcessor.

			@returns A pointer to the Universal Label.
		*/
		virtual const mxfKey* GetDarkMetadataSetKey() = 0; 

		/**
		*	Registers the version-specific KLV EBUCore metadata extensions with a given MXF metadata data model. 
			These extensions comprise the class structure and ULs associated with metadata sets.\n
			<em>@b Note!</em> Only a single EBUCoreProcessor may register its extensions, unless no overlap in terms of ULs between versions exists.

			@param data_model The MXF metadata data model to which the extensions are to be appended.

		*/
		virtual void RegisterMetadataExtensions(mxfpp::DataModel *data_model) = 0;

		/**
		*	Registers the version-specific KLV EBUCore metadata object factories with a given MXF header metadata structure.
			These object factories allow the MXF metadata processing code to locate appropriate custom metadata set 
			instantiation functions (factories) to call when encountering custom ULs in the metadata. 
			Essentially, when a metadata set with a registered UL is encountered in the MXF metadata, 
			the appropriate factory function will be called to create a metadata set of the correct type.\n
			<em>@b Note!</em> The factory functions must be registered with the empty metadata before actually parsing the MXF file header metadata.\n
			<em>@b Note!</em> Only a single EBUCoreProcessor may register its extensions, unless no overlap in terms of ULs between versions exists.

			@param metadata The HeaderMetadata structure with which the factory functions must be registered.
		*/
		virtual void RegisterFrameworkObjectFactories(mxfpp::HeaderMetadata *metadata) = 0;

		/**
		*	Generates and returns an EBUCore DM Framework object and metadata object structure which refers to an external metadata location.
			
			@returns A pointer to the generated side-car metadata object.
			@param metadataLocation Location of the external metadata document that the generated side-car framework will refer to.
			@param destination The HeaderMetadata structure to which the framework and its connected object should be added.
			@param identificationToAppend The additional MXF metadata Identification set to identify the SDK as source of the EBUCore metadata serialization. Can be NULL if no identification metadata should be appended.
		*/
		virtual mxfpp::DMFramework* GenerateSideCarFramework(const char* metadataLocation, mxfpp::HeaderMetadata *destination, mxfpp::Identification* identificationToAppend) = 0;

		/**
		*	Locates and returns an existing EBUCore DM Framework on the timeline of the provided header metadata, if any.
			
			@returns A pointer to the DM Framework metadata object. Returns NULL if no framework was found.
			@param metadata The header metadata in which to locate the DM Framework.
		*/
		virtual mxfpp::DMFramework* FindMetadataFramework(mxfpp::HeaderMetadata *metadata) = 0;

		/**
		*	Determines whether the provided DM Framework refers to actual EBUCore metadata.
			
			@returns True if the DM Framework object refers to actual metadata. Returns false otherwise, e.g., if the framework refers to an external side-car metadata location.
			@param fw A pointer to the DM Framework.
		*/
		virtual bool FrameworkHasActualMetadata(mxfpp::DMFramework *fw) = 0;

		/**
		*	Determines whether the provided DM Framework refers to an external side-car metadata location.
			
			@returns True if the DM Framework object refers to an external side-car metadata location. Returns false otherwise.
			@param fw A pointer to the DM Framework.
		*/
		virtual bool FrameworkRefersToExternalMetadata(mxfpp::DMFramework *fw) = 0;

		/**
		*	Returns the location of the external side-car metadata that the provided DM Framework referes to. Throws an exception if no such reference exists, which can be verified in advance using the _FrameworkRefersToExternalMetadata_ function.
			
			@returns The location of the external side-car metadata.
			@param fw A pointer to the DM Framework.
		*/
		virtual std::string GetFrameworkExternalMetadataLocation(mxfpp::DMFramework *fw) = 0;
		
		/**
		*	Processes and converts a Xerces-C++ XML DOM representation into a KLV-encode representation which is returned in the form of a DM Framework object.
			
			@returns A pointer to the generated metadata object which refers to the processed and converted EBUCore metadata.
			@param metadataDocument The DOM Document that serves as metadata input for the conversion process.
			@param metadataLocation The external location of the DOM Document.
			@param destination The HeaderMetadata structure to which the DM Framework and its descending metadata sets will be added.
			@param eventFrameworks A vector to which MXF Event Frameworks generated by the converion process are added. These frameworks can be appended to Event Tracks on the MXF timeline.
			@param identificationToAppend The additional MXF metadata Identification set to identify the SDK as source of the EBUCore metadata serialization. Can be NULL if no identification metadata should be appended.
		*/
		virtual mxfpp::DMFramework* Process(xercesc::DOMDocument* metadataDocument, const char* metadataLocation, mxfpp::HeaderMetadata *destination, 
			std::vector<EBUSDK::MXFCustomMetadata::EventInput> &eventFrameworks, mxfpp::Identification* identificationToAppend) = 0;

		/**
		*	Parses and serializes an EBUCore metadata object structure referred to by a given DM Framework 
			and serializes this metadata according to the specified output fashion.
			
			@param fw A pointer to the DM Framework.
			@param outputFashion. The way to serialize the metadata.
			@param metadataLocation The file location to which to write the metadata. 
			Must be provided if _outputFashion_ is SERIALIZE_TO_FILE, and can be NULL otherwise
			@param outputDocument A pointer to a Xerces-C++ XML DOM document object pointer. 
			The pointer will be set to a newly generated DOM document if _outputFashion_ is OUTPUT_AS_DOM_DOCUMENT and can be NULL otherwise.
			@param progress_callback A function that is called with updated progress concerning the serialization process. 
			The function is called with the overall progress of the operation in __progress__,  a __message__ that describes the updated status, 
			and the name of the internal __function__ to which the progress update relates (which can be used for debugging purposes).
		*/
		virtual void ParseAndSerializeMetadata(	mxfpp::DMFramework *fw, 
											EBUSDK::EBUCore::MetadataOutput outputFashion, 
											const char* metadataLocation, 
											xercesc::DOMDocument** outputDocument, 
											void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...)) = 0;
	};

	/**
	*	Returns a newly created instance of the default EBUCoreProcessor object. This object represents processing capabilities for the preferred EBUCore version supported by the SDK.
			
		@returns An instance of the default EBUCoreProcessor.
	*/	
	DLLEXPORT EBUCoreProcessor* GetDefaultEBUCoreProcessor();

	/**
	*	Returns a newly created instance of the EBUCoreProcessor object for processing capabilities for EBUCore metadata declared in the given vector of DM Schemes.
			
		@returns The EBUCoreProcessor that matches the declared DM Schemes, if any. The first matching EBUCoreProcessor is returned, or NULL if no supported EBUCore DM Scheme is found in the _descriptiveMetadataSchemes_ vector.
		@param descriptiveMetadataSchemes A vector with DM Scheme Universal Labals as declared in the header metadata of the MXF file.
	*/
	DLLEXPORT EBUCoreProcessor* GetEBUCoreProcessor(const std::vector<mxfUL>& descriptiveMetadataSchemes);

	/**
	*	Defines the ways of serializing metadata in MXF files.
	*/
	enum EBUCoreProcessors {
		/**	EBUCore v1.4 */
		EBUCORE_1_4,
		/**	EBUCore v1.5 */
		EBUCORE_1_5
	};

	/**
	*	Returns a newly created instance of the EBUCoreProcessor object for processing capabilities for the given EBUCore metadata version.
			
		@returns The EBUCoreProcessor that matches the given enumeration value.
		@param version The version of EBUCoreProcessor to be returned.
	*/
	DLLEXPORT EBUCoreProcessor* GetEBUCoreProcessor(const EBUCoreProcessors version);

	/**
	*	Determines whether the provided KLV label is supported by the SDK as a Descriptive Metadata Scheme label for EBUCore metadata.

		@returns Whether the label is supported by the SDK.
		@param label The label to be investigaged.
	*/
	DLLEXPORT bool IsSupportedEBUCoreMetadataScheme(const mxfUL* label);

	/**
	*	Enumerates and adds to the given vector each of the KLV set keys supported by the SDK as keys for EBUCore dark metadata.

		@param darkSetKeys A references to the vector to which the supported keys will be added.
	*/
	DLLEXPORT void EnumerateSupportedEBUCoreDarkSetKeys(std::vector<const mxfKey*>& darkSetKeys);

	} // namespace EBUCore

} // namespace EBUSDK

#endif
