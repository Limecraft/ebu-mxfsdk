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
  
#ifndef __MXFPP_EBUCORESTATUSGROUP_BASE_H__
#define __MXFPP_EBUCORESTATUSGROUP_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreStatusGroupBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreStatusGroupBase>;
    static const mxfKey setKey;

public:
    ebucoreStatusGroupBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreStatusGroupBase();


   // getters

   bool havestatusGroupThesaurus() const;
   std::string getstatusGroupThesaurus() const;
   bool havestatusGroupLabel() const;
   std::string getstatusGroupLabel() const;
   bool havestatusGroupLink() const;
   std::string getstatusGroupLink() const;
   bool havestatusGroupUL() const;
   mxfUL getstatusGroupUL() const;
   bool havestatusGroupDefinition() const;
   std::string getstatusGroupDefinition() const;
   bool havestatusGroupLanguage() const;
   std::string getstatusGroupLanguage() const;


   // setters

   void setstatusGroupThesaurus(std::string value);
   void setstatusGroupLabel(std::string value);
   void setstatusGroupLink(std::string value);
   void setstatusGroupUL(mxfUL value);
   void setstatusGroupDefinition(std::string value);
   void setstatusGroupLanguage(std::string value);


protected:
    ebucoreStatusGroupBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
