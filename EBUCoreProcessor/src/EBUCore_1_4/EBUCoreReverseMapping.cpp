/*#include <iostream>
#include <fstream>
#include <memory>

#include <bmx/BMXException.h>
#include <bmx/Logging.h>*/

#include <EBUCore_1_4/EBUCoreMapping.h>

#include <xercesc/util/TransService.hpp>

using namespace ebuCore_2012;
using namespace mxfpp;
//using namespace bmx;

namespace EBUSDK {
namespace EBUCore {
namespace EBUCore_1_4 {

#define	SIMPLE_RMAP(source, sourceProperty, dest, destProperty)	\
	dest.destProperty() = source->sourceProperty();
#define	SIMPLE_MAP_NO_GET(source, sourceProperty, dest, destProperty)	\
	dest->destProperty(source.sourceProperty());
#define	SIMPLE_RMAP_DIRECT(source, dest, destProperty)	\
		dest.destProperty() = source;

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
#define NEW_OBJECT_AND_RASSIGN_DIRECT(source, destType, mapMethod, dest, destProperty) \
	{	\
		std::auto_ptr<destType> p( new destType() );	\
		mapMethod(source, *p);	\
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

#define NEW_VECTOR_AND_RASSIGN_OPTIONAL(source, hasSourceProperty, sourceProperty, destType, destSequenceType, vectorType, mapMethod, dest, destProperty)	\
	if (source->hasSourceProperty()) {	\
		NEW_VECTOR_AND_RASSIGN(source, sourceProperty, destType, destSequenceType, vectorType, mapMethod, dest, destProperty)	\
	}
#define NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, hasSourceProperty, sourceProperty, destType, destSequenceType, vectorType, mapMethod, dest, destProperty, constructorArgs)	\
	if (source->hasSourceProperty()) {	\
		NEW_VECTOR_AND_RASSIGN_CARGS(source, sourceProperty, destType, destSequenceType, vectorType, mapMethod, dest, destProperty, constructorArgs)	\
	}

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

void mapCountry(ebucoreCountry *source, country& dest) {
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havecountryTypeGroup, getcountryTypeGroup, dest, country)
}

void mapCountry(ebucoreCountry *source, country1& dest) {
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havecountryTypeGroup, getcountryTypeGroup, dest, country)
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

	//SIMPLE_RMAP_OPTIONAL(source, havetownCity, gettownCity, dest, addressTownCity)
	if (source->havetownCity() && source->gettownCity().size() > 0) {
		NEW_OBJECT_AND_RASSIGN_DIRECT(source->gettownCity()[0], addressType::addressTownCity_type, mapTextualAnnotation, dest, addressTownCity)
	}
	if (source->havecountyState() && source->getcountyState().size() > 0) {
		NEW_OBJECT_AND_RASSIGN_DIRECT(source->getcountyState()[0], addressType::addressCountyState_type, mapTextualAnnotation, dest, addressCountyState)
	}
	SIMPLE_RMAP_OPTIONAL(source, havedeliveryCode, getdeliveryCode, dest, addressDeliveryCode)

	if (source->havecountry() && source->getcountry().size() > 0) {
		NEW_OBJECT_AND_RASSIGN_DIRECT(source->getcountry()[0], addressType::country_type, mapCountry, dest, country)
	}
}

void mapDetails(ebucoreContactDetails *source, detailsType& dest) {
	if (source->haveemailAddress()) {
		detailsType::emailAddress_sequence seq;
		seq.push_back(source->getemailAddress());
		dest.emailAddress(seq);
	}

	SIMPLE_RMAP_OPTIONAL(source, havewebAddress, getwebAddress, dest, webAddress)

	NEW_OBJECT_AND_RASSIGN_OPTIONAL_GETPOINTER(source, haveaddress, getaddress, addressType, mapAddress, dest, address)

	SIMPLE_RMAP_OPTIONAL(source, havetelephoneNumber, gettelephoneNumber, dest, telephoneNumber)
	SIMPLE_RMAP_OPTIONAL(source, havemobileTelephoneNumber, getmobileTelephoneNumber, dest, mobileTelephoneNumber)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havedetailsType, getdetailsType, dest, detailsType)
}

void mapName(ebucoreCompoundName *source, compoundNameType& dest) {
	if (source->havecompoundName())
		dest = source->getcompoundName();
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havecompoundNameTypeGroup, getcompoundNameTypeGroup, dest, compoundNameType)
	RMAP_FORMAT_GROUP_GET_OPTIONAL(source, havecompoundNameFormatGroup, getcompoundNameFormatGroup, dest, compoundNameType)
}

void mapContact(ebucoreContact *source, contactDetailsType& dest) {

	SIMPLE_RMAP_OPTIONAL(source, havecontactId, getcontactId, dest, contactId)

	if (source->havecontactName()) {
		NEW_VECTOR_AND_RASSIGN(source, getcontactName, contactDetailsType::name_type, contactDetailsType::name_sequence, std::vector<ebucoreCompoundName*>, mapName, dest, name)
	}
	SIMPLE_RMAP_OPTIONAL(source, havefamilyName, getfamilyName, dest, familyName) 
	SIMPLE_RMAP_OPTIONAL(source, havegivenName, getgivenName, dest, givenName)
	SIMPLE_RMAP_OPTIONAL(source, havesuffix, getsuffix, dest, suffix)
	SIMPLE_RMAP_OPTIONAL(source, havesalutation, getsalutation, dest, salutation) 
	if (source->haveotherGivenName()) {
		NEW_VECTOR_AND_RASSIGN(source, getotherGivenName, contactDetailsType::otherGivenName_type, contactDetailsType::otherGivenName_sequence, std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, otherGivenName)
	}
	if (source->haveusername()) {
		contactDetailsType::username_sequence seq;
		seq.push_back(source->getusername());
		dest.username(seq);
	}
	SIMPLE_RMAP_OPTIONAL(source, haveoccupation, getoccupation, dest, occupation)
	SIMPLE_RMAP_OPTIONAL(source, haveguestFlag, getguestFlag, dest, guest)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havecontactType, getcontactType, dest, contactDetailsType)
	if (source->havecontactDetails()) {
		NEW_VECTOR_AND_RASSIGN(source, getcontactDetails, detailsType, contactDetailsType::details_sequence, std::vector<ebucoreContactDetails*>, mapDetails, dest, details)
	}
	if (source->havestageName()) {
		NEW_VECTOR_AND_RASSIGN(source, getstageName, contactDetailsType::stageName_type, contactDetailsType::stageName_sequence, std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, stageName)
	}
	if (source->havecontactRelatedContacts()) {
		NEW_VECTOR_AND_RASSIGN(source, getcontactRelatedContacts, entityType, contactDetailsType::relatedContacts_sequence, std::vector<ebucoreEntity*>, mapEntity, dest, relatedContacts)
	}

	if (source->havecontactRelatedInformationLink()) {
		contactDetailsType::relatedInformationLink_sequence seq;
		const std::vector<ebucoreBasicLink*>& vec = source->getcontactRelatedInformationLink();
		for (std::vector<ebucoreBasicLink*>::const_iterator it = vec.begin(); it != vec.end(); it++) { \
			if ( (*it)->havebasicLinkURI() ) {
				std::auto_ptr<relatedInformationLink> p( new relatedInformationLink( (*it)->getbasicLinkURI() ) ); \
				seq.push_back(p);
			}
		}
		dest.relatedInformationLink(seq);
	}
}

void mapIdentifier(ebucoreIdentifier *source, identifierType& dest) {

	std::auto_ptr<dc::elementType> dcp( new dc::elementType( source->getidentifierValue() ) );
	dest.identifier(dcp);

	SIMPLE_RMAP_OPTIONAL(source, haveidentifierNote, getidentifierNote, dest, note)

	RMAP_FORMAT_GROUP_GET_OPTIONAL(source, haveidentifierFormatGroup, getidentifierFormatGroup, dest, identifierType)
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, haveidentifierTypeGroup, getidentifierTypeGroup, dest, identifierType)

	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, haveidentifierAttributorEntity, getidentifierAttributorEntity, entityType, mapEntity, dest, attributor)
}

