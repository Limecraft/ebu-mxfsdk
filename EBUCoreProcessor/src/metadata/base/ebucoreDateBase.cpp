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


std::string ebucoreDateBase::getotherDate() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDate, otherDate));
}

std::string ebucoreDateBase::getotherYear() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDate, otherYear));
}

std::string ebucoreDateBase::getdateCreated() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDate, dateCreated));
}

bool ebucoreDateBase::haveyearCreated() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, yearCreated));
}

std::string ebucoreDateBase::getyearCreated() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDate, yearCreated));
}

std::string ebucoreDateBase::getdateIssued() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDate, dateIssued));
}

std::string ebucoreDateBase::getyearIssued() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDate, yearIssued));
}

std::string ebucoreDateBase::getdateModified() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDate, dateModified));
}

std::string ebucoreDateBase::getyearModified() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDate, yearModified));
}

std::string ebucoreDateBase::getdateDigitized() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDate, dateDigitized));
}

std::string ebucoreDateBase::getyearDigitized() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDate, yearDigitized));
}

ebucoreTypeGroup* ebucoreDateBase::getdateTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreDate, dateTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

void ebucoreDateBase::setotherDate(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDate, otherDate), value);
}

void ebucoreDateBase::setotherYear(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDate, otherYear), value);
}

void ebucoreDateBase::setdateCreated(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDate, dateCreated), value);
}

void ebucoreDateBase::setyearCreated(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDate, yearCreated), value);
}

void ebucoreDateBase::setdateIssued(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDate, dateIssued), value);
}

void ebucoreDateBase::setyearIssued(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDate, yearIssued), value);
}

void ebucoreDateBase::setdateModified(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDate, dateModified), value);
}

void ebucoreDateBase::setyearModified(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDate, yearModified), value);
}

void ebucoreDateBase::setdateDigitized(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDate, dateDigitized), value);
}

void ebucoreDateBase::setyearDigitized(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDate, yearDigitized), value);
}

void ebucoreDateBase::setdateTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreDate, dateTypeGroup), value);
}

