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

#ifndef __MXFPP_EBUCOREIMAGEFORMAT_BASE_H__
#define __MXFPP_EBUCOREIMAGEFORMAT_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace KLV
{


class ebucoreImageFormatBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreImageFormatBase>;
    static const mxfKey setKey;

public:
    ebucoreImageFormatBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreImageFormatBase();


   // getters

   bool haveimageFormatID() const;
   std::string getimageFormatID() const;
   bool haveimageFormatName() const;
   std::string getimageFormatName() const;
   bool haveimageFormatDefinition() const;
   std::string getimageFormatDefinition() const;
   bool haveimageOrientation() const;
   std::string getimageOrientation() const;
   bool haveimageAspectRatio() const;
   ebucoreAspectRatio* getimageAspectRatio() const;
   bool haveimageEncoding() const;
   std::vector<ebucoreEncoding*> getimageEncoding() const;
   bool haveimageCodec() const;
   ebucoreCodec* getimageCodec() const;
   bool haveimageHeight() const;
   ebucoreDimension* getimageHeight() const;
   bool haveimageWidth() const;
   ebucoreDimension* getimageWidth() const;
   bool haveimageTechnicalAttributeString() const;
   std::vector<ebucoreTechnicalAttributeString*> getimageTechnicalAttributeString() const;
   bool haveimageTechnicalAttributeInt8() const;
   std::vector<ebucoreTechnicalAttributeInt8*> getimageTechnicalAttributeInt8() const;
   bool haveimageTechnicalAttributeInt16() const;
   std::vector<ebucoreTechnicalAttributeInt16*> getimageTechnicalAttributeInt16() const;
   bool haveimageTechnicalAttributeInt32() const;
   std::vector<ebucoreTechnicalAttributeInt32*> getimageTechnicalAttributeInt32() const;
   bool haveimageTechnicalAttributeInt64() const;
   std::vector<ebucoreTechnicalAttributeInt64*> getimageTechnicalAttributeInt64() const;
   bool haveimageTechnicalAttributeUInt8() const;
   std::vector<ebucoreTechnicalAttributeUInt8*> getimageTechnicalAttributeUInt8() const;
   bool haveimageTechnicalAttributeUInt16() const;
   std::vector<ebucoreTechnicalAttributeUInt16*> getimageTechnicalAttributeUInt16() const;
   bool haveimageTechnicalAttributeUInt32() const;
   std::vector<ebucoreTechnicalAttributeUInt32*> getimageTechnicalAttributeUInt32() const;
   bool haveimageTechnicalAttributeUInt64() const;
   std::vector<ebucoreTechnicalAttributeUInt64*> getimageTechnicalAttributeUInt64() const;
   bool haveimageTechnicalAttributeFloat() const;
   std::vector<ebucoreTechnicalAttributeFloat*> getimageTechnicalAttributeFloat() const;
   bool haveimageTechnicalAttributeRational() const;
   std::vector<ebucoreTechnicalAttributeRational*> getimageTechnicalAttributeRational() const;
   bool haveimageTechnicalAttributeAnyURI() const;
   std::vector<ebucoreTechnicalAttributeAnyURI*> getimageTechnicalAttributeAnyURI() const;
   bool haveimageTechnicalAttributeBoolean() const;
   std::vector<ebucoreTechnicalAttributeBoolean*> getimageTechnicalAttributeBoolean() const;


   // setters

   void setimageFormatID(std::string value);
   void setimageFormatName(std::string value);
   void setimageFormatDefinition(std::string value);
   void setimageOrientation(std::string value);
   void setimageAspectRatio(ebucoreAspectRatio* value);
   void setimageEncoding(const std::vector<ebucoreEncoding*>& value);
   void appendimageEncoding(ebucoreEncoding* value);
   void setimageCodec(ebucoreCodec* value);
   void setimageHeight(ebucoreDimension* value);
   void setimageWidth(ebucoreDimension* value);
   void setimageTechnicalAttributeString(const std::vector<ebucoreTechnicalAttributeString*>& value);
   void appendimageTechnicalAttributeString(ebucoreTechnicalAttributeString* value);
   void setimageTechnicalAttributeInt8(const std::vector<ebucoreTechnicalAttributeInt8*>& value);
   void appendimageTechnicalAttributeInt8(ebucoreTechnicalAttributeInt8* value);
   void setimageTechnicalAttributeInt16(const std::vector<ebucoreTechnicalAttributeInt16*>& value);
   void appendimageTechnicalAttributeInt16(ebucoreTechnicalAttributeInt16* value);
   void setimageTechnicalAttributeInt32(const std::vector<ebucoreTechnicalAttributeInt32*>& value);
   void appendimageTechnicalAttributeInt32(ebucoreTechnicalAttributeInt32* value);
   void setimageTechnicalAttributeInt64(const std::vector<ebucoreTechnicalAttributeInt64*>& value);
   void appendimageTechnicalAttributeInt64(ebucoreTechnicalAttributeInt64* value);
   void setimageTechnicalAttributeUInt8(const std::vector<ebucoreTechnicalAttributeUInt8*>& value);
   void appendimageTechnicalAttributeUInt8(ebucoreTechnicalAttributeUInt8* value);
   void setimageTechnicalAttributeUInt16(const std::vector<ebucoreTechnicalAttributeUInt16*>& value);
   void appendimageTechnicalAttributeUInt16(ebucoreTechnicalAttributeUInt16* value);
   void setimageTechnicalAttributeUInt32(const std::vector<ebucoreTechnicalAttributeUInt32*>& value);
   void appendimageTechnicalAttributeUInt32(ebucoreTechnicalAttributeUInt32* value);
   void setimageTechnicalAttributeUInt64(const std::vector<ebucoreTechnicalAttributeUInt64*>& value);
   void appendimageTechnicalAttributeUInt64(ebucoreTechnicalAttributeUInt64* value);
   void setimageTechnicalAttributeFloat(const std::vector<ebucoreTechnicalAttributeFloat*>& value);
   void appendimageTechnicalAttributeFloat(ebucoreTechnicalAttributeFloat* value);
   void setimageTechnicalAttributeRational(const std::vector<ebucoreTechnicalAttributeRational*>& value);
   void appendimageTechnicalAttributeRational(ebucoreTechnicalAttributeRational* value);
   void setimageTechnicalAttributeAnyURI(const std::vector<ebucoreTechnicalAttributeAnyURI*>& value);
   void appendimageTechnicalAttributeAnyURI(ebucoreTechnicalAttributeAnyURI* value);
   void setimageTechnicalAttributeBoolean(const std::vector<ebucoreTechnicalAttributeBoolean*>& value);
   void appendimageTechnicalAttributeBoolean(ebucoreTechnicalAttributeBoolean* value);


protected:
    ebucoreImageFormatBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}};


#endif
