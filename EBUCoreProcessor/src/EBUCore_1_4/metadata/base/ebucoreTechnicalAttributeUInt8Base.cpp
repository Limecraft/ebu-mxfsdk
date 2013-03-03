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
  
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <memory>

#include <libMXF++/MXF.h>
#include <EBUCore_1_4/metadata/EBUCoreDMS++.h>


using namespace std;
using namespace mxfpp;
using namespace EBUSDK::EBUCore::EBUCore_1_4::KLV;


const mxfKey ebucoreTechnicalAttributeUInt8Base::setKey = MXF_SET_K(ebucoreTechnicalAttributeUInt8);


ebucoreTechnicalAttributeUInt8Base::ebucoreTechnicalAttributeUInt8Base(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreTechnicalAttributeUInt8Base::ebucoreTechnicalAttributeUInt8Base(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreTechnicalAttributeUInt8Base::~ebucoreTechnicalAttributeUInt8Base()
{}


uint8_t ebucoreTechnicalAttributeUInt8Base::gettechnicalAttributeUInt8Value() const
{
    return getUInt8Item(&MXF_ITEM_K(ebucoreTechnicalAttributeUInt8, technicalAttributeUInt8Value));
}

bool ebucoreTechnicalAttributeUInt8Base::havetechnicalAttributeTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTechnicalAttributeUInt8, technicalAttributeTypeGroup));
}

ebucoreTypeGroup* ebucoreTechnicalAttributeUInt8Base::gettechnicalAttributeTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreTechnicalAttributeUInt8, technicalAttributeTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

void ebucoreTechnicalAttributeUInt8Base::settechnicalAttributeUInt8Value(uint8_t value)
{
    setUInt8Item(&MXF_ITEM_K(ebucoreTechnicalAttributeUInt8, technicalAttributeUInt8Value), value);
}

void ebucoreTechnicalAttributeUInt8Base::settechnicalAttributeTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreTechnicalAttributeUInt8, technicalAttributeTypeGroup), value);
}

