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

#ifndef __MXFPP_EBUCOREENTITY_BASE_H__
#define __MXFPP_EBUCOREENTITY_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUCore { namespace KLV
{


class ebucoreEntityBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreEntityBase>;
    static const mxfKey setKey;

public:
    ebucoreEntityBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreEntityBase();


   // getters

   mxfUUID getentityId() const;
   bool haveentityContact() const;
   std::vector<ebucoreContact*> getentityContact() const;
   bool haveentityOrganisation() const;
   std::vector<ebucoreOrganisation*> getentityOrganisation() const;
   bool haveentityRole() const;
   std::vector<ebucoreRole*> getentityRole() const;


   // setters

   void setentityId(mxfUUID value);
   void setentityContact(const std::vector<ebucoreContact*>& value);
   void appendentityContact(ebucoreContact* value);
   void setentityOrganisation(const std::vector<ebucoreOrganisation*>& value);
   void appendentityOrganisation(ebucoreOrganisation* value);
   void setentityRole(const std::vector<ebucoreRole*>& value);
   void appendentityRole(ebucoreRole* value);


protected:
    ebucoreEntityBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}};


#endif
