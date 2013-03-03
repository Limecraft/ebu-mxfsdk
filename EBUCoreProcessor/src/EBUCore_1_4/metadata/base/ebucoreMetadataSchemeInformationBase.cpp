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


const mxfKey ebucoreMetadataSchemeInformationBase::setKey = MXF_SET_K(ebucoreMetadataSchemeInformation);


ebucoreMetadataSchemeInformationBase::ebucoreMetadataSchemeInformationBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreMetadataSchemeInformationBase::ebucoreMetadataSchemeInformationBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreMetadataSchemeInformationBase::~ebucoreMetadataSchemeInformationBase()
{}


bool ebucoreMetadataSchemeInformationBase::haveebucoreMetadataScheme() const
{
    return haveItem(&MXF_ITEM_K(ebucoreMetadataSchemeInformation, ebucoreMetadataScheme));
}

std::string ebucoreMetadataSchemeInformationBase::getebucoreMetadataScheme() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreMetadataSchemeInformation, ebucoreMetadataScheme));
}

bool ebucoreMetadataSchemeInformationBase::haveebucoreMetadataSchemeVersion() const
{
    return haveItem(&MXF_ITEM_K(ebucoreMetadataSchemeInformation, ebucoreMetadataSchemeVersion));
}

std::string ebucoreMetadataSchemeInformationBase::getebucoreMetadataSchemeVersion() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreMetadataSchemeInformation, ebucoreMetadataSchemeVersion));
}

bool ebucoreMetadataSchemeInformationBase::haveebucoreFrameworktextLanguage() const
{
    return haveItem(&MXF_ITEM_K(ebucoreMetadataSchemeInformation, ebucoreFrameworktextLanguage));
}

std::string ebucoreMetadataSchemeInformationBase::getebucoreFrameworktextLanguage() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreMetadataSchemeInformation, ebucoreFrameworktextLanguage));
}

bool ebucoreMetadataSchemeInformationBase::haveebucoreMetadataNamespacePrefix() const
{
    return haveItem(&MXF_ITEM_K(ebucoreMetadataSchemeInformation, ebucoreMetadataNamespacePrefix));
}

std::string ebucoreMetadataSchemeInformationBase::getebucoreMetadataNamespacePrefix() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreMetadataSchemeInformation, ebucoreMetadataNamespacePrefix));
}

bool ebucoreMetadataSchemeInformationBase::haveebucoreMetadataProvider() const
{
    return haveItem(&MXF_ITEM_K(ebucoreMetadataSchemeInformation, ebucoreMetadataProvider));
}

ebucoreEntity* ebucoreMetadataSchemeInformationBase::getebucoreMetadataProvider() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreMetadataSchemeInformation, ebucoreMetadataProvider)));
    MXFPP_CHECK(dynamic_cast<ebucoreEntity*>(obj.get()) != 0);
    return dynamic_cast<ebucoreEntity*>(obj.release());
}

void ebucoreMetadataSchemeInformationBase::setebucoreMetadataScheme(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreMetadataSchemeInformation, ebucoreMetadataScheme), value);
}

void ebucoreMetadataSchemeInformationBase::setebucoreMetadataSchemeVersion(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreMetadataSchemeInformation, ebucoreMetadataSchemeVersion), value);
}

void ebucoreMetadataSchemeInformationBase::setebucoreFrameworktextLanguage(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreMetadataSchemeInformation, ebucoreFrameworktextLanguage), value);
}

void ebucoreMetadataSchemeInformationBase::setebucoreMetadataNamespacePrefix(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreMetadataSchemeInformation, ebucoreMetadataNamespacePrefix), value);
}

void ebucoreMetadataSchemeInformationBase::setebucoreMetadataProvider(ebucoreEntity* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreMetadataSchemeInformation, ebucoreMetadataProvider), value);
}

