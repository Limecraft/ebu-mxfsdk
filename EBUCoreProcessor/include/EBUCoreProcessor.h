
#include <libMXF++/MXF.h>

#include <xercesc/dom/DOMDocument.hpp>

/**
*	EBU MXF SDK main namespace for EBUCore functionality.
*/
namespace EBUCore
{
	/**
	*	Generates an MXF Identification metadata set that can be referred to by new and updated metdata sets in the MXF file.\n
		The following information is contained in the set:\n
		- Company Name: "EBU"
		- Product Name: "EBUCore SDK"
		- ProductUID: { 0xda, 0xe5, 0x92, 0x18, 0xaf, 0x8d, 0x47, 0xd4, 0xa2, 0x16, 0xb6, 0xc6, 0x48, 0xea, 0x54, 0x8c }

		@return Returns the generated Identification set.
		@param destination The HeaderMetadata structure to which the Identification set will be added.
	*/
	mxfpp::Identification* GenerateEBUCoreIdentificationSet(mxfpp::HeaderMetadata *destination);

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
	mxfpp::DMFramework* Process(const char* location, mxfpp::HeaderMetadata *destination, mxfpp::Identification *identificationToAppend = NULL);

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

	/**
	*	Inserts a given descriptive metadata framework set in the provided header metadata structure.\n
		This function first appends the EBUCore DMS scheme label to the metadata Preface set and then 
		adds a static DM track to the MXF timeline, from which the provided __framework__ is referenced.\n
		Currently, the DM track added is assigned a Track ID _10001_ and is given a Track Name _EBU_Core_.

		@param header_metadata The HeaderMetadata structure to which the framework and timeline elements are added.
		@param framework The DM framework set to be added to the MXF timeline.
		@param identificationToAppend Optional Identification metadata set that will be referenced from each metadata set created by this function.
	*/
	void InsertEBUCoreFramework(mxfpp::HeaderMetadata *header_metadata, mxfpp::DMFramework *framework, mxfpp::Identification *identificationToAppend = NULL);

	/**
	*	Buffers the index entries of the given __partition__ in a ByteArray and returns the size of the index 
		entries buffered and the first byte of the header metadata in the given __partition__.

		@returns Returns the location of the first byte of the header metadata in the given __partition__. 
		This position is location behind the partition pack set and any KLV filler elements that follow it.
		@param mFile An MXF file structure opened with (at least) read access.
		@param partition The partition for which the index entries must be buffered.
		@param index_bytes A reference to a pre-allocated ByteArray structure to hold the buffered index bytes.
		@param index_length A pointer to an integer that will receive the length of the index bytes buffered when the function returns.
	*/
	uint64_t BufferIndex(mxfpp::File* mFile, mxfpp::Partition* partition, bmx::ByteArray& index_bytes, uint32_t* index_length);

	/**
	*	Serializes KLV-encoded header metadata to a memory-backed file. Its purpose is to write obtain 
		a linear buffer of serialized metadata of which the size is known, 
		before committing this buffer (i.e., the memory-backed file) to a disk-backed file.

		<em>@b Note!</em> The original disk-backed file is also provided to this function such that dark metadata sets not parsed by the header metadata
		can also be transferred to the memory-backed file. As such, this function is used in scenario's where existing MXF files are updated with modified metadata.

		@returns Returns the total header metadata bytes written to the memory-backed file.
		@param mFile The base MXF file structure opened with read/write access.
		@param destMemFile A pointer that will receive a reference to the memory-backed MXF file structure created during the serialization process.
		@param mHeaderMetadata The header metadata that is to be serialized.
		@param metadata_read_position The offset in the __mFile__ from where the original header metadata is to be read. This is the actual starting position
		of the metadata, beyond any preceeding KLV Filler elements.
		@param metadata_write_position The offset in the __mFile__ where the new header metadata is to be written. This is the actual starting position
		of the metadata, beyond any preceeding KLV Filler elements.
		@param metadataDestinationPartition The partition in the __mFile__ to which the metadata is being written.
		@param metadataSourcePartition The partition in the __mFile__ from which the updated metadata was obtained.
	*/
	uint64_t WriteMetadataToMemoryFile(mxfpp::File* mFile, MXFMemoryFile **destMemFile, mxfpp::HeaderMetadata *mHeaderMetadata, uint64_t metadata_read_position, uint64_t metadata_write_position, mxfpp::Partition* metadataDestinationPartition, mxfpp::Partition* metadataSourcePartition);

