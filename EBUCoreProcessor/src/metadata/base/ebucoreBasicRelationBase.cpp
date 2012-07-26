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


const mxfKey ebucoreBasicRelationBase::setKey = MXF_SET_K(ebucoreBasicRelation);


ebucoreBasicRelationBase::ebucoreBasicRelationBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreBasicRelationBase::ebucoreBasicRelationBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreBasicRelationBase::~ebucoreBasicRelationBase()
{}


mxfUMID ebucoreBasicRelationBase::getisVersionOf() const
{
    return getUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, isVersionOf));
}

mxfUMID ebucoreBasicRelationBase::gethasVersion() const
{
    return getUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, hasVersion));
}

mxfUMID ebucoreBasicRelationBase::getisReplacedBy() const
{
    return getUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, isReplacedBy));
}

mxfUMID ebucoreBasicRelationBase::getreplaces() const
{
    return getUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, replaces));
}

mxfUMID ebucoreBasicRelationBase::getisRequiredBy() const
{
    return getUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, isRequiredBy));
}

mxfUMID ebucoreBasicRelationBase::getrequires() const
{
    return getUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, requires));
}

mxfUMID ebucoreBasicRelationBase::getisPartOf() const
{
    return getUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, isPartOf));
}

mxfUMID ebucoreBasicRelationBase::gethasPart() const
{
    return getUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, hasPart));
}

mxfUMID ebucoreBasicRelationBase::getisReferencedBy() const
{
    return getUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, isReferencedBy));
}

mxfUMID ebucoreBasicRelationBase::getreferences() const
{
    return getUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, references));
}

mxfUMID ebucoreBasicRelationBase::getisFormatOf() const
{
    return getUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, isFormatOf));
}

mxfUMID ebucoreBasicRelationBase::gethasFormat() const
{
    return getUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, hasFormat));
}

mxfUMID ebucoreBasicRelationBase::getisEpisodeOf() const
{
    return getUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, isEpisodeOf));
}

mxfUMID ebucoreBasicRelationBase::getisMemberOf() const
{
    return getUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, isMemberOf));
}

void ebucoreBasicRelationBase::setisVersionOf(mxfUMID value)
{
    setUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, isVersionOf), value);
}

void ebucoreBasicRelationBase::sethasVersion(mxfUMID value)
{
    setUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, hasVersion), value);
}

void ebucoreBasicRelationBase::setisReplacedBy(mxfUMID value)
{
    setUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, isReplacedBy), value);
}

void ebucoreBasicRelationBase::setreplaces(mxfUMID value)
{
    setUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, replaces), value);
}

void ebucoreBasicRelationBase::setisRequiredBy(mxfUMID value)
{
    setUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, isRequiredBy), value);
}

void ebucoreBasicRelationBase::setrequires(mxfUMID value)
{
    setUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, requires), value);
}

void ebucoreBasicRelationBase::setisPartOf(mxfUMID value)
{
    setUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, isPartOf), value);
}

void ebucoreBasicRelationBase::sethasPart(mxfUMID value)
{
    setUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, hasPart), value);
}

void ebucoreBasicRelationBase::setisReferencedBy(mxfUMID value)
{
    setUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, isReferencedBy), value);
}

void ebucoreBasicRelationBase::setreferences(mxfUMID value)
{
    setUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, references), value);
}

void ebucoreBasicRelationBase::setisFormatOf(mxfUMID value)
{
    setUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, isFormatOf), value);
}

void ebucoreBasicRelationBase::sethasFormat(mxfUMID value)
{
    setUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, hasFormat), value);
}

void ebucoreBasicRelationBase::setisEpisodeOf(mxfUMID value)
{
    setUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, isEpisodeOf), value);
}

void ebucoreBasicRelationBase::setisMemberOf(mxfUMID value)
{
    setUMIDItem(&MXF_ITEM_K(ebucoreBasicRelation, isMemberOf), value);
}

