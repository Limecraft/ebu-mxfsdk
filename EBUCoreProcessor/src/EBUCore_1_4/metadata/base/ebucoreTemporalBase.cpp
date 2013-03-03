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


const mxfKey ebucoreTemporalBase::setKey = MXF_SET_K(ebucoreTemporal);


ebucoreTemporalBase::ebucoreTemporalBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreTemporalBase::ebucoreTemporalBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreTemporalBase::~ebucoreTemporalBase()
{}


bool ebucoreTemporalBase::havetemporalDefinitionNote() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTemporal, temporalDefinitionNote));
}

std::string ebucoreTemporalBase::gettemporalDefinitionNote() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTemporal, temporalDefinitionNote));
}

bool ebucoreTemporalBase::haveperiodOfTime() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTemporal, periodOfTime));
}

std::vector<ebucorePeriodOfTime*> ebucoreTemporalBase::getperiodOfTime() const
{
    vector<ebucorePeriodOfTime*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreTemporal, periodOfTime)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucorePeriodOfTime*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucorePeriodOfTime*>(iter->get()));
    }
    return result;
}

bool ebucoreTemporalBase::havetemporalTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTemporal, temporalTypeGroup));
}

ebucoreTypeGroup* ebucoreTemporalBase::gettemporalTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreTemporal, temporalTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

void ebucoreTemporalBase::settemporalDefinitionNote(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTemporal, temporalDefinitionNote), value);
}

void ebucoreTemporalBase::setperiodOfTime(const std::vector<ebucorePeriodOfTime*>& value)
{
    WrapObjectVectorIterator<ebucorePeriodOfTime> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreTemporal, periodOfTime), &iter);
}

void ebucoreTemporalBase::appendperiodOfTime(ebucorePeriodOfTime* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreTemporal, periodOfTime), value);
}

void ebucoreTemporalBase::settemporalTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreTemporal, temporalTypeGroup), value);
}

