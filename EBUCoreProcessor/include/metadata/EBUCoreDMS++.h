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

#include <metadata/EBUCoreDMS.h>

// forward declare circularly referenced classes
namespace EBUCore
{
	namespace KLV {
		class ebucoreContact;
		class ebucoreRole;
		class ebucoreOrganisation;
		class ebucoreMetadataSchemeInformation;
		class ebucoreEntity;
	}
}

#include <metadata/ebucoreTypeGroup.h>
#include <metadata/ebucoreFormatGroup.h>
#include <metadata/ebucoreStatusGroup.h>
#include <metadata/ebucoreRole.h>
#include <metadata/ebucoreTextualAnnotation.h>
#include <metadata/ebucoreAddress.h>
#include <metadata/ebucoreContactDetails.h>
#include <metadata/ebucoreContact.h>
#include <metadata/ebucoreEntity.h>
#include <metadata/ebucoreOrganisationDepartment.h>
#include <metadata/ebucoreOrganisation.h>
#include <metadata/ebucoreIdentifier.h>
#include <metadata/ebucoreAlternativeTitle.h>
#include <metadata/ebucoreBasicRelation.h>
#include <metadata/ebucoreCoordinates.h>
#include <metadata/ebucoreCustomRelation.h>
#include <metadata/ebucoreDate.h>
#include <metadata/ebucoreDescription.h>
#include <metadata/ebucoreGenre.h>
#include <metadata/ebucoreLanguagePurpose.h>
#include <metadata/ebucoreLanguage.h>
#include <metadata/ebucoreLocation.h>
#include <metadata/ebucoreObjectType.h>
#include <metadata/ebucorePeriodOfTime.h>
#include <metadata/ebucorePublicationHistoryEvent.h>
#include <metadata/ebucoreRating.h>
#include <metadata/ebucoreSpatial.h>
#include <metadata/ebucoreSubject.h>
#include <metadata/ebucoreTargetAudience.h>
#include <metadata/ebucoreTemporal.h>
#include <metadata/ebucoreTitle.h>
#include <metadata/ebucoreType.h>
#include <metadata/ebucoreVersion.h>
#include <metadata/ebucoreCoverage.h>
#include <metadata/ebucoreRights.h>
#include <metadata/ebucoreCoreMetadata.h>
#include <metadata/ebucoreMainFramework.h>
#include <metadata/ebucorePartMetadata.h>
#include <metadata/ebucoreMetadataSchemeInformation.h>


#endif

using namespace mxfpp;

namespace EBUCore
{
	void RegisterExtensions(DataModel *dataModel);
	void RegisterFrameworkObjectFactory(HeaderMetadata *header_metadata);
};