void mapOrganisationDepartment(ebucoreOrganisationDepartment *source, organisationDepartment& dest) {
	if (source->havedepartmentName())
		dest = source->getdepartmentName();
	SIMPLE_RMAP_OPTIONAL(source, havedepartmentId, getdepartmentId, dest, departmentId)
}

void mapOrganisation(ebucoreOrganisation *source, organisationDetailsType& dest) {

	SIMPLE_RMAP_OPTIONAL(source, haveorganisationId, getorganisationId, dest, organisationId)

	if (source->haveorganisationName()) {
		NEW_VECTOR_AND_RASSIGN(source, getorganisationName, organisationDetailsType::organisationName_type, 
			organisationDetailsType::organisationName_sequence, std::vector<ebucoreCompoundName*>, mapName, dest, organisationName)
	}
	if (source->haveorganisationCode()) {
		NEW_VECTOR_AND_RASSIGN_CARGS(source, getorganisationCode, organisationDetailsType::organisationCode_type, 
			organisationDetailsType::organisationCode_sequence, std::vector<ebucoreIdentifier*>, mapIdentifier, dest, organisationCode, "" /* initialize ID with empty text */)
	}

	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, haveorganisationDepartment, getorganisationDepartment, organisationDepartment, mapOrganisationDepartment, dest, organisationDepartment)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, haveorganisationType, getorganisationType, dest, organisationDetailsType)

	if (source->haveorganisationRelatedContacts()) {
		NEW_VECTOR_AND_RASSIGN(source, getorganisationRelatedContacts, entityType, organisationDetailsType::contacts_sequence, std::vector<ebucoreEntity*>, mapEntity, dest, contacts)
	}
	if (source->haveorganisationDetails()) {
		NEW_VECTOR_AND_RASSIGN(source, getorganisationDetails, detailsType, organisationDetailsType::details_sequence, std::vector<ebucoreContactDetails*>, mapDetails, dest, details)
	}

	if (source->haveorganisationRelatedInformationLink()) {
		organisationDetailsType::relatedInformationLink_sequence seq;
		const std::vector<ebucoreBasicLink*>& vec = source->getorganisationRelatedInformationLink();
		for (std::vector<ebucoreBasicLink*>::const_iterator it = vec.begin(); it != vec.end(); it++) { \
			if ( (*it)->havebasicLinkURI() ) {
				std::auto_ptr<relatedInformationLink1> p( new relatedInformationLink1( (*it)->getbasicLinkURI() ) ); \
				seq.push_back(p);
			}
		}
		dest.relatedInformationLink(seq);
	}
}

void mapRole(ebucoreRole *source, role& dest) {
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, haveroleTypeGroup, getroleTypeGroup, dest, role)
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
		NEW_VECTOR_AND_RASSIGN(source, getentityRole, role, entityType::role_sequence, std::vector<ebucoreRole*>, mapRole, dest, role)
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

	if (source->havetitleValue()) {
		NEW_VECTOR_AND_RASSIGN(source, gettitleValue, titleType::title_type, titleType::title_sequence, 
			std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, title)
	}

	SIMPLE_RMAP_OPTIONAL(source, havetitleNote, gettitleNote, dest, note)
	if (source->havetitleAttributionDate()) {
		std::auto_ptr<ebuCoreMainType::dateLastModified_type> dp( convert_timestamp_date(source->gettitleAttributionDate()));
		dest.attributiondate().set(dp);
	}
}

void mapAlternativeTitle(ebucoreAlternativeTitle *source, alternativeTitleType& dest) {

	if (source->havealternativeTitleValue()) {
		NEW_VECTOR_AND_RASSIGN(source, getalternativeTitleValue, alternativeTitleType::title_type, alternativeTitleType::title_sequence, 
			std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, title)
	}

	SIMPLE_RMAP_OPTIONAL(source, havealternativeTitleNote, getalternativeTitleNote, dest, note)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havealternativeTitleTypeGroup, getalternativeTitleTypeGroup, dest, alternativeTitleType)
	RMAP_STATUS_GROUP_GET_OPTIONAL(source, havealternativeTitleStatusGroup, getalternativeTitleStatusGroup, dest, alternativeTitleType)
	
	if (source->havealternativeTitleAttributionDate()) {
		std::auto_ptr<ebuCoreMainType::dateLastModified_type> dp( convert_timestamp_date(source->getalternativeTitleAttributionDate()));
		dest.startDate().set(dp);
	}
}

void mapDescription(ebucoreDescription *source, descriptionType& dest) {

	if (source->havedescriptionValue()) {
		NEW_VECTOR_AND_RASSIGN(source, getdescriptionValue, descriptionType::description_type, descriptionType::description_sequence, 
			std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, description)
	}

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havedescriptionTypeGroup, getdescriptionTypeGroup, dest, identifierType)

	SIMPLE_RMAP_OPTIONAL(source, havedescriptionNote, getdescriptionNote, dest, note)
}

void mapSubject(ebucoreSubject *source, subjectType& dest) {

	if (source->havesubjectValue()) {
		NEW_VECTOR_AND_RASSIGN(source, getsubjectValue, subjectType::subject_type, subjectType::subject_sequence, 
			std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, subject)
	}

	SIMPLE_RMAP_OPTIONAL(source, havesubjectCode, getsubjectCode, dest, subjectCode)

	if (source->havesubjectDefinition()) {
		NEW_VECTOR_AND_RASSIGN(source, getsubjectDefinition, subjectType::subjectDefinition_type, subjectType::subjectDefinition_sequence, 
			std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, subjectDefinition)
	}
	SIMPLE_RMAP_OPTIONAL(source, havesubjectNote, getsubjectNote, dest, note)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havesubjectTypeGroup, getsubjectTypeGroup, dest, identifierType)

	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havesubjectAttributorEntity, getsubjectAttributorEntity, entityType, mapEntity, dest, attributor)
}

void mapRegion(ebucoreRegion *source, regionType& dest) {
	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havecountry, getcountry, country1, mapCountry, dest, country)
	if (source->havecountryRegion()) {
		regionType::countryRegion_sequence seq;
		std::auto_ptr<countryRegion> p( new countryRegion() );
		RMAP_TYPE_GROUP(source->getcountryRegion(), (*p), countryRegion::typeDefinition_type, countryRegion::typeLabel_type, countryRegion::typeLink_type, countryRegion::typeLanguage_type)
		seq.push_back(p);
		dest.countryRegion(seq);
	}
}

void mapRating(ebucoreRating *source, ratingType& dest) {

	if (source->haveratingValue()) {
		NEW_VECTOR_AND_RASSIGN(source, getratingValue, ratingType::ratingValue_type, ratingType::ratingValue_sequence, 
			std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, ratingValue)
	}
	if (source->haveratingScaleMinValue()) {
		NEW_VECTOR_AND_RASSIGN(source, getratingScaleMinValue, ratingType::ratingScaleMinValue_type, ratingType::ratingScaleMinValue_sequence, 
			std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, ratingScaleMinValue)
	}
	if (source->haveratingScaleMaxValue()) {
		NEW_VECTOR_AND_RASSIGN(source, getratingScaleMaxValue, ratingType::ratingScaleMaxValue_type, ratingType::ratingScaleMaxValue_sequence, 
			std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, ratingScaleMaxValue)
	}

	SIMPLE_RMAP_OPTIONAL(source, haveratingReason, getratingReason, dest, reason)
	SIMPLE_RMAP_OPTIONAL(source, haveratingLinkToLogo, getratingLinkToLogo, dest, linkToLogo)
	SIMPLE_RMAP_OPTIONAL(source, haveratingNotRatedFlag, getratingNotRatedFlag, dest, notRated)
	SIMPLE_RMAP_OPTIONAL(source, haveratingAdultContentFlag, getratingAdultContentFlag, dest, adultContent)

	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, haveratingProviderEntity, getratingProviderEntity, entityType, mapEntity, dest, ratingProvider)

	if (source->haveratingRegion()) {
		ratingType::ratingRegion_sequence seq;
		std::auto_ptr<regionType> p( new regionType() );
		mapRegion(source->getratingRegion(), *p);
		seq.push_back(p);
		dest.ratingRegion(seq);
	}

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, haveratingTypeGroup, getratingTypeGroup, dest, identifierType)
	RMAP_FORMAT_GROUP_GET_OPTIONAL(source, haveratingFormatGroup, getratingFormatGroup, dest, identifierType)
}

