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


const mxfKey ebucoreTechnicalAttributeInt16Base::setKey = MXF_SET_K(ebucoreTechnicalAttributeInt16);


ebucoreTechnicalAttributeInt16Base::ebucoreTechnicalAttributeInt16Base(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreTechnicalAttributeInt16Base::ebucoreTechnicalAttributeInt16Base(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreTechnicalAttributeInt16Base::~ebucoreTechnicalAttributeInt16Base()
{}


int16_t ebucoreTechnicalAttributeInt16Base::gettechnicalAttributeInt16Value() const
{
    return getInt16Item(&MXF_ITEM_K(ebucoreTechnicalAttributeInt16, technicalAttributeInt16Value));
}

bool ebucoreTechnicalAttributeInt16Base::havetechnicalAttributeTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTechnicalAttributeInt16, technicalAttributeTypeGroup));
}

ebucoreTypeGroup* ebucoreTechnicalAttributeInt16Base::gettechnicalAttributeTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreTechnicalAttributeInt16, technicalAttributeTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

void ebucoreTechnicalAttributeInt16Base::settechnicalAttributeInt16Value(int16_t value)
{
    setInt16Item(&MXF_ITEM_K(ebucoreTechnicalAttributeInt16, technicalAttributeInt16Value), value);
}

void ebucoreTechnicalAttributeInt16Base::settechnicalAttributeTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreTechnicalAttributeInt16, technicalAttributeTypeGroup), value);
}

