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


const mxfKey ebucoreTextualAnnotationBase::setKey = MXF_SET_K(ebucoreTextualAnnotation);


ebucoreTextualAnnotationBase::ebucoreTextualAnnotationBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreTextualAnnotationBase::ebucoreTextualAnnotationBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreTextualAnnotationBase::~ebucoreTextualAnnotationBase()
{}


bool ebucoreTextualAnnotationBase::havetext() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTextualAnnotation, text));
}

std::string ebucoreTextualAnnotationBase::gettext() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTextualAnnotation, text));
}

bool ebucoreTextualAnnotationBase::havetextLanguage() const
{
    return haveItem(&MXF_ITEM_K(ebucoreTextualAnnotation, textLanguage));
}

std::string ebucoreTextualAnnotationBase::gettextLanguage() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreTextualAnnotation, textLanguage));
}

void ebucoreTextualAnnotationBase::settext(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTextualAnnotation, text), value);
}

void ebucoreTextualAnnotationBase::settextLanguage(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreTextualAnnotation, textLanguage), value);
}