void mapVersion(ebucoreVersion *source, coreMetadataType::version_type& dest) {
	if (source->haveversionValue() && source->getversionValue().size() > 0) {
		mapTextualAnnotation(source->getversionValue()[0], dest);
	}

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, haveversionTypeGroup, getversionTypeGroup, dest, versionType)
}

void mapLanguage(ebucoreLanguage *source, languageType& dest) {
	SIMPLE_RMAP_OPTIONAL(source, havelanguageCode, getlanguageCode, dest, language)
	SIMPLE_RMAP_OPTIONAL(source, havelanguageLanguageCode, getlanguageLanguageCode, dest, language().get().lang)
	SIMPLE_RMAP_OPTIONAL(source, havelanguageNote, getlanguageNote, dest, note)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havelanguagePurposeSet, getlanguagePurposeSet, dest, languageType)
}

void mapGenre(ebucoreGenre *source, genre& dest) {
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havegenreKindGroup, getgenreKindGroup, dest, genre)
}

void mapTargetAudience(ebucoreTargetAudience *source, targetAudience& dest) {
	SIMPLE_RMAP_OPTIONAL(source, havetargetAudienceReason, gettargetAudienceReason, dest, reason)
	SIMPLE_RMAP_OPTIONAL(source, havetargetAudienceLinkToLogo, gettargetAudienceLinkToLogo, dest, linkToLogo)
	SIMPLE_RMAP_OPTIONAL(source, havetargetAudienceNotRatedFlag, gettargetAudienceNotRatedFlag, dest, notRated)
	SIMPLE_RMAP_OPTIONAL(source, havetargetAudienceAdultContentFlag, gettargetAudienceAdultContentFlag, dest, adultContent)

	if (source->havetargetAudienceRegion()) {
		NEW_VECTOR_AND_RASSIGN(source, gettargetAudienceRegion, targetAudience::targetRegion_type, targetAudience::targetRegion_sequence, 
			std::vector<ebucoreRegion*>, mapRegion, dest, targetRegion)
	}
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havetargetAudienceTypeGroup, gettargetAudienceTypeGroup, dest, targetAudience)
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
		NEW_VECTOR_AND_RASSIGN(source, gettargetAudience, targetAudience, typeType::targetAudience_sequence, std::vector<ebucoreTargetAudience*>, mapTargetAudience, dest, targetAudience)
	}
	if (source->havegenre()) {
		NEW_VECTOR_AND_RASSIGN(source, getgenre, genre, typeType::genre_sequence, std::vector<ebucoreGenre*>, mapGenre, dest, genre)
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
	if (source->havealternativeDate()) {
		NEW_VECTOR_AND_RASSIGN(source, getalternativeDate, alternative, dateType::alternative_sequence, std::vector<ebucoreDateType*>, mapDateType, dest, alternative)
	}

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
	if (source->havedateReleased() || source->haveyearReleased()) {
		std::auto_ptr<dateType::released_type> p ( new dateType::released_type() );
		if (source->havedateReleased()) {
			p->startDate( std::auto_ptr<xml_schema::date>( convert_timestamp_date(source->getdateReleased()) ) );
		if (source->haveyearReleased())
			p->startYear( std::auto_ptr<xml_schema::gyear>( convert_timestamp_year(source->getyearReleased()) ) );		
		}
		dest.released(p);
	}
	if (source->havedateCopyrighted() || source->haveyearCopyrighted()) {
		std::auto_ptr<dateType::copyrighted_type> p ( new dateType::copyrighted_type() );
		if (source->havedateCopyrighted()) {
			p->startDate( std::auto_ptr<xml_schema::date>( convert_timestamp_date(source->getdateCopyrighted()) ) );
		if (source->haveyearCopyrighted())
			p->startYear( std::auto_ptr<xml_schema::gyear>( convert_timestamp_year(source->getyearCopyrighted()) ) );		
		}
		dest.copyrighted(p);
	}
}

void mapPeriodOfTime(ebucorePeriodOfTime* source, periodOfTimeType& dest) {
	// [TODO] Fix correct location of periodId!
	//SIMPLE_RMAP_OPTIONAL(source, haveperiodId, getperiodId, dest, period)
	if (source->haveperiodName() && source->getperiodName().size() > 0) { 
		NEW_OBJECT_AND_RASSIGN_DIRECT(source->getperiodName()[0], periodOfTimeType::periodName_type, mapTextualAnnotation, dest, periodName)
	}
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

void mapCoordinates(ebucoreCoordinates *source, coordinates& dest) {
	// don't bother with X and Y, have been set when dest was constructed
	RMAP_FORMAT_GROUP_GET_OPTIONAL(source, havecoordinatesFormatGroup, getcoordinatesFormatGroup, dest, coordinates)
}

void mapTemporal(ebucoreTemporal *source, temporal& dest) {
	// if there is more that a single period of time, we only use the first one
	// [FIX?] Updated cardinality, source has only max 1 periodoftime
	if (source->haveperiodOfTime()) {
		NEW_VECTOR_AND_RASSIGN(source, getperiodOfTime, periodOfTimeType, temporal::PeriodOfTime_sequence, std::vector<ebucorePeriodOfTime*>, mapPeriodOfTime, dest, PeriodOfTime)
	}
	SIMPLE_RMAP_OPTIONAL(source, havetemporalDefinitionNote, gettemporalDefinitionNote, dest, note)
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havetemporalTypeGroup, gettemporalTypeGroup, dest, temporal)
}

void mapLocation(ebucoreLocation *source, spatial::location_type& dest) {
	SIMPLE_RMAP_OPTIONAL(source, havelocationId, getlocationId, dest, locationId)
	SIMPLE_RMAP_OPTIONAL(source, havelocationCode, getlocationCode, dest, code)
	SIMPLE_RMAP_OPTIONAL(source, havelocationDefinitionNote, getlocationDefinitionNote, dest, note)


	if (source->havelocationName() && source->getlocationName().size() > 0) {
		NEW_OBJECT_AND_RASSIGN_DIRECT(source->getlocationName()[0], spatial::location_type::name_type, mapTextualAnnotation, dest, name)
	}

	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havelocationRegion, getlocationRegion, regionType, mapRegion, dest, region)

	if (source->havelocationCoordinates()) {
		ebucoreCoordinates *coords = source->getlocationCoordinates();
		if (coords->haveposX() && coords->haveposY()) {
			// create a coordinates object only if both X and Y are present (required by schema)
			std::auto_ptr<coordinates> p( new coordinates( coords->getposX(), coords->getposY()) );
			mapCoordinates(coords, *p);
			dest.coordinates(p);
		}
	}

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havelocationTypeGroup, getlocationTypeGroup, dest, locationType)
}

void mapSpatial(ebucoreSpatial *source, spatial& dest) {
	if (source->havelocation()) {
		NEW_VECTOR_AND_RASSIGN(source, getlocation, locationType, spatial::location_sequence, std::vector<ebucoreLocation*>, mapLocation, dest, location)
	}
}

void mapMetadataCoverage(ebucoreCoverage *source, coverageType& dest) {
	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havecoverageValue, getcoverageValue, coverageType::coverage_type, mapTextualAnnotation, dest, coverage)
	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havespatial, getspatial, spatial, mapSpatial, dest, spatial)
	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havetemporal, gettemporal, temporal, mapTemporal, dest, temporal)
}

