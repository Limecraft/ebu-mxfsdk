/*#include <iostream>
#include <fstream>
#include <memory>

#include <bmx/BMXException.h>
#include <bmx/Logging.h>*/

#include "EBUCoreMapping.h"

#include <xercesc/util/TransService.hpp>

using namespace ebuCore_2012;
using namespace mxfpp;
//using namespace bmx;

namespace EBUSDK {
namespace EBUCore {

#define	SIMPLE_RMAP(source, sourceProperty, dest, destProperty)	\
	dest.destProperty() = source->sourceProperty();
#define	SIMPLE_MAP_NO_GET(source, sourceProperty, dest, destProperty)	\
	dest->destProperty(source.sourceProperty());

#define	SIMPLE_RMAP_OPTIONAL(source, haveSourceProperty, getSourceProperty, dest, destProperty)	\
	if (source->haveSourceProperty())	\
		dest.destProperty() = source->getSourceProperty();
#define	SIMPLE_RMAP_OPTIONAL_POINTER(source, haveSourceProperty, getSourceProperty, dest, destProperty)	\
	if (source->haveSourceProperty())	\
		dest->destProperty() = source->getSourceProperty();
#define	SIMPLE_RMAP_OPTIONAL_CONVERT(source, haveSourceProperty, getSourceProperty, dest, destProperty, convertFunction)	\
	if (source->haveSourceProperty())	\
		dest.destProperty() = convertFunction(source->getSourceProperty());

#define NEW_OBJECT_AND_RASSIGN(source, getSourceProperty, destType, mapMethod, dest, destProperty) \
	{	\
		std::auto_ptr<destType> p( new destType() );	\
		mapMethod(source->getSourceProperty(), *p);	\
		dest.destProperty(p);	\
	}
#define NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, haveSourceProperty, getSourceProperty, destType, mapMethod, dest, destProperty) \
	NEW_OBJECT_AND_RASSIGN_OPTIONAL_CARGS(source, haveSourceProperty, getSourceProperty, destType, mapMethod, dest, destProperty,)
#define NEW_OBJECT_AND_RASSIGN_OPTIONAL_CARGS(source, haveSourceProperty, getSourceProperty, destType, mapMethod, dest, destProperty, constructorArgs) \
	if (source->haveSourceProperty()) {	\
		std::auto_ptr<destType> p( new destType(constructorArgs) );	\
		mapMethod(source->getSourceProperty(), *p);	\
		dest.destProperty(p);	\
	}
#define NEW_OBJECT_AND_RASSIGN_OPTIONAL_GETPOINTER(source, haveSourceProperty, getSourceProperty, destType, mapMethod, dest, destProperty) \
	if (source->haveSourceProperty()) {	\
		std::auto_ptr<destType> p( new destType() );	\
		mapMethod(source->getSourceProperty(), *(p.get()));	\
		dest.destProperty(p);	\
	}

#define NEW_VECTOR_AND_RASSIGN_CARGS_PREFIXCODE(source, sourceProperty, destType, destSequenceType, vectorType, mapMethod, dest, destProperty, prefixCode, ctrArgs)	\
	{ destSequenceType vec_##dest##destProperty; const vectorType& vec_##source##sourceProperty = source->sourceProperty(); \
	for (vectorType::const_iterator it = vec_##source##sourceProperty.begin(); it != vec_##source##sourceProperty.end(); it++) { \
		prefixCode; \
		std::auto_ptr<destType> p( new destType(ctrArgs) ); \
		mapMethod(*it, *p); \
		vec_##dest##destProperty.push_back(p); \
	} \
	dest.destProperty(vec_##dest##destProperty); }

#define NEW_VECTOR_AND_RASSIGN(source, sourceProperty, destType, destSequenceType, vectorType, mapMethod, dest, destProperty)	\
	NEW_VECTOR_AND_RASSIGN_CARGS_PREFIXCODE(source, sourceProperty, destType, destSequenceType, vectorType, mapMethod, dest, destProperty,,)

#define NEW_VECTOR_AND_RASSIGN_WITH_DC(source, sourceProperty, destType, destSequenceType, vectorType, mapMethod, dest, destProperty)	\
	NEW_VECTOR_AND_RASSIGN_CARGS_PREFIXCODE(source, sourceProperty, destType, destSequenceType, vectorType, mapMethod, dest, destProperty, std::auto_ptr<dc::elementType> dcp( new dc::elementType() ), dcp)

#define NEW_VECTOR_AND_RASSIGN_CARGS(source, sourceProperty, destType, destSequenceType, vectorType, mapMethod, dest, destProperty, constructorArgs)	\
	NEW_VECTOR_AND_RASSIGN_CARGS_PREFIXCODE(source, sourceProperty, destType, destSequenceType, vectorType, mapMethod, dest, destProperty,,constructorArgs)

#define RMAP_TYPE_GROUP_GET_OPTIONAL(source, haveTypeGroupProperty, getTypeGroupProperty, dest, destType)	\
	if (source->haveTypeGroupProperty()) { \
		ebucoreTypeGroup *tg = source->getTypeGroupProperty(); \
		RMAP_TYPE_GROUP(tg, dest, destType::typeDefinition_type, destType::typeLabel_type, destType::typeLink_type, destType::typeLanguage_type) \
	}
#define RMAP_FORMAT_GROUP_GET_OPTIONAL(source, haveFormatGroupProperty, getFormatGroupProperty, dest, destType)	\
	if (source->haveFormatGroupProperty()) { \
		ebucoreFormatGroup *g = source->getFormatGroupProperty(); \
		RMAP_FORMAT_GROUP(g, dest, destType::formatDefinition_type, destType::formatLabel_type, destType::formatLink_type, destType::formatLanguage_type) \
	}
#define RMAP_STATUS_GROUP_GET_OPTIONAL(source, haveStatusGroupProperty, getStatusGroupProperty, dest, destType)	\
	if (source->haveStatusGroupProperty()) { \
		ebucoreStatusGroup *g = source->getStatusGroupProperty(); \
		RMAP_STATUS_GROUP(g, dest, destType::statusDefinition_type, destType::statusLabel_type, destType::statusLink_type, destType::statusLanguage_type) \
	}


#define RMAP_TYPE_GROUP(source, dest, definitionType, labelType, linkType, languageType)	\
	if (source->havetypeGroupDefinition()) {	\
		dest.typeDefinition().set(std::auto_ptr<definitionType>( new definitionType( source->gettypeGroupDefinition() ) ));	\
	}	\
	if (source->havetypeGroupLabel()) {	\
		dest.typeLabel().set(std::auto_ptr<labelType>( new labelType( source->gettypeGroupLabel() ) ));	\
	}	\
	if (source->havetypeGroupLink()) {	\
		dest.typeLink().set( std::auto_ptr<linkType> ( new linkType( source->gettypeGroupLink() ) ));	\
	}	\
	if (source->havetypeGroupLanguage()) {	\
		dest.typeLanguage().set( std::auto_ptr<languageType> ( new languageType( source->gettypeGroupLanguage() ) ));	\
	}
#define RMAP_STATUS_GROUP(source, dest, definitionType, labelType, linkType, languageType)	\
	if (source->havestatusGroupDefinition()) {	\
		dest.statusDefinition().set(std::auto_ptr<definitionType>( new definitionType( source->getstatusGroupDefinition() ) ));	\
	}	\
	if (source->havestatusGroupLabel()) {	\
		dest.statusLabel().set(std::auto_ptr<labelType>( new labelType( source->getstatusGroupLabel() ) ));	\
	}	\
	if (source->havestatusGroupLink()) {	\
		dest.statusLink().set( std::auto_ptr<linkType> ( new linkType( source->getstatusGroupLink() ) ));	\
	} \
	if (source->havestatusGroupLanguage()) {	\
		dest.statusLanguage().set( std::auto_ptr<languageType> ( new languageType( source->getstatusGroupLanguage() ) ));	\
	}
#define RMAP_FORMAT_GROUP(source, dest, definitionType, labelType, linkType, languageType)	\
	if (source->haveformatGroupDefinition()) {	\
		dest.formatDefinition().set(std::auto_ptr<definitionType>( new definitionType( source->getformatGroupDefinition() ) ));	\
	}	\
	if (source->haveformatGroupLabel()) {	\
		dest.formatLabel().set(std::auto_ptr<labelType>( new labelType( source->getformatGroupLabel() ) ));	\
	}	\
	if (source->haveformatGroupLink()) {	\
		dest.formatLink().set( std::auto_ptr<linkType> ( new linkType( source->getformatGroupLink() ) ));	\
	} \
	if (source->haveformatGroupLanguage()) {	\
		dest.formatLanguage().set( std::auto_ptr<languageType> ( new languageType( source->getformatGroupLanguage() ) ));	\
	}

void mapTextualAnnotation(ebucoreTextualAnnotation *source, dc::elementType& dest) {
	dest = source->gettext();
	if (source->havetextLanguage())
		dest.lang() = source->gettextLanguage();
}

void mapTextualAnnotation(ebucoreTextualAnnotation *source, std::string& dest) {
	dest = source->gettext();
}

void mapAddress(ebucoreAddress *source, addressType& dest) {
	if (source->haveaddressLines()) {
		addressType::addressLine_sequence lines;
		std::vector<ebucoreTextualAnnotation*> source_vec = source->getaddressLines();
		for (std::vector<ebucoreTextualAnnotation*>::iterator it = source_vec.begin(); it != source_vec.end(); it++) {
			std::auto_ptr<detailsType> p( new detailsType() );
			lines.push_back((*it)->gettext());
			if ((*it)->havetextLanguage())
				lines.back().lang() = (*it)->gettextLanguage();
		}
		dest.addressLine(lines);
	}

	SIMPLE_RMAP_OPTIONAL(source, havetownCity, gettownCity, dest, addressTownCity)
	SIMPLE_RMAP_OPTIONAL(source, havecountyState, getcountyState, dest, addressCountyState)
	SIMPLE_RMAP_OPTIONAL(source, havedeliveryCode, getdeliveryCode, dest, addressDeliveryCode)

	// special treatment for country, current KLV mapping is not via a typeGroup!
	if (source->havecountryCode() || source->havecountryName()) {
		std::auto_ptr<addressType::country_type> p( new addressType::country_type() );
		SIMPLE_RMAP_OPTIONAL_POINTER(source, havecountryCode, getcountryCode, p, typeLink)
		SIMPLE_RMAP_OPTIONAL_POINTER(source, havecountryName, getcountryName, p, typeLabel)
		dest.country(p);
	}
}

void mapDetails(ebucoreContactDetails *source, detailsType& dest) {

	if (source->haveemailAddress()) {
		NEW_VECTOR_AND_RASSIGN(source, getemailAddress, detailsType::emailAddress_type, detailsType::emailAddress_sequence, std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, emailAddress)
	}
	
	SIMPLE_RMAP_OPTIONAL(source, havewebAddress, getwebAddress, dest, webAddress)

	NEW_OBJECT_AND_RASSIGN_OPTIONAL_GETPOINTER(source, haveaddress, getaddress, addressType, mapAddress, dest, address)

	SIMPLE_RMAP_OPTIONAL(source, havetelephoneNumber, gettelephoneNumber, dest, telephoneNumber)
	SIMPLE_RMAP_OPTIONAL(source, havemobileTelephoneNumber, getmobileTelephoneNumber, dest, mobileTelephoneNumber)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havedetailsType, getdetailsType, dest, detailsType)
}

void mapContact(ebucoreContact *source, contactDetailsType& dest) {

	SIMPLE_RMAP_OPTIONAL(source, havecontactId, getcontactId, dest, contactId)

	if (source->havecontactName()) {
		dest.name() = source->getcontactName();
	} else {
		SIMPLE_RMAP_OPTIONAL(source, havefamilyName, getfamilyName, dest, familyName) 
		SIMPLE_RMAP_OPTIONAL(source, havegivenName, getgivenName, dest, givenName)
		SIMPLE_RMAP_OPTIONAL(source, havesuffix, getsuffix, dest, suffix)
		SIMPLE_RMAP_OPTIONAL(source, havesalutation, getsalutation, dest, salutation) 
		if (source->haveotherGivenName()) {
			NEW_VECTOR_AND_RASSIGN(source, getotherGivenName, contactDetailsType::otherGivenName_type, contactDetailsType::otherGivenName_sequence, std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, otherGivenName)
		}
	}
	if (source->haveusername()) {
		NEW_VECTOR_AND_RASSIGN(source, getusername, contactDetailsType::username_type, contactDetailsType::username_sequence, std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, username)
	}
	SIMPLE_RMAP_OPTIONAL(source, haveoccupation, getoccupation, dest, occupation)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havecontactType, getcontactType, dest, contactDetailsType)

	NEW_VECTOR_AND_RASSIGN(source, getcontactDetails, detailsType, contactDetailsType::details_sequence, std::vector<ebucoreContactDetails*>, mapDetails, dest, details)
	if (source->havestageName()) {
		NEW_VECTOR_AND_RASSIGN(source, getstageName, contactDetailsType::stageName_type, contactDetailsType::stageName_sequence, std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, stageName)
	}
	NEW_VECTOR_AND_RASSIGN(source, getcontactRelatedContacts, entityType, contactDetailsType::relatedContacts_sequence, std::vector<ebucoreEntity*>, mapEntity, dest, relatedContacts)
}

void mapOrganisationDepartment(ebucoreOrganisationDepartment *source, organisationDepartment& dest) {
	if (source->havedepartmentName())
		dest = source->getdepartmentName();
	SIMPLE_RMAP_OPTIONAL(source, havedepartmentId, getdepartmentId, dest, departmentId)
}

void mapOrganisation(ebucoreOrganisation *source, organisationDetailsType& dest) {

	SIMPLE_RMAP_OPTIONAL(source, haveorganisationId, getorganisationId, dest, organisationId)

	NEW_VECTOR_AND_RASSIGN(source, getorganisationName, organisationDetailsType::organisationName_type, 
		organisationDetailsType::organisationName_sequence, std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, organisationName)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getorganisationCode, organisationDetailsType::organisationCode_type, 
		organisationDetailsType::organisationCode_sequence, std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, organisationCode, "" /* initialize URI with empty text */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getorganisationCode, organisationDetailsType::organisationCode_type, 
		organisationDetailsType::organisationCode_sequence, std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, organisationCode, (*it)->gettext())

	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, haveorganisationDepartment, getorganisationDepartment, organisationDepartment, mapOrganisationDepartment, dest, organisationDepartment)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, haveorganisationType, getorganisationType, dest, organisationDetailsType)

	NEW_VECTOR_AND_RASSIGN(source, getorganisationRelatedContacts, entityType, organisationDetailsType::contacts_sequence, std::vector<ebucoreEntity*>, mapEntity, dest, contacts)
	NEW_VECTOR_AND_RASSIGN(source, getorganisationDetails, detailsType, organisationDetailsType::details_sequence, std::vector<ebucoreContactDetails*>, mapDetails, dest, details)
}

