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


const mxfKey ebucoreRightsBase::setKey = MXF_SET_K(ebucoreRights);


ebucoreRightsBase::ebucoreRightsBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreRightsBase::ebucoreRightsBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreRightsBase::~ebucoreRightsBase()
{}


bool ebucoreRightsBase::haverightsId() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsId));
}

std::string ebucoreRightsBase::getrightsId() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreRights, rightsId));
}

bool ebucoreRightsBase::haverightsValue() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsValue));
}

std::string ebucoreRightsBase::getrightsValue() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreRights, rightsValue));
}

bool ebucoreRightsBase::haverightsLanguage() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsLanguage));
}

std::string ebucoreRightsBase::getrightsLanguage() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreRights, rightsLanguage));
}

bool ebucoreRightsBase::haverightsLink() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsLink));
}

std::string ebucoreRightsBase::getrightsLink() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreRights, rightsLink));
}

bool ebucoreRightsBase::haverightsClearanceFlag() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsClearanceFlag));
}

bool ebucoreRightsBase::getrightsClearanceFlag() const
{
    return getBooleanItem(&MXF_ITEM_K(ebucoreRights, rightsClearanceFlag));
}

bool ebucoreRightsBase::haverightsAttributedID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsAttributedID));
}

std::string ebucoreRightsBase::getrightsAttributedID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreRights, rightsAttributedID));
}

bool ebucoreRightsBase::haverightsFormatIDRef() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsFormatIDRef));
}

std::string ebucoreRightsBase::getrightsFormatIDRef() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreRights, rightsFormatIDRef));
}

bool ebucoreRightsBase::haveexploitationIssues() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, exploitationIssues));
}

std::string ebucoreRightsBase::getexploitationIssues() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreRights, exploitationIssues));
}

bool ebucoreRightsBase::haverightsCoverage() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsCoverage));
}

std::vector<ebucoreCoverage*> ebucoreRightsBase::getrightsCoverage() const
{
    vector<ebucoreCoverage*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsCoverage)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreCoverage*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreCoverage*>(iter->get()));
    }
    return result;
}

bool ebucoreRightsBase::haverightsHolderEntity() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsHolderEntity));
}

std::vector<ebucoreEntity*> ebucoreRightsBase::getrightsHolderEntity() const
{
    vector<ebucoreEntity*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsHolderEntity)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreEntity*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreEntity*>(iter->get()));
    }
    return result;
}

bool ebucoreRightsBase::haverightsContacts() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsContacts));
}

std::vector<ebucoreContact*> ebucoreRightsBase::getrightsContacts() const
{
    vector<ebucoreContact*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsContacts)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreContact*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreContact*>(iter->get()));
    }
    return result;
}

ebucoreTypeGroup* ebucoreRightsBase::getrightsKindGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreRights, rightsKindGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

void ebucoreRightsBase::setrightsId(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreRights, rightsId), value);
}

void ebucoreRightsBase::setrightsValue(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreRights, rightsValue), value);
}

void ebucoreRightsBase::setrightsLanguage(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreRights, rightsLanguage), value);
}

void ebucoreRightsBase::setrightsLink(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreRights, rightsLink), value);
}

void ebucoreRightsBase::setrightsClearanceFlag(bool value)
{
    setBooleanItem(&MXF_ITEM_K(ebucoreRights, rightsClearanceFlag), value);
}

void ebucoreRightsBase::setrightsAttributedID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreRights, rightsAttributedID), value);
}

void ebucoreRightsBase::setrightsFormatIDRef(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreRights, rightsFormatIDRef), value);
}

void ebucoreRightsBase::setexploitationIssues(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreRights, exploitationIssues), value);
}

void ebucoreRightsBase::setrightsCoverage(const std::vector<ebucoreCoverage*>& value)
{
    WrapObjectVectorIterator<ebucoreCoverage> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsCoverage), &iter);
}

void ebucoreRightsBase::appendrightsCoverage(ebucoreCoverage* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsCoverage), value);
}

void ebucoreRightsBase::setrightsHolderEntity(const std::vector<ebucoreEntity*>& value)
{
    WrapObjectVectorIterator<ebucoreEntity> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsHolderEntity), &iter);
}

void ebucoreRightsBase::appendrightsHolderEntity(ebucoreEntity* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsHolderEntity), value);
}

void ebucoreRightsBase::setrightsContacts(const std::vector<ebucoreContact*>& value)
{
    WrapObjectVectorIterator<ebucoreContact> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsContacts), &iter);
}

void ebucoreRightsBase::appendrightsContacts(ebucoreContact* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsContacts), value);
}

void ebucoreRightsBase::setrightsKindGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreRights, rightsKindGroup), value);
}

