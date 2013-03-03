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
