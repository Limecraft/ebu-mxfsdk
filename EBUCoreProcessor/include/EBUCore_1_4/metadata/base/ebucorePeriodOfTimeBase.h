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
  
#ifndef __MXFPP_EBUCOREPERIODOFTIME_BASE_H__
#define __MXFPP_EBUCOREPERIODOFTIME_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucorePeriodOfTimeBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucorePeriodOfTimeBase>;
    static const mxfKey setKey;

public:
    ebucorePeriodOfTimeBase(HeaderMetadata *headerMetadata);
    virtual ~ebucorePeriodOfTimeBase();


   // getters

   bool haveperiodId() const;
   std::string getperiodId() const;
   bool haveperiodStartYear() const;
   mxfTimestamp getperiodStartYear() const;
   bool haveperiodStartDate() const;
   mxfTimestamp getperiodStartDate() const;
   bool haveperiodStartTime() const;
   mxfTimestamp getperiodStartTime() const;
   bool haveperiodEndYear() const;
   mxfTimestamp getperiodEndYear() const;
   bool haveperiodEndDate() const;
   mxfTimestamp getperiodEndDate() const;
   bool haveperiodEndTime() const;
   mxfTimestamp getperiodEndTime() const;
   bool haveperiodName() const;
   std::vector<ebucoreTextualAnnotation*> getperiodName() const;


   // setters

   void setperiodId(std::string value);
   void setperiodStartYear(mxfTimestamp value);
   void setperiodStartDate(mxfTimestamp value);
   void setperiodStartTime(mxfTimestamp value);
   void setperiodEndYear(mxfTimestamp value);
   void setperiodEndDate(mxfTimestamp value);
   void setperiodEndTime(mxfTimestamp value);
   void setperiodName(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendperiodName(ebucoreTextualAnnotation* value);


protected:
    ebucorePeriodOfTimeBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
