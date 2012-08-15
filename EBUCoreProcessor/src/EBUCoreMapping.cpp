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

namespace EBUCore {

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

#define NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, sourceProperty, destType, mapMethod, dest, destProperty) \
	if (source.sourceProperty().present()) {	\
		destType *obj = newAndModifyObject<destType>(dest->getHeaderMetadata(), mod);	\
		mapMethod(source.sourceProperty().get(), obj, mod);	\
		dest->destProperty(obj);	\
	}

#define NEW_VECTOR_AND_ASSIGN(source, sourceProperty, destType, iteratorType, mapMethod, dest, destProperty)	\
	{ std::vector<destType*> vec_dest_destProperty;	\
	for (iteratorType it = source.sourceProperty().begin(); it != source.sourceProperty().end(); it++) {	\
		destType *obj = newAndModifyObject<destType>(dest->getHeaderMetadata(), mod);	\
		mapMethod(*it, obj, mod);	\
		vec_dest_destProperty.push_back(obj);	\
	}	\
	dest->destProperty(vec_dest_destProperty); }

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
	SIMPLE_MAP_OPTIONAL(source, typeLink, dest, settypeGroupLink)

	/*
	<attributeGroup name="typeGroup">
		<attribute name="typeLabel" type="string"/>
		<attribute name="typeDefinition" type="string"/>
		<attribute name="typeLink" type="anyURI"/>
	</attributeGroup>

	This macro is not defined as a function since typeGroups are not separate types 
	but are more like duck typing (just a group of included attributes).
*/

#define MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, destProperty) \
	ebucoreTypeGroup *typeGroup = newAndModifyObject<ebucoreTypeGroup>(dest->getHeaderMetadata(), mod);	\
	MAP_TYPE_GROUP(source, typeGroup)	\
	dest->destProperty(typeGroup);	\


#define MAP_STATUS_GROUP(source, dest)	\
	SIMPLE_MAP_OPTIONAL(source, statusDefinition, dest, setstatusGroupDefinition) \
	SIMPLE_MAP_OPTIONAL(source, statusLabel, dest, setstatusGroupLabel) \
	SIMPLE_MAP_OPTIONAL(source, statusLink, dest, setstatusGroupLink)
/*
	<attributeGroup name="statusGroup">
		<attribute name="statusLabel" type="string"/>
		<attribute name="statusDefinition" type="string"/>
		<attribute name="statusLink" type="anyURI"/>
	</attributeGroup>

	This macro is not defined as a function since statusGroups are not separate types 
	but are more like duck typing (just a group of included attributes).
*/

#define MAP_NEW_STATUS_GROUP_AND_ASSIGN(source, dest, destProperty) \
	ebucoreStatusGroup *statusGroup = newAndModifyObject<ebucoreStatusGroup>(dest->getHeaderMetadata(), mod); \
	MAP_STATUS_GROUP(source, statusGroup)	\
	dest->destProperty(statusGroup);


#define MAP_FORMAT_GROUP(source, dest)	\
	SIMPLE_MAP_OPTIONAL(source, formatDefinition, dest, setformatGroupDefinition) \
	SIMPLE_MAP_OPTIONAL(source, formatLabel, dest, setformatGroupLabel) \
	SIMPLE_MAP_OPTIONAL(source, formatLink, dest, setformatGroupLink)

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
	ebucoreTypeGroup *obj = newAndModifyObject<ebucoreTypeGroup>(dest->getHeaderMetadata(), mod);
	MAP_TYPE_GROUP(source, obj)
	dest->setroleType(obj);
}

void mapTextualAnnotation(std::string source, ebucoreTextualAnnotation *dest, ObjectModifier* mod = NULL) {
	/* deal with lang! */
	dest->settext(source);
}

void mapAddress(addressType& source, ebucoreAddress *dest, ObjectModifier* mod = NULL) {
	/*
	<sequence>
		<element name="addressLine" minOccurs="0" type="string" maxOccurs="unbounded"/>
		<element name="addressTownCity" type="string" minOccurs="0"/>
		<element name="addressCountyState" type="string" minOccurs="0"/>
		<element name="addressDeliveryCode" type="string" minOccurs="0"/>
		<element name="country" minOccurs="0">
			<complexType>
				<attributeGroup ref="ebucore:typeGroup"/>
			</complexType>
		</element>
	</sequence>
	*/

	if (source.addressLine().size() > 0) {
		NEW_VECTOR_AND_ASSIGN(source, addressLine, ebucoreTextualAnnotation, addressType::addressLine_iterator, mapTextualAnnotation, dest, setaddressLines)
	}
	
	SIMPLE_MAP_OPTIONAL(source, addressTownCity, dest, settownCity)
	SIMPLE_MAP_OPTIONAL(source, addressCountyState, dest, setcountyState)
	SIMPLE_MAP_OPTIONAL(source, addressDeliveryCode, dest, setdeliveryCode)

	// special treatment for country, current KLV mapping is not via a typeGroup!
	if (source.country().present()) {
		addressType::country_type& c = source.country().get();
		SIMPLE_MAP_OPTIONAL(c, typeLink, dest, setcountryCode)
		SIMPLE_MAP_OPTIONAL(c, typeLabel, dest, setcountryName)
	}
}

