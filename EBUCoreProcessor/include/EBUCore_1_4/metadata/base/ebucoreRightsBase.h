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
  
#ifndef __MXFPP_EBUCORERIGHTS_BASE_H__
#define __MXFPP_EBUCORERIGHTS_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreRightsBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreRightsBase>;
    static const mxfKey setKey;

public:
    ebucoreRightsBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreRightsBase();


   // getters

   bool haverightsId() const;
   std::string getrightsId() const;
   bool haverightsLink() const;
   std::string getrightsLink() const;
   bool haverightsClearanceFlag() const;
   bool getrightsClearanceFlag() const;
   bool haverightsNote() const;
   std::string getrightsNote() const;
   bool haverightsValue() const;
   std::vector<ebucoreTextualAnnotation*> getrightsValue() const;
   bool haveexploitationIssues() const;
   std::vector<ebucoreTextualAnnotation*> getexploitationIssues() const;
   bool havecopyrightStatement() const;
   std::vector<ebucoreTextualAnnotation*> getcopyrightStatement() const;
   bool haverightsCoverage() const;
   ebucoreCoverage* getrightsCoverage() const;
   bool haverightsHolderEntity() const;
   std::vector<ebucoreEntity*> getrightsHolderEntity() const;
   bool haverightsContacts() const;
   std::vector<ebucoreContact*> getrightsContacts() const;
   bool haverightsTypeGroup() const;
   ebucoreTypeGroup* getrightsTypeGroup() const;
   bool haverightsAttributeID() const;
   std::vector<ebucoreIdentifier*> getrightsAttributeID() const;
   bool haverightsFormatReferences() const;
   std::vector<ebucoreFormat*> getrightsFormatReferences() const;


   // setters

   void setrightsId(std::string value);
   void setrightsLink(std::string value);
   void setrightsClearanceFlag(bool value);
   void setrightsNote(std::string value);
   void setrightsValue(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendrightsValue(ebucoreTextualAnnotation* value);
   void setexploitationIssues(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendexploitationIssues(ebucoreTextualAnnotation* value);
   void setcopyrightStatement(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendcopyrightStatement(ebucoreTextualAnnotation* value);
   void setrightsCoverage(ebucoreCoverage* value);
   void setrightsHolderEntity(const std::vector<ebucoreEntity*>& value);
   void appendrightsHolderEntity(ebucoreEntity* value);
   void setrightsContacts(const std::vector<ebucoreContact*>& value);
   void appendrightsContacts(ebucoreContact* value);
   void setrightsTypeGroup(ebucoreTypeGroup* value);
   void setrightsAttributeID(const std::vector<ebucoreIdentifier*>& value);
   void appendrightsAttributeID(ebucoreIdentifier* value);
   void setrightsFormatReferences(const std::vector<ebucoreFormat*>& value);
   void appendrightsFormatReferences(ebucoreFormat* value);


protected:
    ebucoreRightsBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
