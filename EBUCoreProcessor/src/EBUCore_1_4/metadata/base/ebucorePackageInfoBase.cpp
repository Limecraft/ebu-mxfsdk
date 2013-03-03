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


const mxfKey ebucorePackageInfoBase::setKey = MXF_SET_K(ebucorePackageInfo);


ebucorePackageInfoBase::ebucorePackageInfoBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucorePackageInfoBase::ebucorePackageInfoBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucorePackageInfoBase::~ebucorePackageInfoBase()
{}


bool ebucorePackageInfoBase::havepackageSize() const
{
    return haveItem(&MXF_ITEM_K(ebucorePackageInfo, packageSize));
}

uint64_t ebucorePackageInfoBase::getpackageSize() const
{
    return getUInt64Item(&MXF_ITEM_K(ebucorePackageInfo, packageSize));
}

bool ebucorePackageInfoBase::havepackageName() const
{
    return haveItem(&MXF_ITEM_K(ebucorePackageInfo, packageName));
}

std::string ebucorePackageInfoBase::getpackageName() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePackageInfo, packageName));
}

bool ebucorePackageInfoBase::havepackageLocator() const
{
    return haveItem(&MXF_ITEM_K(ebucorePackageInfo, packageLocator));
}

std::string ebucorePackageInfoBase::getpackageLocator() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePackageInfo, packageLocator));
}

void ebucorePackageInfoBase::setpackageSize(uint64_t value)
{
    setUInt64Item(&MXF_ITEM_K(ebucorePackageInfo, packageSize), value);
}

void ebucorePackageInfoBase::setpackageName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePackageInfo, packageName), value);
}

void ebucorePackageInfoBase::setpackageLocator(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePackageInfo, packageLocator), value);
}

