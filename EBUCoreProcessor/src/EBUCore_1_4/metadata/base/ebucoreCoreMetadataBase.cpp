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


const mxfKey ebucoreCoreMetadataBase::setKey = MXF_SET_K(ebucoreCoreMetadata);


ebucoreCoreMetadataBase::ebucoreCoreMetadataBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreCoreMetadataBase::ebucoreCoreMetadataBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreCoreMetadataBase::~ebucoreCoreMetadataBase()
{}


bool ebucoreCoreMetadataBase::haveidentifier() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, identifier));
}

std::vector<ebucoreIdentifier*> ebucoreCoreMetadataBase::getidentifier() const
{
    vector<ebucoreIdentifier*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, identifier)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreIdentifier*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreIdentifier*>(iter->get()));
    }
    return result;
}

bool ebucoreCoreMetadataBase::havetitle() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, title));
}

std::vector<ebucoreTitle*> ebucoreCoreMetadataBase::gettitle() const
{
    vector<ebucoreTitle*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, title)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTitle*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTitle*>(iter->get()));
    }
    return result;
}

bool ebucoreCoreMetadataBase::havealternativeTitle() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, alternativeTitle));
}

std::vector<ebucoreAlternativeTitle*> ebucoreCoreMetadataBase::getalternativeTitle() const
{
    vector<ebucoreAlternativeTitle*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, alternativeTitle)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreAlternativeTitle*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreAlternativeTitle*>(iter->get()));
    }
    return result;
}

bool ebucoreCoreMetadataBase::havecreator() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, creator));
}

std::vector<ebucoreEntity*> ebucoreCoreMetadataBase::getcreator() const
{
    vector<ebucoreEntity*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, creator)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreEntity*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreEntity*>(iter->get()));
    }
    return result;
}

bool ebucoreCoreMetadataBase::havesubject() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, subject));
}

std::vector<ebucoreSubject*> ebucoreCoreMetadataBase::getsubject() const
{
    vector<ebucoreSubject*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, subject)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreSubject*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreSubject*>(iter->get()));
    }
    return result;
}

bool ebucoreCoreMetadataBase::havedescription() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, description));
}

std::vector<ebucoreDescription*> ebucoreCoreMetadataBase::getdescription() const
{
    vector<ebucoreDescription*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, description)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreDescription*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreDescription*>(iter->get()));
    }
    return result;
}

bool ebucoreCoreMetadataBase::havepublisher() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, publisher));
}

std::vector<ebucoreEntity*> ebucoreCoreMetadataBase::getpublisher() const
{
    vector<ebucoreEntity*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, publisher)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreEntity*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreEntity*>(iter->get()));
    }
    return result;
}

bool ebucoreCoreMetadataBase::havecontributor() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, contributor));
}

std::vector<ebucoreEntity*> ebucoreCoreMetadataBase::getcontributor() const
{
    vector<ebucoreEntity*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, contributor)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreEntity*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreEntity*>(iter->get()));
    }
    return result;
}

bool ebucoreCoreMetadataBase::havedate() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, date));
}

std::vector<ebucoreDate*> ebucoreCoreMetadataBase::getdate() const
{
    vector<ebucoreDate*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, date)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreDate*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreDate*>(iter->get()));
    }
    return result;
}

bool ebucoreCoreMetadataBase::havetype() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, type));
}

std::vector<ebucoreType*> ebucoreCoreMetadataBase::gettype() const
{
    vector<ebucoreType*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, type)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreType*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreType*>(iter->get()));
    }
    return result;
}

bool ebucoreCoreMetadataBase::havelanguage() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, language));
}

std::vector<ebucoreLanguage*> ebucoreCoreMetadataBase::getlanguage() const
{
    vector<ebucoreLanguage*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, language)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreLanguage*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreLanguage*>(iter->get()));
    }
    return result;
}

bool ebucoreCoreMetadataBase::havecoverage() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, coverage));
}

std::vector<ebucoreCoverage*> ebucoreCoreMetadataBase::getcoverage() const
{
    vector<ebucoreCoverage*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, coverage)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreCoverage*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreCoverage*>(iter->get()));
    }
    return result;
}

bool ebucoreCoreMetadataBase::haverights() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, rights));
}

std::vector<ebucoreRights*> ebucoreCoreMetadataBase::getrights() const
{
    vector<ebucoreRights*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, rights)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreRights*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreRights*>(iter->get()));
    }
    return result;
}

