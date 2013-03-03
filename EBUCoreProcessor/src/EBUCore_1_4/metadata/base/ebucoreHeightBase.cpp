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


const mxfKey ebucoreHeightBase::setKey = MXF_SET_K(ebucoreHeight);


ebucoreHeightBase::ebucoreHeightBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreHeightBase::ebucoreHeightBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreHeightBase::~ebucoreHeightBase()
{}


ebucoreDimension* ebucoreHeightBase::getheightValue() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreHeight, heightValue)));
    MXFPP_CHECK(dynamic_cast<ebucoreDimension*>(obj.get()) != 0);
    return dynamic_cast<ebucoreDimension*>(obj.release());
}

bool ebucoreHeightBase::haveheightTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreHeight, heightTypeGroup));
}

ebucoreTypeGroup* ebucoreHeightBase::getheightTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreHeight, heightTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

void ebucoreHeightBase::setheightValue(ebucoreDimension* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreHeight, heightValue), value);
}

void ebucoreHeightBase::setheightTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreHeight, heightTypeGroup), value);
}

