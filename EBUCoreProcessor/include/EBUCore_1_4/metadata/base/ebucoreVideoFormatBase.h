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
  
#ifndef __MXFPP_EBUCOREVIDEOFORMAT_BASE_H__
#define __MXFPP_EBUCOREVIDEOFORMAT_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreVideoFormatBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreVideoFormatBase>;
    static const mxfKey setKey;

public:
    ebucoreVideoFormatBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreVideoFormatBase();


   // getters

   bool havevideoFormatID() const;
   std::string getvideoFormatID() const;
   bool havevideoFormatName() const;
   std::string getvideoFormatName() const;
   bool havevideoFormatDefinition() const;
   std::string getvideoFormatDefinition() const;
   bool havevideoBitRate() const;
   uint64_t getvideoBitRate() const;
   bool havevideoMaxBitRate() const;
   uint64_t getvideoMaxBitRate() const;
   bool havevideoBitRateMode() const;
   std::string getvideoBitRateMode() const;
   bool havevideoSamplingFormat() const;
   std::string getvideoSamplingFormat() const;
   bool havevideoScanningOrder() const;
   std::string getvideoScanningOrder() const;
   bool havevideoActiveLines() const;
   uint64_t getvideoActiveLines() const;
   bool havevideoNoiseFilterFlag() const;
   bool getvideoNoiseFilterFlag() const;
   bool havevideo3DFlag() const;
   bool getvideo3DFlag() const;
   bool havevideoAspectRatio() const;
   std::vector<ebucoreAspectRatio*> getvideoAspectRatio() const;
   bool havevideoFrameRate() const;
   mxfRational getvideoFrameRate() const;
   bool havevideoHeight() const;
   ebucoreHeight* getvideoHeight() const;
   bool havevideoWidth() const;
   ebucoreWidth* getvideoWidth() const;
   bool havevideoEncoding() const;
   ebucoreTypeGroup* getvideoEncoding() const;
   bool havevideoCodec() const;
   ebucoreCodec* getvideoCodec() const;
   bool havevideoTrack() const;
   std::vector<ebucoreTrack*> getvideoTrack() const;
   bool havevideoTechnicalAttributeString() const;
   std::vector<ebucoreTechnicalAttributeString*> getvideoTechnicalAttributeString() const;
   bool havevideoTechnicalAttributeInt8() const;
   std::vector<ebucoreTechnicalAttributeInt8*> getvideoTechnicalAttributeInt8() const;
   bool havevideoTechnicalAttributeInt16() const;
   std::vector<ebucoreTechnicalAttributeInt16*> getvideoTechnicalAttributeInt16() const;
   bool havevideoTechnicalAttributeInt32() const;
   std::vector<ebucoreTechnicalAttributeInt32*> getvideoTechnicalAttributeInt32() const;
   bool havevideoTechnicalAttributeInt64() const;
   std::vector<ebucoreTechnicalAttributeInt64*> getvideoTechnicalAttributeInt64() const;
   bool havevideoTechnicalAttributeUInt8() const;
   std::vector<ebucoreTechnicalAttributeUInt8*> getvideoTechnicalAttributeUInt8() const;
   bool havevideoTechnicalAttributeUInt16() const;
   std::vector<ebucoreTechnicalAttributeUInt16*> getvideoTechnicalAttributeUInt16() const;
   bool havevideoTechnicalAttributeUInt32() const;
   std::vector<ebucoreTechnicalAttributeUInt32*> getvideoTechnicalAttributeUInt32() const;
   bool havevideoTechnicalAttributeUInt64() const;
   std::vector<ebucoreTechnicalAttributeUInt64*> getvideoTechnicalAttributeUInt64() const;
   bool havevideoTechnicalAttributeFloat() const;
   std::vector<ebucoreTechnicalAttributeFloat*> getvideoTechnicalAttributeFloat() const;
   bool havevideoTechnicalAttributeRational() const;
   std::vector<ebucoreTechnicalAttributeRational*> getvideoTechnicalAttributeRational() const;
   bool havevideoTechnicalAttributeAnyURI() const;
   std::vector<ebucoreTechnicalAttributeAnyURI*> getvideoTechnicalAttributeAnyURI() const;
   bool havevideoTechnicalAttributeBoolean() const;
   std::vector<ebucoreTechnicalAttributeBoolean*> getvideoTechnicalAttributeBoolean() const;


   // setters

   void setvideoFormatID(std::string value);
   void setvideoFormatName(std::string value);
   void setvideoFormatDefinition(std::string value);
   void setvideoBitRate(uint64_t value);
   void setvideoMaxBitRate(uint64_t value);
   void setvideoBitRateMode(std::string value);
   void setvideoSamplingFormat(std::string value);
   void setvideoScanningOrder(std::string value);
   void setvideoActiveLines(uint64_t value);
   void setvideoNoiseFilterFlag(bool value);
   void setvideo3DFlag(bool value);
   void setvideoAspectRatio(const std::vector<ebucoreAspectRatio*>& value);
   void appendvideoAspectRatio(ebucoreAspectRatio* value);
   void setvideoFrameRate(mxfRational value);
   void setvideoHeight(ebucoreHeight* value);
   void setvideoWidth(ebucoreWidth* value);
   void setvideoEncoding(ebucoreTypeGroup* value);
   void setvideoCodec(ebucoreCodec* value);
   void setvideoTrack(const std::vector<ebucoreTrack*>& value);
   void appendvideoTrack(ebucoreTrack* value);
   void setvideoTechnicalAttributeString(const std::vector<ebucoreTechnicalAttributeString*>& value);
   void appendvideoTechnicalAttributeString(ebucoreTechnicalAttributeString* value);
   void setvideoTechnicalAttributeInt8(const std::vector<ebucoreTechnicalAttributeInt8*>& value);
   void appendvideoTechnicalAttributeInt8(ebucoreTechnicalAttributeInt8* value);
   void setvideoTechnicalAttributeInt16(const std::vector<ebucoreTechnicalAttributeInt16*>& value);
   void appendvideoTechnicalAttributeInt16(ebucoreTechnicalAttributeInt16* value);
   void setvideoTechnicalAttributeInt32(const std::vector<ebucoreTechnicalAttributeInt32*>& value);
   void appendvideoTechnicalAttributeInt32(ebucoreTechnicalAttributeInt32* value);
   void setvideoTechnicalAttributeInt64(const std::vector<ebucoreTechnicalAttributeInt64*>& value);
   void appendvideoTechnicalAttributeInt64(ebucoreTechnicalAttributeInt64* value);
   void setvideoTechnicalAttributeUInt8(const std::vector<ebucoreTechnicalAttributeUInt8*>& value);
   void appendvideoTechnicalAttributeUInt8(ebucoreTechnicalAttributeUInt8* value);
   void setvideoTechnicalAttributeUInt16(const std::vector<ebucoreTechnicalAttributeUInt16*>& value);
   void appendvideoTechnicalAttributeUInt16(ebucoreTechnicalAttributeUInt16* value);
   void setvideoTechnicalAttributeUInt32(const std::vector<ebucoreTechnicalAttributeUInt32*>& value);
   void appendvideoTechnicalAttributeUInt32(ebucoreTechnicalAttributeUInt32* value);
   void setvideoTechnicalAttributeUInt64(const std::vector<ebucoreTechnicalAttributeUInt64*>& value);
   void appendvideoTechnicalAttributeUInt64(ebucoreTechnicalAttributeUInt64* value);
   void setvideoTechnicalAttributeFloat(const std::vector<ebucoreTechnicalAttributeFloat*>& value);
   void appendvideoTechnicalAttributeFloat(ebucoreTechnicalAttributeFloat* value);
   void setvideoTechnicalAttributeRational(const std::vector<ebucoreTechnicalAttributeRational*>& value);
   void appendvideoTechnicalAttributeRational(ebucoreTechnicalAttributeRational* value);
   void setvideoTechnicalAttributeAnyURI(const std::vector<ebucoreTechnicalAttributeAnyURI*>& value);
   void appendvideoTechnicalAttributeAnyURI(ebucoreTechnicalAttributeAnyURI* value);
   void setvideoTechnicalAttributeBoolean(const std::vector<ebucoreTechnicalAttributeBoolean*>& value);
   void appendvideoTechnicalAttributeBoolean(ebucoreTechnicalAttributeBoolean* value);


protected:
    ebucoreVideoFormatBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
