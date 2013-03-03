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


const mxfKey ebucoreSubtitlingBase::setKey = MXF_SET_K(ebucoreSubtitling);


ebucoreSubtitlingBase::ebucoreSubtitlingBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreSubtitlingBase::ebucoreSubtitlingBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreSubtitlingBase::~ebucoreSubtitlingBase()
{}


bool ebucoreSubtitlingBase::havesubtitlingFormatID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingFormatID));
}

std::string ebucoreSubtitlingBase::getsubtitlingFormatID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingFormatID));
}

bool ebucoreSubtitlingBase::havesubtitlingFormatName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingFormatName));
}

std::string ebucoreSubtitlingBase::getsubtitlingFormatName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingFormatName));
}

bool ebucoreSubtitlingBase::havesubtitlingSourceUri() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingSourceUri));
}

std::string ebucoreSubtitlingBase::getsubtitlingSourceUri() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingSourceUri));
}

bool ebucoreSubtitlingBase::havesubtitlingTrackID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingTrackID));
}

std::string ebucoreSubtitlingBase::getsubtitlingTrackID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingTrackID));
}

bool ebucoreSubtitlingBase::havesubtitlingTrackName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingTrackName));
}

std::string ebucoreSubtitlingBase::getsubtitlingTrackName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingTrackName));
}

bool ebucoreSubtitlingBase::havesubtitlingLanguageCode() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingLanguageCode));
}

std::string ebucoreSubtitlingBase::getsubtitlingLanguageCode() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingLanguageCode));
}

bool ebucoreSubtitlingBase::havesubtitlingTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingTypeGroup));
}

ebucoreTypeGroup* ebucoreSubtitlingBase::getsubtitlingTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreSubtitlingBase::havesubtitlingFormatGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingFormatGroup));
}

ebucoreFormatGroup* ebucoreSubtitlingBase::getsubtitlingFormatGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingFormatGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreFormatGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreFormatGroup*>(obj.release());
}

void ebucoreSubtitlingBase::setsubtitlingFormatID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingFormatID), value);
}

void ebucoreSubtitlingBase::setsubtitlingFormatName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingFormatName), value);
}

void ebucoreSubtitlingBase::setsubtitlingSourceUri(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingSourceUri), value);
}

void ebucoreSubtitlingBase::setsubtitlingTrackID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingTrackID), value);
}

void ebucoreSubtitlingBase::setsubtitlingTrackName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingTrackName), value);
}

void ebucoreSubtitlingBase::setsubtitlingLanguageCode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingLanguageCode), value);
}

void ebucoreSubtitlingBase::setsubtitlingTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingTypeGroup), value);
}

void ebucoreSubtitlingBase::setsubtitlingFormatGroup(ebucoreFormatGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreSubtitling, subtitlingFormatGroup), value);
}

