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
  
#ifndef __MXFPP_EBUCOREPARTFRAMEWORK_BASE_H__
#define __MXFPP_EBUCOREPARTFRAMEWORK_BASE_H__



#include <libMXF++/metadata/DMFramework.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucorePartFrameworkBase : public DMFramework
{
public:
    friend class MetadataSetFactory<ebucorePartFrameworkBase>;
    static const mxfKey setKey;

public:
    ebucorePartFrameworkBase(HeaderMetadata *headerMetadata);
    virtual ~ebucorePartFrameworkBase();


   // getters

   bool havepartMetadata() const;
   ebucorePartMetadata* getpartMetadata() const;


   // setters

   void setpartMetadata(ebucorePartMetadata* value);


protected:
    ebucorePartFrameworkBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
