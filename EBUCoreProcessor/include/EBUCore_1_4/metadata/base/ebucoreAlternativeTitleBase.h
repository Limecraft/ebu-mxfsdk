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
  
#ifndef __MXFPP_EBUCOREALTERNATIVETITLE_BASE_H__
#define __MXFPP_EBUCOREALTERNATIVETITLE_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreAlternativeTitleBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreAlternativeTitleBase>;
    static const mxfKey setKey;

public:
    ebucoreAlternativeTitleBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreAlternativeTitleBase();


   // getters

   bool havealternativeTitleAttributionDate() const;
   mxfTimestamp getalternativeTitleAttributionDate() const;
   bool havealternativeTitleNote() const;
   std::string getalternativeTitleNote() const;
   bool havealternativeTitleValue() const;
   std::vector<ebucoreTextualAnnotation*> getalternativeTitleValue() const;
   bool havealternativeTitleTypeGroup() const;
   ebucoreTypeGroup* getalternativeTitleTypeGroup() const;
   bool havealternativeTitleStatusGroup() const;
   ebucoreStatusGroup* getalternativeTitleStatusGroup() const;


   // setters

   void setalternativeTitleAttributionDate(mxfTimestamp value);
   void setalternativeTitleNote(std::string value);
   void setalternativeTitleValue(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendalternativeTitleValue(ebucoreTextualAnnotation* value);
   void setalternativeTitleTypeGroup(ebucoreTypeGroup* value);
   void setalternativeTitleStatusGroup(ebucoreStatusGroup* value);


protected:
    ebucoreAlternativeTitleBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
