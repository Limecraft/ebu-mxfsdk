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


const mxfKey ebucoreAudioFormatBase::setKey = MXF_SET_K(ebucoreAudioFormat);


ebucoreAudioFormatBase::ebucoreAudioFormatBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreAudioFormatBase::ebucoreAudioFormatBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreAudioFormatBase::~ebucoreAudioFormatBase()
{}


bool ebucoreAudioFormatBase::haveaudioFormatID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioFormatID));
}

std::string ebucoreAudioFormatBase::getaudioFormatID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreAudioFormat, audioFormatID));
}

bool ebucoreAudioFormatBase::haveaudioFormatName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioFormatName));
}

std::string ebucoreAudioFormatBase::getaudioFormatName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreAudioFormat, audioFormatName));
}

bool ebucoreAudioFormatBase::haveaudioFormatDefinition() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioFormatDefinition));
}

std::string ebucoreAudioFormatBase::getaudioFormatDefinition() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreAudioFormat, audioFormatDefinition));
}

bool ebucoreAudioFormatBase::haveaudioTrackConfiguration() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTrackConfiguration));
}

ebucoreTypeGroup* ebucoreAudioFormatBase::getaudioTrackConfiguration() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTrackConfiguration)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreAudioFormatBase::haveaudioSamplingSize() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioSamplingSize));
}

uint16_t ebucoreAudioFormatBase::getaudioSamplingSize() const
{
    return getUInt16Item(&MXF_ITEM_K(ebucoreAudioFormat, audioSamplingSize));
}

bool ebucoreAudioFormatBase::haveaudioSamplingType() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioSamplingType));
}

std::string ebucoreAudioFormatBase::getaudioSamplingType() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreAudioFormat, audioSamplingType));
}

bool ebucoreAudioFormatBase::haveaudioTotalNumberOfChannels() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTotalNumberOfChannels));
}

uint16_t ebucoreAudioFormatBase::getaudioTotalNumberOfChannels() const
{
    return getUInt16Item(&MXF_ITEM_K(ebucoreAudioFormat, audioTotalNumberOfChannels));
}

bool ebucoreAudioFormatBase::haveaudioBitRate() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioBitRate));
}

uint64_t ebucoreAudioFormatBase::getaudioBitRate() const
{
    return getUInt64Item(&MXF_ITEM_K(ebucoreAudioFormat, audioBitRate));
}

bool ebucoreAudioFormatBase::haveaudioMaxBitRate() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioMaxBitRate));
}

uint64_t ebucoreAudioFormatBase::getaudioMaxBitRate() const
{
    return getUInt64Item(&MXF_ITEM_K(ebucoreAudioFormat, audioMaxBitRate));
}

bool ebucoreAudioFormatBase::haveaudioBitRateMode() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioBitRateMode));
}

std::string ebucoreAudioFormatBase::getaudioBitRateMode() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreAudioFormat, audioBitRateMode));
}

bool ebucoreAudioFormatBase::haveaudioSamplingRate() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioSamplingRate));
}

mxfRational ebucoreAudioFormatBase::getaudioSamplingRate() const
{
    return getRationalItem(&MXF_ITEM_K(ebucoreAudioFormat, audioSamplingRate));
}

bool ebucoreAudioFormatBase::haveaudioEncoding() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioEncoding));
}

ebucoreTypeGroup* ebucoreAudioFormatBase::getaudioEncoding() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreAudioFormat, audioEncoding)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreAudioFormatBase::haveaudioCodec() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioCodec));
}

ebucoreCodec* ebucoreAudioFormatBase::getaudioCodec() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreAudioFormat, audioCodec)));
    MXFPP_CHECK(dynamic_cast<ebucoreCodec*>(obj.get()) != 0);
    return dynamic_cast<ebucoreCodec*>(obj.release());
}

bool ebucoreAudioFormatBase::haveaudioTrack() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTrack));
}

