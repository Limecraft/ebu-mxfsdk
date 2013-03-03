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

bool ebucoreCustomRelationBase::haverelationNote() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCustomRelation, relationNote));
}

std::string ebucoreCustomRelationBase::getrelationNote() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCustomRelation, relationNote));
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

void ebucoreCustomRelationBase::setrelationNote(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCustomRelation, relationNote), value);
}

void ebucoreCustomRelationBase::setcustomRelationTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreCustomRelation, customRelationTypeGroup), value);
}

void ebucoreCustomRelationBase::setrelationIdentifier(ebucoreIdentifier* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreCustomRelation, relationIdentifier), value);
}

