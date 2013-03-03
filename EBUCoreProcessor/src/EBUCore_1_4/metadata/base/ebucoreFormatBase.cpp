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


const mxfKey ebucoreFormatBase::setKey = MXF_SET_K(ebucoreFormat);


ebucoreFormatBase::ebucoreFormatBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreFormatBase::ebucoreFormatBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreFormatBase::~ebucoreFormatBase()
{}


bool ebucoreFormatBase::haveformatID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, formatID));
}

std::string ebucoreFormatBase::getformatID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreFormat, formatID));
}

bool ebucoreFormatBase::haveformatVersionID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, formatVersionID));
}

std::string ebucoreFormatBase::getformatVersionID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreFormat, formatVersionID));
}

bool ebucoreFormatBase::haveformatName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, formatName));
}

std::string ebucoreFormatBase::getformatName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreFormat, formatName));
}

bool ebucoreFormatBase::haveformatDefinition() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, formatDefinition));
}

std::string ebucoreFormatBase::getformatDefinition() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreFormat, formatDefinition));
}

bool ebucoreFormatBase::haveformatYearCreated() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, formatYearCreated));
}

mxfTimestamp ebucoreFormatBase::getformatYearCreated() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreFormat, formatYearCreated));
}

bool ebucoreFormatBase::haveformatDateCreated() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, formatDateCreated));
}

mxfTimestamp ebucoreFormatBase::getformatDateCreated() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreFormat, formatDateCreated));
}

bool ebucoreFormatBase::haveoverallDurationTimecode() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, overallDurationTimecode));
}

std::string ebucoreFormatBase::getoverallDurationTimecode() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreFormat, overallDurationTimecode));
}

bool ebucoreFormatBase::haveoverallDurationTimecodeDropframe() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, overallDurationTimecodeDropframe));
}

std::string ebucoreFormatBase::getoverallDurationTimecodeDropframe() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreFormat, overallDurationTimecodeDropframe));
}

bool ebucoreFormatBase::haveoverallDurationTime() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, overallDurationTime));
}

mxfRational ebucoreFormatBase::getoverallDurationTime() const
{
    return getRationalItem(&MXF_ITEM_K(ebucoreFormat, overallDurationTime));
}

bool ebucoreFormatBase::haveoverallDurationEditUnit() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, overallDurationEditUnit));
}

int64_t ebucoreFormatBase::getoverallDurationEditUnit() const
{
    return getLengthItem(&MXF_ITEM_K(ebucoreFormat, overallDurationEditUnit));
}

bool ebucoreFormatBase::haveeditRate() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, editRate));
}

ebucoreRational* ebucoreFormatBase::geteditRate() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreFormat, editRate)));
    MXFPP_CHECK(dynamic_cast<ebucoreRational*>(obj.get()) != 0);
    return dynamic_cast<ebucoreRational*>(obj.release());
}

bool ebucoreFormatBase::havecontainerFormat() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, containerFormat));
}

ebucoreFormatGroup* ebucoreFormatBase::getcontainerFormat() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreFormat, containerFormat)));
    MXFPP_CHECK(dynamic_cast<ebucoreFormatGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreFormatGroup*>(obj.release());
}

bool ebucoreFormatBase::havemedium() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, medium));
}

ebucoreMedium* ebucoreFormatBase::getmedium() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreFormat, medium)));
    MXFPP_CHECK(dynamic_cast<ebucoreMedium*>(obj.get()) != 0);
    return dynamic_cast<ebucoreMedium*>(obj.release());
}

bool ebucoreFormatBase::havepackageInfo() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, packageInfo));
}

ebucorePackageInfo* ebucoreFormatBase::getpackageInfo() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreFormat, packageInfo)));
    MXFPP_CHECK(dynamic_cast<ebucorePackageInfo*>(obj.get()) != 0);
    return dynamic_cast<ebucorePackageInfo*>(obj.release());
}

bool ebucoreFormatBase::havemimeType() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, mimeType));
}

ebucoreTypeGroup* ebucoreFormatBase::getmimeType() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreFormat, mimeType)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreFormatBase::havematerialAudioFormat() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, materialAudioFormat));
}

std::vector<ebucoreAudioFormat*> ebucoreFormatBase::getmaterialAudioFormat() const
{
    vector<ebucoreAudioFormat*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialAudioFormat)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreAudioFormat*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreAudioFormat*>(iter->get()));
    }
    return result;
}

bool ebucoreFormatBase::havematerialVideoFormat() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, materialVideoFormat));
}

std::vector<ebucoreVideoFormat*> ebucoreFormatBase::getmaterialVideoFormat() const
{
    vector<ebucoreVideoFormat*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialVideoFormat)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreVideoFormat*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreVideoFormat*>(iter->get()));
    }
    return result;
}

