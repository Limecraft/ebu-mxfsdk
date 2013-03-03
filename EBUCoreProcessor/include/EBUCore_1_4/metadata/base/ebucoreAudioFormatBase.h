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
  
#ifndef __MXFPP_EBUCOREAUDIOFORMAT_BASE_H__
#define __MXFPP_EBUCOREAUDIOFORMAT_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreAudioFormatBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreAudioFormatBase>;
    static const mxfKey setKey;

public:
    ebucoreAudioFormatBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreAudioFormatBase();


   // getters

   bool haveaudioFormatID() const;
   std::string getaudioFormatID() const;
   bool haveaudioFormatName() const;
   std::string getaudioFormatName() const;
   bool haveaudioFormatDefinition() const;
   std::string getaudioFormatDefinition() const;
   bool haveaudioTrackConfiguration() const;
   ebucoreTypeGroup* getaudioTrackConfiguration() const;
   bool haveaudioSamplingSize() const;
   uint16_t getaudioSamplingSize() const;
   bool haveaudioSamplingType() const;
   std::string getaudioSamplingType() const;
   bool haveaudioTotalNumberOfChannels() const;
   uint16_t getaudioTotalNumberOfChannels() const;
   bool haveaudioBitRate() const;
   uint64_t getaudioBitRate() const;
   bool haveaudioMaxBitRate() const;
   uint64_t getaudioMaxBitRate() const;
   bool haveaudioBitRateMode() const;
   std::string getaudioBitRateMode() const;
   bool haveaudioSamplingRate() const;
   mxfRational getaudioSamplingRate() const;
   bool haveaudioEncoding() const;
   ebucoreTypeGroup* getaudioEncoding() const;
   bool haveaudioCodec() const;
   ebucoreCodec* getaudioCodec() const;
   bool haveaudioTrack() const;
   std::vector<ebucoreTrack*> getaudioTrack() const;
   bool haveaudioTechnicalAttributeString() const;
   std::vector<ebucoreTechnicalAttributeString*> getaudioTechnicalAttributeString() const;
   bool haveaudioTechnicalAttributeInt8() const;
   std::vector<ebucoreTechnicalAttributeInt8*> getaudioTechnicalAttributeInt8() const;
   bool haveaudioTechnicalAttributeInt16() const;
   std::vector<ebucoreTechnicalAttributeInt16*> getaudioTechnicalAttributeInt16() const;
   bool haveaudioTechnicalAttributeInt32() const;
   std::vector<ebucoreTechnicalAttributeInt32*> getaudioTechnicalAttributeInt32() const;
   bool haveaudioTechnicalAttributeInt64() const;
   std::vector<ebucoreTechnicalAttributeInt64*> getaudioTechnicalAttributeInt64() const;
   bool haveaudioTechnicalAttributeUInt8() const;
   std::vector<ebucoreTechnicalAttributeUInt8*> getaudioTechnicalAttributeUInt8() const;
   bool haveaudioTechnicalAttributeUInt16() const;
   std::vector<ebucoreTechnicalAttributeUInt16*> getaudioTechnicalAttributeUInt16() const;
   bool haveaudioTechnicalAttributeUInt32() const;
   std::vector<ebucoreTechnicalAttributeUInt32*> getaudioTechnicalAttributeUInt32() const;
   bool haveaudioTechnicalAttributeUInt64() const;
   std::vector<ebucoreTechnicalAttributeUInt64*> getaudioTechnicalAttributeUInt64() const;
   bool haveaudioTechnicalAttributeFloat() const;
   std::vector<ebucoreTechnicalAttributeFloat*> getaudioTechnicalAttributeFloat() const;
   bool haveaudioTechnicalAttributeRational() const;
   std::vector<ebucoreTechnicalAttributeRational*> getaudioTechnicalAttributeRational() const;
   bool haveaudioTechnicalAttributeAnyURI() const;
   std::vector<ebucoreTechnicalAttributeAnyURI*> getaudioTechnicalAttributeAnyURI() const;
   bool haveaudioTechnicalAttributeBoolean() const;
   std::vector<ebucoreTechnicalAttributeBoolean*> getaudioTechnicalAttributeBoolean() const;


   // setters

   void setaudioFormatID(std::string value);
   void setaudioFormatName(std::string value);
   void setaudioFormatDefinition(std::string value);
   void setaudioTrackConfiguration(ebucoreTypeGroup* value);
   void setaudioSamplingSize(uint16_t value);
   void setaudioSamplingType(std::string value);
   void setaudioTotalNumberOfChannels(uint16_t value);
   void setaudioBitRate(uint64_t value);
   void setaudioMaxBitRate(uint64_t value);
   void setaudioBitRateMode(std::string value);
   void setaudioSamplingRate(mxfRational value);
   void setaudioEncoding(ebucoreTypeGroup* value);
   void setaudioCodec(ebucoreCodec* value);
   void setaudioTrack(const std::vector<ebucoreTrack*>& value);
   void appendaudioTrack(ebucoreTrack* value);
   void setaudioTechnicalAttributeString(const std::vector<ebucoreTechnicalAttributeString*>& value);
   void appendaudioTechnicalAttributeString(ebucoreTechnicalAttributeString* value);
   void setaudioTechnicalAttributeInt8(const std::vector<ebucoreTechnicalAttributeInt8*>& value);
   void appendaudioTechnicalAttributeInt8(ebucoreTechnicalAttributeInt8* value);
   void setaudioTechnicalAttributeInt16(const std::vector<ebucoreTechnicalAttributeInt16*>& value);
   void appendaudioTechnicalAttributeInt16(ebucoreTechnicalAttributeInt16* value);
   void setaudioTechnicalAttributeInt32(const std::vector<ebucoreTechnicalAttributeInt32*>& value);
   void appendaudioTechnicalAttributeInt32(ebucoreTechnicalAttributeInt32* value);
   void setaudioTechnicalAttributeInt64(const std::vector<ebucoreTechnicalAttributeInt64*>& value);
   void appendaudioTechnicalAttributeInt64(ebucoreTechnicalAttributeInt64* value);
   void setaudioTechnicalAttributeUInt8(const std::vector<ebucoreTechnicalAttributeUInt8*>& value);
   void appendaudioTechnicalAttributeUInt8(ebucoreTechnicalAttributeUInt8* value);
   void setaudioTechnicalAttributeUInt16(const std::vector<ebucoreTechnicalAttributeUInt16*>& value);
   void appendaudioTechnicalAttributeUInt16(ebucoreTechnicalAttributeUInt16* value);
   void setaudioTechnicalAttributeUInt32(const std::vector<ebucoreTechnicalAttributeUInt32*>& value);
   void appendaudioTechnicalAttributeUInt32(ebucoreTechnicalAttributeUInt32* value);
   void setaudioTechnicalAttributeUInt64(const std::vector<ebucoreTechnicalAttributeUInt64*>& value);
   void appendaudioTechnicalAttributeUInt64(ebucoreTechnicalAttributeUInt64* value);
   void setaudioTechnicalAttributeFloat(const std::vector<ebucoreTechnicalAttributeFloat*>& value);
   void appendaudioTechnicalAttributeFloat(ebucoreTechnicalAttributeFloat* value);
   void setaudioTechnicalAttributeRational(const std::vector<ebucoreTechnicalAttributeRational*>& value);
   void appendaudioTechnicalAttributeRational(ebucoreTechnicalAttributeRational* value);
   void setaudioTechnicalAttributeAnyURI(const std::vector<ebucoreTechnicalAttributeAnyURI*>& value);
   void appendaudioTechnicalAttributeAnyURI(ebucoreTechnicalAttributeAnyURI* value);
   void setaudioTechnicalAttributeBoolean(const std::vector<ebucoreTechnicalAttributeBoolean*>& value);
   void appendaudioTechnicalAttributeBoolean(ebucoreTechnicalAttributeBoolean* value);


protected:
    ebucoreAudioFormatBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
