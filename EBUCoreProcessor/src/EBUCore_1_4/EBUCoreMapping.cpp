/*#include <iostream>
#include <fstream>
#include <memory>

#include <bmx/BMXException.h>
#include <bmx/Logging.h>*/

#include "EBUCore_1_4/EBUCoreMapping.h"
#include "AppUtils.h"

#include <xercesc/util/TransService.hpp>

using namespace ebuCore_2012;
using namespace mxfpp;
//using namespace bmx;

namespace EBUSDK {
namespace EBUCore {
namespace EBUCore_1_4 {

#define	SIMPLE_MAP(source, sourceProperty, dest, destProperty)	\
	dest->destProperty(source.sourceProperty().get());
#define	SIMPLE_MAP_NO_GET(source, sourceProperty, dest, destProperty)	\
	dest->destProperty(source.sourceProperty());

#define	SIMPLE_MAP_OPTIONAL(source, sourceProperty, dest, destProperty)	\
	if (source.sourceProperty().present())	\
		dest->destProperty(source.sourceProperty().get());
#define	SIMPLE_MAP_OPTIONAL_CONVERT(source, sourceProperty, dest, destProperty, convertFunction)	\
	if (source.sourceProperty().present())	\
		dest->destProperty(convertFunction(source.sourceProperty().get()));

#define NEW_OBJECT_AND_ASSIGN(source, sourceProperty, destType, mapMethod, dest, destProperty) \
	{	\
		destType *obj = newAndModifyObject<destType>(dest->getHeaderMetadata(), mod);	\
		mapMethod(source.sourceProperty(), obj, mod);	\
		dest->destProperty(obj);	\
	}
#define NEW_OBJECT_AND_ASSIGN_DIRECT(source, destType, mapMethod, dest, destProperty) \
	{	\
		destType *obj = newAndModifyObject<destType>(dest->getHeaderMetadata(), mod);	\
		mapMethod(source, obj, mod);	\
		dest->destProperty(obj);	\
	}

#define NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, sourceProperty, destType, mapMethod, dest, destProperty) \
	if (source.sourceProperty().present()) {	\
		destType *obj = newAndModifyObject<destType>(dest->getHeaderMetadata(), mod);	\
		mapMethod(source.sourceProperty().get(), obj, mod);	\
		dest->destProperty(obj);	\
	}

#define NEW_VECTOR_AND_ASSIGN(source, sourceProperty, destType, iteratorType, mapMethod, dest, destProperty)	\
	if (source.sourceProperty().size() > 0)	\
	{   std::vector<destType*> vec_dest_destProperty;	\
		for (iteratorType it = source.sourceProperty().begin(); it != source.sourceProperty().end(); it++) {	\
			destType *obj = newAndModifyObject<destType>(dest->getHeaderMetadata(), mod);	\
			mapMethod(*it, obj, mod);	\
			vec_dest_destProperty.push_back(obj);	\
		}	\
		dest->destProperty(vec_dest_destProperty); }

#define NEW_VECTOR_AND_APPEND(source, sourceProperty, destType, iteratorType, mapMethod, dest, destVector)	\
	{ \
	for (iteratorType it = source.sourceProperty().begin(); it != source.sourceProperty().end(); it++) {	\
		destType *obj = newAndModifyObject<destType>(dest->getHeaderMetadata(), mod);	\
		mapMethod(*it, obj, mod);	\
		destVector.push_back(obj);	\
	} }

#define	SIMPLE_MAP_OPTIONAL_TO_NEW_VECTOR_AND_ASSIGN(source, sourceProperty, destType, mapMethod, dest, destProperty) \
	if (source.sourceProperty().present()) {	\
		destType *obj = newAndModifyObject<destType>(dest->getHeaderMetadata(), mod);	\
		mapMethod(source.sourceProperty().get(), obj, mod);	\
		std::vector<destType*> v_dest_destProperty;	\
		v_dest_destProperty.push_back(obj);	\
		dest->destProperty(v_dest_destProperty);	\
	}

#define MAP_TYPE_GROUP(source, dest)	\
	SIMPLE_MAP_OPTIONAL(source, typeDefinition, dest, settypeGroupDefinition) \
	SIMPLE_MAP_OPTIONAL(source, typeLabel, dest, settypeGroupLabel) \
	SIMPLE_MAP_OPTIONAL(source, typeLink, dest, settypeGroupLink) \
	SIMPLE_MAP_OPTIONAL(source, typeLanguage, dest, settypeGroupLanguage)

	/*
	This macro is not defined as a function since typeGroups are not separate types 
	but are more like duck typing (just a group of included attributes).
	Same for other such groups (format-, status-)
	*/

#define MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, destProperty) \
	ebucoreTypeGroup *typeGroup = newAndModifyObject<ebucoreTypeGroup>(dest->getHeaderMetadata(), mod);	\
	MAP_TYPE_GROUP(source, typeGroup)	\
	dest->destProperty(typeGroup);	\


#define MAP_STATUS_GROUP(source, dest)	\
	SIMPLE_MAP_OPTIONAL(source, statusDefinition, dest, setstatusGroupDefinition) \
	SIMPLE_MAP_OPTIONAL(source, statusLabel, dest, setstatusGroupLabel) \
	SIMPLE_MAP_OPTIONAL(source, statusLink, dest, setstatusGroupLink) \
	SIMPLE_MAP_OPTIONAL(source, statusLanguage, dest, setstatusGroupLanguage)

#define MAP_NEW_STATUS_GROUP_AND_ASSIGN(source, dest, destProperty) \
	ebucoreStatusGroup *statusGroup = newAndModifyObject<ebucoreStatusGroup>(dest->getHeaderMetadata(), mod); \
	MAP_STATUS_GROUP(source, statusGroup)	\
	dest->destProperty(statusGroup);


#define MAP_FORMAT_GROUP(source, dest)	\
	SIMPLE_MAP_OPTIONAL(source, formatDefinition, dest, setformatGroupDefinition) \
	SIMPLE_MAP_OPTIONAL(source, formatLabel, dest, setformatGroupLabel) \
	SIMPLE_MAP_OPTIONAL(source, formatLink, dest, setformatGroupLink) \
	SIMPLE_MAP_OPTIONAL(source, formatLanguage, dest, setformatGroupLanguage)

#define MAP_NEW_FORMAT_GROUP_AND_ASSIGN(source, dest, destProperty) \
	ebucoreFormatGroup *statusGroup = newAndModifyObject<ebucoreFormatGroup>(dest->getHeaderMetadata(), mod);	\
	MAP_FORMAT_GROUP(source, statusGroup)	\
	dest->destProperty(statusGroup);

template <class T> T* newAndModifyObject(HeaderMetadata *headerMetadata, ObjectModifier *mod) {
	T *obj = new T(headerMetadata);
	if (mod != NULL)
		mod->Modify(obj);
	return obj;
}

void mapRole(role& source, ebucoreRole *dest, ObjectModifier* mod = NULL) {
	// [TODO]
	// [XSD] Fix attribute type of costcenter to string so we can map it here
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setroleTypeGroup)
}

void mapTextualAnnotation(std::string source, ebucoreTextualAnnotation *dest, ObjectModifier* mod = NULL) {
	/* cannot deal with lang as source is single string */
	dest->settext(source);
}

void mapTextualAnnotation(dc::elementType source, ebucoreTextualAnnotation *dest, ObjectModifier* mod = NULL) {
	dest->settext(source);
	dest->settextLanguage(source.lang());
}

void mapCountry(country& source, ebucoreCountry *dest, ObjectModifier* mod = NULL) {
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setcountryTypeGroup)
}

void mapCountry(regionType::country_type& source, ebucoreCountry *dest, ObjectModifier* mod = NULL) {
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setcountryTypeGroup)
}

void mapAddress(addressType& source, ebucoreAddress *dest, ObjectModifier* mod = NULL) {

	if (source.addressLine().size() > 0) {
		NEW_VECTOR_AND_ASSIGN(source, addressLine, ebucoreTextualAnnotation, addressType::addressLine_iterator, mapTextualAnnotation, dest, setaddressLines)
	}
	
	SIMPLE_MAP_OPTIONAL_TO_NEW_VECTOR_AND_ASSIGN(source, addressTownCity, ebucoreTextualAnnotation, mapTextualAnnotation, dest, settownCity)
	SIMPLE_MAP_OPTIONAL_TO_NEW_VECTOR_AND_ASSIGN(source, addressCountyState, ebucoreTextualAnnotation, mapTextualAnnotation, dest, setcountyState)
	SIMPLE_MAP_OPTIONAL(source, addressDeliveryCode, dest, setdeliveryCode)
	SIMPLE_MAP_OPTIONAL_TO_NEW_VECTOR_AND_ASSIGN(source, country, ebucoreCountry, mapCountry, dest, setcountry)
}

void mapDetails(detailsType& source, ebucoreContactDetails *dest, ObjectModifier* mod = NULL) {
	
	if (source.emailAddress().size() > 0) {
		dest->setemailAddress(source.emailAddress()[0]);
	}
	
	SIMPLE_MAP_OPTIONAL(source, webAddress, dest, setwebAddress)

	// map address
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, address, ebucoreAddress, mapAddress, dest, setaddress)
	SIMPLE_MAP_OPTIONAL(source, telephoneNumber, dest, settelephoneNumber)
	SIMPLE_MAP_OPTIONAL(source, mobileTelephoneNumber, dest, setmobileTelephoneNumber)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setdetailsType)
}

void mapName(compoundNameType& source, ebucoreCompoundName *dest, ObjectModifier* mod = NULL) {
	dest->setcompoundName(source);
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setcompoundNameTypeGroup)
	MAP_NEW_FORMAT_GROUP_AND_ASSIGN(source, dest, setcompoundNameFormatGroup)
}

void mapIdentifier(identifierType& source, ebucoreIdentifier *dest, ObjectModifier* mod = NULL);

void mapBasicLink(relatedInformationLink& source, ebucoreBasicLink *dest, ObjectModifier* mod = NULL) {
	dest->setbasicLinkURI(source);
}

void mapBasicLink(relatedInformationLink1& source, ebucoreBasicLink *dest, ObjectModifier* mod = NULL) {
	dest->setbasicLinkURI(source);
}

