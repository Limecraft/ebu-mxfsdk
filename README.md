# EBU MXF SDK

The EBU MXF SDK is a software development kit for the manipulation of MXF files with the aim of adding embedded descriptive metadata, in the form of [EBUCore](http://tech.ebu.ch/lang/en/MetadataEbuCore) metadata. Additionally, the SDK can be used to analyze the structure of MXF files and generate [ST-434](http://standards.smpte.org/content/978-1-61482-595-1/st-434-2006/SEC1.abstract)-compliant reports that describe their properties and header information.

## Context

While file-based media production has now found its way into the production 
processes of most broadcasters and production facilities, 
building unified workflows from heterogenous file-based systems 
remains challenging. When exchanges of audiovisual material require 
accompanying metadata to describe its semantics and origins, integration 
complications about interfaces, metadata formats and delivery mechanisms 
(busses, SOAP interfaces, FTP servers, ...) often manifest themselves.

A solution is to embed the descriptive metadata in the essence containers themselves 
such that it can no longer get lost and needs no separate out-of-band delivery mechanism; 
if the essence arrives, so does the metadata.

The software in this repository is a software development kit, 
the result of a collaborative project of [EBU](http://www.ebu.ch) and [Limecraft](http://www.limecraft.com), 
for embedding descriptive metadata into MXF files. The resulting files 
can be used to tie systems in a media production chain together. 

The code in this SDK extends the [BMX](http://sourceforge.net/projects/bmxlib/) libraries developed by BBC Research for the manipulation and creation of broadcast MXF files.

## Features

* In its current version, the SDK can be employed to embed EBUCore [EBUCore](http://tech.ebu.ch/lang/en/MetadataEbuCore) 
metadata documents into MXF file containers. The SDK is constructed such that additional metadata specifications can be easily added.
* The SDK also offers analysis capabilities and can be used to generated SMPTE ST-434-compliant XML reports describing the properties of MXF files.

## Getting Started

The code of the SDK can be obtained in two ways.

* From our [Sourceforge project](http://sourceforge.net/projects/ebu-mxfsdk/files/), where we offer prepackaged installers for Windows platforms.
* From this repository. Git clone this repo and its submodules, and build using Microsoft Visual Studio/C++ 2010 (or later).

## Included command line tools

### ebu2mxf

The ebu2mxf example program in ebu-bmx/apps/ebu2mxf opens an existing MXF file, and the EBUCore metadata is appended to its most appropriated (closed and complete metadata where available) set of metadata, while attempting to modify only the file metadata without rewriting its essence.

	Usage: ebu2mxf <<options>> <filename>
	Options:
	 -h | --help           Show usage and exit
	 -v | --version        Print version info
	 -l <file>             Log filename. Default log to stderr/stdout
	 -i                    Print file information to stdout
	 --ebu-core <file>     Write embedded EBU Core metadata to file
	 --force-header        Force metadata to be appended into the header partition
	 --dark                Write EBU Core metadata into a dark metadata set
	 --sidecar             Write EBU Core metadata as a side-car reference
	 --remove              Remove EBU Core metadata from the MXF file header metadata


### mxf2ebu

The mxf2ebu example program in ebu-bmx/apps/mxf2ebu extracts EBUCore metadata. An existing MXF file is opened, and the EBUCore metadata is read from its metadata and written to an EBUCore-compliant XML document.

	Usage: mxf2ebu.exe <<options>> <filename>
	Options:
	 -h | --help           Show usage and exit
	 -v | --version        Print version info
	 -l <file>             Log filename. Default log to stderr/stdout
	 -i                    Print file information to stdout
	 --ebu-core <file>     Write embedded EBU Core metadata to file

### raw2bmx

The raw2bmx example program in ebu-mxfsdk/apps/raw2bmx constructs a new MXF file from a number of essence tracks (delivered in separate files) and the EBUCore metadata (encoded as KLV packets) are mixed in with the newly constructed metadata (incl., track structure and essence characteristics) of the MXF file. The EBUCore metadata is provided in the form of a EBUCore-compliant XML document.

	Usage: raw2bmx.exe <<options>> [<<input options>> <input>]+
	Options (* means option is required):
	  -h | --help             Show usage and exit
	  -v | --version          Print version info
	  -l <file>               Log filename. Default log to stderr/stdout
	  -t <type>               Clip type: as02, as11op1a, as11d10, op1a, avid, d10, wave. Default is as02
	* -o <name>               as02: <name> is a bundle name
	                          as11op1a/as11d10/op1a/d10/wave: <name> is a filename
	                          avid: <name> is a filename prefix
	  -f <rate>               Frame rate: 23976 (24000/1001), 24, 25, 2997 (30000/1001), 50 or 5994 (60000/1001). Default parsed or 25
	  -y <hh:mm:sscff>        Start timecode. Is drop frame when c is not ':'. Default 00:00:00:00
	  --clip <name>           Set the clip name
	  --dur <frame>           Set the duration in frames in frame rate units. Default is minimum input duration
	  --avcihead <format> <file> <offset>
	                          Default AVC-Intra sequence header data (512 bytes) to use when the input file does have it
	                          <format> is a comma separated list of one or more of the following integer values:
	                               0: AVC-Intra 100 1080i50
	                               1: AVC-Intra 100 1080i59.94
	                               2: AVC-Intra 100 1080p25
	                               3: AVC-Intra 100 1080p29.97
	                               4: AVC-Intra 100 720p25
	                               5: AVC-Intra 100 720p50
	                               6: AVC-Intra 100 720p29.97
	                               7: AVC-Intra 100 720p59.94
	                               8: AVC-Intra 50 1080p50
	                               9: AVC-Intra 50 1080p29.97
	                              10: AVC-Intra 50 1080p25
	                              11: AVC-Intra 50 1080p29.97
	                              12: AVC-Intra 50 720p25
	                              13: AVC-Intra 50 720p50
	                              14: AVC-Intra 50 720p29.97
	                              15: AVC-Intra 50 720p59.94
	                          or set <format> to 'all' for all formats listed above
	                          The 512 bytes are extracted from <file> starting at <offset> bytes
	                              and incrementing 512 bytes for each format in the list

	  as02:
	    --mic-type <type>       Media integrity check type: 'md5' or 'none'. Default 'md5'
	    --mic-file              Calculate checksum for entire essence component file. Default is essence only
	    --shim-name <name>      Set ShimName element value in shim.xml file to <name>. Default is 'Sample File'
	    --shim-id <id>          Set ShimID element value in shim.xml file to <id>. Default is 'http://bbc.co.uk/rd/as02/default-shim.txt'
	    --shim-annot <str>      Set AnnotationText element value in shim.xml file to <str>. Default is 'Default AS-02 shim'

	  as02/as11op1a/op1a:
	    --part <interval>       Video essence partition interval in frames, or seconds with 's' suffix. Default single partition

	  as11op1a/as11d10:
	    --dm <fwork> <name> <value>    Set descriptive framework property. <fwork> is 'as11' or 'dpp'
	    --dm-file <fwork> <name>       Parse and set descriptive framework properties from text file <name>. <fwork> is 'as11' or 'dpp'
	    --seg <name>                   Parse and set segmentation data from text file <name>

	  as11op1a/op1a:
	    --out-start <offset>    Offset to start of first output frame, eg. pre-charge in MPEG-2 Long GOP
	    --out-end <offset>      Offset (positive value) from last frame to last output frame, eg. rollout in MPEG-2 Long GOP

	  as11op1a/as11d10/op1a/d10:
	    --seq-off <value>       Sound sample sequence offset. Default 0 for as11d10/d10 and not set (0) for as11op1a/op1a

	  as11op1a/op1a:
	    --single-pass           Write file in a single pass
	                            The header and body partitions will be incomplete
	    --file-md5              Calculate an MD5 checksum of the file. This requires writing in a single pass (--single-pass is assumed)

	  op1a:
	    --min-part              Only use a header and footer MXF file partition. Use this for applications that don't support
	                                separate partitions for header metadata, index tables, essence container data and footer

	  as11d10/d10:
	    --d10-mute <flags>      Indicate using a string of 8 '0' or '1' which sound channels should be muted. The lsb is the rightmost digit
	    --d10-invalid <flags>   Indicate using a string of 8 '0' or '1' which sound channels should be flagged invalid. The lsb is the rightmost digit

	  avid:
	    --project <name>        Set the Avid project name
	    --tape <name>           Source tape name
	    --import <name>         Source import name. <name> is one of the following:
	                              - a file URL starting with 'file://'
	                              - an absolute Windows (starts with '[A-Z]:') or *nix (starts with '/') filename
	                              - a relative filename, which will be converted to an absolute filename
	    --comment <string>      Add 'Comments' user comment to the MaterialPackage
	    --desc <string>         Add 'Descript' user comment to the MaterialPackage
	    --tag <name> <value>    Add <name> user comment to the MaterialPackage. Option can be used multiple times
	    --locator <position> <comment> <color>
	                            Add locator at <position> (in frame rate units) with <comment> and <color>
	                            <position> format is o?hh:mm:sscff, where the optional 'o' indicates it is an offset
	    --mp-uid <umid>         Set the Material Package UID. Autogenerated by default
	    --mp-created <tstamp>   Set the Material Package creation date. Default is 'now'
	    --tp-uid <umid>         Set the tape Source Package UID. Autogenerated by default
	    --tp-created <tstamp>   Set the tape Source Package creation date. Default is 'now'
	    --allow-no-avci-head    Allow inputs with no AVCI header (512 bytes, sequence and picture parameter sets)
	    --force-no-avci-head    Strip AVCI header (512 bytes, sequence and picture parameter sets) if present

	  wave:
	    --orig <name>           Set originator in the output Wave bext chunk. Default 'bmx'

	  EBU Core:
	    --ebu-core <name>       Parse and set EBU Core metadata from EBU Core XML file <name>
	    --sidecar               Write EBU Core metadata as a side-car reference


	Input Options (must precede the input to which it applies):
	  -a <n:d>                Image aspect ratio. Either 4:3 or 16:9. Default parsed or 16:9
	  --afd <value>           Active Format Descriptor 4-bit code from table 1 in SMPTE ST 2016-1. Default not set
	  -c <depth>              Component depth for uncompressed/DV100 video. Either 8 or 10. Default parsed or 8
	  --height                Height of input uncompressed video data. Default is the production aperture height, except for PAL (592) and NTSC (496)
	  -s <bps>                Audio sampling rate numerator. Default 48000
	  -q <bps>                Audio quantization bits per sample. Either 16 or 24. Default 16
	  --locked <bool>         Indicate whether the number of audio samples is locked to the video. Either true or false. Default not set
	  --audio-ref <level>     Audio reference level, number of dBm for 0VU. Default not set
	  --dial-norm <value>     Gain to be applied to normalize perceived loudness of the clip. Default not set
	  --off <bytes>           Skip bytes at start of the next input/track's file
	  --maxlen <bytes>        Maximum number of bytes to read from next input/track's file
	  --track-num <num>       Set the output track number. Default track number equals last track number of same picture/sound type + 1
	                          For as11d10/d10 the track number must be > 0 and <= 8 because the AES-3 channel index equals track number - 1
	  --no-d10-depad          Don't reduce the size of the D-10 frame to the maximum size
	                          Use this option if there are non-zero bytes beyond the maximum size

	  as02:
	    --trk-out-start <offset>   Offset to start of first output frame, eg. pre-charge in MPEG-2 Long GOP
	    --trk-out-end <offset>     Offset (positive value) from last frame to last output frame, eg. rollout in MPEG-2 Long GOP


	Inputs:
	  --dv <name>             Raw DV video input file
	  --iecdv25 <name>        Raw IEC DV25 video input file
	  --dvbased25 <name>      Raw DV-Based DV25 video input file
	  --dv50 <name>           Raw DV50 video input file
	  --dv100_1080i <name>    Raw DV100 1080i video input file
	  --dv100_1080p <name>    Raw DV100 1080p video input file
	  --dv100_720p <name>     Raw DV100 720p video input file
	  --d10 <name>            Raw D10 video input file
	  --d10_30 <name>         Raw D10 30Mbps video input file
	  --d10_40 <name>         Raw D10 40Mbps video input file
	  --d10_50 <name>         Raw D10 50Mbps video input file
	  --avci100_1080i <name>  Raw AVC-Intra 100 1080i video input file
	  --avci100_1080p <name>  Raw AVC-Intra 100 1080p video input file
	  --avci100_720p <name>   Raw AVC-Intra 100 720p video input file
	  --avci50_1080i <name>   Raw AVC-Intra 50 1080i video input file
	  --avci50_1080p <name>   Raw AVC-Intra 50 1080p video input file
	  --avci50_720p <name>    Raw AVC-Intra 50 720p video input file
	  --unc <name>            Raw uncompressed SD UYVY 422 video input file
	  --unc_1080i <name>      Raw uncompressed HD 1080i UYVY 422 video input file
	  --unc_1080p <name>      Raw uncompressed HD 1080p UYVY 422 video input file
	  --unc_720p <name>       Raw uncompressed HD 720p UYVY 422 video input file
	  --avid_alpha <name>               Raw Avid alpha component SD video input file
	  --avid_alpha_1080i <name>         Raw Avid alpha component HD 1080i video input file
	  --avid_alpha_1080p <name>         Raw Avid alpha component HD 1080p video input file
	  --avid_alpha_720p <name>          Raw Avid alpha component HD 720p video input file
	  --mpeg2lg <name>                  Raw MPEG-2 Long GOP video input file
	  --mpeg2lg_422p_hl_1080i <name>    Raw MPEG-2 Long GOP 422P@HL 1080i video input file
	  --mpeg2lg_422p_hl_1080p <name>    Raw MPEG-2 Long GOP 422P@HL 1080p video input file
	  --mpeg2lg_422p_hl_720p <name>     Raw MPEG-2 Long GOP 422P@HL 720p video input file
	  --mpeg2lg_mp_hl_1920_1080i <name> Raw MPEG-2 Long GOP MP@HL 1920x1080i video input file
	  --mpeg2lg_mp_hl_1920_1080p <name> Raw MPEG-2 Long GOP MP@HL 1920x1080p video input file
	  --mpeg2lg_mp_hl_1440_1080i <name> Raw MPEG-2 Long GOP MP@HL 1440x1080i video input file
	  --mpeg2lg_mp_hl_1440_1080p <name> Raw MPEG-2 Long GOP MP@HL 1440x1080p video input file
	  --mpeg2lg_mp_hl_720p <name>       Raw MPEG-2 Long GOP MP@HL 720p video input file
	  --mpeg2lg_mp_h14_1080i <name>     Raw MPEG-2 Long GOP MP@H14 1080i video input file
	  --mpeg2lg_mp_h14_1080p <name>     Raw MPEG-2 Long GOP MP@H14 1080p video input file
	  --mjpeg21 <name>        Raw Avid MJPEG 2:1 video input file
	  --mjpeg31 <name>        Raw Avid MJPEG 3:1 video input file
	  --mjpeg101 <name>       Raw Avid MJPEG 10:1 video input file
	  --mjpeg201 <name>       Raw Avid MJPEG 20:1 video input file
	  --mjpeg41m <name>       Raw Avid MJPEG 4:1m video input file
	  --mjpeg101m <name>      Raw Avid MJPEG 10:1m video input file
	  --mjpeg151s <name>      Raw Avid MJPEG 15:1s video input file
	  --vc3 <name>            Raw VC3/DNxHD input file
	  --vc3_1080p_1235 <name> Raw VC3/DNxHD 1920x1080p 220/185/175 Mbps 10bit input file
	  --vc3_1080p_1237 <name> Raw VC3/DNxHD 1920x1080p 145/120/115 Mbps input file
	  --vc3_1080p_1238 <name> Raw VC3/DNxHD 1920x1080p 220/185/175 Mbps input file
	  --vc3_1080i_1241 <name> Raw VC3/DNxHD 1920x1080i 220/185 Mbps 10bit input file
	  --vc3_1080i_1242 <name> Raw VC3/DNxHD 1920x1080i 145/120 Mbps input file
	  --vc3_1080i_1243 <name> Raw VC3/DNxHD 1920x1080i 220/185 Mbps input file
	  --vc3_720p_1250 <name>  Raw VC3/DNxHD 1280x720p 220/185/110/90 Mbps 10bit input file
	  --vc3_720p_1251 <name>  Raw VC3/DNxHD 1280x720p 220/185/110/90 Mbps input file
	  --vc3_720p_1252 <name>  Raw VC3/DNxHD 1280x720p 220/185/110/90 Mbps input file
	  --vc3_1080p_1253 <name> Raw VC3/DNxHD 1920x1080p 45/36 Mbps input file
	  --pcm <name>            Raw PCM audio input file
	  --wave <name>           Wave PCM audio input file


	Notes:
	 - <umid> format is [0-9a-fA-F]{64}, a sequence of 32 hexadecimal bytes
	 - <tstamp> format is YYYY-MM-DDThh:mm:ss:qm where qm is in units of 1/250th second

### ebuaudio2mxf

The ebuaudio2mxf example program in ebu-bmx/apps/ebuaudio2mxf opens an existing MXF file, and the EBUCore audio metadata is appended to its most appropriated (closed and complete metadata where available) set of metadata, while attempting to modify only the file metadata without rewriting its essence. This is an optimized version of the ebu2mxf program, with a number of optimizations for embedded of audio metadata, incl. only serialization of metadata in a dark way.

	Usage: ebuaudio2mxf <<options>> <filename>
	Options:
	 -h | --help           Show usage and exit
	 -v | --version        Print version info
	 -l <file>             Log filename. Default log to stderr/stdout
	 --ebu-core <file>     Write embedded EBU Core metadata to file
	 --force-header        Force metadata to be appended into the header partition
	 --remove              Remove EBU Core metadata from the MXF file header metadata
	 
### mxfanalyzer

The mxfanalyzer example program in ebu-mxfsdk/Analyzer/apps/analyzer demonstrates the use of the SDK's analyzer functions. An existing MXF file is opened, analyzed, and the report is written in the format selected by a number of command line options.

	Usage: mxfanalyzer.exe <<options>> <filename>
	Options:
	 -h | --help           Show usage and exit
	 -v | --version        Print version info
	 --report <file>       Write analysis report to file
	 --physical            Output a physical layout of the header metadata
	 --logical             Output a logical layout of the header metadata (default)
	 --metadata            Perform only a metadata analysis (default)
	 --mux                 Perform an analysis on the entire MXF file mux
	 --deepindex           Perform a deep index table analysis

## Documentation

Further documentation about the workings of the SDK, its use and developer documentation is available in the following resources:

* doc/EBU MXF SDK.pdf: Provides a high-level overview of the internal structure of the SDK an MXF manipulation techniques used.
* doc/doxygen/html/index.html: Provides the developer documentation with information about how the SDK's functions are to be used and embedded in custom applications.


## License

Copyright 2012-2013 European Broadcasting Union and Limecraft, NV.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   [http://www.apache.org/licenses/LICENSE-2.0](http://www.apache.org/licenses/LICENSE-2.0)

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
