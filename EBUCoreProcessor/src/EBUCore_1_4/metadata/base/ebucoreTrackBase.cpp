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


const mxfKey ebucoreTrackBase::setKey = MXF_SET_K(ebucoreTrack);


ebucoreTrackBase::ebucoreTrackBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreTrackBase::ebucoreTrackBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreTrackBase::~ebucoreTrackBase()
{}


bool ebucoreTrackBase::havetrackID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTrack, trackID));
}

std::string ebucoreTrackBase::gettrackID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTrack, trackID));
}

bool ebucoreTrackBase::havetrackName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTrack, trackName));
}

std::string ebucoreTrackBase::gettrackName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTrack, trackName));
}

bool ebucoreTrackBase::havetrackLanguageCode() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTrack, trackLanguageCode));
}

std::string ebucoreTrackBase::gettrackLanguageCode() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTrack, trackLanguageCode));
}

bool ebucoreTrackBase::havetrackTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTrack, trackTypeGroup));
}

ebucoreTypeGroup* ebucoreTrackBase::gettrackTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreTrack, trackTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

void ebucoreTrackBase::settrackID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTrack, trackID), value);
}

void ebucoreTrackBase::settrackName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTrack, trackName), value);
}

void ebucoreTrackBase::settrackLanguageCode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTrack, trackLanguageCode), value);
}

void ebucoreTrackBase::settrackTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreTrack, trackTypeGroup), value);
}

