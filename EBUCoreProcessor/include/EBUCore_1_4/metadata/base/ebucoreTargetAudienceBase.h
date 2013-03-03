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
  
#ifndef __MXFPP_EBUCORETARGETAUDIENCE_BASE_H__
#define __MXFPP_EBUCORETARGETAUDIENCE_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreTargetAudienceBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreTargetAudienceBase>;
    static const mxfKey setKey;

public:
    ebucoreTargetAudienceBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreTargetAudienceBase();


   // getters

   bool havetargetAudienceReason() const;
   std::string gettargetAudienceReason() const;
   bool havetargetAudienceLinkToLogo() const;
   std::string gettargetAudienceLinkToLogo() const;
   bool havetargetAudienceNotRatedFlag() const;
   bool gettargetAudienceNotRatedFlag() const;
   bool havetargetAudienceAdultContentFlag() const;
   bool gettargetAudienceAdultContentFlag() const;
   bool havetargetAudienceTypeGroup() const;
   ebucoreTypeGroup* gettargetAudienceTypeGroup() const;
   bool havetargetAudienceRegion() const;
   std::vector<ebucoreRegion*> gettargetAudienceRegion() const;


   // setters

   void settargetAudienceReason(std::string value);
   void settargetAudienceLinkToLogo(std::string value);
   void settargetAudienceNotRatedFlag(bool value);
   void settargetAudienceAdultContentFlag(bool value);
   void settargetAudienceTypeGroup(ebucoreTypeGroup* value);
   void settargetAudienceRegion(const std::vector<ebucoreRegion*>& value);
   void appendtargetAudienceRegion(ebucoreRegion* value);


protected:
    ebucoreTargetAudienceBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
