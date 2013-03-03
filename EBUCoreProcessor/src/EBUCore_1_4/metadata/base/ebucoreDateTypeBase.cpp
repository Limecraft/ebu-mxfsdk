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


const mxfKey ebucoreDateTypeBase::setKey = MXF_SET_K(ebucoreDateType);


ebucoreDateTypeBase::ebucoreDateTypeBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreDateTypeBase::ebucoreDateTypeBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreDateTypeBase::~ebucoreDateTypeBase()
{}


bool ebucoreDateTypeBase::havedateValue() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDateType, dateValue));
}

mxfTimestamp ebucoreDateTypeBase::getdateValue() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDateType, dateValue));
}

bool ebucoreDateTypeBase::havetextualDate() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDateType, textualDate));
}

ebucoreTextualAnnotation* ebucoreDateTypeBase::gettextualDate() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreDateType, textualDate)));
    MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTextualAnnotation*>(obj.release());
}

bool ebucoreDateTypeBase::havedateTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDateType, dateTypeGroup));
}

ebucoreTypeGroup* ebucoreDateTypeBase::getdateTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreDateType, dateTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

void ebucoreDateTypeBase::setdateValue(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDateType, dateValue), value);
}

void ebucoreDateTypeBase::settextualDate(ebucoreTextualAnnotation* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreDateType, textualDate), value);
}

void ebucoreDateTypeBase::setdateTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreDateType, dateTypeGroup), value);
}

