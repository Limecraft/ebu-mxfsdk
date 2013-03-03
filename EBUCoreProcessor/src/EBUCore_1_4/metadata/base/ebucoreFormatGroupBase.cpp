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


const mxfKey ebucoreFormatGroupBase::setKey = MXF_SET_K(ebucoreFormatGroup);


ebucoreFormatGroupBase::ebucoreFormatGroupBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreFormatGroupBase::ebucoreFormatGroupBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreFormatGroupBase::~ebucoreFormatGroupBase()
{}


bool ebucoreFormatGroupBase::haveformatGroupThesaurus() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormatGroup, formatGroupThesaurus));
}

std::string ebucoreFormatGroupBase::getformatGroupThesaurus() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreFormatGroup, formatGroupThesaurus));
}

bool ebucoreFormatGroupBase::haveformatGroupLabel() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormatGroup, formatGroupLabel));
}

std::string ebucoreFormatGroupBase::getformatGroupLabel() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreFormatGroup, formatGroupLabel));
}

bool ebucoreFormatGroupBase::haveformatGroupLink() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormatGroup, formatGroupLink));
}

std::string ebucoreFormatGroupBase::getformatGroupLink() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreFormatGroup, formatGroupLink));
}

bool ebucoreFormatGroupBase::haveformatGroupUL() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormatGroup, formatGroupUL));
}

mxfUL ebucoreFormatGroupBase::getformatGroupUL() const
{
    return getULItem(&MXF_ITEM_K(ebucoreFormatGroup, formatGroupUL));
}

bool ebucoreFormatGroupBase::haveformatGroupDefinition() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormatGroup, formatGroupDefinition));
}

std::string ebucoreFormatGroupBase::getformatGroupDefinition() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreFormatGroup, formatGroupDefinition));
}

bool ebucoreFormatGroupBase::haveformatGroupLanguage() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormatGroup, formatGroupLanguage));
}

std::string ebucoreFormatGroupBase::getformatGroupLanguage() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreFormatGroup, formatGroupLanguage));
}

void ebucoreFormatGroupBase::setformatGroupThesaurus(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreFormatGroup, formatGroupThesaurus), value);
}

void ebucoreFormatGroupBase::setformatGroupLabel(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreFormatGroup, formatGroupLabel), value);
}

void ebucoreFormatGroupBase::setformatGroupLink(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreFormatGroup, formatGroupLink), value);
}

void ebucoreFormatGroupBase::setformatGroupUL(mxfUL value)
{
    setULItem(&MXF_ITEM_K(ebucoreFormatGroup, formatGroupUL), value);
}

void ebucoreFormatGroupBase::setformatGroupDefinition(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreFormatGroup, formatGroupDefinition), value);
}

void ebucoreFormatGroupBase::setformatGroupLanguage(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreFormatGroup, formatGroupLanguage), value);
}

