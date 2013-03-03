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
  
#ifndef __MXFPP_EBUCORETRACK_BASE_H__
#define __MXFPP_EBUCORETRACK_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreTrackBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreTrackBase>;
    static const mxfKey setKey;

public:
    ebucoreTrackBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreTrackBase();


   // getters

   bool havetrackID() const;
   std::string gettrackID() const;
   bool havetrackName() const;
   std::string gettrackName() const;
   bool havetrackLanguageCode() const;
   std::string gettrackLanguageCode() const;
   bool havetrackTypeGroup() const;
   ebucoreTypeGroup* gettrackTypeGroup() const;


   // setters

   void settrackID(std::string value);
   void settrackName(std::string value);
   void settrackLanguageCode(std::string value);
   void settrackTypeGroup(ebucoreTypeGroup* value);


protected:
    ebucoreTrackBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
