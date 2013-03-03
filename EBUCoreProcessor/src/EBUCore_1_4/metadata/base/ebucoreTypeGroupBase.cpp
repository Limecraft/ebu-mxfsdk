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


const mxfKey ebucoreTypeGroupBase::setKey = MXF_SET_K(ebucoreTypeGroup);


ebucoreTypeGroupBase::ebucoreTypeGroupBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreTypeGroupBase::ebucoreTypeGroupBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreTypeGroupBase::~ebucoreTypeGroupBase()
{}


bool ebucoreTypeGroupBase::havetypeGroupThesaurus() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupThesaurus));
}

std::string ebucoreTypeGroupBase::gettypeGroupThesaurus() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupThesaurus));
}

bool ebucoreTypeGroupBase::havetypeGroupLabel() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupLabel));
}

std::string ebucoreTypeGroupBase::gettypeGroupLabel() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupLabel));
}

bool ebucoreTypeGroupBase::havetypeGroupLink() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupLink));
}

std::string ebucoreTypeGroupBase::gettypeGroupLink() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupLink));
}

bool ebucoreTypeGroupBase::havetypeGroupUL() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupUL));
}

mxfUL ebucoreTypeGroupBase::gettypeGroupUL() const
{
    return getULItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupUL));
}

bool ebucoreTypeGroupBase::havetypeGroupDefinition() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupDefinition));
}

std::string ebucoreTypeGroupBase::gettypeGroupDefinition() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupDefinition));
}

bool ebucoreTypeGroupBase::havetypeGroupLanguage() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupLanguage));
}

std::string ebucoreTypeGroupBase::gettypeGroupLanguage() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupLanguage));
}

void ebucoreTypeGroupBase::settypeGroupThesaurus(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupThesaurus), value);
}

void ebucoreTypeGroupBase::settypeGroupLabel(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupLabel), value);
}

void ebucoreTypeGroupBase::settypeGroupLink(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupLink), value);
}

void ebucoreTypeGroupBase::settypeGroupUL(mxfUL value)
{
    setULItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupUL), value);
}

void ebucoreTypeGroupBase::settypeGroupDefinition(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupDefinition), value);
}

void ebucoreTypeGroupBase::settypeGroupLanguage(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupLanguage), value);
}

