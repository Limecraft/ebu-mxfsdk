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

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
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
   std::string getcontactId() const;
   bool havefamilyName() const;
   std::string getfamilyName() const;
   bool havegivenName() const;
   std::string getgivenName() const;
   bool havesalutation() const;
   std::string getsalutation() const;
   bool havesuffix() const;
   std::string getsuffix() const;
   bool haveoccupation() const;
   std::string getoccupation() const;
   bool haveusername() const;
   std::string getusername() const;
   bool haveguestFlag() const;
   bool getguestFlag() const;
   bool havecontactName() const;
   std::vector<ebucoreCompoundName*> getcontactName() const;
   bool havecontactType() const;
   ebucoreTypeGroup* getcontactType() const;
   bool havecontactDetails() const;
   std::vector<ebucoreContactDetails*> getcontactDetails() const;
   bool havecontactRelatedContacts() const;
   std::vector<ebucoreEntity*> getcontactRelatedContacts() const;
   bool havestageName() const;
   std::vector<ebucoreTextualAnnotation*> getstageName() const;
   bool havegender() const;
   ebucoreTextualAnnotation* getgender() const;
   bool havecontactRelatedInformationLink() const;
   std::vector<ebucoreBasicLink*> getcontactRelatedInformationLink() const;
   bool haveotherGivenName() const;
   std::vector<ebucoreTextualAnnotation*> getotherGivenName() const;


   // setters

   void setcontactId(std::string value);
   void setfamilyName(std::string value);
   void setgivenName(std::string value);
   void setsalutation(std::string value);
   void setsuffix(std::string value);
   void setoccupation(std::string value);
   void setusername(std::string value);
   void setguestFlag(bool value);
   void setcontactName(const std::vector<ebucoreCompoundName*>& value);
   void appendcontactName(ebucoreCompoundName* value);
   void setcontactType(ebucoreTypeGroup* value);
   void setcontactDetails(const std::vector<ebucoreContactDetails*>& value);
   void appendcontactDetails(ebucoreContactDetails* value);
   void setcontactRelatedContacts(const std::vector<ebucoreEntity*>& value);
   void appendcontactRelatedContacts(ebucoreEntity* value);
   void setstageName(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendstageName(ebucoreTextualAnnotation* value);
   void setgender(ebucoreTextualAnnotation* value);
   void setcontactRelatedInformationLink(const std::vector<ebucoreBasicLink*>& value);
   void appendcontactRelatedInformationLink(ebucoreBasicLink* value);
   void setotherGivenName(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendotherGivenName(ebucoreTextualAnnotation* value);


protected:
    ebucoreContactBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