void mapDetails(detailsType& source, ebucoreContactDetails *dest, ObjectModifier* mod = NULL) {
	/*
		<sequence>
			<element name="emailAddress" type="string" minOccurs="0">
			</element>
			<element name="webAddress" type="string" minOccurs="0">
			</element>
			<element name="address" type="ebucore:addressType" minOccurs="0">
			</element>
			<element name="telephoneNumber" type="string" minOccurs="0"/>
			<element name="mobileTelephoneNumber" type="string" minOccurs="0"/>
		</sequence>
		<attributeGroup ref="ebucore:typeGroup"/>
	*/
	NEW_VECTOR_AND_ASSIGN(source, emailAddress, ebucoreTextualAnnotation, detailsType::emailAddress_iterator, mapTextualAnnotation, dest, setemailAddress)
	SIMPLE_MAP_OPTIONAL(source, webAddress, dest, setwebAddress)

	// map address
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, address, ebucoreAddress, mapAddress, dest, setaddress)
	SIMPLE_MAP_OPTIONAL(source, telephoneNumber, dest, settelephoneNumber)
	SIMPLE_MAP_OPTIONAL(source, mobileTelephoneNumber, dest, setmobileTelephoneNumber)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setdetailsType)
}

void mapContact(contactDetailsType& source, ebucoreContact *dest, ObjectModifier* mod = NULL) {
	/*
		<sequence>
		<choice>
			<element name="name" type="string"/>
			<sequence>
				<element name="givenName" type="string"/>
				<element name="familyName" type="string"/>
			</sequence>
		</choice>
		<element name="username" type="string" minOccurs="0"/>
		<element name="occupation" type="string" minOccurs="0">
		</element>
		<element name="details" type="ebucore:detailsType" minOccurs="0" maxOccurs="unbounded"/>
		<element name="stageName" type="string" minOccurs="0" maxOccurs="unbounded">
		</element>
		<element name="relatedContacts" type="ebucore:entityType" minOccurs="0" maxOccurs="unbounded">
		</element>
	</sequence>
	<attribute name="contactId" type="anyURI"/>
	*/
	if (source.name().present()) {
		SIMPLE_MAP(source, name, dest, setgivenName)
	} else {
		SIMPLE_MAP_OPTIONAL(source, givenName, dest, setgivenName)
		SIMPLE_MAP_OPTIONAL(source, familyName, dest, setfamilyName)
	}

	NEW_VECTOR_AND_ASSIGN(source, otherGivenName, ebucoreTextualAnnotation, contactDetailsType::otherGivenName_iterator, mapTextualAnnotation, dest, setotherGivenName)
	NEW_VECTOR_AND_ASSIGN(source, username, ebucoreTextualAnnotation, contactDetailsType::username_iterator, mapTextualAnnotation, dest, setusername)

	//SIMPLE_MAP_OPTIONAL(source, username, dest, setotherGivenName)
	SIMPLE_MAP_OPTIONAL(source, occupation, dest, setoccupation)

	// map contactdetails
	NEW_VECTOR_AND_ASSIGN(source, details, ebucoreContactDetails, contactDetailsType::details_sequence::iterator, mapDetails, dest, setcontactDetails)

	NEW_VECTOR_AND_ASSIGN(source, stageName, ebucoreTextualAnnotation, contactDetailsType::stageName_iterator, mapTextualAnnotation, dest, setstageName)

	// [TODO] We skip RelatedContacts for now, KLV mapping refers to Contacts, while the XSD refers to entities
	// [FIX?] KLV mapping updated to entities
	NEW_VECTOR_AND_ASSIGN(source, relatedContacts, ebucoreEntity, contactDetailsType::relatedContacts_iterator, mapEntity, dest, setcontactRelatedContacts)
	
	// [TODO] We skip contactId for now, KLV mapping refers to an UID, while the XSD refers to anyURI type
}

void mapOrganisationDepartment(organisationDepartment& source, ebucoreOrganisationDepartment *dest, ObjectModifier* mod = NULL) {
	dest->setdepartmentName(source);
	SIMPLE_MAP_OPTIONAL(source, departmentId, dest, setdepartmentId)
}

void mapOrganisation(organisationDetailsType& source, ebucoreOrganisation *dest, ObjectModifier* mod = NULL) {
/*
	<sequence>
		<element name="organisationName" type="dc:elementType"/>
		<element name="organisationDepartment" minOccurs="0">
			<complexType>
				<complexContent>
					<extension base="dc:elementType">
						<attribute name="departmentId" type="anyURI"/>
					</extension>
				</complexContent>
			</complexType>
		</element>
		<element name="details" type="ebucore:detailsType" minOccurs="0" maxOccurs="unbounded"/>
		<element name="contacts" type="ebucore:entityType" minOccurs="0" maxOccurs="unbounded">
		</element>
	</sequence>
	<attribute name="organisationId" type="anyURI"/>
*/
	// [TODO] The KLV mapping is somewhat inconsistent at this point with the XSD:
	//		- KLV organizationID is UID, XSD is anyURI
	//		- XSD does not define an organisationCode
	//		- XSD departmentId is not present in KLV
	//		- KLV defines a typegroup, which is not present in XSD
	//		- KLV organizationRelatedContacts refers to contacts, XSD refers to entities

	if (source.organisationName().size() > 0) {
		dest->setorganisationName(source.organisationName()[0]);
	}

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, organisationDepartment, ebucoreOrganisationDepartment, mapOrganisationDepartment, dest, setorganisationDepartment)

	NEW_VECTOR_AND_ASSIGN(source, details, ebucoreContactDetails, contactDetailsType::details_sequence::iterator, mapDetails, dest, setorganisationDetails)
	// [FIX?] Related contacts are now entities	
	NEW_VECTOR_AND_ASSIGN(source, contacts, ebucoreEntity, organisationDetailsType::contacts_iterator, mapEntity, dest, setorganisationRelatedContacts)
}