void mapContact(contactDetailsType& source, ebucoreContact *dest, ObjectModifier* mod = NULL) {

	SIMPLE_MAP_OPTIONAL(source, contactId, dest, setcontactId)

	NEW_VECTOR_AND_ASSIGN(source, name, ebucoreCompoundName, contactDetailsType::name_iterator, mapName, dest, setcontactName)

	SIMPLE_MAP_OPTIONAL(source, givenName, dest, setgivenName)
	SIMPLE_MAP_OPTIONAL(source, familyName, dest, setfamilyName)
	SIMPLE_MAP_OPTIONAL(source, suffix, dest, setsuffix)
	SIMPLE_MAP_OPTIONAL(source, salutation, dest, setsalutation)
	SIMPLE_MAP_OPTIONAL(source, guest, dest, setguestFlag)

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, gender, ebucoreTextualAnnotation, mapTextualAnnotation, dest, setgender)
	NEW_VECTOR_AND_ASSIGN(source, otherGivenName, ebucoreTextualAnnotation, contactDetailsType::otherGivenName_iterator, mapTextualAnnotation, dest, setotherGivenName)
	
	if (source.username().size() > 0) {
		dest->setusername(source.username()[0]);
	}
	SIMPLE_MAP_OPTIONAL(source, occupation, dest, setoccupation)
	NEW_VECTOR_AND_ASSIGN(source, details, ebucoreContactDetails, contactDetailsType::details_sequence::iterator, mapDetails, dest, setcontactDetails)
	NEW_VECTOR_AND_ASSIGN(source, stageName, ebucoreTextualAnnotation, contactDetailsType::stageName_iterator, mapTextualAnnotation, dest, setstageName)
	NEW_VECTOR_AND_ASSIGN(source, relatedContacts, ebucoreEntity, contactDetailsType::relatedContacts_iterator, mapEntity, dest, setcontactRelatedContacts)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setcontactType)

	NEW_VECTOR_AND_ASSIGN(source, relatedInformationLink, ebucoreBasicLink, contactDetailsType::relatedInformationLink_iterator, mapBasicLink, dest, setcontactRelatedInformationLink)
}

void mapOrganisationDepartment(organisationDepartment& source, ebucoreOrganisationDepartment *dest, ObjectModifier* mod = NULL) {
	dest->setdepartmentName(source);
	SIMPLE_MAP_OPTIONAL(source, departmentId, dest, setdepartmentId)
}

void mapOrganisation(organisationDetailsType& source, ebucoreOrganisation *dest, ObjectModifier* mod = NULL) {

	// [TODO] The KLV mapping is somewhat inconsistent at this point with the XSD:
	//		- XSD departmentId is not present in KLV

	SIMPLE_MAP_OPTIONAL(source, organisationId, dest, setorganisationId)

	NEW_VECTOR_AND_ASSIGN(source, organisationName, ebucoreCompoundName, organisationDetailsType::organisationName_iterator, mapName, dest, setorganisationName)
	NEW_VECTOR_AND_ASSIGN(source, organisationCode, ebucoreIdentifier, organisationDetailsType::organisationCode_iterator, mapIdentifier, dest, setorganisationCode)

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, organisationDepartment, ebucoreOrganisationDepartment, mapOrganisationDepartment, dest, setorganisationDepartment)

	NEW_VECTOR_AND_ASSIGN(source, details, ebucoreContactDetails, contactDetailsType::details_sequence::iterator, mapDetails, dest, setorganisationDetails)
	NEW_VECTOR_AND_ASSIGN(source, contacts, ebucoreEntity, organisationDetailsType::contacts_iterator, mapEntity, dest, setorganisationRelatedContacts)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setorganisationType)

	NEW_VECTOR_AND_ASSIGN(source, relatedInformationLink, ebucoreBasicLink, organisationDetailsType::relatedInformationLink_iterator, 
		mapBasicLink, dest, setorganisationRelatedInformationLink)
}

void mapEntity(entityType& source, ebucoreEntity *dest, ObjectModifier* mod) {
	SIMPLE_MAP_OPTIONAL(source, entityId, dest, setentityId)
	NEW_VECTOR_AND_ASSIGN(source, contactDetails, ebucoreContact, entityType::contactDetails_iterator, mapContact, dest, setentityContact)
	NEW_VECTOR_AND_ASSIGN(source, organisationDetails, ebucoreOrganisation, entityType::organisationDetails_iterator, mapOrganisation, dest, setentityOrganisation)
	NEW_VECTOR_AND_ASSIGN(source, role, ebucoreRole, entityType::role_iterator, mapRole, dest, setentityRole)
}

void mapMetadataSchemeInformation(ebuCoreMainType& source, ebucoreMetadataSchemeInformation *dest, ObjectModifier* mod) {
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

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, metadataProvider, ebucoreEntity, mapEntity, dest, setebucoreMetadataProvider)

	// is there a version node? appearently, no easier way to check than
	// to look through the attributes of the source node and see if there 
	// is a matching attribute
	xercesc::DOMNamedNodeMap* attrs = source._node()->getAttributes();
	XMLCh* str_version = xercesc::XMLString::transcode("version");
	const xercesc::DOMNode* version_node = attrs->getNamedItem(str_version);
	xercesc::XMLString::release(&str_version);
	if (version_node != NULL) {
		xercesc::TranscodeToStr version(source.version()._node()->getTextContent(), "UTF-8");
		std::string std_version((char*)version.str());
		dest->setebucoreMetadataSchemeVersion(std_version);
	}
	/* EBUCore1.4:
	XMLCh* str_schema = xercesc_3_1::XMLString::transcode("schema");
	const xercesc_3_1::DOMNode* schema_node = attrs->getNamedItem(str_schema);
	xercesc_3_1::XMLString::release(&str_schema);
	if (schema_node != NULL) {
		xercesc_3_1::TranscodeToStr schema(source.schema()._node()->getTextContent(), "UTF-8");
		std::string std_schema((char*)schema.str());
		dest->setebucoreMetadataScheme(std_schema);
	}*/
}

mxfTimestamp convert_timestamp(xml_schema::date& source) {
	mxfTimestamp ts = {0,0,0,0,0,0,0};
	ts.day = source.day();
	ts.month = source.month();
	ts.year = source.year();
	return ts;
}

mxfTimestamp convert_timestamp(xml_schema::gyear& source) {
	mxfTimestamp ts = {0,0,0,0,0,0,0};
	ts.year = source.year();
	return ts;
}

std::string convert(xml_schema::gyear& source) {
	std::stringstream ss;
	ss << source.year();
	return ss.str();
}

std::string convert(xml_schema::date& source) {
	std::stringstream ss;
	ss << source.day() << '/' << source.month() << '/' << source.year();
	return ss.str();
}

std::string convert(xml_schema::time& source) {
	std::stringstream ss;
	ss << source.hours() << ':' << source.minutes() << ':' << source.seconds();
	return ss.str();
}

mxfTimestamp convert_timestamp(xml_schema::time& source) {
	mxfTimestamp ts = {0,0,0,0,0,0,0};
	ts.hour = source.hours();
	ts.min = source.minutes();
	ts.sec = source.seconds();
	return ts;
}

std::string convert(xml_schema::idrefs& source) {
	std::stringstream ss;
	size_t l = source.size(); size_t i = 0;
	for (xml_schema::idrefs::iterator it = source.begin(); it != source.end(); it++) {
		i++;
		ss << (*it);
		if (i < l) ss << ' ';
	}
	return ss.str();
}

mxfRational convert(xml_schema::long_& source) {
	mxfRational r = {source, 1};
	return r;
}

mxfRational convert(rationalType& source) {
	mxfRational r = {source.factorNumerator(), source.factorDenominator()};
	return r;
}

std::string convert_to_string(::xml_schema::integer& source) {
	std::stringstream ss;
	ss << source;
	return ss.str();
}

mxfRational convert_rational(xml_schema::duration& source) {
	mxfRational r = { 
	   (source.years() * 365 * 86400 + 
		source.months() * 30 * 86400 + 
		source.days() * 86400 + 
		source.hours() * 3600 + 
		source.minutes() * 60 + 
		source.seconds()) * 100,
	100};
	return r;
}

mxfRational convert_rational(xml_schema::time& source) {
	mxfRational r = { 
	   (source.hours() * 3600 + 
		source.minutes() * 60 + 
		source.seconds()) * 100,
	100};
	return r;
}

void mapTitle(titleType& source, ebucoreTitle *dest, ObjectModifier* mod = NULL) {
	NEW_VECTOR_AND_ASSIGN(source, title, ebucoreTextualAnnotation, titleType::title_iterator, mapTextualAnnotation, dest, settitleValue)

	SIMPLE_MAP_OPTIONAL(source, note, dest, settitleNote)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, attributiondate, dest, settitleAttributionDate, convert_timestamp)
}

void mapAlternativeTitle(alternativeTitleType& source, ebucoreAlternativeTitle *dest, ObjectModifier* mod = NULL) {
	NEW_VECTOR_AND_ASSIGN(source, title, ebucoreTextualAnnotation, alternativeTitleType::title_iterator, mapTextualAnnotation, dest, setalternativeTitleValue)
	SIMPLE_MAP_OPTIONAL(source, note, dest, setalternativeTitleNote)

	SIMPLE_MAP_OPTIONAL_CONVERT(source, startDate, dest, setalternativeTitleAttributionDate, convert_timestamp)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setalternativeTitleTypeGroup)
	MAP_NEW_STATUS_GROUP_AND_ASSIGN(source, dest, setalternativeTitleStatusGroup)
}

void mapIdentifier(identifierType& source, ebucoreIdentifier *dest, ObjectModifier* mod) {
	SIMPLE_MAP_NO_GET(source, identifier, dest, setidentifierValue)
	SIMPLE_MAP_OPTIONAL(source, note, dest, setidentifierNote)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setidentifierTypeGroup)
	MAP_NEW_FORMAT_GROUP_AND_ASSIGN(source, dest, setidentifierFormatGroup)

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, attributor, ebucoreEntity, mapEntity, dest, setidentifierAttributorEntity)
}

void mapDescription(descriptionType& source, ebucoreDescription *dest, ObjectModifier* mod = NULL) {
	NEW_VECTOR_AND_ASSIGN(source, description, ebucoreTextualAnnotation, descriptionType::description_iterator, mapTextualAnnotation, dest, setdescriptionValue)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setdescriptionTypeGroup)
	SIMPLE_MAP_OPTIONAL(source, note, dest, setdescriptionNote)
}

void mapSubject(subjectType& source, ebucoreSubject *dest, ObjectModifier* mod = NULL) {
	NEW_VECTOR_AND_ASSIGN(source, subject, ebucoreTextualAnnotation, subjectType::subject_const_iterator, mapTextualAnnotation, dest, setsubjectValue)

	SIMPLE_MAP_OPTIONAL(source, subjectCode, dest, setsubjectCode)
	NEW_VECTOR_AND_ASSIGN(source, subjectDefinition, ebucoreTextualAnnotation, subjectType::subjectDefinition_const_iterator, mapTextualAnnotation, dest, setsubjectDefinition)
	SIMPLE_MAP_OPTIONAL(source, note, dest, setsubjectNote)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setsubjectTypeGroup)

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, attributor, ebucoreEntity, mapEntity, dest, setsubjectAttributorEntity)
}

