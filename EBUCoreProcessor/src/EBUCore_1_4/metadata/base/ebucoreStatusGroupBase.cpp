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


const mxfKey ebucoreStatusGroupBase::setKey = MXF_SET_K(ebucoreStatusGroup);


ebucoreStatusGroupBase::ebucoreStatusGroupBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreStatusGroupBase::ebucoreStatusGroupBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreStatusGroupBase::~ebucoreStatusGroupBase()
{}


bool ebucoreStatusGroupBase::havestatusGroupThesaurus() const
{
    return haveItem(&MXF_ITEM_K(ebucoreStatusGroup, statusGroupThesaurus));
}

std::string ebucoreStatusGroupBase::getstatusGroupThesaurus() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreStatusGroup, statusGroupThesaurus));
}

bool ebucoreStatusGroupBase::havestatusGroupLabel() const
{
    return haveItem(&MXF_ITEM_K(ebucoreStatusGroup, statusGroupLabel));
}

std::string ebucoreStatusGroupBase::getstatusGroupLabel() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreStatusGroup, statusGroupLabel));
}

bool ebucoreStatusGroupBase::havestatusGroupLink() const
{
    return haveItem(&MXF_ITEM_K(ebucoreStatusGroup, statusGroupLink));
}

std::string ebucoreStatusGroupBase::getstatusGroupLink() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreStatusGroup, statusGroupLink));
}

bool ebucoreStatusGroupBase::havestatusGroupUL() const
{
    return haveItem(&MXF_ITEM_K(ebucoreStatusGroup, statusGroupUL));
}

mxfUL ebucoreStatusGroupBase::getstatusGroupUL() const
{
    return getULItem(&MXF_ITEM_K(ebucoreStatusGroup, statusGroupUL));
}

bool ebucoreStatusGroupBase::havestatusGroupDefinition() const
{
    return haveItem(&MXF_ITEM_K(ebucoreStatusGroup, statusGroupDefinition));
}

std::string ebucoreStatusGroupBase::getstatusGroupDefinition() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreStatusGroup, statusGroupDefinition));
}

bool ebucoreStatusGroupBase::havestatusGroupLanguage() const
{
    return haveItem(&MXF_ITEM_K(ebucoreStatusGroup, statusGroupLanguage));
}

std::string ebucoreStatusGroupBase::getstatusGroupLanguage() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreStatusGroup, statusGroupLanguage));
}

void ebucoreStatusGroupBase::setstatusGroupThesaurus(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreStatusGroup, statusGroupThesaurus), value);
}

void ebucoreStatusGroupBase::setstatusGroupLabel(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreStatusGroup, statusGroupLabel), value);
}

void ebucoreStatusGroupBase::setstatusGroupLink(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreStatusGroup, statusGroupLink), value);
}

void ebucoreStatusGroupBase::setstatusGroupUL(mxfUL value)
{
    setULItem(&MXF_ITEM_K(ebucoreStatusGroup, statusGroupUL), value);
}

void ebucoreStatusGroupBase::setstatusGroupDefinition(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreStatusGroup, statusGroupDefinition), value);
}

void ebucoreStatusGroupBase::setstatusGroupLanguage(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreStatusGroup, statusGroupLanguage), value);
}