void mapRights(ebucoreRights *source, rightsType& dest) {

	SIMPLE_RMAP_OPTIONAL(source, haverightsId, getrightsId, dest, rightsID)

	if (source->haverightsAttributeID()) {
		NEW_VECTOR_AND_RASSIGN_WITH_DC(source, getrightsAttributeID, rightsType::rightsAttributedId_type, rightsType::rightsAttributedId_sequence, 
			std::vector<ebucoreIdentifier*>, mapIdentifier, dest, rightsAttributedId)
	}
	
	if (source->haverightsValue()) {
		NEW_VECTOR_AND_RASSIGN(source, getrightsValue, rightsType::rights_type, rightsType::rights_sequence, 
			std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, rights)
	}

	SIMPLE_RMAP_OPTIONAL(source, haverightsClearanceFlag, getrightsClearanceFlag, dest, rightsClearanceFlag)
	SIMPLE_RMAP_OPTIONAL(source, haverightsNote, getrightsNote, dest, note)

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

	if (source->haveexploitationIssues()) {
		NEW_VECTOR_AND_RASSIGN(source, getexploitationIssues, rightsType::exploitationIssues_type, rightsType::exploitationIssues_sequence, 
			std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, exploitationIssues)
	}
	if (source->havecopyrightStatement()) {
		NEW_VECTOR_AND_RASSIGN(source, getcopyrightStatement, rightsType::copyrightStatement_type, rightsType::copyrightStatement_sequence, 
			std::vector<ebucoreTextualAnnotation*>, mapTextualAnnotation, dest, copyrightStatement)
	}

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


void mapPublicationChannel(ebucorePublicationChannel* source, publicationChannelType& dest) {
	if (source->havepublicationChannelName())
		dest = source->getpublicationChannelName();
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havepublicationChannelType, getpublicationChannelType, dest, publicationChannelType)
}

void mapPublicationMedium(ebucorePublicationMedium* source, publicationMediumType& dest) {
	if (source->havepublicationMediumName())
		dest = source->getpublicationMediumName();
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havepublicationMediumType, getpublicationMediumType, dest, publicationMediumType)
}

void mapPublicationHistoryEvent(ebucorePublicationHistoryEvent* source, publicationEventType& dest) {

	SIMPLE_RMAP_OPTIONAL(source, havefirstPublicationFlag, getfirstPublicationFlag, dest, firstShowing)
	SIMPLE_RMAP_OPTIONAL(source, havefreePublicationFlag, getfreePublicationFlag, dest, free)
	SIMPLE_RMAP_OPTIONAL(source, havelivePublicationFlag, getlivePublicationFlag, dest, live)
	SIMPLE_RMAP_OPTIONAL(source, havepublicationNote, getpublicationNote, dest, note)

	if (source->havepublicationDate()) {
		dest.publicationDate( std::auto_ptr<publicationEventType::publicationDate_type>( convert_timestamp_date(source->getpublicationDate())) );
	}
	if (source->havepublicationTime()) {
		dest.publicationTime( std::auto_ptr<publicationEventType::publicationTime_type>( convert_timestamp_time(source->getpublicationTime())) );
	}
	if (source->havepublicationService()) {
		std::auto_ptr<publicationEventType::publicationService_type> p( new publicationEventType::publicationService_type());
		p->publicationServiceName(source->getpublicationService());
		dest.publicationService(p);
	}

	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havepublicationMedium, getpublicationMedium, publicationMediumType, mapPublicationMedium, dest, publicationMedium)
	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havepublicationChannel, getpublicationChannel, publicationChannelType, mapPublicationChannel, dest, publicationChannel)
	if (source->havepublicationRegion()) {
		NEW_VECTOR_AND_RASSIGN(source, getpublicationRegion, regionType, publicationEventType::publicationRegion_sequence, std::vector<ebucoreRegion*>, mapRegion, dest, publicationRegion)
	}

	if (source->havepublicationFormatReference()) {
		ebucoreFormat *fmt =source->getpublicationFormatReference();
		if (fmt != NULL) {
			std::auto_ptr<publicationEventType::formatIdRef_type> p( new publicationEventType::formatIdRef_type(fmt->getformatID()) );
			dest.formatIdRef(p);
		}
	}

	if (source->havepublicationRightsReference()) {
		const std::vector<ebucoreRights*>& vec_rights = source->getpublicationRightsReference();
		if (vec_rights.size() > 0) {
			std::vector<xml_schema::idref> refs;
			for (std::vector<ebucoreRights*>::const_iterator it = vec_rights.begin(); it != vec_rights.end(); it++) {
				ebucoreRights *rights = *it;
				if (rights->haverightsId()) {
					refs.push_back( xml_schema::idref( rights->getrightsId() ) );
				}
			}
			std::auto_ptr<publicationEventType::rightsIDRefs_type> p( new publicationEventType::rightsIDRefs_type( refs.begin(), refs.end() ) );
			dest.rightsIDRefs(p);
		}
	}


}

void mapPublicationHistory(ebucorePublicationHistory *source, publicationHistoryType& dest) {
	if (source->havepublicationEvent()) {
		NEW_VECTOR_AND_RASSIGN(source, getpublicationEvent, publicationEventType, publicationHistoryType::publicationEvent_sequence, 
			std::vector<ebucorePublicationHistoryEvent*>, mapPublicationHistoryEvent, dest, publicationEvent)
	}
}

/*void mapPublicationHistory(std::vector<ebucorePublicationHistoryEvent*>& source, publicationHistoryType& dest) {
	publicationHistoryType::publicationEvent_sequence vec_dest;
	for (std::vector<ebucorePublicationHistoryEvent*>::iterator it = source.begin(); it != source.end(); it++) {
		std::auto_ptr<publicationEvent> p( new publicationEvent() );
		mapPublicationHistoryEvent(*it, *p);
		vec_dest.push_back(p);
	}
	dest.publicationEvent(vec_dest);
}*/

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
		RMAP_TYPE_GROUP_GET_OPTIONAL(source, havetechnicalAttributeTypeGroup, gettechnicalAttributeTypeGroup, dest, destType) \
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
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havetechnicalAttributeTypeGroup, gettechnicalAttributeTypeGroup, dest, technicalAttributeRationalType);
}

void mapTechnicalAttributeAnyURI(ebucoreTechnicalAttributeAnyURI *source, technicalAttributeUriType& dest) {
	dest.assign(source->gettechnicalAttributeAnyURIValue()); // use assign as no more convenient operator works
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havetechnicalAttributeTypeGroup, gettechnicalAttributeTypeGroup, dest, technicalAttributeUriType);
}

void mapMedium(ebucoreMedium *source, medium& dest) {
	SIMPLE_RMAP_OPTIONAL(source, havemediumID, getmediumID, dest, mediumId)
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havemediumTypeGroup, getmediumTypeGroup, dest, medium)
}

void mapPackageInfo(ebucorePackageInfo *source, formatType& dest) {
	SIMPLE_RMAP_OPTIONAL(source, havepackageName, getpackageName, dest, fileName)
	SIMPLE_RMAP_OPTIONAL(source, havepackageSize, getpackageSize, dest, fileSize)

	if (source->havepackageLocator()) {
		formatType::locator_sequence seq;
		std::auto_ptr<locator> p( new locator( source->getpackageLocator() ) );
		seq.push_back(p);
		dest.locator(seq);
	}	
}

void mapSigningFormat(ebucoreSigningFormat *source, signingFormat& dest) {
	SIMPLE_RMAP_OPTIONAL(source, havesigningTrackID, getsigningTrackID, dest, trackId)
	SIMPLE_RMAP_OPTIONAL(source, havesigningTrackName, getsigningTrackName, dest, trackName)
	SIMPLE_RMAP_OPTIONAL(source, havesigningTrackLanguageCode, getsigningTrackLanguageCode, dest, language)
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
	SIMPLE_RMAP_OPTIONAL(source, havetrackLanguageCode, gettrackLanguageCode, dest, trackLanguage)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havetrackTypeGroup, gettrackTypeGroup, dest, audioTrack)
}

void mapVideoTrack(ebucoreTrack *source, videoTrack& dest) {
	SIMPLE_RMAP_OPTIONAL(source, havetrackID, gettrackID, dest, trackId)
	SIMPLE_RMAP_OPTIONAL(source, havetrackName, gettrackName, dest, trackName)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havetrackTypeGroup, gettrackTypeGroup, dest, videoTrack)
}

xml_schema::long_ convert(mxfRational source) {
	return source.numerator;
}

