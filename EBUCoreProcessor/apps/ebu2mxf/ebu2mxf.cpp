/*
 * Copyright (C) 2010, British Broadcasting Corporation
 * All Rights Reserved.
 *
 * Author: Philip de Nier
 *
 * Modifications Copyright (C) 2012-2013, European Broadcasting Union and Limecraft, NV.
 *
 * Author: Dieter Van Rijsselbergen
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the British Broadcasting Corporation nor the names
 *       of its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

// C:\code\BMX\bmxlib-bmx\msvc_build\vs8\apps\raw2bmx\out.mxf

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
#include <bmx/Version.h>
#include <bmx/as11/AS11Info.h>
#include <bmx/BMXException.h>
#include <bmx/Logging.h>

#if defined(_WIN32)
#include <mxf/mxf_win32_file.h>
#endif

#include <EBUCoreProcessor.h>

using namespace std;
using namespace bmx;
using namespace mxfpp;

using namespace EBUSDK;

static const uint32_t MEMORY_WRITE_CHUNK_SIZE   = 8192;

static char* get_label_string(mxfUL label, char *buf)
{
    sprintf(buf,
            "%02x%02x%02x%02x.%02x%02x%02x%02x.%02x%02x%02x%02x.%02x%02x%02x%02x",
            label.octet0,  label.octet1,  label.octet2,  label.octet3,
            label.octet4,  label.octet5,  label.octet6,  label.octet7,
            label.octet8,  label.octet9,  label.octet10, label.octet11,
            label.octet12, label.octet13, label.octet14, label.octet15);

    return buf;
}

static char* get_uuid_string(mxfUUID uuid, char *buf)
{
    return get_label_string(*(mxfUL*)&uuid, buf);
}

static char* get_umid_string(mxfUMID umid, char *buf)
{
    sprintf(buf,
            "%02x%02x%02x%02x.%02x%02x%02x%02x.%02x%02x%02x%02x.%02x%02x%02x%02x."
            "%02x%02x%02x%02x.%02x%02x%02x%02x.%02x%02x%02x%02x.%02x%02x%02x%02x",
            umid.octet0,  umid.octet1,  umid.octet2,  umid.octet3,
            umid.octet4,  umid.octet5,  umid.octet6,  umid.octet7,
            umid.octet8,  umid.octet9,  umid.octet10, umid.octet11,
            umid.octet12, umid.octet13, umid.octet14, umid.octet15,
            umid.octet16, umid.octet17, umid.octet18, umid.octet19,
            umid.octet20, umid.octet21, umid.octet22, umid.octet23,
            umid.octet24, umid.octet25, umid.octet26, umid.octet27,
            umid.octet28, umid.octet29, umid.octet30, umid.octet31);

    return buf;
}

static char* get_rational_string(mxfRational rat, char *buf)
{
    sprintf(buf, "%d/%d", rat.numerator, rat.denominator);
    return buf;
}

static char* get_timestamp_string(mxfTimestamp timestamp, char *buf)
{
    sprintf(buf, "%d-%02u-%02u %02u:%02u:%02u.%03u",
            timestamp.year, timestamp.month, timestamp.day,
            timestamp.hour, timestamp.min, timestamp.sec, timestamp.qmsec * 4);

    return buf;
}

static char* get_product_version_string(mxfProductVersion version, char *buf)
{
    const char *release_string;
    switch (version.release)
    {
        case 0:
            release_string = "unknown version";
            break;
        case 1:
            release_string = "released version";
            break;
        case 2:
            release_string = "development version";
            break;
        case 3:
            release_string = "released with patches version";
            break;
        case 4:
            release_string = "pre-release beta version";
            break;
        case 5:
            release_string = "private version";
            break;
        default:
            release_string = "unrecognized release number";
            break;
    }

    sprintf(buf, "%u.%u.%u.%u.%u (%s)",
            version.major, version.minor, version.patch, version.build, version.release, release_string);

    return buf;
}

static const char* get_signal_standard_string(uint8_t signal_standard)
{
    switch (signal_standard)
    {
        case MXF_SIGNAL_STANDARD_NONE:
            return "None";
        case MXF_SIGNAL_STANDARD_ITU601:
            return "ITU 601";
        case MXF_SIGNAL_STANDARD_ITU1358:
            return "ITU 1358";
        case MXF_SIGNAL_STANDARD_SMPTE347M:
            return "SMPTE 347M";
        case MXF_SIGNAL_STANDARD_SMPTE274M:
            return "SMPTE 274M";
        case MXF_SIGNAL_STANDARD_SMPTE296M:
            return "SMPTE 296M";
        case MXF_SIGNAL_STANDARD_SMPTE349M:
            return "SMPTE 349M";
        case MXF_SIGNAL_STANDARD_SMPTE428_1:
            return "SMPTE 428-1";
        default:
            break;
    }

    return "not recognized";
}

static const char* get_frame_layout_string(uint8_t frame_layout)
{
    switch (frame_layout)
    {
        case MXF_FULL_FRAME:
            return "Full Frame";
        case MXF_SEPARATE_FIELDS:
            return "Separate Fields";
        case MXF_SINGLE_FIELD:
            return "Single Field";
        case MXF_MIXED_FIELDS:
            return "Mixed Fields";
        case MXF_SEGMENTED_FRAME:
            return "Segmented Frame";
        default:
            break;
    }

    return "not recognized";
}

static const char* get_color_siting_string(uint8_t color_siting)
{
    switch (color_siting)
    {
        case MXF_COLOR_SITING_COSITING:
            return "Co-siting";
        case MXF_COLOR_SITING_HORIZ_MIDPOINT:
            return "Horizontal Mid-point";
        case MXF_COLOR_SITING_THREE_TAP:
            return "Three Tap";
        case MXF_COLOR_SITING_QUINCUNX:
            return "Quincunx";
        case MXF_COLOR_SITING_REC601:
            return "Rec 601";
        case MXF_COLOR_SITING_LINE_ALTERN:
            return "Line Alternating";
        case MXF_COLOR_SITING_VERT_MIDPOINT:
            return "Vertical Mid-point";
        case MXF_COLOR_SITING_UNKNOWN:
            return "Unknown";
        default:
            break;
    }

    return "not recognized";
}

static const char* get_d10_sound_flags(uint8_t flags, char *buf)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        if (flags & (1 << i))
            buf[7 - i] = '1';
        else
            buf[7 - i] = '0';
    }
    buf[i    ] = 'b';
    buf[i + 1] = 0;

    return buf;
}

static void print_track_info(const MXFTrackInfo *track_info)
{
    char string_buffer[128];

    const MXFPictureTrackInfo *picture_info = dynamic_cast<const MXFPictureTrackInfo*>(track_info);
    const MXFSoundTrackInfo *sound_info = dynamic_cast<const MXFSoundTrackInfo*>(track_info);

    printf("  Essence kind         : %s\n", (picture_info ? "Picture" : (sound_info ? "Sound" : "Unknown")));
    printf("  Essence type         : %s\n", essence_type_to_string(track_info->essence_type));
    printf("  Essence label        : %s\n", get_label_string(track_info->essence_container_label, string_buffer));
    printf("  Material package uid : %s\n", get_umid_string(track_info->material_package_uid, string_buffer));
    printf("  Material track id    : %u\n", track_info->material_track_id);
    printf("  Material track number: %u\n", track_info->material_track_number);
    printf("  File package uid     : %s\n", get_umid_string(track_info->file_package_uid, string_buffer));
    printf("  File track id        : %u\n", track_info->file_track_id);
    printf("  File track number    : 0x%08x\n", track_info->file_track_number);
    printf("  Edit rate            : %s\n", get_rational_string(track_info->edit_rate, string_buffer));
    printf("  Duration             : %"PRId64"\n", track_info->duration);
    printf("  Lead filler offset   : %"PRId64"\n", track_info->lead_filler_offset);

    if (picture_info) {
        printf("  Picture coding label : %s\n", get_label_string(picture_info->picture_essence_coding_label, string_buffer));
        printf("  Signal standard      : %u (%s)\n", picture_info->signal_standard, get_signal_standard_string(picture_info->signal_standard));
        printf("  Frame layout         : %u (%s)\n", picture_info->frame_layout, get_frame_layout_string(picture_info->frame_layout));
        printf("  Stored dimensions    : %ux%u\n", picture_info->stored_width, picture_info->stored_height);
        printf("  Display dimensions   : %ux%u\n", picture_info->display_width, picture_info->display_height);
        printf("  Display x offset     : %u\n", picture_info->display_x_offset);
        printf("  Display y offset     : %u\n", picture_info->display_y_offset);
        printf("  Aspect ratio         : %s\n", get_rational_string(picture_info->aspect_ratio, string_buffer));
        printf("  AFD                  : ");
        if (picture_info->afd)
            printf("%u\n", picture_info->afd);
        else
            printf("(not set)\n");
        if (picture_info->is_cdci) {
            printf("  Component depth      : %u\n", picture_info->component_depth);
            printf("  Horiz subsampling    : %u\n", picture_info->horiz_subsampling);
            printf("  Vert subsampling     : %u\n", picture_info->vert_subsampling);
            printf("  Color siting         : %u (%s)\n", picture_info->color_siting, get_color_siting_string(picture_info->color_siting));
            /*if (track_info->essence_type == D10_30 ||
                track_info->essence_type == D10_40 ||
                track_info->essence_type == D10_50)
            {
                printf("  Frame size           : %u\n", picture_info->d10_frame_size);
            }*/
            if (track_info->essence_type == AVCI100_1080I ||
                track_info->essence_type == AVCI100_1080P ||
                track_info->essence_type == AVCI100_720P ||
                track_info->essence_type == AVCI50_1080I ||
                track_info->essence_type == AVCI50_1080P ||
                track_info->essence_type == AVCI50_720P)
            {
                printf("  AVCI header          : %s\n", picture_info->have_avci_header ? "true" : "false");
            }
        }
    } else if (sound_info) {
        printf("  Sampling rate        : %s\n", get_rational_string(sound_info->sampling_rate, string_buffer));
        printf("  Bits per sample      : %u\n", sound_info->bits_per_sample);
        printf("  Block align          : %u\n", sound_info->block_align);
        printf("  Channel count        : %u\n", sound_info->channel_count);
        if (track_info->essence_type == D10_AES3_PCM)
            printf("  D10 AES3 valid flags : %s\n", get_d10_sound_flags(sound_info->d10_aes3_valid_flags, string_buffer));
        printf("  Sequence offset      : %u\n", sound_info->sequence_offset);
        printf("  Locked               : %s\n", (sound_info->locked_set ? (sound_info->locked ? "true" : "false") : "(not set)"));
        printf("  Audio ref level      : ");
        if (sound_info->audio_ref_level_set)
            printf("%d\n", sound_info->audio_ref_level);
        else
            printf("(not set)\n");
        printf("  Dial norm            : ");
        if (sound_info->dial_norm_set)
            printf("%d\n", sound_info->dial_norm);
        else
            printf("(not set)\n");
    }
}