bool ebucoreFormatBase::havematerialImageFormat() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, materialImageFormat));
}

std::vector<ebucoreImageFormat*> ebucoreFormatBase::getmaterialImageFormat() const
{
    vector<ebucoreImageFormat*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialImageFormat)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreImageFormat*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreImageFormat*>(iter->get()));
    }
    return result;
}

bool ebucoreFormatBase::havematerialDataFormat() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, materialDataFormat));
}

std::vector<ebucoreDataFormat*> ebucoreFormatBase::getmaterialDataFormat() const
{
    vector<ebucoreDataFormat*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialDataFormat)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreDataFormat*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreDataFormat*>(iter->get()));
    }
    return result;
}

bool ebucoreFormatBase::havematerialSigningFormat() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, materialSigningFormat));
}

std::vector<ebucoreSigningFormat*> ebucoreFormatBase::getmaterialSigningFormat() const
{
    vector<ebucoreSigningFormat*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialSigningFormat)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreSigningFormat*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreSigningFormat*>(iter->get()));
    }
    return result;
}

bool ebucoreFormatBase::havematerialTechnicalAttributeString() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeString));
}

std::vector<ebucoreTechnicalAttributeString*> ebucoreFormatBase::getmaterialTechnicalAttributeString() const
{
    vector<ebucoreTechnicalAttributeString*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeString)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeString*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeString*>(iter->get()));
    }
    return result;
}

bool ebucoreFormatBase::havematerialTechnicalAttributeInt8() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt8));
}

std::vector<ebucoreTechnicalAttributeInt8*> ebucoreFormatBase::getmaterialTechnicalAttributeInt8() const
{
    vector<ebucoreTechnicalAttributeInt8*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt8)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt8*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt8*>(iter->get()));
    }
    return result;
}

bool ebucoreFormatBase::havematerialTechnicalAttributeInt16() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt16));
}

std::vector<ebucoreTechnicalAttributeInt16*> ebucoreFormatBase::getmaterialTechnicalAttributeInt16() const
{
    vector<ebucoreTechnicalAttributeInt16*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt16)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt16*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt16*>(iter->get()));
    }
    return result;
}

bool ebucoreFormatBase::havematerialTechnicalAttributeInt32() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt32));
}

std::vector<ebucoreTechnicalAttributeInt32*> ebucoreFormatBase::getmaterialTechnicalAttributeInt32() const
{
    vector<ebucoreTechnicalAttributeInt32*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt32)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt32*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt32*>(iter->get()));
    }
    return result;
}

bool ebucoreFormatBase::havematerialTechnicalAttributeInt64() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt64));
}

std::vector<ebucoreTechnicalAttributeInt64*> ebucoreFormatBase::getmaterialTechnicalAttributeInt64() const
{
    vector<ebucoreTechnicalAttributeInt64*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt64)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt64*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt64*>(iter->get()));
    }
    return result;
}

bool ebucoreFormatBase::havematerialTechnicalAttributeUInt8() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt8));
}

std::vector<ebucoreTechnicalAttributeUInt8*> ebucoreFormatBase::getmaterialTechnicalAttributeUInt8() const
{
    vector<ebucoreTechnicalAttributeUInt8*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt8)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt8*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt8*>(iter->get()));
    }
    return result;
}

bool ebucoreFormatBase::havematerialTechnicalAttributeUInt16() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt16));
}

std::vector<ebucoreTechnicalAttributeUInt16*> ebucoreFormatBase::getmaterialTechnicalAttributeUInt16() const
{
    vector<ebucoreTechnicalAttributeUInt16*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt16)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt16*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt16*>(iter->get()));
    }
    return result;
}

bool ebucoreFormatBase::havematerialTechnicalAttributeUInt32() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt32));
}

std::vector<ebucoreTechnicalAttributeUInt32*> ebucoreFormatBase::getmaterialTechnicalAttributeUInt32() const
{
    vector<ebucoreTechnicalAttributeUInt32*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt32)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt32*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt32*>(iter->get()));
    }
    return result;
}

bool ebucoreFormatBase::havematerialTechnicalAttributeUInt64() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt64));
}

std::vector<ebucoreTechnicalAttributeUInt64*> ebucoreFormatBase::getmaterialTechnicalAttributeUInt64() const
{
    vector<ebucoreTechnicalAttributeUInt64*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt64)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt64*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt64*>(iter->get()));
    }
    return result;
}

bool ebucoreFormatBase::havematerialTechnicalAttributeFloat() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeFloat));
}

std::vector<ebucoreTechnicalAttributeFloat*> ebucoreFormatBase::getmaterialTechnicalAttributeFloat() const
{
    vector<ebucoreTechnicalAttributeFloat*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeFloat)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeFloat*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeFloat*>(iter->get()));
    }
    return result;
}

