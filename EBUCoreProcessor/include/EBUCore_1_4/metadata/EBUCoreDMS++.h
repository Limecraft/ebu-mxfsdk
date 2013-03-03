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

#ifndef __EBUCORE_DMSPP_H__
#define __EBUCORE_DMSPP_H__

#include <libMXF++/MXF.h>

#include <EBUCore_1_4/metadata/EBUCoreDMS.h>

using namespace mxfpp;

// declare our global metadata functions and
// forward declare circularly referenced classes
namespace EBUSDK {
namespace EBUCore
{
	namespace EBUCore_1_4 {
		void RegisterExtensions(DataModel *dataModel);
		void RegisterFrameworkObjectFactory(HeaderMetadata *header_metadata);

		namespace KLV {
			class ebucoreContact;
			class ebucoreOrganisation;
			class ebucoreMetadataSchemeInformation;
			class ebucoreEntity;
	
			class ebucorePartMetadata;
			class ebucoreCoreMetadata;
		}
	}
}
}

#include <EBUCore_1_4/metadata/ebucoreTextualAnnotation.h>
#include <EBUCore_1_4/metadata/ebucoreBasicLink.h>
#include <EBUCore_1_4/metadata/ebucoreTypeGroup.h>
#include <EBUCore_1_4/metadata/ebucoreFormatGroup.h>
#include <EBUCore_1_4/metadata/ebucoreStatusGroup.h>

#include <EBUCore_1_4/metadata/ebucoreCompoundName.h>
#include <EBUCore_1_4/metadata/ebucoreCountry.h>
#include <EBUCore_1_4/metadata/ebucoreRegion.h>
#include <EBUCore_1_4/metadata/ebucoreRole.h>
#include <EBUCore_1_4/metadata/ebucoreAddress.h>
#include <EBUCore_1_4/metadata/ebucoreContactDetails.h>
#include <EBUCore_1_4/metadata/ebucoreContact.h>
#include <EBUCore_1_4/metadata/ebucoreEntity.h>
#include <EBUCore_1_4/metadata/ebucoreIdentifier.h>
#include <EBUCore_1_4/metadata/ebucoreOrganisationDepartment.h>
#include <EBUCore_1_4/metadata/ebucoreOrganisation.h>
#include <EBUCore_1_4/metadata/ebucoreAlternativeTitle.h>
#include <EBUCore_1_4/metadata/ebucoreBasicRelation.h>
#include <EBUCore_1_4/metadata/ebucoreCoordinates.h>
#include <EBUCore_1_4/metadata/ebucoreCustomRelation.h>
#include <EBUCore_1_4/metadata/ebucoreDateType.h>
#include <EBUCore_1_4/metadata/ebucoreDate.h>
#include <EBUCore_1_4/metadata/ebucoreDescription.h>
#include <EBUCore_1_4/metadata/ebucoreGenre.h>
#include <EBUCore_1_4/metadata/ebucoreLanguage.h>
#include <EBUCore_1_4/metadata/ebucoreLocation.h>
#include <EBUCore_1_4/metadata/ebucoreObjectType.h>
#include <EBUCore_1_4/metadata/ebucorePeriodOfTime.h>
#include <EBUCore_1_4/metadata/ebucoreRating.h>
#include <EBUCore_1_4/metadata/ebucoreSpatial.h>
#include <EBUCore_1_4/metadata/ebucoreSubject.h>
#include <EBUCore_1_4/metadata/ebucoreTargetAudience.h>
#include <EBUCore_1_4/metadata/ebucoreTemporal.h>
#include <EBUCore_1_4/metadata/ebucoreTitle.h>
#include <EBUCore_1_4/metadata/ebucoreType.h>
#include <EBUCore_1_4/metadata/ebucoreVersion.h>
#include <EBUCore_1_4/metadata/ebucoreCoverage.h>

#include <EBUCore_1_4/metadata/ebucoreTechnicalAttributeAnyURI.h>
#include <EBUCore_1_4/metadata/ebucoreTechnicalAttributeBoolean.h>
#include <EBUCore_1_4/metadata/ebucoreTechnicalAttributeFloat.h>
#include <EBUCore_1_4/metadata/ebucoreTechnicalAttributeInt16.h>
#include <EBUCore_1_4/metadata/ebucoreTechnicalAttributeInt32.h>
#include <EBUCore_1_4/metadata/ebucoreTechnicalAttributeInt64.h>
#include <EBUCore_1_4/metadata/ebucoreTechnicalAttributeInt8.h>
#include <EBUCore_1_4/metadata/ebucoreTechnicalAttributeRational.h>
#include <EBUCore_1_4/metadata/ebucoreTechnicalAttributeString.h>
#include <EBUCore_1_4/metadata/ebucoreTechnicalAttributeUInt16.h>
#include <EBUCore_1_4/metadata/ebucoreTechnicalAttributeUInt32.h>
#include <EBUCore_1_4/metadata/ebucoreTechnicalAttributeUInt64.h>
#include <EBUCore_1_4/metadata/ebucoreTechnicalAttributeUInt8.h>
#include <EBUCore_1_4/metadata/ebucoreAncillaryData.h>
#include <EBUCore_1_4/metadata/ebucoreAspectRatio.h>
#include <EBUCore_1_4/metadata/ebucoreCaptioning.h>
#include <EBUCore_1_4/metadata/ebucoreCodec.h>
#include <EBUCore_1_4/metadata/ebucoreDimension.h>
#include <EBUCore_1_4/metadata/ebucoreWidth.h>
#include <EBUCore_1_4/metadata/ebucoreHeight.h>
#include <EBUCore_1_4/metadata/ebucoreMedium.h>
#include <EBUCore_1_4/metadata/ebucorePackageInfo.h>
#include <EBUCore_1_4/metadata/ebucoreRational.h>
#include <EBUCore_1_4/metadata/ebucoreSubtitling.h>
#include <EBUCore_1_4/metadata/ebucoreSigningFormat.h>
#include <EBUCore_1_4/metadata/ebucoreTrack.h>
#include <EBUCore_1_4/metadata/ebucoreVideoFormat.h>
#include <EBUCore_1_4/metadata/ebucoreImageFormat.h>
#include <EBUCore_1_4/metadata/ebucoreAudioFormat.h>
#include <EBUCore_1_4/metadata/ebucoreDataFormat.h>
#include <EBUCore_1_4/metadata/ebucoreFormat.h>

#include <EBUCore_1_4/metadata/ebucoreRights.h>
#include <EBUCore_1_4/metadata/ebucorePublicationChannel.h>
#include <EBUCore_1_4/metadata/ebucorePublicationMedium.h>
#include <EBUCore_1_4/metadata/ebucorePublicationService.h>
#include <EBUCore_1_4/metadata/ebucorePublicationHistoryEvent.h>
#include <EBUCore_1_4/metadata/ebucorePublicationHistory.h>

#include <EBUCore_1_4/metadata/ebucoreMetadataSchemeInformation.h>
#include <EBUCore_1_4/metadata/ebucorePartMetadata.h>
#include <EBUCore_1_4/metadata/ebucoreCoreMetadata.h>
#include <EBUCore_1_4/metadata/ebucoreMainFramework.h>
#include <EBUCore_1_4/metadata/ebucorePartFramework.h>

#endif


