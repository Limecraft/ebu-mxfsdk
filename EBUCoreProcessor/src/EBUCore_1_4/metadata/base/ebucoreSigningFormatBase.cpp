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


const mxfKey ebucoreSigningFormatBase::setKey = MXF_SET_K(ebucoreSigningFormat);


ebucoreSigningFormatBase::ebucoreSigningFormatBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreSigningFormatBase::ebucoreSigningFormatBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreSigningFormatBase::~ebucoreSigningFormatBase()
{}


bool ebucoreSigningFormatBase::havesigningFormatID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSigningFormat, signingFormatID));
}

std::string ebucoreSigningFormatBase::getsigningFormatID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingFormatID));
}

bool ebucoreSigningFormatBase::havesigningFormatVersionID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSigningFormat, signingFormatVersionID));
}

std::string ebucoreSigningFormatBase::getsigningFormatVersionID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingFormatVersionID));
}

bool ebucoreSigningFormatBase::havesigningFormatName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSigningFormat, signingFormatName));
}

std::string ebucoreSigningFormatBase::getsigningFormatName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingFormatName));
}

bool ebucoreSigningFormatBase::havesigningTrackID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackID));
}

std::string ebucoreSigningFormatBase::getsigningTrackID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackID));
}

bool ebucoreSigningFormatBase::havesigningTrackName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackName));
}

std::string ebucoreSigningFormatBase::getsigningTrackName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackName));
}

bool ebucoreSigningFormatBase::havesigningTrackLanguageCode() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackLanguageCode));
}

std::string ebucoreSigningFormatBase::getsigningTrackLanguageCode() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackLanguageCode));
}

bool ebucoreSigningFormatBase::havesigningSourceUri() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSigningFormat, signingSourceUri));
}

std::string ebucoreSigningFormatBase::getsigningSourceUri() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingSourceUri));
}

bool ebucoreSigningFormatBase::havesigningTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTypeGroup));
}

ebucoreTypeGroup* ebucoreSigningFormatBase::getsigningTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreSigningFormatBase::havesigningFormatGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSigningFormat, signingFormatGroup));
}

ebucoreFormatGroup* ebucoreSigningFormatBase::getsigningFormatGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreSigningFormat, signingFormatGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreFormatGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreFormatGroup*>(obj.release());
}

void ebucoreSigningFormatBase::setsigningFormatID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingFormatID), value);
}

void ebucoreSigningFormatBase::setsigningFormatVersionID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingFormatVersionID), value);
}

void ebucoreSigningFormatBase::setsigningFormatName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingFormatName), value);
}

void ebucoreSigningFormatBase::setsigningTrackID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackID), value);
}

void ebucoreSigningFormatBase::setsigningTrackName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackName), value);
}

void ebucoreSigningFormatBase::setsigningTrackLanguageCode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTrackLanguageCode), value);
}

void ebucoreSigningFormatBase::setsigningSourceUri(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSigningFormat, signingSourceUri), value);
}

void ebucoreSigningFormatBase::setsigningTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreSigningFormat, signingTypeGroup), value);
}

void ebucoreSigningFormatBase::setsigningFormatGroup(ebucoreFormatGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreSigningFormat, signingFormatGroup), value);
}