bool ebucoreCoreMetadataBase::haverating() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, rating));
}

std::vector<ebucoreRating*> ebucoreCoreMetadataBase::getrating() const
{
    vector<ebucoreRating*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, rating)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreRating*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreRating*>(iter->get()));
    }
    return result;
}

bool ebucoreCoreMetadataBase::haveversion() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, version));
}

ebucoreVersion* ebucoreCoreMetadataBase::getversion() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreCoreMetadata, version)));
    MXFPP_CHECK(dynamic_cast<ebucoreVersion*>(obj.get()) != 0);
    return dynamic_cast<ebucoreVersion*>(obj.release());
}

bool ebucoreCoreMetadataBase::havepublicationHistoryEvent() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, publicationHistoryEvent));
}

std::vector<ebucorePublicationHistoryEvent*> ebucoreCoreMetadataBase::getpublicationHistoryEvent() const
{
    vector<ebucorePublicationHistoryEvent*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, publicationHistoryEvent)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucorePublicationHistoryEvent*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucorePublicationHistoryEvent*>(iter->get()));
    }
    return result;
}

bool ebucoreCoreMetadataBase::havecustomRelation() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, customRelation));
}

std::vector<ebucoreCustomRelation*> ebucoreCoreMetadataBase::getcustomRelation() const
{
    vector<ebucoreCustomRelation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, customRelation)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreCustomRelation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreCustomRelation*>(iter->get()));
    }
    return result;
}

bool ebucoreCoreMetadataBase::havebasicRelation() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, basicRelation));
}

std::vector<ebucoreBasicRelation*> ebucoreCoreMetadataBase::getbasicRelation() const
{
    vector<ebucoreBasicRelation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, basicRelation)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreBasicRelation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreBasicRelation*>(iter->get()));
    }
    return result;
}

bool ebucoreCoreMetadataBase::haveformat() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, format));
}

std::vector<ebucoreFormat*> ebucoreCoreMetadataBase::getformat() const
{
    vector<ebucoreFormat*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, format)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreFormat*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreFormat*>(iter->get()));
    }
    return result;
}

bool ebucoreCoreMetadataBase::havepart() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoreMetadata, part));
}

std::vector<ebucorePartMetadata*> ebucoreCoreMetadataBase::getpart() const
{
    vector<ebucorePartMetadata*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, part)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucorePartMetadata*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucorePartMetadata*>(iter->get()));
    }
    return result;
}

void ebucoreCoreMetadataBase::setidentifier(const std::vector<ebucoreIdentifier*>& value)
{
    WrapObjectVectorIterator<ebucoreIdentifier> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, identifier), &iter);
}

void ebucoreCoreMetadataBase::appendidentifier(ebucoreIdentifier* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, identifier), value);
}

void ebucoreCoreMetadataBase::settitle(const std::vector<ebucoreTitle*>& value)
{
    WrapObjectVectorIterator<ebucoreTitle> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, title), &iter);
}

void ebucoreCoreMetadataBase::appendtitle(ebucoreTitle* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, title), value);
}

void ebucoreCoreMetadataBase::setalternativeTitle(const std::vector<ebucoreAlternativeTitle*>& value)
{
    WrapObjectVectorIterator<ebucoreAlternativeTitle> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, alternativeTitle), &iter);
}

void ebucoreCoreMetadataBase::appendalternativeTitle(ebucoreAlternativeTitle* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, alternativeTitle), value);
}

void ebucoreCoreMetadataBase::setcreator(const std::vector<ebucoreEntity*>& value)
{
    WrapObjectVectorIterator<ebucoreEntity> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, creator), &iter);
}

void ebucoreCoreMetadataBase::appendcreator(ebucoreEntity* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, creator), value);
}

void ebucoreCoreMetadataBase::setsubject(const std::vector<ebucoreSubject*>& value)
{
    WrapObjectVectorIterator<ebucoreSubject> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, subject), &iter);
}

void ebucoreCoreMetadataBase::appendsubject(ebucoreSubject* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, subject), value);
}

void ebucoreCoreMetadataBase::setdescription(const std::vector<ebucoreDescription*>& value)
{
    WrapObjectVectorIterator<ebucoreDescription> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, description), &iter);
}

