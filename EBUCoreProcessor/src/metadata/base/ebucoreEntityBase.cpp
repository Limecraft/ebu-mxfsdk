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


const mxfKey ebucoreEntityBase::setKey = MXF_SET_K(ebucoreEntity);


ebucoreEntityBase::ebucoreEntityBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreEntityBase::ebucoreEntityBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreEntityBase::~ebucoreEntityBase()
{}


mxfUUID ebucoreEntityBase::getentityId() const
{
    return getUUIDItem(&MXF_ITEM_K(ebucoreEntity, entityId));
}

ebucoreContact* ebucoreEntityBase::getentityContact() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreEntity, entityContact)));
    MXFPP_CHECK(dynamic_cast<ebucoreContact*>(obj.get()) != 0);
    return dynamic_cast<ebucoreContact*>(obj.release());
}

ebucoreOrganisation* ebucoreEntityBase::getentityOrganisation() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreEntity, entityOrganisation)));
    MXFPP_CHECK(dynamic_cast<ebucoreOrganisation*>(obj.get()) != 0);
    return dynamic_cast<ebucoreOrganisation*>(obj.release());
}

ebucoreRole* ebucoreEntityBase::getentityRole() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreEntity, entityRole)));
    MXFPP_CHECK(dynamic_cast<ebucoreRole*>(obj.get()) != 0);
    return dynamic_cast<ebucoreRole*>(obj.release());
}

void ebucoreEntityBase::setentityId(mxfUUID value)
{
    setUUIDItem(&MXF_ITEM_K(ebucoreEntity, entityId), value);
}

void ebucoreEntityBase::setentityContact(ebucoreContact* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreEntity, entityContact), value);
}

void ebucoreEntityBase::setentityOrganisation(ebucoreOrganisation* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreEntity, entityOrganisation), value);
}

void ebucoreEntityBase::setentityRole(ebucoreRole* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreEntity, entityRole), value);
}