	/**
	*	Writes KLV-encoded header metadata to an MXF file.

		@returns Returns the total header metadata bytes written to the MXF file.
		@param mFile The base MXF file structure opened with read/write access.
		@param mHeaderMetadata The header metadata that is to be serialized.
		@param metadata_read_position The offset in the __mFile__ from where the original header metadata is to be read. This is the actual starting position
		of the metadata, beyond any preceeding KLV Filler elements.
		@param metadata_write_position The offset in the __mFile__ where the new header metadata is to be written. This is the actual starting position
		of the metadata, beyond any preceeding KLV Filler elements.
		@param shiftFileBytesIfNeeded Dictates whether file bytes should be shifted further down the file 
		to accomodate metadata that has grown from what was originally in the file. 
		If _false_, however, file bytes are written disregarding any previous file content.\n
		<em>@b Note!</em> Use this parameter with care as incorrect use can corrupt the MXF file.
		@param metadataDestinationPartition The partition in the __mFile__ to which the metadata is being written.
		@param metadataSourcePartition The partition in the __mFile__ from which the updated metadata was obtained.
	*/
	uint64_t WriteMetadataToFile(mxfpp::File* mFile, mxfpp::HeaderMetadata *mHeaderMetadata, uint64_t metadata_read_position, uint64_t metadata_write_position, bool shiftFileBytesIfNeeded, mxfpp::Partition* metadataDestinationPartition, mxfpp::Partition* metadataSourcePartition);

	/**
	*	Abstract Utility class that defines an interface for writing dark metadata (i.e., blobs of bytes) to an MXF file.
	*/
	class MXFFileDarkSerializer {
	public:
		/**
		*	Writes the dark metadata to the given MXF file. The file may be assumed to be ready to receive the metadata and positioned at the start
			of the value of a specially prepared KLV element. 

			@returns The number of dark bytes written to the MXF file.
			@param f The MXF file to which to write the dark bytes.
		*/
		virtual uint64_t WriteToMXFFile(mxfpp::File *f) = 0;
		virtual ~MXFFileDarkSerializer() {};
	};

	/**
	*	Serializes dark header metadata to a memory-backed file, at the end of original metadata in the __metadataSourcePartition__ in a single KLV element. 
		Its purpose is to write obtain a linear buffer of serialized metadata of which the size is known, 
		before committing this buffer (i.e., the memory-backed file) to a disk-backed file.

		@returns Returns the total header metadata bytes written to the memory-backed file.
		@param mFile The base MXF file structure opened with read/write access.
		@param destMemFile A pointer that will receive a reference to the memory-backed MXF file structure created during the serialization process.
		@param metadata The dark metadata serializer that will write to the memory-backed file.
		@param metadata_read_position The offset in the __mFile__ from where the original header metadata is to be read. This is the actual starting position
		of the metadata, beyond any preceeding KLV Filler elements.
		@param metadata_write_position The offset in the __mFile__ where the new header metadata is to be written. This is the actual starting position
		of the metadata, beyond any preceeding KLV Filler elements.
		@param metadataDestinationPartition The partition in the __mFile__ to which the metadata is being written.
		@param metadataSourcePartition The partition in the __mFile__ from which the updated metadata was obtained.
	*/
	uint64_t WriteDarkMetadataToMemoryFile(mxfpp::File* mFile, MXFMemoryFile **destMemFile, MXFFileDarkSerializer& metadata, uint64_t metadata_read_position, uint64_t metadata_write_position, mxfpp::Partition* metadataDestinationPartition, mxfpp::Partition* metadataSourcePartition);
	
