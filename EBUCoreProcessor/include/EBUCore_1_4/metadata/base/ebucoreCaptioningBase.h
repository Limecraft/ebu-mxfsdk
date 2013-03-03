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
  
#ifndef __MXFPP_EBUCORECAPTIONING_BASE_H__
#define __MXFPP_EBUCORECAPTIONING_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreCaptioningBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreCaptioningBase>;
    static const mxfKey setKey;

public:
    ebucoreCaptioningBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreCaptioningBase();


   // getters

   bool havecaptioningFormatID() const;
   std::string getcaptioningFormatID() const;
   bool havecaptioningFormatName() const;
   std::string getcaptioningFormatName() const;
   bool havecaptioningSourceUri() const;
   std::string getcaptioningSourceUri() const;
   bool havecaptioningTrackID() const;
   std::string getcaptioningTrackID() const;
   bool havecaptioningTrackName() const;
   std::string getcaptioningTrackName() const;
   bool havecaptioningLanguageCode() const;
   std::string getcaptioningLanguageCode() const;
   bool havecaptioningTypeGroup() const;
   ebucoreTypeGroup* getcaptioningTypeGroup() const;
   bool havecaptioningFormatGroup() const;
   ebucoreFormatGroup* getcaptioningFormatGroup() const;


   // setters

   void setcaptioningFormatID(std::string value);
   void setcaptioningFormatName(std::string value);
   void setcaptioningSourceUri(std::string value);
   void setcaptioningTrackID(std::string value);
   void setcaptioningTrackName(std::string value);
   void setcaptioningLanguageCode(std::string value);
   void setcaptioningTypeGroup(ebucoreTypeGroup* value);
   void setcaptioningFormatGroup(ebucoreFormatGroup* value);


protected:
    ebucoreCaptioningBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
