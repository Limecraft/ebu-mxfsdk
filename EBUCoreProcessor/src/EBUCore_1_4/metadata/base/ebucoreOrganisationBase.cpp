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


const mxfKey ebucoreOrganisationBase::setKey = MXF_SET_K(ebucoreOrganisation);


ebucoreOrganisationBase::ebucoreOrganisationBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreOrganisationBase::ebucoreOrganisationBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreOrganisationBase::~ebucoreOrganisationBase()
{}


bool ebucoreOrganisationBase::haveorganisationId() const
{
    return haveItem(&MXF_ITEM_K(ebucoreOrganisation, organisationId));
}

std::string ebucoreOrganisationBase::getorganisationId() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreOrganisation, organisationId));
}

bool ebucoreOrganisationBase::haveorganisationLinkToLogo() const
{
    return haveItem(&MXF_ITEM_K(ebucoreOrganisation, organisationLinkToLogo));
}

std::string ebucoreOrganisationBase::getorganisationLinkToLogo() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreOrganisation, organisationLinkToLogo));
}

bool ebucoreOrganisationBase::haveorganisationCode() const
{
    return haveItem(&MXF_ITEM_K(ebucoreOrganisation, organisationCode));
}

std::vector<ebucoreIdentifier*> ebucoreOrganisationBase::getorganisationCode() const
{
    vector<ebucoreIdentifier*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationCode)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreIdentifier*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreIdentifier*>(iter->get()));
    }
    return result;
}

bool ebucoreOrganisationBase::haveorganisationRelatedInformationLink() const
{
    return haveItem(&MXF_ITEM_K(ebucoreOrganisation, organisationRelatedInformationLink));
}

std::vector<ebucoreBasicLink*> ebucoreOrganisationBase::getorganisationRelatedInformationLink() const
{
    vector<ebucoreBasicLink*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationRelatedInformationLink)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreBasicLink*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreBasicLink*>(iter->get()));
    }
    return result;
}

bool ebucoreOrganisationBase::haveorganisationName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreOrganisation, organisationName));
}

std::vector<ebucoreCompoundName*> ebucoreOrganisationBase::getorganisationName() const
{
    vector<ebucoreCompoundName*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationName)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreCompoundName*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreCompoundName*>(iter->get()));
    }
    return result;
}

bool ebucoreOrganisationBase::haveorganisationDepartment() const
{
    return haveItem(&MXF_ITEM_K(ebucoreOrganisation, organisationDepartment));
}

ebucoreOrganisationDepartment* ebucoreOrganisationBase::getorganisationDepartment() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreOrganisation, organisationDepartment)));
    MXFPP_CHECK(dynamic_cast<ebucoreOrganisationDepartment*>(obj.get()) != 0);
    return dynamic_cast<ebucoreOrganisationDepartment*>(obj.release());
}

bool ebucoreOrganisationBase::haveorganisationType() const
{
    return haveItem(&MXF_ITEM_K(ebucoreOrganisation, organisationType));
}

ebucoreTypeGroup* ebucoreOrganisationBase::getorganisationType() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreOrganisation, organisationType)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreOrganisationBase::haveorganisationDetails() const
{
    return haveItem(&MXF_ITEM_K(ebucoreOrganisation, organisationDetails));
}

std::vector<ebucoreContactDetails*> ebucoreOrganisationBase::getorganisationDetails() const
{
    vector<ebucoreContactDetails*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationDetails)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreContactDetails*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreContactDetails*>(iter->get()));
    }
    return result;
}

bool ebucoreOrganisationBase::haveorganisationRelatedContacts() const
{
    return haveItem(&MXF_ITEM_K(ebucoreOrganisation, organisationRelatedContacts));
}

std::vector<ebucoreEntity*> ebucoreOrganisationBase::getorganisationRelatedContacts() const
{
    vector<ebucoreEntity*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationRelatedContacts)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreEntity*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreEntity*>(iter->get()));
    }
    return result;
}

void ebucoreOrganisationBase::setorganisationId(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreOrganisation, organisationId), value);
}

void ebucoreOrganisationBase::setorganisationLinkToLogo(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreOrganisation, organisationLinkToLogo), value);
}

void ebucoreOrganisationBase::setorganisationCode(const std::vector<ebucoreIdentifier*>& value)
{
    WrapObjectVectorIterator<ebucoreIdentifier> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationCode), &iter);
}

void ebucoreOrganisationBase::appendorganisationCode(ebucoreIdentifier* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationCode), value);
}

void ebucoreOrganisationBase::setorganisationRelatedInformationLink(const std::vector<ebucoreBasicLink*>& value)
{
    WrapObjectVectorIterator<ebucoreBasicLink> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationRelatedInformationLink), &iter);
}

void ebucoreOrganisationBase::appendorganisationRelatedInformationLink(ebucoreBasicLink* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationRelatedInformationLink), value);
}

void ebucoreOrganisationBase::setorganisationName(const std::vector<ebucoreCompoundName*>& value)
{
    WrapObjectVectorIterator<ebucoreCompoundName> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationName), &iter);
}

void ebucoreOrganisationBase::appendorganisationName(ebucoreCompoundName* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationName), value);
}

void ebucoreOrganisationBase::setorganisationDepartment(ebucoreOrganisationDepartment* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreOrganisation, organisationDepartment), value);
}

void ebucoreOrganisationBase::setorganisationType(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreOrganisation, organisationType), value);
}

void ebucoreOrganisationBase::setorganisationDetails(const std::vector<ebucoreContactDetails*>& value)
{
    WrapObjectVectorIterator<ebucoreContactDetails> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationDetails), &iter);
}

void ebucoreOrganisationBase::appendorganisationDetails(ebucoreContactDetails* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationDetails), value);
}

void ebucoreOrganisationBase::setorganisationRelatedContacts(const std::vector<ebucoreEntity*>& value)
{
    WrapObjectVectorIterator<ebucoreEntity> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationRelatedContacts), &iter);
}

void ebucoreOrganisationBase::appendorganisationRelatedContacts(ebucoreEntity* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationRelatedContacts), value);
}

