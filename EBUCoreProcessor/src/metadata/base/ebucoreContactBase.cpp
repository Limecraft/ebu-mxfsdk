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


const mxfKey ebucoreContactBase::setKey = MXF_SET_K(ebucoreContact);


ebucoreContactBase::ebucoreContactBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreContactBase::ebucoreContactBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreContactBase::~ebucoreContactBase()
{}


bool ebucoreContactBase::havecontactId() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, contactId));
}

std::string ebucoreContactBase::getcontactId() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreContact, contactId));
}

bool ebucoreContactBase::havecontactName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, contactName));
}

std::string ebucoreContactBase::getcontactName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreContact, contactName));
}

bool ebucoreContactBase::havefamilyName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, familyName));
}

std::string ebucoreContactBase::getfamilyName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreContact, familyName));
}

std::string ebucoreContactBase::getgivenName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreContact, givenName));
}

bool ebucoreContactBase::haveotherGivenName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, otherGivenName));
}

std::vector<ebucoreTextualAnnotation*> ebucoreContactBase::getotherGivenName() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, otherGivenName)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

bool ebucoreContactBase::havesaluation() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, saluation));
}

std::string ebucoreContactBase::getsaluation() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreContact, saluation));
}

bool ebucoreContactBase::havesuffix() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, suffix));
}

std::string ebucoreContactBase::getsuffix() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreContact, suffix));
}

bool ebucoreContactBase::haveoccupation() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, occupation));
}

std::string ebucoreContactBase::getoccupation() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreContact, occupation));
}

bool ebucoreContactBase::haveusername() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, username));
}

std::vector<ebucoreTextualAnnotation*> ebucoreContactBase::getusername() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, username)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

ebucoreTypeGroup* ebucoreContactBase::getcontactType() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreContact, contactType)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

std::vector<ebucoreContactDetails*> ebucoreContactBase::getcontactDetails() const
{
    vector<ebucoreContactDetails*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, contactDetails)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreContactDetails*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreContactDetails*>(iter->get()));
    }
    return result;
}

std::vector<ebucoreEntity*> ebucoreContactBase::getcontactRelatedContacts() const
{
    vector<ebucoreEntity*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, contactRelatedContacts)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreEntity*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreEntity*>(iter->get()));
    }
    return result;
}

bool ebucoreContactBase::havestageName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, stageName));
}

std::vector<ebucoreTextualAnnotation*> ebucoreContactBase::getstageName() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, stageName)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

void ebucoreContactBase::setcontactId(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContact, contactId), value);
}

void ebucoreContactBase::setcontactName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContact, contactName), value);
}

void ebucoreContactBase::setfamilyName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContact, familyName), value);
}

void ebucoreContactBase::setgivenName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContact, givenName), value);
}

void ebucoreContactBase::setotherGivenName(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, otherGivenName), &iter);
}

void ebucoreContactBase::appendotherGivenName(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, otherGivenName), value);
}

void ebucoreContactBase::setsaluation(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContact, saluation), value);
}

void ebucoreContactBase::setsuffix(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContact, suffix), value);
}

void ebucoreContactBase::setoccupation(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContact, occupation), value);
}

void ebucoreContactBase::setusername(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, username), &iter);
}

void ebucoreContactBase::appendusername(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, username), value);
}

void ebucoreContactBase::setcontactType(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreContact, contactType), value);
}

void ebucoreContactBase::setcontactDetails(const std::vector<ebucoreContactDetails*>& value)
{
    WrapObjectVectorIterator<ebucoreContactDetails> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, contactDetails), &iter);
}

void ebucoreContactBase::appendcontactDetails(ebucoreContactDetails* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, contactDetails), value);
}

void ebucoreContactBase::setcontactRelatedContacts(const std::vector<ebucoreEntity*>& value)
{
    WrapObjectVectorIterator<ebucoreEntity> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, contactRelatedContacts), &iter);
}

void ebucoreContactBase::appendcontactRelatedContacts(ebucoreEntity* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, contactRelatedContacts), value);
}

void ebucoreContactBase::setstageName(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, stageName), &iter);
}

void ebucoreContactBase::appendstageName(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, stageName), value);
}

