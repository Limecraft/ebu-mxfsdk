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
  
#ifndef __MXFPP_EBUCORECODEC_BASE_H__
#define __MXFPP_EBUCORECODEC_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreCodecBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreCodecBase>;
    static const mxfKey setKey;

public:
    ebucoreCodecBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreCodecBase();


   // getters

   bool havename() const;
   std::string getname() const;
   bool havevendor() const;
   std::string getvendor() const;
   bool haveversion() const;
   std::string getversion() const;
   bool havefamily() const;
   std::string getfamily() const;
   bool havecodecIdentifier() const;
   std::string getcodecIdentifier() const;


   // setters

   void setname(std::string value);
   void setvendor(std::string value);
   void setversion(std::string value);
   void setfamily(std::string value);
   void setcodecIdentifier(std::string value);


protected:
    ebucoreCodecBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