void mapRegion(regionType& source, ebucoreRegion *dest, ObjectModifier* mod = NULL) {
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, country, ebucoreCountry, mapCountry, dest, setcountry)
	if (source.countryRegion().size() > 0) {
		MAP_NEW_TYPE_GROUP_AND_ASSIGN(source.countryRegion()[0], dest, setcountryRegion)
	}
}

void mapRating(ratingType& source, ebucoreRating *dest, ObjectModifier* mod = NULL) {

	NEW_VECTOR_AND_ASSIGN(source, ratingValue, ebucoreTextualAnnotation, ratingType::ratingValue_const_iterator, mapTextualAnnotation, dest, setratingValue)
	NEW_VECTOR_AND_ASSIGN(source, ratingScaleMaxValue, ebucoreTextualAnnotation, ratingType::ratingScaleMaxValue_const_iterator, mapTextualAnnotation, dest, setratingScaleMaxValue)
	NEW_VECTOR_AND_ASSIGN(source, ratingScaleMinValue, ebucoreTextualAnnotation, ratingType::ratingScaleMinValue_const_iterator, mapTextualAnnotation, dest, setratingScaleMinValue)

	SIMPLE_MAP_OPTIONAL(source, reason, dest, setratingReason)
	SIMPLE_MAP_OPTIONAL(source, linkToLogo, dest, setratingLinkToLogo)
	SIMPLE_MAP_OPTIONAL(source, notRated, dest, setratingNotRatedFlag)
	SIMPLE_MAP_OPTIONAL(source, adultContent, dest, setratingAdultContentFlag)

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, ratingProvider, ebucoreEntity, mapEntity, dest, setratingProviderEntity)

	if (source.ratingRegion().size() > 0) {
		NEW_OBJECT_AND_ASSIGN_DIRECT(source.ratingRegion()[0], ebucoreRegion, mapRegion, dest, setratingRegion)
	}

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setratingTypeGroup)
	MAP_NEW_FORMAT_GROUP_AND_ASSIGN(source, dest, setratingFormatGroup)
}

void mapVersion(coreMetadataType::version_type& source, ebucoreVersion *dest, ObjectModifier* mod = NULL) {
	ebucoreTextualAnnotation *obj = newAndModifyObject<ebucoreTextualAnnotation>(dest->getHeaderMetadata(), mod);
	mapTextualAnnotation(source, obj, mod);
	std::vector<ebucoreTextualAnnotation*> v_dest_destProperty;
	v_dest_destProperty.push_back(obj);
	dest->setversionValue(v_dest_destProperty);

 	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setversionTypeGroup)
}

void mapLanguage(languageType& source, ebucoreLanguage *dest, ObjectModifier* mod = NULL) {

	// TODO: KLV Language has an indirection for languagepurpose via a languagepurposeset which contains
	// only a reference to the typegroup, required?
	SIMPLE_MAP_OPTIONAL(source, language, dest, setlanguageCode)
	if (source.language().present()) {
		dest->setlanguageLanguageCode(source.language().get().lang());
	}
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setlanguagePurposeSet)
	SIMPLE_MAP_OPTIONAL(source, note, dest, setlanguageNote)
}

void mapTargetAudience(targetAudience& source, ebucoreTargetAudience *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, reason, dest, settargetAudienceReason)
	SIMPLE_MAP_OPTIONAL(source, linkToLogo, dest, settargetAudienceLinkToLogo)
	SIMPLE_MAP_OPTIONAL(source, notRated, dest, settargetAudienceNotRatedFlag)
	SIMPLE_MAP_OPTIONAL(source, adultContent, dest, settargetAudienceAdultContentFlag)

	NEW_VECTOR_AND_ASSIGN(source, targetRegion, ebucoreRegion, targetAudience::targetRegion_iterator, mapRegion, dest, settargetAudienceRegion)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, settargetAudienceTypeGroup)
}

void mapGenre(genre& source, ebucoreGenre *dest, ObjectModifier* mod = NULL) {
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setgenreKindGroup)
}

void mapType(typeType& source, ebucoreType *dest, ObjectModifier* mod = NULL) {

	NEW_VECTOR_AND_ASSIGN(source, type, ebucoreTextualAnnotation, typeType::type_iterator, mapTextualAnnotation, dest, settypeValue)
	
	std::vector<ebucoreObjectType*> vec_dest_objecttype;
	for (typeType::objectType_iterator it = source.objectType().begin(); it != source.objectType().end(); it++) {
		ebucoreObjectType *obj = newAndModifyObject<ebucoreObjectType>(dest->getHeaderMetadata(), mod);
		MAP_NEW_TYPE_GROUP_AND_ASSIGN(source.objectType().front(), obj, setobjectTypeGroup)
		vec_dest_objecttype.push_back(obj);
	}
	dest->setobjectType(vec_dest_objecttype);

	NEW_VECTOR_AND_ASSIGN(source, targetAudience, ebucoreTargetAudience, typeType::targetAudience_iterator, mapTargetAudience, dest, settargetAudience)
	NEW_VECTOR_AND_ASSIGN(source, genre, ebucoreGenre, typeType::genre_iterator, mapGenre, dest, setgenre)

	SIMPLE_MAP_OPTIONAL(source, note, dest, settypeNote)
}

void mapDateType(alternative& source, ebucoreDateType *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL_CONVERT(source, startDate, dest, setdateValue, convert_timestamp)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setdateTypeGroup)
}

void mapDate(dateType& source, ebucoreDate* dest, ObjectModifier* mod = NULL) {
	// no valid mapping currently for a single note element (DC date is candidate, but cardinality is wrong)

	if (source.created().present()) {
		dateType::created_type& date = source.created().get();
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startYear, dest, setyearCreated, convert_timestamp)
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startDate, dest, setdateCreated, convert_timestamp)
	}
	if (source.issued().present()) {
		dateType::issued_type& date = source.issued().get();
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startYear, dest, setyearIssued, convert_timestamp)
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startDate, dest, setdateIssued, convert_timestamp)
	}
	if (source.modified().present()) {
		dateType::modified_type& date = source.modified().get();
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startYear, dest, setyearModified, convert_timestamp)
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startDate, dest, setdateModified, convert_timestamp)
	}
	if (source.digitised().present()) {
		dateType::digitised_type& date = source.digitised().get();
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startYear, dest, setyearDigitized, convert_timestamp)
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startDate, dest, setdateDigitized, convert_timestamp)
	}
	if (source.released().present()) {
		dateType::released_type& date = source.released().get();
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startYear, dest, setyearReleased, convert_timestamp)
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startDate, dest, setdateReleased, convert_timestamp)
	}
	if (source.copyrighted().present()) {
		dateType::copyrighted_type& date = source.copyrighted().get();
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startYear, dest, setyearCopyrighted, convert_timestamp)
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startDate, dest, setdateCopyrighted, convert_timestamp)
	}

	NEW_VECTOR_AND_ASSIGN(source, alternative, ebucoreDateType, dateType::alternative_iterator, mapDateType, dest, setalternativeDate)
}

void mapPeriodOfTime(periodOfTimeType& source, ebucorePeriodOfTime* dest, ObjectModifier* mod = NULL) {
	// [TODO] PeriodId is at temporal level
	//SIMPLE_MAP_OPTIONAL(source, period, dest, setperiodId)
	SIMPLE_MAP_OPTIONAL_TO_NEW_VECTOR_AND_ASSIGN(source, periodName, ebucoreTextualAnnotation, mapTextualAnnotation, dest, setperiodName)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, startYear, dest, setperiodStartYear, convert_timestamp)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, startDate, dest, setperiodStartDate, convert_timestamp)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, startTime, dest, setperiodStartTime, convert_timestamp)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, endYear, dest, setperiodEndYear, convert_timestamp)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, endDate, dest, setperiodEndDate, convert_timestamp)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, endTime, dest, setperiodEndTime, convert_timestamp)
}

void mapTemporal(temporal& source, ebucoreTemporal *dest, ObjectModifier* mod = NULL) {
	// [EBUCore1.4] PeriodId in temporal??
	NEW_VECTOR_AND_ASSIGN(source, PeriodOfTime, ebucorePeriodOfTime, temporal::PeriodOfTime_iterator, mapPeriodOfTime, dest, setperiodOfTime)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, settemporalTypeGroup)
	SIMPLE_MAP_OPTIONAL(source, note, dest, settemporalDefinitionNote)
}

void mapCoordinates(coordinates& source, ebucoreCoordinates *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_NO_GET(source, posx, dest, setposX)
	SIMPLE_MAP_NO_GET(source, posy, dest, setposY)
	MAP_NEW_FORMAT_GROUP_AND_ASSIGN(source, dest, setcoordinatesFormatGroup)
}

void mapLocation(spatial::location_type& source, ebucoreLocation *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, locationId, dest, setlocationId)
	SIMPLE_MAP_OPTIONAL(source, code, dest, setlocationCode)
	SIMPLE_MAP_OPTIONAL(source, note, dest, setlocationDefinitionNote)

	SIMPLE_MAP_OPTIONAL_TO_NEW_VECTOR_AND_ASSIGN(source, name, ebucoreTextualAnnotation, mapTextualAnnotation, dest, setlocationName)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, region, ebucoreRegion, mapRegion, dest, setlocationRegion)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, coordinates, ebucoreCoordinates, mapCoordinates, dest, setlocationCoordinates)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setlocationTypeGroup)
}

void mapSpatial(spatial& source, ebucoreSpatial *dest, ObjectModifier* mod = NULL) {
	NEW_VECTOR_AND_ASSIGN(source, location, ebucoreLocation, spatial::location_iterator, mapLocation, dest, setlocation)
}

void mapMetadataCoverage(coverageType& source, ebucoreCoverage *dest, ObjectModifier* mod = NULL) {
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, coverage, ebucoreTextualAnnotation, mapTextualAnnotation, dest, setcoverageValue)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, temporal, ebucoreTemporal, mapTemporal, dest, settemporal)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, spatial, ebucoreSpatial, mapSpatial, dest, setspatial)
}

