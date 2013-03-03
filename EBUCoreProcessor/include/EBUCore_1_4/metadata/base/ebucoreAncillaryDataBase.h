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
  
#ifndef __MXFPP_EBUCOREANCILLARYDATA_BASE_H__
#define __MXFPP_EBUCOREANCILLARYDATA_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreAncillaryDataBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreAncillaryDataBase>;
    static const mxfKey setKey;

public:
    ebucoreAncillaryDataBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreAncillaryDataBase();


   // getters

   bool haveDID() const;
   uint32_t getDID() const;
   bool haveSDID() const;
   uint32_t getSDID() const;
   bool havelineNumber() const;
   std::vector<uint32_t> getlineNumber() const;
   bool haveANCWrappingType() const;
   ebucoreTypeGroup* getANCWrappingType() const;


   // setters

   void setDID(uint32_t value);
   void setSDID(uint32_t value);
   void setlineNumber(const std::vector<uint32_t>& value);
   void appendlineNumber(uint32_t value);
   void setANCWrappingType(ebucoreTypeGroup* value);


protected:
    ebucoreAncillaryDataBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
