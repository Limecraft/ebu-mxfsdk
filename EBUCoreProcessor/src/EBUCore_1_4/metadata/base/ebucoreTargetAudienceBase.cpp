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


const mxfKey ebucoreTargetAudienceBase::setKey = MXF_SET_K(ebucoreTargetAudience);


ebucoreTargetAudienceBase::ebucoreTargetAudienceBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreTargetAudienceBase::ebucoreTargetAudienceBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreTargetAudienceBase::~ebucoreTargetAudienceBase()
{}


bool ebucoreTargetAudienceBase::havetargetAudienceReason() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceReason));
}

std::string ebucoreTargetAudienceBase::gettargetAudienceReason() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceReason));
}

bool ebucoreTargetAudienceBase::havetargetAudienceLinkToLogo() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceLinkToLogo));
}

std::string ebucoreTargetAudienceBase::gettargetAudienceLinkToLogo() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceLinkToLogo));
}

bool ebucoreTargetAudienceBase::havetargetAudienceNotRatedFlag() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceNotRatedFlag));
}

bool ebucoreTargetAudienceBase::gettargetAudienceNotRatedFlag() const
{
    return getBooleanItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceNotRatedFlag));
}

bool ebucoreTargetAudienceBase::havetargetAudienceAdultContentFlag() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceAdultContentFlag));
}

bool ebucoreTargetAudienceBase::gettargetAudienceAdultContentFlag() const
{
    return getBooleanItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceAdultContentFlag));
}

bool ebucoreTargetAudienceBase::havetargetAudienceTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceTypeGroup));
}

ebucoreTypeGroup* ebucoreTargetAudienceBase::gettargetAudienceTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreTargetAudienceBase::havetargetAudienceRegion() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceRegion));
}

std::vector<ebucoreRegion*> ebucoreTargetAudienceBase::gettargetAudienceRegion() const
{
    vector<ebucoreRegion*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceRegion)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreRegion*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreRegion*>(iter->get()));
    }
    return result;
}

void ebucoreTargetAudienceBase::settargetAudienceReason(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceReason), value);
}

void ebucoreTargetAudienceBase::settargetAudienceLinkToLogo(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceLinkToLogo), value);
}

void ebucoreTargetAudienceBase::settargetAudienceNotRatedFlag(bool value)
{
    setBooleanItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceNotRatedFlag), value);
}

void ebucoreTargetAudienceBase::settargetAudienceAdultContentFlag(bool value)
{
    setBooleanItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceAdultContentFlag), value);
}

void ebucoreTargetAudienceBase::settargetAudienceTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceTypeGroup), value);
}

void ebucoreTargetAudienceBase::settargetAudienceRegion(const std::vector<ebucoreRegion*>& value)
{
    WrapObjectVectorIterator<ebucoreRegion> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceRegion), &iter);
}

void ebucoreTargetAudienceBase::appendtargetAudienceRegion(ebucoreRegion* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreTargetAudience, targetAudienceRegion), value);
}