	/**
	*	Writes dark header metadata to an MXF file.

		@returns Returns the total header metadata bytes written to the MXF file.
		@param mFile The base MXF file structure opened with read/write access.
		@param metadata The dark metadata serializer that will write to the memory-backed file.
		@param metadata_read_position The offset in the __mFile__ from where the original header metadata is to be read. This is the actual starting position
		of the metadata, beyond any preceeding KLV Filler elements.
		@param metadata_write_position The offset in the __mFile__ where the new header metadata is to be written. This is the actual starting position
		of the metadata, beyond any preceeding KLV Filler elements.
		@param shiftFileBytesIfNeeded Dictates whether file bytes should be shifted further down the file 
		to accomodate metadata that has grown from what was originally in the file. 
		If _false_, however, file bytes are written disregarding any previous file content.\n
		<em>@b Note!</em> Use this parameter with care as incorrect use can corrupt the MXF file.
		@param metadataDestinationPartition The partition in the __mFile__ to which the metadata is being written.
		@param metadataSourcePartition The partition in the __mFile__ from which the updated metadata was obtained.
	*/
	uint64_t WriteDarkMetadataToFile(mxfpp::File* mFile, MXFFileDarkSerializer& metadata, uint64_t metadata_read_position, uint64_t metadata_write_position, bool shiftFileBytesIfNeeded, mxfpp::Partition* metadataDestinationPartition, mxfpp::Partition* metadataSourcePartition);

	/**
	*	Finds the last KLV filler element in the given __partition__.

		@returns Returns the byte position of the last KLV filler element in the given partition.
		@param mFile The MXF file structure opened with (at least) read access.
		@param partition The partition in which to locate the last KLV filler element.
		@param partitionSectionOffset Pointer to the integer that receives the byte position from where the last KLV filler was searched for. 
		Depending on the configuration of the __partition__, this can be immediatelly behind the partition pack, behind the header metadata (if present), or
		behind the partition's index entries (if present). This can be the same value as returned by this function, but not necessarily in case multiple filler
		elements are found.
		@param extractedFileSize Pointer to the integer that receives the length of the provided MXF file.
	*/
	int64_t FindLastPartitionFill(mxfpp::File* mFile, mxfpp::Partition* partition, int64_t* partitionSectionOffset, int64_t *extractedFileSize = NULL);
	
	/**
	*	Shifts bytes in an MXF file from a given posiition by a given offset.

		@param mFile The MXF file structure opened with read/write access.
		@param shiftPosition The byte position in the file from which the shift operation will take place.
		@param shiftOffset The byte offset by how much each file byte must be shifted.
	*/
	void ShiftBytesInFile(mxfpp::File* mFile, int64_t shiftPosition, int64_t shiftOffset);

	/**
	*	From a given set of partitions, locates the partition which has the preferred header metadata. Additionally, also locates the header and footer partition.\n
		The preferred metadata is located as follows. 
		- If the footer partition is marked as closed and contains header metadata, it is selected. 
		- Else, if the header partition is marked as closed and contains header metadata, it is selected.
		- Else, if any of the body partitions is marked as closed and contains header metadata, it is selected. The last body partition to match is chosen.
		- Else, if there are any open partitions that contain metadata, the last of these is selected.
		
		@returns Returns the partition that contains the preferred metadata, or NULL if no applicable partition could be found.
		@param partitions The list of partitions from which the selection is made, typically all partitions of an MXF file.
		@param headerPartition Pointer to variable that will be assigned the header partition of the list.
		@param footerPartition Pointer to variable that will be assigned the footer partition of the list.
	*/
	mxfpp::Partition* FindPreferredMetadataPartition(const std::vector<mxfpp::Partition*>& partitions, mxfpp::Partition** headerPartition, mxfpp::Partition** footerPartition);

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
		SIDECAR
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
	void EmbedEBUCoreMetadata(	const char* metadataLocation, 
							const char* mxfLocation, 
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
							MetadataKind optWaytoWrite = KLV_ENCODED,
							bool optNoIdentification = false, bool optForceHeader = false);

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
	void EmbedEBUCoreMetadata(	xercesc::DOMDocument& metadataDocument, 
							const char* metadataLocation,
							const char* mxfLocation, 
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
							MetadataKind optWaytoWrite = KLV_ENCODED,
							bool optNoIdentification = false, bool optForceHeader = false);

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
	xercesc::DOMDocument& ExtractEBUCoreMetadata(
							const char* mxfLocation,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...));
	
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
	void ExtractEBUCoreMetadata(
							const char* mxfLocation,
							const char* metadataLocation,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...));

}