static void print_identification_info(Identification *identification)
{
    char string_buffer[128];

    printf("      Generation UID    : %s\n", get_uuid_string(identification->getThisGenerationUID(), string_buffer));
    printf("      Company name      : %s\n", identification->getCompanyName().c_str());
    printf("      Product name      : %s\n", identification->getProductName().c_str());
    printf("      Product version   : ");
    if (identification->haveProductVersion())
        printf("%s\n", get_product_version_string(identification->getProductVersion(), string_buffer));
    else
        printf("(not set)\n");
    printf("      Version string    : %s\n", identification->getVersionString().c_str());
    printf("      Product UID       : %s\n", get_uuid_string(identification->getProductUID(), string_buffer));
    printf("      Modification date : %s\n", get_timestamp_string(identification->getModificationDate(), string_buffer));
    printf("      Toolkit version   : ");
    if (identification->haveToolkitVersion())
        printf("%s\n", get_product_version_string(identification->getToolkitVersion(), string_buffer));
    else
        printf("(not set)\n");
    printf("      Platform          : ");
    if (identification->havePlatform())
        printf("%s\n", identification->getPlatform().c_str());
    else
        printf("(not set)\n");
}

static string timecode_to_string(Timecode timecode)
{
    char buffer[64];
    sprintf(buffer, "%02d:%02d:%02d%c%02d (@ %dfps)",
            timecode.GetHour(), timecode.GetMin(), timecode.GetSec(),
            timecode.IsDropFrame() ? ';' : ':', timecode.GetFrame(),
            timecode.GetRoundedTCBase());
    return buffer;
}

