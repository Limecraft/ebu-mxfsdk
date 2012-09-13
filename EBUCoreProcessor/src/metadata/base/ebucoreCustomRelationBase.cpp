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
using namespace EBUSDK::EBUCore::KLV;


const mxfKey ebucoreCustomRelationBase::setKey = MXF_SET_K(ebucoreCustomRelation);


ebucoreCustomRelationBase::ebucoreCustomRelationBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreCustomRelationBase::ebucoreCustomRelationBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreCustomRelationBase::~ebucoreCustomRelationBase()
{}


bool ebucoreCustomRelationBase::haverelationByName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCustomRelation, relationByName));
}

std::string ebucoreCustomRelationBase::getrelationByName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCustomRelation, relationByName));
}

bool ebucoreCustomRelationBase::haverelationLink() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCustomRelation, relationLink));
}

std::string ebucoreCustomRelationBase::getrelationLink() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCustomRelation, relationLink));
}

bool ebucoreCustomRelationBase::haverunningOrderNumber() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCustomRelation, runningOrderNumber));
}

uint32_t ebucoreCustomRelationBase::getrunningOrderNumber() const
{
    return getUInt32Item(&MXF_ITEM_K(ebucoreCustomRelation, runningOrderNumber));
}

bool ebucoreCustomRelationBase::havetotalNumberOfGroupMembers() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCustomRelation, totalNumberOfGroupMembers));
}

uint32_t ebucoreCustomRelationBase::gettotalNumberOfGroupMembers() const
{
    return getUInt32Item(&MXF_ITEM_K(ebucoreCustomRelation, totalNumberOfGroupMembers));
}

bool ebucoreCustomRelationBase::haveorderedGroupFlag() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCustomRelation, orderedGroupFlag));
}

bool ebucoreCustomRelationBase::getorderedGroupFlag() const
{
    return getBooleanItem(&MXF_ITEM_K(ebucoreCustomRelation, orderedGroupFlag));
}

bool ebucoreCustomRelationBase::havecustomRelationTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCustomRelation, customRelationTypeGroup));
}

ebucoreTypeGroup* ebucoreCustomRelationBase::getcustomRelationTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreCustomRelation, customRelationTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreCustomRelationBase::haverelationIdentifier() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCustomRelation, relationIdentifier));
}

ebucoreIdentifier* ebucoreCustomRelationBase::getrelationIdentifier() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreCustomRelation, relationIdentifier)));
    MXFPP_CHECK(dynamic_cast<ebucoreIdentifier*>(obj.get()) != 0);
    return dynamic_cast<ebucoreIdentifier*>(obj.release());
}

void ebucoreCustomRelationBase::setrelationByName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCustomRelation, relationByName), value);
}

void ebucoreCustomRelationBase::setrelationLink(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCustomRelation, relationLink), value);
}

void ebucoreCustomRelationBase::setrunningOrderNumber(uint32_t value)
{
    setUInt32Item(&MXF_ITEM_K(ebucoreCustomRelation, runningOrderNumber), value);
}

void ebucoreCustomRelationBase::settotalNumberOfGroupMembers(uint32_t value)
{
    setUInt32Item(&MXF_ITEM_K(ebucoreCustomRelation, totalNumberOfGroupMembers), value);
}

void ebucoreCustomRelationBase::setorderedGroupFlag(bool value)
{
    setBooleanItem(&MXF_ITEM_K(ebucoreCustomRelation, orderedGroupFlag), value);
}

void ebucoreCustomRelationBase::setcustomRelationTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreCustomRelation, customRelationTypeGroup), value);
}

void ebucoreCustomRelationBase::setrelationIdentifier(ebucoreIdentifier* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreCustomRelation, relationIdentifier), value);
}

