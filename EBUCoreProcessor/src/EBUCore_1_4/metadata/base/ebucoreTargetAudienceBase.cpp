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


const mxfKey ebucoreTargetAudienceBase::setKey = MXF_SET_K(ebucoreTargetAudience);


ebucoreTargetAudienceBase::ebucoreTargetAudienceBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreTargetAudienceBase::ebucoreTargetAudienceBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreTargetAudienceBase::~ebucoreTargetAudienceBase()
{}


bool ebucoreTargetAudienceBase::havetargetAudienceReason() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceReason));
}

std::string ebucoreTargetAudienceBase::gettargetAudienceReason() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceReason));
}

bool ebucoreTargetAudienceBase::havetargetAudienceLinkToLogo() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceLinkToLogo));
}

std::string ebucoreTargetAudienceBase::gettargetAudienceLinkToLogo() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceLinkToLogo));
}

bool ebucoreTargetAudienceBase::havetargetAudienceNotRatedFlag() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceNotRatedFlag));
}

bool ebucoreTargetAudienceBase::gettargetAudienceNotRatedFlag() const
{
    return getBooleanItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceNotRatedFlag));
}

bool ebucoreTargetAudienceBase::havetargetAudienceAdultContentFlag() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceAdultContentFlag));
}

bool ebucoreTargetAudienceBase::gettargetAudienceAdultContentFlag() const
{
    return getBooleanItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceAdultContentFlag));
}

bool ebucoreTargetAudienceBase::havetargetAudienceTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceTypeGroup));
}

ebucoreTypeGroup* ebucoreTargetAudienceBase::gettargetAudienceTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreTargetAudienceBase::havetargetAudienceRegion() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceRegion));
}

std::vector<ebucoreRegion*> ebucoreTargetAudienceBase::gettargetAudienceRegion() const
{
    vector<ebucoreRegion*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceRegion)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreRegion*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreRegion*>(iter->get()));
    }
    return result;
}

void ebucoreTargetAudienceBase::settargetAudienceReason(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceReason), value);
}

void ebucoreTargetAudienceBase::settargetAudienceLinkToLogo(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceLinkToLogo), value);
}

void ebucoreTargetAudienceBase::settargetAudienceNotRatedFlag(bool value)
{
    setBooleanItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceNotRatedFlag), value);
}

void ebucoreTargetAudienceBase::settargetAudienceAdultContentFlag(bool value)
{
    setBooleanItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceAdultContentFlag), value);
}

void ebucoreTargetAudienceBase::settargetAudienceTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceTypeGroup), value);
}

void ebucoreTargetAudienceBase::settargetAudienceRegion(const std::vector<ebucoreRegion*>& value)
{
    WrapObjectVectorIterator<ebucoreRegion> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceRegion), &iter);
}

void ebucoreTargetAudienceBase::appendtargetAudienceRegion(ebucoreRegion* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceRegion), value);
}