void ebucoreCoreMetadataBase::appenddescription(ebucoreDescription* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, description), value);
}

void ebucoreCoreMetadataBase::setpublisher(const std::vector<ebucoreEntity*>& value)
{
    WrapObjectVectorIterator<ebucoreEntity> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, publisher), &iter);
}

void ebucoreCoreMetadataBase::appendpublisher(ebucoreEntity* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, publisher), value);
}

void ebucoreCoreMetadataBase::setcontributor(const std::vector<ebucoreEntity*>& value)
{
    WrapObjectVectorIterator<ebucoreEntity> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, contributor), &iter);
}

void ebucoreCoreMetadataBase::appendcontributor(ebucoreEntity* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, contributor), value);
}

void ebucoreCoreMetadataBase::setdate(const std::vector<ebucoreDate*>& value)
{
    WrapObjectVectorIterator<ebucoreDate> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, date), &iter);
}

void ebucoreCoreMetadataBase::appenddate(ebucoreDate* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, date), value);
}

void ebucoreCoreMetadataBase::settype(const std::vector<ebucoreType*>& value)
{
    WrapObjectVectorIterator<ebucoreType> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, type), &iter);
}

void ebucoreCoreMetadataBase::appendtype(ebucoreType* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, type), value);
}

void ebucoreCoreMetadataBase::setlanguage(const std::vector<ebucoreLanguage*>& value)
{
    WrapObjectVectorIterator<ebucoreLanguage> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, language), &iter);
}

void ebucoreCoreMetadataBase::appendlanguage(ebucoreLanguage* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, language), value);
}

void ebucoreCoreMetadataBase::setcoverage(const std::vector<ebucoreCoverage*>& value)
{
    WrapObjectVectorIterator<ebucoreCoverage> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, coverage), &iter);
}

void ebucoreCoreMetadataBase::appendcoverage(ebucoreCoverage* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, coverage), value);
}

void ebucoreCoreMetadataBase::setrights(const std::vector<ebucoreRights*>& value)
{
    WrapObjectVectorIterator<ebucoreRights> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, rights), &iter);
}

void ebucoreCoreMetadataBase::appendrights(ebucoreRights* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, rights), value);
}

void ebucoreCoreMetadataBase::setrating(const std::vector<ebucoreRating*>& value)
{
    WrapObjectVectorIterator<ebucoreRating> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, rating), &iter);
}

void ebucoreCoreMetadataBase::appendrating(ebucoreRating* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, rating), value);
}

void ebucoreCoreMetadataBase::setversion(ebucoreVersion* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreCoreMetadata, version), value);
}

void ebucoreCoreMetadataBase::setpublicationHistoryEvent(const std::vector<ebucorePublicationHistoryEvent*>& value)
{
    WrapObjectVectorIterator<ebucorePublicationHistoryEvent> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, publicationHistoryEvent), &iter);
}

void ebucoreCoreMetadataBase::appendpublicationHistoryEvent(ebucorePublicationHistoryEvent* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, publicationHistoryEvent), value);
}

void ebucoreCoreMetadataBase::setcustomRelation(const std::vector<ebucoreCustomRelation*>& value)
{
    WrapObjectVectorIterator<ebucoreCustomRelation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, customRelation), &iter);
}

void ebucoreCoreMetadataBase::appendcustomRelation(ebucoreCustomRelation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, customRelation), value);
}

void ebucoreCoreMetadataBase::setbasicRelation(const std::vector<ebucoreBasicRelation*>& value)
{
    WrapObjectVectorIterator<ebucoreBasicRelation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, basicRelation), &iter);
}

void ebucoreCoreMetadataBase::appendbasicRelation(ebucoreBasicRelation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, basicRelation), value);
}

void ebucoreCoreMetadataBase::setformat(const std::vector<ebucoreFormat*>& value)
{
    WrapObjectVectorIterator<ebucoreFormat> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, format), &iter);
}

void ebucoreCoreMetadataBase::appendformat(ebucoreFormat* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, format), value);
}

void ebucoreCoreMetadataBase::setpart(const std::vector<ebucorePartMetadata*>& value)
{
    WrapObjectVectorIterator<ebucorePartMetadata> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, part), &iter);
}

void ebucoreCoreMetadataBase::appendpart(ebucorePartMetadata* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreCoreMetadata, part), value);
}

