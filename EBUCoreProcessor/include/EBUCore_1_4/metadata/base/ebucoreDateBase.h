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

#ifndef __MXFPP_EBUCOREDATE_BASE_H__
#define __MXFPP_EBUCOREDATE_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreDateBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreDateBase>;
    static const mxfKey setKey;

public:
    ebucoreDateBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreDateBase();


   // getters

   bool havedateCreated() const;
   mxfTimestamp getdateCreated() const;
   bool haveyearCreated() const;
   mxfTimestamp getyearCreated() const;
   bool havedateIssued() const;
   mxfTimestamp getdateIssued() const;
   bool haveyearIssued() const;
   mxfTimestamp getyearIssued() const;
   bool havedateModified() const;
   mxfTimestamp getdateModified() const;
   bool haveyearModified() const;
   mxfTimestamp getyearModified() const;
   bool havedateDigitized() const;
   mxfTimestamp getdateDigitized() const;
   bool haveyearDigitized() const;
   mxfTimestamp getyearDigitized() const;
   bool havedateNote() const;
   std::string getdateNote() const;
   bool havealternativeDate() const;
   std::vector<ebucoreDateType*> getalternativeDate() const;


   // setters

   void setdateCreated(mxfTimestamp value);
   void setyearCreated(mxfTimestamp value);
   void setdateIssued(mxfTimestamp value);
   void setyearIssued(mxfTimestamp value);
   void setdateModified(mxfTimestamp value);
   void setyearModified(mxfTimestamp value);
   void setdateDigitized(mxfTimestamp value);
   void setyearDigitized(mxfTimestamp value);
   void setdateNote(std::string value);
   void setalternativeDate(const std::vector<ebucoreDateType*>& value);
   void appendalternativeDate(ebucoreDateType* value);


protected:
    ebucoreDateBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
