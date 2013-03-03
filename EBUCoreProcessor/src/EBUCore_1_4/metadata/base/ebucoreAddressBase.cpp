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


const mxfKey ebucoreAddressBase::setKey = MXF_SET_K(ebucoreAddress);


ebucoreAddressBase::ebucoreAddressBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreAddressBase::ebucoreAddressBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreAddressBase::~ebucoreAddressBase()
{}


bool ebucoreAddressBase::havedeliveryCode() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAddress, deliveryCode));
}

std::string ebucoreAddressBase::getdeliveryCode() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreAddress, deliveryCode));
}

bool ebucoreAddressBase::havetownCity() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAddress, townCity));
}

std::vector<ebucoreTextualAnnotation*> ebucoreAddressBase::gettownCity() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, townCity)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

bool ebucoreAddressBase::havecountyState() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAddress, countyState));
}

std::vector<ebucoreTextualAnnotation*> ebucoreAddressBase::getcountyState() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, countyState)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

bool ebucoreAddressBase::havecountry() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAddress, country));
}

std::vector<ebucoreCountry*> ebucoreAddressBase::getcountry() const
{
    vector<ebucoreCountry*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, country)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreCountry*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreCountry*>(iter->get()));
    }
    return result;
}

bool ebucoreAddressBase::haveaddressLines() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAddress, addressLines));
}

std::vector<ebucoreTextualAnnotation*> ebucoreAddressBase::getaddressLines() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, addressLines)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

void ebucoreAddressBase::setdeliveryCode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreAddress, deliveryCode), value);
}

void ebucoreAddressBase::settownCity(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, townCity), &iter);
}

void ebucoreAddressBase::appendtownCity(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, townCity), value);
}

void ebucoreAddressBase::setcountyState(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, countyState), &iter);
}

void ebucoreAddressBase::appendcountyState(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, countyState), value);
}

void ebucoreAddressBase::setcountry(const std::vector<ebucoreCountry*>& value)
{
    WrapObjectVectorIterator<ebucoreCountry> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, country), &iter);
}

void ebucoreAddressBase::appendcountry(ebucoreCountry* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, country), value);
}

void ebucoreAddressBase::setaddressLines(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, addressLines), &iter);
}

void ebucoreAddressBase::appendaddressLines(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, addressLines), value);
}

