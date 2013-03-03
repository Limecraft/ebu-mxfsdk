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


const mxfKey ebucoreCoordinatesBase::setKey = MXF_SET_K(ebucoreCoordinates);


ebucoreCoordinatesBase::ebucoreCoordinatesBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreCoordinatesBase::ebucoreCoordinatesBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreCoordinatesBase::~ebucoreCoordinatesBase()
{}


bool ebucoreCoordinatesBase::haveposX() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoordinates, posX));
}

float ebucoreCoordinatesBase::getposX() const
{
    return getFloatItem(&MXF_ITEM_K(ebucoreCoordinates, posX));
}

bool ebucoreCoordinatesBase::haveposY() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoordinates, posY));
}

float ebucoreCoordinatesBase::getposY() const
{
    return getFloatItem(&MXF_ITEM_K(ebucoreCoordinates, posY));
}

bool ebucoreCoordinatesBase::havecoordinatesFormatGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoordinates, coordinatesFormatGroup));
}

ebucoreFormatGroup* ebucoreCoordinatesBase::getcoordinatesFormatGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreCoordinates, coordinatesFormatGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreFormatGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreFormatGroup*>(obj.release());
}

void ebucoreCoordinatesBase::setposX(float value)
{
    setFloatItem(&MXF_ITEM_K(ebucoreCoordinates, posX), value);
}

void ebucoreCoordinatesBase::setposY(float value)
{
    setFloatItem(&MXF_ITEM_K(ebucoreCoordinates, posY), value);
}

void ebucoreCoordinatesBase::setcoordinatesFormatGroup(ebucoreFormatGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreCoordinates, coordinatesFormatGroup), value);
}

