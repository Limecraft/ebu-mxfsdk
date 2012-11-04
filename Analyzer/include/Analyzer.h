
#ifndef __EBUSDK_ANALYZER_H__
#define __EBUSDK_ANALYZER_H__

#include <memory>

#include <xercesc/dom/DOMDocument.hpp>

using namespace xercesc;

namespace EBUSDK {
	namespace Analyzer {

		struct AnalyzerConfig {
			enum {
				METADATA,
				MXF_MUX
			} AnalysisType;
			enum { 		
				LOGICAL,
				PHYSICAL
			} MetadataAnalysisType;
		};

		std::auto_ptr<DOMDocument> AnalyzeMXFFile(const char* mxfLocation, AnalyzerConfig configuration);

	}
}

#endif
