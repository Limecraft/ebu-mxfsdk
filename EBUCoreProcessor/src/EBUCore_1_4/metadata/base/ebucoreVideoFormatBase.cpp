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


const mxfKey ebucoreVideoFormatBase::setKey = MXF_SET_K(ebucoreVideoFormat);


ebucoreVideoFormatBase::ebucoreVideoFormatBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreVideoFormatBase::ebucoreVideoFormatBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreVideoFormatBase::~ebucoreVideoFormatBase()
{}


bool ebucoreVideoFormatBase::havevideoFormatID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoFormatID));
}

std::string ebucoreVideoFormatBase::getvideoFormatID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreVideoFormat, videoFormatID));
}

bool ebucoreVideoFormatBase::havevideoFormatName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoFormatName));
}

std::string ebucoreVideoFormatBase::getvideoFormatName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreVideoFormat, videoFormatName));
}

bool ebucoreVideoFormatBase::havevideoFormatDefinition() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoFormatDefinition));
}

std::string ebucoreVideoFormatBase::getvideoFormatDefinition() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreVideoFormat, videoFormatDefinition));
}

bool ebucoreVideoFormatBase::havevideoBitRate() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoBitRate));
}

uint64_t ebucoreVideoFormatBase::getvideoBitRate() const
{
    return getUInt64Item(&MXF_ITEM_K(ebucoreVideoFormat, videoBitRate));
}

bool ebucoreVideoFormatBase::havevideoMaxBitRate() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoMaxBitRate));
}

uint64_t ebucoreVideoFormatBase::getvideoMaxBitRate() const
{
    return getUInt64Item(&MXF_ITEM_K(ebucoreVideoFormat, videoMaxBitRate));
}

bool ebucoreVideoFormatBase::havevideoBitRateMode() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoBitRateMode));
}

std::string ebucoreVideoFormatBase::getvideoBitRateMode() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreVideoFormat, videoBitRateMode));
}

bool ebucoreVideoFormatBase::havevideoSamplingFormat() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoSamplingFormat));
}

std::string ebucoreVideoFormatBase::getvideoSamplingFormat() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreVideoFormat, videoSamplingFormat));
}

bool ebucoreVideoFormatBase::havevideoScanningOrder() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoScanningOrder));
}

std::string ebucoreVideoFormatBase::getvideoScanningOrder() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreVideoFormat, videoScanningOrder));
}

bool ebucoreVideoFormatBase::havevideoActiveLines() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoActiveLines));
}

uint64_t ebucoreVideoFormatBase::getvideoActiveLines() const
{
    return getUInt64Item(&MXF_ITEM_K(ebucoreVideoFormat, videoActiveLines));
}

bool ebucoreVideoFormatBase::havevideoNoiseFilterFlag() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoNoiseFilterFlag));
}

bool ebucoreVideoFormatBase::getvideoNoiseFilterFlag() const
{
    return getBooleanItem(&MXF_ITEM_K(ebucoreVideoFormat, videoNoiseFilterFlag));
}

bool ebucoreVideoFormatBase::havevideo3DFlag() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, video3DFlag));
}

bool ebucoreVideoFormatBase::getvideo3DFlag() const
{
    return getBooleanItem(&MXF_ITEM_K(ebucoreVideoFormat, video3DFlag));
}

bool ebucoreVideoFormatBase::havevideoAspectRatio() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoAspectRatio));
}

std::vector<ebucoreAspectRatio*> ebucoreVideoFormatBase::getvideoAspectRatio() const
{
    vector<ebucoreAspectRatio*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoAspectRatio)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreAspectRatio*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreAspectRatio*>(iter->get()));
    }
    return result;
}

bool ebucoreVideoFormatBase::havevideoFrameRate() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoFrameRate));
}

mxfRational ebucoreVideoFormatBase::getvideoFrameRate() const
{
    return getRationalItem(&MXF_ITEM_K(ebucoreVideoFormat, videoFrameRate));
}

bool ebucoreVideoFormatBase::havevideoHeight() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoHeight));
}

ebucoreHeight* ebucoreVideoFormatBase::getvideoHeight() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreVideoFormat, videoHeight)));
    MXFPP_CHECK(dynamic_cast<ebucoreHeight*>(obj.get()) != 0);
    return dynamic_cast<ebucoreHeight*>(obj.release());
}

bool ebucoreVideoFormatBase::havevideoWidth() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoWidth));
}

ebucoreWidth* ebucoreVideoFormatBase::getvideoWidth() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreVideoFormat, videoWidth)));
    MXFPP_CHECK(dynamic_cast<ebucoreWidth*>(obj.get()) != 0);
    return dynamic_cast<ebucoreWidth*>(obj.release());
}

