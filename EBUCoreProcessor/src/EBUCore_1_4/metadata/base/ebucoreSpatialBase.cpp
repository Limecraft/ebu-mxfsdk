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
#include <EBUCore_1_5/metadata/EBUCoreDMS++.h>


using namespace std;
using namespace mxfpp;
using namespace EBUSDK::EBUCore::EBUCore_1_4::KLV;


const mxfKey ebucoreSpatialBase::setKey = MXF_SET_K(ebucoreSpatial);


ebucoreSpatialBase::ebucoreSpatialBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreSpatialBase::ebucoreSpatialBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreSpatialBase::~ebucoreSpatialBase()
{}


bool ebucoreSpatialBase::havelocation() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSpatial, location));
}

std::vector<ebucoreLocation*> ebucoreSpatialBase::getlocation() const
{
    vector<ebucoreLocation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreSpatial, location)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreLocation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreLocation*>(iter->get()));
    }
    return result;
}

bool ebucoreSpatialBase::havecoordinates() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSpatial, coordinates));
}

std::vector<ebucoreCoordinates*> ebucoreSpatialBase::getcoordinates() const
{
    vector<ebucoreCoordinates*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreSpatial, coordinates)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreCoordinates*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreCoordinates*>(iter->get()));
    }
    return result;
}

void ebucoreSpatialBase::setlocation(const std::vector<ebucoreLocation*>& value)
{
    WrapObjectVectorIterator<ebucoreLocation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreSpatial, location), &iter);
}

void ebucoreSpatialBase::appendlocation(ebucoreLocation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreSpatial, location), value);
}

void ebucoreSpatialBase::setcoordinates(const std::vector<ebucoreCoordinates*>& value)
{
    WrapObjectVectorIterator<ebucoreCoordinates> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreSpatial, coordinates), &iter);
}

void ebucoreSpatialBase::appendcoordinates(ebucoreCoordinates* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreSpatial, coordinates), value);
}

