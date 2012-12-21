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
#include <EBUCore_1_4/metadata/EBUCoreDMS++.h>


using namespace std;
using namespace mxfpp;
using namespace EBUSDK::EBUCore::EBUCore_1_4::KLV;


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


bool ebucoreBasicRelationBase::haveisVersionOf() const
{
    return haveItem(&MXF_ITEM_K(ebucoreBasicRelation, isVersionOf));
}

std::string ebucoreBasicRelationBase::getisVersionOf() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreBasicRelation, isVersionOf));
}

bool ebucoreBasicRelationBase::havehasVersion() const
{
    return haveItem(&MXF_ITEM_K(ebucoreBasicRelation, hasVersion));
}

std::string ebucoreBasicRelationBase::gethasVersion() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreBasicRelation, hasVersion));
}

bool ebucoreBasicRelationBase::haveisReplacedBy() const
{
    return haveItem(&MXF_ITEM_K(ebucoreBasicRelation, isReplacedBy));
}

std::string ebucoreBasicRelationBase::getisReplacedBy() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreBasicRelation, isReplacedBy));
}

bool ebucoreBasicRelationBase::havereplaces() const
{
    return haveItem(&MXF_ITEM_K(ebucoreBasicRelation, replaces));
}

std::string ebucoreBasicRelationBase::getreplaces() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreBasicRelation, replaces));
}

bool ebucoreBasicRelationBase::haveisRequiredBy() const
{
    return haveItem(&MXF_ITEM_K(ebucoreBasicRelation, isRequiredBy));
}

std::string ebucoreBasicRelationBase::getisRequiredBy() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreBasicRelation, isRequiredBy));
}

bool ebucoreBasicRelationBase::haverequires() const
{
    return haveItem(&MXF_ITEM_K(ebucoreBasicRelation, requires));
}

std::string ebucoreBasicRelationBase::getrequires() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreBasicRelation, requires));
}

bool ebucoreBasicRelationBase::haveisPartOf() const
{
    return haveItem(&MXF_ITEM_K(ebucoreBasicRelation, isPartOf));
}

std::string ebucoreBasicRelationBase::getisPartOf() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreBasicRelation, isPartOf));
}

bool ebucoreBasicRelationBase::havehasPart() const
{
    return haveItem(&MXF_ITEM_K(ebucoreBasicRelation, hasPart));
}

std::string ebucoreBasicRelationBase::gethasPart() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreBasicRelation, hasPart));
}

bool ebucoreBasicRelationBase::haveisReferencedBy() const
{
    return haveItem(&MXF_ITEM_K(ebucoreBasicRelation, isReferencedBy));
}

std::string ebucoreBasicRelationBase::getisReferencedBy() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreBasicRelation, isReferencedBy));
}

bool ebucoreBasicRelationBase::havereferences() const
{
    return haveItem(&MXF_ITEM_K(ebucoreBasicRelation, references));
}

std::string ebucoreBasicRelationBase::getreferences() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreBasicRelation, references));
}

bool ebucoreBasicRelationBase::haveisFormatOf() const
{
    return haveItem(&MXF_ITEM_K(ebucoreBasicRelation, isFormatOf));
}

std::string ebucoreBasicRelationBase::getisFormatOf() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreBasicRelation, isFormatOf));
}

bool ebucoreBasicRelationBase::havehasFormat() const
{
    return haveItem(&MXF_ITEM_K(ebucoreBasicRelation, hasFormat));
}

std::string ebucoreBasicRelationBase::gethasFormat() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreBasicRelation, hasFormat));
}

bool ebucoreBasicRelationBase::haveisEpisodeOf() const
{
    return haveItem(&MXF_ITEM_K(ebucoreBasicRelation, isEpisodeOf));
}

std::string ebucoreBasicRelationBase::getisEpisodeOf() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreBasicRelation, isEpisodeOf));
}

bool ebucoreBasicRelationBase::haveisMemberOf() const
{
    return haveItem(&MXF_ITEM_K(ebucoreBasicRelation, isMemberOf));
}

std::string ebucoreBasicRelationBase::getisMemberOf() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreBasicRelation, isMemberOf));
}

void ebucoreBasicRelationBase::setisVersionOf(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreBasicRelation, isVersionOf), value);
}

void ebucoreBasicRelationBase::sethasVersion(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreBasicRelation, hasVersion), value);
}

void ebucoreBasicRelationBase::setisReplacedBy(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreBasicRelation, isReplacedBy), value);
}

void ebucoreBasicRelationBase::setreplaces(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreBasicRelation, replaces), value);
}

void ebucoreBasicRelationBase::setisRequiredBy(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreBasicRelation, isRequiredBy), value);
}

void ebucoreBasicRelationBase::setrequires(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreBasicRelation, requires), value);
}

void ebucoreBasicRelationBase::setisPartOf(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreBasicRelation, isPartOf), value);
}

void ebucoreBasicRelationBase::sethasPart(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreBasicRelation, hasPart), value);
}

void ebucoreBasicRelationBase::setisReferencedBy(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreBasicRelation, isReferencedBy), value);
}

void ebucoreBasicRelationBase::setreferences(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreBasicRelation, references), value);
}

void ebucoreBasicRelationBase::setisFormatOf(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreBasicRelation, isFormatOf), value);
}

void ebucoreBasicRelationBase::sethasFormat(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreBasicRelation, hasFormat), value);
}

void ebucoreBasicRelationBase::setisEpisodeOf(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreBasicRelation, isEpisodeOf), value);
}

void ebucoreBasicRelationBase::setisMemberOf(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreBasicRelation, isMemberOf), value);
}

