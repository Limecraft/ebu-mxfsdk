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

#ifndef __MXFPP_EBUCOREBASICRELATION_BASE_H__
#define __MXFPP_EBUCOREBASICRELATION_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_5 { namespace KLV
{


class ebucoreBasicRelationBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreBasicRelationBase>;
    static const mxfKey setKey;

public:
    ebucoreBasicRelationBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreBasicRelationBase();


   // getters

   bool haveisVersionOf() const;
   std::string getisVersionOf() const;
   bool havehasVersion() const;
   std::string gethasVersion() const;
   bool haveisReplacedBy() const;
   std::string getisReplacedBy() const;
   bool havereplaces() const;
   std::string getreplaces() const;
   bool haveisRequiredBy() const;
   std::string getisRequiredBy() const;
   bool haverequires() const;
   std::string getrequires() const;
   bool haveisPartOf() const;
   std::string getisPartOf() const;
   bool havehasPart() const;
   std::string gethasPart() const;
   bool haveisReferencedBy() const;
   std::string getisReferencedBy() const;
   bool havereferences() const;
   std::string getreferences() const;
   bool haveisFormatOf() const;
   std::string getisFormatOf() const;
   bool havehasFormat() const;
   std::string gethasFormat() const;
   bool haveisEpisodeOf() const;
   std::string getisEpisodeOf() const;
   bool haveisMemberOf() const;
   std::string getisMemberOf() const;


   // setters

   void setisVersionOf(std::string value);
   void sethasVersion(std::string value);
   void setisReplacedBy(std::string value);
   void setreplaces(std::string value);
   void setisRequiredBy(std::string value);
   void setrequires(std::string value);
   void setisPartOf(std::string value);
   void sethasPart(std::string value);
   void setisReferencedBy(std::string value);
   void setreferences(std::string value);
   void setisFormatOf(std::string value);
   void sethasFormat(std::string value);
   void setisEpisodeOf(std::string value);
   void setisMemberOf(std::string value);


protected:
    ebucoreBasicRelationBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
