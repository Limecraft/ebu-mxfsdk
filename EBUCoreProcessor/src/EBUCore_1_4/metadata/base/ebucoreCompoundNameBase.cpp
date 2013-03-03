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


const mxfKey ebucoreCompoundNameBase::setKey = MXF_SET_K(ebucoreCompoundName);


ebucoreCompoundNameBase::ebucoreCompoundNameBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreCompoundNameBase::ebucoreCompoundNameBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreCompoundNameBase::~ebucoreCompoundNameBase()
{}


bool ebucoreCompoundNameBase::havecompoundName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCompoundName, compoundName));
}

std::string ebucoreCompoundNameBase::getcompoundName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCompoundName, compoundName));
}

bool ebucoreCompoundNameBase::havecompoundNameTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCompoundName, compoundNameTypeGroup));
}

ebucoreTypeGroup* ebucoreCompoundNameBase::getcompoundNameTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreCompoundName, compoundNameTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreCompoundNameBase::havecompoundNameFormatGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCompoundName, compoundNameFormatGroup));
}

ebucoreFormatGroup* ebucoreCompoundNameBase::getcompoundNameFormatGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreCompoundName, compoundNameFormatGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreFormatGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreFormatGroup*>(obj.release());
}

void ebucoreCompoundNameBase::setcompoundName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCompoundName, compoundName), value);
}

void ebucoreCompoundNameBase::setcompoundNameTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreCompoundName, compoundNameTypeGroup), value);
}

void ebucoreCompoundNameBase::setcompoundNameFormatGroup(ebucoreFormatGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreCompoundName, compoundNameFormatGroup), value);
}

