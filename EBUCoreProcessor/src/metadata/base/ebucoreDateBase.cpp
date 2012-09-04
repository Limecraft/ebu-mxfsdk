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


const mxfKey ebucoreDateBase::setKey = MXF_SET_K(ebucoreDate);


ebucoreDateBase::ebucoreDateBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreDateBase::ebucoreDateBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreDateBase::~ebucoreDateBase()
{}


bool ebucoreDateBase::havedateCreated() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, dateCreated));
}

mxfTimestamp ebucoreDateBase::getdateCreated() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, dateCreated));
}

bool ebucoreDateBase::haveyearCreated() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, yearCreated));
}

mxfTimestamp ebucoreDateBase::getyearCreated() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, yearCreated));
}

bool ebucoreDateBase::havedateIssued() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, dateIssued));
}

mxfTimestamp ebucoreDateBase::getdateIssued() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, dateIssued));
}

bool ebucoreDateBase::haveyearIssued() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, yearIssued));
}

mxfTimestamp ebucoreDateBase::getyearIssued() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, yearIssued));
}

bool ebucoreDateBase::havedateModified() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, dateModified));
}

mxfTimestamp ebucoreDateBase::getdateModified() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, dateModified));
}

bool ebucoreDateBase::haveyearModified() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, yearModified));
}

mxfTimestamp ebucoreDateBase::getyearModified() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, yearModified));
}

bool ebucoreDateBase::havedateDigitized() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, dateDigitized));
}

mxfTimestamp ebucoreDateBase::getdateDigitized() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, dateDigitized));
}

bool ebucoreDateBase::haveyearDigitized() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, yearDigitized));
}

mxfTimestamp ebucoreDateBase::getyearDigitized() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, yearDigitized));
}

bool ebucoreDateBase::havedateNote() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, dateNote));
}

std::string ebucoreDateBase::getdateNote() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDate, dateNote));
}

bool ebucoreDateBase::havealternativeDate() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, alternativeDate));
}

std::vector<ebucoreDateType*> ebucoreDateBase::getalternativeDate() const
{
    vector<ebucoreDateType*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreDate, alternativeDate)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreDateType*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreDateType*>(iter->get()));
    }
    return result;
}

void ebucoreDateBase::setdateCreated(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, dateCreated), value);
}

void ebucoreDateBase::setyearCreated(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, yearCreated), value);
}

void ebucoreDateBase::setdateIssued(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, dateIssued), value);
}

void ebucoreDateBase::setyearIssued(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, yearIssued), value);
}

void ebucoreDateBase::setdateModified(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, dateModified), value);
}

void ebucoreDateBase::setyearModified(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, yearModified), value);
}

void ebucoreDateBase::setdateDigitized(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, dateDigitized), value);
}

void ebucoreDateBase::setyearDigitized(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, yearDigitized), value);
}

void ebucoreDateBase::setdateNote(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDate, dateNote), value);
}

void ebucoreDateBase::setalternativeDate(const std::vector<ebucoreDateType*>& value)
{
    WrapObjectVectorIterator<ebucoreDateType> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreDate, alternativeDate), &iter);
}

void ebucoreDateBase::appendalternativeDate(ebucoreDateType* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreDate, alternativeDate), value);
}