void mapAudioEncoding(ebucoreTypeGroup *source, audioFormatType::audioEncoding_type& dest) {
	RMAP_TYPE_GROUP(source, dest, audioFormatType::audioEncoding_type::typeDefinition_type, 
		audioFormatType::audioEncoding_type::typeLabel_type, audioFormatType::audioEncoding_type::typeLink_type, audioFormatType::audioEncoding_type::typeLanguage_type)
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
	SIMPLE_RMAP_OPTIONAL(source, haveaudioMaxBitRate, getaudioMaxBitRate, dest, bitRateMax)

	SIMPLE_RMAP_OPTIONAL(source, haveaudioBitRateMode, getaudioBitRateMode, dest, bitRateMode)
	SIMPLE_RMAP_OPTIONAL_CONVERT(source, haveaudioSamplingRate, getaudioSamplingRate, dest, samplingRate, convert)

	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, haveaudioEncoding, getaudioEncoding, audioFormatType::audioEncoding_type, mapAudioEncoding, dest, audioEncoding)

	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, haveaudioCodec, getaudioCodec, codecType, mapCodec, dest, codec)
	if (source->haveaudioTrack()) {
		NEW_VECTOR_AND_RASSIGN(source, getaudioTrack, audioTrack, audioFormatType::audioTrack_sequence, std::vector<ebucoreTrack*>, mapAudioTrack, dest, audioTrack)
	}

	NEW_VECTOR_AND_RASSIGN_OPTIONAL(source, haveaudioTechnicalAttributeString, getaudioTechnicalAttributeString, String, audioFormatType::technicalAttributeString_sequence, 
		std::vector<ebucoreTechnicalAttributeString*>, mapTechnicalAttributeString, dest, technicalAttributeString)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveaudioTechnicalAttributeInt8, getaudioTechnicalAttributeInt8, Int8, audioFormatType::technicalAttributeByte_sequence, 
		std::vector<ebucoreTechnicalAttributeInt8*>, mapTechnicalAttributeInt8, dest, technicalAttributeByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveaudioTechnicalAttributeInt16, getaudioTechnicalAttributeInt16, Int16, audioFormatType::technicalAttributeShort_sequence, 
		std::vector<ebucoreTechnicalAttributeInt16*>, mapTechnicalAttributeInt16, dest, technicalAttributeShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveaudioTechnicalAttributeInt32, getaudioTechnicalAttributeInt32, Int32, audioFormatType::technicalAttributeInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeInt32*>, mapTechnicalAttributeInt32, dest, technicalAttributeInteger, 0 /* initialize value as 0, will be replaced by mapping method */)	
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveaudioTechnicalAttributeInt64, getaudioTechnicalAttributeInt64, Int64, audioFormatType::technicalAttributeLong_sequence, 
		std::vector<ebucoreTechnicalAttributeInt64*>, mapTechnicalAttributeInt64, dest, technicalAttributeLong, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveaudioTechnicalAttributeUInt8, getaudioTechnicalAttributeUInt8, UInt8, audioFormatType::technicalAttributeUnsignedByte_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt8*>, mapTechnicalAttributeUInt8, dest, technicalAttributeUnsignedByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveaudioTechnicalAttributeUInt16, getaudioTechnicalAttributeUInt16, UInt16, audioFormatType::technicalAttributeUnsignedShort_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt16*>, mapTechnicalAttributeUInt16, dest, technicalAttributeUnsignedShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveaudioTechnicalAttributeUInt32, getaudioTechnicalAttributeUInt32, UInt32, audioFormatType::technicalAttributeUnsignedInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt32*>, mapTechnicalAttributeUInt32, dest, technicalAttributeUnsignedInteger, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveaudioTechnicalAttributeUInt64, getaudioTechnicalAttributeUInt64, UInt64, audioFormatType::technicalAttributeUnsignedLong_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt64*>, mapTechnicalAttributeUInt64, dest, technicalAttributeUnsignedLong, 0 /* initialize value as 0, will be replaced by mapping method */)

	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveaudioTechnicalAttributeFloat, getaudioTechnicalAttributeFloat, Float, audioFormatType::technicalAttributeFloat_sequence, 
		std::vector<ebucoreTechnicalAttributeFloat*>, mapTechnicalAttributeFloat, dest, technicalAttributeFloat, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveaudioTechnicalAttributeRational, getaudioTechnicalAttributeRational, technicalAttributeRationalType, audioFormatType::technicalAttributeRational_sequence, 
		std::vector<ebucoreTechnicalAttributeRational*>, mapTechnicalAttributeRational, dest, technicalAttributeRational, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveaudioTechnicalAttributeBoolean, getaudioTechnicalAttributeBoolean, Boolean, audioFormatType::technicalAttributeBoolean_sequence, 
		std::vector<ebucoreTechnicalAttributeBoolean*>, mapTechnicalAttributeBoolean, dest, technicalAttributeBoolean, false /* initialize value as false, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveaudioTechnicalAttributeAnyURI, getaudioTechnicalAttributeAnyURI, technicalAttributeUriType, audioFormatType::technicalAttributeUri_sequence, 
		std::vector<ebucoreTechnicalAttributeAnyURI*>, mapTechnicalAttributeAnyURI, dest, technicalAttributeUri, "" /* initialize value as "", will be replaced by mapping method */)
}

void mapImageEncoding(ebucoreTypeGroup *source, imageFormatType::imageEncoding_type& dest) {
	RMAP_TYPE_GROUP(source, dest, imageFormatType::imageEncoding_type::typeDefinition_type, 
		imageFormatType::imageEncoding_type::typeLabel_type, imageFormatType::imageEncoding_type::typeLink_type, imageFormatType::imageEncoding_type::typeLanguage_type)
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

void mapDimension(ebucoreDimension *source, dimensionType& dest) {
	dest = source->getdimensionValue();
	SIMPLE_RMAP_OPTIONAL(source, havedimensionUnit, getdimensionUnit, dest, unit)
}

void mapWidth(ebucoreWidth *source, width& dest) {
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havewidthTypeGroup, getwidthTypeGroup, dest, width)
	mapDimension(source->getwidthValue(), dest);
}

void mapHeight(ebucoreHeight *source, height& dest) {
	RMAP_TYPE_GROUP_GET_OPTIONAL(source, haveheightTypeGroup, getheightTypeGroup, dest, height)
	mapDimension(source->getheightValue(), dest);
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

	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, haveimageEncoding, getimageEncoding, imageFormatType::imageEncoding_type, mapImageEncoding, dest, imageEncoding)

	/* [TODO] XSD is missing image codec
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, codec, ebucoreCodec, mapCodec, dest, setimageCodec) */

	NEW_OBJECT_AND_RASSIGN_OPTIONAL_CARGS(source, haveimageWidth, getimageWidth, dimensionType, mapDimension, dest, width, 0) 
	NEW_OBJECT_AND_RASSIGN_OPTIONAL_CARGS(source, haveimageHeight, getimageHeight, dimensionType, mapDimension, dest, height, 0) 

	NEW_VECTOR_AND_RASSIGN_OPTIONAL(source, haveimageTechnicalAttributeString, getimageTechnicalAttributeString, String, imageFormatType::technicalAttributeString_sequence, 
		std::vector<ebucoreTechnicalAttributeString*>, mapTechnicalAttributeString, dest, technicalAttributeString)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveimageTechnicalAttributeInt8, getimageTechnicalAttributeInt8, Int8, imageFormatType::technicalAttributeByte_sequence, 
		std::vector<ebucoreTechnicalAttributeInt8*>, mapTechnicalAttributeInt8, dest, technicalAttributeByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveimageTechnicalAttributeInt16, getimageTechnicalAttributeInt16, Int16, imageFormatType::technicalAttributeShort_sequence, 
		std::vector<ebucoreTechnicalAttributeInt16*>, mapTechnicalAttributeInt16, dest, technicalAttributeShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveimageTechnicalAttributeInt32, getimageTechnicalAttributeInt32, Int32, imageFormatType::technicalAttributeInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeInt32*>, mapTechnicalAttributeInt32, dest, technicalAttributeInteger, 0 /* initialize value as 0, will be replaced by mapping method */)	
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveimageTechnicalAttributeInt64, getimageTechnicalAttributeInt64, Int64, imageFormatType::technicalAttributeLong_sequence, 
		std::vector<ebucoreTechnicalAttributeInt64*>, mapTechnicalAttributeInt64, dest, technicalAttributeLong, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveimageTechnicalAttributeUInt8, getimageTechnicalAttributeUInt8, UInt8, imageFormatType::technicalAttributeUnsignedByte_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt8*>, mapTechnicalAttributeUInt8, dest, technicalAttributeUnsignedByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveimageTechnicalAttributeUInt16, getimageTechnicalAttributeUInt16, UInt16, imageFormatType::technicalAttributeUnsignedShort_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt16*>, mapTechnicalAttributeUInt16, dest, technicalAttributeUnsignedShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveimageTechnicalAttributeUInt32, getimageTechnicalAttributeUInt32, UInt32, imageFormatType::technicalAttributeUnsignedInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt32*>, mapTechnicalAttributeUInt32, dest, technicalAttributeUnsignedInteger, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveimageTechnicalAttributeUInt64, getimageTechnicalAttributeUInt64, UInt64, imageFormatType::technicalAttributeUnsignedLong_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt64*>, mapTechnicalAttributeUInt64, dest, technicalAttributeUnsignedLong, 0 /* initialize value as 0, will be replaced by mapping method */)

	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveimageTechnicalAttributeFloat, getimageTechnicalAttributeFloat, Float, imageFormatType::technicalAttributeFloat_sequence, 
		std::vector<ebucoreTechnicalAttributeFloat*>, mapTechnicalAttributeFloat, dest, technicalAttributeFloat, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveimageTechnicalAttributeRational, getimageTechnicalAttributeRational, technicalAttributeRationalType, imageFormatType::technicalAttributeRational_sequence, 
		std::vector<ebucoreTechnicalAttributeRational*>, mapTechnicalAttributeRational, dest, technicalAttributeRational, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveimageTechnicalAttributeBoolean, getimageTechnicalAttributeBoolean, Boolean, imageFormatType::technicalAttributeBoolean_sequence, 
		std::vector<ebucoreTechnicalAttributeBoolean*>, mapTechnicalAttributeBoolean, dest, technicalAttributeBoolean, false /* initialize value as false, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, haveimageTechnicalAttributeAnyURI, getimageTechnicalAttributeAnyURI, technicalAttributeUriType, imageFormatType::technicalAttributeUri_sequence, 
		std::vector<ebucoreTechnicalAttributeAnyURI*>, mapTechnicalAttributeAnyURI, dest, technicalAttributeUri, "" /* initialize value as "", will be replaced by mapping method */)
}

