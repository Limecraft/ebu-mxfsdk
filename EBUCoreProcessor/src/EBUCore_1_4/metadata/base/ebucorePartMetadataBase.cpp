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


const mxfKey ebucorePartMetadataBase::setKey = MXF_SET_K(ebucorePartMetadata);


ebucorePartMetadataBase::ebucorePartMetadataBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucorePartMetadataBase::ebucorePartMetadataBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucorePartMetadataBase::~ebucorePartMetadataBase()
{}


bool ebucorePartMetadataBase::havepartId() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partId));
}

std::string ebucorePartMetadataBase::getpartId() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePartMetadata, partId));
}

bool ebucorePartMetadataBase::havepartName() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partName));
}

std::string ebucorePartMetadataBase::getpartName() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePartMetadata, partName));
}

bool ebucorePartMetadataBase::havepartDefinition() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partDefinition));
}

std::string ebucorePartMetadataBase::getpartDefinition() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePartMetadata, partDefinition));
}

bool ebucorePartMetadataBase::havepartStartTimecode() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partStartTimecode));
}

std::string ebucorePartMetadataBase::getpartStartTimecode() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePartMetadata, partStartTimecode));
}

bool ebucorePartMetadataBase::havepartStartTimecodeDropframe() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partStartTimecodeDropframe));
}

std::string ebucorePartMetadataBase::getpartStartTimecodeDropframe() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePartMetadata, partStartTimecodeDropframe));
}

bool ebucorePartMetadataBase::havepartStartTime() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partStartTime));
}

mxfRational ebucorePartMetadataBase::getpartStartTime() const
{
    return getRationalItem(&MXF_ITEM_K(ebucorePartMetadata, partStartTime));
}

bool ebucorePartMetadataBase::havepartStartEditUnitNumber() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partStartEditUnitNumber));
}

int64_t ebucorePartMetadataBase::getpartStartEditUnitNumber() const
{
    return getLengthItem(&MXF_ITEM_K(ebucorePartMetadata, partStartEditUnitNumber));
}

bool ebucorePartMetadataBase::havepartDurationTimecode() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partDurationTimecode));
}

std::string ebucorePartMetadataBase::getpartDurationTimecode() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePartMetadata, partDurationTimecode));
}

bool ebucorePartMetadataBase::havepartDurationTimecodeDropframe() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partDurationTimecodeDropframe));
}

std::string ebucorePartMetadataBase::getpartDurationTimecodeDropframe() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePartMetadata, partDurationTimecodeDropframe));
}

bool ebucorePartMetadataBase::havepartDurationTime() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partDurationTime));
}

mxfRational ebucorePartMetadataBase::getpartDurationTime() const
{
    return getRationalItem(&MXF_ITEM_K(ebucorePartMetadata, partDurationTime));
}

bool ebucorePartMetadataBase::havepartDurationEditUnitNumber() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partDurationEditUnitNumber));
}

int64_t ebucorePartMetadataBase::getpartDurationEditUnitNumber() const
{
    return getLengthItem(&MXF_ITEM_K(ebucorePartMetadata, partDurationEditUnitNumber));
}

bool ebucorePartMetadataBase::havepartNumber() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partNumber));
}

uint8_t ebucorePartMetadataBase::getpartNumber() const
{
    return getUInt8Item(&MXF_ITEM_K(ebucorePartMetadata, partNumber));
}

bool ebucorePartMetadataBase::havepartTotalNumber() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partTotalNumber));
}

uint8_t ebucorePartMetadataBase::getpartTotalNumber() const
{
    return getUInt8Item(&MXF_ITEM_K(ebucorePartMetadata, partTotalNumber));
}

bool ebucorePartMetadataBase::havepartTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partTypeGroup));
}

ebucoreTypeGroup* ebucorePartMetadataBase::getpartTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucorePartMetadata, partTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucorePartMetadataBase::havepartMeta() const
{
    return haveItem(&MXF_ITEM_K(ebucorePartMetadata, partMeta));
}

ebucoreCoreMetadata* ebucorePartMetadataBase::getpartMeta() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucorePartMetadata, partMeta)));
    MXFPP_CHECK(dynamic_cast<ebucoreCoreMetadata*>(obj.get()) != 0);
    return dynamic_cast<ebucoreCoreMetadata*>(obj.release());
}

void ebucorePartMetadataBase::setpartId(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePartMetadata, partId), value);
}

void ebucorePartMetadataBase::setpartName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePartMetadata, partName), value);
}

void ebucorePartMetadataBase::setpartDefinition(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePartMetadata, partDefinition), value);
}

void ebucorePartMetadataBase::setpartStartTimecode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePartMetadata, partStartTimecode), value);
}

void ebucorePartMetadataBase::setpartStartTimecodeDropframe(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePartMetadata, partStartTimecodeDropframe), value);
}

void ebucorePartMetadataBase::setpartStartTime(mxfRational value)
{
    setRationalItem(&MXF_ITEM_K(ebucorePartMetadata, partStartTime), value);
}

void ebucorePartMetadataBase::setpartStartEditUnitNumber(int64_t value)
{
    setLengthItem(&MXF_ITEM_K(ebucorePartMetadata, partStartEditUnitNumber), value);
}

void ebucorePartMetadataBase::setpartDurationTimecode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePartMetadata, partDurationTimecode), value);
}

void ebucorePartMetadataBase::setpartDurationTimecodeDropframe(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePartMetadata, partDurationTimecodeDropframe), value);
}

void ebucorePartMetadataBase::setpartDurationTime(mxfRational value)
{
    setRationalItem(&MXF_ITEM_K(ebucorePartMetadata, partDurationTime), value);
}

void ebucorePartMetadataBase::setpartDurationEditUnitNumber(int64_t value)
{
    setLengthItem(&MXF_ITEM_K(ebucorePartMetadata, partDurationEditUnitNumber), value);
}

void ebucorePartMetadataBase::setpartNumber(uint8_t value)
{
    setUInt8Item(&MXF_ITEM_K(ebucorePartMetadata, partNumber), value);
}

void ebucorePartMetadataBase::setpartTotalNumber(uint8_t value)
{
    setUInt8Item(&MXF_ITEM_K(ebucorePartMetadata, partTotalNumber), value);
}

void ebucorePartMetadataBase::setpartTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucorePartMetadata, partTypeGroup), value);
}

void ebucorePartMetadataBase::setpartMeta(ebucoreCoreMetadata* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucorePartMetadata, partMeta), value);
}