void mapRole(ebucoreTypeGroup *source, role& dest) {
	RMAP_TYPE_GROUP(source, dest, role::typeDefinition_type, role::typeLabel_type, role::typeLink_type, role::typeLanguage_type)
}

void mapEntity(ebucoreEntity *source, entityType& dest) {

	SIMPLE_RMAP_OPTIONAL(source, haveentityId, getentityId, dest, entityId)

	if (source->haveentityContact()) {
		NEW_VECTOR_AND_RASSIGN(source, getentityContact, contactDetailsType, entityType::contactDetails_sequence, std::vector<ebucoreContact*>, mapContact, dest, contactDetails)
	}

	if (source->haveentityOrganisation()) {
		NEW_VECTOR_AND_RASSIGN(source, getentityOrganisation, organisationDetailsType, entityType::organisationDetails_sequence, std::vector<ebucoreOrganisation*>, mapOrganisation, dest, organisationDetails)
	}

	if (source->haveentityRole()) {
		NEW_VECTOR_AND_RASSIGN(source, getentityRole, role, entityType::role_sequence, std::vector<ebucoreTypeGroup*>, mapRole, dest, role)
	}
}

void mapMetadataSchemeInformation(ebucoreMetadataSchemeInformation *source, ebuCoreMainType& dest) {
	/*
	<sequence>
		<element name="coreMetadata" type="ebucore:coreMetadataType">
		</element>
		<element name="metadataProvider" type="ebucore:entityType" minOccurs="0">
		</element>
	</sequence>
	<attribute name="schema" default="EBU_CORE_20110531.xsd">
	</attribute>
	<attribute name="version" default="1.3">
	</attribute>
	<attribute name="dateLastModified" type="date">
	</attribute>
	<attribute name="documentId" type="NMTOKEN">
	</attribute>
	<attribute ref="xml:lang">
	</attribute>
	*/

	// [TODO] Version and schema need processing

	//NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, metadataProvider, ebucoreEntity, mapEntity, dest, setebucoreMetadataProvider)

}

xml_schema::date* convert_timestamp_date(mxfTimestamp source) {
	return new xml_schema::date(source.year, source.month, source.day);
}

xml_schema::time* convert_timestamp_time(mxfTimestamp source) {
	return new xml_schema::time(source.hour, source.min, source.sec);
}

xml_schema::gyear* convert_timestamp_year(mxfTimestamp source) {
	return new xml_schema::gyear(source.year);
}

xml_schema::idrefs* convert_idrefs(const std::string& source) {
	const char *delims = " ";
	xml_schema::idrefs *dest = new xml_schema::idrefs();
    // Skip delimiters at beginning.
    std::string::size_type lastPos = source.find_first_not_of(delims, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = source.find_first_of(delims, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector.
		dest->push_back(source.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = source.find_first_not_of(delims, pos);
        // Find next "non-delimiter"
        pos = source.find_first_of(delims, lastPos);
    }
	return dest;
}

int32_t convert_to_int(const std::string& source) {
	int32_t out;
	std::stringstream ss;
	ss << source;
	ss >> out;
	return out;
}

void mapTitle(ebucoreTitle *source, titleType& dest) {

	NEW_VECTOR_AND_RASSIGN(source, gettitleValue, titleType::title_type, titleType::title_sequence, 
		std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, title)

	SIMPLE_RMAP_OPTIONAL(source, havetitleNote, gettitleNote, dest, note)
	if (source->havetitleAttributionDate()) {
		std::auto_ptr<ebuCoreMainType::dateLastModified_type> dp( convert_timestamp_date(source->gettitleAttributionDate()));
		dest.attributiondate().set(dp);
	}
}

void mapAlternativeTitle(ebucoreAlternativeTitle *source, alternativeTitleType& dest) {

	NEW_VECTOR_AND_RASSIGN(source, getalternativeTitleValue, alternativeTitleType::title_type, alternativeTitleType::title_sequence, 
		std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, title)

	SIMPLE_RMAP_OPTIONAL(source, havealternativeTitleNote, getalternativeTitleNote, dest, note)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havealternativeTitleTypeGroup, getalternativeTitleTypeGroup, dest, alternativeTitleType)
	RMAP_STATUS_GROUP_GET_OPTIONAL(source, havealternativeTitleStatusGroup, getalternativeTitleStatusGroup, dest, alternativeTitleType)
	
	if (source->havealternativeTitleAttributionDate()) {
		std::auto_ptr<ebuCoreMainType::dateLastModified_type> dp( convert_timestamp_date(source->getalternativeTitleAttributionDate()));
		dest.startDate().set(dp);
	}
}

void mapIdentifier(ebucoreIdentifier *source, identifierType& dest) {
	/*
		<sequence>
			<element ref="dc:identifier">
			</element>
			<element name="attributor" type="ebucore:entityType" minOccurs="0">
			</element>
		</sequence>
		<attributeGroup ref="ebucore:typeGroup">
		</attributeGroup>
		<attributeGroup ref="ebucore:formatGroup">
		</attributeGroup>
		<attribute name="note" type="string">
		</attribute>
	*/

	std::auto_ptr<dc::elementType> dcp( new dc::elementType( source->getidentifierValue() ) );
	dest.identifier(dcp);

	SIMPLE_RMAP_OPTIONAL(source, haveidentifierNote, getidentifierNote, dest, note)

	RMAP_FORMAT_GROUP_GET_OPTIONAL(source, haveidentifierFormatGroup, getidentifierFormatGroup, dest, identifierType)
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, haveidentifierTypeGroup, getidentifierTypeGroup, dest, identifierType)

	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, haveidentifierAttributorEntity, getidentifierAttributorEntity, entityType, mapEntity, dest, attributor)
}

void mapDescription(ebucoreDescription *source, descriptionType& dest) {

	NEW_VECTOR_AND_RASSIGN(source, getdescriptionValue, descriptionType::description_type, descriptionType::description_sequence, 
		std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, description)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havedescriptionTypeGroup, getdescriptionTypeGroup, dest, identifierType)

	SIMPLE_RMAP_OPTIONAL(source, havedescriptionNote, getdescriptionNote, dest, note)
}

void mapSubject(ebucoreSubject *source, subjectType& dest) {
	NEW_OBJECT_AND_RASSIGN(source, getsubjectValue, subjectType::subject_type, mapTextualAnnotation, dest, subject)

	SIMPLE_RMAP_OPTIONAL(source, havesubjectCode, getsubjectCode, dest, subjectCode)
	SIMPLE_RMAP_OPTIONAL(source, havesubjectDefinition, getsubjectDefinition, dest, subjectDefinition)
	SIMPLE_RMAP_OPTIONAL(source, havesubjectNote, getsubjectNote, dest, note)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havesubjectTypeGroup, getsubjectTypeGroup, dest, identifierType)

	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havesubjectAttributorEntity, getsubjectAttributorEntity, entityType, mapEntity, dest, attributor)
}

