{ &MXF_ITEM_K(ebucoreMainFramework, coreMetadata), "ebucoreCoreMetadata*" },
{ &MXF_ITEM_K(ebucoreMainFramework, metadataSchemeInformation), "ebucoreMetadataSchemeInformation*" },

{ &MXF_ITEM_K(ebucorePartFramework, partMetadata), "ebucorePartMetadata*" },

{ &MXF_ITEM_K(ebucoreMetadataSchemeInformation, ebucoreMetadataProvider), "ebucoreEntity*" },

{ &MXF_ITEM_K(ebucoreEntity, entityContact), "ebucoreContact*" },
{ &MXF_ITEM_K(ebucoreEntity, entityOrganisation), "ebucoreOrganisation*" },
{ &MXF_ITEM_K(ebucoreEntity, entityRole), "ebucoreTypeGroup*" },

{ &MXF_ITEM_K(ebucoreContact, otherGivenName), "ebucoreTextualAnnotation*" },
{ &MXF_ITEM_K(ebucoreContact, username), "ebucoreTextualAnnotation*" },
{ &MXF_ITEM_K(ebucoreContact, contactType), "ebucoreTypeGroup*" },
{ &MXF_ITEM_K(ebucoreContact, contactDetails), "ebucoreContactDetails*" },
{ &MXF_ITEM_K(ebucoreContact, contactRelatedContacts), "ebucoreEntity*" },
{ &MXF_ITEM_K(ebucoreContact, stageName), "ebucoreTextualAnnotation*" },

{ &MXF_ITEM_K(ebucoreContactDetails, detailsType), "ebucoreTypeGroup*" },
{ &MXF_ITEM_K(ebucoreContactDetails, address), "ebucoreAddress*" },
{ &MXF_ITEM_K(ebucoreContactDetails, emailAddress), "ebucoreTextualAnnotation*" },

{ &MXF_ITEM_K(ebucoreAddress, addressLines), "ebucoreTextualAnnotation*" },



{ &MXF_ITEM_K(ebucoreOrganisation, organisationName), "ebucoreTextualAnnotation*" },
{ &MXF_ITEM_K(ebucoreOrganisation, organisationCode), "ebucoreTextualAnnotation*" },
{ &MXF_ITEM_K(ebucoreOrganisation, organisationDepartment), "ebucoreOrganisationDepartment*" },
{ &MXF_ITEM_K(ebucoreOrganisation, organisationType), "ebucoreTypeGroup*" },
{ &MXF_ITEM_K(ebucoreOrganisation, organisationDetails), "ebucoreContactDetails*" },
{ &MXF_ITEM_K(ebucoreOrganisation, organisationRelatedContacts), "ebucoreEntity*" },


{ &MXF_ITEM_K(ebucoreCoreMetadata, identifier), "ebucoreIdentifier*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, title), "ebucoreTitle*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, alternativeTitle), "ebucoreAlternativeTitle*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, creator), "ebucoreEntity*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, subject), "ebucoreSubject*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, description), "ebucoreDescription*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, publisher), "ebucoreEntity*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, contributor), "ebucoreEntity*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, date), "ebucoreDate*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, type), "ebucoreType*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, language), "ebucoreLanguage*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, coverage), "ebucoreCoverage*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, rights), "ebucoreRights*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, rating), "ebucoreRating*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, version), "ebucoreVersion*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, publicationHistoryEvent), "ebucorePublicationHistoryEvent*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, customRelation), "ebucoreCustomRelation*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, basicRelation), "ebucoreBasicRelation*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, format), "ebucoreFormat*" },
{ &MXF_ITEM_K(ebucoreCoreMetadata, part), "ebucorePartMetadata*" },

{ &MXF_ITEM_K(ebucoreIdentifier, identifierTypeGroup), "ebucoreTypeGroup*" },
{ &MXF_ITEM_K(ebucoreIdentifier, identifierFormatGroup), "ebucoreFormatGroup*" },
{ &MXF_ITEM_K(ebucoreIdentifier, identifierAttributorEntity), "ebucoreEntity*" },

{ &MXF_ITEM_K(ebucoreTitle, titleValue), "ebucoreTextualAnnotation*" },

{ &MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleValue), "ebucoreTextualAnnotation*" },
{ &MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleTypeGroup), "ebucoreTypeGroup*" },
{ &MXF_ITEM_K(ebucoreAlternativeTitle, alternativeTitleStatusGroup), "ebucoreStatusGroup*" },



{ &MXF_ITEM_K(ebucoreSubject, subjectValue), "ebucoreTextualAnnotation*" },
{ &MXF_ITEM_K(ebucoreSubject, subjectTypeGroup), "ebucoreTypeGroup*" },
{ &MXF_ITEM_K(ebucoreSubject, subjectAttributorEntity), "ebucoreEntity*" },

