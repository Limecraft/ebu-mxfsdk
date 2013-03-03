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


const mxfKey ebucoreRightsBase::setKey = MXF_SET_K(ebucoreRights);


ebucoreRightsBase::ebucoreRightsBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreRightsBase::ebucoreRightsBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreRightsBase::~ebucoreRightsBase()
{}


bool ebucoreRightsBase::haverightsId() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsId));
}

std::string ebucoreRightsBase::getrightsId() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreRights, rightsId));
}

bool ebucoreRightsBase::haverightsLink() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsLink));
}

std::string ebucoreRightsBase::getrightsLink() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreRights, rightsLink));
}

bool ebucoreRightsBase::haverightsClearanceFlag() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsClearanceFlag));
}

bool ebucoreRightsBase::getrightsClearanceFlag() const
{
    return getBooleanItem(&MXF_ITEM_K(ebucoreRights, rightsClearanceFlag));
}

bool ebucoreRightsBase::haverightsNote() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsNote));
}

std::string ebucoreRightsBase::getrightsNote() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreRights, rightsNote));
}

bool ebucoreRightsBase::haverightsValue() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsValue));
}

std::vector<ebucoreTextualAnnotation*> ebucoreRightsBase::getrightsValue() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsValue)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

bool ebucoreRightsBase::haveexploitationIssues() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, exploitationIssues));
}

std::vector<ebucoreTextualAnnotation*> ebucoreRightsBase::getexploitationIssues() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, exploitationIssues)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

bool ebucoreRightsBase::havecopyrightStatement() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, copyrightStatement));
}

std::vector<ebucoreTextualAnnotation*> ebucoreRightsBase::getcopyrightStatement() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, copyrightStatement)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

bool ebucoreRightsBase::haverightsCoverage() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsCoverage));
}

ebucoreCoverage* ebucoreRightsBase::getrightsCoverage() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreRights, rightsCoverage)));
    MXFPP_CHECK(dynamic_cast<ebucoreCoverage*>(obj.get()) != 0);
    return dynamic_cast<ebucoreCoverage*>(obj.release());
}

bool ebucoreRightsBase::haverightsHolderEntity() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsHolderEntity));
}

std::vector<ebucoreEntity*> ebucoreRightsBase::getrightsHolderEntity() const
{
    vector<ebucoreEntity*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsHolderEntity)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreEntity*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreEntity*>(iter->get()));
    }
    return result;
}

bool ebucoreRightsBase::haverightsContacts() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsContacts));
}

std::vector<ebucoreContact*> ebucoreRightsBase::getrightsContacts() const
{
    vector<ebucoreContact*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsContacts)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreContact*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreContact*>(iter->get()));
    }
    return result;
}

bool ebucoreRightsBase::haverightsTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsTypeGroup));
}

ebucoreTypeGroup* ebucoreRightsBase::getrightsTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreRights, rightsTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreRightsBase::haverightsAttributeID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsAttributeID));
}

std::vector<ebucoreIdentifier*> ebucoreRightsBase::getrightsAttributeID() const
{
    vector<ebucoreIdentifier*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsAttributeID)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreIdentifier*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreIdentifier*>(iter->get()));
    }
    return result;
}

bool ebucoreRightsBase::haverightsFormatReferences() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRights, rightsFormatReferences));
}

std::vector<ebucoreFormat*> ebucoreRightsBase::getrightsFormatReferences() const
{
    vector<ebucoreFormat*> result;
    auto_ptr<ObjectIterator> iter(getWeakRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsFormatReferences)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreFormat*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreFormat*>(iter->get()));
    }
    return result;
}

void ebucoreRightsBase::setrightsId(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreRights, rightsId), value);
}

void ebucoreRightsBase::setrightsLink(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreRights, rightsLink), value);
}

void ebucoreRightsBase::setrightsClearanceFlag(bool value)
{
    setBooleanItem(&MXF_ITEM_K(ebucoreRights, rightsClearanceFlag), value);
}

void ebucoreRightsBase::setrightsNote(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreRights, rightsNote), value);
}

void ebucoreRightsBase::setrightsValue(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsValue), &iter);
}

void ebucoreRightsBase::appendrightsValue(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsValue), value);
}

void ebucoreRightsBase::setexploitationIssues(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, exploitationIssues), &iter);
}

void ebucoreRightsBase::appendexploitationIssues(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, exploitationIssues), value);
}

void ebucoreRightsBase::setcopyrightStatement(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, copyrightStatement), &iter);
}

void ebucoreRightsBase::appendcopyrightStatement(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, copyrightStatement), value);
}

void ebucoreRightsBase::setrightsCoverage(ebucoreCoverage* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreRights, rightsCoverage), value);
}

void ebucoreRightsBase::setrightsHolderEntity(const std::vector<ebucoreEntity*>& value)
{
    WrapObjectVectorIterator<ebucoreEntity> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsHolderEntity), &iter);
}

void ebucoreRightsBase::appendrightsHolderEntity(ebucoreEntity* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsHolderEntity), value);
}

void ebucoreRightsBase::setrightsContacts(const std::vector<ebucoreContact*>& value)
{
    WrapObjectVectorIterator<ebucoreContact> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsContacts), &iter);
}

void ebucoreRightsBase::appendrightsContacts(ebucoreContact* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsContacts), value);
}

void ebucoreRightsBase::setrightsTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreRights, rightsTypeGroup), value);
}

void ebucoreRightsBase::setrightsAttributeID(const std::vector<ebucoreIdentifier*>& value)
{
    WrapObjectVectorIterator<ebucoreIdentifier> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsAttributeID), &iter);
}

void ebucoreRightsBase::appendrightsAttributeID(ebucoreIdentifier* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsAttributeID), value);
}

void ebucoreRightsBase::setrightsFormatReferences(const std::vector<ebucoreFormat*>& value)
{
    WrapObjectVectorIterator<ebucoreFormat> iter(value);
    setWeakRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsFormatReferences), &iter);
}

void ebucoreRightsBase::appendrightsFormatReferences(ebucoreFormat* value)
{
    appendWeakRefArrayItem(&MXF_ITEM_K(ebucoreRights, rightsFormatReferences), value);
}

