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

   bool havepublicationEventName() const;
   std::string getpublicationEventName() const;
   bool havepublicationEventId() const;
   std::string getpublicationEventId() const;
   bool havefirstPublicationFlag() const;
   bool getfirstPublicationFlag() const;
   bool havepublicationDate() const;
   mxfTimestamp getpublicationDate() const;
   bool havepublicationTime() const;
   mxfTimestamp getpublicationTime() const;
   bool havefreePublicationFlag() const;
   bool getfreePublicationFlag() const;
   bool havelivePublicationFlag() const;
   bool getlivePublicationFlag() const;
   bool havepublicationNote() const;
   std::string getpublicationNote() const;
   bool havepublicationFormatReference() const;
   ebucoreFormat* getpublicationFormatReference() const;
   bool havepublicationRightsReference() const;
   std::vector<ebucoreRights*> getpublicationRightsReference() const;
   bool havepublicationRegion() const;
   std::vector<ebucoreRegion*> getpublicationRegion() const;
   bool havepublicationMedium() const;
   ebucorePublicationMedium* getpublicationMedium() const;
   bool havepublicationChannel() const;
   ebucorePublicationChannel* getpublicationChannel() const;
   bool havepublicationService() const;
   ebucorePublicationService* getpublicationService() const;


   // setters

   void setpublicationEventName(std::string value);
   void setpublicationEventId(std::string value);
   void setfirstPublicationFlag(bool value);
   void setpublicationDate(mxfTimestamp value);
   void setpublicationTime(mxfTimestamp value);
   void setfreePublicationFlag(bool value);
   void setlivePublicationFlag(bool value);
   void setpublicationNote(std::string value);
   void setpublicationFormatReference(ebucoreFormat* value);
   void setpublicationRightsReference(const std::vector<ebucoreRights*>& value);
   void appendpublicationRightsReference(ebucoreRights* value);
   void setpublicationRegion(const std::vector<ebucoreRegion*>& value);
   void appendpublicationRegion(ebucoreRegion* value);
   void setpublicationMedium(ebucorePublicationMedium* value);
   void setpublicationChannel(ebucorePublicationChannel* value);
   void setpublicationService(ebucorePublicationService* value);


protected:
    ebucorePublicationHistoryEventBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
