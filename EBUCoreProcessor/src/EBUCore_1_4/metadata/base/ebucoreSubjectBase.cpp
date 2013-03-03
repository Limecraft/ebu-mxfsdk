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


const mxfKey ebucoreSubjectBase::setKey = MXF_SET_K(ebucoreSubject);


ebucoreSubjectBase::ebucoreSubjectBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreSubjectBase::ebucoreSubjectBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreSubjectBase::~ebucoreSubjectBase()
{}


bool ebucoreSubjectBase::havesubjectCode() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubject, subjectCode));
}

std::string ebucoreSubjectBase::getsubjectCode() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSubject, subjectCode));
}

bool ebucoreSubjectBase::havesubjectNote() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubject, subjectNote));
}

std::string ebucoreSubjectBase::getsubjectNote() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreSubject, subjectNote));
}

bool ebucoreSubjectBase::havesubjectValue() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubject, subjectValue));
}

std::vector<ebucoreTextualAnnotation*> ebucoreSubjectBase::getsubjectValue() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreSubject, subjectValue)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

bool ebucoreSubjectBase::havesubjectDefinition() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubject, subjectDefinition));
}

std::vector<ebucoreTextualAnnotation*> ebucoreSubjectBase::getsubjectDefinition() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreSubject, subjectDefinition)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

bool ebucoreSubjectBase::havesubjectTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubject, subjectTypeGroup));
}

ebucoreTypeGroup* ebucoreSubjectBase::getsubjectTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreSubject, subjectTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreSubjectBase::havesubjectAttributorEntity() const
{
    return haveItem(&MXF_ITEM_K(ebucoreSubject, subjectAttributorEntity));
}

ebucoreEntity* ebucoreSubjectBase::getsubjectAttributorEntity() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreSubject, subjectAttributorEntity)));
    MXFPP_CHECK(dynamic_cast<ebucoreEntity*>(obj.get()) != 0);
    return dynamic_cast<ebucoreEntity*>(obj.release());
}

void ebucoreSubjectBase::setsubjectCode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSubject, subjectCode), value);
}

void ebucoreSubjectBase::setsubjectNote(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreSubject, subjectNote), value);
}

void ebucoreSubjectBase::setsubjectValue(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreSubject, subjectValue), &iter);
}

void ebucoreSubjectBase::appendsubjectValue(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreSubject, subjectValue), value);
}

void ebucoreSubjectBase::setsubjectDefinition(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreSubject, subjectDefinition), &iter);
}

void ebucoreSubjectBase::appendsubjectDefinition(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreSubject, subjectDefinition), value);
}

void ebucoreSubjectBase::setsubjectTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreSubject, subjectTypeGroup), value);
}

void ebucoreSubjectBase::setsubjectAttributorEntity(ebucoreEntity* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreSubject, subjectAttributorEntity), value);
}