{ &MXF_ITEM_K(ebucoreDescription, descriptionValue), "ebucoreTextualAnnotation*" },
{ &MXF_ITEM_K(ebucoreDescription, descriptionTypeGroup), "ebucoreTypeGroup*" },

{ &MXF_ITEM_K(ebucoreDate, alternativeDate), "ebucoreDateType*" },

{ &MXF_ITEM_K(ebucoreDateType, textualDate), "ebucoreTextualAnnotation*" },
{ &MXF_ITEM_K(ebucoreDateType, dateTypeGroup), "ebucoreTypeGroup*" },

{ &MXF_ITEM_K(ebucoreType, typeValue), "ebucoreTextualAnnotation*" },
{ &MXF_ITEM_K(ebucoreType, objectType), "ebucoreObjectType*" },
{ &MXF_ITEM_K(ebucoreType, genre), "ebucoreGenre*" },
{ &MXF_ITEM_K(ebucoreType, targetAudience), "ebucoreTargetAudience*" },

{ &MXF_ITEM_K(ebucoreObjectType, objectTypeGroup), "ebucoreTypeGroup*" },

{ &MXF_ITEM_K(ebucoreGenre, genreKindGroup), "ebucoreTypeGroup*" },

{ &MXF_ITEM_K(ebucoreTargetAudience, targetAudienceKindGroup), "ebucoreTypeGroup*" },

{ &MXF_ITEM_K(ebucoreLanguage, languagePurposeSet), "ebucoreTypeGroup*" },

{ &MXF_ITEM_K(ebucoreCoverage, coverageValue), "ebucoreTextualAnnotation*" },
{ &MXF_ITEM_K(ebucoreCoverage, spatial), "ebucoreSpatial*" },
{ &MXF_ITEM_K(ebucoreCoverage, temporal), "ebucoreTemporal*" },

{ &MXF_ITEM_K(ebucoreSpatial, location), "ebucoreLocation*" },
{ &MXF_ITEM_K(ebucoreSpatial, coordinates), "ebucoreCoordinates*" },

{ &MXF_ITEM_K(ebucoreLocation, locationTypeGroup), "ebucoreTypeGroup*" },
{ &MXF_ITEM_K(ebucoreLocation, coordinateReference), "ebucoreCoordinates*" },

{ &MXF_ITEM_K(ebucoreCoordinates, coordinatesFormatGroup), "ebucoreFormatGroup*" },

{ &MXF_ITEM_K(ebucoreTemporal, periodOfTime), "ebucorePeriodOfTime*" },
{ &MXF_ITEM_K(ebucoreTemporal, temporalTypeGroup), "ebucoreTypeGroup*" },


{ &MXF_ITEM_K(ebucoreRights, rightsValue), "ebucoreTextualAnnotation*" },
{ &MXF_ITEM_K(ebucoreRights, exploitationIssues), "ebucoreTextualAnnotation*" },
{ &MXF_ITEM_K(ebucoreRights, rightsCoverage), "ebucoreCoverage*" },
{ &MXF_ITEM_K(ebucoreRights, rightsHolderEntity), "ebucoreEntity*" },
{ &MXF_ITEM_K(ebucoreRights, rightsContacts), "ebucoreContact*" },
{ &MXF_ITEM_K(ebucoreRights, rightsTypeGroup), "ebucoreTypeGroup*" },
{ &MXF_ITEM_K(ebucoreRights, rightsAttributeID), "ebucoreIdentifier*" },
{ &MXF_ITEM_K(ebucoreRights, rightsFormatReferences), "ebucoreFormat*" },


{ &MXF_ITEM_K(ebucoreRating, ratingTypeGroup), "ebucoreTypeGroup*" },
{ &MXF_ITEM_K(ebucoreRating, ratingFormatGroup), "ebucoreFormatGroup*" },
{ &MXF_ITEM_K(ebucoreRating, ratingProviderEntity), "ebucoreEntity*" },

{ &MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationMedium), "ebucoreTypeGroup*" },
{ &MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationFormatReference), "ebucoreFormat*" },

{ &MXF_ITEM_K(ebucoreCustomRelation, customRelationTypeGroup), "ebucoreTypeGroup*" },
{ &MXF_ITEM_K(ebucoreCustomRelation, relationIdentifier), "ebucoreIdentifier*" },


{ &MXF_ITEM_K(ebucorePartMetadata, partTypeGroup), "ebucoreTypeGroup*" },
{ &MXF_ITEM_K(ebucorePartMetadata, partMeta), "ebucoreCoreMetadata*" },

