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


const mxfKey ebucorePeriodOfTimeBase::setKey = MXF_SET_K(ebucorePeriodOfTime);


ebucorePeriodOfTimeBase::ebucorePeriodOfTimeBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucorePeriodOfTimeBase::ebucorePeriodOfTimeBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucorePeriodOfTimeBase::~ebucorePeriodOfTimeBase()
{}


bool ebucorePeriodOfTimeBase::haveperiodId() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodId));
}

std::string ebucorePeriodOfTimeBase::getperiodId() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodId));
}

bool ebucorePeriodOfTimeBase::haveperiodName() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodName));
}

std::string ebucorePeriodOfTimeBase::getperiodName() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodName));
}

bool ebucorePeriodOfTimeBase::haveperiodStartYear() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartYear));
}

std::string ebucorePeriodOfTimeBase::getperiodStartYear() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartYear));
}

bool ebucorePeriodOfTimeBase::haveperiodStartDate() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartDate));
}

std::string ebucorePeriodOfTimeBase::getperiodStartDate() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartDate));
}

bool ebucorePeriodOfTimeBase::haveperiodStartTime() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartTime));
}

std::string ebucorePeriodOfTimeBase::getperiodStartTime() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartTime));
}

bool ebucorePeriodOfTimeBase::haveperiodEndYear() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndYear));
}

std::string ebucorePeriodOfTimeBase::getperiodEndYear() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndYear));
}

bool ebucorePeriodOfTimeBase::haveperiodEndDate() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndDate));
}

std::string ebucorePeriodOfTimeBase::getperiodEndDate() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndDate));
}

bool ebucorePeriodOfTimeBase::haveperiodEndTime() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndTime));
}

std::string ebucorePeriodOfTimeBase::getperiodEndTime() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndTime));
}

bool ebucorePeriodOfTimeBase::haveperiodKindGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodKindGroup));
}

ebucoreTypeGroup* ebucorePeriodOfTimeBase::getperiodKindGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodKindGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

void ebucorePeriodOfTimeBase::setperiodId(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodId), value);
}

void ebucorePeriodOfTimeBase::setperiodName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodName), value);
}

void ebucorePeriodOfTimeBase::setperiodStartYear(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartYear), value);
}

void ebucorePeriodOfTimeBase::setperiodStartDate(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartDate), value);
}

void ebucorePeriodOfTimeBase::setperiodStartTime(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartTime), value);
}

void ebucorePeriodOfTimeBase::setperiodEndYear(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndYear), value);
}

void ebucorePeriodOfTimeBase::setperiodEndDate(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndDate), value);
}

void ebucorePeriodOfTimeBase::setperiodEndTime(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndTime), value);
}

void ebucorePeriodOfTimeBase::setperiodKindGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodKindGroup), value);
}

