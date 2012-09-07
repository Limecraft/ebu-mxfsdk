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

#ifndef __MXFPP_EBUCOREPARTMETADATA_BASE_H__
#define __MXFPP_EBUCOREPARTMETADATA_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUCore { namespace KLV
{


class ebucorePartMetadataBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucorePartMetadataBase>;
    static const mxfKey setKey;

public:
    ebucorePartMetadataBase(HeaderMetadata *headerMetadata);
    virtual ~ebucorePartMetadataBase();


   // getters

   bool havepartId() const;
   std::string getpartId() const;
   bool havepartName() const;
   std::string getpartName() const;
   bool havepartDefinition() const;
   std::string getpartDefinition() const;
   bool havepartStartTimecode() const;
   std::string getpartStartTimecode() const;
   bool havepartStartTime() const;
   mxfRational getpartStartTime() const;
   bool havepartStartEditUnitNumber() const;
   int64_t getpartStartEditUnitNumber() const;
   bool havepartEndTimecode() const;
   std::string getpartEndTimecode() const;
   bool havepartEndTime() const;
   mxfRational getpartEndTime() const;
   bool havepartEndEditUnitNumber() const;
   int64_t getpartEndEditUnitNumber() const;
   bool havepartDurationTimecode() const;
   std::string getpartDurationTimecode() const;
   bool havepartDurationTime() const;
   mxfRational getpartDurationTime() const;
   bool havepartDurationEditUnitNumber() const;
   int64_t getpartDurationEditUnitNumber() const;
   bool havepartTypeGroup() const;
   ebucoreTypeGroup* getpartTypeGroup() const;
   bool havepartMeta() const;
   ebucoreCoreMetadata* getpartMeta() const;


   // setters

   void setpartId(std::string value);
   void setpartName(std::string value);
   void setpartDefinition(std::string value);
   void setpartStartTimecode(std::string value);
   void setpartStartTime(mxfRational value);
   void setpartStartEditUnitNumber(int64_t value);
   void setpartEndTimecode(std::string value);
   void setpartEndTime(mxfRational value);
   void setpartEndEditUnitNumber(int64_t value);
   void setpartDurationTimecode(std::string value);
   void setpartDurationTime(mxfRational value);
   void setpartDurationEditUnitNumber(int64_t value);
   void setpartTypeGroup(ebucoreTypeGroup* value);
   void setpartMeta(ebucoreCoreMetadata* value);


protected:
    ebucorePartMetadataBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}};


#endif