void mapEntity(entityType& source, ebucoreEntity *dest, ObjectModifier* mod) {
	/*
	<sequence>
		<element name="contactDetails" type="ebucore:contactDetailsType" minOccurs="0" maxOccurs="unbounded">
		</element>
		<element name="organisationDetails" type="ebucore:organisationDetailsType" minOccurs="0">
		</element>
		<element name="role" minOccurs="0" maxOccurs="unbounded">
			<complexType>
				<attributeGroup ref="ebucore:typeGroup"/>
			</complexType>
		</element>
	</sequence>
	<attribute name="entityId" type="anyURI"/>
	*/

	// [TODO] The KLV mapping lists a single contact, while the XSD specifies a sequence
	// [FIX?] Updated to sequence
	NEW_VECTOR_AND_ASSIGN(source, contactDetails, ebucoreContact, entityType::contactDetails_iterator, mapContact, dest, setentityContact)

	//NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, organisationDetails, ebucoreOrganisation, mapOrganisation, dest, setentityOrganisation)
	NEW_VECTOR_AND_ASSIGN(source, organisationDetails, ebucoreOrganisation, entityType::organisationDetails_iterator, mapOrganisation, dest, setentityOrganisation)

	// [TODO] The KLV mapping lists a single role, while the XSD specifies a sequence
	// [FIX?] Updated to sequence
	NEW_VECTOR_AND_ASSIGN(source, role, ebucoreRole, entityType::role_iterator, mapRole, dest, setentityRole)

	// [TODO] We skip entityId for now, KLV mapping refers to an UID, while the XSD refers to anyURI type
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

	// [TODO] Version and schema need processing

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, metadataProvider, ebucoreEntity, mapEntity, dest, setebucoreMetadataProvider)

	// is there a version node? appearently, no easier way to check than
	// to look through the attributes of the source node and see if there 
	// is a matching attribute
	xercesc_3_1::DOMNamedNodeMap* attrs = source._node()->getAttributes();
	XMLCh* str_version = xercesc_3_1::XMLString::transcode("version");
	const xercesc_3_1::DOMNode* version_node = attrs->getNamedItem(str_version);
	xercesc_3_1::XMLString::release(&str_version);
	if (version_node != NULL) {
		xercesc_3_1::TranscodeToStr version(source.version()._node()->getTextContent(), "UTF-8");
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

void mapTitle(titleType& source, ebucoreTitle *dest, ObjectModifier* mod = NULL) {
	/*
		<sequence>
			<element ref="dc:title">
			</element>
		</sequence>
		<attribute name="attributiondate" type="date">
		</attribute>
		<attribute name="note" type="string">
		</attribute>
	*/
	/* Deprecated 1.3:
	SIMPLE_MAP_NO_GET(source, title, dest, settitleValue)
	SIMPLE_MAP_NO_GET(source, title().lang, dest, settitleLanguage)
	*/
	if (source.title().size() > 0) {
		titleType::title_type& title = source.title()[0];
		dest->settitleValue(title);
		SIMPLE_MAP_NO_GET(title, lang, dest, settitleLanguage)
	}

	SIMPLE_MAP_OPTIONAL(source, note, dest, settitleNote)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, attributiondate, dest, settitleAttributionDate, convert_timestamp)
}

void mapAlternativeTitle(alternativeTitleType& source, ebucoreAlternativeTitle *dest, ObjectModifier* mod = NULL) {
	/*
		<sequence>
			<element ref="dc:title">
			</element>
		</sequence>
		<attributeGroup ref="ebucore:typeGroup">
		</attributeGroup>
 		<attributeGroup ref="ebucore:statusGroup">
		</attributeGroup>
		<attributeGroup ref="ebucore:dateGroup">
		</attributeGroup>
		<attribute name="note" type="string">
		</attribute>
	*/

	// [TODO] XSD alternativeTitle has the dateGroup attributegroup which maps to a number of dates,
	// KLV alternativeTitle only has an alternativeTitleAttributeDate, skipped for now.
	// [FIX?] map date to XSD startdate

	/* Deprecated 1.3:
	SIMPLE_MAP_NO_GET(source, title, dest, setalternativeTitleValue)
	SIMPLE_MAP_NO_GET(source, title().lang, dest, setalternativeTitleLanguage)
	*/
	if (source.title().size() > 0) {
		titleType::title_type& title = source.title()[0];
		dest->setalternativeTitleValue(title);
		SIMPLE_MAP_NO_GET(title, lang, dest, setalternativeTitleLanguage)
	}

	SIMPLE_MAP_OPTIONAL_CONVERT(source, startDate, dest, setalternativeTitleAttributionDate, convert_timestamp)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setalternativeTitleTypeGroup)
	MAP_NEW_STATUS_GROUP_AND_ASSIGN(source, dest, setalternativeTitleStatusGroup)
}

