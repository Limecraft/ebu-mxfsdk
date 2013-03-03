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
  
#ifndef __MXFPP_EBUCORELOCATION_BASE_H__
#define __MXFPP_EBUCORELOCATION_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreLocationBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreLocationBase>;
    static const mxfKey setKey;

public:
    ebucoreLocationBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreLocationBase();


   // getters

   bool havelocationId() const;
   std::string getlocationId() const;
   bool havelocationCode() const;
   std::string getlocationCode() const;
   bool havelocationDefinitionNote() const;
   std::string getlocationDefinitionNote() const;
   bool havelocationName() const;
   std::vector<ebucoreTextualAnnotation*> getlocationName() const;
   bool havelocationRegion() const;
   ebucoreRegion* getlocationRegion() const;
   bool havelocationTypeGroup() const;
   ebucoreTypeGroup* getlocationTypeGroup() const;
   bool havelocationCoordinates() const;
   ebucoreCoordinates* getlocationCoordinates() const;


   // setters

   void setlocationId(std::string value);
   void setlocationCode(std::string value);
   void setlocationDefinitionNote(std::string value);
   void setlocationName(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendlocationName(ebucoreTextualAnnotation* value);
   void setlocationRegion(ebucoreRegion* value);
   void setlocationTypeGroup(ebucoreTypeGroup* value);
   void setlocationCoordinates(ebucoreCoordinates* value);


protected:
    ebucoreLocationBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
