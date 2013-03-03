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
  
#ifndef __MXFPP_EBUCORESUBTITLING_BASE_H__
#define __MXFPP_EBUCORESUBTITLING_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreSubtitlingBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreSubtitlingBase>;
    static const mxfKey setKey;

public:
    ebucoreSubtitlingBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreSubtitlingBase();


   // getters

   bool havesubtitlingFormatID() const;
   std::string getsubtitlingFormatID() const;
   bool havesubtitlingFormatName() const;
   std::string getsubtitlingFormatName() const;
   bool havesubtitlingSourceUri() const;
   std::string getsubtitlingSourceUri() const;
   bool havesubtitlingTrackID() const;
   std::string getsubtitlingTrackID() const;
   bool havesubtitlingTrackName() const;
   std::string getsubtitlingTrackName() const;
   bool havesubtitlingLanguageCode() const;
   std::string getsubtitlingLanguageCode() const;
   bool havesubtitlingTypeGroup() const;
   ebucoreTypeGroup* getsubtitlingTypeGroup() const;
   bool havesubtitlingFormatGroup() const;
   ebucoreFormatGroup* getsubtitlingFormatGroup() const;


   // setters

   void setsubtitlingFormatID(std::string value);
   void setsubtitlingFormatName(std::string value);
   void setsubtitlingSourceUri(std::string value);
   void setsubtitlingTrackID(std::string value);
   void setsubtitlingTrackName(std::string value);
   void setsubtitlingLanguageCode(std::string value);
   void setsubtitlingTypeGroup(ebucoreTypeGroup* value);
   void setsubtitlingFormatGroup(ebucoreFormatGroup* value);


protected:
    ebucoreSubtitlingBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
