 /*
  *    Copyright 2012-2013 European Broadcasting Union and Limecraft, NV.
  *
  *    Licensed under the Apache License, Version 2.0 (the "License");
  *    you may not use this file except in compliance with the License.
  *    You may obtain a copy of the License at
  *
  *       http://www.apache.org/licenses/LICENSE-2.0
  *
  *    Unless required by applicable law or agreed to in writing, software
  *    distributed under the License is distributed on an "AS IS" BASIS,
  *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  *    See the License for the specific language governing permissions and
  *    limitations under the License.
  *
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

bool ebucoreContactBase::havefamilyName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, familyName));
}

std::string ebucoreContactBase::getfamilyName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreContact, familyName));
}

bool ebucoreContactBase::havegivenName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, givenName));
}

std::string ebucoreContactBase::getgivenName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreContact, givenName));
}

bool ebucoreContactBase::havesalutation() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, salutation));
}

std::string ebucoreContactBase::getsalutation() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreContact, salutation));
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

std::string ebucoreContactBase::getusername() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreContact, username));
}

bool ebucoreContactBase::haveguestFlag() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, guestFlag));
}

bool ebucoreContactBase::getguestFlag() const
{
    return getBooleanItem(&MXF_ITEM_K(ebucoreContact, guestFlag));
}

bool ebucoreContactBase::havecontactName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, contactName));
}

std::vector<ebucoreCompoundName*> ebucoreContactBase::getcontactName() const
{
    vector<ebucoreCompoundName*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, contactName)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreCompoundName*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreCompoundName*>(iter->get()));
    }
    return result;
}

bool ebucoreContactBase::havecontactType() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, contactType));
}

ebucoreTypeGroup* ebucoreContactBase::getcontactType() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreContact, contactType)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreContactBase::havecontactDetails() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, contactDetails));
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

bool ebucoreContactBase::havecontactRelatedContacts() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, contactRelatedContacts));
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

bool ebucoreContactBase::havegender() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, gender));
}

ebucoreTextualAnnotation* ebucoreContactBase::getgender() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreContact, gender)));
    MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTextualAnnotation*>(obj.release());
}

bool ebucoreContactBase::havecontactRelatedInformationLink() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContact, contactRelatedInformationLink));
}

std::vector<ebucoreBasicLink*> ebucoreContactBase::getcontactRelatedInformationLink() const
{
    vector<ebucoreBasicLink*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, contactRelatedInformationLink)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreBasicLink*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreBasicLink*>(iter->get()));
    }
    return result;
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

void ebucoreContactBase::setcontactId(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContact, contactId), value);
}

void ebucoreContactBase::setfamilyName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContact, familyName), value);
}

void ebucoreContactBase::setgivenName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContact, givenName), value);
}

void ebucoreContactBase::setsalutation(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContact, salutation), value);
}

void ebucoreContactBase::setsuffix(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContact, suffix), value);
}

void ebucoreContactBase::setoccupation(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContact, occupation), value);
}

void ebucoreContactBase::setusername(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContact, username), value);
}

void ebucoreContactBase::setguestFlag(bool value)
{
    setBooleanItem(&MXF_ITEM_K(ebucoreContact, guestFlag), value);
}

void ebucoreContactBase::setcontactName(const std::vector<ebucoreCompoundName*>& value)
{
    WrapObjectVectorIterator<ebucoreCompoundName> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, contactName), &iter);
}

void ebucoreContactBase::appendcontactName(ebucoreCompoundName* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, contactName), value);
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

void ebucoreContactBase::setgender(ebucoreTextualAnnotation* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreContact, gender), value);
}

void ebucoreContactBase::setcontactRelatedInformationLink(const std::vector<ebucoreBasicLink*>& value)
{
    WrapObjectVectorIterator<ebucoreBasicLink> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, contactRelatedInformationLink), &iter);
}

void ebucoreContactBase::appendcontactRelatedInformationLink(ebucoreBasicLink* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreContact, contactRelatedInformationLink), value);
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

