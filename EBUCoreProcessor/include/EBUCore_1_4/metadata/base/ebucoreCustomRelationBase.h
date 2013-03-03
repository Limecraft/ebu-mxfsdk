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
  
#ifndef __MXFPP_EBUCORECUSTOMRELATION_BASE_H__
#define __MXFPP_EBUCORECUSTOMRELATION_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreCustomRelationBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreCustomRelationBase>;
    static const mxfKey setKey;

public:
    ebucoreCustomRelationBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreCustomRelationBase();


   // getters

   bool haverelationByName() const;
   std::string getrelationByName() const;
   bool haverelationLink() const;
   std::string getrelationLink() const;
   bool haverunningOrderNumber() const;
   uint32_t getrunningOrderNumber() const;
   bool havetotalNumberOfGroupMembers() const;
   uint32_t gettotalNumberOfGroupMembers() const;
   bool haveorderedGroupFlag() const;
   bool getorderedGroupFlag() const;
   bool haverelationNote() const;
   std::string getrelationNote() const;
   bool havecustomRelationTypeGroup() const;
   ebucoreTypeGroup* getcustomRelationTypeGroup() const;
   bool haverelationIdentifier() const;
   ebucoreIdentifier* getrelationIdentifier() const;


   // setters

   void setrelationByName(std::string value);
   void setrelationLink(std::string value);
   void setrunningOrderNumber(uint32_t value);
   void settotalNumberOfGroupMembers(uint32_t value);
   void setorderedGroupFlag(bool value);
   void setrelationNote(std::string value);
   void setcustomRelationTypeGroup(ebucoreTypeGroup* value);
   void setrelationIdentifier(ebucoreIdentifier* value);


protected:
    ebucoreCustomRelationBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
