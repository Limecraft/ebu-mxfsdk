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
  
#ifndef __MXFPP_EBUCOREFORMATGROUP_BASE_H__
#define __MXFPP_EBUCOREFORMATGROUP_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreFormatGroupBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreFormatGroupBase>;
    static const mxfKey setKey;

public:
    ebucoreFormatGroupBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreFormatGroupBase();


   // getters

   bool haveformatGroupThesaurus() const;
   std::string getformatGroupThesaurus() const;
   bool haveformatGroupLabel() const;
   std::string getformatGroupLabel() const;
   bool haveformatGroupLink() const;
   std::string getformatGroupLink() const;
   bool haveformatGroupUL() const;
   mxfUL getformatGroupUL() const;
   bool haveformatGroupDefinition() const;
   std::string getformatGroupDefinition() const;
   bool haveformatGroupLanguage() const;
   std::string getformatGroupLanguage() const;


   // setters

   void setformatGroupThesaurus(std::string value);
   void setformatGroupLabel(std::string value);
   void setformatGroupLink(std::string value);
   void setformatGroupUL(mxfUL value);
   void setformatGroupDefinition(std::string value);
   void setformatGroupLanguage(std::string value);


protected:
    ebucoreFormatGroupBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
