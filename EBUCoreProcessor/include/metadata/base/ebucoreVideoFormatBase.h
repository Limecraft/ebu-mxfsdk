/*
 * Copyright (C) 2008, British Broadcasting Corporation
 * All Rights Reserved.
 *
 * Author: Philip de Nier
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the British Broadcasting Corporation nor the names
 *       of its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __MXFPP_EBUCOREVIDEOFORMAT_BASE_H__
#define __MXFPP_EBUCOREVIDEOFORMAT_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace KLV
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
   bool havevideoAspectRatio() const;
   ebucoreAspectRatio* getvideoAspectRatio() const;
   bool havevideoFrameRate() const;
   mxfRational getvideoFrameRate() const;
   bool havevideoHeight() const;
   ebucoreDimension* getvideoHeight() const;
   bool havevideoWidth() const;
   ebucoreDimension* getvideoWidth() const;
   bool havevideoEncoding() const;
   std::vector<ebucoreEncoding*> getvideoEncoding() const;
   bool havevideoCodectype() const;
   ebucoreCodec* getvideoCodectype() const;
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
   void setvideoBitRateMode(std::string value);
   void setvideoSamplingFormat(std::string value);
   void setvideoScanningOrder(std::string value);
   void setvideoActiveLines(uint64_t value);
   void setvideoNoiseFilterFlag(bool value);
   void setvideoAspectRatio(ebucoreAspectRatio* value);
   void setvideoFrameRate(mxfRational value);
   void setvideoHeight(ebucoreDimension* value);
   void setvideoWidth(ebucoreDimension* value);
   void setvideoEncoding(const std::vector<ebucoreEncoding*>& value);
   void appendvideoEncoding(ebucoreEncoding* value);
   void setvideoCodectype(ebucoreCodec* value);
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


}}};


#endif
