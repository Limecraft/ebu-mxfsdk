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


const mxfKey ebucoreLocationBase::setKey = MXF_SET_K(ebucoreLocation);


ebucoreLocationBase::ebucoreLocationBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreLocationBase::ebucoreLocationBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreLocationBase::~ebucoreLocationBase()
{}


bool ebucoreLocationBase::havelocationId() const
{
    return haveItem(&MXF_ITEM_K(ebucoreLocation, locationId));
}

std::string ebucoreLocationBase::getlocationId() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreLocation, locationId));
}

bool ebucoreLocationBase::havelocationCode() const
{
    return haveItem(&MXF_ITEM_K(ebucoreLocation, locationCode));
}

std::string ebucoreLocationBase::getlocationCode() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreLocation, locationCode));
}

bool ebucoreLocationBase::havelocationDefinitionNote() const
{
    return haveItem(&MXF_ITEM_K(ebucoreLocation, locationDefinitionNote));
}

std::string ebucoreLocationBase::getlocationDefinitionNote() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreLocation, locationDefinitionNote));
}

bool ebucoreLocationBase::havelocationName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreLocation, locationName));
}

std::vector<ebucoreTextualAnnotation*> ebucoreLocationBase::getlocationName() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreLocation, locationName)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

bool ebucoreLocationBase::havelocationRegion() const
{
    return haveItem(&MXF_ITEM_K(ebucoreLocation, locationRegion));
}

ebucoreRegion* ebucoreLocationBase::getlocationRegion() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreLocation, locationRegion)));
    MXFPP_CHECK(dynamic_cast<ebucoreRegion*>(obj.get()) != 0);
    return dynamic_cast<ebucoreRegion*>(obj.release());
}

bool ebucoreLocationBase::havelocationTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreLocation, locationTypeGroup));
}

ebucoreTypeGroup* ebucoreLocationBase::getlocationTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreLocation, locationTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreLocationBase::havelocationCoordinates() const
{
    return haveItem(&MXF_ITEM_K(ebucoreLocation, locationCoordinates));
}

ebucoreCoordinates* ebucoreLocationBase::getlocationCoordinates() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreLocation, locationCoordinates)));
    MXFPP_CHECK(dynamic_cast<ebucoreCoordinates*>(obj.get()) != 0);
    return dynamic_cast<ebucoreCoordinates*>(obj.release());
}

void ebucoreLocationBase::setlocationId(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreLocation, locationId), value);
}

void ebucoreLocationBase::setlocationCode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreLocation, locationCode), value);
}

void ebucoreLocationBase::setlocationDefinitionNote(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreLocation, locationDefinitionNote), value);
}

void ebucoreLocationBase::setlocationName(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreLocation, locationName), &iter);
}

void ebucoreLocationBase::appendlocationName(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreLocation, locationName), value);
}

void ebucoreLocationBase::setlocationRegion(ebucoreRegion* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreLocation, locationRegion), value);
}

void ebucoreLocationBase::setlocationTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreLocation, locationTypeGroup), value);
}

void ebucoreLocationBase::setlocationCoordinates(ebucoreCoordinates* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreLocation, locationCoordinates), value);
}

