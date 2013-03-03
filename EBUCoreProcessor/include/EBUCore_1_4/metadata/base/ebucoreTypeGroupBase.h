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
  
#ifndef __MXFPP_EBUCORETYPEGROUP_BASE_H__
#define __MXFPP_EBUCORETYPEGROUP_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreTypeGroupBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreTypeGroupBase>;
    static const mxfKey setKey;

public:
    ebucoreTypeGroupBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreTypeGroupBase();


   // getters

   bool havetypeGroupThesaurus() const;
   std::string gettypeGroupThesaurus() const;
   bool havetypeGroupLabel() const;
   std::string gettypeGroupLabel() const;
   bool havetypeGroupLink() const;
   std::string gettypeGroupLink() const;
   bool havetypeGroupUL() const;
   mxfUL gettypeGroupUL() const;
   bool havetypeGroupDefinition() const;
   std::string gettypeGroupDefinition() const;
   bool havetypeGroupLanguage() const;
   std::string gettypeGroupLanguage() const;


   // setters

   void settypeGroupThesaurus(std::string value);
   void settypeGroupLabel(std::string value);
   void settypeGroupLink(std::string value);
   void settypeGroupUL(mxfUL value);
   void settypeGroupDefinition(std::string value);
   void settypeGroupLanguage(std::string value);


protected:
    ebucoreTypeGroupBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