void mapIdentifier(identifierType& source, ebucoreIdentifier *dest, ObjectModifier* mod = NULL) {
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

	// [TODO] 

	SIMPLE_MAP_NO_GET(source, identifier, dest, setidentifierValue)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setidentifierTypeGroup)
	MAP_NEW_FORMAT_GROUP_AND_ASSIGN(source, dest, setidentifierFormatGroup)

	if (source.attributor().present()) {
		ebucoreEntity *obj = newAndModifyObject<ebucoreEntity>(dest->getHeaderMetadata(), mod);
		mapEntity(source.attributor().get(), obj);
		dest->setidentifierAttributorEntity(obj);
	}
}

void mapDescription(descriptionType& source, ebucoreDescription *dest, ObjectModifier* mod = NULL) {
	/*
		<sequence>
			<element ref="dc:description">
			</element>
		</sequence>
		<attributeGroup ref="ebucore:typeGroup">
		</attributeGroup>
		<attribute name="note" type="string">
		</attribute>
	</complexType>
	*/
	SIMPLE_MAP_NO_GET(source, description, dest, setdescriptionValue)
	SIMPLE_MAP_NO_GET(source, description().lang, dest, setdescriptionLanguage)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setdescriptionTypeGroup)
}

void mapSubject(subjectType& source, ebucoreSubject *dest, ObjectModifier* mod = NULL) {
	/*
		<sequence>
			<element ref="dc:subject">
			</element>
			<element name="subjectCode" type="anyURI" minOccurs="0">
			</element>
			<element name="subjectDefinition" type="string" minOccurs="0">
			</element>
			<element name="attributor" type="ebucore:entityType" minOccurs="0">
			</element>
		</sequence>
		<attributeGroup ref="ebucore:typeGroup">
		</attributeGroup>
		<attribute name="note" type="string">
		</attribute>
	*/

	// [TODO] KLV Subject defines batch multiple attributors, XSD (0..1), used a single one in dictionary
	// [FIX?] Updated cardinality

	SIMPLE_MAP_NO_GET(source, subject, dest, setsubjectValue)
	SIMPLE_MAP_NO_GET(source, subject().lang, dest, setsubjectLanguage)
	SIMPLE_MAP_OPTIONAL(source, subjectCode, dest, setsubjectCode)
	SIMPLE_MAP_OPTIONAL(source, subjectDefinition, dest, setsubjectDefinition)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setsubjectTypeGroup)

	if (source.attributor().present()) {
		ebucoreEntity *obj = newAndModifyObject<ebucoreEntity>(dest->getHeaderMetadata(), mod);
		mapEntity(source.attributor().get(), obj);
		dest->setsubjectAttributorEntity(obj);
	}
}

void mapRating(ratingType& source, ebucoreRating *dest, ObjectModifier* mod = NULL) {
	/*
		<sequence>
			<element name="ratingValue" type="string"/>
			<element name="ratingScaleMaxValue" type="string"/>
			<element name="ratingScaleMinValue" type="string"/>
			<element name="ratingProvider" type="ebucore:entityType"/>
		</sequence>
		<attributeGroup ref="ebucore:typeGroup"/>
		<attributeGroup ref="ebucore:formatGroup"/>
	*/
	SIMPLE_MAP_NO_GET(source, ratingValue, dest, setratingValue)
	SIMPLE_MAP_NO_GET(source, ratingScaleMaxValue, dest, setratingScaleMaxValue)
	SIMPLE_MAP_NO_GET(source, ratingScaleMinValue, dest, setratingScaleMinValue)

	ebucoreEntity *obj = newAndModifyObject<ebucoreEntity>(dest->getHeaderMetadata(), mod);
	mapEntity(source.ratingProvider(), obj);
	dest->setratingProviderEntity(obj);

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setratingTypeGroup)
	MAP_NEW_FORMAT_GROUP_AND_ASSIGN(source, dest, setratingFormatGroup)
}

void mapVersion(coreMetadataType::version_type& source, ebucoreVersion *dest, ObjectModifier* mod = NULL) {
	/*
	  <xs:simpleContent>
		<xs:extension base="xs:string">
			<xs:attribute ref="xml:lang" use="optional" default="en"/>
		</xs:extension>
	  </xs:simpleContent>
	*/

	dest->setversionValue(source);
	SIMPLE_MAP_NO_GET(source, lang, dest, setversionLanguage)
}

void mapLanguage(languageType& source, ebucoreLanguage *dest, ObjectModifier* mod = NULL) {
	/*
		<sequence>
			<element ref="dc:language" minOccurs="0">
			</element>
		</sequence>
		<attributeGroup ref="ebucore:typeGroup">
		</attributeGroup>
		<attribute name="note" type="string">
		</attribute>
	*/

	// TODO: KLV Language has an indirection for languagepurpose via a languagepurposeset which contains
	// only a reference to the typegroup, required?
	SIMPLE_MAP_OPTIONAL(source, language, dest, setlanguageName)
	dest->setlanguageCode(source.language().get().lang());
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setlanguagePurposeSet)
}

