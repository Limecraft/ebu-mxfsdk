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

#ifndef __MXFPP_EBUCORECONTACT_BASE_H__
#define __MXFPP_EBUCORECONTACT_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>


namespace mxfpp
{


class ebucoreContactBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreContactBase>;
    static const mxfKey setKey;

public:
    ebucoreContactBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreContactBase();


   // getters

   bool havecontactId() const;
   mxfUUID getcontactId() const;
   bool havefamilyName() const;
   std::string getfamilyName() const;
   std::string getgivenName() const;
   bool haveotherGivenName() const;
   std::string getotherGivenName() const;
   bool havesaluation() const;
   std::string getsaluation() const;
   bool havesuffix() const;
   std::string getsuffix() const;
   bool havestageName() const;
   std::string getstageName() const;
   bool haveoccupation() const;
   std::string getoccupation() const;
   ebucoreTypeGroup* getcontactType() const;
   std::vector<ebucoreContactDetails*> getcontactDetails() const;
   std::vector<ebucoreContact*> getcontactRelatedContacts() const;


   // setters

   void setcontactId(mxfUUID value);
   void setfamilyName(std::string value);
   void setgivenName(std::string value);
   void setotherGivenName(std::string value);
   void setsaluation(std::string value);
   void setsuffix(std::string value);
   void setstageName(std::string value);
   void setoccupation(std::string value);
   void setcontactType(ebucoreTypeGroup* value);
   void setcontactDetails(const std::vector<ebucoreContactDetails*>& value);
   void appendcontactDetails(ebucoreContactDetails* value);
   void setcontactRelatedContacts(const std::vector<ebucoreContact*>& value);
   void appendcontactRelatedContacts(ebucoreContact* value);


protected:
    ebucoreContactBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


};


#endif