std::auto_ptr<ratingType> mapRating(ebucoreRating *source) {

	entityType *e = new entityType();
	mapEntity(source->getratingProviderEntity(), *e);

	// a new ratingType requires a number of values directly in its constructor, 
	// so we need something a little different
	std::auto_ptr<ratingType> dest( new ratingType( 
		source->getratingValue(),
		source->getratingScaleMinValue(),
		source->getratingScaleMaxValue(), 
		*e) );

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, haveratingTypeGroup, getratingTypeGroup, (*dest), identifierType)
	RMAP_FORMAT_GROUP_GET_OPTIONAL(source, haveratingFormatGroup, getratingFormatGroup, (*dest), identifierType)

	return dest;
}

void mapVersion(ebucoreVersion *source, coreMetadataType::version_type& dest) {
	dest = source->getversionValue();
	SIMPLE_RMAP_OPTIONAL(source, haveversionLanguage, getversionLanguage, dest, lang)
}

void mapLanguage(ebucoreLanguage *source, languageType& dest) {

	SIMPLE_RMAP_OPTIONAL(source, havelanguageLanguage, getlanguageLanguage, dest, language)
	SIMPLE_RMAP_OPTIONAL(source, havelanguageCode, getlanguageCode, dest, language().get().lang)
	SIMPLE_RMAP_OPTIONAL(source, havelanguageNote, getlanguageNote, dest, note)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havelanguagePurposeSet, getlanguagePurposeSet, dest, languageType)
}

void mapType(ebucoreType *source, typeType& dest) {

	if (source->havetypeValue()) {
		NEW_VECTOR_AND_RASSIGN(source, gettypeValue, typeType::type_type, typeType::type_sequence, std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, type)
	}

	if (source->haveobjectType()) {
		typeType::objectType_sequence obtyps;
		std::vector<ebucoreObjectType*> source_obtyps = source->getobjectType();
		for (std::vector<ebucoreObjectType*>::iterator it = source_obtyps.begin(); it != source_obtyps.end(); it++) {
			std::auto_ptr<objectType> p( new objectType() );
			RMAP_TYPE_GROUP_GET_OPTIONAL((*it), haveobjectTypeGroup, getobjectTypeGroup, (*p), objectType)
			dest.objectType().push_back(p);
		}
	}

	if (source->havetargetAudience()) {
		typeType::targetAudience_sequence tauds;
		std::vector<ebucoreTargetAudience*> source_tauds = source->gettargetAudience();
		for (std::vector<ebucoreTargetAudience*>::iterator it = source_tauds.begin(); it != source_tauds.end(); it++) {
			std::auto_ptr<targetAudience> p( new targetAudience() );
			RMAP_TYPE_GROUP_GET_OPTIONAL((*it), havetargetAudienceKindGroup, gettargetAudienceKindGroup, (*p), targetAudience)
			tauds.push_back(p);
		}
		dest.targetAudience(tauds);
	}

	if (source->havegenre()) {
		typeType::genre_sequence gens;
		std::vector<ebucoreGenre*> source_gens = source->getgenre();
		for (std::vector<ebucoreGenre*>::iterator it = source_gens.begin(); it != source_gens.end(); it++) {
			std::auto_ptr<genre> p( new genre() );
			RMAP_TYPE_GROUP_GET_OPTIONAL((*it), havegenreKindGroup, getgenreKindGroup, (*p), genre)
			gens.push_back(p);
		}
		dest.genre(gens);
	}

	SIMPLE_RMAP_OPTIONAL(source, havetypeNote, gettypeNote, dest, note)
}

void mapDateType(ebucoreDateType *source, alternative& dest) {
	if (source->havedateValue()) {
		dest.startDate(std::auto_ptr<xml_schema::date>( convert_timestamp_date(source->getdateValue()) ));
	}
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havedateTypeGroup, getdateTypeGroup, dest, dateType::alternative_type)
}

void mapDate(ebucoreDate* source, dateType& dest) {
	// Reserve mapping operation of date:
	// Map each of the regular dates to their counterpart in XSD,
	NEW_VECTOR_AND_RASSIGN(source, getalternativeDate, alternative, dateType::alternative_sequence, std::vector<ebucoreDateType*>, mapDateType, dest, alternative)

	if (source->havedateCreated() || source->haveyearCreated()) {
		std::auto_ptr<dateType::created_type> p ( new dateType::created_type() );
		if (source->havedateCreated()) {
			p->startDate( std::auto_ptr<xml_schema::date>( convert_timestamp_date(source->getdateCreated()) ) );
		if (source->haveyearCreated())
			p->startYear( std::auto_ptr<xml_schema::gyear>( convert_timestamp_year(source->getyearCreated()) ) );		
		}
		dest.created(p);
	}
	if (source->havedateIssued() || source->haveyearIssued()) {
		std::auto_ptr<dateType::issued_type> p ( new dateType::issued_type() );
		if (source->havedateIssued()) {
			p->startDate( std::auto_ptr<xml_schema::date>( convert_timestamp_date(source->getdateIssued()) ) );
		if (source->haveyearIssued())
			p->startYear( std::auto_ptr<xml_schema::gyear>( convert_timestamp_year(source->getyearIssued()) ) );		
		}
		dest.issued(p);
	}
	if (source->havedateModified() || source->haveyearModified()) {
		std::auto_ptr<dateType::modified_type> p ( new dateType::modified_type() );
		if (source->havedateModified()) {
			p->startDate( std::auto_ptr<xml_schema::date>( convert_timestamp_date(source->getdateModified()) ) );
		if (source->haveyearModified())
			p->startYear( std::auto_ptr<xml_schema::gyear>( convert_timestamp_year(source->getyearModified()) ) );		
		}
		dest.modified(p);
	}
	if (source->havedateDigitized() || source->haveyearDigitized()) {
		std::auto_ptr<dateType::digitised_type> p ( new dateType::digitised_type() );
		if (source->havedateDigitized()) {
			p->startDate( std::auto_ptr<xml_schema::date>( convert_timestamp_date(source->getdateDigitized()) ) );
		if (source->haveyearDigitized())
			p->startYear( std::auto_ptr<xml_schema::gyear>( convert_timestamp_year(source->getyearDigitized()) ) );		
		}
		dest.digitised(p);
	}
}

void mapPeriodOfTime(ebucorePeriodOfTime* source, PeriodOfTime& dest) {
	// [TODO] Fix correct location of periodId!
	//SIMPLE_RMAP_OPTIONAL(source, haveperiodId, getperiodId, dest, period)
	if (source->haveperiodName()) 
		dest.periodName( std::auto_ptr<PeriodOfTime::periodName_type>( new PeriodOfTime::periodName_type( source->getperiodName() ) ) );
	if (source->haveperiodStartYear())
		dest.startYear( std::auto_ptr<xml_schema::gyear>( convert_timestamp_year(source->getperiodStartYear()) ) );
	if (source->haveperiodStartDate())
		dest.startDate( std::auto_ptr<xml_schema::date>( convert_timestamp_date(source->getperiodStartDate()) ) );
	if (source->haveperiodStartTime())
		dest.startTime( std::auto_ptr<xml_schema::time>( convert_timestamp_time(source->getperiodStartTime()) ) );
	if (source->haveperiodEndYear())
		dest.endYear( std::auto_ptr<xml_schema::gyear>( convert_timestamp_year(source->getperiodEndYear()) ) );
	if (source->haveperiodEndDate())
		dest.endDate( std::auto_ptr<xml_schema::date>( convert_timestamp_date(source->getperiodEndDate()) ) );
	if (source->haveperiodEndTime())
		dest.endTime( std::auto_ptr<xml_schema::time>( convert_timestamp_time(source->getperiodEndTime()) ) );
}

void mapTemporal(ebucoreTemporal *source, temporal& dest) {
	// if there is more that a single period of time, we only use the first one
	// [FIX?] Updated cardinality, source has only max 1 periodoftime
	if (source->haveperiodOfTime()) {
		NEW_VECTOR_AND_RASSIGN(source, getperiodOfTime, PeriodOfTime, temporal::PeriodOfTime_sequence, std::vector<ebucorePeriodOfTime*>, mapPeriodOfTime, dest, PeriodOfTime)
	}
	SIMPLE_RMAP_OPTIONAL(source, havetemporalDefinitionNote, gettemporalDefinitionNote, dest, note)
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havetemporalTypeGroup, gettemporalTypeGroup, dest, temporal)
}

void mapSpatial(ebucoreSpatial *source, spatial& dest) {
	std::vector<ebucoreLocation*> locs = source->getlocation();
	for (std::vector<ebucoreLocation*>::iterator it = locs.begin(); it != locs.end(); it++) {
		std::auto_ptr<location> p( new location() );
		ebucoreLocation* loc = *it;
		
		SIMPLE_RMAP_OPTIONAL_POINTER(loc, havelocationId, getlocationId, p, locationId)
		SIMPLE_RMAP_OPTIONAL_POINTER(loc, havelocationName, getlocationName, p, name)
		SIMPLE_RMAP_OPTIONAL_POINTER(loc, havelocationCode, getlocationCode, p, code)
		SIMPLE_RMAP_OPTIONAL_POINTER(loc, havelocationNote, getlocationNote, p, note)
		RMAP_TYPE_GROUP_GET_OPTIONAL(loc, havelocationTypeGroup, getlocationTypeGroup, (*p), location)

		// when valid, the weak reference to the coordinate will resolve properly and leave us with little work to be done
		if (loc->havecoordinateReference()) {
			ebucoreCoordinates *coords = loc->getcoordinateReference();
			std::auto_ptr<coordinates> pp( new coordinates(coords->getposX(), coords->getposY()) );
			RMAP_FORMAT_GROUP_GET_OPTIONAL(coords, havecoordinatesFormatGroup, getcoordinatesFormatGroup, (*pp), coordinates)
			p->coordinates(pp);
		}

		dest.location().push_back(p);
	}
}

void mapMetadataCoverage(ebucoreCoverage *source, coverageType& dest) {
	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havecoverageValue, getcoverageValue, coverageType::coverage_type, mapTextualAnnotation, dest, coverage)
	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havespatial, getspatial, spatial, mapSpatial, dest, spatial)
	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havetemporal, gettemporal, temporal, mapTemporal, dest, temporal)
}

