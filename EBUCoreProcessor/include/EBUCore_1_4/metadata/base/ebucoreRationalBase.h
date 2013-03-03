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
  
#ifndef __MXFPP_EBUCORERATIONAL_BASE_H__
#define __MXFPP_EBUCORERATIONAL_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreRationalBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreRationalBase>;
    static const mxfKey setKey;

public:
    ebucoreRationalBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreRationalBase();


   // getters

   bool havenominalValue() const;
   uint64_t getnominalValue() const;
   bool havefactorNumerator() const;
   uint64_t getfactorNumerator() const;
   bool havefactorDenominator() const;
   uint64_t getfactorDenominator() const;


   // setters

   void setnominalValue(uint64_t value);
   void setfactorNumerator(uint64_t value);
   void setfactorDenominator(uint64_t value);


protected:
    ebucoreRationalBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