void mapType(typeType& source, ebucoreType *dest, ObjectModifier* mod = NULL) {
	/*
		<sequence>
			<element ref="dc:type" minOccurs="0" maxOccurs="unbounded">
			</element>
			<element name="genre" minOccurs="0" maxOccurs="unbounded">
				<complexType>
					<attributeGroup ref="ebucore:typeGroup">
					</attributeGroup>
				</complexType>
			</element>
			<element name="objectType" minOccurs="0" maxOccurs="unbounded">
				<complexType>
					<attributeGroup ref="ebucore:typeGroup">
					</attributeGroup>
				</complexType>
			</element>
			<element name="targetAudience" minOccurs="0" maxOccurs="unbounded">
				<complexType>
					<attributeGroup ref="ebucore:typeGroup">
					</attributeGroup>
				</complexType>
			</element>
		</sequence>
		<attribute name="note" type="string">
		</attribute>
	*/
	
	// [TODO] KLV Type ignores content of dc:type?

	// [TODO] KLV objecttypes is only a single reference, and unbounded sequence in XSD
	// [FIX?] Updated cardinality
	std::vector<ebucoreObjectType*> vec_dest_objecttype;
	for (typeType::objectType_iterator it = source.objectType().begin(); it != source.objectType().end(); it++) {
		ebucoreObjectType *obj = newAndModifyObject<ebucoreObjectType>(dest->getHeaderMetadata(), mod);
		MAP_NEW_TYPE_GROUP_AND_ASSIGN(source.objectType().front(), obj, setobjectTypeGroup)
		vec_dest_objecttype.push_back(obj);
	}
	dest->setobjectType(vec_dest_objecttype);

	std::vector<ebucoreTargetAudience*> v1;
	for (typeType::targetAudience_sequence::iterator it = source.targetAudience().begin(); it != source.targetAudience().end(); it++) {
		ebucoreTargetAudience *obj = newAndModifyObject<ebucoreTargetAudience>(dest->getHeaderMetadata(), mod);
		MAP_NEW_TYPE_GROUP_AND_ASSIGN((*it), obj, settargetAudienceKindGroup)
		v1.push_back(obj);
	}
	dest->settargetAudience(v1);

	std::vector<ebucoreGenre*> v2;
	for (typeType::genre_sequence::iterator it = source.genre().begin(); it != source.genre().end(); it++) {
		ebucoreGenre *obj = newAndModifyObject<ebucoreGenre>(dest->getHeaderMetadata(), mod);
		MAP_NEW_TYPE_GROUP_AND_ASSIGN((*it), obj, setgenreKindGroup)
		v2.push_back(obj);
	}
	dest->setgenre(v2);
}

void mapDate(dateType& source, std::vector<ebucoreDate*>& dest, mxfpp::HeaderMetadata *header_metadata, ObjectModifier* mod = NULL) {
	/*
		<sequence>
			<element ref="dc:date" minOccurs="0" maxOccurs="unbounded">
			</element>
			<element name="created" minOccurs="0">
				<complexType>
					<attributeGroup ref="ebucore:dateGroup"/>
				</complexType>
			</element>
			<element name="issued" minOccurs="0">
				<complexType>
					<attributeGroup ref="ebucore:dateGroup"/>
				</complexType>
			</element>
			<element name="modified" minOccurs="0">
				<complexType>
					<attributeGroup ref="ebucore:dateGroup"/>
				</complexType>
			</element>
			<element name="digitised" minOccurs="0">
				<complexType>
					<attributeGroup ref="ebucore:dateGroup"/>
				</complexType>
			</element>
			<element name="alternative" minOccurs="0" maxOccurs="unbounded">
				<complexType>
					<attributeGroup ref="ebucore:dateGroup"/>
					<attributeGroup ref="ebucore:typeGroup"/>
				</complexType>
			</element>
		</sequence>
	*/

	// One XSD EBU Core data is converted to one KLV ebucoreDate + one KLV ebucoreDate per XSD alternative date 
	// (there can be only a single alternative date typegroup def)
	// Only start* attributes are used to map date
	ebucoreDate *obj = newAndModifyObject<ebucoreDate>(header_metadata, mod);
	if (source.created().present()) {
		dateType::created_type& date = source.created().get();
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startYear, obj, setyearCreated, convert_timestamp)
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startDate, obj, setdateCreated, convert_timestamp)
	}
	if (source.issued().present()) {
		dateType::issued_type& date = source.issued().get();
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startYear, obj, setyearIssued, convert_timestamp)
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startDate, obj, setdateIssued, convert_timestamp)
	}
	if (source.modified().present()) {
		dateType::modified_type& date = source.modified().get();
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startYear, obj, setyearModified, convert_timestamp)
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startDate, obj, setdateModified, convert_timestamp)
	}
	if (source.digitised().present()) {
		dateType::digitised_type& date = source.digitised().get();
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startYear, obj, setyearDigitized, convert_timestamp)
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startDate, obj, setdateDigitized, convert_timestamp)
	}
	dest.push_back(obj);

	for (dateType::alternative_iterator it = source.alternative().begin(); it != source.alternative().end(); it++) {
		ebucoreDate *obj = newAndModifyObject<ebucoreDate>(header_metadata, mod);
		dateType::alternative_type& date = (*it);
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startYear, obj, setotherYear, convert_timestamp)
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startDate, obj, setotherDate, convert_timestamp)
		MAP_NEW_TYPE_GROUP_AND_ASSIGN(date, obj, setdateTypeGroup)
		dest.push_back(obj);
	}
}

