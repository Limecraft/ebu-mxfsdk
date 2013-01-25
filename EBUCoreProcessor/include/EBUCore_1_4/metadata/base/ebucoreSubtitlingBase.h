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

#ifndef __MXFPP_EBUCORESUBTITLING_BASE_H__
#define __MXFPP_EBUCORESUBTITLING_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreSubtitlingBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreSubtitlingBase>;
    static const mxfKey setKey;

public:
    ebucoreSubtitlingBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreSubtitlingBase();


   // getters

   bool havesubtitlingFormatID() const;
   std::string getsubtitlingFormatID() const;
   bool havesubtitlingFormatName() const;
   std::string getsubtitlingFormatName() const;
   bool havesubtitlingSourceUri() const;
   std::string getsubtitlingSourceUri() const;
   bool havesubtitlingTrackID() const;
   std::string getsubtitlingTrackID() const;
   bool havesubtitlingTrackName() const;
   std::string getsubtitlingTrackName() const;
   bool havesubtitlingLanguageCode() const;
   std::string getsubtitlingLanguageCode() const;
   bool havesubtitlingTypeGroup() const;
   ebucoreTypeGroup* getsubtitlingTypeGroup() const;
   bool havesubtitlingFormatGroup() const;
   ebucoreFormatGroup* getsubtitlingFormatGroup() const;


   // setters

   void setsubtitlingFormatID(std::string value);
   void setsubtitlingFormatName(std::string value);
   void setsubtitlingSourceUri(std::string value);
   void setsubtitlingTrackID(std::string value);
   void setsubtitlingTrackName(std::string value);
   void setsubtitlingLanguageCode(std::string value);
   void setsubtitlingTypeGroup(ebucoreTypeGroup* value);
   void setsubtitlingFormatGroup(ebucoreFormatGroup* value);


protected:
    ebucoreSubtitlingBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
