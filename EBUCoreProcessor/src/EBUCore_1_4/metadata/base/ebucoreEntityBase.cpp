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


const mxfKey ebucoreEntityBase::setKey = MXF_SET_K(ebucoreEntity);


ebucoreEntityBase::ebucoreEntityBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreEntityBase::ebucoreEntityBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreEntityBase::~ebucoreEntityBase()
{}


bool ebucoreEntityBase::haveentityId() const
{
    return haveItem(&MXF_ITEM_K(ebucoreEntity, entityId));
}

std::string ebucoreEntityBase::getentityId() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreEntity, entityId));
}

bool ebucoreEntityBase::haveentityContact() const
{
    return haveItem(&MXF_ITEM_K(ebucoreEntity, entityContact));
}

std::vector<ebucoreContact*> ebucoreEntityBase::getentityContact() const
{
    vector<ebucoreContact*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreEntity, entityContact)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreContact*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreContact*>(iter->get()));
    }
    return result;
}

bool ebucoreEntityBase::haveentityOrganisation() const
{
    return haveItem(&MXF_ITEM_K(ebucoreEntity, entityOrganisation));
}

std::vector<ebucoreOrganisation*> ebucoreEntityBase::getentityOrganisation() const
{
    vector<ebucoreOrganisation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreEntity, entityOrganisation)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreOrganisation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreOrganisation*>(iter->get()));
    }
    return result;
}

bool ebucoreEntityBase::haveentityRole() const
{
    return haveItem(&MXF_ITEM_K(ebucoreEntity, entityRole));
}

std::vector<ebucoreRole*> ebucoreEntityBase::getentityRole() const
{
    vector<ebucoreRole*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreEntity, entityRole)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreRole*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreRole*>(iter->get()));
    }
    return result;
}

void ebucoreEntityBase::setentityId(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreEntity, entityId), value);
}

void ebucoreEntityBase::setentityContact(const std::vector<ebucoreContact*>& value)
{
    WrapObjectVectorIterator<ebucoreContact> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreEntity, entityContact), &iter);
}

void ebucoreEntityBase::appendentityContact(ebucoreContact* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreEntity, entityContact), value);
}

void ebucoreEntityBase::setentityOrganisation(const std::vector<ebucoreOrganisation*>& value)
{
    WrapObjectVectorIterator<ebucoreOrganisation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreEntity, entityOrganisation), &iter);
}

void ebucoreEntityBase::appendentityOrganisation(ebucoreOrganisation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreEntity, entityOrganisation), value);
}

void ebucoreEntityBase::setentityRole(const std::vector<ebucoreRole*>& value)
{
    WrapObjectVectorIterator<ebucoreRole> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreEntity, entityRole), &iter);
}

void ebucoreEntityBase::appendentityRole(ebucoreRole* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreEntity, entityRole), value);
}

