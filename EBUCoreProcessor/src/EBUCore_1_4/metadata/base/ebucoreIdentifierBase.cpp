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


const mxfKey ebucoreIdentifierBase::setKey = MXF_SET_K(ebucoreIdentifier);


ebucoreIdentifierBase::ebucoreIdentifierBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreIdentifierBase::ebucoreIdentifierBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreIdentifierBase::~ebucoreIdentifierBase()
{}


bool ebucoreIdentifierBase::haveidentifierValue() const
{
    return haveItem(&MXF_ITEM_K(ebucoreIdentifier, identifierValue));
}

std::string ebucoreIdentifierBase::getidentifierValue() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreIdentifier, identifierValue));
}

bool ebucoreIdentifierBase::haveidentifierNote() const
{
    return haveItem(&MXF_ITEM_K(ebucoreIdentifier, identifierNote));
}

std::string ebucoreIdentifierBase::getidentifierNote() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreIdentifier, identifierNote));
}

bool ebucoreIdentifierBase::haveidentifierTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreIdentifier, identifierTypeGroup));
}

ebucoreTypeGroup* ebucoreIdentifierBase::getidentifierTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreIdentifier, identifierTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreIdentifierBase::haveidentifierFormatGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreIdentifier, identifierFormatGroup));
}

ebucoreFormatGroup* ebucoreIdentifierBase::getidentifierFormatGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreIdentifier, identifierFormatGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreFormatGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreFormatGroup*>(obj.release());
}

bool ebucoreIdentifierBase::haveidentifierAttributorEntity() const
{
    return haveItem(&MXF_ITEM_K(ebucoreIdentifier, identifierAttributorEntity));
}

ebucoreEntity* ebucoreIdentifierBase::getidentifierAttributorEntity() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreIdentifier, identifierAttributorEntity)));
    MXFPP_CHECK(dynamic_cast<ebucoreEntity*>(obj.get()) != 0);
    return dynamic_cast<ebucoreEntity*>(obj.release());
}

void ebucoreIdentifierBase::setidentifierValue(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreIdentifier, identifierValue), value);
}

void ebucoreIdentifierBase::setidentifierNote(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreIdentifier, identifierNote), value);
}

void ebucoreIdentifierBase::setidentifierTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreIdentifier, identifierTypeGroup), value);
}

void ebucoreIdentifierBase::setidentifierFormatGroup(ebucoreFormatGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreIdentifier, identifierFormatGroup), value);
}

void ebucoreIdentifierBase::setidentifierAttributorEntity(ebucoreEntity* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreIdentifier, identifierAttributorEntity), value);
}

