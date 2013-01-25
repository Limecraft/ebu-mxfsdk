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
#include <EBUCore_1_4/metadata/EBUCoreDMS++.h>


using namespace std;
using namespace mxfpp;
using namespace EBUSDK::EBUCore::EBUCore_1_4::KLV;


const mxfKey ebucoreSubtitlingBase::setKey = MXF_SET_K(ebucoreSubtitling);


ebucoreSubtitlingBase::ebucoreSubtitlingBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreSubtitlingBase::ebucoreSubtitlingBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreSubtitlingBase::~ebucoreSubtitlingBase()
{}


bool ebucoreSubtitlingBase::havesubtitlingFormatID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingFormatID));
}

std::string ebucoreSubtitlingBase::getsubtitlingFormatID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingFormatID));
}

bool ebucoreSubtitlingBase::havesubtitlingFormatName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingFormatName));
}

std::string ebucoreSubtitlingBase::getsubtitlingFormatName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingFormatName));
}

bool ebucoreSubtitlingBase::havesubtitlingSourceUri() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingSourceUri));
}

std::string ebucoreSubtitlingBase::getsubtitlingSourceUri() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingSourceUri));
}

bool ebucoreSubtitlingBase::havesubtitlingTrackID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingTrackID));
}

std::string ebucoreSubtitlingBase::getsubtitlingTrackID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingTrackID));
}

bool ebucoreSubtitlingBase::havesubtitlingTrackName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingTrackName));
}

std::string ebucoreSubtitlingBase::getsubtitlingTrackName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingTrackName));
}

bool ebucoreSubtitlingBase::havesubtitlingLanguageCode() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingLanguageCode));
}

std::string ebucoreSubtitlingBase::getsubtitlingLanguageCode() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingLanguageCode));
}

bool ebucoreSubtitlingBase::havesubtitlingTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingTypeGroup));
}

ebucoreTypeGroup* ebucoreSubtitlingBase::getsubtitlingTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreSubtitlingBase::havesubtitlingFormatGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingFormatGroup));
}

ebucoreFormatGroup* ebucoreSubtitlingBase::getsubtitlingFormatGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingFormatGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreFormatGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreFormatGroup*>(obj.release());
}

void ebucoreSubtitlingBase::setsubtitlingFormatID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingFormatID), value);
}

void ebucoreSubtitlingBase::setsubtitlingFormatName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingFormatName), value);
}

void ebucoreSubtitlingBase::setsubtitlingSourceUri(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingSourceUri), value);
}

void ebucoreSubtitlingBase::setsubtitlingTrackID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingTrackID), value);
}

void ebucoreSubtitlingBase::setsubtitlingTrackName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingTrackName), value);
}

void ebucoreSubtitlingBase::setsubtitlingLanguageCode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingLanguageCode), value);
}

void ebucoreSubtitlingBase::setsubtitlingTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingTypeGroup), value);
}

void ebucoreSubtitlingBase::setsubtitlingFormatGroup(ebucoreFormatGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingFormatGroup), value);
}

