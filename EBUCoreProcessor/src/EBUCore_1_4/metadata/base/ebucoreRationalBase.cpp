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


const mxfKey ebucoreRationalBase::setKey = MXF_SET_K(ebucoreRational);


ebucoreRationalBase::ebucoreRationalBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreRationalBase::ebucoreRationalBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreRationalBase::~ebucoreRationalBase()
{}


bool ebucoreRationalBase::havenominalValue() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRational, nominalValue));
}

uint64_t ebucoreRationalBase::getnominalValue() const
{
    return getUInt64Item(&MXF_ITEM_K(ebucoreRational, nominalValue));
}

bool ebucoreRationalBase::havefactorNumerator() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRational, factorNumerator));
}

uint64_t ebucoreRationalBase::getfactorNumerator() const
{
    return getUInt64Item(&MXF_ITEM_K(ebucoreRational, factorNumerator));
}

bool ebucoreRationalBase::havefactorDenominator() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRational, factorDenominator));
}

uint64_t ebucoreRationalBase::getfactorDenominator() const
{
    return getUInt64Item(&MXF_ITEM_K(ebucoreRational, factorDenominator));
}

void ebucoreRationalBase::setnominalValue(uint64_t value)
{
    setUInt64Item(&MXF_ITEM_K(ebucoreRational, nominalValue), value);
}

void ebucoreRationalBase::setfactorNumerator(uint64_t value)
{
    setUInt64Item(&MXF_ITEM_K(ebucoreRational, factorNumerator), value);
}

void ebucoreRationalBase::setfactorDenominator(uint64_t value)
{
    setUInt64Item(&MXF_ITEM_K(ebucoreRational, factorDenominator), value);
}

