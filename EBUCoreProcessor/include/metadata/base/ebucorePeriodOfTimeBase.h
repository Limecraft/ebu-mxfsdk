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


namespace mxfpp
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
   std::string getperiodStartYear() const;
   bool haveperiodStartDate() const;
   std::string getperiodStartDate() const;
   bool haveperiodStartTime() const;
   std::string getperiodStartTime() const;
   bool haveperiodEndYear() const;
   std::string getperiodEndYear() const;
   bool haveperiodEndDate() const;
   std::string getperiodEndDate() const;
   bool haveperiodEndTime() const;
   std::string getperiodEndTime() const;
   bool haveperiodKindGroup() const;
   ebucoreTypeGroup* getperiodKindGroup() const;


   // setters

   void setperiodId(std::string value);
   void setperiodName(std::string value);
   void setperiodStartYear(std::string value);
   void setperiodStartDate(std::string value);
   void setperiodStartTime(std::string value);
   void setperiodEndYear(std::string value);
   void setperiodEndDate(std::string value);
   void setperiodEndTime(std::string value);
   void setperiodKindGroup(ebucoreTypeGroup* value);


protected:
    ebucorePeriodOfTimeBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


};


#endif
