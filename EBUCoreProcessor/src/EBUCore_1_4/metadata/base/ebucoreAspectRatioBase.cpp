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


const mxfKey ebucoreAspectRatioBase::setKey = MXF_SET_K(ebucoreAspectRatio);


ebucoreAspectRatioBase::ebucoreAspectRatioBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreAspectRatioBase::ebucoreAspectRatioBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreAspectRatioBase::~ebucoreAspectRatioBase()
{}


uint64_t ebucoreAspectRatioBase::getaspectRatioFactorNumerator() const
{
    return getUInt64Item(&MXF_ITEM_K(ebucoreAspectRatio, aspectRatioFactorNumerator));
}

uint64_t ebucoreAspectRatioBase::getaspectRatioFactorDenominator() const
{
    return getUInt64Item(&MXF_ITEM_K(ebucoreAspectRatio, aspectRatioFactorDenominator));
}

bool ebucoreAspectRatioBase::haveaspectRatioTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAspectRatio, aspectRatioTypeGroup));
}

ebucoreTypeGroup* ebucoreAspectRatioBase::getaspectRatioTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreAspectRatio, aspectRatioTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

void ebucoreAspectRatioBase::setaspectRatioFactorNumerator(uint64_t value)
{
    setUInt64Item(&MXF_ITEM_K(ebucoreAspectRatio, aspectRatioFactorNumerator), value);
}

void ebucoreAspectRatioBase::setaspectRatioFactorDenominator(uint64_t value)
{
    setUInt64Item(&MXF_ITEM_K(ebucoreAspectRatio, aspectRatioFactorDenominator), value);
}

void ebucoreAspectRatioBase::setaspectRatioTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreAspectRatio, aspectRatioTypeGroup), value);
}