void mapTemporal(temporal& source, ebucoreTemporal *dest, ObjectModifier* mod = NULL) {
	/*
	<complexType>
		<sequence>
			<element name="PeriodOfTime" minOccurs="0">
				<complexType>
					<attributeGroup ref="ebucore:dateGroup">
						<attribute name="startYear" type="gYear"/>
						<attribute name="startDate" type="date"/>
						<attribute name="startTime" type="time"/>
						<attribute name="endYear" type="gYear"/>
						<attribute name="endDate" type="date"/>
						<attribute name="endTime" type="time"/>
						<attribute name="period" type="string"/>
					</attributeGroup>
				</complexType>
			</element>
		</sequence>
		<attributeGroup ref="ebucore:typeGroup">
		</attributeGroup>
		<attribute name="note" type="string">
		</attribute>
		<attribute name="periodId" type="anyURI">
		</attribute>
	</complexType>
	*/

	// [TODO] There is no typeGroup equivalent in KLV rep., it is in the PeriodOfTime element, which is a batch, and not a single optional element such as in XSD
	// [FIX?] PeriodOfTime element is now a single optional element
	// [EBUCore1.4] PeriodId in temporal??
	NEW_VECTOR_AND_ASSIGN(source, PeriodOfTime, ebucorePeriodOfTime, temporal::PeriodOfTime_iterator, , dest, setperiodOfTime)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, settemporalTypeGroup)
}

void mapPeriodOfTime(PeriodOfTime& source, ebucorePeriodOfTime* dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, period, dest, setperiodId)
	SIMPLE_MAP_OPTIONAL(source, period, dest, setperiodName)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, startYear, dest, setperiodStartYear, convert_timestamp)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, startDate, dest, setperiodStartDate, convert_timestamp)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, startTime, dest, setperiodStartTime, convert_timestamp)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, endYear, dest, setperiodEndYear, convert_timestamp)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, endDate, dest, setperiodEndDate, convert_timestamp)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, endTime, dest, setperiodEndTime, convert_timestamp)
}

void mapSpatial(spatial& source, ebucoreSpatial *dest, ObjectModifier* mod = NULL) {
	/*
	<complexType>
		<sequence>
			<element name="location" minOccurs="0" maxOccurs="unbounded">
				<complexType>
					<sequence>
						<element name="name" type="string" minOccurs="0">
						</element>
						<element name="coordinates" minOccurs="0">
							<complexType>
								<sequence>
									<element name="posy" type="float"/>
									<element name="posx" type="float"/>
								</sequence>
								<attributeGroup ref="ebucore:formatGroup"/>
							</complexType>
						</element>
						<element name="code" type="anyURI" minOccurs="0">
						</element>
					</sequence>
					<attributeGroup ref="ebucore:typeGroup">
					</attributeGroup>
					<attribute name="note" type="string">
					</attribute>
					<attribute name="locationId" type="anyURI">
					</attribute>
				</complexType>
			</element>
		</sequence>
	</complexType>
	*/

	// [TODO] KLV rep. has a batch of locations and coordinates, the XSD rep only has a location, in which (0..1) coordinates can be nested
	// The proper way to reliably link coordinates and locations must be defined, until then, only locations are mapped
	if (source.location().size() > 0) {
		std::vector<ebucoreLocation*> v;
		for (spatial::location_iterator it = source.location().begin(); it != source.location().end(); it++) {
			ebucoreLocation *obj = newAndModifyObject<ebucoreLocation>(dest->getHeaderMetadata(), mod);
			SIMPLE_MAP_OPTIONAL((*it), locationId, obj, setlocationId)
			SIMPLE_MAP_OPTIONAL((*it), name, obj, setlocationName)
			SIMPLE_MAP_OPTIONAL((*it), code, obj, setlocationCode)
			MAP_NEW_TYPE_GROUP_AND_ASSIGN((*it), obj, setlocationKindGroup)

			v.push_back(obj);
		}
		dest->setlocation(v);
	}
}

void mapMetadataCoverage(coverageType& source, ebucoreCoverage *dest, ObjectModifier* mod = NULL) {
	/*
		<sequence>
			<element ref="dc:coverage" minOccurs="0">
			</element>
			<element name="temporal" minOccurs="0"></element>
			<element name="spatial" minOccurs="0"></element>
		</sequence>
	*/

	// [TODO] KLV Coverage has no XSD dc:coverage string representation
	// [TODO] KLV Coverage has a batch of spatial and tempoal and only 0 or 1 in XSD
	// [Fix?] Updated cardinality
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, temporal, ebucoreTemporal, mapTemporal, dest, settemporal)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, spatial, ebucoreSpatial, mapSpatial, dest, setspatial)
}

