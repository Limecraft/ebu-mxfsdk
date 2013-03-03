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


const mxfKey ebucoreAncillaryDataBase::setKey = MXF_SET_K(ebucoreAncillaryData);


ebucoreAncillaryDataBase::ebucoreAncillaryDataBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreAncillaryDataBase::ebucoreAncillaryDataBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreAncillaryDataBase::~ebucoreAncillaryDataBase()
{}


bool ebucoreAncillaryDataBase::haveDID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAncillaryData, DID));
}

uint32_t ebucoreAncillaryDataBase::getDID() const
{
    return getUInt32Item(&MXF_ITEM_K(ebucoreAncillaryData, DID));
}

bool ebucoreAncillaryDataBase::haveSDID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAncillaryData, SDID));
}

uint32_t ebucoreAncillaryDataBase::getSDID() const
{
    return getUInt32Item(&MXF_ITEM_K(ebucoreAncillaryData, SDID));
}

bool ebucoreAncillaryDataBase::havelineNumber() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAncillaryData, lineNumber));
}

std::vector<uint32_t> ebucoreAncillaryDataBase::getlineNumber() const
{
    return getUInt32ArrayItem(&MXF_ITEM_K(ebucoreAncillaryData, lineNumber));
}

bool ebucoreAncillaryDataBase::haveANCWrappingType() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAncillaryData, ANCWrappingType));
}

ebucoreTypeGroup* ebucoreAncillaryDataBase::getANCWrappingType() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreAncillaryData, ANCWrappingType)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

void ebucoreAncillaryDataBase::setDID(uint32_t value)
{
    setUInt32Item(&MXF_ITEM_K(ebucoreAncillaryData, DID), value);
}

void ebucoreAncillaryDataBase::setSDID(uint32_t value)
{
    setUInt32Item(&MXF_ITEM_K(ebucoreAncillaryData, SDID), value);
}

void ebucoreAncillaryDataBase::setlineNumber(const std::vector<uint32_t>& value)
{
    setUInt32ArrayItem(&MXF_ITEM_K(ebucoreAncillaryData, lineNumber), value);
}

void ebucoreAncillaryDataBase::appendlineNumber(uint32_t value)
{
    appendUInt32ArrayItem(&MXF_ITEM_K(ebucoreAncillaryData, lineNumber), value);
}

void ebucoreAncillaryDataBase::setANCWrappingType(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreAncillaryData, ANCWrappingType), value);
}

