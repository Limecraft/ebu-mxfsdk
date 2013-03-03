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
  
#ifndef __MXFPP_EBUCOREPARTMETADATA_BASE_H__
#define __MXFPP_EBUCOREPARTMETADATA_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucorePartMetadataBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucorePartMetadataBase>;
    static const mxfKey setKey;

public:
    ebucorePartMetadataBase(HeaderMetadata *headerMetadata);
    virtual ~ebucorePartMetadataBase();


   // getters

   bool havepartId() const;
   std::string getpartId() const;
   bool havepartName() const;
   std::string getpartName() const;
   bool havepartDefinition() const;
   std::string getpartDefinition() const;
   bool havepartStartTimecode() const;
   std::string getpartStartTimecode() const;
   bool havepartStartTimecodeDropframe() const;
   std::string getpartStartTimecodeDropframe() const;
   bool havepartStartTime() const;
   mxfRational getpartStartTime() const;
   bool havepartStartEditUnitNumber() const;
   int64_t getpartStartEditUnitNumber() const;
   bool havepartDurationTimecode() const;
   std::string getpartDurationTimecode() const;
   bool havepartDurationTimecodeDropframe() const;
   std::string getpartDurationTimecodeDropframe() const;
   bool havepartDurationTime() const;
   mxfRational getpartDurationTime() const;
   bool havepartDurationEditUnitNumber() const;
   int64_t getpartDurationEditUnitNumber() const;
   bool havepartNumber() const;
   uint8_t getpartNumber() const;
   bool havepartTotalNumber() const;
   uint8_t getpartTotalNumber() const;
   bool havepartTypeGroup() const;
   ebucoreTypeGroup* getpartTypeGroup() const;
   bool havepartMeta() const;
   ebucoreCoreMetadata* getpartMeta() const;


   // setters

   void setpartId(std::string value);
   void setpartName(std::string value);
   void setpartDefinition(std::string value);
   void setpartStartTimecode(std::string value);
   void setpartStartTimecodeDropframe(std::string value);
   void setpartStartTime(mxfRational value);
   void setpartStartEditUnitNumber(int64_t value);
   void setpartDurationTimecode(std::string value);
   void setpartDurationTimecodeDropframe(std::string value);
   void setpartDurationTime(mxfRational value);
   void setpartDurationEditUnitNumber(int64_t value);
   void setpartNumber(uint8_t value);
   void setpartTotalNumber(uint8_t value);
   void setpartTypeGroup(ebucoreTypeGroup* value);
   void setpartMeta(ebucoreCoreMetadata* value);


protected:
    ebucorePartMetadataBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
