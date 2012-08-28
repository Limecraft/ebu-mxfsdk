
#include <metadata/EBUCoreDMS++.h>

using namespace EBUCore::KLV;

namespace EBUCore {

void RegisterExtensions(DataModel *data_model)
{
    // register AS-11 framework set and items in data model

#define MXF_LABEL(d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15) \
    {d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15}

#define MXF_SET_DEFINITION(parent_name, name, label) \
    data_model->registerSetDef(#name, &MXF_SET_K(parent_name), &MXF_SET_K(name));

#define MXF_ITEM_DEFINITION(set_name, name, label, tag, type_id, is_required) \
    data_model->registerItemDef(#name, &MXF_SET_K(set_name), &MXF_ITEM_K(set_name, name), tag, type_id, is_required);

#include <metadata/ebucore_extensions_data_model.h>

    data_model->finalise();
}

void RegisterFrameworkObjectFactory(HeaderMetadata *header_metadata)
{
	header_metadata->registerObjectFactory(&ebucoreMainFramework::setKey, new MetadataSetFactory<ebucoreMainFramework>());
	header_metadata->registerObjectFactory(&ebucoreCoreMetadata::setKey, new MetadataSetFactory<ebucoreCoreMetadata>());
	header_metadata->registerObjectFactory(&ebucoreTitle::setKey, new MetadataSetFactory<ebucoreTitle>());
	header_metadata->registerObjectFactory(&ebucoreAlternativeTitle::setKey, new MetadataSetFactory<ebucoreAlternativeTitle>());
	header_metadata->registerObjectFactory(&ebucoreTypeGroup::setKey, new MetadataSetFactory<ebucoreTypeGroup>());
	header_metadata->registerObjectFactory(&ebucoreStatusGroup::setKey, new MetadataSetFactory<ebucoreStatusGroup>());
	header_metadata->registerObjectFactory(&ebucoreFormatGroup::setKey, new MetadataSetFactory<ebucoreFormatGroup>());
	header_metadata->registerObjectFactory(&ebucoreEntity::setKey, new MetadataSetFactory<ebucoreEntity>());
	header_metadata->registerObjectFactory(&ebucoreTextualAnnotation::setKey, new MetadataSetFactory<ebucoreTextualAnnotation>());
	header_metadata->registerObjectFactory(&ebucoreAddress::setKey, new MetadataSetFactory<ebucoreAddress>());
	header_metadata->registerObjectFactory(&ebucoreContact::setKey, new MetadataSetFactory<ebucoreContact>());
	header_metadata->registerObjectFactory(&ebucoreContactDetails::setKey, new MetadataSetFactory<ebucoreContactDetails>());
	header_metadata->registerObjectFactory(&ebucoreOrganisation::setKey, new MetadataSetFactory<ebucoreOrganisation>());
	header_metadata->registerObjectFactory(&ebucoreIdentifier::setKey, new MetadataSetFactory<ebucoreIdentifier>());
	header_metadata->registerObjectFactory(&ebucoreSubject::setKey, new MetadataSetFactory<ebucoreSubject>());
	header_metadata->registerObjectFactory(&ebucoreRating::setKey, new MetadataSetFactory<ebucoreRating>());
	header_metadata->registerObjectFactory(&ebucoreType::setKey, new MetadataSetFactory<ebucoreType>());
	header_metadata->registerObjectFactory(&ebucoreTargetAudience::setKey, new MetadataSetFactory<ebucoreTargetAudience>());
	header_metadata->registerObjectFactory(&ebucoreGenre::setKey, new MetadataSetFactory<ebucoreGenre>());
	header_metadata->registerObjectFactory(&ebucoreObjectType::setKey, new MetadataSetFactory<ebucoreObjectType>());
	header_metadata->registerObjectFactory(&ebucoreDescription::setKey, new MetadataSetFactory<ebucoreDescription>());
	header_metadata->registerObjectFactory(&ebucorePublicationHistoryEvent::setKey, new MetadataSetFactory<ebucorePublicationHistoryEvent>());
	header_metadata->registerObjectFactory(&ebucoreDateType::setKey, new MetadataSetFactory<ebucoreDate>());
	header_metadata->registerObjectFactory(&ebucoreDate::setKey, new MetadataSetFactory<ebucoreDate>());
	header_metadata->registerObjectFactory(&ebucoreLanguage::setKey, new MetadataSetFactory<ebucoreLanguage>());
	header_metadata->registerObjectFactory(&ebucoreSpatial::setKey, new MetadataSetFactory<ebucoreSpatial>());
	header_metadata->registerObjectFactory(&ebucoreLocation::setKey, new MetadataSetFactory<ebucoreLocation>());
	header_metadata->registerObjectFactory(&ebucoreTemporal::setKey, new MetadataSetFactory<ebucoreTemporal>());
	header_metadata->registerObjectFactory(&ebucorePeriodOfTime::setKey, new MetadataSetFactory<ebucorePeriodOfTime>());
	header_metadata->registerObjectFactory(&ebucoreCoverage::setKey, new MetadataSetFactory<ebucoreCoverage>());
	header_metadata->registerObjectFactory(&ebucoreVersion::setKey, new MetadataSetFactory<ebucoreVersion>());
	header_metadata->registerObjectFactory(&ebucoreRights::setKey, new MetadataSetFactory<ebucoreRights>());
	header_metadata->registerObjectFactory(&ebucoreCustomRelation::setKey, new MetadataSetFactory<ebucoreCustomRelation>());
	header_metadata->registerObjectFactory(&ebucoreMetadataSchemeInformation::setKey, new MetadataSetFactory<ebucoreMetadataSchemeInformation>());
}

};
