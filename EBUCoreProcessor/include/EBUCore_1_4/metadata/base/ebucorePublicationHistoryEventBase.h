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

#ifndef __MXFPP_EBUCOREPUBLICATIONHISTORYEVENT_BASE_H__
#define __MXFPP_EBUCOREPUBLICATIONHISTORYEVENT_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucorePublicationHistoryEventBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucorePublicationHistoryEventBase>;
    static const mxfKey setKey;

public:
    ebucorePublicationHistoryEventBase(HeaderMetadata *headerMetadata);
    virtual ~ebucorePublicationHistoryEventBase();


   // getters

   bool havefirstPublicationFlag() const;
   bool getfirstPublicationFlag() const;
   bool havepublicationDate() const;
   mxfTimestamp getpublicationDate() const;
   bool havepublicationTime() const;
   mxfTimestamp getpublicationTime() const;
   bool havepublicationService() const;
   std::string getpublicationService() const;
   bool havefreePublicationFlag() const;
   bool getfreePublicationFlag() const;
   bool havelivePublicationFlag() const;
   bool getlivePublicationFlag() const;
   bool havepublicationNote() const;
   std::string getpublicationNote() const;
   bool havepublicationFormatReference() const;
   ebucoreFormat* getpublicationFormatReference() const;
   bool havepublicationRightsReference() const;
   ebucoreRights* getpublicationRightsReference() const;
   bool havepublicationRegion() const;
   std::vector<ebucoreRegion*> getpublicationRegion() const;
   bool havepublicationMedium() const;
   ebucorePublicationMedium* getpublicationMedium() const;
   bool havepublicationChannel() const;
   ebucorePublicationChannel* getpublicationChannel() const;


   // setters

   void setfirstPublicationFlag(bool value);
   void setpublicationDate(mxfTimestamp value);
   void setpublicationTime(mxfTimestamp value);
   void setpublicationService(std::string value);
   void setfreePublicationFlag(bool value);
   void setlivePublicationFlag(bool value);
   void setpublicationNote(std::string value);
   void setpublicationFormatReference(ebucoreFormat* value);
   void setpublicationRightsReference(ebucoreRights* value);
   void setpublicationRegion(const std::vector<ebucoreRegion*>& value);
   void appendpublicationRegion(ebucoreRegion* value);
   void setpublicationMedium(ebucorePublicationMedium* value);
   void setpublicationChannel(ebucorePublicationChannel* value);


protected:
    ebucorePublicationHistoryEventBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