void mapRights(rightsType& source, ebucoreRights *dest, std::map<xml_schema::id, ebucoreFormat*>& formatMap, std::map<xml_schema::id, ebucoreRights*>& rightsMap, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, rightsID, dest, setrightsId)
	NEW_VECTOR_AND_ASSIGN(source, rightsAttributedId, ebucoreIdentifier, rightsType::rightsAttributedId_iterator, mapIdentifier, dest, setrightsAttributeID)
	NEW_VECTOR_AND_ASSIGN(source, rights, ebucoreTextualAnnotation, rightsType::rights_iterator, mapTextualAnnotation, dest, setrightsValue)
	SIMPLE_MAP_OPTIONAL(source, rightsClearanceFlag, dest, setrightsClearanceFlag)
	NEW_VECTOR_AND_ASSIGN(source, exploitationIssues, ebucoreTextualAnnotation, rightsType::exploitationIssues_iterator, mapTextualAnnotation, dest, setexploitationIssues)
	NEW_VECTOR_AND_ASSIGN(source, copyrightStatement, ebucoreTextualAnnotation, rightsType::copyrightStatement_iterator, mapTextualAnnotation, dest, setcopyrightStatement)
	SIMPLE_MAP_OPTIONAL(source, rightsLink, dest, setrightsLink)
	SIMPLE_MAP_OPTIONAL(source, note, dest, setrightsNote)

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, coverage, ebucoreCoverage, mapMetadataCoverage, dest, setrightsCoverage)

	NEW_VECTOR_AND_ASSIGN(source, rightsHolder, ebucoreEntity, rightsType::rightsHolder_iterator, mapEntity, dest, setrightsHolderEntity)

	NEW_VECTOR_AND_ASSIGN(source, contactDetails, ebucoreContact, rightsType::contactDetails_sequence::iterator, mapContact, dest, setrightsContacts)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setrightsTypeGroup)

	// [TODO] Deal with format references
	//SIMPLE_MAP_OPTIONAL_CONVERT(source, formatIDRefs, dest, setrightsFormatIDRef, convert)

	// find this formatIdRef in the map of formats
	if (source.formatIDRefs().present()) {
		std::vector<ebucoreFormat*> destRefs;
		rightsType::formatIDRefs_type& refs = source.formatIDRefs().get();
		for (xml_schema::idrefs::iterator it = refs.begin(); it != refs.end(); it++) {
			if (formatMap.find(*it) != formatMap.end()) {
				// present!
				destRefs.push_back(formatMap[*it]);
			}
		}
		if (destRefs.size() > 0)
			dest->setrightsFormatReferences(destRefs);
	}

	// and put the rights object in the map for further use
	if (source.rightsID().present()) {
		rightsMap[source.rightsID().get()] = dest;
	}
}

void mapPublicationChannel(publicationChannelType& source, ebucorePublicationChannel* dest, ObjectModifier* mod = NULL) {
	dest->setpublicationChannelName(source);
	SIMPLE_MAP_OPTIONAL(source, publicationChannelId, dest, setpublicationChannelId)
	SIMPLE_MAP_OPTIONAL(source, linkToLogo, dest, setpublicationChannelLinkToLogo)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setpublicationChannelType)
}

void mapPublicationMedium(publicationMediumType& source, ebucorePublicationMedium* dest, ObjectModifier* mod = NULL) {
	dest->setpublicationMediumName(source);
	SIMPLE_MAP_OPTIONAL(source, publicationMediumId, dest, setpublicationMediumName)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setpublicationMediumType)
}

void mapPublicationService(publicationServiceType& source, ebucorePublicationService* dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, publicationServiceName, dest, setpublicationServiceName)
	SIMPLE_MAP_OPTIONAL(source, linkToLogo, dest, setpublicationServiceLinkToLogo)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, publicationSource, ebucoreOrganisation, mapOrganisation, dest, setpublicationServiceSource)
}

void mapPublicationHistoryEvent(publicationEventType& source, ebucorePublicationHistoryEvent* dest, 
	std::map<xml_schema::id, ebucoreFormat*>& formatMap, std::map<xml_schema::id, ebucoreRights*>& rightsMap, ObjectModifier* mod = NULL) {

	SIMPLE_MAP_OPTIONAL(source, publicationEventName, dest, setpublicationEventName)
	SIMPLE_MAP_OPTIONAL(source, publicationEventId, dest, setpublicationEventId)
	SIMPLE_MAP_OPTIONAL(source, firstShowing, dest, setfirstPublicationFlag)
	SIMPLE_MAP_OPTIONAL(source, free, dest, setfreePublicationFlag)
	SIMPLE_MAP_OPTIONAL(source, live, dest, setlivePublicationFlag)
	SIMPLE_MAP_OPTIONAL(source, note, dest, setpublicationNote)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, publicationDate, dest, setpublicationDate, convert_timestamp)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, publicationTime, dest, setpublicationDate, convert_timestamp)

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, publicationChannel, ebucorePublicationChannel, mapPublicationChannel, dest, setpublicationChannel)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, publicationMedium, ebucorePublicationMedium, mapPublicationMedium, dest, setpublicationMedium)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, publicationService, ebucorePublicationService, mapPublicationService, dest, setpublicationService)

	NEW_VECTOR_AND_ASSIGN(source, publicationRegion, ebucoreRegion, publicationEventType::publicationRegion_iterator, mapRegion, dest, setpublicationRegion)

	if (source.formatIdRef().present()) {
		// find this formatIdRef in the map of formats
		if (formatMap.find(source.formatIdRef().get()) != formatMap.end()) {
			// present!
			dest->setpublicationFormatReference(formatMap[source.formatIdRef().get()]);
		}
	}

	if (source.rightsIDRefs().present()) {
		publicationEventType::rightsIDRefs_type& rightsrefs = source.rightsIDRefs().get();
		if (rightsrefs.size() > 0) {
			// for each of the references to a rights object, locate it in the rights map
			std::vector<ebucoreRights*> vec_rights;
			for (publicationEventType::rightsIDRefs_type::const_iterator it = rightsrefs.begin(); it != rightsrefs.end(); it++) {
				if (rightsMap.find(*it) != rightsMap.end()) {
					// present!
					vec_rights.push_back(rightsMap[*it]);
				}
			}
			dest->setpublicationRightsReference(vec_rights);
			// find this formatIdRef in the map of formats
		}
	}
}

void mapPublicationHistory(publicationHistoryType& source, ebucorePublicationHistory *dest, mxfpp::HeaderMetadata *header_metadata, 
	std::map<xml_schema::id, ebucoreFormat*>& formatMap, std::map<xml_schema::id, ebucoreRights*>& rightsMap, ObjectModifier* mod = NULL) {
	
	std::vector<ebucorePublicationHistoryEvent*> vec_dest_hist;
	for (publicationHistoryType::publicationEvent_iterator it = source.publicationEvent().begin(); it != source.publicationEvent().end(); it++) {
		ebucorePublicationHistoryEvent *obj = newAndModifyObject<ebucorePublicationHistoryEvent>(header_metadata, mod);
		// special case of conversion using the format map
		mapPublicationHistoryEvent(*it, obj, formatMap, rightsMap, mod);
		vec_dest_hist.push_back(obj);
	}
	dest->setpublicationEvent(vec_dest_hist);
}

#define MAP_BASIC_RELATION_FUNCTION(destProperty) \
	void mapBasicRelation_##destProperty(relationType& source, ebucoreBasicRelation *dest, ObjectModifier* mod = NULL) { \
		SIMPLE_MAP_OPTIONAL(source, relationLink, dest, destProperty) \
	}

MAP_BASIC_RELATION_FUNCTION(setisVersionOf)
MAP_BASIC_RELATION_FUNCTION(sethasVersion)
MAP_BASIC_RELATION_FUNCTION(setisReplacedBy)
MAP_BASIC_RELATION_FUNCTION(setreplaces)
MAP_BASIC_RELATION_FUNCTION(setisRequiredBy)
MAP_BASIC_RELATION_FUNCTION(setrequires)
MAP_BASIC_RELATION_FUNCTION(setisPartOf)
MAP_BASIC_RELATION_FUNCTION(sethasPart)
MAP_BASIC_RELATION_FUNCTION(setisReferencedBy)
MAP_BASIC_RELATION_FUNCTION(setreferences)
MAP_BASIC_RELATION_FUNCTION(setisFormatOf)
MAP_BASIC_RELATION_FUNCTION(sethasFormat)
MAP_BASIC_RELATION_FUNCTION(setisEpisodeOf)
MAP_BASIC_RELATION_FUNCTION(setisMemberOf)

void mapBasicRelations(coreMetadataType& source, ebucoreCoreMetadata *dest, ObjectModifier* mod = NULL) {
	std::vector<ebucoreBasicRelation*> rels;

	NEW_VECTOR_AND_APPEND(source, isVersionOf, ebucoreBasicRelation, 
		coreMetadataType::isVersionOf_iterator, mapBasicRelation_setisVersionOf, dest, rels)
	NEW_VECTOR_AND_APPEND(source, hasVersion, ebucoreBasicRelation, 
		coreMetadataType::hasVersion_iterator, mapBasicRelation_sethasVersion, dest, rels)
	NEW_VECTOR_AND_APPEND(source, isReplacedBy, ebucoreBasicRelation, 
		coreMetadataType::isReplacedBy_iterator, mapBasicRelation_setisReplacedBy, dest, rels)
	NEW_VECTOR_AND_APPEND(source, replaces, ebucoreBasicRelation, 
		coreMetadataType::replaces_iterator, mapBasicRelation_setreplaces, dest, rels)
	NEW_VECTOR_AND_APPEND(source, isRequiredBy, ebucoreBasicRelation, 
		coreMetadataType::isRequiredBy_iterator, mapBasicRelation_setisRequiredBy, dest, rels)
	NEW_VECTOR_AND_APPEND(source, requires, ebucoreBasicRelation, 
		coreMetadataType::requires_iterator, mapBasicRelation_setrequires, dest, rels)
	NEW_VECTOR_AND_APPEND(source, isPartOf, ebucoreBasicRelation, 
		coreMetadataType::isPartOf_iterator, mapBasicRelation_setisPartOf, dest, rels)
	NEW_VECTOR_AND_APPEND(source, hasPart, ebucoreBasicRelation, 
		coreMetadataType::hasPart_iterator, mapBasicRelation_sethasVersion, dest, rels)
	NEW_VECTOR_AND_APPEND(source, isReferencedBy, ebucoreBasicRelation, 
		coreMetadataType::isReferencedBy_iterator, mapBasicRelation_setisReferencedBy, dest, rels)
	NEW_VECTOR_AND_APPEND(source, references, ebucoreBasicRelation, 
		coreMetadataType::references_iterator, mapBasicRelation_setreferences, dest, rels)
	NEW_VECTOR_AND_APPEND(source, isFormatOf, ebucoreBasicRelation, 
		coreMetadataType::isFormatOf_iterator, mapBasicRelation_setisFormatOf, dest, rels)
	NEW_VECTOR_AND_APPEND(source, hasFormat, ebucoreBasicRelation, 
		coreMetadataType::hasFormat_iterator, mapBasicRelation_sethasFormat, dest, rels)
	NEW_VECTOR_AND_APPEND(source, isEpisodeOf, ebucoreBasicRelation, 
		coreMetadataType::isEpisodeOf_iterator, mapBasicRelation_setisEpisodeOf, dest, rels)
	NEW_VECTOR_AND_APPEND(source, isMemberOf, ebucoreBasicRelation, 
		coreMetadataType::isMemberOf_iterator, mapBasicRelation_setisMemberOf, dest, rels)

	dest->setbasicRelation(rels);
}