bool ebucoreVideoFormatBase::havevideoEncoding() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoEncoding));
}

ebucoreTypeGroup* ebucoreVideoFormatBase::getvideoEncoding() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreVideoFormat, videoEncoding)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreVideoFormatBase::havevideoCodec() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoCodec));
}

ebucoreCodec* ebucoreVideoFormatBase::getvideoCodec() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreVideoFormat, videoCodec)));
    MXFPP_CHECK(dynamic_cast<ebucoreCodec*>(obj.get()) != 0);
    return dynamic_cast<ebucoreCodec*>(obj.release());
}

bool ebucoreVideoFormatBase::havevideoTrack() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTrack));
}

std::vector<ebucoreTrack*> ebucoreVideoFormatBase::getvideoTrack() const
{
    vector<ebucoreTrack*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTrack)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTrack*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTrack*>(iter->get()));
    }
    return result;
}

bool ebucoreVideoFormatBase::havevideoTechnicalAttributeString() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeString));
}

std::vector<ebucoreTechnicalAttributeString*> ebucoreVideoFormatBase::getvideoTechnicalAttributeString() const
{
    vector<ebucoreTechnicalAttributeString*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeString)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeString*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeString*>(iter->get()));
    }
    return result;
}

bool ebucoreVideoFormatBase::havevideoTechnicalAttributeInt8() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt8));
}

std::vector<ebucoreTechnicalAttributeInt8*> ebucoreVideoFormatBase::getvideoTechnicalAttributeInt8() const
{
    vector<ebucoreTechnicalAttributeInt8*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt8)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt8*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt8*>(iter->get()));
    }
    return result;
}

bool ebucoreVideoFormatBase::havevideoTechnicalAttributeInt16() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt16));
}

std::vector<ebucoreTechnicalAttributeInt16*> ebucoreVideoFormatBase::getvideoTechnicalAttributeInt16() const
{
    vector<ebucoreTechnicalAttributeInt16*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt16)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt16*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt16*>(iter->get()));
    }
    return result;
}

bool ebucoreVideoFormatBase::havevideoTechnicalAttributeInt32() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt32));
}

std::vector<ebucoreTechnicalAttributeInt32*> ebucoreVideoFormatBase::getvideoTechnicalAttributeInt32() const
{
    vector<ebucoreTechnicalAttributeInt32*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt32)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt32*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt32*>(iter->get()));
    }
    return result;
}

bool ebucoreVideoFormatBase::havevideoTechnicalAttributeInt64() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt64));
}

std::vector<ebucoreTechnicalAttributeInt64*> ebucoreVideoFormatBase::getvideoTechnicalAttributeInt64() const
{
    vector<ebucoreTechnicalAttributeInt64*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt64)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt64*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt64*>(iter->get()));
    }
    return result;
}

bool ebucoreVideoFormatBase::havevideoTechnicalAttributeUInt8() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt8));
}

std::vector<ebucoreTechnicalAttributeUInt8*> ebucoreVideoFormatBase::getvideoTechnicalAttributeUInt8() const
{
    vector<ebucoreTechnicalAttributeUInt8*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt8)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt8*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt8*>(iter->get()));
    }
    return result;
}

bool ebucoreVideoFormatBase::havevideoTechnicalAttributeUInt16() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt16));
}

std::vector<ebucoreTechnicalAttributeUInt16*> ebucoreVideoFormatBase::getvideoTechnicalAttributeUInt16() const
{
    vector<ebucoreTechnicalAttributeUInt16*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt16)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt16*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt16*>(iter->get()));
    }
    return result;
}

bool ebucoreVideoFormatBase::havevideoTechnicalAttributeUInt32() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt32));
}

std::vector<ebucoreTechnicalAttributeUInt32*> ebucoreVideoFormatBase::getvideoTechnicalAttributeUInt32() const
{
    vector<ebucoreTechnicalAttributeUInt32*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt32)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt32*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt32*>(iter->get()));
    }
    return result;
}

bool ebucoreVideoFormatBase::havevideoTechnicalAttributeUInt64() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt64));
}

std::vector<ebucoreTechnicalAttributeUInt64*> ebucoreVideoFormatBase::getvideoTechnicalAttributeUInt64() const
{
    vector<ebucoreTechnicalAttributeUInt64*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt64)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt64*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt64*>(iter->get()));
    }
    return result;
}

bool ebucoreVideoFormatBase::havevideoTechnicalAttributeFloat() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeFloat));
}

