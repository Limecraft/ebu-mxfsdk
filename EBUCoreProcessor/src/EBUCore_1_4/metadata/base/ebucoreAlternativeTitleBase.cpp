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


const mxfKey ebucoreAlternativeTitleBase::setKey = MXF_SET_K(ebucoreAlternativeTitle);


ebucoreAlternativeTitleBase::ebucoreAlternativeTitleBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreAlternativeTitleBase::ebucoreAlternativeTitleBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreAlternativeTitleBase::~ebucoreAlternativeTitleBase()
{}


bool ebucoreAlternativeTitleBase::havealternativeTitleAttributionDate() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleAttributionDate));
}

mxfTimestamp ebucoreAlternativeTitleBase::getalternativeTitleAttributionDate() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleAttributionDate));
}

bool ebucoreAlternativeTitleBase::havealternativeTitleNote() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleNote));
}

std::string ebucoreAlternativeTitleBase::getalternativeTitleNote() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleNote));
}

bool ebucoreAlternativeTitleBase::havealternativeTitleValue() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleValue));
}

std::vector<ebucoreTextualAnnotation*> ebucoreAlternativeTitleBase::getalternativeTitleValue() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleValue)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

bool ebucoreAlternativeTitleBase::havealternativeTitleTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleTypeGroup));
}

ebucoreTypeGroup* ebucoreAlternativeTitleBase::getalternativeTitleTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreAlternativeTitleBase::havealternativeTitleStatusGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleStatusGroup));
}

ebucoreStatusGroup* ebucoreAlternativeTitleBase::getalternativeTitleStatusGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleStatusGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreStatusGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreStatusGroup*>(obj.release());
}

void ebucoreAlternativeTitleBase::setalternativeTitleAttributionDate(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleAttributionDate), value);
}

void ebucoreAlternativeTitleBase::setalternativeTitleNote(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleNote), value);
}

void ebucoreAlternativeTitleBase::setalternativeTitleValue(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleValue), &iter);
}

void ebucoreAlternativeTitleBase::appendalternativeTitleValue(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleValue), value);
}

void ebucoreAlternativeTitleBase::setalternativeTitleTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleTypeGroup), value);
}

void ebucoreAlternativeTitleBase::setalternativeTitleStatusGroup(ebucoreStatusGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleStatusGroup), value);
}