std::vector<ebucoreTrack*> ebucoreAudioFormatBase::getaudioTrack() const
{
    vector<ebucoreTrack*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTrack)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTrack*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTrack*>(iter->get()));
    }
    return result;
}

bool ebucoreAudioFormatBase::haveaudioTechnicalAttributeString() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeString));
}

std::vector<ebucoreTechnicalAttributeString*> ebucoreAudioFormatBase::getaudioTechnicalAttributeString() const
{
    vector<ebucoreTechnicalAttributeString*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeString)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeString*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeString*>(iter->get()));
    }
    return result;
}

bool ebucoreAudioFormatBase::haveaudioTechnicalAttributeInt8() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt8));
}

std::vector<ebucoreTechnicalAttributeInt8*> ebucoreAudioFormatBase::getaudioTechnicalAttributeInt8() const
{
    vector<ebucoreTechnicalAttributeInt8*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt8)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt8*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt8*>(iter->get()));
    }
    return result;
}

bool ebucoreAudioFormatBase::haveaudioTechnicalAttributeInt16() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt16));
}

std::vector<ebucoreTechnicalAttributeInt16*> ebucoreAudioFormatBase::getaudioTechnicalAttributeInt16() const
{
    vector<ebucoreTechnicalAttributeInt16*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt16)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt16*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt16*>(iter->get()));
    }
    return result;
}

bool ebucoreAudioFormatBase::haveaudioTechnicalAttributeInt32() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt32));
}

std::vector<ebucoreTechnicalAttributeInt32*> ebucoreAudioFormatBase::getaudioTechnicalAttributeInt32() const
{
    vector<ebucoreTechnicalAttributeInt32*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt32)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt32*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt32*>(iter->get()));
    }
    return result;
}

bool ebucoreAudioFormatBase::haveaudioTechnicalAttributeInt64() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt64));
}

std::vector<ebucoreTechnicalAttributeInt64*> ebucoreAudioFormatBase::getaudioTechnicalAttributeInt64() const
{
    vector<ebucoreTechnicalAttributeInt64*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt64)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt64*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt64*>(iter->get()));
    }
    return result;
}

bool ebucoreAudioFormatBase::haveaudioTechnicalAttributeUInt8() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt8));
}

std::vector<ebucoreTechnicalAttributeUInt8*> ebucoreAudioFormatBase::getaudioTechnicalAttributeUInt8() const
{
    vector<ebucoreTechnicalAttributeUInt8*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt8)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt8*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt8*>(iter->get()));
    }
    return result;
}

bool ebucoreAudioFormatBase::haveaudioTechnicalAttributeUInt16() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt16));
}

std::vector<ebucoreTechnicalAttributeUInt16*> ebucoreAudioFormatBase::getaudioTechnicalAttributeUInt16() const
{
    vector<ebucoreTechnicalAttributeUInt16*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt16)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt16*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt16*>(iter->get()));
    }
    return result;
}

bool ebucoreAudioFormatBase::haveaudioTechnicalAttributeUInt32() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt32));
}

std::vector<ebucoreTechnicalAttributeUInt32*> ebucoreAudioFormatBase::getaudioTechnicalAttributeUInt32() const
{
    vector<ebucoreTechnicalAttributeUInt32*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt32)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt32*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt32*>(iter->get()));
    }
    return result;
}

bool ebucoreAudioFormatBase::haveaudioTechnicalAttributeUInt64() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt64));
}

std::vector<ebucoreTechnicalAttributeUInt64*> ebucoreAudioFormatBase::getaudioTechnicalAttributeUInt64() const
{
    vector<ebucoreTechnicalAttributeUInt64*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt64)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt64*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt64*>(iter->get()));
    }
    return result;
}

bool ebucoreAudioFormatBase::haveaudioTechnicalAttributeFloat() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeFloat));
}

std::vector<ebucoreTechnicalAttributeFloat*> ebucoreAudioFormatBase::getaudioTechnicalAttributeFloat() const
{
    vector<ebucoreTechnicalAttributeFloat*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeFloat)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeFloat*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeFloat*>(iter->get()));
    }
    return result;
}

