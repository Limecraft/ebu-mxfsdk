/*
 * Copyright (C) 2008, British Broadcasting Corporation
 * All Rights Reserved.
 *
 * Author: Philip de Nier
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the British Broadcasting Corporation nor the names
 *       of its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <memory>

#include <libMXF++/MXF.h>
#include <metadata/EBUCoreDMS++.h>


using namespace std;
using namespace mxfpp;
using namespace EBUCore::KLV;


const mxfKey ebucoreImageFormatBase::setKey = MXF_SET_K(ebucoreImageFormat);


ebucoreImageFormatBase::ebucoreImageFormatBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreImageFormatBase::ebucoreImageFormatBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreImageFormatBase::~ebucoreImageFormatBase()
{}


bool ebucoreImageFormatBase::haveimageFormatID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageFormatID));
}

std::string ebucoreImageFormatBase::getimageFormatID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreImageFormat, imageFormatID));
}

bool ebucoreImageFormatBase::haveimageFormatName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageFormatName));
}

std::string ebucoreImageFormatBase::getimageFormatName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreImageFormat, imageFormatName));
}

bool ebucoreImageFormatBase::haveimageFormatDefinition() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageFormatDefinition));
}

std::string ebucoreImageFormatBase::getimageFormatDefinition() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreImageFormat, imageFormatDefinition));
}

bool ebucoreImageFormatBase::haveimageOrientation() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageOrientation));
}

std::string ebucoreImageFormatBase::getimageOrientation() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreImageFormat, imageOrientation));
}

bool ebucoreImageFormatBase::haveimageAspectRatio() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageAspectRatio));
}

mxfRational ebucoreImageFormatBase::getimageAspectRatio() const
{
    return getRationalItem(&MXF_ITEM_K(ebucoreImageFormat, imageAspectRatio));
}

bool ebucoreImageFormatBase::haveimageEncoding() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageEncoding));
}

std::vector<ebucoreEncoding*> ebucoreImageFormatBase::getimageEncoding() const
{
    vector<ebucoreEncoding*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageEncoding)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreEncoding*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreEncoding*>(iter->get()));
    }
    return result;
}

bool ebucoreImageFormatBase::haveimageCodec() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageCodec));
}

ebucoreCodec* ebucoreImageFormatBase::getimageCodec() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreImageFormat, imageCodec)));
    MXFPP_CHECK(dynamic_cast<ebucoreCodec*>(obj.get()) != 0);
    return dynamic_cast<ebucoreCodec*>(obj.release());
}

bool ebucoreImageFormatBase::haveimageHeight() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageHeight));
}

ebucoreDimension* ebucoreImageFormatBase::getimageHeight() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreImageFormat, imageHeight)));
    MXFPP_CHECK(dynamic_cast<ebucoreDimension*>(obj.get()) != 0);
    return dynamic_cast<ebucoreDimension*>(obj.release());
}

bool ebucoreImageFormatBase::haveimageWidth() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageWidth));
}

ebucoreDimension* ebucoreImageFormatBase::getimageWidth() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreImageFormat, imageWidth)));
    MXFPP_CHECK(dynamic_cast<ebucoreDimension*>(obj.get()) != 0);
    return dynamic_cast<ebucoreDimension*>(obj.release());
}

bool ebucoreImageFormatBase::haveimageTechnicalAttributeString() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeString));
}

std::vector<ebucoreTechnicalAttributeString*> ebucoreImageFormatBase::getimageTechnicalAttributeString() const
{
    vector<ebucoreTechnicalAttributeString*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeString)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeString*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeString*>(iter->get()));
    }
    return result;
}

bool ebucoreImageFormatBase::haveimageTechnicalAttributeInt8() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt8));
}

std::vector<ebucoreTechnicalAttributeInt8*> ebucoreImageFormatBase::getimageTechnicalAttributeInt8() const
{
    vector<ebucoreTechnicalAttributeInt8*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt8)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt8*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt8*>(iter->get()));
    }
    return result;
}

bool ebucoreImageFormatBase::haveimageTechnicalAttributeInt16() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt16));
}

std::vector<ebucoreTechnicalAttributeInt16*> ebucoreImageFormatBase::getimageTechnicalAttributeInt16() const
{
    vector<ebucoreTechnicalAttributeInt16*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt16)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt16*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt16*>(iter->get()));
    }
    return result;
}

bool ebucoreImageFormatBase::haveimageTechnicalAttributeInt32() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt32));
}

std::vector<ebucoreTechnicalAttributeInt32*> ebucoreImageFormatBase::getimageTechnicalAttributeInt32() const
{
    vector<ebucoreTechnicalAttributeInt32*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt32)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt32*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt32*>(iter->get()));
    }
    return result;
}

bool ebucoreImageFormatBase::haveimageTechnicalAttributeInt64() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt64));
}

std::vector<ebucoreTechnicalAttributeInt64*> ebucoreImageFormatBase::getimageTechnicalAttributeInt64() const
{
    vector<ebucoreTechnicalAttributeInt64*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt64)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt64*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt64*>(iter->get()));
    }
    return result;
}

bool ebucoreImageFormatBase::haveimageTechnicalAttributeUInt8() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt8));
}

std::vector<ebucoreTechnicalAttributeUInt8*> ebucoreImageFormatBase::getimageTechnicalAttributeUInt8() const
{
    vector<ebucoreTechnicalAttributeUInt8*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt8)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt8*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt8*>(iter->get()));
    }
    return result;
}

bool ebucoreImageFormatBase::haveimageTechnicalAttributeUInt16() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt16));
}

std::vector<ebucoreTechnicalAttributeUInt16*> ebucoreImageFormatBase::getimageTechnicalAttributeUInt16() const
{
    vector<ebucoreTechnicalAttributeUInt16*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt16)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt16*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt16*>(iter->get()));
    }
    return result;
}

bool ebucoreImageFormatBase::haveimageTechnicalAttributeUInt32() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt32));
}

std::vector<ebucoreTechnicalAttributeUInt32*> ebucoreImageFormatBase::getimageTechnicalAttributeUInt32() const
{
    vector<ebucoreTechnicalAttributeUInt32*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt32)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt32*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt32*>(iter->get()));
    }
    return result;
}

bool ebucoreImageFormatBase::haveimageTechnicalAttributeUInt64() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt64));
}

std::vector<ebucoreTechnicalAttributeUInt64*> ebucoreImageFormatBase::getimageTechnicalAttributeUInt64() const
{
    vector<ebucoreTechnicalAttributeUInt64*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt64)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt64*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt64*>(iter->get()));
    }
    return result;
}

bool ebucoreImageFormatBase::haveimageTechnicalAttributeFloat() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeFloat));
}

std::vector<ebucoreTechnicalAttributeFloat*> ebucoreImageFormatBase::getimageTechnicalAttributeFloat() const
{
    vector<ebucoreTechnicalAttributeFloat*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeFloat)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeFloat*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeFloat*>(iter->get()));
    }
    return result;
}

bool ebucoreImageFormatBase::haveimageTechnicalAttributeRational() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeRational));
}

std::vector<ebucoreTechnicalAttributeRational*> ebucoreImageFormatBase::getimageTechnicalAttributeRational() const
{
    vector<ebucoreTechnicalAttributeRational*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeRational)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeRational*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeRational*>(iter->get()));
    }
    return result;
}

bool ebucoreImageFormatBase::haveimageTechnicalAttributeAnyURI() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeAnyURI));
}

std::vector<ebucoreTechnicalAttributeAnyURI*> ebucoreImageFormatBase::getimageTechnicalAttributeAnyURI() const
{
    vector<ebucoreTechnicalAttributeAnyURI*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeAnyURI)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeAnyURI*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeAnyURI*>(iter->get()));
    }
    return result;
}

bool ebucoreImageFormatBase::haveimageTechnicalAttributeBoolean() const
{
    return haveItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeBoolean));
}

std::vector<ebucoreTechnicalAttributeBoolean*> ebucoreImageFormatBase::getimageTechnicalAttributeBoolean() const
{
    vector<ebucoreTechnicalAttributeBoolean*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeBoolean)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeBoolean*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeBoolean*>(iter->get()));
    }
    return result;
}

void ebucoreImageFormatBase::setimageFormatID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreImageFormat, imageFormatID), value);
}

void ebucoreImageFormatBase::setimageFormatName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreImageFormat, imageFormatName), value);
}

void ebucoreImageFormatBase::setimageFormatDefinition(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreImageFormat, imageFormatDefinition), value);
}

void ebucoreImageFormatBase::setimageOrientation(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreImageFormat, imageOrientation), value);
}

void ebucoreImageFormatBase::setimageAspectRatio(mxfRational value)
{
    setRationalItem(&MXF_ITEM_K(ebucoreImageFormat, imageAspectRatio), value);
}

void ebucoreImageFormatBase::setimageEncoding(const std::vector<ebucoreEncoding*>& value)
{
    WrapObjectVectorIterator<ebucoreEncoding> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageEncoding), &iter);
}

void ebucoreImageFormatBase::appendimageEncoding(ebucoreEncoding* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageEncoding), value);
}

void ebucoreImageFormatBase::setimageCodec(ebucoreCodec* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreImageFormat, imageCodec), value);
}

void ebucoreImageFormatBase::setimageHeight(ebucoreDimension* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreImageFormat, imageHeight), value);
}

void ebucoreImageFormatBase::setimageWidth(ebucoreDimension* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreImageFormat, imageWidth), value);
}

void ebucoreImageFormatBase::setimageTechnicalAttributeString(const std::vector<ebucoreTechnicalAttributeString*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeString> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeString), &iter);
}

void ebucoreImageFormatBase::appendimageTechnicalAttributeString(ebucoreTechnicalAttributeString* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeString), value);
}

void ebucoreImageFormatBase::setimageTechnicalAttributeInt8(const std::vector<ebucoreTechnicalAttributeInt8*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt8> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt8), &iter);
}

void ebucoreImageFormatBase::appendimageTechnicalAttributeInt8(ebucoreTechnicalAttributeInt8* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt8), value);
}

void ebucoreImageFormatBase::setimageTechnicalAttributeInt16(const std::vector<ebucoreTechnicalAttributeInt16*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt16> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt16), &iter);
}

void ebucoreImageFormatBase::appendimageTechnicalAttributeInt16(ebucoreTechnicalAttributeInt16* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt16), value);
}

void ebucoreImageFormatBase::setimageTechnicalAttributeInt32(const std::vector<ebucoreTechnicalAttributeInt32*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt32> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt32), &iter);
}

void ebucoreImageFormatBase::appendimageTechnicalAttributeInt32(ebucoreTechnicalAttributeInt32* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt32), value);
}

void ebucoreImageFormatBase::setimageTechnicalAttributeInt64(const std::vector<ebucoreTechnicalAttributeInt64*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt64> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt64), &iter);
}

void ebucoreImageFormatBase::appendimageTechnicalAttributeInt64(ebucoreTechnicalAttributeInt64* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt64), value);
}

void ebucoreImageFormatBase::setimageTechnicalAttributeUInt8(const std::vector<ebucoreTechnicalAttributeUInt8*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt8> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt8), &iter);
}

void ebucoreImageFormatBase::appendimageTechnicalAttributeUInt8(ebucoreTechnicalAttributeUInt8* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt8), value);
}

void ebucoreImageFormatBase::setimageTechnicalAttributeUInt16(const std::vector<ebucoreTechnicalAttributeUInt16*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt16> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt16), &iter);
}

void ebucoreImageFormatBase::appendimageTechnicalAttributeUInt16(ebucoreTechnicalAttributeUInt16* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt16), value);
}

void ebucoreImageFormatBase::setimageTechnicalAttributeUInt32(const std::vector<ebucoreTechnicalAttributeUInt32*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt32> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt32), &iter);
}

void ebucoreImageFormatBase::appendimageTechnicalAttributeUInt32(ebucoreTechnicalAttributeUInt32* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt32), value);
}

void ebucoreImageFormatBase::setimageTechnicalAttributeUInt64(const std::vector<ebucoreTechnicalAttributeUInt64*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt64> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt64), &iter);
}

void ebucoreImageFormatBase::appendimageTechnicalAttributeUInt64(ebucoreTechnicalAttributeUInt64* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt64), value);
}

void ebucoreImageFormatBase::setimageTechnicalAttributeFloat(const std::vector<ebucoreTechnicalAttributeFloat*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeFloat> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeFloat), &iter);
}

void ebucoreImageFormatBase::appendimageTechnicalAttributeFloat(ebucoreTechnicalAttributeFloat* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeFloat), value);
}

void ebucoreImageFormatBase::setimageTechnicalAttributeRational(const std::vector<ebucoreTechnicalAttributeRational*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeRational> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeRational), &iter);
}

void ebucoreImageFormatBase::appendimageTechnicalAttributeRational(ebucoreTechnicalAttributeRational* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeRational), value);
}

void ebucoreImageFormatBase::setimageTechnicalAttributeAnyURI(const std::vector<ebucoreTechnicalAttributeAnyURI*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeAnyURI> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeAnyURI), &iter);
}

void ebucoreImageFormatBase::appendimageTechnicalAttributeAnyURI(ebucoreTechnicalAttributeAnyURI* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeAnyURI), value);
}

void ebucoreImageFormatBase::setimageTechnicalAttributeBoolean(const std::vector<ebucoreTechnicalAttributeBoolean*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeBoolean> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeBoolean), &iter);
}

void ebucoreImageFormatBase::appendimageTechnicalAttributeBoolean(ebucoreTechnicalAttributeBoolean* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeBoolean), value);
}

