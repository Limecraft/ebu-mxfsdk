/*
 * Copyright (C) 2008, British Broadcasting Corporation
 * All Rights Reserved.
 *
 * Author: Philip de Nier
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the British Broadcasting Corporation nor the names
 *       of its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
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

