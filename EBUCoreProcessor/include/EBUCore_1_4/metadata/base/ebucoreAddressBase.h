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
  
#ifndef __MXFPP_EBUCOREADDRESS_BASE_H__
#define __MXFPP_EBUCOREADDRESS_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreAddressBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreAddressBase>;
    static const mxfKey setKey;

public:
    ebucoreAddressBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreAddressBase();


   // getters

   bool havedeliveryCode() const;
   std::string getdeliveryCode() const;
   bool havetownCity() const;
   std::vector<ebucoreTextualAnnotation*> gettownCity() const;
   bool havecountyState() const;
   std::vector<ebucoreTextualAnnotation*> getcountyState() const;
   bool havecountry() const;
   std::vector<ebucoreCountry*> getcountry() const;
   bool haveaddressLines() const;
   std::vector<ebucoreTextualAnnotation*> getaddressLines() const;


   // setters

   void setdeliveryCode(std::string value);
   void settownCity(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendtownCity(ebucoreTextualAnnotation* value);
   void setcountyState(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendcountyState(ebucoreTextualAnnotation* value);
   void setcountry(const std::vector<ebucoreCountry*>& value);
   void appendcountry(ebucoreCountry* value);
   void setaddressLines(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendaddressLines(ebucoreTextualAnnotation* value);


protected:
    ebucoreAddressBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
