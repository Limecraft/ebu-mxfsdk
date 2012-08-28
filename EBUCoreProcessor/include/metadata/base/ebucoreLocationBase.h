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

#ifndef __MXFPP_EBUCORELOCATION_BASE_H__
#define __MXFPP_EBUCORELOCATION_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUCore { namespace KLV
{


class ebucoreLocationBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreLocationBase>;
    static const mxfKey setKey;

public:
    ebucoreLocationBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreLocationBase();


   // getters

   bool havelocationId() const;
   std::string getlocationId() const;
   bool havelocationName() const;
   std::string getlocationName() const;
   bool havelocationCode() const;
   std::string getlocationCode() const;
   ebucoreTypeGroup* getlocationTypeGroup() const;
   bool havecoordinateReference() const;
   XXX getcoordinateReference() const;


   // setters

   void setlocationId(std::string value);
   void setlocationName(std::string value);
   void setlocationCode(std::string value);
   void setlocationTypeGroup(ebucoreTypeGroup* value);
   void setcoordinateReference(XXX value);


protected:
    ebucoreLocationBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}};


#endif
