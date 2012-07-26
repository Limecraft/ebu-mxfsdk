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

#ifndef __MXFPP_EBUCORECUSTOMRELATION_BASE_H__
#define __MXFPP_EBUCORECUSTOMRELATION_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUCore { namespace KLV
{


class ebucoreCustomRelationBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreCustomRelationBase>;
    static const mxfKey setKey;

public:
    ebucoreCustomRelationBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreCustomRelationBase();


   // getters

   bool haverelationByName() const;
   std::string getrelationByName() const;
   bool haverelationIdentifier() const;
   mxfUMID getrelationIdentifier() const;
   bool haverelationLink() const;
   std::string getrelationLink() const;
   bool haverunningOrderNumber() const;
   uint32_t getrunningOrderNumber() const;
   bool havetotalNumberOfGroupMembers() const;
   uint32_t gettotalNumberOfGroupMembers() const;
   bool haveorderedGroupFlag() const;
   bool getorderedGroupFlag() const;
   bool havecustomRelationTypeGroup() const;
   ebucoreTypeGroup* getcustomRelationTypeGroup() const;


   // setters

   void setrelationByName(std::string value);
   void setrelationIdentifier(mxfUMID value);
   void setrelationLink(std::string value);
   void setrunningOrderNumber(uint32_t value);
   void settotalNumberOfGroupMembers(uint32_t value);
   void setorderedGroupFlag(bool value);
   void setcustomRelationTypeGroup(ebucoreTypeGroup* value);


protected:
    ebucoreCustomRelationBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}};


#endif
