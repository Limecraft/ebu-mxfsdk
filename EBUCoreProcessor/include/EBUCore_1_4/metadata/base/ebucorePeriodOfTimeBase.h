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

#ifndef __MXFPP_EBUCOREPERIODOFTIME_BASE_H__
#define __MXFPP_EBUCOREPERIODOFTIME_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucorePeriodOfTimeBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucorePeriodOfTimeBase>;
    static const mxfKey setKey;

public:
    ebucorePeriodOfTimeBase(HeaderMetadata *headerMetadata);
    virtual ~ebucorePeriodOfTimeBase();


   // getters

   bool haveperiodId() const;
   std::string getperiodId() const;
   bool haveperiodName() const;
   std::string getperiodName() const;
   bool haveperiodStartYear() const;
   mxfTimestamp getperiodStartYear() const;
   bool haveperiodStartDate() const;
   mxfTimestamp getperiodStartDate() const;
   bool haveperiodStartTime() const;
   mxfTimestamp getperiodStartTime() const;
   bool haveperiodEndYear() const;
   mxfTimestamp getperiodEndYear() const;
   bool haveperiodEndDate() const;
   mxfTimestamp getperiodEndDate() const;
   bool haveperiodEndTime() const;
   mxfTimestamp getperiodEndTime() const;


   // setters

   void setperiodId(std::string value);
   void setperiodName(std::string value);
   void setperiodStartYear(mxfTimestamp value);
   void setperiodStartDate(mxfTimestamp value);
   void setperiodStartTime(mxfTimestamp value);
   void setperiodEndYear(mxfTimestamp value);
   void setperiodEndDate(mxfTimestamp value);
   void setperiodEndTime(mxfTimestamp value);


protected:
    ebucorePeriodOfTimeBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