{ &MXF_ITEM_K(ebucoreFormat, containerFormat), "ebucoreContainerFormat*" },
{ &MXF_ITEM_K(ebucoreFormat, medium), "ebucoreMedium*" },
{ &MXF_ITEM_K(ebucoreFormat, packageInfo), "ebucorePackageInfo*" },
{ &MXF_ITEM_K(ebucoreFormat, mimeType), "ebucoreMimeType*" },
{ &MXF_ITEM_K(ebucoreFormat, materialAudioFormat), "ebucoreAudioFormat*" },
{ &MXF_ITEM_K(ebucoreFormat, materialVideoFormat), "ebucoreVideoFormat*" },
{ &MXF_ITEM_K(ebucoreFormat, materialImageFormat), "ebucoreImageFormat*" },
{ &MXF_ITEM_K(ebucoreFormat, materialDataFormat), "ebucoreDataFormat*" },
{ &MXF_ITEM_K(ebucoreFormat, materialSigningFormat), "ebucoreSigningFormat*" },
{ &MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeString), "ebucoreTechnicalAttributeString*" },
{ &MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt8), "ebucoreTechnicalAttributeInt8*" },
{ &MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt16), "ebucoreTechnicalAttributeInt16*" },
{ &MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt32), "ebucoreTechnicalAttributeInt32*" },
{ &MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeInt64), "ebucoreTechnicalAttributeInt64*" },
{ &MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt8), "ebucoreTechnicalAttributeUInt8*" },
{ &MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt16), "ebucoreTechnicalAttributeUInt16*" },
{ &MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt32), "ebucoreTechnicalAttributeUInt32*" },
{ &MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeUInt64), "ebucoreTechnicalAttributeUInt64*" },
{ &MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeFloat), "ebucoreTechnicalAttributeFloat*" },
{ &MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeRational), "ebucoreTechnicalAttributeRational*" },
{ &MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeAnyURI), "ebucoreTechnicalAttributeAnyURI*" },
{ &MXF_ITEM_K(ebucoreFormat, materialTechnicalAttributeBoolean), "ebucoreTechnicalAttributeBoolean*" },

{ &MXF_ITEM_K(ebucoreVideoFormat, videoAspectRatio), "ebucoreAspectRatio*" },
{ &MXF_ITEM_K(ebucoreVideoFormat, videoHeight), "ebucoreDimension*" },
{ &MXF_ITEM_K(ebucoreVideoFormat, videoWidth), "ebucoreDimension*" },
{ &MXF_ITEM_K(ebucoreVideoFormat, videoEncoding), "ebucoreEncoding*" },
{ &MXF_ITEM_K(ebucoreVideoFormat, videoCodectype), "ebucoreCodec*" },
{ &MXF_ITEM_K(ebucoreVideoFormat, videoTrack), "ebucoreTrack*" },
{ &MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeString), "ebucoreTechnicalAttributeString*" },
{ &MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt8), "ebucoreTechnicalAttributeInt8*" },
{ &MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt16), "ebucoreTechnicalAttributeInt16*" },
{ &MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt32), "ebucoreTechnicalAttributeInt32*" },
{ &MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeInt64), "ebucoreTechnicalAttributeInt64*" },
{ &MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt8), "ebucoreTechnicalAttributeUInt8*" },
{ &MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt16), "ebucoreTechnicalAttributeUInt16*" },
{ &MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt32), "ebucoreTechnicalAttributeUInt32*" },
{ &MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeUInt64), "ebucoreTechnicalAttributeUInt64*" },
{ &MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeFloat), "ebucoreTechnicalAttributeFloat*" },
{ &MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeRational), "ebucoreTechnicalAttributeRational*" },
{ &MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeAnyURI), "ebucoreTechnicalAttributeAnyURI*" },
{ &MXF_ITEM_K(ebucoreVideoFormat, videoTechnicalAttributeBoolean), "ebucoreTechnicalAttributeBoolean*" },

{ &MXF_ITEM_K(ebucoreImageFormat, imageAspectRatio), "ebucoreAspectRatio*" },
{ &MXF_ITEM_K(ebucoreImageFormat, imageEncoding), "ebucoreEncoding*" },
{ &MXF_ITEM_K(ebucoreImageFormat, imageCodec), "ebucoreCodec*" },
{ &MXF_ITEM_K(ebucoreImageFormat, imageHeight), "ebucoreDimension*" },
{ &MXF_ITEM_K(ebucoreImageFormat, imageWidth), "ebucoreDimension*" },
{ &MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeString), "ebucoreTechnicalAttributeString*" },
{ &MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt8), "ebucoreTechnicalAttributeInt8*" },
{ &MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt16), "ebucoreTechnicalAttributeInt16*" },
{ &MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt32), "ebucoreTechnicalAttributeInt32*" },
{ &MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeInt64), "ebucoreTechnicalAttributeInt64*" },
{ &MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt8), "ebucoreTechnicalAttributeUInt8*" },
{ &MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt16), "ebucoreTechnicalAttributeUInt16*" },
{ &MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt32), "ebucoreTechnicalAttributeUInt32*" },
{ &MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeUInt64), "ebucoreTechnicalAttributeUInt64*" },
{ &MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeFloat), "ebucoreTechnicalAttributeFloat*" },
{ &MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeRational), "ebucoreTechnicalAttributeRational*" },
{ &MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeAnyURI), "ebucoreTechnicalAttributeAnyURI*" },
{ &MXF_ITEM_K(ebucoreImageFormat, imageTechnicalAttributeBoolean), "ebucoreTechnicalAttributeBoolean*" },