void mapCustomRelation(relationType& source, ebucoreCustomRelation *dest, ObjectModifier* mod = NULL) {
	// [TODO] XSD relationIdentifier is identifierType, KLV identifier is a UMID, how do we resolve?

	SIMPLE_MAP_OPTIONAL(source, relation, dest, setrelationByName)
	SIMPLE_MAP_OPTIONAL(source, relationLink, dest, setrelationLink)
	SIMPLE_MAP_OPTIONAL(source, runningOrderNumber, dest, setrunningOrderNumber)
	SIMPLE_MAP_OPTIONAL(source, totalNumberOfGroupMembers, dest, settotalNumberOfGroupMembers)
	SIMPLE_MAP_OPTIONAL(source, orderedGroupFlag, dest, setorderedGroupFlag)
	SIMPLE_MAP_OPTIONAL(source, note, dest, setrelationNote)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setcustomRelationTypeGroup)

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, relationIdentifier, ebucoreIdentifier, mapIdentifier, dest, setrelationIdentifier)
}

#define MAP_TECHNICAL_ATTRIBUTE_FUNCTION(functionName, sourceType, destType, destProperty) \
	void functionName(sourceType& source, destType *dest, ObjectModifier* mod) { \
		dest->destProperty(source);	\
		MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, settechnicalAttributeTypeGroup)	\
	}

MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeString, String, ebucoreTechnicalAttributeString, settechnicalAttributeStringValue)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeInt8, Int8, ebucoreTechnicalAttributeInt8, settechnicalAttributeInt8Value)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeInt16, Int16, ebucoreTechnicalAttributeInt16, settechnicalAttributeInt16Value)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeInt32, Int32, ebucoreTechnicalAttributeInt32, settechnicalAttributeInt32Value)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeInt64, Int64, ebucoreTechnicalAttributeInt64, settechnicalAttributeInt64Value)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeUInt8, UInt8, ebucoreTechnicalAttributeUInt8, settechnicalAttributeUInt8Value)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeUInt16, UInt16, ebucoreTechnicalAttributeUInt16, settechnicalAttributeUInt16Value)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeUInt32, UInt32, ebucoreTechnicalAttributeUInt32, settechnicalAttributeUInt32Value)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeUInt64, UInt64, ebucoreTechnicalAttributeUInt64, settechnicalAttributeUInt64Value)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeFloat, Float, ebucoreTechnicalAttributeFloat, settechnicalAttributeFloatValue)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeAnyURI, technicalAttributeUriType, ebucoreTechnicalAttributeAnyURI, settechnicalAttributeAnyURIValue)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeBoolean, Boolean, ebucoreTechnicalAttributeBoolean, settechnicalAttributeBooleanValue)

void mapTechnicalAttributeRational(technicalAttributeRationalType& source, ebucoreTechnicalAttributeRational *dest, ObjectModifier* mod) {
	mxfRational r = { source.factorNumerator(), source.factorDenominator() };
	dest->settechnicalAttributeRationalValue(r);
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, settechnicalAttributeTypeGroup)
}

void mapMedium(medium& source, ebucoreMedium *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, mediumId, dest, setmediumID)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setmediumTypeGroup)
}

void mapPackageInfo(formatType& source, ebucorePackageInfo *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, fileName, dest, setpackageName)
	SIMPLE_MAP_OPTIONAL(source, fileSize, dest, setpackageSize)
	if (source.locator().size() > 0) {
		dest->setpackageLocator( source.locator()[0] );
	}
}

void mapSigningFormat(signingFormat& source, ebucoreSigningFormat *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, trackId, dest, setsigningTrackID)
	SIMPLE_MAP_OPTIONAL(source, trackName, dest, setsigningTrackName)
	SIMPLE_MAP_OPTIONAL(source, language, dest, setsigningTrackLanguageCode)
	SIMPLE_MAP_OPTIONAL(source, signingSourceUri, dest, setsigningSourceUri)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setsigningTypeGroup)
	MAP_NEW_FORMAT_GROUP_AND_ASSIGN(source, dest, setsigningFormatGroup)
}

void mapCodec(codecType& source, ebucoreCodec *dest, ObjectModifier* mod = NULL) {	
	SIMPLE_MAP_OPTIONAL(source, name, dest, setname)
	SIMPLE_MAP_OPTIONAL(source, vendor, dest, setvendor)
	SIMPLE_MAP_OPTIONAL(source, version, dest, setversion)
	SIMPLE_MAP_OPTIONAL(source, family, dest, setfamily)
	// [TODO] XSD Codec identifier is an identifiertype, KLV is string
	//SIMPLE_MAP_OPTIONAL(source, codecIdentifier, dest, setcodecIdentifier)
}

void mapAudioTrack(audioTrack& source, ebucoreTrack *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, trackId, dest, settrackID)
	SIMPLE_MAP_OPTIONAL(source, trackName, dest, settrackName)
	SIMPLE_MAP_OPTIONAL(source, trackLanguage, dest, settrackLanguageCode)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, settrackTypeGroup)
}

void mapVideoTrack(videoTrack& source, ebucoreTrack *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, trackId, dest, settrackID)
	SIMPLE_MAP_OPTIONAL(source, trackName, dest, settrackName)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, settrackTypeGroup)
}

void mapAudioFormat(audioFormatType& source, ebucoreAudioFormat *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, audioFormatId, dest, setaudioFormatID)
	SIMPLE_MAP_OPTIONAL(source, audioFormatName, dest, setaudioFormatName)
	SIMPLE_MAP_OPTIONAL(source, audioFormatDefinition, dest, setaudioFormatDefinition)

	if (source.audioTrackConfiguration().present()) {
		MAP_NEW_TYPE_GROUP_AND_ASSIGN(source.audioTrackConfiguration().get(), dest, setaudioTrackConfiguration)
	}

	SIMPLE_MAP_OPTIONAL(source, sampleSize, dest, setaudioSamplingSize)
	SIMPLE_MAP_OPTIONAL(source, sampleType, dest, setaudioSamplingType)
	SIMPLE_MAP_OPTIONAL(source, channels, dest, setaudioTotalNumberOfChannels)
	SIMPLE_MAP_OPTIONAL(source, bitRate, dest, setaudioBitRate)
	SIMPLE_MAP_OPTIONAL(source, bitRateMax, dest, setaudioMaxBitRate)
	SIMPLE_MAP_OPTIONAL(source, bitRateMode, dest, setaudioBitRateMode)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, samplingRate, dest, setaudioSamplingRate, convert)
	
	if (source.audioEncoding().present()) {
		MAP_NEW_TYPE_GROUP_AND_ASSIGN(source.audioEncoding().get(), dest, setaudioEncoding)
	}

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, codec, ebucoreCodec, mapCodec, dest, setaudioCodec)
	NEW_VECTOR_AND_ASSIGN(source, audioTrack, ebucoreTrack, audioFormatType::audioTrack_iterator, mapAudioTrack, dest, setaudioTrack)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeString, ebucoreTechnicalAttributeString, 
		audioFormatType::technicalAttributeString_iterator, mapTechnicalAttributeString, dest, setaudioTechnicalAttributeString)
	
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeByte, ebucoreTechnicalAttributeInt8, 
		audioFormatType::technicalAttributeByte_iterator, mapTechnicalAttributeInt8, dest, setaudioTechnicalAttributeInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeShort, ebucoreTechnicalAttributeInt16, 
		audioFormatType::technicalAttributeShort_iterator, mapTechnicalAttributeInt16, dest, setaudioTechnicalAttributeInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeInteger, ebucoreTechnicalAttributeInt32, 
		audioFormatType::technicalAttributeInteger_iterator, mapTechnicalAttributeInt32, dest, setaudioTechnicalAttributeInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeLong, ebucoreTechnicalAttributeInt64, 
		audioFormatType::technicalAttributeLong_iterator, mapTechnicalAttributeInt64, dest, setaudioTechnicalAttributeInt64)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedByte, ebucoreTechnicalAttributeUInt8, 
		audioFormatType::technicalAttributeUnsignedByte_iterator, mapTechnicalAttributeUInt8, dest, setaudioTechnicalAttributeUInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedShort, ebucoreTechnicalAttributeUInt16, 
		audioFormatType::technicalAttributeUnsignedShort_iterator, mapTechnicalAttributeUInt16, dest, setaudioTechnicalAttributeUInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedInteger, ebucoreTechnicalAttributeUInt32, 
		audioFormatType::technicalAttributeUnsignedInteger_iterator, mapTechnicalAttributeUInt32, dest, setaudioTechnicalAttributeUInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedLong, ebucoreTechnicalAttributeUInt64, 
		audioFormatType::technicalAttributeUnsignedLong_iterator, mapTechnicalAttributeUInt64, dest, setaudioTechnicalAttributeUInt64)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeFloat, ebucoreTechnicalAttributeFloat, 
		audioFormatType::technicalAttributeFloat_iterator, mapTechnicalAttributeFloat, dest, setaudioTechnicalAttributeFloat)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeRational, ebucoreTechnicalAttributeRational, 
		audioFormatType::technicalAttributeRational_iterator, mapTechnicalAttributeRational, dest, setaudioTechnicalAttributeRational)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUri, ebucoreTechnicalAttributeAnyURI, 
		audioFormatType::technicalAttributeUri_iterator, mapTechnicalAttributeAnyURI, dest, setaudioTechnicalAttributeAnyURI)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeBoolean, ebucoreTechnicalAttributeBoolean, 
		audioFormatType::technicalAttributeBoolean_iterator, mapTechnicalAttributeBoolean, dest, setaudioTechnicalAttributeBoolean)
}

void mapAspectRatio(aspectRatioType& source, ebucoreAspectRatio *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_NO_GET(source, factorNumerator, dest, setaspectRatioFactorNumerator)
	SIMPLE_MAP_NO_GET(source, factorDenominator, dest, setaspectRatioFactorDenominator)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setaspectRatioTypeGroup)
}

void mapDimension(lengthType& source, ebucoreDimension *dest, ObjectModifier* mod = NULL) {
	dest->setdimensionValue(source);
	SIMPLE_MAP_OPTIONAL(source, unit, dest, setdimensionUnit)
}

void mapDimension(dimensionType& source, ebucoreDimension *dest, ObjectModifier* mod = NULL) {
	dest->setdimensionValue(source);
	SIMPLE_MAP_OPTIONAL(source, unit, dest, setdimensionUnit)
}

