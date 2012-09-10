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

#ifndef __MXFPP_EBUCORECOREMETADATA_BASE_H__
#define __MXFPP_EBUCORECOREMETADATA_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace KLV
{


class ebucoreCoreMetadataBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreCoreMetadataBase>;
    static const mxfKey setKey;

public:
    ebucoreCoreMetadataBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreCoreMetadataBase();


   // getters

   bool haveidentifier() const;
   std::vector<ebucoreIdentifier*> getidentifier() const;
   bool havetitle() const;
   std::vector<ebucoreTitle*> gettitle() const;
   bool havealternativeTitle() const;
   std::vector<ebucoreAlternativeTitle*> getalternativeTitle() const;
   bool havecreator() const;
   std::vector<ebucoreEntity*> getcreator() const;
   bool havesubject() const;
   std::vector<ebucoreSubject*> getsubject() const;
   bool havedescription() const;
   std::vector<ebucoreDescription*> getdescription() const;
   bool havepublisher() const;
   std::vector<ebucoreEntity*> getpublisher() const;
   bool havecontributor() const;
   std::vector<ebucoreEntity*> getcontributor() const;
   bool havedate() const;
   std::vector<ebucoreDate*> getdate() const;
   bool havetype() const;
   std::vector<ebucoreType*> gettype() const;
   bool havelanguage() const;
   std::vector<ebucoreLanguage*> getlanguage() const;
   bool havecoverage() const;
   std::vector<ebucoreCoverage*> getcoverage() const;
   bool haverights() const;
   std::vector<ebucoreRights*> getrights() const;
   bool haverating() const;
   std::vector<ebucoreRating*> getrating() const;
   bool haveversion() const;
   ebucoreVersion* getversion() const;
   bool havepublicationHistoryEvent() const;
   std::vector<ebucorePublicationHistoryEvent*> getpublicationHistoryEvent() const;
   bool havecustomRelation() const;
   std::vector<ebucoreCustomRelation*> getcustomRelation() const;
   bool havebasicRelation() const;
   std::vector<ebucoreBasicRelation*> getbasicRelation() const;
   bool haveformat() const;
   std::vector<ebucoreFormat*> getformat() const;
   bool havepart() const;
   std::vector<ebucorePartMetadata*> getpart() const;


   // setters

   void setidentifier(const std::vector<ebucoreIdentifier*>& value);
   void appendidentifier(ebucoreIdentifier* value);
   void settitle(const std::vector<ebucoreTitle*>& value);
   void appendtitle(ebucoreTitle* value);
   void setalternativeTitle(const std::vector<ebucoreAlternativeTitle*>& value);
   void appendalternativeTitle(ebucoreAlternativeTitle* value);
   void setcreator(const std::vector<ebucoreEntity*>& value);
   void appendcreator(ebucoreEntity* value);
   void setsubject(const std::vector<ebucoreSubject*>& value);
   void appendsubject(ebucoreSubject* value);
   void setdescription(const std::vector<ebucoreDescription*>& value);
   void appenddescription(ebucoreDescription* value);
   void setpublisher(const std::vector<ebucoreEntity*>& value);
   void appendpublisher(ebucoreEntity* value);
   void setcontributor(const std::vector<ebucoreEntity*>& value);
   void appendcontributor(ebucoreEntity* value);
   void setdate(const std::vector<ebucoreDate*>& value);
   void appenddate(ebucoreDate* value);
   void settype(const std::vector<ebucoreType*>& value);
   void appendtype(ebucoreType* value);
   void setlanguage(const std::vector<ebucoreLanguage*>& value);
   void appendlanguage(ebucoreLanguage* value);
   void setcoverage(const std::vector<ebucoreCoverage*>& value);
   void appendcoverage(ebucoreCoverage* value);
   void setrights(const std::vector<ebucoreRights*>& value);
   void appendrights(ebucoreRights* value);
   void setrating(const std::vector<ebucoreRating*>& value);
   void appendrating(ebucoreRating* value);
   void setversion(ebucoreVersion* value);
   void setpublicationHistoryEvent(const std::vector<ebucorePublicationHistoryEvent*>& value);
   void appendpublicationHistoryEvent(ebucorePublicationHistoryEvent* value);
   void setcustomRelation(const std::vector<ebucoreCustomRelation*>& value);
   void appendcustomRelation(ebucoreCustomRelation* value);
   void setbasicRelation(const std::vector<ebucoreBasicRelation*>& value);
   void appendbasicRelation(ebucoreBasicRelation* value);
   void setformat(const std::vector<ebucoreFormat*>& value);
   void appendformat(ebucoreFormat* value);
   void setpart(const std::vector<ebucorePartMetadata*>& value);
   void appendpart(ebucorePartMetadata* value);


protected:
    ebucoreCoreMetadataBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}};


#endif
