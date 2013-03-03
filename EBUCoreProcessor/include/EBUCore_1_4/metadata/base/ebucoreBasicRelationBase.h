 /*
  *    Copyright 2012-2013 European Broadcasting Union and Limecraft, NV.
  *
  *    Licensed under the Apache License, Version 2.0 (the "License");
  *    you may not use this file except in compliance with the License.
  *    You may obtain a copy of the License at
  *
  *       http://www.apache.org/licenses/LICENSE-2.0
  *
  *    Unless required by applicable law or agreed to in writing, software
  *    distributed under the License is distributed on an "AS IS" BASIS,
  *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  *    See the License for the specific language governing permissions and
  *    limitations under the License.
  *
  */
  
#ifndef __MXFPP_EBUCOREBASICRELATION_BASE_H__
#define __MXFPP_EBUCOREBASICRELATION_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
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