bool ebucoreAudioFormatBase::haveaudioTechnicalAttributeRational() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeRational));
}

std::vector<ebucoreTechnicalAttributeRational*> ebucoreAudioFormatBase::getaudioTechnicalAttributeRational() const
{
    vector<ebucoreTechnicalAttributeRational*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeRational)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeRational*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeRational*>(iter->get()));
    }
    return result;
}

bool ebucoreAudioFormatBase::haveaudioTechnicalAttributeAnyURI() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeAnyURI));
}

std::vector<ebucoreTechnicalAttributeAnyURI*> ebucoreAudioFormatBase::getaudioTechnicalAttributeAnyURI() const
{
    vector<ebucoreTechnicalAttributeAnyURI*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeAnyURI)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeAnyURI*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeAnyURI*>(iter->get()));
    }
    return result;
}

bool ebucoreAudioFormatBase::haveaudioTechnicalAttributeBoolean() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeBoolean));
}

std::vector<ebucoreTechnicalAttributeBoolean*> ebucoreAudioFormatBase::getaudioTechnicalAttributeBoolean() const
{
    vector<ebucoreTechnicalAttributeBoolean*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeBoolean)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeBoolean*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeBoolean*>(iter->get()));
    }
    return result;
}

void ebucoreAudioFormatBase::setaudioFormatID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreAudioFormat, audioFormatID), value);
}

void ebucoreAudioFormatBase::setaudioFormatName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreAudioFormat, audioFormatName), value);
}

void ebucoreAudioFormatBase::setaudioFormatDefinition(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreAudioFormat, audioFormatDefinition), value);
}

void ebucoreAudioFormatBase::setaudioTrackConfiguration(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTrackConfiguration), value);
}

void ebucoreAudioFormatBase::setaudioSamplingSize(uint16_t value)
{
    setUInt16Item(&MXF_ITEM_K(ebucoreAudioFormat, audioSamplingSize), value);
}

void ebucoreAudioFormatBase::setaudioSamplingType(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreAudioFormat, audioSamplingType), value);
}

void ebucoreAudioFormatBase::setaudioTotalNumberOfChannels(uint16_t value)
{
    setUInt16Item(&MXF_ITEM_K(ebucoreAudioFormat, audioTotalNumberOfChannels), value);
}

void ebucoreAudioFormatBase::setaudioBitRate(uint64_t value)
{
    setUInt64Item(&MXF_ITEM_K(ebucoreAudioFormat, audioBitRate), value);
}

void ebucoreAudioFormatBase::setaudioMaxBitRate(uint64_t value)
{
    setUInt64Item(&MXF_ITEM_K(ebucoreAudioFormat, audioMaxBitRate), value);
}

void ebucoreAudioFormatBase::setaudioBitRateMode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreAudioFormat, audioBitRateMode), value);
}

void ebucoreAudioFormatBase::setaudioSamplingRate(mxfRational value)
{
    setRationalItem(&MXF_ITEM_K(ebucoreAudioFormat, audioSamplingRate), value);
}

void ebucoreAudioFormatBase::setaudioEncoding(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreAudioFormat, audioEncoding), value);
}

void ebucoreAudioFormatBase::setaudioCodec(ebucoreCodec* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreAudioFormat, audioCodec), value);
}

void ebucoreAudioFormatBase::setaudioTrack(const std::vector<ebucoreTrack*>& value)
{
    WrapObjectVectorIterator<ebucoreTrack> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTrack), &iter);
}

void ebucoreAudioFormatBase::appendaudioTrack(ebucoreTrack* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTrack), value);
}

void ebucoreAudioFormatBase::setaudioTechnicalAttributeString(const std::vector<ebucoreTechnicalAttributeString*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeString> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeString), &iter);
}

void ebucoreAudioFormatBase::appendaudioTechnicalAttributeString(ebucoreTechnicalAttributeString* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeString), value);
}

void ebucoreAudioFormatBase::setaudioTechnicalAttributeInt8(const std::vector<ebucoreTechnicalAttributeInt8*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt8> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt8), &iter);
}