void mapVideoEncoding(ebucoreTypeGroup *source, videoFormatType::videoEncoding_type& dest) {
	RMAP_TYPE_GROUP(source, dest, videoFormatType::videoEncoding_type::typeDefinition_type, 
		videoFormatType::videoEncoding_type::typeLabel_type, videoFormatType::videoEncoding_type::typeLink_type, videoFormatType::videoEncoding_type::typeLanguage_type)
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
	SIMPLE_RMAP_OPTIONAL(source, havevideoMaxBitRate, getvideoMaxBitRate, dest, bitRateMax)
	SIMPLE_RMAP_OPTIONAL(source, havevideoBitRateMode, getvideoBitRateMode, dest, bitRateMode)
	SIMPLE_RMAP_OPTIONAL(source, havevideoSamplingFormat, getvideoSamplingFormat, dest, scanningFormat)
	SIMPLE_RMAP_OPTIONAL(source, havevideoScanningOrder, getvideoScanningOrder, dest, scanningOrder)
	SIMPLE_RMAP_OPTIONAL(source, havevideoActiveLines, getvideoActiveLines, dest, lines)
	SIMPLE_RMAP_OPTIONAL(source, havevideoNoiseFilterFlag, getvideoNoiseFilterFlag, dest, noiseFilter)
	SIMPLE_RMAP_OPTIONAL(source, havevideo3DFlag, getvideo3DFlag, dest, flag_3D)	

	// 	NEW_VECTOR_AND_ASSIGN(source, aspectRatio, ebucoreAspectRatio, videoFormatType::aspectRatio_iterator, mapAspectRatio, dest, setvideoAspectRatio)
	if (source->havevideoAspectRatio()) {
		videoFormatType::aspectRatio_sequence seq;
		const std::vector<ebucoreAspectRatio*>& vec = source->getvideoAspectRatio();
		for (std::vector<ebucoreAspectRatio*>::const_iterator it = vec.begin(); it != vec.end(); it++) {
			std::auto_ptr<aspectRatioType> p( new aspectRatioType( 1, 1 ) );
			mapAspectRatio(*it, *p);
			seq.push_back(p);
		}
		dest.aspectRatio(seq);
	}

	SIMPLE_RMAP_OPTIONAL_CONVERT(source, havevideoFrameRate, getvideoFrameRate, dest, frameRate, convert_rational)

	if (source->havevideoWidth()) {
		videoFormatType::width_sequence seq;
		std::auto_ptr<width> p( new width(0) );
		mapWidth(source->getvideoWidth(), *p);
		dest.width(seq);
	}
	if (source->havevideoHeight()) {
		videoFormatType::height_sequence seq;
		std::auto_ptr<height> p( new height(0) );
		mapHeight(source->getvideoHeight(), *p);
		dest.height(seq);
	}

	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havevideoEncoding, getvideoEncoding, videoFormatType::videoEncoding_type, mapVideoEncoding, dest, videoEncoding)

	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havevideoCodec, getvideoCodec, codecType, mapCodec, dest, codec)
	if (source->havevideoTrack()) {
		NEW_VECTOR_AND_RASSIGN(source, getvideoTrack, videoTrack, videoFormatType::videoTrack_sequence, std::vector<ebucoreTrack*>, mapVideoTrack, dest, videoTrack)
	}

	NEW_VECTOR_AND_RASSIGN_OPTIONAL(source, havevideoTechnicalAttributeString, getvideoTechnicalAttributeString, String, videoFormatType::technicalAttributeString_sequence, 
		std::vector<ebucoreTechnicalAttributeString*>, mapTechnicalAttributeString, dest, technicalAttributeString)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havevideoTechnicalAttributeInt8, getvideoTechnicalAttributeInt8, Int8, videoFormatType::technicalAttributeByte_sequence, 
		std::vector<ebucoreTechnicalAttributeInt8*>, mapTechnicalAttributeInt8, dest, technicalAttributeByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havevideoTechnicalAttributeInt16, getvideoTechnicalAttributeInt16, Int16, videoFormatType::technicalAttributeShort_sequence, 
		std::vector<ebucoreTechnicalAttributeInt16*>, mapTechnicalAttributeInt16, dest, technicalAttributeShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havevideoTechnicalAttributeInt32, getvideoTechnicalAttributeInt32, Int32, videoFormatType::technicalAttributeInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeInt32*>, mapTechnicalAttributeInt32, dest, technicalAttributeInteger, 0 /* initialize value as 0, will be replaced by mapping method */)	
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havevideoTechnicalAttributeInt64, getvideoTechnicalAttributeInt64, Int64, videoFormatType::technicalAttributeLong_sequence, 
		std::vector<ebucoreTechnicalAttributeInt64*>, mapTechnicalAttributeInt64, dest, technicalAttributeLong, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havevideoTechnicalAttributeUInt8, getvideoTechnicalAttributeUInt8, UInt8, videoFormatType::technicalAttributeUnsignedByte_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt8*>, mapTechnicalAttributeUInt8, dest, technicalAttributeUnsignedByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havevideoTechnicalAttributeUInt16, getvideoTechnicalAttributeUInt16, UInt16, videoFormatType::technicalAttributeUnsignedShort_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt16*>, mapTechnicalAttributeUInt16, dest, technicalAttributeUnsignedShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havevideoTechnicalAttributeUInt32, getvideoTechnicalAttributeUInt32, UInt32, videoFormatType::technicalAttributeUnsignedInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt32*>, mapTechnicalAttributeUInt32, dest, technicalAttributeUnsignedInteger, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havevideoTechnicalAttributeUInt64, getvideoTechnicalAttributeUInt64, UInt64, videoFormatType::technicalAttributeUnsignedLong_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt64*>, mapTechnicalAttributeUInt64, dest, technicalAttributeUnsignedLong, 0 /* initialize value as 0, will be replaced by mapping method */)

	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havevideoTechnicalAttributeFloat, getvideoTechnicalAttributeFloat, Float, videoFormatType::technicalAttributeFloat_sequence, 
		std::vector<ebucoreTechnicalAttributeFloat*>, mapTechnicalAttributeFloat, dest, technicalAttributeFloat, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havevideoTechnicalAttributeRational, getvideoTechnicalAttributeRational, technicalAttributeRationalType, videoFormatType::technicalAttributeRational_sequence, 
		std::vector<ebucoreTechnicalAttributeRational*>, mapTechnicalAttributeRational, dest, technicalAttributeRational, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havevideoTechnicalAttributeBoolean, getvideoTechnicalAttributeBoolean, Boolean, videoFormatType::technicalAttributeBoolean_sequence, 
		std::vector<ebucoreTechnicalAttributeBoolean*>, mapTechnicalAttributeBoolean, dest, technicalAttributeBoolean, false /* initialize value as false, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havevideoTechnicalAttributeAnyURI, getvideoTechnicalAttributeAnyURI, technicalAttributeUriType, videoFormatType::technicalAttributeUri_sequence, 
		std::vector<ebucoreTechnicalAttributeAnyURI*>, mapTechnicalAttributeAnyURI, dest, technicalAttributeUri, "" /* initialize value as "", will be replaced by mapping method */)
}