void mapRights(ebucoreRights *source, rightsType& dest) {

	SIMPLE_RMAP_OPTIONAL(source, haverightsId, getrightsId, dest, rightsID)

	NEW_VECTOR_AND_RASSIGN_WITH_DC(source, getrightsAttributeID, rightsType::rightsAttributedId_type, rightsType::rightsAttributedId_sequence, 
		std::vector<ebucoreIdentifier*>, mapIdentifier, dest, rightsAttributedId)
	
	if (source->haverightsValue()) {
		NEW_VECTOR_AND_RASSIGN(source, getrightsValue, rightsType::rights_type, rightsType::rights_sequence, 
			std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, rights)
	}

	SIMPLE_RMAP_OPTIONAL(source, haverightsClearanceFlag, getrightsClearanceFlag, dest, rightsClearanceFlag)

	// resolve formats!
	if (source->haverightsFormatReferences()) {
		std::auto_ptr<rightsType::formatIDRefs_type> p( new rightsType::formatIDRefs_type() );
		const std::vector<ebucoreFormat*>& vec_refs = source->getrightsFormatReferences();
		for (std::vector<ebucoreFormat*>::const_iterator it = vec_refs.begin(); it != vec_refs.end(); it++) {
			if ((*it) != NULL) {
				std::auto_ptr<xml_schema::idref> pp( new xml_schema::idref((*it)->getformatID()) );
				p->push_back(pp);
			}
		}
		dest.formatIDRefs(p);
	}
	
	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, haveexploitationIssues, getexploitationIssues, rightsType::exploitationIssues_type, mapTextualAnnotation, dest, exploitationIssues)

	SIMPLE_RMAP_OPTIONAL(source, haverightsLink, getrightsLink, dest, rightsLink)

	// [FIX?] Updated cardinality
	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, haverightsCoverage, getrightsCoverage, coverageType, mapMetadataCoverage, dest, coverage)

	if (source->haverightsHolderEntity()) {
		NEW_VECTOR_AND_RASSIGN(source, getrightsHolderEntity, entityType, rightsType::rightsHolder_sequence, 
			std::vector<ebucoreEntity*>, mapEntity, dest, rightsHolder)
	}

	if (source->haverightsContacts()) {
		NEW_VECTOR_AND_RASSIGN(source, getrightsContacts, contactDetailsType, rightsType::contactDetails_sequence, std::vector<ebucoreContact*>, mapContact, dest, contactDetails)
	}

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, haverightsTypeGroup, getrightsTypeGroup, dest, rightsType)
}

void mapPublicationHistoryEvent(ebucorePublicationHistoryEvent* source, publicationEvent& dest) {

	SIMPLE_RMAP(source, getfirstPublicationFlag, dest, firstShowing)

	if (source->havepublicationDate()) {
		dest.publicationDate( std::auto_ptr<publicationEvent::publicationDate_type>( convert_timestamp_date(source->getpublicationDate())) );
	}
	if (source->havepublicationTime()) {
		dest.publicationTime( std::auto_ptr<publicationEvent::publicationTime_type>( convert_timestamp_time(source->getpublicationTime())) );
	}
	if (source->havepublicationChannel()) {
		dest.publicationChannel( std::auto_ptr<publicationEvent::publicationChannel_type>( new publicationEvent::publicationChannel_type(source->getpublicationChannel()) ) );
	}
	if (source->havepublicationService()) {
		dest.publicationService( std::auto_ptr<publicationEvent::publicationService_type>( new publicationEvent::publicationService_type(source->getpublicationService()) ) );
	}

	if (source->havepublicationMedium()) {
		std::auto_ptr<publicationMedium> p( new publicationMedium() );
		RMAP_TYPE_GROUP_GET_OPTIONAL(source, havepublicationMedium, getpublicationMedium, (*p), publicationMedium)
		dest.publicationMedium(p);
	}

	if (source->havepublicationFormatReference()) {
		ebucoreFormat *fmt =source->getpublicationFormatReference();
		if (fmt != NULL) {
			std::auto_ptr<publicationEvent::formatIdRef_type> p( new publicationEvent::formatIdRef_type(fmt->getformatID()) );
			dest.formatIdRef(p);
		}
	}
	//SIMPLE_RMAP_OPTIONAL_POINTER(event, havepublicationFormatIDRef, getpublicationFormatIDRef, p, formatIdRef)
}

void mapPublicationHistory(std::vector<ebucorePublicationHistoryEvent*>& source, publicationHistoryType& dest) {
	publicationHistoryType::publicationEvent_sequence vec_dest;
	for (std::vector<ebucorePublicationHistoryEvent*>::iterator it = source.begin(); it != source.end(); it++) {
		std::auto_ptr<publicationEvent> p( new publicationEvent() );
		mapPublicationHistoryEvent(*it, *p);
		vec_dest.push_back(p);
	}
	dest.publicationEvent(vec_dest);
}

#define RMAP_BASIC_RELATION_FUNCTION(sourceProperty) \
	void mapBasicRelation_##sourceProperty(ebucoreBasicRelation *source, relationType& dest, ObjectModifier* mod = NULL) { \
		SIMPLE_RMAP_OPTIONAL(source, have##sourceProperty, get##sourceProperty, dest, relationLink ) \
	}

RMAP_BASIC_RELATION_FUNCTION(isVersionOf)
RMAP_BASIC_RELATION_FUNCTION(hasVersion)
RMAP_BASIC_RELATION_FUNCTION(isReplacedBy)
RMAP_BASIC_RELATION_FUNCTION(replaces)
RMAP_BASIC_RELATION_FUNCTION(isRequiredBy)
RMAP_BASIC_RELATION_FUNCTION(requires)
RMAP_BASIC_RELATION_FUNCTION(isPartOf)
RMAP_BASIC_RELATION_FUNCTION(hasPart)
RMAP_BASIC_RELATION_FUNCTION(isReferencedBy)
RMAP_BASIC_RELATION_FUNCTION(references)
RMAP_BASIC_RELATION_FUNCTION(isFormatOf)
RMAP_BASIC_RELATION_FUNCTION(hasFormat)
RMAP_BASIC_RELATION_FUNCTION(isEpisodeOf)
RMAP_BASIC_RELATION_FUNCTION(isMemberOf)

void mapBasicRelation(ebucoreBasicRelation *source, coreMetadataType& dest) {
	std::auto_ptr<relationType> p( new relationType() );
	if (source->haveisVersionOf()) { mapBasicRelation_isVersionOf(source, *p); dest.isVersionOf().push_back(p); }
	if (source->havehasVersion()) { mapBasicRelation_hasVersion(source, *p); dest.hasVersion().push_back(p); }
	if (source->haveisReplacedBy()) { mapBasicRelation_isReplacedBy(source, *p); dest.isReplacedBy().push_back(p); }
	if (source->havereplaces()) { mapBasicRelation_replaces(source, *p); dest.replaces().push_back(p); }
	if (source->haveisRequiredBy()) { mapBasicRelation_isRequiredBy(source, *p); dest.isRequiredBy().push_back(p); }
	if (source->haverequires()) { mapBasicRelation_requires(source, *p); dest.requires().push_back(p); }
	if (source->haveisPartOf()) { mapBasicRelation_isPartOf(source, *p); dest.isPartOf().push_back(p); }
	if (source->havehasPart()) { mapBasicRelation_hasPart(source, *p); dest.hasPart().push_back(p); }
	if (source->haveisReferencedBy()) { mapBasicRelation_isReferencedBy(source, *p); dest.isReferencedBy().push_back(p); }
	if (source->havereferences()) { mapBasicRelation_references(source, *p); dest.references().push_back(p); }
	if (source->haveisFormatOf()) { mapBasicRelation_isFormatOf(source, *p); dest.isFormatOf().push_back(p); }
	if (source->havehasFormat()) { mapBasicRelation_hasFormat(source, *p); dest.hasFormat().push_back(p); }
	if (source->haveisEpisodeOf()) { mapBasicRelation_isEpisodeOf(source, *p); dest.isEpisodeOf().push_back(p); }
	if (source->haveisMemberOf()) { mapBasicRelation_isMemberOf(source, *p); dest.isMemberOf().push_back(p); }
}

void mapCustomRelation(ebucoreCustomRelation *source, relationType& dest) {
	SIMPLE_RMAP_OPTIONAL(source, haverelationByName, getrelationByName, dest, relation)
	SIMPLE_RMAP_OPTIONAL(source, haverelationLink, getrelationLink, dest, relationLink)
	SIMPLE_RMAP_OPTIONAL(source, haverunningOrderNumber, getrunningOrderNumber, dest, runningOrderNumber)
	SIMPLE_RMAP_OPTIONAL(source, havetotalNumberOfGroupMembers, gettotalNumberOfGroupMembers, dest, totalNumberOfGroupMembers)
	SIMPLE_RMAP_OPTIONAL(source, haveorderedGroupFlag, getorderedGroupFlag, dest, orderedGroupFlag)
	if (source->havecustomRelationTypeGroup()) { // make this field required just like other typegroups??
		RMAP_TYPE_GROUP_GET_OPTIONAL(source, havecustomRelationTypeGroup, getcustomRelationTypeGroup, dest, relationType)
	}
	if (source->haverelationIdentifier()) {
		std::auto_ptr<dc::elementType> dcp( new dc::elementType() );
		std::auto_ptr<identifierType> p( new identifierType(dcp) );
		mapIdentifier(source->getrelationIdentifier(), *p);
	}
}

#define RMAP_TECHNICAL_ATTRIBUTE_FUNCTION(functionName, sourceType, sourceProperty, destType) \
	void functionName(sourceType *source, destType& dest) { \
		dest = source->sourceProperty();	\
		RMAP_TYPE_GROUP(source, dest, destType::typeDefinition_type, destType::typeLabel_type, destType::typeLink_type, destType::typeLanguage_type)	\
	}

RMAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeString, ebucoreTechnicalAttributeString, gettechnicalAttributeStringValue, String)
RMAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeInt8, ebucoreTechnicalAttributeInt8, gettechnicalAttributeInt8Value, Int8)
RMAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeInt16, ebucoreTechnicalAttributeInt16, gettechnicalAttributeInt16Value, Int16)
RMAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeInt32, ebucoreTechnicalAttributeInt32, gettechnicalAttributeInt32Value, Int32)
RMAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeInt64, ebucoreTechnicalAttributeInt64, gettechnicalAttributeInt64Value, Int64)
RMAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeUInt8, ebucoreTechnicalAttributeUInt8, gettechnicalAttributeUInt8Value, UInt8)
RMAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeUInt16, ebucoreTechnicalAttributeUInt16, gettechnicalAttributeUInt16Value, UInt16)
RMAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeUInt32, ebucoreTechnicalAttributeUInt32, gettechnicalAttributeUInt32Value, UInt32)
RMAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeUInt64, ebucoreTechnicalAttributeUInt64, gettechnicalAttributeUInt64Value, UInt64)
RMAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeFloat, ebucoreTechnicalAttributeFloat, gettechnicalAttributeFloatValue, Float)
RMAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeBoolean, ebucoreTechnicalAttributeBoolean, gettechnicalAttributeBooleanValue, Boolean)

void mapTechnicalAttributeRational(ebucoreTechnicalAttributeRational *source, technicalAttributeRationalType& dest) {
	mxfRational r = source->gettechnicalAttributeRationalValue();
	dest.factorNumerator() = r.numerator;
	dest.factorDenominator() = r.denominator;
	RMAP_TYPE_GROUP(source, dest, technicalAttributeRationalType::typeDefinition_type, technicalAttributeRationalType::typeLabel_type, technicalAttributeRationalType::typeLink_type, technicalAttributeRationalType::typeLanguage_type)
}

