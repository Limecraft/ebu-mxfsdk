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


const mxfKey ebucorePublicationChannelBase::setKey = MXF_SET_K(ebucorePublicationChannel);


ebucorePublicationChannelBase::ebucorePublicationChannelBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucorePublicationChannelBase::ebucorePublicationChannelBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucorePublicationChannelBase::~ebucorePublicationChannelBase()
{}


bool ebucorePublicationChannelBase::havepublicationChannelName() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationChannel, publicationChannelName));
}

std::string ebucorePublicationChannelBase::getpublicationChannelName() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePublicationChannel, publicationChannelName));
}

bool ebucorePublicationChannelBase::havepublicationChannelId() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationChannel, publicationChannelId));
}

std::string ebucorePublicationChannelBase::getpublicationChannelId() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePublicationChannel, publicationChannelId));
}

bool ebucorePublicationChannelBase::havepublicationChannelLinkToLogo() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationChannel, publicationChannelLinkToLogo));
}

std::string ebucorePublicationChannelBase::getpublicationChannelLinkToLogo() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePublicationChannel, publicationChannelLinkToLogo));
}

bool ebucorePublicationChannelBase::havepublicationChannelType() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationChannel, publicationChannelType));
}

ebucoreTypeGroup* ebucorePublicationChannelBase::getpublicationChannelType() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucorePublicationChannel, publicationChannelType)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

void ebucorePublicationChannelBase::setpublicationChannelName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePublicationChannel, publicationChannelName), value);
}

void ebucorePublicationChannelBase::setpublicationChannelId(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePublicationChannel, publicationChannelId), value);
}

void ebucorePublicationChannelBase::setpublicationChannelLinkToLogo(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePublicationChannel, publicationChannelLinkToLogo), value);
}

void ebucorePublicationChannelBase::setpublicationChannelType(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucorePublicationChannel, publicationChannelType), value);
}