bool ebucoreFormatBase::havematerialTechnicalAttributeRational() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeRational));
}

std::vector<ebucoreTechnicalAttributeRational*> ebucoreFormatBase::getmaterialTechnicalAttributeRational() const
{
    vector<ebucoreTechnicalAttributeRational*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeRational)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeRational*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeRational*>(iter->get()));
    }
    return result;
}

bool ebucoreFormatBase::havematerialTechnicalAttributeAnyURI() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeAnyURI));
}

std::vector<ebucoreTechnicalAttributeAnyURI*> ebucoreFormatBase::getmaterialTechnicalAttributeAnyURI() const
{
    vector<ebucoreTechnicalAttributeAnyURI*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeAnyURI)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeAnyURI*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeAnyURI*>(iter->get()));
    }
    return result;
}

bool ebucoreFormatBase::havematerialTechnicalAttributeBoolean() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeBoolean));
}

std::vector<ebucoreTechnicalAttributeBoolean*> ebucoreFormatBase::getmaterialTechnicalAttributeBoolean() const
{
    vector<ebucoreTechnicalAttributeBoolean*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeBoolean)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeBoolean*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeBoolean*>(iter->get()));
    }
    return result;
}

bool ebucoreFormatBase::haveformatModifiedDate() const
{
    return haveItem(&MXF_ITEM_K(ebucoreFormat, formatModifiedDate));
}

ebucoreDate* ebucoreFormatBase::getformatModifiedDate() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreFormat, formatModifiedDate)));
    MXFPP_CHECK(dynamic_cast<ebucoreDate*>(obj.get()) != 0);
    return dynamic_cast<ebucoreDate*>(obj.release());
}

void ebucoreFormatBase::setformatID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreFormat, formatID), value);
}

void ebucoreFormatBase::setformatVersionID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreFormat, formatVersionID), value);
}

void ebucoreFormatBase::setformatName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreFormat, formatName), value);
}

void ebucoreFormatBase::setformatDefinition(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreFormat, formatDefinition), value);
}

void ebucoreFormatBase::setformatYearCreated(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreFormat, formatYearCreated), value);
}

void ebucoreFormatBase::setformatDateCreated(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreFormat, formatDateCreated), value);
}

void ebucoreFormatBase::setoverallDurationTimecode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreFormat, overallDurationTimecode), value);
}

void ebucoreFormatBase::setoverallDurationTimecodeDropframe(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreFormat, overallDurationTimecodeDropframe), value);
}

void ebucoreFormatBase::setoverallDurationTime(mxfRational value)
{
    setRationalItem(&MXF_ITEM_K(ebucoreFormat, overallDurationTime), value);
}

void ebucoreFormatBase::setoverallDurationEditUnit(int64_t value)
{
    setLengthItem(&MXF_ITEM_K(ebucoreFormat, overallDurationEditUnit), value);
}

void ebucoreFormatBase::seteditRate(ebucoreRational* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreFormat, editRate), value);
}

void ebucoreFormatBase::setcontainerFormat(ebucoreFormatGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreFormat, containerFormat), value);
}

void ebucoreFormatBase::setmedium(ebucoreMedium* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreFormat, medium), value);
}

void ebucoreFormatBase::setpackageInfo(ebucorePackageInfo* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreFormat, packageInfo), value);
}

void ebucoreFormatBase::setmimeType(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreFormat, mimeType), value);
}

void ebucoreFormatBase::setmaterialAudioFormat(const std::vector<ebucoreAudioFormat*>& value)
{
    WrapObjectVectorIterator<ebucoreAudioFormat> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialAudioFormat), &iter);
}

void ebucoreFormatBase::appendmaterialAudioFormat(ebucoreAudioFormat* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialAudioFormat), value);
}

void ebucoreFormatBase::setmaterialVideoFormat(const std::vector<ebucoreVideoFormat*>& value)
{
    WrapObjectVectorIterator<ebucoreVideoFormat> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialVideoFormat), &iter);
}

void ebucoreFormatBase::appendmaterialVideoFormat(ebucoreVideoFormat* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialVideoFormat), value);
}

void ebucoreFormatBase::setmaterialImageFormat(const std::vector<ebucoreImageFormat*>& value)
{
    WrapObjectVectorIterator<ebucoreImageFormat> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialImageFormat), &iter);
}

void ebucoreFormatBase::appendmaterialImageFormat(ebucoreImageFormat* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialImageFormat), value);
}

void ebucoreFormatBase::setmaterialDataFormat(const std::vector<ebucoreDataFormat*>& value)
{
    WrapObjectVectorIterator<ebucoreDataFormat> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialDataFormat), &iter);
}

void ebucoreFormatBase::appendmaterialDataFormat(ebucoreDataFormat* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialDataFormat), value);
}

