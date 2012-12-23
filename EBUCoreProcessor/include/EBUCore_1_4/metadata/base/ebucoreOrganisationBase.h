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

#ifndef __MXFPP_EBUCOREORGANISATION_BASE_H__
#define __MXFPP_EBUCOREORGANISATION_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreOrganisationBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreOrganisationBase>;
    static const mxfKey setKey;

public:
    ebucoreOrganisationBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreOrganisationBase();


   // getters

   bool haveorganisationId() const;
   std::string getorganisationId() const;
   bool haveorganisationCode() const;
   std::vector<ebucoreIdentifier*> getorganisationCode() const;
   bool haveorganisationRelatedInformationLink() const;
   std::vector<ebucoreBasicLink*> getorganisationRelatedInformationLink() const;
   bool haveorganisationName() const;
   std::vector<ebucoreCompoundName*> getorganisationName() const;
   bool haveorganisationDepartment() const;
   ebucoreOrganisationDepartment* getorganisationDepartment() const;
   bool haveorganisationType() const;
   ebucoreTypeGroup* getorganisationType() const;
   bool haveorganisationDetails() const;
   std::vector<ebucoreContactDetails*> getorganisationDetails() const;
   bool haveorganisationRelatedContacts() const;
   std::vector<ebucoreEntity*> getorganisationRelatedContacts() const;


   // setters

   void setorganisationId(std::string value);
   void setorganisationCode(const std::vector<ebucoreIdentifier*>& value);
   void appendorganisationCode(ebucoreIdentifier* value);
   void setorganisationRelatedInformationLink(const std::vector<ebucoreBasicLink*>& value);
   void appendorganisationRelatedInformationLink(ebucoreBasicLink* value);
   void setorganisationName(const std::vector<ebucoreCompoundName*>& value);
   void appendorganisationName(ebucoreCompoundName* value);
   void setorganisationDepartment(ebucoreOrganisationDepartment* value);
   void setorganisationType(ebucoreTypeGroup* value);
   void setorganisationDetails(const std::vector<ebucoreContactDetails*>& value);
   void appendorganisationDetails(ebucoreContactDetails* value);
   void setorganisationRelatedContacts(const std::vector<ebucoreEntity*>& value);
   void appendorganisationRelatedContacts(ebucoreEntity* value);


protected:
    ebucoreOrganisationBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
