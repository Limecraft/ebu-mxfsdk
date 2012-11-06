
#ifndef __EBUSDK_ANALYZER_H__
#define __EBUSDK_ANALYZER_H__

#include <memory>

#include <xercesc/dom/DOMDocument.hpp>

using namespace xercesc;

/**
*	EBU MXF SDK main namespace.
*/
namespace EBUSDK {

	/**
	 *	EBU MXF SDK Namespace for analyzer functionality.
	 */
	namespace Analyzer {

		/**
		*	Analyzer configuration structure to be provided when the Analyzer is invoked.
		*/
		struct AnalyzerConfig {
			/**
			*	The overall type of analysis to be performed on the MXF file.
			*/
			enum AnalysisType {
				/**
				*	Perform only a metadata analysis, using the most preferrable metadata partition.
				*/
				METADATA,
				/**
				*	Perform an analysis on the entire MXF file mux, including all partitions and the random index pack (RIP). 
					Additionally, for each partition, the partition pack and both the header metadata and index tables will be analyzed.
				*/
				MXF_MUX
			} AnalysisType;
			/**
			*	The type of metadata analysis to be performed on the MXF file.
			*/
			enum MetadataAnalysisType { 		
				/**
				*	Perform a logical layout of the header metadata in which the XML report reflects a tree structure similar 
					to the one represented by the header metadata with all strong references resolved and used as parent for child metadata sets.
				*/
				LOGICAL,
				/**
				*	Perform a physical layout of the header metadata in which all metadata sets are listed one after the other in a flat list. 
					Strong references are not resolved, the reference is indicated by means the TargetInstance attribute with the target InstanceUID UUID as value.
				*/
				PHYSICAL
			} MetadataAnalysisType;
			/**
				When true, the analyzer performs a deep index table analysis, including all Delta and Index entries in each index table segment. 
				When false, only information about index table segments is returned.
			*/
			bool DeepIndexTableAnalysis;
		};

		/**
		*	Analyzes the MXF file at __mxfLocation__ and returns the resulting analysis report in a SMPTE ST-434-compliant DOM document object.

			@return Returns a smart pointer to the MXF file anaysis report in the form of a Xerces-C DOM document object.
			@param mxfLocation Location of the MXF file.
			@param configuration The configuration structure of the analyzer.
		*/
		std::auto_ptr<DOMDocument> AnalyzeMXFFile(const char* mxfLocation, AnalyzerConfig configuration);

		/**
		*	Analyzes the MXF file at __mxfLocation__ and writes the resulting analysis report in a SMPTE ST-434-compliant XML document at __reportLocation__.

			@param mxfLocation Location of the MXF file.
			@param reportLocation Location of the report XML document.
			@param configuration The configuration structure of the analyzer.
		*/
		void AnalyzeMXFFile(const char* mxfLocation, const char* reportLocation, AnalyzerConfig configuration);
	}
}

#endif
