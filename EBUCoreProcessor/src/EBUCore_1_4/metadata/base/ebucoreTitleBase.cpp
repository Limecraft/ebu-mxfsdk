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


const mxfKey ebucoreTitleBase::setKey = MXF_SET_K(ebucoreTitle);


ebucoreTitleBase::ebucoreTitleBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreTitleBase::ebucoreTitleBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreTitleBase::~ebucoreTitleBase()
{}


bool ebucoreTitleBase::havetitleAttributionDate() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTitle, titleAttributionDate));
}

mxfTimestamp ebucoreTitleBase::gettitleAttributionDate() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreTitle, titleAttributionDate));
}

bool ebucoreTitleBase::havetitleNote() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTitle, titleNote));
}

std::string ebucoreTitleBase::gettitleNote() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTitle, titleNote));
}

bool ebucoreTitleBase::havetitleValue() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTitle, titleValue));
}

std::vector<ebucoreTextualAnnotation*> ebucoreTitleBase::gettitleValue() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreTitle, titleValue)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

void ebucoreTitleBase::settitleAttributionDate(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreTitle, titleAttributionDate), value);
}

void ebucoreTitleBase::settitleNote(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTitle, titleNote), value);
}

void ebucoreTitleBase::settitleValue(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreTitle, titleValue), &iter);
}

void ebucoreTitleBase::appendtitleValue(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreTitle, titleValue), value);
}

