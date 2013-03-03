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


const mxfKey ebucoreTechnicalAttributeFloatBase::setKey = MXF_SET_K(ebucoreTechnicalAttributeFloat);


ebucoreTechnicalAttributeFloatBase::ebucoreTechnicalAttributeFloatBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreTechnicalAttributeFloatBase::ebucoreTechnicalAttributeFloatBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreTechnicalAttributeFloatBase::~ebucoreTechnicalAttributeFloatBase()
{}


float ebucoreTechnicalAttributeFloatBase::gettechnicalAttributeFloatValue() const
{
    return getFloatItem(&MXF_ITEM_K(ebucoreTechnicalAttributeFloat, technicalAttributeFloatValue));
}

bool ebucoreTechnicalAttributeFloatBase::havetechnicalAttributeTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTechnicalAttributeFloat, technicalAttributeTypeGroup));
}

ebucoreTypeGroup* ebucoreTechnicalAttributeFloatBase::gettechnicalAttributeTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreTechnicalAttributeFloat, technicalAttributeTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

void ebucoreTechnicalAttributeFloatBase::settechnicalAttributeFloatValue(float value)
{
    setFloatItem(&MXF_ITEM_K(ebucoreTechnicalAttributeFloat, technicalAttributeFloatValue), value);
}

void ebucoreTechnicalAttributeFloatBase::settechnicalAttributeTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreTechnicalAttributeFloat, technicalAttributeTypeGroup), value);
}

