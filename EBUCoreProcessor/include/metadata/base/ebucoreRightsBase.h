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

#ifndef __MXFPP_EBUCORERIGHTS_BASE_H__
#define __MXFPP_EBUCORERIGHTS_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>


namespace mxfpp
{


class ebucoreRightsBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreRightsBase>;
    static const mxfKey setKey;

public:
    ebucoreRightsBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreRightsBase();


   // getters

   bool haverightsId() const;
   std::string getrightsId() const;
   bool haverightsValue() const;
   std::string getrightsValue() const;
   bool haverightsLanguage() const;
   std::string getrightsLanguage() const;
   bool haverightsLink() const;
   std::string getrightsLink() const;
   bool haverightsClearanceFlag() const;
   bool getrightsClearanceFlag() const;
   bool haverightsAttributedID() const;
   std::string getrightsAttributedID() const;
   bool haverightsFormatIDRef() const;
   std::string getrightsFormatIDRef() const;
   bool haveexploitationIssues() const;
   std::string getexploitationIssues() const;
   bool haverightsCoverage() const;
   std::vector<ebucoreCoverage*> getrightsCoverage() const;
   bool haverightsHolderEntity() const;
   std::vector<ebucoreEntity*> getrightsHolderEntity() const;
   bool haverightsContacts() const;
   std::vector<ebucoreContact*> getrightsContacts() const;
   ebucoreTypeGroup* getrightsKindGroup() const;


   // setters

   void setrightsId(std::string value);
   void setrightsValue(std::string value);
   void setrightsLanguage(std::string value);
   void setrightsLink(std::string value);
   void setrightsClearanceFlag(bool value);
   void setrightsAttributedID(std::string value);
   void setrightsFormatIDRef(std::string value);
   void setexploitationIssues(std::string value);
   void setrightsCoverage(const std::vector<ebucoreCoverage*>& value);
   void appendrightsCoverage(ebucoreCoverage* value);
   void setrightsHolderEntity(const std::vector<ebucoreEntity*>& value);
   void appendrightsHolderEntity(ebucoreEntity* value);
   void setrightsContacts(const std::vector<ebucoreContact*>& value);
   void appendrightsContacts(ebucoreContact* value);
   void setrightsKindGroup(ebucoreTypeGroup* value);


protected:
    ebucoreRightsBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


};


#endif
