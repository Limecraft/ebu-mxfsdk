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
 
#ifndef __EBUSDK_MXFCUSTOMMETADATA_H__
#define __EBUSDK_MXFCUSTOMMETADATA_H__

#include <fstream>
#include <memory>

#include <libMXF++/MXF.h>
#include <bmx/ByteArray.h>

/**
*	EBU MXF SDK main namespace.
*/
namespace EBUSDK {

	/**
	 *	EBU MXF SDK Namespace for generic functionality that deals with custom MXF metadata.
	 */
	namespace MXFCustomMetadata {

	/**
	*	Abstract utility class which defines an interface for modifying instances of the MXF InterchangeObject and its subclasses.
	*/
	class ObjectModifier {
	public:
		/** Modify the given InterchangeObject in a subclass-specific fashion. */
		virtual void Modify(mxfpp::InterchangeObject *obj) = 0;
	};

	/**
	*	Class which modifies MXF InterchangeObjects by setting their GenerationUID field to a value given during construction.
	*/
	class GenerationUIDAppender : public ObjectModifier {
		mxfUUID _generationUID;
	public:
		GenerationUIDAppender(mxfUUID GenerationUID) {
			_generationUID = GenerationUID;
		}
		void Modify(mxfpp::InterchangeObject *obj) {
			obj->setGenerationUID(_generationUID);
		}
	};

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
	uint64_t WriteMetadataToMemoryFile(mxfpp::File* mFile, MXFMemoryFile **destMemFile, mxfpp::HeaderMetadata *mHeaderMetadata, uint64_t metadata_read_position, uint64_t metadata_write_position, mxfpp::Partition* metadataDestinationPartition, mxfpp::Partition* metadataSourcePartition, std::vector<const mxfKey*>& darkElementKeysToIgnore);

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
	uint64_t WriteMetadataToFile(mxfpp::File* mFile, mxfpp::HeaderMetadata *mHeaderMetadata, uint64_t metadata_read_position, uint64_t metadata_write_position, bool shiftFileBytesIfNeeded, mxfpp::Partition* metadataDestinationPartition, mxfpp::Partition* metadataSourcePartition, std::vector<const mxfKey*>& darkElementKeysToIgnore);

	/**
	*	Abstract utility class which defines an interface for writing dark metadata (i.e., blobs of bytes) to an MXF file.
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
        /** Tries to get the (file) size of the dark metadata. No data is actually written out at this stage. 
        
            @returns The number of dark bytes contained in the metadata.
        */
        virtual uint64_t ProbeSize();
	};

	/**
		Utility class for writing dark metadata to MXF files, using dark metadata read from a file. 
	*/
	class DarkFileSerializer : public MXFFileDarkSerializer {
		std::ifstream in;
        uint64_t probe_size;
	public:
		/**
			Constructor. Opens the file at given location.

			@param metadataLocation Location of the dark metadata file.
		*/
		DarkFileSerializer(const char* metadataLocation);
		uint64_t WriteToMXFFile(mxfpp::File *f);
		virtual ~DarkFileSerializer();

        uint64_t ProbeSize() { return probe_size; }
	};

	/**
	*	Serializes dark header metadata to a memory-backed file, at the end of original metadata in the __metadataSourcePartition__ in a single KLV element. 
		Its purpose is to write obtain a linear buffer of serialized metadata of which the size is known, 
		before committing this buffer (i.e., the memory-backed file) to a disk-backed file.

		@returns Returns the total header metadata bytes written to the memory-backed file.
		@param mFile The base MXF file structure opened with read/write access.
		@param destMemFile A pointer that will receive a reference to the memory-backed MXF file structure created during the serialization process.
		@param metadata The dark metadata serializer that will write to the memory-backed file.
		@param darkMetadataSetKey The key to use as dark metadata KLV packet key.
		@param metadata_read_position The offset in the __mFile__ from where the original header metadata is to be read. This is the actual starting position
		of the metadata, beyond any preceeding KLV Filler elements.
		@param metadata_write_position The offset in the __mFile__ where the new header metadata is to be written. This is the actual starting position
		of the metadata, beyond any preceeding KLV Filler elements.
		@param metadataDestinationPartition The partition in the __mFile__ to which the metadata is being written.
		@param metadataSourcePartition The partition in the __mFile__ from which the updated metadata was obtained.
	*/
	uint64_t WriteDarkMetadataToMemoryFile(mxfpp::File* mFile, MXFMemoryFile **destMemFile, MXFFileDarkSerializer& metadata, const mxfKey *darkMetadataSetKey, uint64_t metadata_read_position, uint64_t metadata_write_position, mxfpp::Partition* metadataDestinationPartition, mxfpp::Partition* metadataSourcePartition);
	
