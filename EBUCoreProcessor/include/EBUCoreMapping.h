
#include <libMXF++/MXF.h>

#include "EBU_CORE_20110915.hxx"

#include <metadata/EBUCoreDMS++.h>

using namespace EBUCore::KLV;

namespace EBUCore {

class ObjectModifier {
public:
	virtual void Modify(mxfpp::InterchangeObject *obj) = 0;
};

class GenerationUIDAppender : public ObjectModifier {
	mxfUUID _generationUID;
public:
	GenerationUIDAppender(mxfUUID GenerationUID) {
		_generationUID = GenerationUID;
	}
	void Modify(mxfpp::InterchangeObject *obj) {
		obj->setGenerationUID(_generationUID);
	}
};

void mapCoreMetadata(ebuCore_2011::coreMetadataType& source, ebucoreCoreMetadata *dest, ObjectModifier* mod = NULL);
void mapCoreMetadata(ebucoreCoreMetadata *source, ebuCore_2011::coreMetadataType& dest);
void mapMetadataSchemeInformation(ebuCore_2011::ebuCoreMainType& source, ebucoreMetadataSchemeInformation *dest, ObjectModifier* mod = NULL);
void mapMetadataSchemeInformation(ebucoreMetadataSchemeInformation *source, ebuCore_2011::ebuCoreMainType& dest);
void mapEntity(ebuCore_2011::entityType& source, ebucoreEntity *dest, ObjectModifier* mod = NULL);
void mapEntity(ebucoreEntity *source, ebuCore_2011::entityType& dest);

}
