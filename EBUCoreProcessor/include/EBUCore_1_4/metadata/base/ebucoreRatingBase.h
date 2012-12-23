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

#ifndef __MXFPP_EBUCORERATING_BASE_H__
#define __MXFPP_EBUCORERATING_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreRatingBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreRatingBase>;
    static const mxfKey setKey;

public:
    ebucoreRatingBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreRatingBase();


   // getters

   bool haveratingReason() const;
   std::string getratingReason() const;
   bool haveratingLinkToLogo() const;
   std::string getratingLinkToLogo() const;
   bool haveratingNotRatedFlag() const;
   bool getratingNotRatedFlag() const;
   bool haveratingAdultContentFlag() const;
   bool getratingAdultContentFlag() const;
   bool haveratingValue() const;
   std::vector<ebucoreTextualAnnotation*> getratingValue() const;
   bool haveratingScaleMinValue() const;
   std::vector<ebucoreTextualAnnotation*> getratingScaleMinValue() const;
   bool haveratingScaleMaxValue() const;
   std::vector<ebucoreTextualAnnotation*> getratingScaleMaxValue() const;
   bool haveratingTypeGroup() const;
   ebucoreTypeGroup* getratingTypeGroup() const;
   bool haveratingFormatGroup() const;
   ebucoreFormatGroup* getratingFormatGroup() const;
   bool haveratingProviderEntity() const;
   ebucoreEntity* getratingProviderEntity() const;
   bool haveratingRegion() const;
   ebucoreRegion* getratingRegion() const;


   // setters

   void setratingReason(std::string value);
   void setratingLinkToLogo(std::string value);
   void setratingNotRatedFlag(bool value);
   void setratingAdultContentFlag(bool value);
   void setratingValue(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendratingValue(ebucoreTextualAnnotation* value);
   void setratingScaleMinValue(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendratingScaleMinValue(ebucoreTextualAnnotation* value);
   void setratingScaleMaxValue(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendratingScaleMaxValue(ebucoreTextualAnnotation* value);
   void setratingTypeGroup(ebucoreTypeGroup* value);
   void setratingFormatGroup(ebucoreFormatGroup* value);
   void setratingProviderEntity(ebucoreEntity* value);
   void setratingRegion(ebucoreRegion* value);


protected:
    ebucoreRatingBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