	/**
	*	Writes dark header metadata to an MXF file.

		@returns Returns the total header metadata bytes written to the MXF file.
		@param mFile The base MXF file structure opened with read/write access.
		@param metadata The dark metadata serializer that will write to the memory-backed file.
		@param darkMetadataSetKey The key to use as dark metadata KLV packet key.
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
	uint64_t WriteDarkMetadataToFile(mxfpp::File* mFile, MXFFileDarkSerializer& metadata, const mxfKey *darkMetadataSetKey, uint64_t metadata_read_position, uint64_t metadata_write_position, bool shiftFileBytesIfNeeded, mxfpp::Partition* metadataDestinationPartition, mxfpp::Partition* metadataSourcePartition);

	/**
	*	Removes a 'tree' of metadata sets from the given header metadata.\n
		The tree removed from the header metadata comprises all metadata sets reachable recursively from the initial set through strong references. Weak references are not followed as they do not imply ownership.
	*/
	void RemoveMetadataSetTree(mxfpp::HeaderMetadata *header_metadata, mxfpp::MetadataSet *startSet);

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

	/**
	*	Rewrite the KLV partition pack for the given partition.

		@param mxfFile The MXF file structure opened with read/write access.
		@param partition The partition pack data structure to be rewritten to the file. The partition pack is written to the position indicated by the _thisPartition_ member.
		@param forceSimilar When true, this function tries to mimic the original parition pack is closely as possible, incl. by rewriting the length value of identical length.
	*/
	void RewritePartitionPack(mxfpp::File *mxfFile, mxfpp::Partition *partition, bool forceSimilar = false);

	/**
	*	Retrieve all 'static' descriptive metadata frameworks contained int the given Material Package object.

		@returns A vector of references to the located framework objects.
		@param mp The material package structure in which the frameworks must be found, as the framework of a timeline track.
	*/
	std::vector<mxfpp::DMFramework*> GetStaticFrameworks(mxfpp::MaterialPackage *mp);

	/**
	*	Appends a descriptive metadata scheme Universal Label to the given header metadata object, where it is written into the Preface metadata set.
		
		@param header_metadata The header metadata to which to append the DM framework.
		@param scheme_label The Universal Label of the descriptive metadata scheme.
	*/
	void AppendDMSLabel(mxfpp::HeaderMetadata *header_metadata, mxfUL scheme_label);

	/**
	*	Inserts the given descriptive metadata framework into the MXF timeline of the provided header metadata.\n
		The framework is inserted as the framework for a newly created DM Static Track (identified by the __track_id__ and __track_name__ parameters) in the Material Package of the metadata. 
		The structure built is as follows: [Preface] -> [ContentStorage] -> [Material Package] -> [DM Static Track] -> [Sequence] -> [DMSegment] -> [__framework__].
		
		@param header_metadata The header metadata to which to append the DM framework.
		@param track_id The identifier given to the newly created Static Track.
		@param track_name The name given to the newly created Static Track.
		@param framework The framework attached to DM Segment of the Static Track.
		@param mod An optional object modifier which updates all metadata objects created by this function, e.g., for unique identification purposes.
	*/
	void InsertFramework(mxfpp::HeaderMetadata *header_metadata, uint32_t track_id, std::string track_name, mxfpp::DMFramework *framework, ObjectModifier *mod = NULL);

	/**
	  * Looks throught the material package of the given __header_metadata__ and locates the edit rate most appropriate to the overall package. 
		The edit rate is selected from timeline tracks in the following order: timecode tracks, video tracks or audio tracks. 
		The edit rate of the first of these tracks found is used.
	
		@returns The edit rate, or a special rational {-1, 0} if no valid value was found.
		@param header_metadata The header metadata from which to select the material package.
	  */
	mxfRational FindMaterialPackageEditRate(mxfpp::HeaderMetadata *header_metadata);

	/**
	  *	Structure for defining temporal location of a DM framework on an MXF timeline. Used as input to the __InsertEventFrameworks__ function.
	  */
	struct EventInput {
		mxfPosition start;
		mxfLength duration;
		mxfpp::DMFramework *framework;
	};

	/**
	*	Inserts a given list of descriptive metadata frameworks into the MXF timeline of the provided header metadata.\n
		The frameworks are attached to a newly created DM Event Track (identified by the __track_id__ and __track_name__ parameters) in the Material Package of the metadata. 
		The structure built is as follows: [Preface] -> [ContentStorage] -> [Material Package] -> [DM Event Track] -> [Sequence] -> [DMSegment],... -> [__frameworks__[i]]. 
		The EventInput members are used to properly position the created DMSegments on the Event timeline.
		
		@param header_metadata The header metadata to which to append the DM framework.
		@param track_id The identifier given to the newly created Event Track.
		@param track_name The name given to the newly created Event Track.
		@param frameworks A list of frameworks to be attached to series of DM Segments of the Event Track.
		@param mod An optional object modifier which updates all metadata objects created by this function, e.g., for unique identification purposes.
	*/
	void InsertEventFrameworks(mxfpp::HeaderMetadata *header_metadata, uint32_t track_id, std::string track_name, std::vector<EventInput> &frameworks, ObjectModifier *mod = NULL);


    namespace RP2057 {

        /**
	    *	Abstract utility class which defines an interface for writing dark metadata (i.e., blobs of bytes) to an MXF file.
	    */
	    class MXFFileDarkXMLSerializer : public MXFFileDarkSerializer {
	    public:
		    virtual bmx::TextEncoding GetTextEncoding();
            virtual bmx::ByteOrder GetByteOrder();
            virtual std::string GetLanguageCode();
            virtual std::string GetNamespace();
            virtual std::string GetData();
	    };

    }


	} // namespace MXFCustomMetadata

} // namespace EBUSDK

#endif
