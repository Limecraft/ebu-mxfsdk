/*
 * Copyright (C) 2011, British Broadcasting Corporation
 * All Rights Reserved.
 *
 * Author: Philip de Nier
 *
 * Modifications Copyright (C) 2012-2013, European Broadcasting Union and Limecraft, NV.
 *
 * Author: Dieter Van Rijsselbergen
 *
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

#ifndef __BMX_VERSION_H__
#define __BMX_VERSION_H__


#include <string>

#include <bmx/BMXTypes.h>


#define EBUSDK_VERSION_MAJOR    1
#define EBUSDK_VERSION_MINOR    2
#define EBUSDK_VERSION_MICRO    0

#define EBUSDK_MXF_VERSION_RELEASE  4   /* 0 = Unknown version
                                        1 = Released version
                                        2 = Development version
                                        3 = Released version with patches
                                        4 = Pre-release beta version
                                        5 = Private version not intended for general release */

#define EBUSDK_VERSION          (EBUSDK_VERSION_MAJOR << 16 | EBUSDK_VERSION_MINOR << 8 | EBUSDK_VERSION_MICRO)

#define EBUSDK_LIBRARY_NAME     "ebu-mxfsdk"


#ifdef EXPORTING
#define DLLEXPORT __declspec(dllexport)
#elif IMPORTING
#define DLLEXPORT __declspec(dllimport)
#else
#define DLLEXPORT
#endif

namespace EBUSDK
{

DLLEXPORT std::string get_library_name();
DLLEXPORT std::string get_version_string();
DLLEXPORT std::string get_scm_version_string();
DLLEXPORT std::string get_build_string();

DLLEXPORT std::string get_company_name();
DLLEXPORT bmx::UUID get_product_uid();
DLLEXPORT mxfProductVersion get_mxf_product_version();
DLLEXPORT std::string get_mxf_version_string();

};



#endif

