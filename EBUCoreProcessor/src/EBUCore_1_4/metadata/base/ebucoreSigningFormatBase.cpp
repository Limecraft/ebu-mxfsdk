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


const mxfKey ebucoreSigningFormatBase::setKey = MXF_SET_K(ebucoreSigningFormat);


ebucoreSigningFormatBase::ebucoreSigningFormatBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreSigningFormatBase::ebucoreSigningFormatBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreSigningFormatBase::~ebucoreSigningFormatBase()
{}


bool ebucoreSigningFormatBase::havesigningTrackID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackID));
}

std::string ebucoreSigningFormatBase::getsigningTrackID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackID));
}

bool ebucoreSigningFormatBase::havesigningTrackName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackName));
}

std::string ebucoreSigningFormatBase::getsigningTrackName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackName));
}

bool ebucoreSigningFormatBase::havesigningTrackLanguageName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackLanguageName));
}

std::string ebucoreSigningFormatBase::getsigningTrackLanguageName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackLanguageName));
}

bool ebucoreSigningFormatBase::havesigningTrackLanguageCode() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackLanguageCode));
}

std::string ebucoreSigningFormatBase::getsigningTrackLanguageCode() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackLanguageCode));
}

bool ebucoreSigningFormatBase::havesigningSourceUri() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSigningFormat, signingSourceUri));
}

std::string ebucoreSigningFormatBase::getsigningSourceUri() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingSourceUri));
}

bool ebucoreSigningFormatBase::havesigningTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTypeGroup));
}

ebucoreTypeGroup* ebucoreSigningFormatBase::getsigningTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreSigningFormatBase::havesigningFormatGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSigningFormat, signingFormatGroup));
}

ebucoreFormatGroup* ebucoreSigningFormatBase::getsigningFormatGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreSigningFormat, signingFormatGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreFormatGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreFormatGroup*>(obj.release());
}

void ebucoreSigningFormatBase::setsigningTrackID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackID), value);
}

void ebucoreSigningFormatBase::setsigningTrackName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackName), value);
}

void ebucoreSigningFormatBase::setsigningTrackLanguageName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackLanguageName), value);
}

void ebucoreSigningFormatBase::setsigningTrackLanguageCode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackLanguageCode), value);
}

void ebucoreSigningFormatBase::setsigningSourceUri(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingSourceUri), value);
}

void ebucoreSigningFormatBase::setsigningTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTypeGroup), value);
}

void ebucoreSigningFormatBase::setsigningFormatGroup(ebucoreFormatGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreSigningFormat, signingFormatGroup), value);
}