void mapTechnicalAttributeAnyURI(ebucoreTechnicalAttributeAnyURI *source, technicalAttributeUriType& dest) {
	dest.assign(source->gettechnicalAttributeAnyURIValue()); // use assign as no more convenient operator works
	RMAP_TYPE_GROUP(source, dest, technicalAttributeUriType::typeDefinition_type, technicalAttributeUriType::typeLabel_type, technicalAttributeUriType::typeLink_type, technicalAttributeUriType::typeLanguage_type)
}

void mapMIMEType(ebucoreMimeType *source, mimeType& dest) {
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havemimeTypeGroup, getmimeTypeGroup, dest, mimeType)
}

void mapContainerFormat(ebucoreContainerFormat *source, formatType::containerFormat_type& dest) {
	RMAP_FORMAT_GROUP_GET_OPTIONAL(source, havecontainerFormatGroup, getcontainerFormatGroup, dest, formatType::containerFormat_type)
}

void mapMedium(ebucoreMedium *source, medium& dest) {
	SIMPLE_RMAP_OPTIONAL(source, havemediumID, getmediumID, dest, mediumId)
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havemediumTypeGroup, getmediumTypeGroup, dest, medium)
}

void mapLocator(ebucoreLocator *source, formatType::locator_type& dest) {
	// [TODO] In XSD, provide a locator string that can be mapped to the KLV locatorLocation field
	//SIMPLE_RMAP(source, getlocatorLocation, dest, <<locator value>>

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havelocatorTypeGroup, getlocatorTypeGroup , dest, formatType::locator_type)
}

void mapPackageInfo(ebucorePackageInfo *source, formatType& dest) {
	SIMPLE_RMAP_OPTIONAL(source, havepackageName, getpackageName, dest, fileName)
	SIMPLE_RMAP_OPTIONAL(source, havepackageSize, getpackageSize, dest, fileSize)

	NEW_VECTOR_AND_RASSIGN(source, getpackageLocator, formatType::locator_type, formatType::locator_sequence, std::vector<ebucoreLocator*>, mapLocator, dest, locator)
}

void mapSigningFormat(ebucoreSigningFormat *source, signingFormat& dest) {
	SIMPLE_RMAP_OPTIONAL(source, havesigningTrackID, getsigningTrackID, dest, trackId)
	SIMPLE_RMAP_OPTIONAL(source, havesigningTrackName, getsigningTrackName, dest, trackName)
	SIMPLE_RMAP_OPTIONAL(source, havesigningTrackLanguageCode, getsigningTrackLanguageCode, dest, language)
	SIMPLE_RMAP_OPTIONAL(source, havesigningTrackLanguageName, getsigningTrackLanguageName, dest, language)
	SIMPLE_RMAP_OPTIONAL(source, havesigningSourceUri, getsigningSourceUri, dest, signingSourceUri)


	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havesigningTypeGroup, getsigningTypeGroup, dest, signingFormat)
	RMAP_FORMAT_GROUP_GET_OPTIONAL(source, havesigningFormatGroup, getsigningFormatGroup, dest, signingFormat)
}

void mapCodec(ebucoreCodec *source, codecType& dest) {
	SIMPLE_RMAP_OPTIONAL(source, havename, getname, dest, name)
	SIMPLE_RMAP_OPTIONAL(source, havevendor, getvendor, dest, vendor)
	SIMPLE_RMAP_OPTIONAL(source, haveversion, getversion, dest, version)
	SIMPLE_RMAP_OPTIONAL(source, havefamily, getfamily, dest, family)
	// [TODO] XSD Codec identifier is an identifiertype, KLV is string
	//SIMPLE_RMAP_OPTIONAL(source, codecIdentifier, dest, setcodecIdentifier)
}

void mapAudioTrack(ebucoreTrack *source, audioTrack& dest) {
	SIMPLE_RMAP_OPTIONAL(source, havetrackID, gettrackID, dest, trackId)
	SIMPLE_RMAP_OPTIONAL(source, havetrackName, gettrackName, dest, trackName)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havetrackTypeGroup, gettrackTypeGroup, dest, audioTrack)
}

void mapVideoTrack(ebucoreTrack *source, videoTrack& dest) {
	SIMPLE_RMAP_OPTIONAL(source, havetrackID, gettrackID, dest, trackId)
	SIMPLE_RMAP_OPTIONAL(source, havetrackName, gettrackName, dest, trackName)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havetrackTypeGroup, gettrackTypeGroup, dest, videoTrack)
}

void mapAudioEncoding(ebucoreEncoding *source, audioFormatType::audioEncoding_type& dest) {
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, haveencodingTypeGroup, getencodingTypeGroup, dest, audioFormatType::audioEncoding_type)
}

xml_schema::long_ convert(mxfRational source) {
	return source.numerator;
}

void mapAudioFormat(ebucoreAudioFormat *source, audioFormatType& dest) {
	SIMPLE_RMAP_OPTIONAL(source, haveaudioFormatID, getaudioFormatID, dest, audioFormatId)
	SIMPLE_RMAP_OPTIONAL(source, haveaudioFormatName, getaudioFormatName, dest, audioFormatName)
	SIMPLE_RMAP_OPTIONAL(source, haveaudioFormatDefinition, getaudioFormatDefinition, dest, audioFormatDefinition)

	std::auto_ptr<audioTrackConfiguration> p( new audioTrackConfiguration() );
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, haveaudioTrackConfiguration, getaudioTrackConfiguration, (*p), audioTrackConfiguration)
	dest.audioTrackConfiguration(p);

	SIMPLE_RMAP_OPTIONAL(source, haveaudioSamplingSize, getaudioSamplingSize, dest, sampleSize)
	SIMPLE_RMAP_OPTIONAL(source, haveaudioSamplingType, getaudioSamplingType, dest, sampleType)
	SIMPLE_RMAP_OPTIONAL(source, haveaudioTotalNumberOfChannels, getaudioTotalNumberOfChannels, dest, channels)
	SIMPLE_RMAP_OPTIONAL(source, haveaudioBitRate, getaudioBitRate, dest, bitRate)
	SIMPLE_RMAP_OPTIONAL(source, haveaudioBitRateMode, getaudioBitRateMode, dest, bitRateMode)
	SIMPLE_RMAP_OPTIONAL_CONVERT(source, haveaudioSamplingRate, getaudioSamplingRate, dest, samplingRate, convert)

	NEW_VECTOR_AND_RASSIGN(source, getaudioEncoding, audioEncoding, audioFormatType::audioEncoding_sequence, std::vector<ebucoreEncoding*>, mapAudioEncoding, dest, audioEncoding)
	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, haveaudioCodec, getaudioCodec, codecType, mapCodec, dest, codec)
	NEW_VECTOR_AND_RASSIGN(source, getaudioTrack, audioTrack, audioFormatType::audioTrack_sequence, std::vector<ebucoreTrack*>, mapAudioTrack, dest, audioTrack)

	NEW_VECTOR_AND_RASSIGN(source, getaudioTechnicalAttributeString, String, audioFormatType::technicalAttributeString_sequence, 
		std::vector<ebucoreTechnicalAttributeString*>, mapTechnicalAttributeString, dest, technicalAttributeString)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getaudioTechnicalAttributeInt8, Int8, audioFormatType::technicalAttributeByte_sequence, 
		std::vector<ebucoreTechnicalAttributeInt8*>, mapTechnicalAttributeInt8, dest, technicalAttributeByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getaudioTechnicalAttributeInt16, Int16, audioFormatType::technicalAttributeShort_sequence, 
		std::vector<ebucoreTechnicalAttributeInt16*>, mapTechnicalAttributeInt16, dest, technicalAttributeShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getaudioTechnicalAttributeInt32, Int32, audioFormatType::technicalAttributeInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeInt32*>, mapTechnicalAttributeInt32, dest, technicalAttributeInteger, 0 /* initialize value as 0, will be replaced by mapping method */)	
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getaudioTechnicalAttributeInt64, Int64, audioFormatType::technicalAttributeLong_sequence, 
		std::vector<ebucoreTechnicalAttributeInt64*>, mapTechnicalAttributeInt64, dest, technicalAttributeLong, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getaudioTechnicalAttributeUInt8, UInt8, audioFormatType::technicalAttributeUnsignedByte_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt8*>, mapTechnicalAttributeUInt8, dest, technicalAttributeUnsignedByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getaudioTechnicalAttributeUInt16, UInt16, audioFormatType::technicalAttributeUnsignedShort_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt16*>, mapTechnicalAttributeUInt16, dest, technicalAttributeUnsignedShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getaudioTechnicalAttributeUInt32, UInt32, audioFormatType::technicalAttributeUnsignedInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt32*>, mapTechnicalAttributeUInt32, dest, technicalAttributeUnsignedInteger, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getaudioTechnicalAttributeUInt64, UInt64, audioFormatType::technicalAttributeUnsignedLong_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt64*>, mapTechnicalAttributeUInt64, dest, technicalAttributeUnsignedLong, 0 /* initialize value as 0, will be replaced by mapping method */)

	NEW_VECTOR_AND_RASSIGN_CARGS(source, getaudioTechnicalAttributeFloat, Float, audioFormatType::technicalAttributeFloat_sequence, 
		std::vector<ebucoreTechnicalAttributeFloat*>, mapTechnicalAttributeFloat, dest, technicalAttributeFloat, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getaudioTechnicalAttributeRational, technicalAttributeRationalType, audioFormatType::technicalAttributeRational_sequence, 
		std::vector<ebucoreTechnicalAttributeRational*>, mapTechnicalAttributeRational, dest, technicalAttributeRational, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getaudioTechnicalAttributeBoolean, Boolean, audioFormatType::technicalAttributeBoolean_sequence, 
		std::vector<ebucoreTechnicalAttributeBoolean*>, mapTechnicalAttributeBoolean, dest, technicalAttributeBoolean, false /* initialize value as false, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getaudioTechnicalAttributeAnyURI, technicalAttributeUriType, audioFormatType::technicalAttributeUri_sequence, 
		std::vector<ebucoreTechnicalAttributeAnyURI*>, mapTechnicalAttributeAnyURI, dest, technicalAttributeUri, "" /* initialize value as "", will be replaced by mapping method */)
}

void mapImageEncoding(ebucoreEncoding *source, imageFormatType::imageEncoding_type& dest) {
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, haveencodingTypeGroup, getencodingTypeGroup, dest, imageFormatType::imageEncoding_type)
}

void mapAspectRatio(ebucoreAspectRatio *source, aspectRatioType& dest) {
	SIMPLE_RMAP(source, getaspectRatioFactorNumerator, dest, factorNumerator)
	SIMPLE_RMAP(source, getaspectRatioFactorDenominator, dest, factorDenominator)
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, haveaspectRatioTypeGroup, getaspectRatioTypeGroup, dest, aspectRatioType)
}

