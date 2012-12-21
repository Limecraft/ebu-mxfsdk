/*
 * Copyright (C) 2011, British Broadcasting Corporation
 * All Rights Reserved.
 *
 * Author: Philip de Nier
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the British Broadcasting Corporation nor the names
 *       of its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
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
#include <EBUCore_1_4/metadata/ebucoreTypeGroup.h>
#include <EBUCore_1_4/metadata/ebucoreFormatGroup.h>
#include <EBUCore_1_4/metadata/ebucoreStatusGroup.h>

#include <EBUCore_1_4/metadata/ebucoreAddress.h>
#include <EBUCore_1_4/metadata/ebucoreContactDetails.h>
#include <EBUCore_1_4/metadata/ebucoreContact.h>
#include <EBUCore_1_4/metadata/ebucoreEntity.h>
#include <EBUCore_1_4/metadata/ebucoreOrganisationDepartment.h>
#include <EBUCore_1_4/metadata/ebucoreOrganisation.h>
#include <EBUCore_1_4/metadata/ebucoreIdentifier.h>
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
#include <EBUCore_1_4/metadata/ebucoreContainerFormat.h>
#include <EBUCore_1_4/metadata/ebucoreDimension.h>
#include <EBUCore_1_4/metadata/ebucoreEncoding.h>
#include <EBUCore_1_4/metadata/ebucoreMedium.h>
#include <EBUCore_1_4/metadata/ebucoreMimeType.h>
#include <EBUCore_1_4/metadata/ebucoreLocator.h>
#include <EBUCore_1_4/metadata/ebucorePackageInfo.h>
#include <EBUCore_1_4/metadata/ebucoreRational.h>
#include <EBUCore_1_4/metadata/ebucoreSigningFormat.h>
#include <EBUCore_1_4/metadata/ebucoreTrack.h>
#include <EBUCore_1_4/metadata/ebucoreVideoFormat.h>
#include <EBUCore_1_4/metadata/ebucoreImageFormat.h>
#include <EBUCore_1_4/metadata/ebucoreAudioFormat.h>
#include <EBUCore_1_4/metadata/ebucoreDataFormat.h>
#include <EBUCore_1_4/metadata/ebucoreFormat.h>

#include <EBUCore_1_4/metadata/ebucoreRights.h>
#include <EBUCore_1_4/metadata/ebucorePublicationHistoryEvent.h>

#include <EBUCore_1_4/metadata/ebucoreMetadataSchemeInformation.h>
#include <EBUCore_1_4/metadata/ebucorePartMetadata.h>
#include <EBUCore_1_4/metadata/ebucoreCoreMetadata.h>
#include <EBUCore_1_4/metadata/ebucoreMainFramework.h>
#include <EBUCore_1_4/metadata/ebucorePartFramework.h>

#endif


