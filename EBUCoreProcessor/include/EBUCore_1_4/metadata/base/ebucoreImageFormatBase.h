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
  
#ifndef __MXFPP_EBUCOREIMAGEFORMAT_BASE_H__
#define __MXFPP_EBUCOREIMAGEFORMAT_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
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
   ebucoreTypeGroup* getimageEncoding() const;
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
   void setimageEncoding(ebucoreTypeGroup* value);
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


}}}};


#endif
