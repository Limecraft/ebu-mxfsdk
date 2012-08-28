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


const mxfKey ebucoreTypeBase::setKey = MXF_SET_K(ebucoreType);


ebucoreTypeBase::ebucoreTypeBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreTypeBase::ebucoreTypeBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreTypeBase::~ebucoreTypeBase()
{}


bool ebucoreTypeBase::havetypeNote() const
{
    return haveItem(&MXF_ITEM_K(ebucoreType, typeNote));
}

std::string ebucoreTypeBase::gettypeNote() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreType, typeNote));
}

bool ebucoreTypeBase::havetypeValue() const
{
    return haveItem(&MXF_ITEM_K(ebucoreType, typeValue));
}

std::vector<textualAnnotation*> ebucoreTypeBase::gettypeValue() const
{
    vector<textualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, typeValue)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<textualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<textualAnnotation*>(iter->get()));
    }
    return result;
}

std::vector<ebucoreObjectType*> ebucoreTypeBase::getobjectType() const
{
    vector<ebucoreObjectType*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, objectType)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreObjectType*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreObjectType*>(iter->get()));
    }
    return result;
}

std::vector<ebucoreGenre*> ebucoreTypeBase::getgenre() const
{
    vector<ebucoreGenre*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, genre)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreGenre*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreGenre*>(iter->get()));
    }
    return result;
}

std::vector<ebucoreTargetAudience*> ebucoreTypeBase::gettargetAudience() const
{
    vector<ebucoreTargetAudience*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, targetAudience)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTargetAudience*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTargetAudience*>(iter->get()));
    }
    return result;
}

void ebucoreTypeBase::settypeNote(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreType, typeNote), value);
}

void ebucoreTypeBase::settypeValue(const std::vector<textualAnnotation*>& value)
{
    WrapObjectVectorIterator<textualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, typeValue), &iter);
}

void ebucoreTypeBase::appendtypeValue(textualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, typeValue), value);
}

void ebucoreTypeBase::setobjectType(const std::vector<ebucoreObjectType*>& value)
{
    WrapObjectVectorIterator<ebucoreObjectType> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, objectType), &iter);
}

void ebucoreTypeBase::appendobjectType(ebucoreObjectType* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, objectType), value);
}

void ebucoreTypeBase::setgenre(const std::vector<ebucoreGenre*>& value)
{
    WrapObjectVectorIterator<ebucoreGenre> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, genre), &iter);
}

void ebucoreTypeBase::appendgenre(ebucoreGenre* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, genre), value);
}

void ebucoreTypeBase::settargetAudience(const std::vector<ebucoreTargetAudience*>& value)
{
    WrapObjectVectorIterator<ebucoreTargetAudience> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, targetAudience), &iter);
}

void ebucoreTypeBase::appendtargetAudience(ebucoreTargetAudience* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreType, targetAudience), value);
}