std::vector<ebucoreTechnicalAttributeFloat*> ebucoreVideoFormatBase::getvideoTechnicalAttributeFloat() const
{
    vector<ebucoreTechnicalAttributeFloat*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeFloat)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeFloat*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeFloat*>(iter->get()));
    }
    return result;
}

bool ebucoreVideoFormatBase::havevideoTechnicalAttributeRational() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeRational));
}

std::vector<ebucoreTechnicalAttributeRational*> ebucoreVideoFormatBase::getvideoTechnicalAttributeRational() const
{
    vector<ebucoreTechnicalAttributeRational*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeRational)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeRational*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeRational*>(iter->get()));
    }
    return result;
}

bool ebucoreVideoFormatBase::havevideoTechnicalAttributeAnyURI() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeAnyURI));
}

std::vector<ebucoreTechnicalAttributeAnyURI*> ebucoreVideoFormatBase::getvideoTechnicalAttributeAnyURI() const
{
    vector<ebucoreTechnicalAttributeAnyURI*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeAnyURI)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeAnyURI*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeAnyURI*>(iter->get()));
    }
    return result;
}

bool ebucoreVideoFormatBase::havevideoTechnicalAttributeBoolean() const
{
    return haveItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeBoolean));
}

std::vector<ebucoreTechnicalAttributeBoolean*> ebucoreVideoFormatBase::getvideoTechnicalAttributeBoolean() const
{
    vector<ebucoreTechnicalAttributeBoolean*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeBoolean)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeBoolean*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeBoolean*>(iter->get()));
    }
    return result;
}

void ebucoreVideoFormatBase::setvideoFormatID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreVideoFormat, videoFormatID), value);
}

void ebucoreVideoFormatBase::setvideoFormatName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreVideoFormat, videoFormatName), value);
}

void ebucoreVideoFormatBase::setvideoFormatDefinition(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreVideoFormat, videoFormatDefinition), value);
}

void ebucoreVideoFormatBase::setvideoBitRate(uint64_t value)
{
    setUInt64Item(&MXF_ITEM_K(ebucoreVideoFormat, videoBitRate), value);
}

void ebucoreVideoFormatBase::setvideoMaxBitRate(uint64_t value)
{
    setUInt64Item(&MXF_ITEM_K(ebucoreVideoFormat, videoMaxBitRate), value);
}

void ebucoreVideoFormatBase::setvideoBitRateMode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreVideoFormat, videoBitRateMode), value);
}

void ebucoreVideoFormatBase::setvideoSamplingFormat(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreVideoFormat, videoSamplingFormat), value);
}

void ebucoreVideoFormatBase::setvideoScanningOrder(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreVideoFormat, videoScanningOrder), value);
}

void ebucoreVideoFormatBase::setvideoActiveLines(uint64_t value)
{
    setUInt64Item(&MXF_ITEM_K(ebucoreVideoFormat, videoActiveLines), value);
}

void ebucoreVideoFormatBase::setvideoNoiseFilterFlag(bool value)
{
    setBooleanItem(&MXF_ITEM_K(ebucoreVideoFormat, videoNoiseFilterFlag), value);
}

void ebucoreVideoFormatBase::setvideo3DFlag(bool value)
{
    setBooleanItem(&MXF_ITEM_K(ebucoreVideoFormat, video3DFlag), value);
}

void ebucoreVideoFormatBase::setvideoAspectRatio(const std::vector<ebucoreAspectRatio*>& value)
{
    WrapObjectVectorIterator<ebucoreAspectRatio> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoAspectRatio), &iter);
}

void ebucoreVideoFormatBase::appendvideoAspectRatio(ebucoreAspectRatio* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoAspectRatio), value);
}

void ebucoreVideoFormatBase::setvideoFrameRate(mxfRational value)
{
    setRationalItem(&MXF_ITEM_K(ebucoreVideoFormat, videoFrameRate), value);
}

void ebucoreVideoFormatBase::setvideoHeight(ebucoreHeight* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreVideoFormat, videoHeight), value);
}

void ebucoreVideoFormatBase::setvideoWidth(ebucoreWidth* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreVideoFormat, videoWidth), value);
}

void ebucoreVideoFormatBase::setvideoEncoding(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreVideoFormat, videoEncoding), value);
}

void ebucoreVideoFormatBase::setvideoCodec(ebucoreCodec* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreVideoFormat, videoCodec), value);
}

void ebucoreVideoFormatBase::setvideoTrack(const std::vector<ebucoreTrack*>& value)
{
    WrapObjectVectorIterator<ebucoreTrack> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTrack), &iter);
}

