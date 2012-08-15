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
#include <metadata/EBUCoreDMS++.h>


using namespace std;
using namespace mxfpp;
using namespace EBUCore::KLV;


const mxfKey ebucorePartMetadataBase::setKey = MXF_SET_K(ebucorePartMetadata);


ebucorePartMetadataBase::ebucorePartMetadataBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucorePartMetadataBase::ebucorePartMetadataBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucorePartMetadataBase::~ebucorePartMetadataBase()
{}


std::string ebucorePartMetadataBase::getpartId() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePartMetadata, partId));
}

std::string ebucorePartMetadataBase::getpartName() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePartMetadata, partName));
}

bool ebucorePartMetadataBase::havepartDefinition() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partDefinition));
}

std::string ebucorePartMetadataBase::getpartDefinition() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePartMetadata, partDefinition));
}

bool ebucorePartMetadataBase::havepartStartTime() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partStartTime));
}

mxfRational ebucorePartMetadataBase::getpartStartTime() const
{
    return getRationalItem(&MXF_ITEM_K(ebucorePartMetadata, partStartTime));
}

bool ebucorePartMetadataBase::havepartStartEditUnitNumber() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partStartEditUnitNumber));
}

int64_t ebucorePartMetadataBase::getpartStartEditUnitNumber() const
{
    return getLengthItem(&MXF_ITEM_K(ebucorePartMetadata, partStartEditUnitNumber));
}

bool ebucorePartMetadataBase::havepartEndTime() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partEndTime));
}

mxfRational ebucorePartMetadataBase::getpartEndTime() const
{
    return getRationalItem(&MXF_ITEM_K(ebucorePartMetadata, partEndTime));
}

bool ebucorePartMetadataBase::havepartEndEditUnitNumber() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partEndEditUnitNumber));
}

int64_t ebucorePartMetadataBase::getpartEndEditUnitNumber() const
{
    return getLengthItem(&MXF_ITEM_K(ebucorePartMetadata, partEndEditUnitNumber));
}

bool ebucorePartMetadataBase::havepartDurationTime() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partDurationTime));
}

mxfRational ebucorePartMetadataBase::getpartDurationTime() const
{
    return getRationalItem(&MXF_ITEM_K(ebucorePartMetadata, partDurationTime));
}

bool ebucorePartMetadataBase::havepartDurationEditUnitNumber() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partDurationEditUnitNumber));
}

int64_t ebucorePartMetadataBase::getpartDurationEditUnitNumber() const
{
    return getLengthItem(&MXF_ITEM_K(ebucorePartMetadata, partDurationEditUnitNumber));
}

bool ebucorePartMetadataBase::havepartTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partTypeGroup));
}

std::string ebucorePartMetadataBase::getpartTypeGroup() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePartMetadata, partTypeGroup));
}

ebucoreCoreMetadata* ebucorePartMetadataBase::getpartMeta() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucorePartMetadata, partMeta)));
    MXFPP_CHECK(dynamic_cast<ebucoreCoreMetadata*>(obj.get()) != 0);
    return dynamic_cast<ebucoreCoreMetadata*>(obj.release());
}

void ebucorePartMetadataBase::setpartId(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePartMetadata, partId), value);
}

void ebucorePartMetadataBase::setpartName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePartMetadata, partName), value);
}

void ebucorePartMetadataBase::setpartDefinition(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePartMetadata, partDefinition), value);
}

void ebucorePartMetadataBase::setpartStartTime(mxfRational value)
{
    setRationalItem(&MXF_ITEM_K(ebucorePartMetadata, partStartTime), value);
}

void ebucorePartMetadataBase::setpartStartEditUnitNumber(int64_t value)
{
    setLengthItem(&MXF_ITEM_K(ebucorePartMetadata, partStartEditUnitNumber), value);
}

void ebucorePartMetadataBase::setpartEndTime(mxfRational value)
{
    setRationalItem(&MXF_ITEM_K(ebucorePartMetadata, partEndTime), value);
}

void ebucorePartMetadataBase::setpartEndEditUnitNumber(int64_t value)
{
    setLengthItem(&MXF_ITEM_K(ebucorePartMetadata, partEndEditUnitNumber), value);
}

void ebucorePartMetadataBase::setpartDurationTime(mxfRational value)
{
    setRationalItem(&MXF_ITEM_K(ebucorePartMetadata, partDurationTime), value);
}

void ebucorePartMetadataBase::setpartDurationEditUnitNumber(int64_t value)
{
    setLengthItem(&MXF_ITEM_K(ebucorePartMetadata, partDurationEditUnitNumber), value);
}

void ebucorePartMetadataBase::setpartTypeGroup(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePartMetadata, partTypeGroup), value);
}

void ebucorePartMetadataBase::setpartMeta(ebucoreCoreMetadata* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucorePartMetadata, partMeta), value);
}

