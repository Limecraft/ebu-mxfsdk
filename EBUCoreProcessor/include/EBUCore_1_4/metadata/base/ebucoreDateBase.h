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
  
#ifndef __MXFPP_EBUCOREDATE_BASE_H__
#define __MXFPP_EBUCOREDATE_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreDateBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreDateBase>;
    static const mxfKey setKey;

public:
    ebucoreDateBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreDateBase();


   // getters

   bool havedateCreated() const;
   mxfTimestamp getdateCreated() const;
   bool haveyearCreated() const;
   mxfTimestamp getyearCreated() const;
   bool havedateIssued() const;
   mxfTimestamp getdateIssued() const;
   bool haveyearIssued() const;
   mxfTimestamp getyearIssued() const;
   bool havedateModified() const;
   mxfTimestamp getdateModified() const;
   bool haveyearModified() const;
   mxfTimestamp getyearModified() const;
   bool havedateDigitized() const;
   mxfTimestamp getdateDigitized() const;
   bool haveyearDigitized() const;
   mxfTimestamp getyearDigitized() const;
   bool havedateReleased() const;
   mxfTimestamp getdateReleased() const;
   bool haveyearReleased() const;
   mxfTimestamp getyearReleased() const;
   bool havedateCopyrighted() const;
   mxfTimestamp getdateCopyrighted() const;
   bool haveyearCopyrighted() const;
   mxfTimestamp getyearCopyrighted() const;
   bool havedateNote() const;
   std::string getdateNote() const;
   bool havealternativeDate() const;
   std::vector<ebucoreDateType*> getalternativeDate() const;


   // setters

   void setdateCreated(mxfTimestamp value);
   void setyearCreated(mxfTimestamp value);
   void setdateIssued(mxfTimestamp value);
   void setyearIssued(mxfTimestamp value);
   void setdateModified(mxfTimestamp value);
   void setyearModified(mxfTimestamp value);
   void setdateDigitized(mxfTimestamp value);
   void setyearDigitized(mxfTimestamp value);
   void setdateReleased(mxfTimestamp value);
   void setyearReleased(mxfTimestamp value);
   void setdateCopyrighted(mxfTimestamp value);
   void setyearCopyrighted(mxfTimestamp value);
   void setdateNote(std::string value);
   void setalternativeDate(const std::vector<ebucoreDateType*>& value);
   void appendalternativeDate(ebucoreDateType* value);


protected:
    ebucoreDateBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
