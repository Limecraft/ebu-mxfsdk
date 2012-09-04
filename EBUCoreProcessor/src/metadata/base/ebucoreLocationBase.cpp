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


const mxfKey ebucoreLocationBase::setKey = MXF_SET_K(ebucoreLocation);


ebucoreLocationBase::ebucoreLocationBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreLocationBase::ebucoreLocationBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreLocationBase::~ebucoreLocationBase()
{}


bool ebucoreLocationBase::havelocationId() const
{
    return haveItem(&MXF_ITEM_K(ebucoreLocation, locationId));
}

std::string ebucoreLocationBase::getlocationId() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreLocation, locationId));
}

bool ebucoreLocationBase::havelocationName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreLocation, locationName));
}

std::string ebucoreLocationBase::getlocationName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreLocation, locationName));
}

bool ebucoreLocationBase::havelocationCode() const
{
    return haveItem(&MXF_ITEM_K(ebucoreLocation, locationCode));
}

std::string ebucoreLocationBase::getlocationCode() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreLocation, locationCode));
}

bool ebucoreLocationBase::havelocationNote() const
{
    return haveItem(&MXF_ITEM_K(ebucoreLocation, locationNote));
}

std::string ebucoreLocationBase::getlocationNote() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreLocation, locationNote));
}

ebucoreTypeGroup* ebucoreLocationBase::getlocationTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreLocation, locationTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreLocationBase::havecoordinateReference() const
{
    return haveItem(&MXF_ITEM_K(ebucoreLocation, coordinateReference));
}

ebucoreCoordinates* ebucoreLocationBase::getcoordinateReference() const
{
    auto_ptr<MetadataSet> obj(getWeakRefItem(&MXF_ITEM_K(ebucoreLocation, coordinateReference)));
    MXFPP_CHECK(dynamic_cast<ebucoreCoordinates*>(obj.get()) != 0);
    return dynamic_cast<ebucoreCoordinates*>(obj.release());
}

void ebucoreLocationBase::setlocationId(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreLocation, locationId), value);
}

void ebucoreLocationBase::setlocationName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreLocation, locationName), value);
}

void ebucoreLocationBase::setlocationCode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreLocation, locationCode), value);
}

void ebucoreLocationBase::setlocationNote(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreLocation, locationNote), value);
}

void ebucoreLocationBase::setlocationTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreLocation, locationTypeGroup), value);
}

void ebucoreLocationBase::setcoordinateReference(ebucoreCoordinates* value)
{
    setWeakRefItem(&MXF_ITEM_K(ebucoreLocation, coordinateReference), value);
}

