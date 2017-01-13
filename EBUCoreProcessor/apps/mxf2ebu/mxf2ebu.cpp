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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define __STDC_FORMAT_MACROS

#include <cstdio>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <algorithm>

#include <bmx/mxf_reader/MXFFileReader.h>
#include <bmx/mxf_reader/MXFGroupReader.h>
#include <bmx/mxf_reader/MXFSequenceReader.h>
#include <bmx/mxf_reader/MXFFrameMetadata.h>
#include <bmx/essence_parser/SoundConversion.h>
#include <bmx/MD5.h>
#include <bmx/CRC32.h>
#include <bmx/MXFUtils.h>
#include <bmx/Utils.h>
#include <bmx/as11/AS11Info.h>
#include <bmx/BMXException.h>
#include <bmx/Logging.h>
#include <AppUtils.h>

#if defined(_WIN32)
#include <mxf/mxf_win32_file.h>
#endif

#include <EBUCoreProcessor.h>
#include <Version.h>

using namespace std;
using namespace bmx;
using namespace mxfpp;

using namespace EBUSDK;

static string get_version_info()
{
    char buffer[256];
    sprintf(buffer, "mxf2ebu, %s v%s, %s %s (scm %s)",
            EBUSDK::get_library_name().c_str(),
            EBUSDK::get_version_string().c_str(),
            __DATE__, __TIME__,
            EBUSDK::get_scm_version_string().c_str());
    return buffer;
}

static void usage(const char *cmd)
{
    fprintf(stderr, "%s\n", get_version_info().c_str());
    fprintf(stderr, "Usage: %s <<options>> <filename>\n", cmd);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, " -h | --help           Show usage and exit\n");
    fprintf(stderr, " -v | --version        Print version info\n");
    fprintf(stderr, " -l <file>             Log filename. Default log to stderr/stdout\n");
    fprintf(stderr, " --ebu-core <file>     Write embedded EBU Core metadata to file\n");
    fprintf(stderr, " --dark-key            Use this custom dark metadata key when searching for dark embedded metadata.\n");
    fprintf(stderr, "                       The provided key should a SMPTE UL, in the format ....\n");
}

void progress_cb(float progress, EBUCore::ProgressCallbackLevel level, const char *function, const char *msg_format, ...) {
	// append a newline to the msg_format string
	int len = strlen(msg_format);
	char* newline_msg_format =(char*)malloc((len+2) * sizeof(char));
	strncpy(newline_msg_format, msg_format, len); newline_msg_format[len] = 0;
	strncat(newline_msg_format, "\n", 1);

	va_list p_arg;
    va_start(p_arg, msg_format);
	switch (level) {
	case EBUCore::INFO:
		log_info(newline_msg_format, p_arg); return;
	case EBUCore::DEBUG:
	case EBUCore::TRACE:
		log_debug(newline_msg_format, p_arg); return;
	case EBUCore::ERROR:
		log_error(newline_msg_format, p_arg); return;
	case EBUCore::WARN:
		log_warn(newline_msg_format, p_arg); return;
	};
	va_end(p_arg);

	free(newline_msg_format);
}

int main(int argc, const char** argv)
{
    const char *log_filename = 0;
    std::vector<const char *> filenames;
    bool do_print_version = false;
    const char *ebucore_filename = 0;
    bool do_use_dark_metadata_key = false;
    mxfKey darkMetadataKey;
    int cmdln_index;

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
                printf("%s\n", get_version_info().c_str());
                return 0;
            }
            do_print_version = true;
        }
        else if (strcmp(argv[cmdln_index], "-l") == 0)
        {
            if (cmdln_index + 1 >= argc)
            {
                usage(argv[0]);
                fprintf(stderr, "Missing argument for option '%s'\n", argv[cmdln_index]);
                return 1;
            }
            log_filename = argv[cmdln_index + 1];
            cmdln_index++;
        }
		else if (strcmp(argv[cmdln_index], "--ebu-core") == 0)
        {
            if (cmdln_index + 1 >= argc)
            {
                usage(argv[0]);
                fprintf(stderr, "Missing argument for option '%s'\n", argv[cmdln_index]);
                return 1;
            }
			ebucore_filename = argv[cmdln_index + 1];
            cmdln_index++;
        }
        else if (strcmp(argv[cmdln_index], "--dark-key") == 0)
        {
            if (cmdln_index + 1 >= argc)
            {
                usage(argv[0]);
                fprintf(stderr, "Missing argument for option '%s'\n", argv[cmdln_index]);
                return 1;
            }
            // parse the argument into an MXF UL
            if (bmx::parse_hex_string(argv[cmdln_index + 1], (unsigned char*)&darkMetadataKey, 16)) {
                do_use_dark_metadata_key = true;
            } else {
                usage(argv[0]);
                fprintf(stderr, "Invalid argument for option '%s'\n", argv[cmdln_index]);
                return 1;
            }
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


    if (log_filename) {
        if (!open_log_file(log_filename))
            return 1;
    }

    connect_libmxf_logging();

    if (do_print_version)
        log_info("%s\n", get_version_info().c_str());

    int cmd_result = 0;

    try
    {
		if (ebucore_filename) {
			EBUCore::ExtractEBUCoreMetadata(filenames[0], ebucore_filename, &progress_cb, do_use_dark_metadata_key, do_use_dark_metadata_key ? &darkMetadataKey : NULL);
		}
    }
    catch (const MXFException &ex)
    {
        log_error("MXF exception caught: %s\n", ex.getMessage().c_str());
        cmd_result = 1;
    }
    catch (const BMXException &ex)
    {
        log_error("BMX exception caught: %s\n", ex.what());
        cmd_result = 1;
    }
    catch (const bool &ex)
    {
        (void)ex;
        cmd_result = 1;
    }
    catch (...)
    {
        log_error("Unknown exception caught\n");
        cmd_result = 1;
    }

    if (log_filename)
        close_log_file();


    return cmd_result;
}

