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


const mxfKey ebucoreRatingBase::setKey = MXF_SET_K(ebucoreRating);


ebucoreRatingBase::ebucoreRatingBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreRatingBase::ebucoreRatingBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreRatingBase::~ebucoreRatingBase()
{}


bool ebucoreRatingBase::haveratingReason() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRating, ratingReason));
}

std::string ebucoreRatingBase::getratingReason() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreRating, ratingReason));
}

bool ebucoreRatingBase::haveratingLinkToLogo() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRating, ratingLinkToLogo));
}

std::string ebucoreRatingBase::getratingLinkToLogo() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreRating, ratingLinkToLogo));
}

bool ebucoreRatingBase::haveratingNotRatedFlag() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRating, ratingNotRatedFlag));
}

bool ebucoreRatingBase::getratingNotRatedFlag() const
{
    return getBooleanItem(&MXF_ITEM_K(ebucoreRating, ratingNotRatedFlag));
}

bool ebucoreRatingBase::haveratingAdultContentFlag() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRating, ratingAdultContentFlag));
}

bool ebucoreRatingBase::getratingAdultContentFlag() const
{
    return getBooleanItem(&MXF_ITEM_K(ebucoreRating, ratingAdultContentFlag));
}

bool ebucoreRatingBase::haveratingValue() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRating, ratingValue));
}

std::vector<ebucoreTextualAnnotation*> ebucoreRatingBase::getratingValue() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreRating, ratingValue)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

bool ebucoreRatingBase::haveratingScaleMinValue() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRating, ratingScaleMinValue));
}

std::vector<ebucoreTextualAnnotation*> ebucoreRatingBase::getratingScaleMinValue() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreRating, ratingScaleMinValue)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

bool ebucoreRatingBase::haveratingScaleMaxValue() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRating, ratingScaleMaxValue));
}

std::vector<ebucoreTextualAnnotation*> ebucoreRatingBase::getratingScaleMaxValue() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreRating, ratingScaleMaxValue)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

bool ebucoreRatingBase::haveratingTypeGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRating, ratingTypeGroup));
}

ebucoreTypeGroup* ebucoreRatingBase::getratingTypeGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreRating, ratingTypeGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreTypeGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreTypeGroup*>(obj.release());
}

bool ebucoreRatingBase::haveratingFormatGroup() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRating, ratingFormatGroup));
}

ebucoreFormatGroup* ebucoreRatingBase::getratingFormatGroup() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreRating, ratingFormatGroup)));
    MXFPP_CHECK(dynamic_cast<ebucoreFormatGroup*>(obj.get()) != 0);
    return dynamic_cast<ebucoreFormatGroup*>(obj.release());
}

bool ebucoreRatingBase::haveratingProviderEntity() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRating, ratingProviderEntity));
}

ebucoreEntity* ebucoreRatingBase::getratingProviderEntity() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreRating, ratingProviderEntity)));
    MXFPP_CHECK(dynamic_cast<ebucoreEntity*>(obj.get()) != 0);
    return dynamic_cast<ebucoreEntity*>(obj.release());
}

bool ebucoreRatingBase::haveratingRegion() const
{
    return haveItem(&MXF_ITEM_K(ebucoreRating, ratingRegion));
}

ebucoreRegion* ebucoreRatingBase::getratingRegion() const
{
    auto_ptr<MetadataSet> obj(getStrongRefItem(&MXF_ITEM_K(ebucoreRating, ratingRegion)));
    MXFPP_CHECK(dynamic_cast<ebucoreRegion*>(obj.get()) != 0);
    return dynamic_cast<ebucoreRegion*>(obj.release());
}

void ebucoreRatingBase::setratingReason(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreRating, ratingReason), value);
}

void ebucoreRatingBase::setratingLinkToLogo(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreRating, ratingLinkToLogo), value);
}

void ebucoreRatingBase::setratingNotRatedFlag(bool value)
{
    setBooleanItem(&MXF_ITEM_K(ebucoreRating, ratingNotRatedFlag), value);
}

void ebucoreRatingBase::setratingAdultContentFlag(bool value)
{
    setBooleanItem(&MXF_ITEM_K(ebucoreRating, ratingAdultContentFlag), value);
}

void ebucoreRatingBase::setratingValue(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreRating, ratingValue), &iter);
}

void ebucoreRatingBase::appendratingValue(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreRating, ratingValue), value);
}

void ebucoreRatingBase::setratingScaleMinValue(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreRating, ratingScaleMinValue), &iter);
}

void ebucoreRatingBase::appendratingScaleMinValue(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreRating, ratingScaleMinValue), value);
}

void ebucoreRatingBase::setratingScaleMaxValue(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreRating, ratingScaleMaxValue), &iter);
}

void ebucoreRatingBase::appendratingScaleMaxValue(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreRating, ratingScaleMaxValue), value);
}

void ebucoreRatingBase::setratingTypeGroup(ebucoreTypeGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreRating, ratingTypeGroup), value);
}

void ebucoreRatingBase::setratingFormatGroup(ebucoreFormatGroup* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreRating, ratingFormatGroup), value);
}

void ebucoreRatingBase::setratingProviderEntity(ebucoreEntity* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreRating, ratingProviderEntity), value);
}

void ebucoreRatingBase::setratingRegion(ebucoreRegion* value)
{
    setStrongRefItem(&MXF_ITEM_K(ebucoreRating, ratingRegion), value);
}

