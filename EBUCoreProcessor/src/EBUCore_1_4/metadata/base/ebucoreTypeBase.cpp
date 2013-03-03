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


const mxfKey ebucoreTypeBase::setKey = MXF_SET_K(ebucoreType);


ebucoreTypeBase::ebucoreTypeBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreTypeBase::ebucoreTypeBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreTypeBase::~ebucoreTypeBase()
{}


bool ebucoreTypeBase::havetypeNote() const
{
    return haveItem(&MXF_ITEM_K(ebucoreType, typeNote));
}

std::string ebucoreTypeBase::gettypeNote() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreType, typeNote));
}

bool ebucoreTypeBase::havetypeValue() const
{
    return haveItem(&MXF_ITEM_K(ebucoreType, typeValue));
}

std::vector<ebucoreTextualAnnotation*> ebucoreTypeBase::gettypeValue() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, typeValue)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

bool ebucoreTypeBase::haveobjectType() const
{
    return haveItem(&MXF_ITEM_K(ebucoreType, objectType));
}

std::vector<ebucoreObjectType*> ebucoreTypeBase::getobjectType() const
{
    vector<ebucoreObjectType*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, objectType)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreObjectType*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreObjectType*>(iter->get()));
    }
    return result;
}

bool ebucoreTypeBase::havegenre() const
{
    return haveItem(&MXF_ITEM_K(ebucoreType, genre));
}

std::vector<ebucoreGenre*> ebucoreTypeBase::getgenre() const
{
    vector<ebucoreGenre*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, genre)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreGenre*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreGenre*>(iter->get()));
    }
    return result;
}

bool ebucoreTypeBase::havetargetAudience() const
{
    return haveItem(&MXF_ITEM_K(ebucoreType, targetAudience));
}

std::vector<ebucoreTargetAudience*> ebucoreTypeBase::gettargetAudience() const
{
    vector<ebucoreTargetAudience*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, targetAudience)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTargetAudience*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTargetAudience*>(iter->get()));
    }
    return result;
}

void ebucoreTypeBase::settypeNote(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreType, typeNote), value);
}

void ebucoreTypeBase::settypeValue(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, typeValue), &iter);
}

void ebucoreTypeBase::appendtypeValue(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, typeValue), value);
}

void ebucoreTypeBase::setobjectType(const std::vector<ebucoreObjectType*>& value)
{
    WrapObjectVectorIterator<ebucoreObjectType> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, objectType), &iter);
}

void ebucoreTypeBase::appendobjectType(ebucoreObjectType* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, objectType), value);
}

void ebucoreTypeBase::setgenre(const std::vector<ebucoreGenre*>& value)
{
    WrapObjectVectorIterator<ebucoreGenre> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, genre), &iter);
}

void ebucoreTypeBase::appendgenre(ebucoreGenre* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, genre), value);
}

void ebucoreTypeBase::settargetAudience(const std::vector<ebucoreTargetAudience*>& value)
{
    WrapObjectVectorIterator<ebucoreTargetAudience> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, targetAudience), &iter);
}

void ebucoreTypeBase::appendtargetAudience(ebucoreTargetAudience* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, targetAudience), value);
}

