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
     --dark-key            Use this custom dark metadata key for metadata embedding.
                           The provided key should a SMPTE UL, formatted as a 'urn:smpte:ul:...'.
     --rp2057              Embed EBU Core metadata according to SMPTE RP 2057 XML embedding.
                           If the XML size is less than 64KB and uses UTF-8 or UTF-16 encoding (declared in
                           the XML prolog) then the XML data is included in the header metadata. Otherwise
                           a Generic Stream partition is used to hold the XML data.
     --remove              Remove EBU Core metadata from the MXF file header metadata
    SMPTE RP2057-based XML embedding options:
     --xml-scheme-id <id>  Set the XML payload scheme identifier associated with the RP-2057-embedded metadata.
                           The <id> is one of the following:
                               * a SMPTE UL, formatted as a 'urn:smpte:ul:...',
                               * a UUID, formatted as a 'urn:uuid:...'or as 32 hexadecimal characters using a '.' or '-' separator,
                           A default EBU Core scheme identifier is used if this option is not provided.
     --xml-lang <tag>      Set the RFC 5646 language tag associated with the the following --embed-xml option.
                           Defaults to the xml:lang attribute in the root element or empty string if not present.     
         

### mxf2ebu

The mxf2ebu example program in ebu-bmx/apps/mxf2ebu extracts EBUCore metadata. An existing MXF file is opened, and the EBUCore metadata is read from its metadata and written to an EBUCore-compliant XML document.

	Usage: mxf2ebu.exe <<options>> <filename>
	Options:
	 -h | --help           Show usage and exit
	 -v | --version        Print version info
	 -l <file>             Log filename. Default log to stderr/stdout
	 -i                    Print file information to stdout
	 --ebu-core <file>     Write embedded EBU Core metadata to file
     --dark-key            Use this custom dark metadata key when searching for dark embedded metadata.
                           The provided key should a SMPTE UL, formatted as a 'urn:smpte:ul:...'.
     --xml-scheme-id <id>  Use this XML scheme when searching for relevant RP2057-embedded metadata.
                           The <id> is one of the following:
                               * a SMPTE UL, formatted as a 'urn:smpte:ul:...',
                               * a UUID, formatted as a 'urn:uuid:...'or as 32 hexadecimal characters using a '.' or '-' separator,
                           A default EBU Core scheme identifier is used if this option is not provided.
                           

### raw2bmx