static string create_raw_filename(string prefix, bool is_video, uint32_t index, int32_t child_index)
{
    char buffer[64];
    if (child_index >= 0)
        sprintf(buffer, "_%s%u_%d.raw", is_video ? "v" : "a", index, child_index);
    else
        sprintf(buffer, "_%s%u.raw", is_video ? "v" : "a", index);

    return prefix + buffer;
}

static string get_version_info()
{
    char buffer[256];
    sprintf(buffer, "mxf2raw, %s v%s, %s %s (scm %s)",
            get_bmx_library_name().c_str(),
            get_bmx_version_string().c_str(),
            __DATE__, __TIME__,
            get_bmx_scm_version_string().c_str());
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
    fprintf(stderr, " -i                    Print file information to stdout\n");
    fprintf(stderr, " --ebu-core <file>     Write embedded EBU Core metadata to file\n");
    fprintf(stderr, " --force-header        Force metadata to be appended into the header partition\n");
    fprintf(stderr, " --dark                Write EBU Core metadata into a dark metadata set\n");
    fprintf(stderr, " --sidecar             Write EBU Core metadata as a side-car reference\n");
    fprintf(stderr, " --remove              Remove EBU Core metadata from the MXF file header metadata\n");
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
	bool do_force_header = false;
	bool do_sidecar = false;
	bool do_dark = false;
	bool do_remove = false;
    bool do_print_info = false;
    bool do_print_version = false;
    const char *ebucore_filename = 0;
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
        else if (strcmp(argv[cmdln_index], "-i") == 0)
        {
            do_print_info = true;
        }
        else if (strcmp(argv[cmdln_index], "--force-header") == 0)
        {
            do_force_header = true;
        }
		else if (strcmp(argv[cmdln_index], "--dark") == 0)
        {
            do_dark = true;
        }
		else if (strcmp(argv[cmdln_index], "--sidecar") == 0)
        {
            do_sidecar = true;
        }
		else if (strcmp(argv[cmdln_index], "--remove") == 0)
        {
            do_remove = true;
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
		if (do_remove) {
			EBUCore::RemoveEBUCoreMetadata(filenames[0], &progress_cb, false, do_force_header);
		}
		else {
			if (ebucore_filename) {
				// select correct serialization mode
				EBUCore::MetadataKind kind = do_sidecar ? EBUCore::SIDECAR : (do_dark ? EBUCore::DARK : EBUCore::KLV_ENCODED);
				EBUCore::EmbedEBUCoreMetadata(ebucore_filename, filenames[0], &progress_cb, kind, false, do_force_header);
			}
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
	catch (const exception &std_ex) {
		log_error("Unknown std::exception caught: %s\n", std_ex.what());
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

