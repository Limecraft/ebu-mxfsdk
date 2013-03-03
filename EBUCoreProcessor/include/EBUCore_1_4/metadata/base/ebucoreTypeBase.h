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
  
#ifndef __MXFPP_EBUCORETYPE_BASE_H__
#define __MXFPP_EBUCORETYPE_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreTypeBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreTypeBase>;
    static const mxfKey setKey;

public:
    ebucoreTypeBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreTypeBase();


   // getters

   bool havetypeNote() const;
   std::string gettypeNote() const;
   bool havetypeValue() const;
   std::vector<ebucoreTextualAnnotation*> gettypeValue() const;
   bool haveobjectType() const;
   std::vector<ebucoreObjectType*> getobjectType() const;
   bool havegenre() const;
   std::vector<ebucoreGenre*> getgenre() const;
   bool havetargetAudience() const;
   std::vector<ebucoreTargetAudience*> gettargetAudience() const;


   // setters

   void settypeNote(std::string value);
   void settypeValue(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendtypeValue(ebucoreTextualAnnotation* value);
   void setobjectType(const std::vector<ebucoreObjectType*>& value);
   void appendobjectType(ebucoreObjectType* value);
   void setgenre(const std::vector<ebucoreGenre*>& value);
   void appendgenre(ebucoreGenre* value);
   void settargetAudience(const std::vector<ebucoreTargetAudience*>& value);
   void appendtargetAudience(ebucoreTargetAudience* value);


protected:
    ebucoreTypeBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
