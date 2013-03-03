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
  
#ifndef __MXFPP_EBUCORETECHNICALATTRIBUTEINT16_H__
#define __MXFPP_EBUCORETECHNICALATTRIBUTEINT16_H__



#include <EBUCore_1_4/metadata/base/ebucoreTechnicalAttributeInt16Base.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreTechnicalAttributeInt16 : public ebucoreTechnicalAttributeInt16Base
{
public:
    friend class MetadataSetFactory<ebucoreTechnicalAttributeInt16>;

public:
    ebucoreTechnicalAttributeInt16(HeaderMetadata *headerMetadata);
    virtual ~ebucoreTechnicalAttributeInt16();




protected:
    ebucoreTechnicalAttributeInt16(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