void mapWidth(width& source, ebucoreWidth *dest, ObjectModifier* mod = NULL) {
	ebucoreDimension *obj = newAndModifyObject<ebucoreDimension>(dest->getHeaderMetadata(), mod);
	mapDimension(source, obj, mod);
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setwidthTypeGroup)
}

void mapHeight(height& source, ebucoreHeight *dest, ObjectModifier* mod = NULL) {
	ebucoreDimension *obj = newAndModifyObject<ebucoreDimension>(dest->getHeaderMetadata(), mod);
	mapDimension(source, obj, mod);
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setheightTypeGroup)
}

void mapImageFormat(imageFormatType& source, ebucoreImageFormat *dest, ObjectModifier* mod = NULL) {

	SIMPLE_MAP_OPTIONAL(source, imageFormatId, dest, setimageFormatID)
	SIMPLE_MAP_OPTIONAL(source, imageFormatName, dest, setimageFormatName)
	SIMPLE_MAP_OPTIONAL(source, imageFormatDefinition, dest, setimageFormatDefinition)
	SIMPLE_MAP_OPTIONAL(source, orientation, dest, setimageOrientation)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, aspectRatio, ebucoreAspectRatio, mapAspectRatio, dest, setimageAspectRatio)
	
	if (source.imageEncoding().present()) {
		MAP_NEW_TYPE_GROUP_AND_ASSIGN(source.imageEncoding().get(), dest, setimageEncoding)
	}

	/* [TODO] XSD is missing image codec!!
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, codec, ebucoreCodec, mapCodec, dest, setimageCodec) */

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, width, ebucoreDimension, mapDimension, dest, setimageWidth)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, height, ebucoreDimension, mapDimension, dest, setimageHeight)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeString, ebucoreTechnicalAttributeString, 
		imageFormatType::technicalAttributeString_iterator, mapTechnicalAttributeString, dest, setimageTechnicalAttributeString)
	
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeByte, ebucoreTechnicalAttributeInt8, 
		imageFormatType::technicalAttributeByte_iterator, mapTechnicalAttributeInt8, dest, setimageTechnicalAttributeInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeShort, ebucoreTechnicalAttributeInt16, 
		imageFormatType::technicalAttributeShort_iterator, mapTechnicalAttributeInt16, dest, setimageTechnicalAttributeInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeInteger, ebucoreTechnicalAttributeInt32, 
		imageFormatType::technicalAttributeInteger_iterator, mapTechnicalAttributeInt32, dest, setimageTechnicalAttributeInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeLong, ebucoreTechnicalAttributeInt64, 
		imageFormatType::technicalAttributeLong_iterator, mapTechnicalAttributeInt64, dest, setimageTechnicalAttributeInt64)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedByte, ebucoreTechnicalAttributeUInt8, 
		imageFormatType::technicalAttributeUnsignedByte_iterator, mapTechnicalAttributeUInt8, dest, setimageTechnicalAttributeUInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedShort, ebucoreTechnicalAttributeUInt16, 
		imageFormatType::technicalAttributeUnsignedShort_iterator, mapTechnicalAttributeUInt16, dest, setimageTechnicalAttributeUInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedInteger, ebucoreTechnicalAttributeUInt32, 
		imageFormatType::technicalAttributeUnsignedInteger_iterator, mapTechnicalAttributeUInt32, dest, setimageTechnicalAttributeUInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedLong, ebucoreTechnicalAttributeUInt64, 
		imageFormatType::technicalAttributeUnsignedLong_iterator, mapTechnicalAttributeUInt64, dest, setimageTechnicalAttributeUInt64)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeFloat, ebucoreTechnicalAttributeFloat, 
		imageFormatType::technicalAttributeFloat_iterator, mapTechnicalAttributeFloat, dest, setimageTechnicalAttributeFloat)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeRational, ebucoreTechnicalAttributeRational, 
		imageFormatType::technicalAttributeRational_iterator, mapTechnicalAttributeRational, dest, setimageTechnicalAttributeRational)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUri, ebucoreTechnicalAttributeAnyURI, 
		imageFormatType::technicalAttributeUri_iterator, mapTechnicalAttributeAnyURI, dest, setimageTechnicalAttributeAnyURI)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeBoolean, ebucoreTechnicalAttributeBoolean, 
		imageFormatType::technicalAttributeBoolean_iterator, mapTechnicalAttributeBoolean, dest, setimageTechnicalAttributeBoolean)
}

void mapVideoFormat(videoFormatType& source, ebucoreVideoFormat *dest, ObjectModifier* mod = NULL) {

	SIMPLE_MAP_OPTIONAL(source, videoFormatId, dest, setvideoFormatID)
	SIMPLE_MAP_OPTIONAL(source, videoFormatName, dest, setvideoFormatName)
	SIMPLE_MAP_OPTIONAL(source, videoFormatDefinition, dest, setvideoFormatDefinition)
	
	SIMPLE_MAP_OPTIONAL(source, bitRate, dest, setvideoBitRate)
	SIMPLE_MAP_OPTIONAL(source, bitRateMax, dest, setvideoMaxBitRate)
	SIMPLE_MAP_OPTIONAL(source, bitRateMode, dest, setvideoBitRateMode)
	SIMPLE_MAP_OPTIONAL(source, scanningFormat, dest, setvideoSamplingFormat)
	SIMPLE_MAP_OPTIONAL(source, scanningOrder, dest, setvideoScanningOrder)
	SIMPLE_MAP_OPTIONAL(source, lines, dest, setvideoActiveLines)
	SIMPLE_MAP_OPTIONAL(source, noiseFilter, dest, setvideoNoiseFilterFlag)
	SIMPLE_MAP_OPTIONAL(source, flag_3D, dest, setvideo3DFlag)
	NEW_VECTOR_AND_ASSIGN(source, aspectRatio, ebucoreAspectRatio, videoFormatType::aspectRatio_iterator, mapAspectRatio, dest, setvideoAspectRatio)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, frameRate, dest, setvideoFrameRate, convert)
	if (source.width().size() > 0) {
		NEW_OBJECT_AND_ASSIGN_DIRECT(source.width()[0], ebucoreWidth, mapWidth, dest, setvideoWidth)
	}
	if (source.height().size() > 0) {
		NEW_OBJECT_AND_ASSIGN_DIRECT(source.height()[0], ebucoreHeight, mapHeight, dest, setvideoHeight)
	}

	if (source.videoEncoding().present()) {
		MAP_NEW_TYPE_GROUP_AND_ASSIGN(source.videoEncoding().get(), dest, setvideoEncoding)
	}

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, codec, ebucoreCodec, mapCodec, dest, setvideoCodec)
	NEW_VECTOR_AND_ASSIGN(source, videoTrack, ebucoreTrack, videoFormatType::videoTrack_iterator, mapVideoTrack, dest, setvideoTrack)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeString, ebucoreTechnicalAttributeString, 
		videoFormatType::technicalAttributeString_iterator, mapTechnicalAttributeString, dest, setvideoTechnicalAttributeString)
	
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeByte, ebucoreTechnicalAttributeInt8, 
		videoFormatType::technicalAttributeByte_iterator, mapTechnicalAttributeInt8, dest, setvideoTechnicalAttributeInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeShort, ebucoreTechnicalAttributeInt16, 
		videoFormatType::technicalAttributeShort_iterator, mapTechnicalAttributeInt16, dest, setvideoTechnicalAttributeInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeInteger, ebucoreTechnicalAttributeInt32, 
		videoFormatType::technicalAttributeInteger_iterator, mapTechnicalAttributeInt32, dest, setvideoTechnicalAttributeInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeLong, ebucoreTechnicalAttributeInt64, 
		videoFormatType::technicalAttributeLong_iterator, mapTechnicalAttributeInt64, dest, setvideoTechnicalAttributeInt64)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedByte, ebucoreTechnicalAttributeUInt8, 
		videoFormatType::technicalAttributeUnsignedByte_iterator, mapTechnicalAttributeUInt8, dest, setvideoTechnicalAttributeUInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedShort, ebucoreTechnicalAttributeUInt16, 
		videoFormatType::technicalAttributeUnsignedShort_iterator, mapTechnicalAttributeUInt16, dest, setvideoTechnicalAttributeUInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedInteger, ebucoreTechnicalAttributeUInt32, 
		videoFormatType::technicalAttributeUnsignedInteger_iterator, mapTechnicalAttributeUInt32, dest, setvideoTechnicalAttributeUInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedLong, ebucoreTechnicalAttributeUInt64, 
		videoFormatType::technicalAttributeUnsignedLong_iterator, mapTechnicalAttributeUInt64, dest, setvideoTechnicalAttributeUInt64)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeFloat, ebucoreTechnicalAttributeFloat, 
		videoFormatType::technicalAttributeFloat_iterator, mapTechnicalAttributeFloat, dest, setvideoTechnicalAttributeFloat)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeRational, ebucoreTechnicalAttributeRational, 
		videoFormatType::technicalAttributeRational_iterator, mapTechnicalAttributeRational, dest, setvideoTechnicalAttributeRational)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUri, ebucoreTechnicalAttributeAnyURI, 
		videoFormatType::technicalAttributeUri_iterator, mapTechnicalAttributeAnyURI, dest, setvideoTechnicalAttributeAnyURI)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeBoolean, ebucoreTechnicalAttributeBoolean, 
		videoFormatType::technicalAttributeBoolean_iterator, mapTechnicalAttributeBoolean, dest, setvideoTechnicalAttributeBoolean)
}

void mapCaptioning(captioningFormat& source, ebucoreCaptioning* dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, captioningFormatId, dest, setcaptioningFormatID)
	SIMPLE_MAP_OPTIONAL(source, captioningFormatName, dest, setcaptioningFormatName)
	SIMPLE_MAP_OPTIONAL(source, captioningSourceUri, dest, setcaptioningSourceUri)
	SIMPLE_MAP_OPTIONAL(source, trackId, dest, setcaptioningTrackID)
	SIMPLE_MAP_OPTIONAL(source, trackName, dest, setcaptioningTrackName)
	SIMPLE_MAP_OPTIONAL(source, language, dest, setcaptioningLanguageCode)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setcaptioningTypeGroup)
	MAP_NEW_FORMAT_GROUP_AND_ASSIGN(source, dest, setcaptioningFormatGroup)
}

