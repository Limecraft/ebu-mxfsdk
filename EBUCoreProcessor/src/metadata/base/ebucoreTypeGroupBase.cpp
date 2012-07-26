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


const mxfKey ebucoreTypeGroupBase::setKey = MXF_SET_K(ebucoreTypeGroup);


ebucoreTypeGroupBase::ebucoreTypeGroupBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreTypeGroupBase::ebucoreTypeGroupBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreTypeGroupBase::~ebucoreTypeGroupBase()
{}


bool ebucoreTypeGroupBase::havetypeGroupThesaurus() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupThesaurus));
}

std::string ebucoreTypeGroupBase::gettypeGroupThesaurus() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupThesaurus));
}

bool ebucoreTypeGroupBase::havetypeGroupLabel() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupLabel));
}

std::string ebucoreTypeGroupBase::gettypeGroupLabel() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupLabel));
}

bool ebucoreTypeGroupBase::havetypeGroupLink() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupLink));
}

std::string ebucoreTypeGroupBase::gettypeGroupLink() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupLink));
}

bool ebucoreTypeGroupBase::havetypeGroupUL() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupUL));
}

mxfUL ebucoreTypeGroupBase::gettypeGroupUL() const
{
    return getULItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupUL));
}

bool ebucoreTypeGroupBase::havetypeGroupDefinition() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupDefinition));
}

std::string ebucoreTypeGroupBase::gettypeGroupDefinition() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupDefinition));
}

bool ebucoreTypeGroupBase::havetypeGroupLanguage() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupLanguage));
}

std::string ebucoreTypeGroupBase::gettypeGroupLanguage() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupLanguage));
}

void ebucoreTypeGroupBase::settypeGroupThesaurus(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupThesaurus), value);
}

void ebucoreTypeGroupBase::settypeGroupLabel(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupLabel), value);
}

void ebucoreTypeGroupBase::settypeGroupLink(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupLink), value);
}

void ebucoreTypeGroupBase::settypeGroupUL(mxfUL value)
{
    setULItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupUL), value);
}

void ebucoreTypeGroupBase::settypeGroupDefinition(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupDefinition), value);
}

void ebucoreTypeGroupBase::settypeGroupLanguage(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTypeGroup, typeGroupLanguage), value);
}

