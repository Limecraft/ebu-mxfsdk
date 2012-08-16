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

mxfTimestamp ebucorePeriodOfTimeBase::getperiodStartYear() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartYear));
}

bool ebucorePeriodOfTimeBase::haveperiodStartDate() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartDate));
}

mxfTimestamp ebucorePeriodOfTimeBase::getperiodStartDate() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartDate));
}

bool ebucorePeriodOfTimeBase::haveperiodStartTime() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartTime));
}

mxfTimestamp ebucorePeriodOfTimeBase::getperiodStartTime() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartTime));
}

bool ebucorePeriodOfTimeBase::haveperiodEndYear() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndYear));
}

mxfTimestamp ebucorePeriodOfTimeBase::getperiodEndYear() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndYear));
}

bool ebucorePeriodOfTimeBase::haveperiodEndDate() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndDate));
}

mxfTimestamp ebucorePeriodOfTimeBase::getperiodEndDate() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndDate));
}

bool ebucorePeriodOfTimeBase::haveperiodEndTime() const
{
    return haveItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndTime));
}

mxfTimestamp ebucorePeriodOfTimeBase::getperiodEndTime() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndTime));
}

void ebucorePeriodOfTimeBase::setperiodId(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodId), value);
}

void ebucorePeriodOfTimeBase::setperiodName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodName), value);
}

void ebucorePeriodOfTimeBase::setperiodStartYear(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartYear), value);
}

void ebucorePeriodOfTimeBase::setperiodStartDate(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartDate), value);
}

void ebucorePeriodOfTimeBase::setperiodStartTime(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodStartTime), value);
}

void ebucorePeriodOfTimeBase::setperiodEndYear(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndYear), value);
}

void ebucorePeriodOfTimeBase::setperiodEndDate(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndDate), value);
}

void ebucorePeriodOfTimeBase::setperiodEndTime(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucorePeriodOfTime, periodEndTime), value);
}