void mapDimension(ebucoreDimension *source, lengthType& dest) {
	dest = source->getdimensionValue();
	SIMPLE_RMAP_OPTIONAL(source, havedimensionUnit, getdimensionUnit, dest, unit)
}

void mapImageFormat(ebucoreImageFormat *source, imageFormatType& dest) {

	SIMPLE_RMAP_OPTIONAL(source, haveimageFormatID, getimageFormatID, dest, imageFormatId)
	SIMPLE_RMAP_OPTIONAL(source, haveimageFormatName, getimageFormatName, dest, imageFormatName)
	SIMPLE_RMAP_OPTIONAL(source, haveimageFormatDefinition, getimageFormatDefinition, dest, imageFormatDefinition)

	SIMPLE_RMAP_OPTIONAL(source, haveimageOrientation, getimageOrientation, dest, orientation)
	
	if (source->haveimageAspectRatio()) {
		std::auto_ptr<aspectRatioType> p( new aspectRatioType(1,1) );
		mapAspectRatio(source->getimageAspectRatio(), *p);
		dest.aspectRatio(p);
	}

	NEW_VECTOR_AND_RASSIGN(source, getimageEncoding, imageEncoding, imageFormatType::imageEncoding_sequence, 
		std::vector<ebucoreEncoding*>, mapImageEncoding, dest, imageEncoding)

	/* [TODO] XSD is missing image codec
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, codec, ebucoreCodec, mapCodec, dest, setimageCodec) */

	NEW_OBJECT_AND_RASSIGN_OPTIONAL_CARGS(source, haveimageWidth, getimageWidth, lengthType, mapDimension, dest, width, 0) 
	NEW_OBJECT_AND_RASSIGN_OPTIONAL_CARGS(source, haveimageHeight, getimageHeight, lengthType, mapDimension, dest, height, 0) 

	NEW_VECTOR_AND_RASSIGN(source, getimageTechnicalAttributeString, String, imageFormatType::technicalAttributeString_sequence, 
		std::vector<ebucoreTechnicalAttributeString*>, mapTechnicalAttributeString, dest, technicalAttributeString)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getimageTechnicalAttributeInt8, Int8, imageFormatType::technicalAttributeByte_sequence, 
		std::vector<ebucoreTechnicalAttributeInt8*>, mapTechnicalAttributeInt8, dest, technicalAttributeByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getimageTechnicalAttributeInt16, Int16, imageFormatType::technicalAttributeShort_sequence, 
		std::vector<ebucoreTechnicalAttributeInt16*>, mapTechnicalAttributeInt16, dest, technicalAttributeShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getimageTechnicalAttributeInt32, Int32, imageFormatType::technicalAttributeInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeInt32*>, mapTechnicalAttributeInt32, dest, technicalAttributeInteger, 0 /* initialize value as 0, will be replaced by mapping method */)	
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getimageTechnicalAttributeInt64, Int64, imageFormatType::technicalAttributeLong_sequence, 
		std::vector<ebucoreTechnicalAttributeInt64*>, mapTechnicalAttributeInt64, dest, technicalAttributeLong, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getimageTechnicalAttributeUInt8, UInt8, imageFormatType::technicalAttributeUnsignedByte_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt8*>, mapTechnicalAttributeUInt8, dest, technicalAttributeUnsignedByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getimageTechnicalAttributeUInt16, UInt16, imageFormatType::technicalAttributeUnsignedShort_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt16*>, mapTechnicalAttributeUInt16, dest, technicalAttributeUnsignedShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getimageTechnicalAttributeUInt32, UInt32, imageFormatType::technicalAttributeUnsignedInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt32*>, mapTechnicalAttributeUInt32, dest, technicalAttributeUnsignedInteger, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getimageTechnicalAttributeUInt64, UInt64, imageFormatType::technicalAttributeUnsignedLong_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt64*>, mapTechnicalAttributeUInt64, dest, technicalAttributeUnsignedLong, 0 /* initialize value as 0, will be replaced by mapping method */)

	NEW_VECTOR_AND_RASSIGN_CARGS(source, getimageTechnicalAttributeFloat, Float, imageFormatType::technicalAttributeFloat_sequence, 
		std::vector<ebucoreTechnicalAttributeFloat*>, mapTechnicalAttributeFloat, dest, technicalAttributeFloat, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getimageTechnicalAttributeRational, technicalAttributeRationalType, imageFormatType::technicalAttributeRational_sequence, 
		std::vector<ebucoreTechnicalAttributeRational*>, mapTechnicalAttributeRational, dest, technicalAttributeRational, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getimageTechnicalAttributeBoolean, Boolean, imageFormatType::technicalAttributeBoolean_sequence, 
		std::vector<ebucoreTechnicalAttributeBoolean*>, mapTechnicalAttributeBoolean, dest, technicalAttributeBoolean, false /* initialize value as false, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getimageTechnicalAttributeAnyURI, technicalAttributeUriType, imageFormatType::technicalAttributeUri_sequence, 
		std::vector<ebucoreTechnicalAttributeAnyURI*>, mapTechnicalAttributeAnyURI, dest, technicalAttributeUri, "" /* initialize value as "", will be replaced by mapping method */)
}

void mapVideoEncoding(ebucoreEncoding *source, videoFormatType::videoEncoding_type& dest) {
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, haveencodingTypeGroup, getencodingTypeGroup, dest, videoFormatType::videoEncoding_type)
}

rationalType convert_rational(mxfRational source) {
	rationalType r(1);
	r.factorNumerator() = source.numerator;
	r.factorDenominator() = source.denominator;
	return r;
}

void mapVideoFormat(ebucoreVideoFormat *source, videoFormatType& dest) {

	SIMPLE_RMAP_OPTIONAL(source, havevideoFormatID, getvideoFormatID, dest, videoFormatId)
	SIMPLE_RMAP_OPTIONAL(source, havevideoFormatName, getvideoFormatName, dest, videoFormatName)
	SIMPLE_RMAP_OPTIONAL(source, havevideoFormatDefinition, getvideoFormatDefinition, dest, videoFormatDefinition)

	SIMPLE_RMAP_OPTIONAL(source, havevideoBitRate, getvideoBitRate, dest, bitRate)
	SIMPLE_RMAP_OPTIONAL(source, havevideoBitRateMode, getvideoBitRateMode, dest, bitRateMode)
	SIMPLE_RMAP_OPTIONAL(source, havevideoSamplingFormat, getvideoSamplingFormat, dest, scanningFormat)
	SIMPLE_RMAP_OPTIONAL(source, havevideoScanningOrder, getvideoScanningOrder, dest, scanningOrder)
	SIMPLE_RMAP_OPTIONAL(source, havevideoActiveLines, getvideoActiveLines, dest, lines)
	SIMPLE_RMAP_OPTIONAL(source, havevideoNoiseFilterFlag, getvideoNoiseFilterFlag, dest, noiseFilter)
	
	if (source->havevideoAspectRatio()) {
		std::auto_ptr<aspectRatioType> p( new aspectRatioType(1,1) );
		mapAspectRatio(source->getvideoAspectRatio(), *p);
		dest.aspectRatio(p);
	}
	SIMPLE_RMAP_OPTIONAL_CONVERT(source, havevideoFrameRate, getvideoFrameRate, dest, frameRate, convert_rational)

	NEW_OBJECT_AND_RASSIGN_OPTIONAL_CARGS(source, havevideoWidth, getvideoWidth, lengthType, mapDimension, dest, width, 0) 
	NEW_OBJECT_AND_RASSIGN_OPTIONAL_CARGS(source, havevideoHeight, getvideoHeight, lengthType, mapDimension, dest, height, 0)

	NEW_VECTOR_AND_RASSIGN(source, getvideoEncoding, videoEncoding, videoFormatType::videoEncoding_sequence, std::vector<ebucoreEncoding*>, mapVideoEncoding, dest, videoEncoding)
	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havevideoCodectype, getvideoCodectype, codecType, mapCodec, dest, codec)
	NEW_VECTOR_AND_RASSIGN(source, getvideoTrack, videoTrack, videoFormatType::videoTrack_sequence, std::vector<ebucoreTrack*>, mapVideoTrack, dest, videoTrack)

	NEW_VECTOR_AND_RASSIGN(source, getvideoTechnicalAttributeString, String, videoFormatType::technicalAttributeString_sequence, 
		std::vector<ebucoreTechnicalAttributeString*>, mapTechnicalAttributeString, dest, technicalAttributeString)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getvideoTechnicalAttributeInt8, Int8, videoFormatType::technicalAttributeByte_sequence, 
		std::vector<ebucoreTechnicalAttributeInt8*>, mapTechnicalAttributeInt8, dest, technicalAttributeByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getvideoTechnicalAttributeInt16, Int16, videoFormatType::technicalAttributeShort_sequence, 
		std::vector<ebucoreTechnicalAttributeInt16*>, mapTechnicalAttributeInt16, dest, technicalAttributeShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getvideoTechnicalAttributeInt32, Int32, videoFormatType::technicalAttributeInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeInt32*>, mapTechnicalAttributeInt32, dest, technicalAttributeInteger, 0 /* initialize value as 0, will be replaced by mapping method */)	
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getvideoTechnicalAttributeInt64, Int64, videoFormatType::technicalAttributeLong_sequence, 
		std::vector<ebucoreTechnicalAttributeInt64*>, mapTechnicalAttributeInt64, dest, technicalAttributeLong, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getvideoTechnicalAttributeUInt8, UInt8, videoFormatType::technicalAttributeUnsignedByte_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt8*>, mapTechnicalAttributeUInt8, dest, technicalAttributeUnsignedByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getvideoTechnicalAttributeUInt16, UInt16, videoFormatType::technicalAttributeUnsignedShort_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt16*>, mapTechnicalAttributeUInt16, dest, technicalAttributeUnsignedShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getvideoTechnicalAttributeUInt32, UInt32, videoFormatType::technicalAttributeUnsignedInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt32*>, mapTechnicalAttributeUInt32, dest, technicalAttributeUnsignedInteger, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getvideoTechnicalAttributeUInt64, UInt64, videoFormatType::technicalAttributeUnsignedLong_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt64*>, mapTechnicalAttributeUInt64, dest, technicalAttributeUnsignedLong, 0 /* initialize value as 0, will be replaced by mapping method */)

	NEW_VECTOR_AND_RASSIGN_CARGS(source, getvideoTechnicalAttributeFloat, Float, videoFormatType::technicalAttributeFloat_sequence, 
		std::vector<ebucoreTechnicalAttributeFloat*>, mapTechnicalAttributeFloat, dest, technicalAttributeFloat, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getvideoTechnicalAttributeRational, technicalAttributeRationalType, videoFormatType::technicalAttributeRational_sequence, 
		std::vector<ebucoreTechnicalAttributeRational*>, mapTechnicalAttributeRational, dest, technicalAttributeRational, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getvideoTechnicalAttributeBoolean, Boolean, videoFormatType::technicalAttributeBoolean_sequence, 
		std::vector<ebucoreTechnicalAttributeBoolean*>, mapTechnicalAttributeBoolean, dest, technicalAttributeBoolean, false /* initialize value as false, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getvideoTechnicalAttributeAnyURI, technicalAttributeUriType, videoFormatType::technicalAttributeUri_sequence, 
		std::vector<ebucoreTechnicalAttributeAnyURI*>, mapTechnicalAttributeAnyURI, dest, technicalAttributeUri, "" /* initialize value as "", will be replaced by mapping method */)
}

