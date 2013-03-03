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


const mxfKey ebucorePartFrameworkBase::setKey = MXF_SET_K(ebucorePartFramework);


ebucorePartFrameworkBase::ebucorePartFrameworkBase(HeaderMetadata *headerMetadata)
: DMFramework(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucorePartFrameworkBase::ebucorePartFrameworkBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: DMFramework(headerMetadata, cMetadataSet)
{}

ebucorePartFrameworkBase::~ebucorePartFrameworkBase()
{}


bool ebucorePartFrameworkBase::havepartMetadata() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartFramework, partMetadata));
}

ebucorePartMetadata* ebucorePartFrameworkBase::getpartMetadata() const
{
    auto_ptr<MetadataSet> obj(getWeakRefItem(&MXF_ITEM_K(ebucorePartFramework, partMetadata)));
    MXFPP_CHECK(dynamic_cast<ebucorePartMetadata*>(obj.get()) != 0);
    return dynamic_cast<ebucorePartMetadata*>(obj.release());
}

void ebucorePartFrameworkBase::setpartMetadata(ebucorePartMetadata* value)
{
    setWeakRefItem(&MXF_ITEM_K(ebucorePartFramework, partMetadata), value);
}