void mapCaptioning(ebucoreCaptioning* source, captioningFormat& dest) {
	SIMPLE_RMAP_OPTIONAL(source, havecaptioningFormatID, getcaptioningFormatID, dest, captioningFormatId)
	SIMPLE_RMAP_OPTIONAL(source, havecaptioningFormatName, getcaptioningFormatName, dest, captioningFormatName)
	SIMPLE_RMAP_OPTIONAL(source, havecaptioningSourceUri, getcaptioningSourceUri, dest, captioningSourceUri)
	SIMPLE_RMAP_OPTIONAL(source, havecaptioningLanguageCode, getcaptioningLanguageCode, dest, language)
	SIMPLE_RMAP_OPTIONAL(source, havecaptioningTrackID, getcaptioningTrackID, dest, trackId)
	SIMPLE_RMAP_OPTIONAL(source, havecaptioningTrackName, getcaptioningTrackName, dest, trackName)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havecaptioningTypeGroup, getcaptioningTypeGroup, dest, captioningFormat)
	RMAP_FORMAT_GROUP_GET_OPTIONAL(source, havecaptioningFormatGroup, getcaptioningFormatGroup, dest, captioningFormat)
}

void mapSubtitling(ebucoreSubtitling* source, subtitlingFormat& dest) {
	SIMPLE_RMAP_OPTIONAL(source, havesubtitlingFormatID, getsubtitlingFormatID, dest, subtitlingFormatId)
	SIMPLE_RMAP_OPTIONAL(source, havesubtitlingFormatName, getsubtitlingFormatName, dest, subtitlingFormatName)
	SIMPLE_RMAP_OPTIONAL(source, havesubtitlingSourceUri, getsubtitlingSourceUri, dest, subtitlingSourceUri)
	SIMPLE_RMAP_OPTIONAL(source, havesubtitlingLanguageCode, getsubtitlingLanguageCode, dest, language)
	SIMPLE_RMAP_OPTIONAL(source, havesubtitlingTrackID, getsubtitlingTrackID, dest, trackId)
	SIMPLE_RMAP_OPTIONAL(source, havesubtitlingTrackName, getsubtitlingTrackName, dest, trackName)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havesubtitlingTypeGroup, getsubtitlingTypeGroup, dest, subtitlingFormat)
	RMAP_FORMAT_GROUP_GET_OPTIONAL(source, havesubtitlingFormatGroup, getsubtitlingFormatGroup, dest, subtitlingFormat)
}

