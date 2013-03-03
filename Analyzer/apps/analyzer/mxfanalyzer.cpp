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
 
#include <Analyzer.h>

#include <MXFCustomMetadata.h>
#include <XercesUtils.h>

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

using namespace xercesc;

using namespace EBUSDK::Utils;
using namespace EBUSDK::Analyzer;

bool check_file_exists(std::string filename)
{
    FILE *file = fopen(filename.c_str(), "rb");
    if (!file)
        return false;

    fclose(file);
    return true;
}

static void usage(const char *cmd)
{
    //fprintf(stderr, "mxfanalyzer%s\n", get_version_info().c_str());
	fprintf(stderr, "mxfanalyzer\n");
    fprintf(stderr, "Usage: %s <<options>> <filename>\n", cmd);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, " -h | --help           Show usage and exit\n");
    fprintf(stderr, " -v | --version        Print version info\n");
    //fprintf(stderr, " -l <file>             Log filename. Default log to stderr/stdout\n");
    //fprintf(stderr, " -i                    Print file information to stdout\n");
    fprintf(stderr, " --report <file>       Write analysis report to file\n");
    fprintf(stderr, " --physical            Output a physical layout of the header metadata\n");
    fprintf(stderr, " --logical             Output a logical layout of the header metadata (default)\n");
    fprintf(stderr, " --metadata            Perform only a metadata analysis (default)\n");
    fprintf(stderr, " --mux                 Perform an analysis on the entire MXF file mux\n");
    fprintf(stderr, " --deepindex           Perform a deep index table analysis\n");
}

int main(int argc, char* argv[])
{
	int cmdln_index;
	const char *report_filename = 0;
    std::vector<const char *> filenames;

	AnalyzerConfig cfg;
	cfg.AnalysisType = AnalyzerConfig::METADATA;
	cfg.MetadataAnalysisType = AnalyzerConfig::LOGICAL;
	cfg.DeepIndexTableAnalysis = false;

    if (argc == 1) {
        usage(argv[0]);
        return 0;
    }
	
	for (cmdln_index = 1; cmdln_index < argc; cmdln_index++)
    {
        if (strcmp(argv[cmdln_index], "--help") == 0 ||
            strcmp(argv[cmdln_index], "-h") == 0)
        {
            usage(argv[0]);
            return 0;
        }
        else if (strcmp(argv[cmdln_index], "--version") == 0 ||
                 strcmp(argv[cmdln_index], "-v") == 0)
        {
            if (argc == 2) {
                //printf("%s\n", get_version_info().c_str());
                return 0;
            }
            //do_print_version = true;
        }
        /*else if (strcmp(argv[cmdln_index], "-l") == 0)
        {
            if (cmdln_index + 1 >= argc)
            {
                usage(argv[0]);
                fprintf(stderr, "Missing argument for option '%s'\n", argv[cmdln_index]);
                return 1;
            }
            log_filename = argv[cmdln_index + 1];
            cmdln_index++;
        }*/
        else if (strcmp(argv[cmdln_index], "--physical") == 0)
        {
			cfg.MetadataAnalysisType = AnalyzerConfig::PHYSICAL;
        }
		else if (strcmp(argv[cmdln_index], "--logical") == 0)
        {
			cfg.MetadataAnalysisType = AnalyzerConfig::LOGICAL;
        }
		else if (strcmp(argv[cmdln_index], "--metadata") == 0)
        {
			cfg.AnalysisType = AnalyzerConfig::METADATA;
        }
		else if (strcmp(argv[cmdln_index], "--mux") == 0)
        {
			cfg.AnalysisType = AnalyzerConfig::MXF_MUX;
        }
		else if (strcmp(argv[cmdln_index], "--deepindex") == 0)
        {
			cfg.DeepIndexTableAnalysis = true;
        }
		else if (strcmp(argv[cmdln_index], "--report") == 0)
        {
            if (cmdln_index + 1 >= argc)
            {
                usage(argv[0]);
                fprintf(stderr, "Missing argument for option '%s'\n", argv[cmdln_index]);
                return 1;
            }
			report_filename = argv[cmdln_index + 1];
            cmdln_index++;
        }
        else
        {
            break;
        }
    }

	if (cmdln_index + 1 > argc) {
        usage(argv[0]);
        fprintf(stderr, "Missing parameters\n");
        return 1;
    } else if (cmdln_index >= argc) {
        usage(argv[0]);
        fprintf(stderr, "No <filename> given\n");
        return 1;
    }

    for (; cmdln_index < argc; cmdln_index++) {
        if (!check_file_exists(argv[cmdln_index])) {
            if (argv[cmdln_index][0] == '-') {
                usage(argv[0]);
                fprintf(stderr, "Unknown argument '%s'\n", argv[cmdln_index]);
            } else {
                fprintf(stderr, "Failed to open input filename '%s'\n", argv[cmdln_index]);
            }
            return 1;
        }
        filenames.push_back(argv[cmdln_index]);
    }

	AnalyzeMXFFile(filenames[0], report_filename, cfg);
	
	return 0;
}

