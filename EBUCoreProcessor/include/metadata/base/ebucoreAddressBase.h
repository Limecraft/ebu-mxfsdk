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

#ifndef __MXFPP_EBUCOREADDRESS_BASE_H__
#define __MXFPP_EBUCOREADDRESS_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUCore { namespace KLV
{


class ebucoreAddressBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreAddressBase>;
    static const mxfKey setKey;

public:
    ebucoreAddressBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreAddressBase();


   // getters

   bool haveaddressLines() const;
   std::vector<ebucoreAddressLine*> getaddressLines() const;
   bool havetownCity() const;
   std::string gettownCity() const;
   bool havecountyState() const;
   std::string getcountyState() const;
   bool havedeliveryCode() const;
   std::string getdeliveryCode() const;
   bool havecountryName() const;
   std::string getcountryName() const;
   bool havecountryCode() const;
   std::string getcountryCode() const;


   // setters

   void setaddressLines(const std::vector<ebucoreAddressLine*>& value);
   void appendaddressLines(ebucoreAddressLine* value);
   void settownCity(std::string value);
   void setcountyState(std::string value);
   void setdeliveryCode(std::string value);
   void setcountryName(std::string value);
   void setcountryCode(std::string value);


protected:
    ebucoreAddressBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}};


#endif