void mapSigning(ebucoreSigningFormat* source, signingFormat& dest) {
	SIMPLE_RMAP_OPTIONAL(source, havesigningFormatID, getsigningFormatID, dest, signingFormatId)
	SIMPLE_RMAP_OPTIONAL(source, havesigningFormatName, getsigningFormatName, dest, signingFormatName)
	SIMPLE_RMAP_OPTIONAL(source, havesigningSourceUri, getsigningSourceUri, dest, signingSourceUri)
	SIMPLE_RMAP_OPTIONAL(source, havesigningTrackLanguageCode, getsigningTrackLanguageCode, dest, language)
	SIMPLE_RMAP_OPTIONAL(source, havesigningTrackID, getsigningTrackID, dest, trackId)
	SIMPLE_RMAP_OPTIONAL(source, havesigningTrackName, getsigningTrackName, dest, trackName)

	RMAP_TYPE_GROUP_GET_OPTIONAL(source, havesigningTypeGroup, getsigningTypeGroup, dest, signingFormat)
	RMAP_FORMAT_GROUP_GET_OPTIONAL(source, havesigningFormatGroup, getsigningFormatGroup, dest, signingFormat)
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
	SIMPLE_RMAP_OPTIONAL(source, havedataFormatVersionID, getdataFormatVersionID, dest, dataFormatVersionId)
	SIMPLE_RMAP_OPTIONAL(source, havedataFormatName, getdataFormatName, dest, dataFormatName)
	SIMPLE_RMAP_OPTIONAL(source, havedataFormatDefinition, getdataFormatDefinition, dest, dataFormatDefinition)

	SIMPLE_RMAP_OPTIONAL(source, havedataTrackId, getdataTrackId, dest, dataTrackId)
	SIMPLE_RMAP_OPTIONAL(source, havedataTrackName, getdataTrackName, dest, dataTrackName)
	SIMPLE_RMAP_OPTIONAL(source, havedataTrackLanguageCode, getdataTrackLanguageCode, dest, dataTrackLanguage)

	if (source->havecaptioning()) {
		NEW_VECTOR_AND_RASSIGN(source, getcaptioning, captioningFormat, dataFormatType::captioningFormat_sequence, std::vector<ebucoreCaptioning*>, mapCaptioning, dest, captioningFormat)
	}
	if (source->haveancillaryData()) {
		NEW_VECTOR_AND_RASSIGN(source, getancillaryData, ancillaryDataFormat, dataFormatType::ancillaryDataFormat_sequence, std::vector<ebucoreAncillaryData*>, mapAncillaryData, dest, ancillaryDataFormat)
	}
	if (source->havesubtitling()) {
		NEW_VECTOR_AND_RASSIGN(source, getsubtitling, subtitlingFormat, dataFormatType::subtitlingFormat_sequence, std::vector<ebucoreSubtitling*>, mapSubtitling, dest, subtitlingFormat)
	}

	NEW_VECTOR_AND_RASSIGN_OPTIONAL(source, havedataTechnicalAttributeString, getdataTechnicalAttributeString, String, dataFormatType::technicalAttributeString_sequence, 
		std::vector<ebucoreTechnicalAttributeString*>, mapTechnicalAttributeString, dest, technicalAttributeString)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havedataTechnicalAttributeInt8, getdataTechnicalAttributeInt8, Int8, dataFormatType::technicalAttributeByte_sequence, 
		std::vector<ebucoreTechnicalAttributeInt8*>, mapTechnicalAttributeInt8, dest, technicalAttributeByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havedataTechnicalAttributeInt16, getdataTechnicalAttributeInt16, Int16, dataFormatType::technicalAttributeShort_sequence, 
		std::vector<ebucoreTechnicalAttributeInt16*>, mapTechnicalAttributeInt16, dest, technicalAttributeShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havedataTechnicalAttributeInt32, getdataTechnicalAttributeInt32, Int32, dataFormatType::technicalAttributeInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeInt32*>, mapTechnicalAttributeInt32, dest, technicalAttributeInteger, 0 /* initialize value as 0, will be replaced by mapping method */)	
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havedataTechnicalAttributeInt64, getdataTechnicalAttributeInt64, Int64, dataFormatType::technicalAttributeLong_sequence, 
		std::vector<ebucoreTechnicalAttributeInt64*>, mapTechnicalAttributeInt64, dest, technicalAttributeLong, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havedataTechnicalAttributeUInt8, getdataTechnicalAttributeUInt8, UInt8, dataFormatType::technicalAttributeUnsignedByte_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt8*>, mapTechnicalAttributeUInt8, dest, technicalAttributeUnsignedByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havedataTechnicalAttributeUInt16, getdataTechnicalAttributeUInt16, UInt16, dataFormatType::technicalAttributeUnsignedShort_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt16*>, mapTechnicalAttributeUInt16, dest, technicalAttributeUnsignedShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havedataTechnicalAttributeUInt32, getdataTechnicalAttributeUInt32, UInt32, dataFormatType::technicalAttributeUnsignedInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt32*>, mapTechnicalAttributeUInt32, dest, technicalAttributeUnsignedInteger, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havedataTechnicalAttributeUInt64, getdataTechnicalAttributeUInt64, UInt64, dataFormatType::technicalAttributeUnsignedLong_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt64*>, mapTechnicalAttributeUInt64, dest, technicalAttributeUnsignedLong, 0 /* initialize value as 0, will be replaced by mapping method */)

	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havedataTechnicalAttributeFloat, getdataTechnicalAttributeFloat, Float, dataFormatType::technicalAttributeFloat_sequence, 
		std::vector<ebucoreTechnicalAttributeFloat*>, mapTechnicalAttributeFloat, dest, technicalAttributeFloat, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havedataTechnicalAttributeRational, getdataTechnicalAttributeRational, technicalAttributeRationalType, dataFormatType::technicalAttributeRational_sequence, 
		std::vector<ebucoreTechnicalAttributeRational*>, mapTechnicalAttributeRational, dest, technicalAttributeRational, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havedataTechnicalAttributeBoolean, getdataTechnicalAttributeBoolean, Boolean, dataFormatType::technicalAttributeBoolean_sequence, 
		std::vector<ebucoreTechnicalAttributeBoolean*>, mapTechnicalAttributeBoolean, dest, technicalAttributeBoolean, false /* initialize value as false, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havedataTechnicalAttributeAnyURI, getdataTechnicalAttributeAnyURI, technicalAttributeUriType, dataFormatType::technicalAttributeUri_sequence, 
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

	if (source->havecontainerFormat()) {
		formatType::containerFormat_sequence seq;
		std::auto_ptr<containerFormat> p( new containerFormat() );
		RMAP_FORMAT_GROUP(source->getcontainerFormat(), (*p), containerFormat::formatDefinition_type, containerFormat::formatLabel_type, containerFormat::formatLink_type, containerFormat::formatLanguage_type)
		dest.containerFormat(seq);
	}
	if (source->havemedium()) {
		formatType::medium_sequence seq;
		std::auto_ptr<medium> p( new medium() );
		mapMedium(source->getmedium(), *p);
		dest.medium(seq);
	}
	
	if (source->havepackageInfo()) {
		mapPackageInfo(source->getpackageInfo(), dest);
	}

	if (source->havemimeType()) {
		formatType::mimeType_sequence seq;
		std::auto_ptr<mimeType> p( new mimeType() );
		RMAP_TYPE_GROUP(source->getmimeType(), (*p), mimeType::typeDefinition_type, mimeType::typeLabel_type, mimeType::typeLink_type, mimeType::typeLanguage_type)
		dest.mimeType(seq);
	}

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

	NEW_VECTOR_AND_RASSIGN_OPTIONAL(source, havematerialTechnicalAttributeString, getmaterialTechnicalAttributeString, String, formatType::technicalAttributeString_sequence, 
		std::vector<ebucoreTechnicalAttributeString*>, mapTechnicalAttributeString, dest, technicalAttributeString)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havematerialTechnicalAttributeInt8, getmaterialTechnicalAttributeInt8, Int8, formatType::technicalAttributeByte_sequence, 
		std::vector<ebucoreTechnicalAttributeInt8*>, mapTechnicalAttributeInt8, dest, technicalAttributeByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havematerialTechnicalAttributeInt16, getmaterialTechnicalAttributeInt16, Int16, formatType::technicalAttributeShort_sequence, 
		std::vector<ebucoreTechnicalAttributeInt16*>, mapTechnicalAttributeInt16, dest, technicalAttributeShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havematerialTechnicalAttributeInt32, getmaterialTechnicalAttributeInt32, Int32, formatType::technicalAttributeInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeInt32*>, mapTechnicalAttributeInt32, dest, technicalAttributeInteger, 0 /* initialize value as 0, will be replaced by mapping method */)	
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havematerialTechnicalAttributeInt64, getmaterialTechnicalAttributeInt64, Int64, formatType::technicalAttributeLong_sequence, 
		std::vector<ebucoreTechnicalAttributeInt64*>, mapTechnicalAttributeInt64, dest, technicalAttributeLong, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havematerialTechnicalAttributeUInt8, getmaterialTechnicalAttributeUInt8, UInt8, formatType::technicalAttributeUnsignedByte_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt8*>, mapTechnicalAttributeUInt8, dest, technicalAttributeUnsignedByte, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havematerialTechnicalAttributeUInt16, getmaterialTechnicalAttributeUInt16, UInt16, formatType::technicalAttributeUnsignedShort_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt16*>, mapTechnicalAttributeUInt16, dest, technicalAttributeUnsignedShort, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havematerialTechnicalAttributeUInt32, getmaterialTechnicalAttributeUInt32, UInt32, formatType::technicalAttributeUnsignedInteger_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt32*>, mapTechnicalAttributeUInt32, dest, technicalAttributeUnsignedInteger, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havematerialTechnicalAttributeUInt64, getmaterialTechnicalAttributeUInt64, UInt64, formatType::technicalAttributeUnsignedLong_sequence, 
		std::vector<ebucoreTechnicalAttributeUInt64*>, mapTechnicalAttributeUInt64, dest, technicalAttributeUnsignedLong, 0 /* initialize value as 0, will be replaced by mapping method */)

	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havematerialTechnicalAttributeFloat, getmaterialTechnicalAttributeFloat, Float, formatType::technicalAttributeFloat_sequence, 
		std::vector<ebucoreTechnicalAttributeFloat*>, mapTechnicalAttributeFloat, dest, technicalAttributeFloat, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havematerialTechnicalAttributeRational, getmaterialTechnicalAttributeRational, technicalAttributeRationalType, formatType::technicalAttributeRational_sequence, 
		std::vector<ebucoreTechnicalAttributeRational*>, mapTechnicalAttributeRational, dest, technicalAttributeRational, 0 /* initialize value as 0, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havematerialTechnicalAttributeBoolean, getmaterialTechnicalAttributeBoolean, Boolean, formatType::technicalAttributeBoolean_sequence, 
		std::vector<ebucoreTechnicalAttributeBoolean*>, mapTechnicalAttributeBoolean, dest, technicalAttributeBoolean, false /* initialize value as false, will be replaced by mapping method */)
	NEW_VECTOR_AND_RASSIGN_OPTIONAL_CARGS(source, havematerialTechnicalAttributeAnyURI, getmaterialTechnicalAttributeAnyURI, technicalAttributeUriType, formatType::technicalAttributeUri_sequence, 
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
	if (source->havesubject()) { NEW_VECTOR_AND_RASSIGN(source, getsubject, subjectType, coreMetadataType::subject_sequence, std::vector<ebucoreSubject*>, mapSubject, dest, subject) }
	
	if (source->havetype()) { NEW_VECTOR_AND_RASSIGN(source, gettype, typeType, coreMetadataType::type_sequence, std::vector<ebucoreType*>, mapType, dest, type) }

	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havepublicationHistory, getpublicationHistory, publicationHistoryType, mapPublicationHistory, dest, publicationHistory)

	if (source->havedate()) { NEW_VECTOR_AND_RASSIGN(source, getdate, dateType, coreMetadataType::date_sequence, std::vector<ebucoreDate*>, mapDate, dest, date) }
	if (source->havelanguage()) { NEW_VECTOR_AND_RASSIGN(source, getlanguage, languageType, coreMetadataType::language_sequence, std::vector<ebucoreLanguage*>, mapLanguage, dest, language) }
	if (source->havecoverage()) { NEW_VECTOR_AND_RASSIGN(source, getcoverage, coverageType, coreMetadataType::coverage_sequence, std::vector<ebucoreCoverage*>, mapMetadataCoverage, dest, coverage) }

	if (source->haverating()) {
		NEW_VECTOR_AND_RASSIGN(source, getrating, ratingType, coreMetadataType::rating_sequence, std::vector<ebucoreRating*>, mapRating, dest, rating)
	}

	if (source->haveversion()) {
		coreMetadataType::version_sequence seq;
		std::auto_ptr<versionType> p( new versionType() );
		mapVersion(source->getversion(), *p);
		dest.version(seq);
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

} // namespace EBUCore_1_4
} // namespace EBUCore
} // namespace EBUSDK
