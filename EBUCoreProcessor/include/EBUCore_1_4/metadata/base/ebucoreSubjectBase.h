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
  
#ifndef __MXFPP_EBUCORESUBJECT_BASE_H__
#define __MXFPP_EBUCORESUBJECT_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreSubjectBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreSubjectBase>;
    static const mxfKey setKey;

public:
    ebucoreSubjectBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreSubjectBase();


   // getters

   bool havesubjectCode() const;
   std::string getsubjectCode() const;
   bool havesubjectNote() const;
   std::string getsubjectNote() const;
   bool havesubjectValue() const;
   std::vector<ebucoreTextualAnnotation*> getsubjectValue() const;
   bool havesubjectDefinition() const;
   std::vector<ebucoreTextualAnnotation*> getsubjectDefinition() const;
   bool havesubjectTypeGroup() const;
   ebucoreTypeGroup* getsubjectTypeGroup() const;
   bool havesubjectAttributorEntity() const;
   ebucoreEntity* getsubjectAttributorEntity() const;


   // setters

   void setsubjectCode(std::string value);
   void setsubjectNote(std::string value);
   void setsubjectValue(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendsubjectValue(ebucoreTextualAnnotation* value);
   void setsubjectDefinition(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendsubjectDefinition(ebucoreTextualAnnotation* value);
   void setsubjectTypeGroup(ebucoreTypeGroup* value);
   void setsubjectAttributorEntity(ebucoreEntity* value);


protected:
    ebucoreSubjectBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