void mapSubtitling(subtitlingFormat& source, ebucoreSubtitling* dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, subtitlingFormatId, dest, setsubtitlingFormatID)
	SIMPLE_MAP_OPTIONAL(source, subtitlingFormatName, dest, setsubtitlingFormatName)
	SIMPLE_MAP_OPTIONAL(source, subtitlingSourceUri, dest, setsubtitlingSourceUri)
	SIMPLE_MAP_OPTIONAL(source, trackId, dest, setsubtitlingTrackID)
	SIMPLE_MAP_OPTIONAL(source, trackName, dest, setsubtitlingTrackName)
	SIMPLE_MAP_OPTIONAL(source, language, dest, setsubtitlingLanguageCode)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setsubtitlingTypeGroup)
	MAP_NEW_FORMAT_GROUP_AND_ASSIGN(source, dest, setsubtitlingFormatGroup)
}

void mapSigning(signingFormat& source, ebucoreSigningFormat* dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, signingFormatId, dest, setsigningFormatID)
	SIMPLE_MAP_OPTIONAL(source, signingFormatName, dest, setsigningFormatName)
	SIMPLE_MAP_OPTIONAL(source, signingSourceUri, dest, setsigningSourceUri)
	SIMPLE_MAP_OPTIONAL(source, trackId, dest, setsigningTrackID)
	SIMPLE_MAP_OPTIONAL(source, trackName, dest, setsigningTrackName)
	SIMPLE_MAP_OPTIONAL(source, language, dest, setsigningTrackLanguageCode)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setsigningTypeGroup)
	MAP_NEW_FORMAT_GROUP_AND_ASSIGN(source, dest, setsigningFormatGroup)
}

void mapAncillaryData(ancillaryDataFormat& source, ebucoreAncillaryData* dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, DID, dest, setDID)
	SIMPLE_MAP_OPTIONAL(source, SDID, dest, setSDID)

	std::vector<uint32_t> vec_lines;
	for (ancillaryDataFormat::lineNumber_const_iterator it = source.lineNumber().begin(); it != source.lineNumber().end(); it++) {
		vec_lines.push_back(*it);
	}
	dest->setlineNumber(vec_lines);

	ebucoreTypeGroup *obj = newAndModifyObject<ebucoreTypeGroup>(dest->getHeaderMetadata(), mod);
	// source is only an integer to map from, lets be creative
	SIMPLE_MAP_OPTIONAL(source, ancillaryDataFormatName, obj, settypeGroupLabel)
	SIMPLE_MAP_OPTIONAL(source, ancillaryDataFormatId, obj, settypeGroupLink)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, wrappingType, obj, settypeGroupDefinition, convert_to_string)
}

void mapDataFormat(dataFormatType& source, ebucoreDataFormat *dest, ObjectModifier* mod = NULL) {

	SIMPLE_MAP_OPTIONAL(source, dataFormatId, dest, setdataFormatID)
	SIMPLE_MAP_OPTIONAL(source, dataFormatVersionId, dest, setdataFormatVersionID)
	SIMPLE_MAP_OPTIONAL(source, dataFormatName, dest, setdataFormatName)
	SIMPLE_MAP_OPTIONAL(source, dataFormatDefinition, dest, setdataFormatDefinition)

	SIMPLE_MAP_OPTIONAL(source, dataTrackId, dest, setdataTrackId)
	SIMPLE_MAP_OPTIONAL(source, dataTrackName, dest, setdataTrackName)
	SIMPLE_MAP_OPTIONAL(source, dataTrackLanguage, dest, setdataTrackLanguageCode)

	NEW_VECTOR_AND_ASSIGN(source, captioningFormat, ebucoreCaptioning, dataFormatType::captioningFormat_iterator, mapCaptioning, dest, setcaptioning)
	NEW_VECTOR_AND_ASSIGN(source, subtitlingFormat, ebucoreSubtitling, dataFormatType::subtitlingFormat_iterator, mapSubtitling, dest, setsubtitling)
	NEW_VECTOR_AND_ASSIGN(source, ancillaryDataFormat, ebucoreAncillaryData, dataFormatType::ancillaryDataFormat_iterator, mapAncillaryData, dest, setancillaryData)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeString, ebucoreTechnicalAttributeString, 
		dataFormatType::technicalAttributeString_iterator, mapTechnicalAttributeString, dest, setdataTechnicalAttributeString)
	
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeByte, ebucoreTechnicalAttributeInt8, 
		dataFormatType::technicalAttributeByte_iterator, mapTechnicalAttributeInt8, dest, setdataTechnicalAttributeInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeShort, ebucoreTechnicalAttributeInt16, 
		dataFormatType::technicalAttributeShort_iterator, mapTechnicalAttributeInt16, dest, setdataTechnicalAttributeInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeInteger, ebucoreTechnicalAttributeInt32, 
		dataFormatType::technicalAttributeInteger_iterator, mapTechnicalAttributeInt32, dest, setdataTechnicalAttributeInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeLong, ebucoreTechnicalAttributeInt64, 
		dataFormatType::technicalAttributeLong_iterator, mapTechnicalAttributeInt64, dest, setdataTechnicalAttributeInt64)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedByte, ebucoreTechnicalAttributeUInt8, 
		dataFormatType::technicalAttributeUnsignedByte_iterator, mapTechnicalAttributeUInt8, dest, setdataTechnicalAttributeUInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedShort, ebucoreTechnicalAttributeUInt16, 
		dataFormatType::technicalAttributeUnsignedShort_iterator, mapTechnicalAttributeUInt16, dest, setdataTechnicalAttributeUInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedInteger, ebucoreTechnicalAttributeUInt32, 
		dataFormatType::technicalAttributeUnsignedInteger_iterator, mapTechnicalAttributeUInt32, dest, setdataTechnicalAttributeUInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedLong, ebucoreTechnicalAttributeUInt64, 
		dataFormatType::technicalAttributeUnsignedLong_iterator, mapTechnicalAttributeUInt64, dest, setdataTechnicalAttributeUInt64)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeFloat, ebucoreTechnicalAttributeFloat, 
		dataFormatType::technicalAttributeFloat_iterator, mapTechnicalAttributeFloat, dest, setdataTechnicalAttributeFloat)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeRational, ebucoreTechnicalAttributeRational, 
		dataFormatType::technicalAttributeRational_iterator, mapTechnicalAttributeRational, dest, setdataTechnicalAttributeRational)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUri, ebucoreTechnicalAttributeAnyURI, 
		dataFormatType::technicalAttributeUri_iterator, mapTechnicalAttributeAnyURI, dest, setdataTechnicalAttributeAnyURI)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeBoolean, ebucoreTechnicalAttributeBoolean, 
		dataFormatType::technicalAttributeBoolean_iterator, mapTechnicalAttributeBoolean, dest, setdataTechnicalAttributeBoolean)
}

void mapFormat(formatType& source, ebucoreFormat *dest, std::map<xml_schema::id, ebucoreFormat*>& formatMap, ObjectModifier* mod = NULL) {

	SIMPLE_MAP_OPTIONAL(source, formatId, dest, setformatID)
	SIMPLE_MAP_OPTIONAL(source, formatVersionId, dest, setformatVersionID)
	SIMPLE_MAP_OPTIONAL(source, formatName, dest, setformatName)
	SIMPLE_MAP_OPTIONAL(source, formatDefinition, dest, setformatDefinition)
	
	if (source.dateCreated().present()) {
		SIMPLE_MAP_OPTIONAL_CONVERT(source, dateCreated().get().startYear, dest, setformatYearCreated, convert_timestamp)
		SIMPLE_MAP_OPTIONAL_CONVERT(source, dateCreated().get().startDate, dest, setformatDateCreated, convert_timestamp)
	}

	if (source.duration().present()) {
		// [NOTE] Mapped playtime as duration because we need a numeric value (rational) # of seconds.
		// [NOTE] We just map the timecode as a string to the KLV representation
		SIMPLE_MAP_OPTIONAL(source, duration().get().editUnitNumber, dest, setoverallDurationEditUnit)
		SIMPLE_MAP_OPTIONAL(source, duration().get().timecode, dest, setoverallDurationTimecode)
		SIMPLE_MAP_OPTIONAL_CONVERT(source, duration().get().normalPlayTime, dest, setoverallDurationTime, convert_rational)
	}

	if (source.containerFormat().size() > 0) {
		MAP_NEW_FORMAT_GROUP_AND_ASSIGN(source.containerFormat()[0], dest, setcontainerFormat)
	}
	if (source.medium().size() > 0) {
		NEW_OBJECT_AND_ASSIGN_DIRECT(source.medium()[0], ebucoreMedium, mapMedium, dest, setmedium)
	}
	
	ebucorePackageInfo *obj = newAndModifyObject<ebucorePackageInfo>(dest->getHeaderMetadata(), mod);
	mapPackageInfo(source, obj, mod);
	dest->setpackageInfo(obj);

	if (source.mimeType().size() > 0) {
		MAP_NEW_TYPE_GROUP_AND_ASSIGN(source.mimeType()[0], dest, setmimeType)
	}

	NEW_VECTOR_AND_ASSIGN(source, audioFormat, ebucoreAudioFormat, formatType::audioFormat_iterator, mapAudioFormat, dest, setmaterialAudioFormat)
	NEW_VECTOR_AND_ASSIGN(source, videoFormat, ebucoreVideoFormat, formatType::videoFormat_iterator, mapVideoFormat, dest, setmaterialVideoFormat)
	NEW_VECTOR_AND_ASSIGN(source, imageFormat, ebucoreImageFormat, formatType::imageFormat_iterator, mapImageFormat, dest, setmaterialImageFormat)
	NEW_VECTOR_AND_ASSIGN(source, dataFormat, ebucoreDataFormat, formatType::dataFormat_iterator, mapDataFormat, dest, setmaterialDataFormat)
	NEW_VECTOR_AND_ASSIGN(source, signingFormat, ebucoreSigningFormat, formatType::signingFormat_iterator, mapSigningFormat, dest, setmaterialSigningFormat)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeString, ebucoreTechnicalAttributeString, 
		formatType::technicalAttributeString_iterator, mapTechnicalAttributeString, dest, setmaterialTechnicalAttributeString)
	
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeByte, ebucoreTechnicalAttributeInt8, 
		formatType::technicalAttributeByte_iterator, mapTechnicalAttributeInt8, dest, setmaterialTechnicalAttributeInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeShort, ebucoreTechnicalAttributeInt16, 
		formatType::technicalAttributeShort_iterator, mapTechnicalAttributeInt16, dest, setmaterialTechnicalAttributeInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeInteger, ebucoreTechnicalAttributeInt32, 
		formatType::technicalAttributeInteger_iterator, mapTechnicalAttributeInt32, dest, setmaterialTechnicalAttributeInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeLong, ebucoreTechnicalAttributeInt64, 
		formatType::technicalAttributeLong_iterator, mapTechnicalAttributeInt64, dest, setmaterialTechnicalAttributeInt64)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedByte, ebucoreTechnicalAttributeUInt8, 
		formatType::technicalAttributeUnsignedByte_iterator, mapTechnicalAttributeUInt8, dest, setmaterialTechnicalAttributeUInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedShort, ebucoreTechnicalAttributeUInt16, 
		formatType::technicalAttributeUnsignedShort_iterator, mapTechnicalAttributeUInt16, dest, setmaterialTechnicalAttributeUInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedInteger, ebucoreTechnicalAttributeUInt32, 
		formatType::technicalAttributeUnsignedInteger_iterator, mapTechnicalAttributeUInt32, dest, setmaterialTechnicalAttributeUInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedLong, ebucoreTechnicalAttributeUInt64, 
		formatType::technicalAttributeUnsignedLong_iterator, mapTechnicalAttributeUInt64, dest, setmaterialTechnicalAttributeUInt64)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeFloat, ebucoreTechnicalAttributeFloat, 
		formatType::technicalAttributeFloat_iterator, mapTechnicalAttributeFloat, dest, setmaterialTechnicalAttributeFloat)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeRational, ebucoreTechnicalAttributeRational, 
		formatType::technicalAttributeRational_iterator, mapTechnicalAttributeRational, dest, setmaterialTechnicalAttributeRational)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUri, ebucoreTechnicalAttributeAnyURI, 
		formatType::technicalAttributeUri_iterator, mapTechnicalAttributeAnyURI, dest, setmaterialTechnicalAttributeAnyURI)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeBoolean, ebucoreTechnicalAttributeBoolean, 
		formatType::technicalAttributeBoolean_iterator, mapTechnicalAttributeBoolean, dest, setmaterialTechnicalAttributeBoolean)

	// add this format element to the list
	if (source.formatId().present()) {
		formatMap[source.formatId().get()] = dest;
	}
}

