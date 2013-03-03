/*
 *	Copyright 2012-2013 European Broadcasting Union and Limecraft, NV.
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *	   http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *	See the License for the specific language governing permissions and
 *	limitations under the License.
 *
 */
 
#include <libMXF++/MXF.h>

#include <EBUCore_1_4/xsd/EBU_CORE_20130107.hxx>

#include <MXFCustomMetadata.h>
#include <EBUCore_1_4/metadata/EBUCoreDMS++.h>

using namespace EBUSDK::MXFCustomMetadata;
using namespace EBUSDK::EBUCore::EBUCore_1_4::KLV;

namespace EBUSDK {
namespace EBUCore {
namespace EBUCore_1_4 {

void mapCoreMetadata(ebuCore_2012::coreMetadataType& source, ebucoreCoreMetadata *dest, mxfRational overallFrameRate, std::vector<ebucorePartMetadata*>& timelineParts, ObjectModifier* mod = NULL);
void mapCoreMetadata(ebucoreCoreMetadata *source, ebuCore_2012::coreMetadataType& dest);
void mapMetadataSchemeInformation(ebuCore_2012::ebuCoreMainType& source, ebucoreMetadataSchemeInformation *dest, ObjectModifier* mod = NULL);
void mapMetadataSchemeInformation(ebucoreMetadataSchemeInformation *source, ebuCore_2012::ebuCoreMainType& dest);
void mapEntity(ebuCore_2012::entityType& source, ebucoreEntity *dest, ObjectModifier* mod = NULL);
void mapEntity(ebucoreEntity *source, ebuCore_2012::entityType& dest);

}
}
}