void ebucoreVideoFormatBase::appendvideoTrack(ebucoreTrack* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTrack), value);
}

void ebucoreVideoFormatBase::setvideoTechnicalAttributeString(const std::vector<ebucoreTechnicalAttributeString*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeString> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeString), &iter);
}

void ebucoreVideoFormatBase::appendvideoTechnicalAttributeString(ebucoreTechnicalAttributeString* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeString), value);
}

void ebucoreVideoFormatBase::setvideoTechnicalAttributeInt8(const std::vector<ebucoreTechnicalAttributeInt8*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt8> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt8), &iter);
}

void ebucoreVideoFormatBase::appendvideoTechnicalAttributeInt8(ebucoreTechnicalAttributeInt8* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt8), value);
}

void ebucoreVideoFormatBase::setvideoTechnicalAttributeInt16(const std::vector<ebucoreTechnicalAttributeInt16*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt16> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt16), &iter);
}

void ebucoreVideoFormatBase::appendvideoTechnicalAttributeInt16(ebucoreTechnicalAttributeInt16* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt16), value);
}

void ebucoreVideoFormatBase::setvideoTechnicalAttributeInt32(const std::vector<ebucoreTechnicalAttributeInt32*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt32> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt32), &iter);
}

void ebucoreVideoFormatBase::appendvideoTechnicalAttributeInt32(ebucoreTechnicalAttributeInt32* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt32), value);
}

void ebucoreVideoFormatBase::setvideoTechnicalAttributeInt64(const std::vector<ebucoreTechnicalAttributeInt64*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt64> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt64), &iter);
}

void ebucoreVideoFormatBase::appendvideoTechnicalAttributeInt64(ebucoreTechnicalAttributeInt64* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt64), value);
}

void ebucoreVideoFormatBase::setvideoTechnicalAttributeUInt8(const std::vector<ebucoreTechnicalAttributeUInt8*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt8> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt8), &iter);
}

void ebucoreVideoFormatBase::appendvideoTechnicalAttributeUInt8(ebucoreTechnicalAttributeUInt8* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt8), value);
}

void ebucoreVideoFormatBase::setvideoTechnicalAttributeUInt16(const std::vector<ebucoreTechnicalAttributeUInt16*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt16> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt16), &iter);
}

void ebucoreVideoFormatBase::appendvideoTechnicalAttributeUInt16(ebucoreTechnicalAttributeUInt16* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt16), value);
}

void ebucoreVideoFormatBase::setvideoTechnicalAttributeUInt32(const std::vector<ebucoreTechnicalAttributeUInt32*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt32> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt32), &iter);
}

void ebucoreVideoFormatBase::appendvideoTechnicalAttributeUInt32(ebucoreTechnicalAttributeUInt32* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt32), value);
}

void ebucoreVideoFormatBase::setvideoTechnicalAttributeUInt64(const std::vector<ebucoreTechnicalAttributeUInt64*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt64> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt64), &iter);
}

void ebucoreVideoFormatBase::appendvideoTechnicalAttributeUInt64(ebucoreTechnicalAttributeUInt64* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt64), value);
}

void ebucoreVideoFormatBase::setvideoTechnicalAttributeFloat(const std::vector<ebucoreTechnicalAttributeFloat*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeFloat> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeFloat), &iter);
}

void ebucoreVideoFormatBase::appendvideoTechnicalAttributeFloat(ebucoreTechnicalAttributeFloat* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeFloat), value);
}

void ebucoreVideoFormatBase::setvideoTechnicalAttributeRational(const std::vector<ebucoreTechnicalAttributeRational*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeRational> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeRational), &iter);
}

void ebucoreVideoFormatBase::appendvideoTechnicalAttributeRational(ebucoreTechnicalAttributeRational* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeRational), value);
}

void ebucoreVideoFormatBase::setvideoTechnicalAttributeAnyURI(const std::vector<ebucoreTechnicalAttributeAnyURI*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeAnyURI> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeAnyURI), &iter);
}

void ebucoreVideoFormatBase::appendvideoTechnicalAttributeAnyURI(ebucoreTechnicalAttributeAnyURI* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeAnyURI), value);
}

void ebucoreVideoFormatBase::setvideoTechnicalAttributeBoolean(const std::vector<ebucoreTechnicalAttributeBoolean*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeBoolean> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeBoolean), &iter);
}

void ebucoreVideoFormatBase::appendvideoTechnicalAttributeBoolean(ebucoreTechnicalAttributeBoolean* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeBoolean), value);
}

