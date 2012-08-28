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

#ifndef __MXFPP_EBUCORESUBJECT_BASE_H__
#define __MXFPP_EBUCORESUBJECT_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUCore { namespace KLV
{


class ebucoreSubjectBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreSubjectBase>;
    static const mxfKey setKey;

public:
    ebucoreSubjectBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreSubjectBase();


   // getters

   bool havesubjectCode() const;
   std::string getsubjectCode() const;
   bool havesubjectDefinition() const;
   std::string getsubjectDefinition() const;
   bool havesubjectNote() const;
   std::string getsubjectNote() const;
   std::vector<ebucoreTextualAnnotation*> getsubjectValue() const;
   ebucoreTypeGroup* getsubjectTypeGroup() const;
   bool havesubjectAttributorEntity() const;
   ebucoreEntity* getsubjectAttributorEntity() const;


   // setters

   void setsubjectCode(std::string value);
   void setsubjectDefinition(std::string value);
   void setsubjectNote(std::string value);
   void setsubjectValue(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendsubjectValue(ebucoreTextualAnnotation* value);
   void setsubjectTypeGroup(ebucoreTypeGroup* value);
   void setsubjectAttributorEntity(ebucoreEntity* value);


protected:
    ebucoreSubjectBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}};


#endif
