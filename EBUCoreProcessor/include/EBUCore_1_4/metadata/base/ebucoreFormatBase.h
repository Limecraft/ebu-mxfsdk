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
  
#ifndef __MXFPP_EBUCOREFORMAT_BASE_H__
#define __MXFPP_EBUCOREFORMAT_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreFormatBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreFormatBase>;
    static const mxfKey setKey;

public:
    ebucoreFormatBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreFormatBase();


   // getters

   bool haveformatID() const;
   std::string getformatID() const;
   bool haveformatVersionID() const;
   std::string getformatVersionID() const;
   bool haveformatName() const;
   std::string getformatName() const;
   bool haveformatDefinition() const;
   std::string getformatDefinition() const;
   bool haveformatYearCreated() const;
   mxfTimestamp getformatYearCreated() const;
   bool haveformatDateCreated() const;
   mxfTimestamp getformatDateCreated() const;
   bool haveoverallDurationTimecode() const;
   std::string getoverallDurationTimecode() const;
   bool haveoverallDurationTimecodeDropframe() const;
   std::string getoverallDurationTimecodeDropframe() const;
   bool haveoverallDurationTime() const;
   mxfRational getoverallDurationTime() const;
   bool haveoverallDurationEditUnit() const;
   int64_t getoverallDurationEditUnit() const;
   bool haveeditRate() const;
   ebucoreRational* geteditRate() const;
   bool havecontainerFormat() const;
   ebucoreFormatGroup* getcontainerFormat() const;
   bool havemedium() const;
   ebucoreMedium* getmedium() const;
   bool havepackageInfo() const;
   ebucorePackageInfo* getpackageInfo() const;
   bool havemimeType() const;
   ebucoreTypeGroup* getmimeType() const;
   bool havematerialAudioFormat() const;
   std::vector<ebucoreAudioFormat*> getmaterialAudioFormat() const;
   bool havematerialVideoFormat() const;
   std::vector<ebucoreVideoFormat*> getmaterialVideoFormat() const;
   bool havematerialImageFormat() const;
   std::vector<ebucoreImageFormat*> getmaterialImageFormat() const;
   bool havematerialDataFormat() const;
   std::vector<ebucoreDataFormat*> getmaterialDataFormat() const;
   bool havematerialSigningFormat() const;
   std::vector<ebucoreSigningFormat*> getmaterialSigningFormat() const;
   bool havematerialTechnicalAttributeString() const;
   std::vector<ebucoreTechnicalAttributeString*> getmaterialTechnicalAttributeString() const;
   bool havematerialTechnicalAttributeInt8() const;
   std::vector<ebucoreTechnicalAttributeInt8*> getmaterialTechnicalAttributeInt8() const;
   bool havematerialTechnicalAttributeInt16() const;
   std::vector<ebucoreTechnicalAttributeInt16*> getmaterialTechnicalAttributeInt16() const;
   bool havematerialTechnicalAttributeInt32() const;
   std::vector<ebucoreTechnicalAttributeInt32*> getmaterialTechnicalAttributeInt32() const;
   bool havematerialTechnicalAttributeInt64() const;
   std::vector<ebucoreTechnicalAttributeInt64*> getmaterialTechnicalAttributeInt64() const;
   bool havematerialTechnicalAttributeUInt8() const;
   std::vector<ebucoreTechnicalAttributeUInt8*> getmaterialTechnicalAttributeUInt8() const;
   bool havematerialTechnicalAttributeUInt16() const;
   std::vector<ebucoreTechnicalAttributeUInt16*> getmaterialTechnicalAttributeUInt16() const;
   bool havematerialTechnicalAttributeUInt32() const;
   std::vector<ebucoreTechnicalAttributeUInt32*> getmaterialTechnicalAttributeUInt32() const;
   bool havematerialTechnicalAttributeUInt64() const;
   std::vector<ebucoreTechnicalAttributeUInt64*> getmaterialTechnicalAttributeUInt64() const;
   bool havematerialTechnicalAttributeFloat() const;
   std::vector<ebucoreTechnicalAttributeFloat*> getmaterialTechnicalAttributeFloat() const;
   bool havematerialTechnicalAttributeRational() const;
   std::vector<ebucoreTechnicalAttributeRational*> getmaterialTechnicalAttributeRational() const;
   bool havematerialTechnicalAttributeAnyURI() const;
   std::vector<ebucoreTechnicalAttributeAnyURI*> getmaterialTechnicalAttributeAnyURI() const;
   bool havematerialTechnicalAttributeBoolean() const;
   std::vector<ebucoreTechnicalAttributeBoolean*> getmaterialTechnicalAttributeBoolean() const;
   bool haveformatModifiedDate() const;
   ebucoreDate* getformatModifiedDate() const;


   // setters

   void setformatID(std::string value);
   void setformatVersionID(std::string value);
   void setformatName(std::string value);
   void setformatDefinition(std::string value);
   void setformatYearCreated(mxfTimestamp value);
   void setformatDateCreated(mxfTimestamp value);
   void setoverallDurationTimecode(std::string value);
   void setoverallDurationTimecodeDropframe(std::string value);
   void setoverallDurationTime(mxfRational value);
   void setoverallDurationEditUnit(int64_t value);
   void seteditRate(ebucoreRational* value);
   void setcontainerFormat(ebucoreFormatGroup* value);
   void setmedium(ebucoreMedium* value);
   void setpackageInfo(ebucorePackageInfo* value);
   void setmimeType(ebucoreTypeGroup* value);
   void setmaterialAudioFormat(const std::vector<ebucoreAudioFormat*>& value);
   void appendmaterialAudioFormat(ebucoreAudioFormat* value);
   void setmaterialVideoFormat(const std::vector<ebucoreVideoFormat*>& value);
   void appendmaterialVideoFormat(ebucoreVideoFormat* value);
   void setmaterialImageFormat(const std::vector<ebucoreImageFormat*>& value);
   void appendmaterialImageFormat(ebucoreImageFormat* value);
   void setmaterialDataFormat(const std::vector<ebucoreDataFormat*>& value);
   void appendmaterialDataFormat(ebucoreDataFormat* value);
   void setmaterialSigningFormat(const std::vector<ebucoreSigningFormat*>& value);
   void appendmaterialSigningFormat(ebucoreSigningFormat* value);
   void setmaterialTechnicalAttributeString(const std::vector<ebucoreTechnicalAttributeString*>& value);
   void appendmaterialTechnicalAttributeString(ebucoreTechnicalAttributeString* value);
   void setmaterialTechnicalAttributeInt8(const std::vector<ebucoreTechnicalAttributeInt8*>& value);
   void appendmaterialTechnicalAttributeInt8(ebucoreTechnicalAttributeInt8* value);
   void setmaterialTechnicalAttributeInt16(const std::vector<ebucoreTechnicalAttributeInt16*>& value);
   void appendmaterialTechnicalAttributeInt16(ebucoreTechnicalAttributeInt16* value);
   void setmaterialTechnicalAttributeInt32(const std::vector<ebucoreTechnicalAttributeInt32*>& value);
   void appendmaterialTechnicalAttributeInt32(ebucoreTechnicalAttributeInt32* value);
   void setmaterialTechnicalAttributeInt64(const std::vector<ebucoreTechnicalAttributeInt64*>& value);
   void appendmaterialTechnicalAttributeInt64(ebucoreTechnicalAttributeInt64* value);
   void setmaterialTechnicalAttributeUInt8(const std::vector<ebucoreTechnicalAttributeUInt8*>& value);
   void appendmaterialTechnicalAttributeUInt8(ebucoreTechnicalAttributeUInt8* value);
   void setmaterialTechnicalAttributeUInt16(const std::vector<ebucoreTechnicalAttributeUInt16*>& value);
   void appendmaterialTechnicalAttributeUInt16(ebucoreTechnicalAttributeUInt16* value);
   void setmaterialTechnicalAttributeUInt32(const std::vector<ebucoreTechnicalAttributeUInt32*>& value);
   void appendmaterialTechnicalAttributeUInt32(ebucoreTechnicalAttributeUInt32* value);
   void setmaterialTechnicalAttributeUInt64(const std::vector<ebucoreTechnicalAttributeUInt64*>& value);
   void appendmaterialTechnicalAttributeUInt64(ebucoreTechnicalAttributeUInt64* value);
   void setmaterialTechnicalAttributeFloat(const std::vector<ebucoreTechnicalAttributeFloat*>& value);
   void appendmaterialTechnicalAttributeFloat(ebucoreTechnicalAttributeFloat* value);
   void setmaterialTechnicalAttributeRational(const std::vector<ebucoreTechnicalAttributeRational*>& value);
   void appendmaterialTechnicalAttributeRational(ebucoreTechnicalAttributeRational* value);
   void setmaterialTechnicalAttributeAnyURI(const std::vector<ebucoreTechnicalAttributeAnyURI*>& value);
   void appendmaterialTechnicalAttributeAnyURI(ebucoreTechnicalAttributeAnyURI* value);
   void setmaterialTechnicalAttributeBoolean(const std::vector<ebucoreTechnicalAttributeBoolean*>& value);
   void appendmaterialTechnicalAttributeBoolean(ebucoreTechnicalAttributeBoolean* value);
   void setformatModifiedDate(ebucoreDate* value);


protected:
    ebucoreFormatBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