void ebucoreFormatBase::setmaterialSigningFormat(const std::vector<ebucoreSigningFormat*>& value)
{
    WrapObjectVectorIterator<ebucoreSigningFormat> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialSigningFormat), &iter);
}

void ebucoreFormatBase::appendmaterialSigningFormat(ebucoreSigningFormat* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialSigningFormat), value);
}

void ebucoreFormatBase::setmaterialTechnicalAttributeString(const std::vector<ebucoreTechnicalAttributeString*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeString> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeString), &iter);
}

void ebucoreFormatBase::appendmaterialTechnicalAttributeString(ebucoreTechnicalAttributeString* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeString), value);
}

void ebucoreFormatBase::setmaterialTechnicalAttributeInt8(const std::vector<ebucoreTechnicalAttributeInt8*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt8> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt8), &iter);
}

void ebucoreFormatBase::appendmaterialTechnicalAttributeInt8(ebucoreTechnicalAttributeInt8* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt8), value);
}

void ebucoreFormatBase::setmaterialTechnicalAttributeInt16(const std::vector<ebucoreTechnicalAttributeInt16*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt16> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt16), &iter);
}

void ebucoreFormatBase::appendmaterialTechnicalAttributeInt16(ebucoreTechnicalAttributeInt16* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt16), value);
}

void ebucoreFormatBase::setmaterialTechnicalAttributeInt32(const std::vector<ebucoreTechnicalAttributeInt32*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt32> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt32), &iter);
}

void ebucoreFormatBase::appendmaterialTechnicalAttributeInt32(ebucoreTechnicalAttributeInt32* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt32), value);
}

void ebucoreFormatBase::setmaterialTechnicalAttributeInt64(const std::vector<ebucoreTechnicalAttributeInt64*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt64> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt64), &iter);
}

void ebucoreFormatBase::appendmaterialTechnicalAttributeInt64(ebucoreTechnicalAttributeInt64* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt64), value);
}

void ebucoreFormatBase::setmaterialTechnicalAttributeUInt8(const std::vector<ebucoreTechnicalAttributeUInt8*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt8> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt8), &iter);
}

void ebucoreFormatBase::appendmaterialTechnicalAttributeUInt8(ebucoreTechnicalAttributeUInt8* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt8), value);
}

void ebucoreFormatBase::setmaterialTechnicalAttributeUInt16(const std::vector<ebucoreTechnicalAttributeUInt16*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt16> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt16), &iter);
}

void ebucoreFormatBase::appendmaterialTechnicalAttributeUInt16(ebucoreTechnicalAttributeUInt16* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt16), value);
}

void ebucoreFormatBase::setmaterialTechnicalAttributeUInt32(const std::vector<ebucoreTechnicalAttributeUInt32*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt32> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt32), &iter);
}

void ebucoreFormatBase::appendmaterialTechnicalAttributeUInt32(ebucoreTechnicalAttributeUInt32* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt32), value);
}

void ebucoreFormatBase::setmaterialTechnicalAttributeUInt64(const std::vector<ebucoreTechnicalAttributeUInt64*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt64> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt64), &iter);
}

void ebucoreFormatBase::appendmaterialTechnicalAttributeUInt64(ebucoreTechnicalAttributeUInt64* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt64), value);
}

void ebucoreFormatBase::setmaterialTechnicalAttributeFloat(const std::vector<ebucoreTechnicalAttributeFloat*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeFloat> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeFloat), &iter);
}

void ebucoreFormatBase::appendmaterialTechnicalAttributeFloat(ebucoreTechnicalAttributeFloat* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeFloat), value);
}

void ebucoreFormatBase::setmaterialTechnicalAttributeRational(const std::vector<ebucoreTechnicalAttributeRational*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeRational> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeRational), &iter);
}

void ebucoreFormatBase::appendmaterialTechnicalAttributeRational(ebucoreTechnicalAttributeRational* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeRational), value);
}

void ebucoreFormatBase::setmaterialTechnicalAttributeAnyURI(const std::vector<ebucoreTechnicalAttributeAnyURI*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeAnyURI> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeAnyURI), &iter);
}

void ebucoreFormatBase::appendmaterialTechnicalAttributeAnyURI(ebucoreTechnicalAttributeAnyURI* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeAnyURI), value);
}

void ebucoreFormatBase::setmaterialTechnicalAttributeBoolean(const std::vector<ebucoreTechnicalAttributeBoolean*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeBoolean> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeBoolean), &iter);
}

void ebucoreFormatBase::appendmaterialTechnicalAttributeBoolean(ebucoreTechnicalAttributeBoolean* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeBoolean), value);
}

void ebucoreFormatBase::setformatModifiedDate(ebucoreDate* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreFormat, formatModifiedDate), value);
}

