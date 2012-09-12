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
using namespace EBUSDK::EBUCore::KLV;


const mxfKey ebucoreAlternativeTitleBase::setKey = MXF_SET_K(ebucoreAlternativeTitle);


ebucoreAlternativeTitleBase::ebucoreAlternativeTitleBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreAlternativeTitleBase::ebucoreAlternativeTitleBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreAlternativeTitleBase::~ebucoreAlternativeTitleBase()
{}


bool ebucoreAlternativeTitleBase::havealternativeTitleAttributionDate() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleAttributionDate));
}

mxfTimestamp ebucoreAlternativeTitleBase::getalternativeTitleAttributionDate() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleAttributionDate));
}

bool ebucoreAlternativeTitleBase::havealternativeTitleNote() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleNote));
}

std::string ebucoreAlternativeTitleBase::getalternativeTitleNote() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleNote));
}

std::vector<ebucoreTextualAnnotation*> ebucoreAlternativeTitleBase::getalternativeTitleValue() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleValue)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

bool ebucoreAlternativeTitleBase::havealternativeTitleTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleTypeGroup));
}

ebucoreTypeGroup* ebucoreAlternativeTitleBase::getalternativeTitleTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreAlternativeTitleBase::havealternativeTitleStatusGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleStatusGroup));
}

ebucoreStatusGroup* ebucoreAlternativeTitleBase::getalternativeTitleStatusGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleStatusGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreStatusGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreStatusGroup*>(obj.release());
}

void ebucoreAlternativeTitleBase::setalternativeTitleAttributionDate(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleAttributionDate), value);
}

void ebucoreAlternativeTitleBase::setalternativeTitleNote(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleNote), value);
}

void ebucoreAlternativeTitleBase::setalternativeTitleValue(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleValue), &iter);
}

void ebucoreAlternativeTitleBase::appendalternativeTitleValue(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleValue), value);
}

void ebucoreAlternativeTitleBase::setalternativeTitleTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleTypeGroup), value);
}

void ebucoreAlternativeTitleBase::setalternativeTitleStatusGroup(ebucoreStatusGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleStatusGroup), value);
}