The raw2bmx example program in ebu-mxfsdk/apps/raw2bmx constructs a new MXF file from a number of essence tracks (delivered in separate files) and the EBUCore metadata (encoded as KLV packets) are mixed in with the newly constructed metadata (incl., track structure and essence characteristics) of the MXF file. The EBUCore metadata is provided in the form of a EBUCore-compliant XML document.

    Usage: raw2bmx.exe <<options>> [<<input options>> <input>]+
    Options (* means option is required):
      -h | --help             Show usage and exit
      -v | --version          Print version info
      -l <file>               Log filename. Default log to stderr/stdout
     --log-level <level>      Set the log level. 0=debug, 1=info, 2=warning, 3=error. Default is 1
      -t <type>               Clip type: as02, as11op1a, as11d10, op1a, avid, d10, rdd9, as10, wave. Default is op1a
    * -o <name>               as02: <name> is a bundle name
                              as11op1a/as11d10/op1a/d10/rdd9/as10/wave: <name> is a filename
                              avid: <name> is a filename prefix
      --prod-info <cname>
                  <pname>
                  <ver>
                  <verstr>
                  <uid>
                              Set the product info in the MXF Identification set
                              <cname> is a string and is the Company Name property
                              <pname> is a string and is the Product Name property
                              <ver> has format '<major>.<minor>.<patch>.<build>.<release>' and is the Product Version property. Set to '0.0.0.0.0' to omit it
                              <verstr> is a string and is the Version String property
                              <uid> is a UUID (see Notes at the end) and is the Product UID property
      -f <rate>               Set the frame rate, overriding any frame rate parsed from the essence data
                              The <rate> is either 'num', 'num'/'den', 23976 (=24000/1001), 2997 (=30000/1001) or 5994 (=60000/1001)
      --dflt-rate <rate>      Set the default frame rate which is used when no rate is provided by the essence data. Without this option the default is 25
                              The <rate> is either 'num', 'num'/'den', 23976 (=24000/1001), 2997 (=30000/1001) or 5994 (=60000/1001)
      -y <hh:mm:sscff>        Start timecode. Default 00:00:00:00
                              The c character in the pattern should be ':' for non-drop frame; any other character indicates drop frame
      --clip <name>           Set the clip name
      --dur <frame>           Set the duration in frames in frame rate units. Default is minimum input duration
      --rt <factor>           Wrap at realtime rate x <factor>, where <factor> is a floating point value
                              <factor> value 1.0 results in realtime rate, value < 1.0 slower and > 1.0 faster
      --avcihead <format> <file> <offset>
                              Default AVC-Intra sequence header data (512 bytes) to use when the input file does not have it
                              <format> is a comma separated list of one or more of the following integer values:
                                   0: AVC-Intra 100 1080i50
                                   1: AVC-Intra 100 1080i59.94
                                   2: AVC-Intra 100 1080p25
                                   3: AVC-Intra 100 1080p29.97
                                   4: AVC-Intra 100 720p25
                                   5: AVC-Intra 100 720p50
                                   6: AVC-Intra 100 720p29.97
                                   7: AVC-Intra 100 720p59.94
                                   8: AVC-Intra 50 1080i50
                                   9: AVC-Intra 50 1080i29.97
                                  10: AVC-Intra 50 1080p25
                                  11: AVC-Intra 50 1080p29.97
                                  12: AVC-Intra 50 720p25
                                  13: AVC-Intra 50 720p50
                                  14: AVC-Intra 50 720p29.97
                                  15: AVC-Intra 50 720p59.94
                                  16: AVC-Intra 100 1080p50
                                  17: AVC-Intra 100 1080p59.94
                                  18: AVC-Intra 50 1080p50
                                  19: AVC-Intra 50 1080p59.94
                                  20: AVC-Intra 50 1080p23.98
                                  21: AVC-Intra 50 720p23.98
                                  22: AVC-Intra 100 1080p23.98
                                  23: AVC-Intra 100 720p23.98
                                  24: AVC-Intra 200 1080i50
                                  25: AVC-Intra 200 1080i59.94
                                  26: AVC-Intra 200 1080p25
                                  27: AVC-Intra 200 1080p29.97
                                  28: AVC-Intra 200 1080p23.98
                                  29: AVC-Intra 200 720p25
                                  30: AVC-Intra 200 720p50
                                  31: AVC-Intra 200 720p29.97
                                  32: AVC-Intra 200 720p59.94
                                  33: AVC-Intra 200 720p23.98
                                  34: AVC-Intra 200 1080p50
                                  35: AVC-Intra 200 1080p59.94
                              or set <format> to 'all' for all formats listed above
                              The 512 bytes are extracted from <file> starting at <offset> bytes
                              and incrementing 512 bytes for each format in the list
      --ps-avcihead           Panasonic AVC-Intra sequence header data for Panasonic-compatible files that don't include the header data
                              These formats are supported:
                                  AVC-Intra 100 1080i50, AVC-Intra 100 1080p25, AVC-Intra 100 720p25, AVC-Intra 100 720p50,
                                  AVC-Intra 50 1080i50, AVC-Intra 50 1080p25, AVC-Intra 50 720p25, AVC-Intra 50 720p50
      --track-map <expr>      Map input audio channels to output tracks. See below for details of the <expr> format
      --dump-track-map        Dump the output audio track map to stderr.
                              The dumps consists of a list output tracks, where each output track channel
                              is shown as '<output track channel> <- <input channel>
      --dump-track-map-exit   Same as --dump-track-map, but exit immediately afterwards

      as11op1a/as11d10/as11rdd9/op1a/rdd9/d10:
        --head-fill <bytes>     Reserve minimum <bytes> at the end of the header metadata using a KLV Fill
                                Add a 'K' suffix for kibibytes and 'M' for mibibytes

      as02:
        --mic-type <type>       Media integrity check type: 'md5' or 'none'. Default 'md5'
        --mic-file              Calculate checksum for entire essence component file. Default is essence only
        --shim-name <name>      Set ShimName element value in shim.xml file to <name>. Default is 'Sample File'
        --shim-id <id>          Set ShimID element value in shim.xml file to <id>. Default is 'http://bbc.co.uk/rd/as02/default-shim.txt'
        --shim-annot <str>      Set AnnotationText element value in shim.xml file to <str>. Default is 'Default AS-02 shim'

      as02/as11op1a/op1a/rdd9/as10:
        --part <interval>       Video essence partition interval in frames, or seconds with 's' suffix. Default single partition

      as11op1a/as11d10:
        --dm <fwork> <name> <value>    Set descriptive framework property. <fwork> is 'as11' or 'dpp'
        --dm-file <fwork> <name>       Parse and set descriptive framework properties from text file <name>. <fwork> is 'as11' or 'dpp'
        --seg <name>                   Parse and set segmentation data from text file <name>
        --spec-id <id>                 Set the AS-11 specification identifier labels associated with <id>
                                       The <id> is one of the following:
                                           as11-x1 : AMWA AS-11 X1, delivery of finished UHD programs to Digital Production Partnership (DPP) broadcasters
                                           as11-x2 : AMWA AS-11 X2, delivery of finished HD AVC Intra programs to a broadcaster or publisher
                                           as11-x3 : AMWA AS-11 X3, delivery of finished HD AVC Long GOP programs to a broadcaster or publisher
                                           as11-x4 : AMWA AS-11 X4, delivery of finished HD AVC Long GOP programs to a broadcaster or publisher
                                           as11-x7 : AMWA AS-11 X7, delivery of finished SD D10 programs to a broadcaster or publisher
                                           as11-x8 : AMWA AS-11 X8, delivery of finished HD (MPEG-2) programs to North American Broadcasters Association (NABA) broadcasters

      as11op1a/op1a/rdd9/as10:
        --out-start <offset>    Offset to start of first output frame, eg. pre-charge in MPEG-2 Long GOP
        --out-end <offset>      Offset (positive value) from last frame to last output frame, eg. rollout in MPEG-2 Long GOP

      as11op1a/as11d10/op1a/d10/rdd9/as10:
        --seq-off <value>       Sound sample sequence offset. Default 0 for as11d10/d10 and not set (0) for as11op1a/op1a

      as11op1a/op1a/rdd9/as10:
        --single-pass           Write file in a single pass
                                The header and body partitions will be incomplete
        --file-md5              Calculate an MD5 checksum of the file. This requires writing in a single pass (--single-pass is assumed)

      op1a:
        --min-part              Only use a header and footer MXF file partition. Use this for applications that don't support
                                separate partitions for header metadata, index tables, essence container data and footer
        --body-part             Create separate body partitions for essence data
                                and don't create separate body partitions for index table segments
        --clip-wrap             Use clip wrapping for a single sound track
        --mp-track-num          Use the material package track number property to define a track order. By default the track number is set to 0

      op1a/rdd9/d10:
        --xml-scheme-id <id>    Set the XML payload scheme identifier associated with the following --embed-xml option.
                                The <id> is one of the following:
                                    * a SMPTE UL, formatted as a 'urn:smpte:ul:...',
                                    * a UUID, formatted as a 'urn:uuid:...'or as 32 hexadecimal characters using a '.' or '-' seperator,
                                    * 'as11', which corresponds to urn:smpte:ul:060e2b34.04010101.0d010801.04010000
                                A default BMX scheme identifier is used if this option is not provided
        --xml-lang <tag>        Set the RFC 5646 language tag associated with the the following --embed-xml option.
                                Defaults to the xml:lang attribute in the root element or empty string if not present
        --embed-xml <filename>  Embed the XML from <filename> using the approach specified in SMPTE RP 2057
                                If the XML size is less than 64KB and uses UTF-8 or UTF-16 encoding (declared in
                                the XML prolog) then the XML data is included in the header metadata. Otherwise
                                a Generic Stream partition is used to hold the XML data.

      op1a/rdd9:
        --ard-zdf-hdf           Use the ARD ZDF HDF profile

      as11d10/d10:
        --d10-mute <flags>      Indicate using a string of 8 '0' or '1' which sound channels should be muted. The lsb is the rightmost digit
        --d10-invalid <flags>   Indicate using a string of 8 '0' or '1' which sound channels should be flagged invalid. The lsb is the rightmost digit

      as10:
        --shim-name <name>      Shim name for AS10 (used for setting 'ShimName' metadata and setting video/sound parameters' checks)
                                list of known shims: HIGH_HD_2014, CNN_HD_2012, NRK_HD_2012, JVC_HD_35_VBR_2012, JVC_HD_25_CBR_2012
        --dm-file as10 <name>   Parse and set descriptive framework properties from text file <name>
                                N.B. 'ShimName' is the only mandatary property of AS10 metadata set
        --dm as10 <name> <value>    Set descriptive framework property
        --pass-dm               Copy descriptive metadata from the input file. The metadata can be overidden by other options
        --mpeg-checks [<name>]  Enable AS-10 compliancy checks. The file <name> is optional and contains expected descriptor values
        --loose-checks          Don't stop processing on detected compliancy violations
        --print-checks          Print default values of mpeg descriptors and report on descriptors either found in mpeg headers or copied from mxf headers
        --max-same-warnings <value>  Max same violations warnings logged, default 3

      rdd9/as10:
        --mp-uid <umid>         Set the Material Package UID. Autogenerated by default

      avid:
        --project <name>        Set the Avid project name
        --tape <name>           Source tape name
        --import <name>         Source import name. <name> is one of the following:
                                  - a file URL starting with 'file://'
                                  - an absolute Windows (starts with '[A-Z]:') or *nix (starts with '/') filename
                                  - a relative filename, which will be converted to an absolute filename
        --aux <hh:mm:sscff>     Set up to 5 auxiliary start timecodes. Multiple timecodes are separated by commas e.g. --aux 15:02:15:23,09:37:08:10
                                The c character in the pattern should be ':' for non-drop frame; any other character indicates drop frame
        --comment <string>      Add 'Comments' user comment to the MaterialPackage
        --desc <string>         Add 'Descript' user comment to the MaterialPackage
        --tag <name> <value>    Add <name> user comment to the MaterialPackage. Option can be used multiple times
        --locator <position> <comment> <color>
                                Add locator at <position> (in frame rate units) with <comment> and <color>
                                <position> format is o?hh:mm:sscff, where the optional 'o' indicates it is an offset
        --mp-uid <umid>         Set the Material Package UID. Autogenerated by default
        --mp-created <tstamp>   Set the Material Package creation date. Default is 'now'
        --psp-uid <umid>        Set the tape/import Source Package UID. Autogenerated by default
        --psp-created <tstamp>  Set the tape/import Source Package creation date. Default is 'now'
        --allow-no-avci-head    Allow inputs with no AVCI header (512 bytes, sequence and picture parameter sets)
        --avid-gf               Use the Avid growing file flavour
        --avid-gf-dur <dur>     Set the duration which should be shown whilst the file is growing
                                Avid will show 'Capture in Progress' when this option is used

      op1a/avid:
        --force-no-avci-head    Strip AVCI header (512 bytes, sequence and picture parameter sets) if present

      wave:
        --orig <name>           Set originator in the output Wave bext chunk. Default 'bmx'

      as02/op1a/as11op1a:
        --use-avc-subdesc       Use the AVC sub-descriptor rather than the MPEG video descriptor for AVC-Intra tracks

      op1a/as11op1a/rdd9:
        --audio-layout <label>  Set the Wave essence descriptor channel assignment label which identifies the audio layout mode in operation
                                The <label> is one of the following:
                                    * a SMPTE UL, formatted as a 'urn:smpte:ul:...',
                                    * 'as11-mode-0', which corresponds to urn:smpte:ul:060e2b34.04010101.0d010801.02010000,
                                    * 'as11-mode-1', which corresponds to urn:smpte:ul:060e2b34.04010101.0d010801.02020000,
                                    * 'as11-mode-2', which corresponds to urn:smpte:ul:060e2b34.04010101.0d010801.02030000
        --track-mca-labels <scheme> <file>   Insert audio labels defined in <file> using the symbol <scheme>
                                             The available <scheme>s are: 'as11'

      EBU Core:
        --ebu-core <name>       Parse and set EBU Core metadata from EBU Core XML file <name>
        --sidecar               Write EBU Core metadata as a side-car reference


    Input Options (must precede the input to which it applies):
      -a <n:d>                Image aspect ratio. Default parsed from essence or 16:9
      --bsar                  Set image aspect ratio in video bitstream. Currently supports D-10 essence types only
      --afd <value>           Active Format Descriptor 4-bit code from table 1 in SMPTE ST 2016-1. Default not set
      -c <depth>              Component depth for uncompressed/DV100 video. Either 8 or 10. Default parsed or 8
      --height                Height of input uncompressed video data. Default is the production aperture height, except for PAL (592) and NTSC (496)
      --signal-std  <value>   Set the video signal standard. The <value> is one of the following:
                                  'none', 'bt601', 'bt1358', 'st347', 'st274', 'st296', 'st349', 'st428'
      --frame-layout <value>  Set the video frame layout. The <value> is one of the following:
                                  'fullframe', 'separatefield', 'singlefield', 'mixedfield', 'segmentedframe'
      --field-dom <value>     Set which field is first in temporal order. The <value> is 1 or 2
      --transfer-ch <value>   Set the transfer characteristic label
                              The <value> is a SMPTE UL, formatted as a 'urn:smpte:ul:...' or one of the following:
                                  'bt470', 'bt709', 'st240', 'st274', 'bt1361', 'linear', 'dcdm',
                                  'iec61966', 'bt2020', 'st2084'
      --coding-eq <value>     Set the coding equations label
                              The <value> is a SMPTE UL, formatted as a 'urn:smpte:ul:...' or one of the following:
                                  'bt601', 'bt709', 'st240', 'ycgco', 'gbr', 'bt2020'
      --color-prim <value>    Set the color primaries label
                              The <value> is a SMPTE UL, formatted as a 'urn:smpte:ul:...' or one of the following:
                                  'st170', 'bt470', 'bt709', 'bt2020', 'dcdm', 'p3'
      --color-siting <value>  Set the color siting. The <value> is one of the following:
                                  'cositing', 'horizmp', '3tap', 'quincunx', 'bt601', 'linealt', 'vertmp', 'unknown'
                                  (Note that 'bt601' is deprecated in SMPTE ST 377-1. Use 'cositing' instead)
      --black-level <value>   Set the black reference level
      --white-level <value>   Set the white reference level
      --color-range <value>   Set the color range
      -s <bps>                Audio sampling rate numerator for raw pcm. Default 48000
      -q <bps>                Audio quantization bits per sample for raw pcm. Either 16 or 24. Default 16
      --audio-chan <count>    Audio channel count for raw pcm. Default 1
      --locked <bool>         Indicate whether the number of audio samples is locked to the video. Either true or false. Default not set
      --audio-ref <level>     Audio reference level, number of dBm for 0VU. Default not set
      --dial-norm <value>     Gain to be applied to normalize perceived loudness of the clip. Default not set
      --anc-const <size>      Set the constant ANC data frame <size>
      --vbi-const <size>      Set the constant VBI data frame <size>
      --off <bytes>           Skip <bytes> at the start of the next input/track's file
      --maxlen <bytes>        Maximum number of essence data bytes to read from next input/track's file
      --klv <key>             Essence data is read from the KLV data in the next input/track's file
                              <key> should have one of the following values:
                                - 's', which means the first 16 bytes, at file position 0 or --off byte offset, are taken to be the Key
                                - optional '0x' followed by 8 hexadecimal characters which represents the 4-byte track number part of a generic container essence Key
                                - 32 hexadecimal characters representing a 16-byte Key
      --track-num <num>       Set the output track number. Default track number equals last track number of same picture/sound type + 1
                              For as11d10/d10 the track number must be > 0 and <= 8 because the AES-3 channel index equals track number - 1
      --avci-guess <i/p>      Guess interlaced ('i') or progressive ('p') AVC-Intra when using the --avci option with 1080p25/i50 or 1080p30/i60
                              The default guess uses the H.264 frame_mbs_only_flag field
      --fixed-size            Set to indicate that the d10 frames have a fixed size and therefore do not need to be parsed after the first frame
      --vc2-mode <mode>       Set the mode that determines how the VC-2 data is wrapped
                              <mode> is one of the following integer values:
                                0: Passthrough input, but add a sequence header if not present, remove duplicate/redundant sequence headers
                                   and fix any incorrect parse info offsets and picture numbers
                                1: (default) Same as 0, but remove auxiliary and padding data units and complete the sequence in each frame

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
      --avci <name>           Raw AVC-Intra video input file. See also --avci-guess option
      --avci200_1080i <name>  Raw AVC-Intra 200 1080i video input file
      --avci200_1080p <name>  Raw AVC-Intra 200 1080p video input file
      --avci200_720p <name>   Raw AVC-Intra 200 720p video input file
      --avci100_1080i <name>  Raw AVC-Intra 100 1080i video input file
      --avci100_1080p <name>  Raw AVC-Intra 100 1080p video input file
      --avci100_720p <name>   Raw AVC-Intra 100 720p video input file
      --avci50_1080i <name>   Raw AVC-Intra 50 1080i video input file
      --avci50_1080p <name>   Raw AVC-Intra 50 1080p video input file
      --avci50_720p <name>    Raw AVC-Intra 50 720p video input file
      --avc <name>                 Raw AVC video input file
      --avc_baseline <name>        Raw AVC Baseline profile video input file
      --avc_constr_baseline <name> Raw AVC Constrained Baseline profile video input file
      --avc_main <name>            Raw AVC Main profile video input file
      --avc_extended <name>        Raw AVC Extended profile video input file
      --avc_high <name>            Raw AVC High profile video input file
      --avc_high_10 <name>         Raw AVC High 10 profile video input file
      --avc_high_422 <name>        Raw AVC High 422 profile video input file
      --avc_high_444 <name>        Raw AVC High 444 profile video input file
      --avc_high_10_intra <name>   Raw AVC High 10 Intra profile video input file
      --avc_high_422_intra <name>  Raw AVC High 422 Intra profile video input file
      --avc_high_444_intra <name>  Raw AVC High 444 Intra profile video input file
      --avc_cavlc_444 <name>       Raw AVC CAVLC 444 profile video input file
      --unc <name>            Raw uncompressed SD UYVY 422 video input file
      --unc_1080i <name>      Raw uncompressed HD 1080i UYVY 422 video input file
      --unc_1080p <name>      Raw uncompressed HD 1080p UYVY 422 video input file
      --unc_720p <name>       Raw uncompressed HD 720p UYVY 422 video input file
      --unc_3840 <name>       Raw uncompressed UHD 3840x2160 UYVY 422 video input file
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
      --vc2 <name>            Raw VC2 input file
      --vc3 <name>            Raw VC3/DNxHD input file
      --vc3_1080p_1235 <name> Raw VC3/DNxHD 1920x1080p 220/185/175 Mbps 10bit input file
      --vc3_1080p_1237 <name> Raw VC3/DNxHD 1920x1080p 145/120/115 Mbps input file
      --vc3_1080p_1238 <name> Raw VC3/DNxHD 1920x1080p 220/185/175 Mbps input file
      --vc3_1080i_1241 <name> Raw VC3/DNxHD 1920x1080i 220/185 Mbps 10bit input file
      --vc3_1080i_1242 <name> Raw VC3/DNxHD 1920x1080i 145/120 Mbps input file
      --vc3_1080i_1243 <name> Raw VC3/DNxHD 1920x1080i 220/185 Mbps input file
      --vc3_1080i_1244 <name> Raw VC3/DNxHD 1920x1080i 145/120 Mbps input file
      --vc3_720p_1250 <name>  Raw VC3/DNxHD 1280x720p 220/185/110/90 Mbps 10bit input file
      --vc3_720p_1251 <name>  Raw VC3/DNxHD 1280x720p 220/185/110/90 Mbps input file
      --vc3_720p_1252 <name>  Raw VC3/DNxHD 1280x720p 220/185/110/90 Mbps input file
      --vc3_1080p_1253 <name> Raw VC3/DNxHD 1920x1080p 45/36 Mbps input file
      --vc3_720p_1258 <name>  Raw VC3/DNxHD 1280x720p 45 Mbps input file
      --vc3_1080p_1259 <name> Raw VC3/DNxHD 1920x1080p 85 Mbps input file
      --vc3_1080i_1260 <name> Raw VC3/DNxHD 1920x1080i 85 Mbps input file
      --pcm <name>            Raw PCM audio input file
      --wave <name>           Wave PCM audio input file
      --anc <name>            Raw ST 436 Ancillary data. Currently requires the --anc-const option
      --vbi <name>            Raw ST 436 Vertical Blanking Interval data. Currently requires the --vbi-const option


    Notes:
     - <umid> format is 64 hexadecimal characters and any '.' and '-' characters are ignored
     - <uuid> format is 32 hexadecimal characters and any '.' and '-' characters are ignored
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
     --strict              Perform a strict, fully ST-434-compliant analysis.

## Examples

### Embedding EBU Core metadata using SMPTE RP-2057.

Embed the XML file 20120817.xml into the clip.mxf file, writing the new header metadata at the footer of the file, using the default XML metadata scheme ID.

    ebu2mxf.exe --rp2057 --ebucore 20120817.xml clip.mxf

Embed the XML file 20120817.xml into the clip.mxf file, forcing the new header metadata to replace the existing header metadata in the header partition.
    
    ebu2mxf.exe --force-header --rp2057 --ebucore 20120817.xml clip.mxf
    
Embed the XML file 20120817.xml into the clip.mxf file, using the provided XML metadata scheme ID and XML language identifier 
(e.g., in case this cannot be retrieved from the XML document and an empty string is not wanted).
        
    ebu2mxf.exe --rp2057 --xml-scheme-id urn:smpte:ul:060E2B34027F010B0D02010000000000 --xml-lang fr --ebucore 20120817.xml clip.mxf
     
## Documentation

Further documentation about the workings of the SDK, its use and developer documentation is available in the following resources:

* doc/EBU MXF SDK.pdf: Provides a high-level overview of the internal structure of the SDK an MXF manipulation techniques used.
* doc/doxygen/html/index.html: Provides the developer documentation with information about how the SDK's functions are to be used and embedded in custom applications.


## License

Copyright 2012-2017 European Broadcasting Union and Limecraft, NV.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   [http://www.apache.org/licenses/LICENSE-2.0](http://www.apache.org/licenses/LICENSE-2.0)

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
