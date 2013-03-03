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
  
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <memory>

#include <libMXF++/MXF.h>
#include <EBUCore_1_4/metadata/EBUCoreDMS++.h>


using namespace std;
using namespace mxfpp;
using namespace EBUSDK::EBUCore::EBUCore_1_4::KLV;


const mxfKey ebucoreDateBase::setKey = MXF_SET_K(ebucoreDate);


ebucoreDateBase::ebucoreDateBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreDateBase::ebucoreDateBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreDateBase::~ebucoreDateBase()
{}


bool ebucoreDateBase::havedateCreated() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, dateCreated));
}

mxfTimestamp ebucoreDateBase::getdateCreated() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, dateCreated));
}

bool ebucoreDateBase::haveyearCreated() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, yearCreated));
}

mxfTimestamp ebucoreDateBase::getyearCreated() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, yearCreated));
}

bool ebucoreDateBase::havedateIssued() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, dateIssued));
}

mxfTimestamp ebucoreDateBase::getdateIssued() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, dateIssued));
}

bool ebucoreDateBase::haveyearIssued() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, yearIssued));
}

mxfTimestamp ebucoreDateBase::getyearIssued() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, yearIssued));
}

bool ebucoreDateBase::havedateModified() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, dateModified));
}

mxfTimestamp ebucoreDateBase::getdateModified() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, dateModified));
}

bool ebucoreDateBase::haveyearModified() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, yearModified));
}

mxfTimestamp ebucoreDateBase::getyearModified() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, yearModified));
}

bool ebucoreDateBase::havedateDigitized() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, dateDigitized));
}

mxfTimestamp ebucoreDateBase::getdateDigitized() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, dateDigitized));
}

bool ebucoreDateBase::haveyearDigitized() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, yearDigitized));
}

mxfTimestamp ebucoreDateBase::getyearDigitized() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, yearDigitized));
}

bool ebucoreDateBase::havedateReleased() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, dateReleased));
}

mxfTimestamp ebucoreDateBase::getdateReleased() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, dateReleased));
}

bool ebucoreDateBase::haveyearReleased() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, yearReleased));
}

mxfTimestamp ebucoreDateBase::getyearReleased() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, yearReleased));
}

bool ebucoreDateBase::havedateCopyrighted() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, dateCopyrighted));
}

mxfTimestamp ebucoreDateBase::getdateCopyrighted() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, dateCopyrighted));
}

bool ebucoreDateBase::haveyearCopyrighted() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, yearCopyrighted));
}

mxfTimestamp ebucoreDateBase::getyearCopyrighted() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucoreDate, yearCopyrighted));
}

bool ebucoreDateBase::havedateNote() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, dateNote));
}

std::string ebucoreDateBase::getdateNote() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDate, dateNote));
}

bool ebucoreDateBase::havealternativeDate() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDate, alternativeDate));
}

std::vector<ebucoreDateType*> ebucoreDateBase::getalternativeDate() const
{
    vector<ebucoreDateType*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreDate, alternativeDate)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreDateType*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreDateType*>(iter->get()));
    }
    return result;
}

void ebucoreDateBase::setdateCreated(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, dateCreated), value);
}

void ebucoreDateBase::setyearCreated(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, yearCreated), value);
}

void ebucoreDateBase::setdateIssued(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, dateIssued), value);
}

void ebucoreDateBase::setyearIssued(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, yearIssued), value);
}

void ebucoreDateBase::setdateModified(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, dateModified), value);
}

void ebucoreDateBase::setyearModified(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, yearModified), value);
}

void ebucoreDateBase::setdateDigitized(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, dateDigitized), value);
}

void ebucoreDateBase::setyearDigitized(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, yearDigitized), value);
}

void ebucoreDateBase::setdateReleased(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, dateReleased), value);
}

void ebucoreDateBase::setyearReleased(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, yearReleased), value);
}

void ebucoreDateBase::setdateCopyrighted(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, dateCopyrighted), value);
}

void ebucoreDateBase::setyearCopyrighted(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucoreDate, yearCopyrighted), value);
}

void ebucoreDateBase::setdateNote(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDate, dateNote), value);
}

void ebucoreDateBase::setalternativeDate(const std::vector<ebucoreDateType*>& value)
{
    WrapObjectVectorIterator<ebucoreDateType> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreDate, alternativeDate), &iter);
}

void ebucoreDateBase::appendalternativeDate(ebucoreDateType* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreDate, alternativeDate), value);
}

