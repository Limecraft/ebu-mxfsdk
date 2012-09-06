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

#ifndef __MXFPP_EBUCOREAUDIOFORMAT_BASE_H__
#define __MXFPP_EBUCOREAUDIOFORMAT_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUCore { namespace KLV
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
   std::string getaudioTrackConfiguration() const;
   bool haveaudioSamplingSize() const;
   uint16_t getaudioSamplingSize() const;
   bool haveaudioSamplingType() const;
   std::string getaudioSamplingType() const;
   bool haveaudioTotalNumberOfChannels() const;
   uint16_t getaudioTotalNumberOfChannels() const;
   bool haveaudioBitRate() const;
   uint64_t getaudioBitRate() const;
   bool haveaudioBitRateMode() const;
   std::string getaudioBitRateMode() const;
   bool haveaudioSamplingRate() const;
   mxfRational getaudioSamplingRate() const;
   bool haveaudioEncoding() const;
   ebucoreEncoding* getaudioEncoding() const;
   bool haveaudioCodec() const;
   ebucoreCodec* getaudioCodec() const;
   bool haveaudioTrack() const;
   ebucoreTrack* getaudioTrack() const;
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
   void setaudioTrackConfiguration(std::string value);
   void setaudioSamplingSize(uint16_t value);
   void setaudioSamplingType(std::string value);
   void setaudioTotalNumberOfChannels(uint16_t value);
   void setaudioBitRate(uint64_t value);
   void setaudioBitRateMode(std::string value);
   void setaudioSamplingRate(mxfRational value);
   void setaudioEncoding(ebucoreEncoding* value);
   void setaudioCodec(ebucoreCodec* value);
   void setaudioTrack(ebucoreTrack* value);
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


}};


#endif
