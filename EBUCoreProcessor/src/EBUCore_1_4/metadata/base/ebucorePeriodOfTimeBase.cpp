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


const mxfKey ebucorePeriodOfTimeBase::setKey = MXF_SET_K(ebucorePeriodOfTime);


ebucorePeriodOfTimeBase::ebucorePeriodOfTimeBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucorePeriodOfTimeBase::ebucorePeriodOfTimeBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucorePeriodOfTimeBase::~ebucorePeriodOfTimeBase()
{}


bool ebucorePeriodOfTimeBase::haveperiodId() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodId));
}

std::string ebucorePeriodOfTimeBase::getperiodId() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodId));
}

bool ebucorePeriodOfTimeBase::haveperiodStartYear() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartYear));
}

mxfTimestamp ebucorePeriodOfTimeBase::getperiodStartYear() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartYear));
}

bool ebucorePeriodOfTimeBase::haveperiodStartDate() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartDate));
}

mxfTimestamp ebucorePeriodOfTimeBase::getperiodStartDate() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartDate));
}

bool ebucorePeriodOfTimeBase::haveperiodStartTime() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartTime));
}

mxfTimestamp ebucorePeriodOfTimeBase::getperiodStartTime() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartTime));
}

bool ebucorePeriodOfTimeBase::haveperiodEndYear() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndYear));
}

mxfTimestamp ebucorePeriodOfTimeBase::getperiodEndYear() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndYear));
}

bool ebucorePeriodOfTimeBase::haveperiodEndDate() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndDate));
}

mxfTimestamp ebucorePeriodOfTimeBase::getperiodEndDate() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndDate));
}

bool ebucorePeriodOfTimeBase::haveperiodEndTime() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndTime));
}

mxfTimestamp ebucorePeriodOfTimeBase::getperiodEndTime() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndTime));
}

bool ebucorePeriodOfTimeBase::haveperiodName() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodName));
}

std::vector<ebucoreTextualAnnotation*> ebucorePeriodOfTimeBase::getperiodName() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodName)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

void ebucorePeriodOfTimeBase::setperiodId(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodId), value);
}

void ebucorePeriodOfTimeBase::setperiodStartYear(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartYear), value);
}

void ebucorePeriodOfTimeBase::setperiodStartDate(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartDate), value);
}

void ebucorePeriodOfTimeBase::setperiodStartTime(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartTime), value);
}

void ebucorePeriodOfTimeBase::setperiodEndYear(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndYear), value);
}

void ebucorePeriodOfTimeBase::setperiodEndDate(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndDate), value);
}

void ebucorePeriodOfTimeBase::setperiodEndTime(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndTime), value);
}

void ebucorePeriodOfTimeBase::setperiodName(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodName), &iter);
}

void ebucorePeriodOfTimeBase::appendperiodName(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodName), value);
}

