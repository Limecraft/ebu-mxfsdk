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


const mxfKey ebucoreCodecBase::setKey = MXF_SET_K(ebucoreCodec);


ebucoreCodecBase::ebucoreCodecBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreCodecBase::ebucoreCodecBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreCodecBase::~ebucoreCodecBase()
{}


bool ebucoreCodecBase::havename() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCodec, name));
}

std::string ebucoreCodecBase::getname() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCodec, name));
}

bool ebucoreCodecBase::havevendor() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCodec, vendor));
}

std::string ebucoreCodecBase::getvendor() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCodec, vendor));
}

bool ebucoreCodecBase::haveversion() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCodec, version));
}

std::string ebucoreCodecBase::getversion() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCodec, version));
}

bool ebucoreCodecBase::havefamily() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCodec, family));
}

std::string ebucoreCodecBase::getfamily() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCodec, family));
}

bool ebucoreCodecBase::havecodecIdentifier() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCodec, codecIdentifier));
}

std::string ebucoreCodecBase::getcodecIdentifier() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreCodec, codecIdentifier));
}

void ebucoreCodecBase::setname(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCodec, name), value);
}

void ebucoreCodecBase::setvendor(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCodec, vendor), value);
}

void ebucoreCodecBase::setversion(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCodec, version), value);
}

void ebucoreCodecBase::setfamily(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCodec, family), value);
}

void ebucoreCodecBase::setcodecIdentifier(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreCodec, codecIdentifier), value);
}