void mapCaptioning(ebucoreCaptioning* source, captioningFormat& dest) {
	SIMPLE_RMAP_OPTIONAL(source, havecaptioningFormatID, getcaptioningFormatID, dest, captioningFormatId)
	SIMPLE_RMAP_OPTIONAL(source, havecaptioningFormatName, getcaptioningFormatName, dest, captioningFormatName)
	SIMPLE_RMAP_OPTIONAL(source, havecaptioningFormatDefinition, getcaptioningFormatDefinition, dest, formatDefinition)
	SIMPLE_RMAP_OPTIONAL(source, havecaptioningSourceUri, getcaptioningSourceUri, dest, captioningSourceUri)
	SIMPLE_RMAP_OPTIONAL(source, havecaptioningLanguageCode, getcaptioningLanguageCode, dest, language)
	SIMPLE_RMAP_OPTIONAL(source, havecaptioningLanguageName, getcaptioningLanguageName, dest, language)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havecaptioningTypeGroup, getcaptioningTypeGroup, dest, captioningFormat)
}

void mapAncillaryData(ebucoreAncillaryData* source, ancillaryDataFormat& dest) {
	SIMPLE_RMAP_OPTIONAL(source, haveDID, getDID, dest, DID)
	SIMPLE_RMAP_OPTIONAL(source, haveSDID, getSDID, dest, SDID)

	ancillaryDataFormat::lineNumber_sequence destLines;
	if (source->havelineNumber()) {
		const std::vector<uint32_t>& lines = source->getlineNumber();
		for (std::vector<uint32_t>::const_iterator it = lines.begin(); it != lines.end(); it++) {
			destLines.push_back(*it);
		}
		dest.lineNumber(destLines);
	}

	if (source->haveANCWrappingType()) {
		ebucoreTypeGroup *tg = source->getANCWrappingType();

		if (tg->havetypeGroupLabel()) {
			dest.ancillaryDataFormatName() = tg->gettypeGroupLabel();
		}
		if (tg->havetypeGroupLabel()) {
			dest.ancillaryDataFormatId() = tg->gettypeGroupLabel();
		}	
		if (tg->havetypeGroupLink()) {
			dest.wrappingType() = convert_to_int(tg->gettypeGroupDefinition());
		}
	}
}

void mapDataFormat(ebucoreDataFormat *source, dataFormatType& dest) {

	SIMPLE_RMAP_OPTIONAL(source, havedataFormatID, getdataFormatID, dest, dataFormatId)
	SIMPLE_RMAP_OPTIONAL(source, havedataFormatName, getdataFormatName, dest, dataFormatName)
	SIMPLE_RMAP_OPTIONAL(source, havedataFormatDefinition, getdataFormatDefinition, dest, dataFormatDefinition)

	NEW_VECTOR_AND_RASSIGN(source, getcaptioning, captioningFormat, dataFormatType::captioningFormat_sequence, std::vector<ebucoreCaptioning*>, mapCaptioning, dest, captioningFormat)
	NEW_VECTOR_AND_RASSIGN(source, getancillaryData, ancillaryDataFormat, dataFormatType::ancillaryDataFormat_sequence, std::vector<ebucoreAncillaryData*>, mapAncillaryData, dest, ancillaryDataFormat)

	NEW_VECTOR_AND_RASSIGN(source, getdataTechnicalAttributeString, String, dataFormatType::technicalAttributeString_sequence, 
		std::vector<ebucoreTechnicalAttributeString*>, mapTechnicalAttributeString, dest, technicalAttributeString)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getdataTechnicalAttributeInt8, Int8, dataFormatType::technicalAttributeByte_sequence, 
		std::vector<ebucoreTechnicalAttributeInt8*>, mapTechnicalAttributeInt8, dest, technicalAttributeByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getdataTechnicalAttributeInt16, Int16, dataFormatType::technicalAttributeShort_sequence, 
		std::vector<ebucoreTechnicalAttributeInt16*>, mapTechnicalAttributeInt16, dest, technicalAttributeShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getdataTechnicalAttributeInt32, Int32, dataFormatType::technicalAttributeInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeInt32*>, mapTechnicalAttributeInt32, dest, technicalAttributeInteger, 0 /* initialize value as 0, will be replaced by mapping method */)	
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getdataTechnicalAttributeInt64, Int64, dataFormatType::technicalAttributeLong_sequence, 
		std::vector<ebucoreTechnicalAttributeInt64*>, mapTechnicalAttributeInt64, dest, technicalAttributeLong, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getdataTechnicalAttributeUInt8, UInt8, dataFormatType::technicalAttributeUnsignedByte_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt8*>, mapTechnicalAttributeUInt8, dest, technicalAttributeUnsignedByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getdataTechnicalAttributeUInt16, UInt16, dataFormatType::technicalAttributeUnsignedShort_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt16*>, mapTechnicalAttributeUInt16, dest, technicalAttributeUnsignedShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getdataTechnicalAttributeUInt32, UInt32, dataFormatType::technicalAttributeUnsignedInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt32*>, mapTechnicalAttributeUInt32, dest, technicalAttributeUnsignedInteger, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getdataTechnicalAttributeUInt64, UInt64, dataFormatType::technicalAttributeUnsignedLong_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt64*>, mapTechnicalAttributeUInt64, dest, technicalAttributeUnsignedLong, 0 /* initialize value as 0, will be replaced by mapping method */)

	NEW_VECTOR_AND_RASSIGN_CARGS(source, getdataTechnicalAttributeFloat, Float, dataFormatType::technicalAttributeFloat_sequence, 
		std::vector<ebucoreTechnicalAttributeFloat*>, mapTechnicalAttributeFloat, dest, technicalAttributeFloat, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getdataTechnicalAttributeRational, technicalAttributeRationalType, dataFormatType::technicalAttributeRational_sequence, 
		std::vector<ebucoreTechnicalAttributeRational*>, mapTechnicalAttributeRational, dest, technicalAttributeRational, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getdataTechnicalAttributeBoolean, Boolean, dataFormatType::technicalAttributeBoolean_sequence, 
		std::vector<ebucoreTechnicalAttributeBoolean*>, mapTechnicalAttributeBoolean, dest, technicalAttributeBoolean, false /* initialize value as false, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getdataTechnicalAttributeAnyURI, technicalAttributeUriType, dataFormatType::technicalAttributeUri_sequence, 
		std::vector<ebucoreTechnicalAttributeAnyURI*>, mapTechnicalAttributeAnyURI, dest, technicalAttributeUri, "" /* initialize value as "", will be replaced by mapping method */)


}

xml_schema::duration* convert_duration(mxfRational source) {
	double seconds = source.numerator / source.numerator;
	int minutes = (int)seconds / 60;
	int hours = minutes / 60;
	int days = hours / 24;
	int months = days / 30;
	int years = months / 12;
	return new xml_schema::duration(false, years, months, days, hours, minutes, seconds);
}

xml_schema::time* convert_time(mxfRational source) {
	double seconds = source.numerator / source.numerator;
	int minutes = (int)seconds / 60;
	int hours = minutes / 60;
	return new xml_schema::time(hours, minutes, seconds);
}

