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


const mxfKey ebucoreCaptioningBase::setKey = MXF_SET_K(ebucoreCaptioning);


ebucoreCaptioningBase::ebucoreCaptioningBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreCaptioningBase::ebucoreCaptioningBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreCaptioningBase::~ebucoreCaptioningBase()
{}


bool ebucoreCaptioningBase::havecaptioningFormatID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCaptioning, captioningFormatID));
}

std::string ebucoreCaptioningBase::getcaptioningFormatID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningFormatID));
}

bool ebucoreCaptioningBase::havecaptioningFormatName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCaptioning, captioningFormatName));
}

std::string ebucoreCaptioningBase::getcaptioningFormatName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningFormatName));
}

bool ebucoreCaptioningBase::havecaptioningSourceUri() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCaptioning, captioningSourceUri));
}

std::string ebucoreCaptioningBase::getcaptioningSourceUri() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningSourceUri));
}

bool ebucoreCaptioningBase::havecaptioningTrackID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCaptioning, captioningTrackID));
}

std::string ebucoreCaptioningBase::getcaptioningTrackID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningTrackID));
}

bool ebucoreCaptioningBase::havecaptioningTrackName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCaptioning, captioningTrackName));
}

std::string ebucoreCaptioningBase::getcaptioningTrackName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningTrackName));
}

bool ebucoreCaptioningBase::havecaptioningLanguageCode() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCaptioning, captioningLanguageCode));
}

std::string ebucoreCaptioningBase::getcaptioningLanguageCode() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningLanguageCode));
}

bool ebucoreCaptioningBase::havecaptioningTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCaptioning, captioningTypeGroup));
}

ebucoreTypeGroup* ebucoreCaptioningBase::getcaptioningTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreCaptioning, captioningTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreCaptioningBase::havecaptioningFormatGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCaptioning, captioningFormatGroup));
}

ebucoreFormatGroup* ebucoreCaptioningBase::getcaptioningFormatGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreCaptioning, captioningFormatGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreFormatGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreFormatGroup*>(obj.release());
}

void ebucoreCaptioningBase::setcaptioningFormatID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningFormatID), value);
}

void ebucoreCaptioningBase::setcaptioningFormatName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningFormatName), value);
}

void ebucoreCaptioningBase::setcaptioningSourceUri(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningSourceUri), value);
}

void ebucoreCaptioningBase::setcaptioningTrackID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningTrackID), value);
}

void ebucoreCaptioningBase::setcaptioningTrackName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningTrackName), value);
}

void ebucoreCaptioningBase::setcaptioningLanguageCode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCaptioning, captioningLanguageCode), value);
}

void ebucoreCaptioningBase::setcaptioningTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreCaptioning, captioningTypeGroup), value);
}

void ebucoreCaptioningBase::setcaptioningFormatGroup(ebucoreFormatGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreCaptioning, captioningFormatGroup), value);
}

