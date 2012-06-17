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


namespace mxfpp
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

   mxfUMID getisVersionOf() const;
   mxfUMID gethasVersion() const;
   mxfUMID getisReplacedBy() const;
   mxfUMID getreplaces() const;
   mxfUMID getisRequiredBy() const;
   mxfUMID getrequires() const;
   mxfUMID getisPartOf() const;
   mxfUMID gethasPart() const;
   mxfUMID getisReferencedBy() const;
   mxfUMID getreferences() const;
   mxfUMID getisFormatOf() const;
   mxfUMID gethasFormat() const;
   mxfUMID getisEpisodeOf() const;
   mxfUMID getisMemberOf() const;


   // setters

   void setisVersionOf(mxfUMID value);
   void sethasVersion(mxfUMID value);
   void setisReplacedBy(mxfUMID value);
   void setreplaces(mxfUMID value);
   void setisRequiredBy(mxfUMID value);
   void setrequires(mxfUMID value);
   void setisPartOf(mxfUMID value);
   void sethasPart(mxfUMID value);
   void setisReferencedBy(mxfUMID value);
   void setreferences(mxfUMID value);
   void setisFormatOf(mxfUMID value);
   void sethasFormat(mxfUMID value);
   void setisEpisodeOf(mxfUMID value);
   void setisMemberOf(mxfUMID value);


protected:
    ebucoreBasicRelationBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


};


#endif