void mapFormat(ebucoreFormat *source, formatType& dest) {

	SIMPLE_RMAP_OPTIONAL(source, haveformatID, getformatID, dest, formatId)
	SIMPLE_RMAP_OPTIONAL(source, haveformatVersionID, getformatVersionID, dest, formatVersionId)
	SIMPLE_RMAP_OPTIONAL(source, haveformatName, getformatName, dest, formatName)
	SIMPLE_RMAP_OPTIONAL(source, haveformatDefinition, getformatDefinition, dest, formatDefinition)
	
	if (source->haveformatDateCreated() || source->haveformatYearCreated()) {
		std::auto_ptr<dateCreated> p( new dateCreated() );
		if (source->haveformatDateCreated()) {
			p->startDate( std::auto_ptr<xml_schema::date>( convert_timestamp_date( source->getformatDateCreated() ) ) );
		}
		if (source->haveformatYearCreated()) {
			p->startYear( std::auto_ptr<xml_schema::gyear>( convert_timestamp_year( source->getformatYearCreated() ) ) );
		}
	}

	if (source->haveoverallDurationEditUnit() || source->haveoverallDurationTime() || source->haveoverallDurationTimecode()) {
		std::auto_ptr<durationType> p( new durationType() );
		if (source->haveoverallDurationEditUnit()) {
			p->editUnitNumber() = source->getoverallDurationEditUnit();
		}
		if (source->haveoverallDurationTimecode()) {
			p->timecode() = source->getoverallDurationTimecode();
		}
		if (source->haveoverallDurationTime()) {
			std::auto_ptr<durationType::normalPlayTime_type> pp( convert_duration(source->getoverallDurationTime()) );
			p->normalPlayTime(pp);
		}
		dest.duration(p);
	}

	if (source->haveoverallStartEditUnit() || source->haveoverallStartTime() || source->haveoverallStartTimecode()) {
		std::auto_ptr<timeType> p( new timeType() );
		if (source->haveoverallStartEditUnit()) {
			p->editUnitNumber() = source->getoverallStartEditUnit();
		}
		if (source->haveoverallStartTimecode()) {
			p->timecode() = source->getoverallStartTimecode();
		}
		if (source->haveoverallStartTime()) {
			std::auto_ptr<timeType::normalPlayTime_type> pp( convert_time(source->getoverallStartTime()) );
			p->normalPlayTime(pp);
		}
		dest.start(p);
	}
	if (source->haveoverallEndEditUnit() || source->haveoverallEndTime() || source->haveoverallEndTimecode()) {
		std::auto_ptr<timeType> p( new timeType() );
		if (source->haveoverallEndEditUnit()) {
			p->editUnitNumber() = source->getoverallEndEditUnit();
		}
		if (source->haveoverallEndTimecode()) {
			p->timecode() = source->getoverallEndTimecode();
		}
		if (source->haveoverallEndTime()) {
			std::auto_ptr<timeType::normalPlayTime_type> pp( convert_time(source->getoverallEndTime()) );
			p->normalPlayTime(pp);
		}
		dest.end(p);
	}

	NEW_VECTOR_AND_RASSIGN(source, getcontainerFormat, containerFormat, formatType::containerFormat_sequence, std::vector<ebucoreContainerFormat*>, 
		mapContainerFormat, dest, containerFormat)
	NEW_VECTOR_AND_RASSIGN(source, getmedium, medium, formatType::medium_sequence, std::vector<ebucoreMedium*>, 
		mapMedium, dest, medium)
	
	if (source->havepackageInfo()) {
		mapPackageInfo(source->getpackageInfo(), dest);
	}

	NEW_VECTOR_AND_RASSIGN(source, getmimeType, mimeType, formatType::mimeType_sequence, std::vector<ebucoreMimeType*>, 
		mapMIMEType, dest, mimeType)

	NEW_VECTOR_AND_RASSIGN(source, getmaterialAudioFormat, audioFormatType, formatType::audioFormat_sequence, std::vector<ebucoreAudioFormat*>, 
		mapAudioFormat, dest, audioFormat)
	NEW_VECTOR_AND_RASSIGN(source, getmaterialVideoFormat, videoFormatType, formatType::videoFormat_sequence, std::vector<ebucoreVideoFormat*>, 
		mapVideoFormat, dest, videoFormat)
	NEW_VECTOR_AND_RASSIGN(source, getmaterialImageFormat, imageFormatType, formatType::imageFormat_sequence, std::vector<ebucoreImageFormat*>, 
		mapImageFormat, dest, imageFormat)
	NEW_VECTOR_AND_RASSIGN(source, getmaterialDataFormat, dataFormatType, formatType::dataFormat_sequence, std::vector<ebucoreDataFormat*>, 
		mapDataFormat, dest, dataFormat)
	NEW_VECTOR_AND_RASSIGN(source, getmaterialSigningFormat, signingFormat, formatType::signingFormat_sequence, std::vector<ebucoreSigningFormat*>, 
		mapSigningFormat, dest, signingFormat)

	NEW_VECTOR_AND_RASSIGN(source, getmaterialTechnicalAttributeString, String, formatType::technicalAttributeString_sequence, 
		std::vector<ebucoreTechnicalAttributeString*>, mapTechnicalAttributeString, dest, technicalAttributeString)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getmaterialTechnicalAttributeInt8, Int8, formatType::technicalAttributeByte_sequence, 
		std::vector<ebucoreTechnicalAttributeInt8*>, mapTechnicalAttributeInt8, dest, technicalAttributeByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getmaterialTechnicalAttributeInt16, Int16, formatType::technicalAttributeShort_sequence, 
		std::vector<ebucoreTechnicalAttributeInt16*>, mapTechnicalAttributeInt16, dest, technicalAttributeShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getmaterialTechnicalAttributeInt32, Int32, formatType::technicalAttributeInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeInt32*>, mapTechnicalAttributeInt32, dest, technicalAttributeInteger, 0 /* initialize value as 0, will be replaced by mapping method */)	
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getmaterialTechnicalAttributeInt64, Int64, formatType::technicalAttributeLong_sequence, 
		std::vector<ebucoreTechnicalAttributeInt64*>, mapTechnicalAttributeInt64, dest, technicalAttributeLong, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getmaterialTechnicalAttributeUInt8, UInt8, formatType::technicalAttributeUnsignedByte_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt8*>, mapTechnicalAttributeUInt8, dest, technicalAttributeUnsignedByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getmaterialTechnicalAttributeUInt16, UInt16, formatType::technicalAttributeUnsignedShort_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt16*>, mapTechnicalAttributeUInt16, dest, technicalAttributeUnsignedShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getmaterialTechnicalAttributeUInt32, UInt32, formatType::technicalAttributeUnsignedInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt32*>, mapTechnicalAttributeUInt32, dest, technicalAttributeUnsignedInteger, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getmaterialTechnicalAttributeUInt64, UInt64, formatType::technicalAttributeUnsignedLong_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt64*>, mapTechnicalAttributeUInt64, dest, technicalAttributeUnsignedLong, 0 /* initialize value as 0, will be replaced by mapping method */)

	NEW_VECTOR_AND_RASSIGN_CARGS(source, getmaterialTechnicalAttributeFloat, Float, formatType::technicalAttributeFloat_sequence, 
		std::vector<ebucoreTechnicalAttributeFloat*>, mapTechnicalAttributeFloat, dest, technicalAttributeFloat, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getmaterialTechnicalAttributeRational, technicalAttributeRationalType, formatType::technicalAttributeRational_sequence, 
		std::vector<ebucoreTechnicalAttributeRational*>, mapTechnicalAttributeRational, dest, technicalAttributeRational, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getmaterialTechnicalAttributeBoolean, Boolean, formatType::technicalAttributeBoolean_sequence, 
		std::vector<ebucoreTechnicalAttributeBoolean*>, mapTechnicalAttributeBoolean, dest, technicalAttributeBoolean, false /* initialize value as false, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_CARGS(source, getmaterialTechnicalAttributeAnyURI, technicalAttributeUriType, formatType::technicalAttributeUri_sequence, 
		std::vector<ebucoreTechnicalAttributeAnyURI*>, mapTechnicalAttributeAnyURI, dest, technicalAttributeUri, "" /* initialize value as "", will be replaced by mapping method */)

}

void mapPart(ebucorePartMetadata *source, partType& dest) {
	SIMPLE_RMAP_OPTIONAL(source, havepartId, getpartId, dest, partId)
	SIMPLE_RMAP_OPTIONAL(source, havepartName, getpartName, dest, partName)
	SIMPLE_RMAP_OPTIONAL(source, havepartDefinition, getpartDefinition, dest, partDefinition)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havepartTypeGroup, getpartTypeGroup, dest, partType)
	
	// map ourselves (we are an extension of the coreMetadataType) onto the ebucoreCoreMetadata object
	if (source->havepartMeta()) {
		mapCoreMetadata(source->getpartMeta(), dest);
	}
}

void mapCoreMetadata(ebucoreCoreMetadata *source, coreMetadataType& dest) {
	if (source->havetitle()) { NEW_VECTOR_AND_RASSIGN(source, gettitle, titleType, coreMetadataType::title_sequence, std::vector<ebucoreTitle*>, mapTitle, dest, title) }
	if (source->havealternativeTitle()) { NEW_VECTOR_AND_RASSIGN(source, getalternativeTitle, alternativeTitleType, coreMetadataType::alternativeTitle_sequence, 
		std::vector<ebucoreAlternativeTitle*>, mapAlternativeTitle, dest, alternativeTitle) }
	if (source->havedescription()) { NEW_VECTOR_AND_RASSIGN(source, getdescription, descriptionType, 
		coreMetadataType::description_sequence, std::vector<ebucoreDescription*>, mapDescription, dest, description) }

	if (source->havecreator()) { NEW_VECTOR_AND_RASSIGN(source, getcreator, entityType, coreMetadataType::creator_sequence, std::vector<ebucoreEntity*>, mapEntity, dest, creator) }
	if (source->havepublisher()) { NEW_VECTOR_AND_RASSIGN(source, getpublisher, entityType, coreMetadataType::publisher_sequence, std::vector<ebucoreEntity*>, mapEntity, dest, publisher) }
	if (source->havecontributor()) { NEW_VECTOR_AND_RASSIGN(source, getcontributor, entityType, coreMetadataType::contributor_sequence, std::vector<ebucoreEntity*>, mapEntity, dest, contributor) }

	if (source->haveidentifier()) { NEW_VECTOR_AND_RASSIGN_WITH_DC(source, getidentifier, identifierType, coreMetadataType::identifier_sequence, std::vector<ebucoreIdentifier*>, mapIdentifier, dest, identifier) }
	if (source->havesubject()) { NEW_VECTOR_AND_RASSIGN_WITH_DC(source, getsubject, subjectType, coreMetadataType::subject_sequence, std::vector<ebucoreSubject*>, mapSubject, dest, subject) }
	
	if (source->havetype()) { NEW_VECTOR_AND_RASSIGN(source, gettype, typeType, coreMetadataType::type_sequence, std::vector<ebucoreType*>, mapType, dest, type) }

	if (source->havepublicationHistoryEvent()) {
		std::vector<ebucorePublicationHistoryEvent*> source_events = source->getpublicationHistoryEvent();
		if (source_events.size() > 0) {
			std::auto_ptr<publicationHistoryType> p( new publicationHistoryType() );
			mapPublicationHistory(source_events, *p);
			dest.publicationHistory(p);
		}
	}

	if (source->havedate()) { NEW_VECTOR_AND_RASSIGN(source, getdate, dateType, coreMetadataType::date_sequence, std::vector<ebucoreDate*>, mapDate, dest, date) }
	if (source->havelanguage()) { NEW_VECTOR_AND_RASSIGN(source, getlanguage, languageType, coreMetadataType::language_sequence, std::vector<ebucoreLanguage*>, mapLanguage, dest, language) }
	if (source->havecoverage()) { NEW_VECTOR_AND_RASSIGN(source, getcoverage, coverageType, coreMetadataType::coverage_sequence, std::vector<ebucoreCoverage*>, mapMetadataCoverage, dest, coverage) }

	// a ratingTypes requires a number of values directly in their constructor,
	// so we need something a little different
	if (source->haverating()) { 
		coreMetadataType::rating_sequence vec_ratings;
		const std::vector<ebucoreRating*>& vec_src_ratings = source->getrating();
		for (std::vector<ebucoreRating*>::const_iterator it = vec_src_ratings.begin(); it != vec_src_ratings.end(); it++) {
			vec_ratings.push_back(mapRating(*it));
		}
		dest.rating(vec_ratings);
	}

	if (source->haveversion()) {
		std::auto_ptr<coreMetadataType::version_type> p(new coreMetadataType::version_type( source->getversion()->getversionValue() ));
	}

	if (source->haverights()) { NEW_VECTOR_AND_RASSIGN(source, getrights, rightsType, coreMetadataType::rights_sequence, std::vector<ebucoreRights*>, mapRights, dest, rights) }

	if (source->havebasicRelation()) {
		const std::vector<ebucoreBasicRelation*>& vec_src_rels = source->getbasicRelation();
		for (std::vector<ebucoreBasicRelation*>::const_iterator it = vec_src_rels.begin(); it != vec_src_rels.end(); it++) {
			mapBasicRelation(*it, dest);
		}
	}
	if (source->havecustomRelation()) {  NEW_VECTOR_AND_RASSIGN(source, getcustomRelation, relationType, coreMetadataType::relation_sequence, std::vector<ebucoreCustomRelation*>, mapCustomRelation, dest, relation) }

	if (source->haveformat()) { NEW_VECTOR_AND_RASSIGN(source, getformat, formatType, coreMetadataType::format_sequence, std::vector<ebucoreFormat*>, mapFormat, dest, format) }
	if (source->havepart()) { NEW_VECTOR_AND_RASSIGN(source, getpart, partType, coreMetadataType::part_sequence, std::vector<ebucorePartMetadata*>, mapPart, dest, part) }
}

} // namespace EBUCore
} // namespace EBUSDK
