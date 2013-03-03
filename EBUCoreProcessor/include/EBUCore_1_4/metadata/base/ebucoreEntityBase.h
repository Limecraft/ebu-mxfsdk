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
  
#ifndef __MXFPP_EBUCOREENTITY_BASE_H__
#define __MXFPP_EBUCOREENTITY_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreEntityBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreEntityBase>;
    static const mxfKey setKey;

public:
    ebucoreEntityBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreEntityBase();


   // getters

   bool haveentityId() const;
   std::string getentityId() const;
   bool haveentityContact() const;
   std::vector<ebucoreContact*> getentityContact() const;
   bool haveentityOrganisation() const;
   std::vector<ebucoreOrganisation*> getentityOrganisation() const;
   bool haveentityRole() const;
   std::vector<ebucoreRole*> getentityRole() const;


   // setters

   void setentityId(std::string value);
   void setentityContact(const std::vector<ebucoreContact*>& value);
   void appendentityContact(ebucoreContact* value);
   void setentityOrganisation(const std::vector<ebucoreOrganisation*>& value);
   void appendentityOrganisation(ebucoreOrganisation* value);
   void setentityRole(const std::vector<ebucoreRole*>& value);
   void appendentityRole(ebucoreRole* value);


protected:
    ebucoreEntityBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