void mapPart(partType& source, ebucorePartMetadata *dest, mxfRational overallFrameRate, std::vector<ebucorePartMetadata*>& timelineParts, ObjectModifier* mod) {
	SIMPLE_MAP_OPTIONAL(source, partId, dest, setpartId)
	SIMPLE_MAP_OPTIONAL(source, partName, dest, setpartName)
	SIMPLE_MAP_OPTIONAL(source, partDefinition, dest, setpartDefinition)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setpartTypeGroup)

	if (source.partStartTime().present()) {
		timeType& start = source.partStartTime().get();
		SIMPLE_MAP_OPTIONAL(start, editUnitNumber, dest, setpartStartEditUnitNumber)
		SIMPLE_MAP_OPTIONAL(start, timecode, dest, setpartStartTimecode)
		SIMPLE_MAP_OPTIONAL_CONVERT(start, normalPlayTime, dest, setpartStartTime, convert_rational)
	}
	if (source.partDuration().present()) {
		durationType& dur = source.partDuration().get();
		// [NOTE] Mapped playtime as duration because we need a numeric value (rational) # of seconds.
		// [NOTE] We just map the timecode as a string to the KLV representation
		SIMPLE_MAP_OPTIONAL(dur, editUnitNumber, dest, setpartDurationEditUnitNumber)
		SIMPLE_MAP_OPTIONAL(dur, timecode, dest, setpartDurationTimecode)
		SIMPLE_MAP_OPTIONAL_CONVERT(dur, normalPlayTime, dest, setpartDurationTime, convert_rational)
	}

	// map ourselves (we are an extension of the coreMetadataType) onto a new ebucoreCoreMetadata object
	ebucoreCoreMetadata *obj = newAndModifyObject<ebucoreCoreMetadata>(dest->getHeaderMetadata(), mod);
	mapCoreMetadata(source, obj, overallFrameRate, timelineParts, mod);
	dest->setpartMeta(obj);
}

void mapCoreMetadata(coreMetadataType& source, ebucoreCoreMetadata *dest, mxfRational overallFrameRate, std::vector<ebucorePartMetadata*>& timelineParts, ObjectModifier* mod) {

	std::map<xml_schema::id, ebucoreFormat*> formatMap;
	std::map<xml_schema::id, ebucoreRights*> rightsMap;

	NEW_VECTOR_AND_ASSIGN(source, title, ebucoreTitle, coreMetadataType::title_iterator, mapTitle, dest, settitle)	
	NEW_VECTOR_AND_ASSIGN(source, alternativeTitle, ebucoreAlternativeTitle, coreMetadataType::alternativeTitle_iterator, mapAlternativeTitle, dest, setalternativeTitle)
	NEW_VECTOR_AND_ASSIGN(source, creator, ebucoreEntity, coreMetadataType::creator_iterator, mapEntity, dest, setcreator)
	NEW_VECTOR_AND_ASSIGN(source, subject, ebucoreSubject, coreMetadataType::subject_iterator, mapSubject, dest, setsubject)
	NEW_VECTOR_AND_ASSIGN(source, description, ebucoreDescription, coreMetadataType::description_iterator, mapDescription, dest, setdescription)
	NEW_VECTOR_AND_ASSIGN(source, publisher, ebucoreEntity, coreMetadataType::publisher_iterator, mapEntity, dest, setpublisher)
	NEW_VECTOR_AND_ASSIGN(source, contributor, ebucoreEntity, coreMetadataType::contributor_iterator, mapEntity, dest, setcontributor)
	NEW_VECTOR_AND_ASSIGN(source, date, ebucoreDate, coreMetadataType::date_iterator, mapDate, dest, setdate)
	NEW_VECTOR_AND_ASSIGN(source, type, ebucoreType, coreMetadataType::type_iterator, mapType, dest, settype)
	NEW_VECTOR_AND_ASSIGN(source, identifier, ebucoreIdentifier, coreMetadataType::identifier_iterator, mapIdentifier, dest, setidentifier)
	NEW_VECTOR_AND_ASSIGN(source, language, ebucoreLanguage, coreMetadataType::language_iterator, mapLanguage, dest, setlanguage)
	NEW_VECTOR_AND_ASSIGN(source, coverage, ebucoreCoverage, coreMetadataType::coverage_iterator, mapMetadataCoverage, dest, setcoverage)

	// do formats before rights and publicationhistory to make sure references are available in the map
	std::vector<ebucoreFormat*> vec_dest_fmt;
	for (coreMetadataType::format_iterator it = source.format().begin(); it != source.format().end(); it++) {
		ebucoreFormat *obj = newAndModifyObject<ebucoreFormat>(dest->getHeaderMetadata(), mod);
		mapFormat(*it, obj, formatMap, mod);
		vec_dest_fmt.push_back(obj);
	}
	dest->setformat(vec_dest_fmt);
	//NEW_VECTOR_AND_ASSIGN(source, format, ebucoreFormat, coreMetadataType::format_iterator, mapFormat, dest, setformat)

	std::vector<ebucoreRights*> vec_dest_rights;
	for (coreMetadataType::rights_iterator it = source.rights().begin(); it != source.rights().end(); it++) {
		ebucoreRights *obj = newAndModifyObject<ebucoreRights>(dest->getHeaderMetadata(), mod);
		mapRights(*it, obj, formatMap, rightsMap, mod);
		vec_dest_rights.push_back(obj);
	}
	dest->setrights(vec_dest_rights);
	//NEW_VECTOR_AND_ASSIGN(source, rights, ebucoreRights, coreMetadataType::rights_iterator, mapRights, dest, setrights)

	NEW_VECTOR_AND_ASSIGN(source, rating, ebucoreRating, coreMetadataType::rating_iterator, mapRating, dest, setrating)

	if (source.version().size() > 0) {
		NEW_OBJECT_AND_ASSIGN_DIRECT(source.version()[0], ebucoreVersion, mapVersion, dest, setversion)
	}
	
	if (source.publicationHistory().present()) {
		ebucorePublicationHistory *obj = newAndModifyObject<ebucorePublicationHistory>(dest->getHeaderMetadata(), mod);
		mapPublicationHistory(source.publicationHistory().get(), obj, dest->getHeaderMetadata(), formatMap, rightsMap, mod);
		dest->setpublicationHistory(obj);
	}

	mapBasicRelations(source, dest, mod);
	NEW_VECTOR_AND_ASSIGN(source, relation, ebucoreCustomRelation, coreMetadataType::relation_iterator, mapCustomRelation, dest, setcustomRelation)

	std::vector<ebucorePartMetadata*> vec_parts;
	for (coreMetadataType::part_iterator it = source.part().begin(); it != source.part().end(); it++) {
		ebucorePartMetadata *obj = newAndModifyObject<ebucorePartMetadata>(dest->getHeaderMetadata(), mod);
		mapPart(*it, obj, overallFrameRate, timelineParts, mod);
		vec_parts.push_back(obj);

		// set extremes to start with
		mxfPosition partStart = 0x7FFFFFFFFFFFFFFF;
		mxfLength partEnd = 0;

		// determine which of our parts belong on a timeline
		partType& part = *it;
		if (part.partStartTime().present() && part.partDuration().present()) {
			timeType &start = part.partStartTime().get();
			// sensible values are present!
			mxfPosition formatStart;
			mxfLength formatDuration;
			if (start.editUnitNumber().present()) {
				formatStart = start.editUnitNumber().get();
			} else if (start.normalPlayTime().present()) {
				// convert a duration
				mxfRational d = convert_rational(start.normalPlayTime().get());
				formatStart = (d.numerator * overallFrameRate.numerator) / (d.denominator * overallFrameRate.denominator);
			} else {
				// convert a time code
				bmx::Timecode tc;
				bmx::parse_timecode(start.timecode().get().c_str(), overallFrameRate, &tc);
				formatStart = tc.GetOffset();
			}

			formatType::duration_type &dur = part.partDuration().get();
			if (dur.editUnitNumber().present()) {
				formatDuration = dur.editUnitNumber().get();
			} else if (dur.normalPlayTime().present()) {
				// convert a duration
				mxfRational d = convert_rational(dur.normalPlayTime().get());
				formatDuration = (d.numerator * overallFrameRate.numerator) / (d.denominator * overallFrameRate.denominator);
			} else {
				// convert a time code
				bmx::Timecode tc;
				bmx::parse_timecode(dur.timecode().get().c_str(), overallFrameRate, &tc);
				formatDuration = tc.GetOffset();
			}

			if (partStart != 0x7FFFFFFFFFFFFFFF && partEnd != 0) {
				// this goes onto the timeline!
				obj->setpartStartEditUnitNumber(partStart);
				obj->setpartDurationEditUnitNumber(partEnd - partStart);
				timelineParts.push_back(obj);
			}
		}
	}

	dest->setpart(vec_parts); 
}

} // namespace EBUCore_1_4
} // namespace EBUCore
} // namespace EBUSDK