void ebucoreAudioFormatBase::appendaudioTechnicalAttributeInt8(ebucoreTechnicalAttributeInt8* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt8), value);
}

void ebucoreAudioFormatBase::setaudioTechnicalAttributeInt16(const std::vector<ebucoreTechnicalAttributeInt16*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt16> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt16), &iter);
}

void ebucoreAudioFormatBase::appendaudioTechnicalAttributeInt16(ebucoreTechnicalAttributeInt16* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt16), value);
}

void ebucoreAudioFormatBase::setaudioTechnicalAttributeInt32(const std::vector<ebucoreTechnicalAttributeInt32*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt32> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt32), &iter);
}

void ebucoreAudioFormatBase::appendaudioTechnicalAttributeInt32(ebucoreTechnicalAttributeInt32* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt32), value);
}

void ebucoreAudioFormatBase::setaudioTechnicalAttributeInt64(const std::vector<ebucoreTechnicalAttributeInt64*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt64> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt64), &iter);
}

void ebucoreAudioFormatBase::appendaudioTechnicalAttributeInt64(ebucoreTechnicalAttributeInt64* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt64), value);
}

void ebucoreAudioFormatBase::setaudioTechnicalAttributeUInt8(const std::vector<ebucoreTechnicalAttributeUInt8*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt8> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt8), &iter);
}

void ebucoreAudioFormatBase::appendaudioTechnicalAttributeUInt8(ebucoreTechnicalAttributeUInt8* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt8), value);
}

void ebucoreAudioFormatBase::setaudioTechnicalAttributeUInt16(const std::vector<ebucoreTechnicalAttributeUInt16*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt16> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt16), &iter);
}

void ebucoreAudioFormatBase::appendaudioTechnicalAttributeUInt16(ebucoreTechnicalAttributeUInt16* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt16), value);
}

void ebucoreAudioFormatBase::setaudioTechnicalAttributeUInt32(const std::vector<ebucoreTechnicalAttributeUInt32*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt32> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt32), &iter);
}

void ebucoreAudioFormatBase::appendaudioTechnicalAttributeUInt32(ebucoreTechnicalAttributeUInt32* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt32), value);
}

void ebucoreAudioFormatBase::setaudioTechnicalAttributeUInt64(const std::vector<ebucoreTechnicalAttributeUInt64*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt64> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt64), &iter);
}

void ebucoreAudioFormatBase::appendaudioTechnicalAttributeUInt64(ebucoreTechnicalAttributeUInt64* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt64), value);
}

void ebucoreAudioFormatBase::setaudioTechnicalAttributeFloat(const std::vector<ebucoreTechnicalAttributeFloat*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeFloat> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeFloat), &iter);
}

void ebucoreAudioFormatBase::appendaudioTechnicalAttributeFloat(ebucoreTechnicalAttributeFloat* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeFloat), value);
}

void ebucoreAudioFormatBase::setaudioTechnicalAttributeRational(const std::vector<ebucoreTechnicalAttributeRational*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeRational> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeRational), &iter);
}

void ebucoreAudioFormatBase::appendaudioTechnicalAttributeRational(ebucoreTechnicalAttributeRational* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeRational), value);
}

void ebucoreAudioFormatBase::setaudioTechnicalAttributeAnyURI(const std::vector<ebucoreTechnicalAttributeAnyURI*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeAnyURI> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeAnyURI), &iter);
}

void ebucoreAudioFormatBase::appendaudioTechnicalAttributeAnyURI(ebucoreTechnicalAttributeAnyURI* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeAnyURI), value);
}

void ebucoreAudioFormatBase::setaudioTechnicalAttributeBoolean(const std::vector<ebucoreTechnicalAttributeBoolean*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeBoolean> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeBoolean), &iter);
}

void ebucoreAudioFormatBase::appendaudioTechnicalAttributeBoolean(ebucoreTechnicalAttributeBoolean* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeBoolean), value);
}