void mapRights(rightsType& source, ebucoreRights *dest, ObjectModifier* mod = NULL) {
	/*
		<sequence>
			<element ref="dc:rights" minOccurs="0">
			</element>
			<element name="rightsLink" type="anyURI" minOccurs="0">
			</element>
			<element name="rightsHolder" type="ebucore:entityType" minOccurs="0">
			</element>
			<element name="exploitationIssues" type="dc:elementType" minOccurs="0">
			</element>
			<element name="coverage" type="ebucore:coverageType" minOccurs="0">
			</element>
			<element name="rightsClearanceFlag" type="boolean" minOccurs="0">
			</element>
			<element name="disclaimer" type="dc:elementType" minOccurs="0" maxOccurs="unbounded">
			</element>
			<element name="rightsId" type="ebucore:identifierType" minOccurs="0" maxOccurs="unbounded">
			</element>
			<element name="contactDetails" type="ebucore:contactDetailsType" minOccurs="0" maxOccurs="unbounded">
			</element>
		</sequence>
		<attributeGroup ref="ebucore:typeGroup">
		</attributeGroup>
		<attribute name="note" type="string">
		</attribute>
		<attribute name="formatIDRefs" type="IDREFS">
		</attribute>
	*/

	// [TODO] KLV RightsId is a string, XSD rights id is an identitytype, not clear how to map...
	// [TODO] KLV rightsAttributedID is nowhere to be found in EBU Core?

	SIMPLE_MAP_OPTIONAL(source, rights, dest, setrightsValue)
	if (source.rights().present()) {
		dest->setrightsLanguage(source.rights().get().lang());
	}
	SIMPLE_MAP_OPTIONAL(source, rightsClearanceFlag, dest, setrightsClearanceFlag)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, formatIDRefs, dest, setrightsFormatIDRef, convert)
	SIMPLE_MAP_OPTIONAL(source, exploitationIssues, dest, setexploitationIssues)
	SIMPLE_MAP_OPTIONAL(source, rightsLink, dest, setrightsLink)

	// [TODO] KLV coverage is a vector while XSD coverage is a single optional element
	// [FIX?] Updated cardinality
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, coverage, ebucoreCoverage, mapMetadataCoverage, dest, setrightsCoverage)

	// [TODO] KLV rightsholder is a vector while XSD rightsholder is a single optional element
	// [FIX?] Updated cardinality
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, rightsHolder, ebucoreEntity, mapEntity, dest, setrightsHolderEntity)

	NEW_VECTOR_AND_ASSIGN(source, contactDetails, ebucoreContact, rightsType::contactDetails_sequence::iterator, mapContact, dest, setrightsContacts)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setrightsKindGroup)
}

bool nodeOrdering(xsd::cxx::tree::type *a, xsd::cxx::tree::type *b) 
{
	return (a->_node()->compareDocumentPosition(b->_node()) == 2 /* DOCUMENT_POSITION_PRECEDING */);	// else, return larger...
}

void mapPublicationHistoryEvent(publicationEvent& source, ebucorePublicationHistoryEvent* dest, ObjectModifier* mod = NULL) {
	/*
	<complexType>
			<sequence>
				<element name="publicationDate" type="date" minOccurs="0">
				</element>
				<element name="publicationTime" type="time" minOccurs="0">
				</element>
				<element name="publicationService" minOccurs="0" type="string">
				</element>
				<element name="publicationMedium" minOccurs="0">
					<complexType>
						<attributeGroup ref="ebucore:typeGroup"/>
					</complexType>
				</element>
				<element name="publicationChannel" minOccurs="0">
					<complexType>
						<simpleContent>
							<extension base="string"> </extension>
						</simpleContent>
					</complexType>
				</element>
			</sequence>
			<attribute name="firstShowing" type="boolean"/>
			<attribute name="live" type="boolean"/>
			<attribute name="free" type="boolean"/>
			<attribute name="formatIdRef" type="IDREF">
			</attribute>
			<attribute name="rightsIDRefs" type="IDREFS">
			</attribute>
	</complexType>
	*/

	// [TODO] XSD publicationMedium is an empty type with a typegroup, KLV is a plain string, using typeLabel for now
	// [TODO] XSD has live, free, and rightsIDRefs, no equivalent in KLV?

	SIMPLE_MAP_OPTIONAL(source, firstShowing, dest, setfirstPublicationFlag)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, publicationDate, dest, setpublicationDate, convert_timestamp)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, publicationTime, dest, setpublicationDate, convert_timestamp)
	SIMPLE_MAP_OPTIONAL(source, publicationChannel, dest, setpublicationChannel)
	SIMPLE_MAP_OPTIONAL(source, publicationService, dest, setpublicationService)
	if (source.publicationMedium().present() && source.publicationMedium().get().typeLabel().present()) {
		dest->setpublicationMedium(source.publicationMedium().get().typeLabel().get());
	}
}

void mapPublicationHistory(publicationHistoryType& source, std::vector<ebucorePublicationHistoryEvent*>& dest, mxfpp::HeaderMetadata *header_metadata, ObjectModifier* mod = NULL) {
	/*
	<sequence>
		<element name="publicationEvent" minOccurs="0" maxOccurs="unbounded">
		</element>
	</sequence>
	*/
	std::vector<ebucorePublicationHistoryEvent*> vec_dest_hist;
	for (publicationHistoryType::publicationEvent_iterator it = source.publicationEvent().begin(); it != source.publicationEvent().end(); it++) {
		ebucorePublicationHistoryEvent *obj = newAndModifyObject<ebucorePublicationHistoryEvent>(header_metadata, mod);
		mapPublicationHistoryEvent(*it, obj, mod);
		vec_dest_hist.push_back(obj);
	}
	dest.assign(vec_dest_hist.begin(), vec_dest_hist.end());
}

