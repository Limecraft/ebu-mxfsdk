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


const mxfKey ebucoreTitleBase::setKey = MXF_SET_K(ebucoreTitle);


ebucoreTitleBase::ebucoreTitleBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreTitleBase::ebucoreTitleBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreTitleBase::~ebucoreTitleBase()
{}


std::string ebucoreTitleBase::gettitleValue() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTitle, titleValue));
}

std::string ebucoreTitleBase::gettitleLanguage() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTitle, titleLanguage));
}

bool ebucoreTitleBase::havetitleAttributionDate() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTitle, titleAttributionDate));
}

mxfTimestamp ebucoreTitleBase::gettitleAttributionDate() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreTitle, titleAttributionDate));
}

bool ebucoreTitleBase::havetitleNote() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTitle, titleNote));
}

std::string ebucoreTitleBase::gettitleNote() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTitle, titleNote));
}

void ebucoreTitleBase::settitleValue(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTitle, titleValue), value);
}

void ebucoreTitleBase::settitleLanguage(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTitle, titleLanguage), value);
}

void ebucoreTitleBase::settitleAttributionDate(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreTitle, titleAttributionDate), value);
}

void ebucoreTitleBase::settitleNote(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTitle, titleNote), value);
}

