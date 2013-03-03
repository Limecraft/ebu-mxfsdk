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


const mxfKey ebucorePublicationHistoryBase::setKey = MXF_SET_K(ebucorePublicationHistory);


ebucorePublicationHistoryBase::ebucorePublicationHistoryBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucorePublicationHistoryBase::ebucorePublicationHistoryBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucorePublicationHistoryBase::~ebucorePublicationHistoryBase()
{}


bool ebucorePublicationHistoryBase::havepublicationEvent() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistory, publicationEvent));
}

std::vector<ebucorePublicationHistoryEvent*> ebucorePublicationHistoryBase::getpublicationEvent() const
{
    vector<ebucorePublicationHistoryEvent*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucorePublicationHistory, publicationEvent)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucorePublicationHistoryEvent*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucorePublicationHistoryEvent*>(iter->get()));
    }
    return result;
}

void ebucorePublicationHistoryBase::setpublicationEvent(const std::vector<ebucorePublicationHistoryEvent*>& value)
{
    WrapObjectVectorIterator<ebucorePublicationHistoryEvent> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucorePublicationHistory, publicationEvent), &iter);
}

void ebucorePublicationHistoryBase::appendpublicationEvent(ebucorePublicationHistoryEvent* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucorePublicationHistory, publicationEvent), value);
}

