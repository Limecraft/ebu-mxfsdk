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
  
#ifndef __MXFPP_EBUCORECONTACT_BASE_H__
#define __MXFPP_EBUCORECONTACT_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreContactBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreContactBase>;
    static const mxfKey setKey;

public:
    ebucoreContactBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreContactBase();


   // getters

   bool havecontactId() const;
   std::string getcontactId() const;
   bool havefamilyName() const;
   std::string getfamilyName() const;
   bool havegivenName() const;
   std::string getgivenName() const;
   bool havesalutation() const;
   std::string getsalutation() const;
   bool havesuffix() const;
   std::string getsuffix() const;
   bool haveoccupation() const;
   std::string getoccupation() const;
   bool haveusername() const;
   std::string getusername() const;
   bool haveguestFlag() const;
   bool getguestFlag() const;
   bool havecontactName() const;
   std::vector<ebucoreCompoundName*> getcontactName() const;
   bool havecontactType() const;
   ebucoreTypeGroup* getcontactType() const;
   bool havecontactDetails() const;
   std::vector<ebucoreContactDetails*> getcontactDetails() const;
   bool havecontactRelatedContacts() const;
   std::vector<ebucoreEntity*> getcontactRelatedContacts() const;
   bool havestageName() const;
   std::vector<ebucoreTextualAnnotation*> getstageName() const;
   bool havegender() const;
   ebucoreTextualAnnotation* getgender() const;
   bool havecontactRelatedInformationLink() const;
   std::vector<ebucoreBasicLink*> getcontactRelatedInformationLink() const;
   bool haveotherGivenName() const;
   std::vector<ebucoreTextualAnnotation*> getotherGivenName() const;


   // setters

   void setcontactId(std::string value);
   void setfamilyName(std::string value);
   void setgivenName(std::string value);
   void setsalutation(std::string value);
   void setsuffix(std::string value);
   void setoccupation(std::string value);
   void setusername(std::string value);
   void setguestFlag(bool value);
   void setcontactName(const std::vector<ebucoreCompoundName*>& value);
   void appendcontactName(ebucoreCompoundName* value);
   void setcontactType(ebucoreTypeGroup* value);
   void setcontactDetails(const std::vector<ebucoreContactDetails*>& value);
   void appendcontactDetails(ebucoreContactDetails* value);
   void setcontactRelatedContacts(const std::vector<ebucoreEntity*>& value);
   void appendcontactRelatedContacts(ebucoreEntity* value);
   void setstageName(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendstageName(ebucoreTextualAnnotation* value);
   void setgender(ebucoreTextualAnnotation* value);
   void setcontactRelatedInformationLink(const std::vector<ebucoreBasicLink*>& value);
   void appendcontactRelatedInformationLink(ebucoreBasicLink* value);
   void setotherGivenName(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendotherGivenName(ebucoreTextualAnnotation* value);


protected:
    ebucoreContactBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
