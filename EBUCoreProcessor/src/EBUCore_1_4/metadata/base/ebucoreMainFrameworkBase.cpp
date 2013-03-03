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


const mxfKey ebucoreMainFrameworkBase::setKey = MXF_SET_K(ebucoreMainFramework);


ebucoreMainFrameworkBase::ebucoreMainFrameworkBase(HeaderMetadata *headerMetadata)
: DMFramework(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreMainFrameworkBase::ebucoreMainFrameworkBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: DMFramework(headerMetadata, cMetadataSet)
{}

ebucoreMainFrameworkBase::~ebucoreMainFrameworkBase()
{}


bool ebucoreMainFrameworkBase::havedocumentLocator() const
{
    return haveItem(&MXF_ITEM_K(ebucoreMainFramework, documentLocator));
}

std::string ebucoreMainFrameworkBase::getdocumentLocator() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreMainFramework, documentLocator));
}

bool ebucoreMainFrameworkBase::havedocumentId() const
{
    return haveItem(&MXF_ITEM_K(ebucoreMainFramework, documentId));
}

std::string ebucoreMainFrameworkBase::getdocumentId() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreMainFramework, documentId));
}

bool ebucoreMainFrameworkBase::havecoreMetadata() const
{
    return haveItem(&MXF_ITEM_K(ebucoreMainFramework, coreMetadata));
}

ebucoreCoreMetadata* ebucoreMainFrameworkBase::getcoreMetadata() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreMainFramework, coreMetadata)));
    MXFPP_CHECK(dynamic_cast<ebucoreCoreMetadata*>(obj.get()) != 0);
    return dynamic_cast<ebucoreCoreMetadata*>(obj.release());
}

bool ebucoreMainFrameworkBase::havemetadataSchemeInformation() const
{
    return haveItem(&MXF_ITEM_K(ebucoreMainFramework, metadataSchemeInformation));
}

ebucoreMetadataSchemeInformation* ebucoreMainFrameworkBase::getmetadataSchemeInformation() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreMainFramework, metadataSchemeInformation)));
    MXFPP_CHECK(dynamic_cast<ebucoreMetadataSchemeInformation*>(obj.get()) != 0);
    return dynamic_cast<ebucoreMetadataSchemeInformation*>(obj.release());
}

void ebucoreMainFrameworkBase::setdocumentLocator(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreMainFramework, documentLocator), value);
}

void ebucoreMainFrameworkBase::setdocumentId(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreMainFramework, documentId), value);
}

void ebucoreMainFrameworkBase::setcoreMetadata(ebucoreCoreMetadata* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreMainFramework, coreMetadata), value);
}

void ebucoreMainFrameworkBase::setmetadataSchemeInformation(ebucoreMetadataSchemeInformation* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreMainFramework, metadataSchemeInformation), value);
}

