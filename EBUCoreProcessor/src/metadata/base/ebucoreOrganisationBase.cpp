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


const mxfKey ebucoreOrganisationBase::setKey = MXF_SET_K(ebucoreOrganisation);


ebucoreOrganisationBase::ebucoreOrganisationBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreOrganisationBase::ebucoreOrganisationBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreOrganisationBase::~ebucoreOrganisationBase()
{}


mxfUUID ebucoreOrganisationBase::getorganisationId() const
{
    return getUUIDItem(&MXF_ITEM_K(ebucoreOrganisation, organisationId));
}

std::string ebucoreOrganisationBase::getorganisationName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreOrganisation, organisationName));
}

std::string ebucoreOrganisationBase::getorganisationCode() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreOrganisation, organisationCode));
}

std::string ebucoreOrganisationBase::getorganisationDepartment() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreOrganisation, organisationDepartment));
}

ebucoreTypeGroup* ebucoreOrganisationBase::getorganisationType() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreOrganisation, organisationType)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

std::vector<ebucoreContactDetails*> ebucoreOrganisationBase::getorganisationDetails() const
{
    vector<ebucoreContactDetails*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationDetails)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreContactDetails*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreContactDetails*>(iter->get()));
    }
    return result;
}

std::vector<ebucoreContact*> ebucoreOrganisationBase::getorganisationRelatedContacts() const
{
    vector<ebucoreContact*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationRelatedContacts)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreContact*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreContact*>(iter->get()));
    }
    return result;
}

void ebucoreOrganisationBase::setorganisationId(mxfUUID value)
{
    setUUIDItem(&MXF_ITEM_K(ebucoreOrganisation, organisationId), value);
}

void ebucoreOrganisationBase::setorganisationName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreOrganisation, organisationName), value);
}

void ebucoreOrganisationBase::setorganisationCode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreOrganisation, organisationCode), value);
}

void ebucoreOrganisationBase::setorganisationDepartment(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreOrganisation, organisationDepartment), value);
}

void ebucoreOrganisationBase::setorganisationType(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreOrganisation, organisationType), value);
}

void ebucoreOrganisationBase::setorganisationDetails(const std::vector<ebucoreContactDetails*>& value)
{
    WrapObjectVectorIterator<ebucoreContactDetails> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationDetails), &iter);
}

void ebucoreOrganisationBase::appendorganisationDetails(ebucoreContactDetails* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationDetails), value);
}

void ebucoreOrganisationBase::setorganisationRelatedContacts(const std::vector<ebucoreContact*>& value)
{
    WrapObjectVectorIterator<ebucoreContact> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationRelatedContacts), &iter);
}

void ebucoreOrganisationBase::appendorganisationRelatedContacts(ebucoreContact* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreOrganisation, organisationRelatedContacts), value);
}

