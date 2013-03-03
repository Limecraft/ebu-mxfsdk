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


const mxfKey ebucoreContactDetailsBase::setKey = MXF_SET_K(ebucoreContactDetails);


ebucoreContactDetailsBase::ebucoreContactDetailsBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreContactDetailsBase::ebucoreContactDetailsBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreContactDetailsBase::~ebucoreContactDetailsBase()
{}


bool ebucoreContactDetailsBase::havewebAddress() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContactDetails, webAddress));
}

std::string ebucoreContactDetailsBase::getwebAddress() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreContactDetails, webAddress));
}

bool ebucoreContactDetailsBase::havetelephoneNumber() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContactDetails, telephoneNumber));
}

std::string ebucoreContactDetailsBase::gettelephoneNumber() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreContactDetails, telephoneNumber));
}

bool ebucoreContactDetailsBase::havemobileTelephoneNumber() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContactDetails, mobileTelephoneNumber));
}

std::string ebucoreContactDetailsBase::getmobileTelephoneNumber() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreContactDetails, mobileTelephoneNumber));
}

bool ebucoreContactDetailsBase::haveemailAddress() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContactDetails, emailAddress));
}

std::string ebucoreContactDetailsBase::getemailAddress() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreContactDetails, emailAddress));
}

bool ebucoreContactDetailsBase::havedetailsType() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContactDetails, detailsType));
}

ebucoreTypeGroup* ebucoreContactDetailsBase::getdetailsType() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreContactDetails, detailsType)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreContactDetailsBase::haveaddress() const
{
    return haveItem(&MXF_ITEM_K(ebucoreContactDetails, address));
}

ebucoreAddress* ebucoreContactDetailsBase::getaddress() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreContactDetails, address)));
    MXFPP_CHECK(dynamic_cast<ebucoreAddress*>(obj.get()) != 0);
    return dynamic_cast<ebucoreAddress*>(obj.release());
}

void ebucoreContactDetailsBase::setwebAddress(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContactDetails, webAddress), value);
}

void ebucoreContactDetailsBase::settelephoneNumber(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContactDetails, telephoneNumber), value);
}

void ebucoreContactDetailsBase::setmobileTelephoneNumber(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContactDetails, mobileTelephoneNumber), value);
}

void ebucoreContactDetailsBase::setemailAddress(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreContactDetails, emailAddress), value);
}

void ebucoreContactDetailsBase::setdetailsType(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreContactDetails, detailsType), value);
}

void ebucoreContactDetailsBase::setaddress(ebucoreAddress* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreContactDetails, address), value);
}

