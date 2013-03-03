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

