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

#ifndef __MXFPP_EBUCOREDATAFORMAT_BASE_H__
#define __MXFPP_EBUCOREDATAFORMAT_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreDataFormatBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreDataFormatBase>;
    static const mxfKey setKey;

public:
    ebucoreDataFormatBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreDataFormatBase();


   // getters

   bool havedataFormatID() const;
   std::string getdataFormatID() const;
   bool havedataFormatVersionID() const;
   std::string getdataFormatVersionID() const;
   bool havedataFormatName() const;
   std::string getdataFormatName() const;
   bool havedataFormatDefinition() const;
   std::string getdataFormatDefinition() const;
   bool havedataTrackId() const;
   std::string getdataTrackId() const;
   bool havedataTrackName() const;
   std::string getdataTrackName() const;
   bool havedataTrackLanguageCode() const;
   std::string getdataTrackLanguageCode() const;
   bool havecaptioning() const;
   std::vector<ebucoreCaptioning*> getcaptioning() const;
   bool havesubtitling() const;
   std::vector<ebucoreSubtitling*> getsubtitling() const;
   bool haveancillaryData() const;
   std::vector<ebucoreAncillaryData*> getancillaryData() const;
   bool havedataTechnicalAttributeString() const;
   std::vector<ebucoreTechnicalAttributeString*> getdataTechnicalAttributeString() const;
   bool havedataTechnicalAttributeInt8() const;
   std::vector<ebucoreTechnicalAttributeInt8*> getdataTechnicalAttributeInt8() const;
   bool havedataTechnicalAttributeInt16() const;
   std::vector<ebucoreTechnicalAttributeInt16*> getdataTechnicalAttributeInt16() const;
   bool havedataTechnicalAttributeInt32() const;
   std::vector<ebucoreTechnicalAttributeInt32*> getdataTechnicalAttributeInt32() const;
   bool havedataTechnicalAttributeInt64() const;
   std::vector<ebucoreTechnicalAttributeInt64*> getdataTechnicalAttributeInt64() const;
   bool havedataTechnicalAttributeUInt8() const;
   std::vector<ebucoreTechnicalAttributeUInt8*> getdataTechnicalAttributeUInt8() const;
   bool havedataTechnicalAttributeUInt16() const;
   std::vector<ebucoreTechnicalAttributeUInt16*> getdataTechnicalAttributeUInt16() const;
   bool havedataTechnicalAttributeUInt32() const;
   std::vector<ebucoreTechnicalAttributeUInt32*> getdataTechnicalAttributeUInt32() const;
   bool havedataTechnicalAttributeUInt64() const;
   std::vector<ebucoreTechnicalAttributeUInt64*> getdataTechnicalAttributeUInt64() const;
   bool havedataTechnicalAttributeFloat() const;
   std::vector<ebucoreTechnicalAttributeFloat*> getdataTechnicalAttributeFloat() const;
   bool havedataTechnicalAttributeRational() const;
   std::vector<ebucoreTechnicalAttributeRational*> getdataTechnicalAttributeRational() const;
   bool havedataTechnicalAttributeAnyURI() const;
   std::vector<ebucoreTechnicalAttributeAnyURI*> getdataTechnicalAttributeAnyURI() const;
   bool havedataTechnicalAttributeBoolean() const;
   std::vector<ebucoreTechnicalAttributeBoolean*> getdataTechnicalAttributeBoolean() const;


   // setters

   void setdataFormatID(std::string value);
   void setdataFormatVersionID(std::string value);
   void setdataFormatName(std::string value);
   void setdataFormatDefinition(std::string value);
   void setdataTrackId(std::string value);
   void setdataTrackName(std::string value);
   void setdataTrackLanguageCode(std::string value);
   void setcaptioning(const std::vector<ebucoreCaptioning*>& value);
   void appendcaptioning(ebucoreCaptioning* value);
   void setsubtitling(const std::vector<ebucoreSubtitling*>& value);
   void appendsubtitling(ebucoreSubtitling* value);
   void setancillaryData(const std::vector<ebucoreAncillaryData*>& value);
   void appendancillaryData(ebucoreAncillaryData* value);
   void setdataTechnicalAttributeString(const std::vector<ebucoreTechnicalAttributeString*>& value);
   void appenddataTechnicalAttributeString(ebucoreTechnicalAttributeString* value);
   void setdataTechnicalAttributeInt8(const std::vector<ebucoreTechnicalAttributeInt8*>& value);
   void appenddataTechnicalAttributeInt8(ebucoreTechnicalAttributeInt8* value);
   void setdataTechnicalAttributeInt16(const std::vector<ebucoreTechnicalAttributeInt16*>& value);
   void appenddataTechnicalAttributeInt16(ebucoreTechnicalAttributeInt16* value);
   void setdataTechnicalAttributeInt32(const std::vector<ebucoreTechnicalAttributeInt32*>& value);
   void appenddataTechnicalAttributeInt32(ebucoreTechnicalAttributeInt32* value);
   void setdataTechnicalAttributeInt64(const std::vector<ebucoreTechnicalAttributeInt64*>& value);
   void appenddataTechnicalAttributeInt64(ebucoreTechnicalAttributeInt64* value);
   void setdataTechnicalAttributeUInt8(const std::vector<ebucoreTechnicalAttributeUInt8*>& value);
   void appenddataTechnicalAttributeUInt8(ebucoreTechnicalAttributeUInt8* value);
   void setdataTechnicalAttributeUInt16(const std::vector<ebucoreTechnicalAttributeUInt16*>& value);
   void appenddataTechnicalAttributeUInt16(ebucoreTechnicalAttributeUInt16* value);
   void setdataTechnicalAttributeUInt32(const std::vector<ebucoreTechnicalAttributeUInt32*>& value);
   void appenddataTechnicalAttributeUInt32(ebucoreTechnicalAttributeUInt32* value);
   void setdataTechnicalAttributeUInt64(const std::vector<ebucoreTechnicalAttributeUInt64*>& value);
   void appenddataTechnicalAttributeUInt64(ebucoreTechnicalAttributeUInt64* value);
   void setdataTechnicalAttributeFloat(const std::vector<ebucoreTechnicalAttributeFloat*>& value);
   void appenddataTechnicalAttributeFloat(ebucoreTechnicalAttributeFloat* value);
   void setdataTechnicalAttributeRational(const std::vector<ebucoreTechnicalAttributeRational*>& value);
   void appenddataTechnicalAttributeRational(ebucoreTechnicalAttributeRational* value);
   void setdataTechnicalAttributeAnyURI(const std::vector<ebucoreTechnicalAttributeAnyURI*>& value);
   void appenddataTechnicalAttributeAnyURI(ebucoreTechnicalAttributeAnyURI* value);
   void setdataTechnicalAttributeBoolean(const std::vector<ebucoreTechnicalAttributeBoolean*>& value);
   void appenddataTechnicalAttributeBoolean(ebucoreTechnicalAttributeBoolean* value);


protected:
    ebucoreDataFormatBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
