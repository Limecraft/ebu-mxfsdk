// Analyzer.cpp : Defines the entry point for the console application.
//

#include <Analyzer.h>

#include <MXFCustomMetadata.h>
#include <XercesUtils.h>

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

using namespace xercesc;

using namespace EBUSDK::Utils;
using namespace EBUSDK::Analyzer;

int main(int argc, char* argv[])
{
	AnalyzerConfig cfg;
	cfg.AnalysisType = AnalyzerConfig::MXF_MUX;
	cfg.MetadataAnalysisType = AnalyzerConfig::LOGICAL;
	cfg.DeepIndexTableAnalysis = false;

	std::auto_ptr<DOMDocument> doc = AnalyzeMXFFile(argv[1], cfg);

	LocalFileFormatTarget f("out.xml");
	SerializeXercesDocument(*doc, f);

	return 0;
}

