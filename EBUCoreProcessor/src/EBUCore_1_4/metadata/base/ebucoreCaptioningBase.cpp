/*
 * Copyright (C) 2008, British Broadcasting Corporation
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

#include <memory>

#include <libMXF++/MXF.h>
#include <EBUCore_1_5/metadata/EBUCoreDMS++.h>


using namespace std;
using namespace mxfpp;
using namespace EBUSDK::EBUCore::EBUCore_1_4::KLV;


const mxfKey ebucoreCaptioningBase::setKey = MXF_SET_K(ebucoreCaptioning);


ebucoreCaptioningBase::ebucoreCaptioningBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreCaptioningBase::ebucoreCaptioningBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreCaptioningBase::~ebucoreCaptioningBase()
{}


bool ebucoreCaptioningBase::havecaptioningFormatID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCaptioning, captioningFormatID));
}

std::string ebucoreCaptioningBase::getcaptioningFormatID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningFormatID));
}

bool ebucoreCaptioningBase::havecaptioningFormatName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCaptioning, captioningFormatName));
}

std::string ebucoreCaptioningBase::getcaptioningFormatName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningFormatName));
}

bool ebucoreCaptioningBase::havecaptioningFormatDefinition() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCaptioning, captioningFormatDefinition));
}

std::string ebucoreCaptioningBase::getcaptioningFormatDefinition() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningFormatDefinition));
}

bool ebucoreCaptioningBase::havecaptioningSourceUri() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCaptioning, captioningSourceUri));
}

std::string ebucoreCaptioningBase::getcaptioningSourceUri() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningSourceUri));
}

bool ebucoreCaptioningBase::havecaptioningLanguageName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCaptioning, captioningLanguageName));
}

std::string ebucoreCaptioningBase::getcaptioningLanguageName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningLanguageName));
}

bool ebucoreCaptioningBase::havecaptioningLanguageCode() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCaptioning, captioningLanguageCode));
}

std::string ebucoreCaptioningBase::getcaptioningLanguageCode() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningLanguageCode));
}

bool ebucoreCaptioningBase::havecaptioningTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCaptioning, captioningTypeGroup));
}

ebucoreTypeGroup* ebucoreCaptioningBase::getcaptioningTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreCaptioning, captioningTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

void ebucoreCaptioningBase::setcaptioningFormatID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningFormatID), value);
}

void ebucoreCaptioningBase::setcaptioningFormatName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningFormatName), value);
}

void ebucoreCaptioningBase::setcaptioningFormatDefinition(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningFormatDefinition), value);
}

void ebucoreCaptioningBase::setcaptioningSourceUri(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningSourceUri), value);
}

void ebucoreCaptioningBase::setcaptioningLanguageName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningLanguageName), value);
}

void ebucoreCaptioningBase::setcaptioningLanguageCode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningLanguageCode), value);
}

void ebucoreCaptioningBase::setcaptioningTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreCaptioning, captioningTypeGroup), value);
}

