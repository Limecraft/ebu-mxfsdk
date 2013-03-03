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
  
#ifndef __MXFPP_EBUCORESIGNINGFORMAT_BASE_H__
#define __MXFPP_EBUCORESIGNINGFORMAT_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreSigningFormatBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreSigningFormatBase>;
    static const mxfKey setKey;

public:
    ebucoreSigningFormatBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreSigningFormatBase();


   // getters

   bool havesigningFormatID() const;
   std::string getsigningFormatID() const;
   bool havesigningFormatVersionID() const;
   std::string getsigningFormatVersionID() const;
   bool havesigningFormatName() const;
   std::string getsigningFormatName() const;
   bool havesigningTrackID() const;
   std::string getsigningTrackID() const;
   bool havesigningTrackName() const;
   std::string getsigningTrackName() const;
   bool havesigningTrackLanguageCode() const;
   std::string getsigningTrackLanguageCode() const;
   bool havesigningSourceUri() const;
   std::string getsigningSourceUri() const;
   bool havesigningTypeGroup() const;
   ebucoreTypeGroup* getsigningTypeGroup() const;
   bool havesigningFormatGroup() const;
   ebucoreFormatGroup* getsigningFormatGroup() const;


   // setters

   void setsigningFormatID(std::string value);
   void setsigningFormatVersionID(std::string value);
   void setsigningFormatName(std::string value);
   void setsigningTrackID(std::string value);
   void setsigningTrackName(std::string value);
   void setsigningTrackLanguageCode(std::string value);
   void setsigningSourceUri(std::string value);
   void setsigningTypeGroup(ebucoreTypeGroup* value);
   void setsigningFormatGroup(ebucoreFormatGroup* value);


protected:
    ebucoreSigningFormatBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