{ &MXF_ITEM_K(ebucoreAudioFormat, audioTrackConfiguration), "ebucoreTypeGroup*" },
{ &MXF_ITEM_K(ebucoreAudioFormat, audioEncoding), "ebucoreEncoding*" },
{ &MXF_ITEM_K(ebucoreAudioFormat, audioCodec), "ebucoreCodec*" },
{ &MXF_ITEM_K(ebucoreAudioFormat, audioTrack), "ebucoreTrack*" },
{ &MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeString), "ebucoreTechnicalAttributeString*" },
{ &MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt8), "ebucoreTechnicalAttributeInt8*" },
{ &MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt16), "ebucoreTechnicalAttributeInt16*" },
{ &MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt32), "ebucoreTechnicalAttributeInt32*" },
{ &MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeInt64), "ebucoreTechnicalAttributeInt64*" },
{ &MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt8), "ebucoreTechnicalAttributeUInt8*" },
{ &MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt16), "ebucoreTechnicalAttributeUInt16*" },
{ &MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt32), "ebucoreTechnicalAttributeUInt32*" },
{ &MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeUInt64), "ebucoreTechnicalAttributeUInt64*" },
{ &MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeFloat), "ebucoreTechnicalAttributeFloat*" },
{ &MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeRational), "ebucoreTechnicalAttributeRational*" },
{ &MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeAnyURI), "ebucoreTechnicalAttributeAnyURI*" },
{ &MXF_ITEM_K(ebucoreAudioFormat, audioTechnicalAttributeBoolean), "ebucoreTechnicalAttributeBoolean*" },

{ &MXF_ITEM_K(ebucoreTrack, trackTypeGroup), "ebucoreTypeGroup*" },

{ &MXF_ITEM_K(ebucoreDataFormat, captioning), "ebucoreCaptioning*" },
{ &MXF_ITEM_K(ebucoreDataFormat, ancillaryData), "ebucoreAncillaryData*" },
{ &MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeString), "ebucoreTechnicalAttributeString*" },
{ &MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt8), "ebucoreTechnicalAttributeInt8*" },
{ &MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt16), "ebucoreTechnicalAttributeInt16*" },
{ &MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt32), "ebucoreTechnicalAttributeInt32*" },
{ &MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt64), "ebucoreTechnicalAttributeInt64*" },
{ &MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt8), "ebucoreTechnicalAttributeUInt8*" },
{ &MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt16), "ebucoreTechnicalAttributeUInt16*" },
{ &MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt32), "ebucoreTechnicalAttributeUInt32*" },
{ &MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt64), "ebucoreTechnicalAttributeUInt64*" },
{ &MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeFloat), "ebucoreTechnicalAttributeFloat*" },
{ &MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeRational), "ebucoreTechnicalAttributeRational*" },
{ &MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeAnyURI), "ebucoreTechnicalAttributeAnyURI*" },
{ &MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeBoolean), "ebucoreTechnicalAttributeBoolean*" },

{ &MXF_ITEM_K(ebucoreMimeType, mimeTypeGroup), "ebucoreTypeGroup*" },

{ &MXF_ITEM_K(ebucoreCaptioning, captioningTypeGroup), "ebucoreTypeGroup*" },

{ &MXF_ITEM_K(ebucoreAncillaryData, ANCWrappingType), "ebucoreTypeGroup*" },

{ &MXF_ITEM_K(ebucoreSigningFormat, signingTypeGroup), "ebucoreTypeGroup*" },
{ &MXF_ITEM_K(ebucoreSigningFormat, signingFormatGroup), "ebucoreFormatGroup*" },















{ &MXF_ITEM_K(ebucoreEncoding, encodingTypeGroup), "ebucoreTypeGroup*" },

{ &MXF_ITEM_K(ebucorePackageInfo, packageLocator), "ebucoreLocator*" },

{ &MXF_ITEM_K(ebucoreLocator, locatorTypeGroup), "ebucoreTypeGroup*" },

{ &MXF_ITEM_K(ebucoreContainerFormat, containerFormatGroup), "ebucoreFormatGroup*" },

{ &MXF_ITEM_K(ebucoreMedium, mediumTypeGroup), "ebucoreTypeGroup*" },



{ &MXF_ITEM_K(ebucoreAspectRatio, aspectRatioTypeGroup), "ebucoreTypeGroup*" },
