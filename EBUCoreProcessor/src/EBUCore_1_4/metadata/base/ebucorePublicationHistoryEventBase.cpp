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


const mxfKey ebucorePublicationHistoryEventBase::setKey = MXF_SET_K(ebucorePublicationHistoryEvent);


ebucorePublicationHistoryEventBase::ebucorePublicationHistoryEventBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucorePublicationHistoryEventBase::ebucorePublicationHistoryEventBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucorePublicationHistoryEventBase::~ebucorePublicationHistoryEventBase()
{}


bool ebucorePublicationHistoryEventBase::havepublicationEventName() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationEventName));
}

std::string ebucorePublicationHistoryEventBase::getpublicationEventName() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationEventName));
}

bool ebucorePublicationHistoryEventBase::havepublicationEventId() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationEventId));
}

std::string ebucorePublicationHistoryEventBase::getpublicationEventId() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationEventId));
}

bool ebucorePublicationHistoryEventBase::havefirstPublicationFlag() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, firstPublicationFlag));
}

bool ebucorePublicationHistoryEventBase::getfirstPublicationFlag() const
{
    return getBooleanItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, firstPublicationFlag));
}

bool ebucorePublicationHistoryEventBase::havepublicationDate() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationDate));
}

mxfTimestamp ebucorePublicationHistoryEventBase::getpublicationDate() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationDate));
}

bool ebucorePublicationHistoryEventBase::havepublicationTime() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationTime));
}

mxfTimestamp ebucorePublicationHistoryEventBase::getpublicationTime() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationTime));
}

bool ebucorePublicationHistoryEventBase::havefreePublicationFlag() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, freePublicationFlag));
}

bool ebucorePublicationHistoryEventBase::getfreePublicationFlag() const
{
    return getBooleanItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, freePublicationFlag));
}

bool ebucorePublicationHistoryEventBase::havelivePublicationFlag() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, livePublicationFlag));
}

bool ebucorePublicationHistoryEventBase::getlivePublicationFlag() const
{
    return getBooleanItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, livePublicationFlag));
}

bool ebucorePublicationHistoryEventBase::havepublicationNote() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationNote));
}

std::string ebucorePublicationHistoryEventBase::getpublicationNote() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationNote));
}

bool ebucorePublicationHistoryEventBase::havepublicationFormatReference() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationFormatReference));
}

ebucoreFormat* ebucorePublicationHistoryEventBase::getpublicationFormatReference() const
{
    auto_ptr<MetadataSet> obj(getWeakRefItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationFormatReference)));
    MXFPP_CHECK(dynamic_cast<ebucoreFormat*>(obj.get()) != 0);
    return dynamic_cast<ebucoreFormat*>(obj.release());
}

bool ebucorePublicationHistoryEventBase::havepublicationRightsReference() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationRightsReference));
}

std::vector<ebucoreRights*> ebucorePublicationHistoryEventBase::getpublicationRightsReference() const
{
    vector<ebucoreRights*> result;
    auto_ptr<ObjectIterator> iter(getWeakRefArrayItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationRightsReference)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreRights*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreRights*>(iter->get()));
    }
    return result;
}

bool ebucorePublicationHistoryEventBase::havepublicationRegion() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationRegion));
}

std::vector<ebucoreRegion*> ebucorePublicationHistoryEventBase::getpublicationRegion() const
{
    vector<ebucoreRegion*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationRegion)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreRegion*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreRegion*>(iter->get()));
    }
    return result;
}

bool ebucorePublicationHistoryEventBase::havepublicationMedium() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationMedium));
}

ebucorePublicationMedium* ebucorePublicationHistoryEventBase::getpublicationMedium() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationMedium)));
    MXFPP_CHECK(dynamic_cast<ebucorePublicationMedium*>(obj.get()) != 0);
    return dynamic_cast<ebucorePublicationMedium*>(obj.release());
}

bool ebucorePublicationHistoryEventBase::havepublicationChannel() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationChannel));
}

ebucorePublicationChannel* ebucorePublicationHistoryEventBase::getpublicationChannel() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationChannel)));
    MXFPP_CHECK(dynamic_cast<ebucorePublicationChannel*>(obj.get()) != 0);
    return dynamic_cast<ebucorePublicationChannel*>(obj.release());
}

bool ebucorePublicationHistoryEventBase::havepublicationService() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationService));
}

ebucorePublicationService* ebucorePublicationHistoryEventBase::getpublicationService() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationService)));
    MXFPP_CHECK(dynamic_cast<ebucorePublicationService*>(obj.get()) != 0);
    return dynamic_cast<ebucorePublicationService*>(obj.release());
}

void ebucorePublicationHistoryEventBase::setpublicationEventName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationEventName), value);
}

void ebucorePublicationHistoryEventBase::setpublicationEventId(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationEventId), value);
}

void ebucorePublicationHistoryEventBase::setfirstPublicationFlag(bool value)
{
    setBooleanItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, firstPublicationFlag), value);
}

void ebucorePublicationHistoryEventBase::setpublicationDate(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationDate), value);
}

void ebucorePublicationHistoryEventBase::setpublicationTime(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationTime), value);
}

void ebucorePublicationHistoryEventBase::setfreePublicationFlag(bool value)
{
    setBooleanItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, freePublicationFlag), value);
}

void ebucorePublicationHistoryEventBase::setlivePublicationFlag(bool value)
{
    setBooleanItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, livePublicationFlag), value);
}

void ebucorePublicationHistoryEventBase::setpublicationNote(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationNote), value);
}

void ebucorePublicationHistoryEventBase::setpublicationFormatReference(ebucoreFormat* value)
{
    setWeakRefItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationFormatReference), value);
}

void ebucorePublicationHistoryEventBase::setpublicationRightsReference(const std::vector<ebucoreRights*>& value)
{
    WrapObjectVectorIterator<ebucoreRights> iter(value);
    setWeakRefArrayItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationRightsReference), &iter);
}

void ebucorePublicationHistoryEventBase::appendpublicationRightsReference(ebucoreRights* value)
{
    appendWeakRefArrayItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationRightsReference), value);
}

void ebucorePublicationHistoryEventBase::setpublicationRegion(const std::vector<ebucoreRegion*>& value)
{
    WrapObjectVectorIterator<ebucoreRegion> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationRegion), &iter);
}

void ebucorePublicationHistoryEventBase::appendpublicationRegion(ebucoreRegion* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationRegion), value);
}

void ebucorePublicationHistoryEventBase::setpublicationMedium(ebucorePublicationMedium* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationMedium), value);
}

void ebucorePublicationHistoryEventBase::setpublicationChannel(ebucorePublicationChannel* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationChannel), value);
}

void ebucorePublicationHistoryEventBase::setpublicationService(ebucorePublicationService* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationService), value);
}

