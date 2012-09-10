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


const mxfKey ebucoreContactDetailsBase::setKey = MXF_SET_K(ebucoreContactDetails);


ebucoreContactDetailsBase::ebucoreContactDetailsBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreContactDetailsBase::ebucoreContactDetailsBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreContactDetailsBase::~ebucoreContactDetailsBase()
{}


bool ebucoreContactDetailsBase::havewebAddress() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContactDetails, webAddress));
}

std::string ebucoreContactDetailsBase::getwebAddress() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreContactDetails, webAddress));
}

bool ebucoreContactDetailsBase::havetelephoneNumber() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContactDetails, telephoneNumber));
}

std::string ebucoreContactDetailsBase::gettelephoneNumber() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreContactDetails, telephoneNumber));
}

bool ebucoreContactDetailsBase::havemobileTelephoneNumber() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContactDetails, mobileTelephoneNumber));
}

std::string ebucoreContactDetailsBase::getmobileTelephoneNumber() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreContactDetails, mobileTelephoneNumber));
}

ebucoreTypeGroup* ebucoreContactDetailsBase::getdetailsType() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreContactDetails, detailsType)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreContactDetailsBase::haveaddress() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContactDetails, address));
}

ebucoreAddress* ebucoreContactDetailsBase::getaddress() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreContactDetails, address)));
    MXFPP_CHECK(dynamic_cast<ebucoreAddress*>(obj.get()) != 0);
    return dynamic_cast<ebucoreAddress*>(obj.release());
}

bool ebucoreContactDetailsBase::haveemailAddress() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContactDetails, emailAddress));
}

std::vector<ebucoreTextualAnnotation*> ebucoreContactDetailsBase::getemailAddress() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreContactDetails, emailAddress)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

void ebucoreContactDetailsBase::setwebAddress(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContactDetails, webAddress), value);
}

void ebucoreContactDetailsBase::settelephoneNumber(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContactDetails, telephoneNumber), value);
}

void ebucoreContactDetailsBase::setmobileTelephoneNumber(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContactDetails, mobileTelephoneNumber), value);
}

void ebucoreContactDetailsBase::setdetailsType(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreContactDetails, detailsType), value);
}

void ebucoreContactDetailsBase::setaddress(ebucoreAddress* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreContactDetails, address), value);
}

void ebucoreContactDetailsBase::setemailAddress(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreContactDetails, emailAddress), &iter);
}

void ebucoreContactDetailsBase::appendemailAddress(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreContactDetails, emailAddress), value);
}

