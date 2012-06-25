
#include <metadata/EBUCoreDMS++.h>

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
}

};
