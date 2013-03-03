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


const mxfKey ebucoreCoverageBase::setKey = MXF_SET_K(ebucoreCoverage);


ebucoreCoverageBase::ebucoreCoverageBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreCoverageBase::ebucoreCoverageBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreCoverageBase::~ebucoreCoverageBase()
{}


bool ebucoreCoverageBase::havecoverageValue() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoverage, coverageValue));
}

ebucoreTextualAnnotation* ebucoreCoverageBase::getcoverageValue() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreCoverage, coverageValue)));
    MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTextualAnnotation*>(obj.release());
}

bool ebucoreCoverageBase::havespatial() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoverage, spatial));
}

ebucoreSpatial* ebucoreCoverageBase::getspatial() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreCoverage, spatial)));
    MXFPP_CHECK(dynamic_cast<ebucoreSpatial*>(obj.get()) != 0);
    return dynamic_cast<ebucoreSpatial*>(obj.release());
}

bool ebucoreCoverageBase::havetemporal() const
{
    return haveItem(&MXF_ITEM_K(ebucoreCoverage, temporal));
}

ebucoreTemporal* ebucoreCoverageBase::gettemporal() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreCoverage, temporal)));
    MXFPP_CHECK(dynamic_cast<ebucoreTemporal*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTemporal*>(obj.release());
}

void ebucoreCoverageBase::setcoverageValue(ebucoreTextualAnnotation* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreCoverage, coverageValue), value);
}

void ebucoreCoverageBase::setspatial(ebucoreSpatial* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreCoverage, spatial), value);
}

void ebucoreCoverageBase::settemporal(ebucoreTemporal* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreCoverage, temporal), value);
}

