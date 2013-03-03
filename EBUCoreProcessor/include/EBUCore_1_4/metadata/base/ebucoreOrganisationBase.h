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
  
#ifndef __MXFPP_EBUCOREORGANISATION_BASE_H__
#define __MXFPP_EBUCOREORGANISATION_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreOrganisationBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreOrganisationBase>;
    static const mxfKey setKey;

public:
    ebucoreOrganisationBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreOrganisationBase();


   // getters

   bool haveorganisationId() const;
   std::string getorganisationId() const;
   bool haveorganisationLinkToLogo() const;
   std::string getorganisationLinkToLogo() const;
   bool haveorganisationCode() const;
   std::vector<ebucoreIdentifier*> getorganisationCode() const;
   bool haveorganisationRelatedInformationLink() const;
   std::vector<ebucoreBasicLink*> getorganisationRelatedInformationLink() const;
   bool haveorganisationName() const;
   std::vector<ebucoreCompoundName*> getorganisationName() const;
   bool haveorganisationDepartment() const;
   ebucoreOrganisationDepartment* getorganisationDepartment() const;
   bool haveorganisationType() const;
   ebucoreTypeGroup* getorganisationType() const;
   bool haveorganisationDetails() const;
   std::vector<ebucoreContactDetails*> getorganisationDetails() const;
   bool haveorganisationRelatedContacts() const;
   std::vector<ebucoreEntity*> getorganisationRelatedContacts() const;


   // setters

   void setorganisationId(std::string value);
   void setorganisationLinkToLogo(std::string value);
   void setorganisationCode(const std::vector<ebucoreIdentifier*>& value);
   void appendorganisationCode(ebucoreIdentifier* value);
   void setorganisationRelatedInformationLink(const std::vector<ebucoreBasicLink*>& value);
   void appendorganisationRelatedInformationLink(ebucoreBasicLink* value);
   void setorganisationName(const std::vector<ebucoreCompoundName*>& value);
   void appendorganisationName(ebucoreCompoundName* value);
   void setorganisationDepartment(ebucoreOrganisationDepartment* value);
   void setorganisationType(ebucoreTypeGroup* value);
   void setorganisationDetails(const std::vector<ebucoreContactDetails*>& value);
   void appendorganisationDetails(ebucoreContactDetails* value);
   void setorganisationRelatedContacts(const std::vector<ebucoreEntity*>& value);
   void appendorganisationRelatedContacts(ebucoreEntity* value);


protected:
    ebucoreOrganisationBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