void mapCustomRelation(relationType& source, ebucoreCustomRelation *dest, ObjectModifier* mod = NULL) {
	/*
		<choice>
			<element ref="dc:relation">
			</element>
			<element name="relationIdentifier" type="ebucore:identifierType">
			</element>
			<element name="relationLink" type="anyURI">
			</element>
		</choice>
		<attributeGroup ref="ebucore:typeGroup">
		</attributeGroup>
		<attribute name="runningOrderNumber" type="integer">
		</attribute>
		<attribute name="note" type="string">
		</attribute>
	*/

	// [TODO] XSD relationIdentifier is identifierType, KLV identifier is a UMID, how do we resolve?
	// [TODO] KLV totalNumberOfGroupMembers should be resolved by other means that just the EBU-Core source XML document?
	// [TODO] KLV orderedGroupFlag should be resolved by other means that just the EBU-Core source XML document?

	SIMPLE_MAP_OPTIONAL(source, relation, dest, setrelationByName)
	SIMPLE_MAP_OPTIONAL(source, relationLink, dest, setrelationLink)
	SIMPLE_MAP_OPTIONAL(source, runningOrderNumber, dest, setrunningOrderNumber)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setcustomRelationTypeGroup)
}

void mapCoreMetadata(coreMetadataType& source, ebucoreCoreMetadata *dest, ObjectModifier* mod) {

	NEW_VECTOR_AND_ASSIGN(source, title, ebucoreTitle, coreMetadataType::title_iterator, mapTitle, dest, settitle)	
	NEW_VECTOR_AND_ASSIGN(source, alternativeTitle, ebucoreAlternativeTitle, coreMetadataType::alternativeTitle_iterator, mapAlternativeTitle, dest, setalternativeTitle)
	NEW_VECTOR_AND_ASSIGN(source, creator, ebucoreEntity, coreMetadataType::creator_iterator, mapEntity, dest, setcreator)
	NEW_VECTOR_AND_ASSIGN(source, subject, ebucoreSubject, coreMetadataType::subject_iterator, mapSubject, dest, setsubject)
	NEW_VECTOR_AND_ASSIGN(source, description, ebucoreDescription, coreMetadataType::description_iterator, mapDescription, dest, setdescription)
	NEW_VECTOR_AND_ASSIGN(source, publisher, ebucoreEntity, coreMetadataType::publisher_iterator, mapEntity, dest, setpublisher)
	NEW_VECTOR_AND_ASSIGN(source, contributor, ebucoreEntity, coreMetadataType::contributor_iterator, mapEntity, dest, setcontributor)

	std::vector<ebucoreDate*> vec_dates;
	for (coreMetadataType::date_iterator it = source.date().begin(); it != source.date().end(); it++) {
		mapDate(*it, vec_dates, dest->getHeaderMetadata());
	}
	dest->setdate(vec_dates);

	NEW_VECTOR_AND_ASSIGN(source, type, ebucoreType, coreMetadataType::type_iterator, mapType, dest, settype)
	NEW_VECTOR_AND_ASSIGN(source, identifier, ebucoreIdentifier, coreMetadataType::identifier_iterator, mapIdentifier, dest, setidentifier)
	NEW_VECTOR_AND_ASSIGN(source, language, ebucoreLanguage, coreMetadataType::language_iterator, mapLanguage, dest, setlanguage)
	NEW_VECTOR_AND_ASSIGN(source, coverage, ebucoreCoverage, coreMetadataType::coverage_iterator, mapMetadataCoverage, dest, setcoverage)
	NEW_VECTOR_AND_ASSIGN(source, rights, ebucoreRights, coreMetadataType::rights_iterator, mapRights, dest, setrights)
	NEW_VECTOR_AND_ASSIGN(source, rating, ebucoreRating, coreMetadataType::rating_iterator, mapRating, dest, setrating)

	if (source.version().size() > 0) {
		ebucoreVersion *obj = newAndModifyObject<ebucoreVersion>(dest->getHeaderMetadata(), mod);
		mapVersion(source.version()[0], obj);
		dest->setversion(obj);
	}
	
	if (source.publicationHistory().present()) {
		std::vector<ebucorePublicationHistoryEvent*> vec_publications;
		mapPublicationHistory(source.publicationHistory().get(), vec_publications, dest->getHeaderMetadata());
		dest->setpublicationHistoryEvent(vec_publications);
	}

	NEW_VECTOR_AND_ASSIGN(source, relation, ebucoreCustomRelation, coreMetadataType::relation_iterator, mapCustomRelation, dest, setcustomRelation)

	/*
	[TODO]:
		basicRelation sets
		format sets
		part sets
	*/
}

/*void mapPart(part& source, ebucorePartMetadata *dest, ObjectModifier* mod) {

	//MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setpartTypeGroup)
}*/

}