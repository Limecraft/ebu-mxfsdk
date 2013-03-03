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
  
#ifndef __MXFPP_EBUCORECONTACTDETAILS_BASE_H__
#define __MXFPP_EBUCORECONTACTDETAILS_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreContactDetailsBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreContactDetailsBase>;
    static const mxfKey setKey;

public:
    ebucoreContactDetailsBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreContactDetailsBase();


   // getters

   bool havewebAddress() const;
   std::string getwebAddress() const;
   bool havetelephoneNumber() const;
   std::string gettelephoneNumber() const;
   bool havemobileTelephoneNumber() const;
   std::string getmobileTelephoneNumber() const;
   bool haveemailAddress() const;
   std::string getemailAddress() const;
   bool havedetailsType() const;
   ebucoreTypeGroup* getdetailsType() const;
   bool haveaddress() const;
   ebucoreAddress* getaddress() const;


   // setters

   void setwebAddress(std::string value);
   void settelephoneNumber(std::string value);
   void setmobileTelephoneNumber(std::string value);
   void setemailAddress(std::string value);
   void setdetailsType(ebucoreTypeGroup* value);
   void setaddress(ebucoreAddress* value);


protected:
    ebucoreContactDetailsBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
