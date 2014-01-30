/*
 * Copyright (C) 2011, British Broadcasting Corporation
 * All Rights Reserved.
 *
 * Author: Philip de Nier
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <bmx_scm_version.h>

#include <cstdio>

#include <Version.h>

using namespace std;


static const char* EBUSDK_COMPANY_NAME = "EBU";

// {7EF13EC5-7DBD-4FC0-8AA5-A9FEB1B70870}
static const bmx::UUID EBUSDK_PRODUCT_UID =
	{ 0x7e, 0xf1, 0x3e, 0xc5, 0x7d, 0xbd, 0x4f, 0xc0, 0x8a, 0xa5, 0xa9, 0xfe, 0xb1, 0xb7, 0x8, 0x70};
static const mxfProductVersion EBUSDK_MXF_PRODUCT_VERSION = {	EBUSDK_VERSION_MAJOR,
																EBUSDK_VERSION_MINOR,
																EBUSDK_VERSION_MICRO,
																0,
																EBUSDK_MXF_VERSION_RELEASE};



string EBUSDK::get_library_name()
{
	return EBUSDK_LIBRARY_NAME;
}

string EBUSDK::get_version_string()
{
    char buffer[32];
    sprintf(buffer, "%d.%d.%d", EBUSDK_VERSION_MAJOR, EBUSDK_VERSION_MINOR, EBUSDK_VERSION_MICRO);
    return buffer;
}

string EBUSDK::get_scm_version_string()
{
    return BMX_SCM_VERSION;
}

string EBUSDK::get_build_string()
{
    return __DATE__ " " __TIME__;
}

string EBUSDK::get_company_name()
{
	return EBUSDK_COMPANY_NAME;
}

bmx::UUID EBUSDK::get_product_uid()
{
    return EBUSDK_PRODUCT_UID;
}

mxfProductVersion EBUSDK::get_mxf_product_version()
{
    return EBUSDK_MXF_PRODUCT_VERSION;
}

string EBUSDK::get_mxf_version_string()
{
    char buffer[64];
    sprintf(buffer, "%d.%d.%d (scm %s)",
            EBUSDK_VERSION_MAJOR, EBUSDK_VERSION_MINOR, EBUSDK_VERSION_MICRO,
            BMX_SCM_VERSION);
    return buffer;
}
