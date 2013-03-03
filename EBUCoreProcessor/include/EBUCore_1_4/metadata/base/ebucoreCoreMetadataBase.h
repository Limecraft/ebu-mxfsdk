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
  
#ifndef __MXFPP_EBUCORECOREMETADATA_BASE_H__
#define __MXFPP_EBUCORECOREMETADATA_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
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
   bool havepublicationHistory() const;
   ebucorePublicationHistory* getpublicationHistory() const;
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
   void setpublicationHistory(ebucorePublicationHistory* value);
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


}}}};


#endif
