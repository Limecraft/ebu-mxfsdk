
#include <iostream>
#include <fstream>
#include <memory>

#include <bmx/BMXException.h>
#include <bmx/Logging.h>

#include "EBUCoreProcessor.h"

#include "EBU_CORE_20110915.hxx"

#include <metadata/EBUCoreDMS++.h>

#include <xercesc/util/TransService.hpp>

using namespace ebuCore_2011;
using namespace mxfpp;
using namespace bmx;

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
		mapMethod(source.sourceProperty().get(), obj);	\
		dest->destProperty(obj);	\
	}

#define NEW_VECTOR_AND_ASSIGN(source, sourceProperty, destType, iteratorType, mapMethod, dest, destProperty)	\
	{ std::vector<destType*> vec_dest_destProperty;	\
	for (iteratorType it = source.sourceProperty().begin(); it != source.sourceProperty().end(); it++) {	\
		destType *obj = newAndModifyObject<destType>(dest->getHeaderMetadata(), mod);	\
		mapMethod(*it, obj);	\
		vec_dest_destProperty.push_back(obj);	\
	}	\
	dest->destProperty(vec_dest_destProperty); }

#define	SIMPLE_MAP_OPTIONAL_TO_NEW_VECTOR_AND_ASSIGN(source, sourceProperty, destType, mapMethod, dest, destProperty) \
	if (source.sourceProperty().present()) {	\
		destType *obj = newAndModifyObject<destType>(dest->getHeaderMetadata(), mod);	\
		mapMethod(source.sourceProperty().get(), obj);	\
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

#define RMAP_TYPE_GROUP(source, dest, definitionType, labelType, linkType)	\
	if (source->havetypeGroupDefinition()) {	\
		dest.typeDefinition().set(std::auto_ptr<definitionType>( new definitionType( source->gettypeGroupDefinition() ) ));	\
	}	\
	if (source->havetypeGroupLabel()) {	\
		dest.typeLabel().set(std::auto_ptr<labelType>( new labelType( source->gettypeGroupLabel() ) ));	\
	}	\
	if (source->havetypeGroupLink()) {	\
		dest.typeLink().set( std::auto_ptr<linkType> ( new linkType( source->gettypeGroupLink() ) ));	\
	}
#define RMAP_STATUS_GROUP(source, dest, definitionType, labelType, linkType)	\
	if (source->havestatusGroupDefinition()) {	\
		dest.statusDefinition().set(std::auto_ptr<definitionType>( new definitionType( source->getstatusGroupDefinition() ) ));	\
	}	\
	if (source->havestatusGroupLabel()) {	\
		dest.statusLabel().set(std::auto_ptr<labelType>( new labelType( source->getstatusGroupLabel() ) ));	\
	}	\
	if (source->havestatusGroupLink()) {	\
		dest.statusLink().set( std::auto_ptr<linkType> ( new linkType( source->getstatusGroupLink() ) ));	\
	}
#define RMAP_FORMAT_GROUP(source, dest, definitionType, labelType, linkType)	\
	if (source->haveformatGroupDefinition()) {	\
		dest.formatDefinition().set(std::auto_ptr<definitionType>( new definitionType( source->getformatGroupDefinition() ) ));	\
	}	\
	if (source->haveformatGroupLabel()) {	\
		dest.formatLabel().set(std::auto_ptr<labelType>( new labelType( source->getformatGroupLabel() ) ));	\
	}	\
	if (source->haveformatGroupLink()) {	\
		dest.formatLink().set( std::auto_ptr<linkType> ( new linkType( source->getformatGroupLink() ) ));	\
	}

class ObjectModifier {
public:
	virtual void Modify(InterchangeObject *obj);
};

class GenerationUIDAppender : public ObjectModifier {
	mxfUUID _generationUID;
public:
	GenerationUIDAppender(mxfUUID GenerationUID) {
		_generationUID = GenerationUID;
	}
	void Modify(InterchangeObject *obj) {
		obj->setGenerationUID(_generationUID);
	}
};

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

void mapAddressLine(std::string source, ebucoreAddressLine *dest, ObjectModifier* mod = NULL) {
	dest->setaddressLine(source);
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
		NEW_VECTOR_AND_ASSIGN(source, addressLine, ebucoreAddressLine, addressType::addressLine_iterator, mapAddressLine, dest, setaddressLines)
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

void mapAddress(ebucoreAddress *source, addressType& dest) {
	// atm, only a single address line is defined in KLV mapping
	if (source->haveaddressLines()) {
		addressType::addressLine_sequence lines;
		std::vector<ebucoreAddressLine*> source_vec = source->getaddressLines();
		for (std::vector<ebucoreAddressLine*>::iterator it = source_vec.begin(); it != source_vec.end(); it++) {
			std::auto_ptr<detailsType> p( new detailsType() );
			lines.push_back((*it)->getaddressLine());
		}
		dest.addressLine(lines);
	}

	if (source->havetownCity())
		dest.addressTownCity() = source->gettownCity();
	if (source->havecountyState())
		dest.addressCountyState() = source->getcountyState();
	if (source->havedeliveryCode())
		dest.addressDeliveryCode() = source->getdeliveryCode();

	// special treatment for country, current KLV mapping is not via a typeGroup!
	if (source->havecountryCode() || source->havecountryName()) {
		std::auto_ptr<addressType::country_type> p( new addressType::country_type() );
		if (source->havecountryCode())
			p->typeLink() = source->getcountryCode();
		if (source->havecountryName())
			p->typeLabel() = source->getcountryName();
		dest.country(p);
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
	SIMPLE_MAP_OPTIONAL(source, emailAddress, dest, setemailAddress)
	SIMPLE_MAP_OPTIONAL(source, webAddress, dest, setwebAddress)

	// map address
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, address, ebucoreAddress, mapAddress, dest, setaddress)
	SIMPLE_MAP_OPTIONAL(source, telephoneNumber, dest, settelephoneNumber)
	SIMPLE_MAP_OPTIONAL(source, mobileTelephoneNumber, dest, setmobileTelephoneNumber)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setdetailsType)
}

void mapDetails(ebucoreContactDetails *source, detailsType& dest) {

	if (source->haveemailAddress())
		dest.emailAddress() = source->getemailAddress();
	if (source->havewebAddress())
		dest.webAddress() = source->getwebAddress();

	// map address
	if (source->haveaddress()) {
		std::auto_ptr<addressType> p( new addressType() );
		mapAddress(source->getaddress(), *(p.get()) );
		dest.address(p);
	}
	
	if (source->havetelephoneNumber())
		dest.telephoneNumber() = source->gettelephoneNumber();
	if (source->havemobileTelephoneNumber())
		dest.mobileTelephoneNumber() = source->getmobileTelephoneNumber();

	RMAP_TYPE_GROUP(source->getdetailsType(), dest, detailsType::typeDefinition_type, detailsType::typeLabel_type, detailsType::typeLink_type)
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

	// username -> othergivenname mapping?
	SIMPLE_MAP_OPTIONAL(source, username, dest, setotherGivenName)
	SIMPLE_MAP_OPTIONAL(source, occupation, dest, setoccupation)

	// map contactdetails
	NEW_VECTOR_AND_ASSIGN(source, details, ebucoreContactDetails, contactDetailsType::details_sequence::iterator, mapDetails, dest, setcontactDetails)

	if (source.stageName().size() > 0) {
		dest->setstageName(source.stageName().front());
	}

	// [TODO] We skip RelatedContacts for now, KLV mapping refers to Contacts, while the XSD refers to entities
	/*std::vector<ebucoreContact*> relatedContacts;
	for (contactDetailsType::relatedContacts_sequence::iterator it = source.relatedContacts().begin(); it != source.details().end(); it++) {
		ebucoreContact *obj = new ebucoreContact(dest->getHeaderMetadata());
		mapContact(*it, obj);
		relatedContacts.push_back(obj);
	}
	dest->setcontactRelatedContacts(relatedContacts);*/
	
	// [TODO] We skip contactId for now, KLV mapping refers to an UID, while the XSD refers to anyURI type

}

void mapContact(ebucoreContact *source, contactDetailsType& dest) {

	if (source->havefamilyName()) {
		// both givenname and familyname are present
		dest.familyName() = source->getfamilyName();
		dest.givenName() = source->getgivenName();
	} else {
		dest.name() = source->getgivenName();
	}
	if (source->haveotherGivenName())
		dest.username() = source->getotherGivenName();
	if (source->haveoccupation())
		dest.occupation() = source->getoccupation();

	//dest.details()

	// map contactdetails
	contactDetailsType::details_sequence details;
	std::vector<ebucoreContactDetails*> source_vec = source->getcontactDetails();
	for (std::vector<ebucoreContactDetails*>::iterator it = source_vec.begin(); it != source_vec.end(); it++) {
		std::auto_ptr<detailsType> p( new detailsType() );
		mapDetails(*it, *(p.get()));
		details.push_back(p);
	}
	dest.details(details);

	if (source->havestageName()) {
		contactDetailsType::stageName_sequence seq;
		seq.push_back( source->getstageName() );
		dest.stageName(seq);
	}

	// [TODO] We skip RelatedContacts for now, KLV mapping refers to Contacts, while the XSD refers to entities
	/*std::vector<ebucoreContact*> relatedContacts;
	for (contactDetailsType::relatedContacts_sequence::iterator it = source.relatedContacts().begin(); it != source.details().end(); it++) {
		ebucoreContact *obj = new ebucoreContact(dest->getHeaderMetadata());
		mapContact(*it, obj);
		relatedContacts.push_back(obj);
	}
	dest->setcontactRelatedContacts(relatedContacts);*/
	
	// [TODO] We skip contactId for now, KLV mapping refers to an UID, while the XSD refers to anyURI type

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

	dest->setorganisationName(source.organisationName());
	SIMPLE_MAP_OPTIONAL(source, organisationDepartment, dest, setorganisationDepartment)	
	NEW_VECTOR_AND_ASSIGN(source, details, ebucoreContactDetails, contactDetailsType::details_sequence::iterator, mapDetails, dest, setorganisationDetails)
}

void mapOrganisation(ebucoreOrganisation *source, organisationDetailsType& dest) {

	dest.organisationName() = source->getorganisationName();
	if (source->haveorganisationDepartment())
		dest.organisationDepartment() = source->getorganisationDepartment();

	organisationDetailsType::details_sequence seq;
	std::vector<ebucoreContactDetails*> source_vec = source->getorganisationDetails();
	for (std::vector<ebucoreContactDetails*>::iterator it = source_vec.begin(); it != source_vec.end(); it++) {
		std::auto_ptr<detailsType> p( new detailsType() );
		mapDetails(*it, *(p.get()));
		seq.push_back(p);
	}
	dest.details(seq);

}

void mapEntity(entityType& source, ebucoreEntity *dest, ObjectModifier* mod = NULL) {
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
	/*std::vector<ebucoreContact*> contacts;
	for (entityType::contactDetails_sequence::iterator it = source.contactDetails().begin(); it != source.contactDetails().end(); it++) {
		ebucoreContact *obj = new ebucoreContact(dest->getHeaderMetadata());
		mapContact(*it, obj);
		contacts.push_back(obj);
	}*/
	if (source.contactDetails().size() > 0) {
		ebucoreContact *obj = newAndModifyObject<ebucoreContact>(dest->getHeaderMetadata(), mod);
		mapContact(source.contactDetails().front(), obj);
		dest->setentityContact(obj);
	}

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, organisationDetails, ebucoreOrganisation, mapOrganisation, dest, setentityOrganisation)

	// [TODO] The KLV mapping lists a single role, while the XSD specifies a sequence
	if (source.role().size() > 0) {
		ebucoreRole *obj = newAndModifyObject<ebucoreRole>(dest->getHeaderMetadata(), mod);
		mapRole(source.role().front(), obj);
		dest->setentityRole(obj);
	}

	// [TODO] We skip entityId for now, KLV mapping refers to an UID, while the XSD refers to anyURI type
}

void mapEntity(ebucoreEntity *source, entityType& dest) {
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
	/*std::vector<ebucoreContact*> contacts;
	for (entityType::contactDetails_sequence::iterator it = source.contactDetails().begin(); it != source.contactDetails().end(); it++) {
		ebucoreContact *obj = new ebucoreContact(dest->getHeaderMetadata());
		mapContact(*it, obj);
		contacts.push_back(obj);
	}*/
	if (source->haveentityContact()) {
		entityType::contactDetails_sequence seq;
		std::auto_ptr<entityType::contactDetails_type> p( new entityType::contactDetails_type() );
		mapContact(source->getentityContact(), *(p.get()));
		seq.push_back(p);
		dest.contactDetails(seq);
	}

	if (source->haveentityOrganisation()) {
		std::auto_ptr<entityType::organisationDetails_type> p( new entityType::organisationDetails_type("") );
		mapOrganisation(source->getentityOrganisation(), *(p.get()) );
		dest.organisationDetails(p);
	}

	// [TODO] The KLV mapping lists a single role, while the XSD specifies a sequence
	if (source->haveentityRole()) {
		ebucoreRole *role = source->getentityRole();
		ebucoreTypeGroup *tg = role->getroleType();
		std::auto_ptr<entityType::role_type> p( new entityType::role_type() );
		RMAP_TYPE_GROUP(tg, (*(p.get())), role::typeDefinition_type, role::typeLabel_type, role::typeLink_type)
		entityType::role_sequence seq;
		seq.push_back(p);
		dest.role(seq);
	}

	// [TODO] We skip entityId for now, KLV mapping refers to an UID, while the XSD refers to anyURI type
}


void mapMetadataSchemeInformation(ebuCoreMainType& source, ebucoreMetadataSchemeInformation *dest, ObjectModifier* mod = NULL) {
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
	XMLCh* str_schema = xercesc_3_1::XMLString::transcode("schema");
	const xercesc_3_1::DOMNode* schema_node = attrs->getNamedItem(str_schema);
	xercesc_3_1::XMLString::release(&str_schema);
	if (schema_node != NULL) {
		xercesc_3_1::TranscodeToStr schema(source.schema()._node()->getTextContent(), "UTF-8");
		std::string std_schema((char*)schema.str());
		dest->setebucoreMetadataScheme(std_schema);
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

xml_schema::date* convert_timestamp_date(mxfTimestamp source) {
	return new xml_schema::date(source.year, source.month, source.day);
}

xml_schema::time* convert_timestamp_time(mxfTimestamp source) {
	return new xml_schema::time(source.hour, source.min, source.sec);
}

xml_schema::gyear* convert_timestamp_year(mxfTimestamp source) {
	return new xml_schema::gyear(source.year);
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

xml_schema::idrefs* convert_idrefs(std::string& source) {
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
	SIMPLE_MAP_NO_GET(source, title, dest, settitleValue)
	SIMPLE_MAP_NO_GET(source, title().lang, dest, settitleLanguage)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, attributiondate, dest, settitleAttributionDate, convert_timestamp)
}

void mapTitle(ebucoreTitle *source, titleType& dest) {
	dest.title() = source->gettitleValue();
	dest.title().lang() = source->gettitleLanguage();
	if (source->havetitleAttributionDate()) {
		std::auto_ptr<ebuCoreMainType::dateLastModified_type> dp( convert_timestamp_date(source->gettitleAttributionDate()));
		dest.attributiondate().set(dp);
	}
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

	SIMPLE_MAP_NO_GET(source, title, dest, setalternativeTitleValue)
	SIMPLE_MAP_NO_GET(source, title().lang, dest, setalternativeTitleLanguage)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setalternativeTitleTypeGroup)
	MAP_NEW_STATUS_GROUP_AND_ASSIGN(source, dest, setalternativeTitleStatusGroup)
}

void mapAlternativeTitle(ebucoreAlternativeTitle *source, alternativeTitleType& dest) {
	dest.title() = source->getalternativeTitleValue();
	dest.title().lang() = source->getalternativeTitleLanguage();

	ebucoreTypeGroup* tg = source->getalternativeTitleTypeGroup();
	ebucoreStatusGroup* sg = source->getalternativeTitleStatusGroup();
	RMAP_TYPE_GROUP(tg, dest, alternativeTitleType::typeDefinition_type, alternativeTitleType::typeLabel_type, alternativeTitleType::typeLink_type)
	RMAP_STATUS_GROUP(sg, dest, alternativeTitleType::statusDefinition_type, alternativeTitleType::statusLabel_type, alternativeTitleType::statusLink_type)
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

	RMAP_FORMAT_GROUP(source->getidentifierFormatGroup(), dest, identifierType::formatDefinition_type, identifierType::formatLabel_type, identifierType::formatLink_type)
	RMAP_TYPE_GROUP(source->getidentifierTypeGroup(), dest, identifierType::typeDefinition_type, identifierType::typeLabel_type, identifierType::typeLink_type)

	if (source->haveidentifierAttributorEntity()) {
		std::auto_ptr<entityType> tp( new entityType() );
		mapEntity(source->getidentifierAttributorEntity(), *tp);
		dest.attributor(tp);
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

void mapDescription(ebucoreDescription *source, descriptionType& dest) {
	dest.description() = source->getdescriptionValue();
	dest.description().lang() = source->getdescriptionLanguage();
	RMAP_TYPE_GROUP(source->getdescriptionTypeGroup(), dest, descriptionType::typeDefinition_type, descriptionType::typeLabel_type, descriptionType::typeLink_type)
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

void mapSubject(ebucoreSubject *source, subjectType& dest) {
	// [TODO] KLV Subject defines batch multiple attributors, XSD (0..1), used a single one in dictionary

	dest.subject() = source->getsubjectValue();
	dest.subject().lang() = source->getsubjectLanguage();

	if (source->havesubjectCode()) {
		dest.subjectCode(source->getsubjectCode());
	}

	if (source->havesubjectDefinition()) {
		dest.subjectDefinition(source->getsubjectDefinition());
	}

	RMAP_TYPE_GROUP(source->getsubjectTypeGroup(), dest, subjectType::typeDefinition_type, subjectType::typeLabel_type, subjectType::typeLink_type)

	if (source->havesubjectAttributorEntity()) {
		std::auto_ptr<entityType> tp( new entityType() );
		mapEntity(source->getsubjectAttributorEntity(), *tp);
		dest.attributor(tp);
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

void mapRating(ebucoreRating *source, ratingType& dest) {
	dest.ratingValue() = source->getratingValue();
	dest.ratingScaleMinValue() = source->getratingScaleMinValue();
	dest.ratingScaleMaxValue() = source->getratingScaleMaxValue();

	std::auto_ptr<entityType> tp( new entityType() );
	mapEntity(source->getratingProviderEntity(), *tp);
	dest.ratingProvider(tp);

	RMAP_TYPE_GROUP(source->getratingTypeGroup(), dest, ratingType::typeDefinition_type, ratingType::typeLabel_type, ratingType::typeLink_type)
	RMAP_FORMAT_GROUP(source->getratingFormatGroup(), dest, ratingType::formatDefinition_type, ratingType::formatLabel_type, ratingType::formatLink_type)
}

void mapVersion(coreMetadataType::version_type& source, ebucoreVersion *dest, ObjectModifier* mod = NULL) {
	/*
	  <xs:simpleContent>
		<xs:extension base="xs:string">
			<xs:attribute ref="xml:lang" use="optional" default="en"/>
		</xs:extension>
	  </xs:simpleContent>
	*/

	// [TODO] KLV version does not define a language, while the XSD (i.e., DC element) does.
	dest->setversionValue(source);
	// [TODO] SIMPLE_MAP_NO_GET(source, lang, dest, setversionLanguage)
}

void mapVersion(ebucoreVersion *source, coreMetadataType::version_type& dest) {
	dest = source->getversionValue();
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
	
	ebucoreLanguagePurpose *obj = newAndModifyObject<ebucoreLanguagePurpose>(dest->getHeaderMetadata(), mod);
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, obj, setlanguagePurposeTypeGroup)
	dest->setlanguagePurposeSet(obj);
}

void mapLanguage(ebucoreLanguage *source, languageType& dest) {
	dest.language() = source->getlanguageName();
	dest.language().get().lang() = source->getlanguageCode();

	RMAP_TYPE_GROUP( source->getlanguagePurposeSet()->getlanguagePurposeTypeGroup(), 
		dest, languageType::typeDefinition_type, languageType::typeLabel_type, languageType::typeLink_type)
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

	if (source.objectType().size() > 0) {
		ebucoreObjectType *obj = newAndModifyObject<ebucoreObjectType>(dest->getHeaderMetadata(), mod);
		MAP_NEW_TYPE_GROUP_AND_ASSIGN(source.objectType().front(), obj, setobjectTypeGroup)
		dest->setobjectType(obj);
	}

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

void mapType(ebucoreType *source, typeType& dest) {
	if (source->haveobjectType()) {
		std::auto_ptr<objectType> p( new objectType() );
		RMAP_TYPE_GROUP(source->getobjectType()->getobjectTypeGroup(), (*p), objectType::typeDefinition_type, objectType::typeLabel_type, objectType::typeLink_type)
		dest.objectType().push_back(p);
	}

	typeType::targetAudience_sequence tauds;
	std::vector<ebucoreTargetAudience*> source_tauds = source->gettargetAudience();
	for (std::vector<ebucoreTargetAudience*>::iterator it = source_tauds.begin(); it != source_tauds.end(); it++) {
		std::auto_ptr<targetAudience> p( new targetAudience() );
		RMAP_TYPE_GROUP((*it)->gettargetAudienceKindGroup(), (*p), targetAudience::typeDefinition_type, targetAudience::typeLabel_type, targetAudience::typeLink_type)
		tauds.push_back(p);
	}
	dest.targetAudience(tauds);

	typeType::genre_sequence gens;
	std::vector<ebucoreGenre*> source_gens = source->getgenre();
	for (std::vector<ebucoreGenre*>::iterator it = source_gens.begin(); it != source_gens.end(); it++) {
		std::auto_ptr<genre> p( new genre() );
		RMAP_TYPE_GROUP((*it)->getgenreKindGroup(), (*p), genre::typeDefinition_type, genre::typeLabel_type, genre::typeLink_type)
		gens.push_back(p);
	}
	dest.genre(gens);
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

void mapDate(ebucoreDate* source, dateType& dest) {
	// Reserve mapping operation of date:
	// Map each of the regular dates to their counterpart in XSD,
	if (source->haveotherDate() || source->haveotherYear()) {
		dateType::alternative_sequence alts;
		std::auto_ptr<dateType::alternative_type> p ( new dateType::alternative_type() );
		if (source->haveotherDate())
			p->startDate( std::auto_ptr<xml_schema::date>( convert_timestamp_date(source->getotherDate()) ) );
		if (source->haveotherYear())
			p->startYear( std::auto_ptr<xml_schema::gyear>( convert_timestamp_year(source->getotherYear()) ) );
		RMAP_TYPE_GROUP( source->getdateTypeGroup(), (*p), dateType::alternative_type::typeDefinition_type, dateType::alternative_type::typeLabel_type, dateType::alternative_type::typeLink_type)
		dest.alternative(alts);
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
	bool hasPeriodOfTime = source.periodId().present() | source.PeriodOfTime().present();
	if (hasPeriodOfTime) {
		ebucorePeriodOfTime *obj = newAndModifyObject<ebucorePeriodOfTime>(dest->getHeaderMetadata(), mod);
		if (source.periodId().present()) {
			obj->setperiodId(source.periodId().get());
		}
		if (source.PeriodOfTime().present()) {
			PeriodOfTime &pot = source.PeriodOfTime().get();
			SIMPLE_MAP_OPTIONAL_CONVERT(pot, startYear, obj, setperiodStartYear, convert_timestamp)
			SIMPLE_MAP_OPTIONAL_CONVERT(pot, startDate, obj, setperiodStartDate, convert_timestamp)
			SIMPLE_MAP_OPTIONAL_CONVERT(pot, startTime, obj, setperiodStartTime, convert_timestamp)
			SIMPLE_MAP_OPTIONAL_CONVERT(pot, endYear, obj, setperiodEndYear, convert_timestamp)
			SIMPLE_MAP_OPTIONAL_CONVERT(pot, endDate, obj, setperiodEndDate, convert_timestamp)
			SIMPLE_MAP_OPTIONAL_CONVERT(pot, endTime, obj, setperiodEndTime, convert_timestamp)
			SIMPLE_MAP_OPTIONAL(pot, period, obj, setperiodName)

			MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, obj, setperiodKindGroup)
		}

		std::vector<ebucorePeriodOfTime*> v;
		v.push_back(obj);
		dest->setperiodOfTime(v);
	}
}

void mapTemporal(ebucoreTemporal *source, temporal& dest) {
	// if there is more that a single period of time, we only use the first one
	std::vector<ebucorePeriodOfTime*> pots = source->getperiodOfTime();
	if (pots.size() > 0) {
		// pick the first to work with
		ebucorePeriodOfTime *pot = pots[0];
		std::auto_ptr<PeriodOfTime> p(new PeriodOfTime());

		if (pot->haveperiodId())
			dest.periodId() = pot->getperiodId();
		if (pot->haveperiodName())
			p->period() = pot->getperiodName();
		if (pot->haveperiodStartYear())
			p->startYear( std::auto_ptr<xml_schema::gyear>( convert_timestamp_year(pot->getperiodStartYear()) ) );
		if (pot->haveperiodStartDate())
			p->startDate( std::auto_ptr<xml_schema::date>( convert_timestamp_date(pot->getperiodStartDate()) ) );
		if (pot->haveperiodStartTime())
			p->startTime( std::auto_ptr<xml_schema::time>( convert_timestamp_time(pot->getperiodStartTime()) ) );
		if (pot->haveperiodEndYear())
			p->endYear( std::auto_ptr<xml_schema::gyear>( convert_timestamp_year(pot->getperiodEndYear()) ) );
		if (pot->haveperiodEndDate())
			p->endDate( std::auto_ptr<xml_schema::date>( convert_timestamp_date(pot->getperiodEndDate()) ) );
		if (pot->haveperiodEndTime())
			p->endTime( std::auto_ptr<xml_schema::time>( convert_timestamp_time(pot->getperiodEndTime()) ) );

		RMAP_TYPE_GROUP(pot->getperiodKindGroup(), dest, temporal::typeDefinition_type, temporal::typeLabel_type, temporal::typeLink_type)		
	}
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

void mapSpatial(ebucoreSpatial *source, spatial& dest) {
	std::vector<ebucoreLocation*> locs = source->getlocation();
	for (std::vector<ebucoreLocation*>::iterator it = locs.begin(); it != locs.end(); it++) {
		std::auto_ptr<location> p( new location() );
		ebucoreLocation* loc = *it;
		
		if (loc->havelocationId())
			p->locationId() = loc->getlocationId();
		if (loc->havelocationName())
			p->name() = loc->getlocationName();
		if (loc->havelocationCode())
			p->code() = loc->getlocationCode();
		RMAP_TYPE_GROUP(loc->getlocationKindGroup(), (*p), location::typeDefinition_type, location::typeLabel_type, location::typeLink_type)

		dest.location().push_back(p);
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
	SIMPLE_MAP_OPTIONAL_TO_NEW_VECTOR_AND_ASSIGN(source, temporal, ebucoreTemporal, mapTemporal, dest, settemporal)
	SIMPLE_MAP_OPTIONAL_TO_NEW_VECTOR_AND_ASSIGN(source, spatial, ebucoreSpatial, mapSpatial, dest, setspatial)

}

void mapMetadataCoverage(ebucoreCoverage *source, coverageType& dest) {
	if (source->havespatial() && source->getspatial().size() > 0) {
		std::auto_ptr<spatial> lp( new spatial() );
		ebucoreSpatial *s = source->getspatial()[0];
		mapSpatial(s, *lp);
		dest.spatial(lp);
	}
	if (source->havetemporal() && source->gettemporal().size() > 0) {
		std::auto_ptr<temporal> tp( new temporal() );
		ebucoreTemporal *s = source->gettemporal()[0];
		mapTemporal(s, *tp);
		dest.temporal(tp);
	}
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
	if (source.coverage().present()) {
		ebucoreCoverage *obj = newAndModifyObject<ebucoreCoverage>(dest->getHeaderMetadata(), mod);
		mapMetadataCoverage(source.coverage().get(), obj);
		std::vector<ebucoreCoverage*> coverage;
		coverage.push_back(obj);
		dest->setrightsCoverage(coverage);
	}
	// [TODO] KLV rightsholder is a vector while XSD rightsholder is a single optional element
	if (source.rightsHolder().present()) {
		ebucoreEntity *obj = newAndModifyObject<ebucoreEntity>(dest->getHeaderMetadata(), mod);
		mapEntity(source.rightsHolder().get(), obj);
		std::vector<ebucoreEntity*> holder;
		holder.push_back(obj);
		dest->setrightsHolderEntity(holder);
	}
	NEW_VECTOR_AND_ASSIGN(source, contactDetails, ebucoreContact, rightsType::contactDetails_sequence::iterator, mapContact, dest, setrightsContacts)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setrightsKindGroup)
}

void mapRights(ebucoreRights *source, rightsType& dest) {
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

	// [TODO] KLV RightsId is a string, XSD rights id is an identitytype, not clear how te map...
	// [TODO] KLV rightsAttributedID is nowhere to be found in EBU Core?
	
	if (source->haverightsValue())
		dest.rights() = source->getrightsValue();
	if (source->haverightsLanguage())
		dest.rights().get().lang() = source->getrightsLanguage();
	if (source->haverightsClearanceFlag())
		dest.rightsClearanceFlag( source->getrightsClearanceFlag() );
	if (source->haverightsFormatIDRef())
		dest.formatIDRefs( std::auto_ptr<rightsType::formatIDRefs_type>( convert_idrefs(source->getrightsFormatIDRef())));
	if (source->haveexploitationIssues())
		dest.exploitationIssues( source->getexploitationIssues() );
	if (source->haverightsLink())
		dest.rightsLink( source->getrightsLink());

	if (source->haverightsCoverage()) {
		std::vector<ebucoreCoverage*> cover = source->getrightsCoverage();
		if (cover.size() > 0) {
			ebucoreCoverage *coverage = cover[0];
			std::auto_ptr<coverageType> p( new coverageType() );
			mapMetadataCoverage(coverage, *p); 
			dest.coverage(p);
		}
	}

	if (source->haverightsHolderEntity()) {
		std::vector<ebucoreEntity*> ents = source->getrightsHolderEntity();
		if (ents.size() > 0) {
			ebucoreEntity *ent = ents[0];
			std::auto_ptr<entityType> p( new entityType() );
			mapEntity(ent, *p);
			dest.rightsHolder(p);
		}
	}

	if (source->haverightsContacts()) {
		rightsType::contactDetails_sequence conts;
		std::vector<ebucoreContact*> source_conts = source->getrightsContacts();
		for (std::vector<ebucoreContact*>::iterator it = source_conts.begin(); it != source_conts.end(); it++) {
			std::auto_ptr<contactDetailsType> p( new contactDetailsType() );
			mapContact(*it, *p);
			conts.push_back(p);
		}
		dest.contactDetails(conts);
	}

	RMAP_TYPE_GROUP(source->getrightsKindGroup() , dest, rightsType::typeDefinition_type, rightsType::typeLabel_type, rightsType::typeLink_type)
}

bool nodeOrdering(xsd::cxx::tree::type *a, xsd::cxx::tree::type *b) 
{
	return (a->_node()->compareDocumentPosition(b->_node()) == 2 /* DOCUMENT_POSITION_PRECEDING */);	// else, return larger...
}

void mapPublicationHistory(publicationHistoryType& source, std::vector<ebucorePublicationHistoryEvent*>& dest, mxfpp::HeaderMetadata *header_metadata, ObjectModifier* mod = NULL) {
	/*
		<sequence>
			<element name="firstPublicationDate" type="date" minOccurs="0">
			</element>
			<element name="firstPublicationTime" type="time" minOccurs="0">
			</element>
			<element name="firstPublicationChannel" minOccurs="0">
				<complexType>
					<simpleContent>
						<extension base="string">
							<attribute name="formatIdRef" type="IDREF"/>
						</extension>
					</simpleContent>
				</complexType>
			</element>
			<sequence minOccurs="0" maxOccurs="unbounded">
				<element name="repeatDate" type="date" minOccurs="0">
				</element>
				<element name="repeatTime" type="time" minOccurs="0">
				</element>
				<element name="repeatChannel" minOccurs="0">
					<complexType>
						<simpleContent>
							<extension base="string">
								<attribute name="formatIdRef" type="IDREF"/>
							</extension>
						</simpleContent>
					</complexType>
				</element>
			</sequence>
	*/
	// split the publicationhistory	in a single first publication event and then mulitple other repeats

	if (source.firstPublicationDate().present() || source.firstPublicationTime().present() || source.firstPublicationChannel().present()) {
		// have a first publication event
		ebucorePublicationHistoryEvent *obj = newAndModifyObject<ebucorePublicationHistoryEvent>(header_metadata, mod);
		SIMPLE_MAP_OPTIONAL_CONVERT(source, firstPublicationDate, obj, setpublicationDate, convert_timestamp)
		SIMPLE_MAP_OPTIONAL_CONVERT(source, firstPublicationTime, obj, setpublicationTime, convert_timestamp)
		SIMPLE_MAP_OPTIONAL(source, firstPublicationChannel, obj, setpublicationChannel)
		obj->setfirstPublicationFlag(true);
		if (source.firstPublicationChannel().present() && source.firstPublicationChannel().get().formatIdRef().present()) {
			obj->setpublicationFormatIDRef(source.firstPublicationChannel().get().formatIdRef().get());
		}
		dest.push_back(obj);
	}

#define DATE	0
#define TIME	1
#define CHANNEL	2

	// try and recreate the original order of publication repeat elements
	std::vector< xsd::cxx::tree::type *> elements;
	for (publicationHistoryType::repeatDate_iterator it = source.repeatDate().begin(); it != source.repeatDate().end(); it++) {
		elements.push_back(&*it);
	}
	for (publicationHistoryType::repeatTime_iterator it = source.repeatTime().begin(); it != source.repeatTime().end(); it++) {
		elements.push_back(&*it);
	}
	for (publicationHistoryType::repeatChannel_iterator it = source.repeatChannel().begin(); it != source.repeatChannel().end(); it++) {
		elements.push_back(&*it);
	}
	std::sort(elements.begin(), elements.end(), &nodeOrdering);

	ebucorePublicationHistoryEvent *obj = NULL;
	if (elements.size() > 0)
		obj = new ebucorePublicationHistoryEvent(header_metadata);

	int lastElementType = -1;
	for (std::vector< xsd::cxx::tree::type *>::iterator it = elements.begin(); it != elements.end(); it++) {
		int elementType;
		// loop through the sorted vector and make publicationhistory as needed
		publicationHistoryType::repeatDate_type* date = NULL;
		publicationHistoryType::repeatTime_type* time = NULL;
		publicationHistoryType::repeatChannel_type* channel = NULL;
		date = dynamic_cast<publicationHistoryType::repeatDate_type*>(*it);
		if (date) { // it is a repeatDate
			elementType = DATE;
		} else {
			time = dynamic_cast<publicationHistoryType::repeatTime_type*>(*it);
			if (time) {
				elementType = TIME;
			} else {
				channel = dynamic_cast<publicationHistoryType::repeatChannel_type*>(*it);
				elementType = CHANNEL;
			}
		}
		if (elementType <= lastElementType) {
			// introduce a new element
			dest.push_back(obj);
			obj = newAndModifyObject<ebucorePublicationHistoryEvent>(header_metadata, mod);
		}
		if (date) {
			obj->setpublicationDate(convert_timestamp(*date));
		} else if (time) {
			obj->setpublicationTime(convert_timestamp(*time));
		} else {
			obj->setpublicationChannel(*channel);
			if (channel->formatIdRef().present()) {
				obj->setpublicationFormatIDRef(channel->formatIdRef().get());
			}
		}
	}
	// push the last object into the destination list (if the object is valid)
	if (obj)
		dest.push_back(obj);
}

void mapPublicationHistory(std::vector<ebucorePublicationHistoryEvent*>& source, publicationHistoryType& dest) {
	for (std::vector<ebucorePublicationHistoryEvent*>::iterator it = source.begin(); it != source.end(); it++) {
		ebucorePublicationHistoryEvent *event = *it;
		if (event->getfirstPublicationFlag()) {
			if (event->havepublicationDate()) {
				dest.firstPublicationDate( std::auto_ptr<publicationHistoryType::firstPublicationDate_type>( convert_timestamp_date(event->getpublicationDate()) ));
			}
			if (event->havepublicationTime()) {
				dest.firstPublicationTime( std::auto_ptr<publicationHistoryType::firstPublicationTime_type>( convert_timestamp_time(event->getpublicationTime()) ));
			}
			if (event->havepublicationChannel()) {
				dest.firstPublicationChannel() = event->getpublicationChannel();
				if (event->havepublicationFormatIDRef())
					dest.firstPublicationChannel().get().formatIdRef() = event->getpublicationFormatIDRef();
			}
		} else {
			if (event->havepublicationDate()) {
				dest.repeatDate().push_back( std::auto_ptr<publicationHistoryType::repeatDate_type>( convert_timestamp_date(event->getpublicationDate())) );
			}
			if (event->havepublicationTime()) {
				dest.repeatTime().push_back( std::auto_ptr<publicationHistoryType::repeatTime_type>( convert_timestamp_time(event->getpublicationTime())) );
			}
			if (event->havepublicationChannel()) {
				std::auto_ptr<repeatChannel> p (new repeatChannel());
				(*p) = event->getpublicationChannel();
				if (event->havepublicationFormatIDRef())
					p->formatIdRef() = event->getpublicationFormatIDRef();
				dest.repeatChannel().push_back(p);
			}
		}
	}
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

void mapCustomRelation(ebucoreCustomRelation *source, relationType& dest) {
	if (source->haverelationByName())
		dest.relation() = source->getrelationByName();
	if (source->haverelationLink())
		dest.relationLink() = source->getrelationLink();
	if (source->haverunningOrderNumber())
		dest.runningOrderNumber() = source->getrunningOrderNumber();
	if (source->havecustomRelationTypeGroup()) { // make this field required just like other typegroups??
		RMAP_TYPE_GROUP(source->getcustomRelationTypeGroup(), dest, relationType::typeDefinition_type, relationType::typeLabel_type, relationType::typeLink_type)
	}
}

void mapCoreMetadata(coreMetadataType& source, ebucoreCoreMetadata *dest, ObjectModifier* mod = NULL) {

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

	if (source.version().present()) {
		ebucoreVersion *obj = newAndModifyObject<ebucoreVersion>(dest->getHeaderMetadata(), mod);
		mapVersion(source.version().get(), obj);
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

void mapCoreMetadata(ebucoreCoreMetadata *source, coreMetadataType& dest) {

	coreMetadataType::title_sequence titles;
	std::vector<ebucoreTitle*> source_titles = source->gettitle();
	for (std::vector<ebucoreTitle*>::iterator it = source_titles.begin(); it != source_titles.end(); it++) {
		std::auto_ptr<dc::elementType> dcp( new dc::elementType() );
		std::auto_ptr<titleType> tp( new titleType(dcp) );
		mapTitle(*it, *tp);
		titles.push_back(tp);
	}
	dest.title(titles);

	coreMetadataType::alternativeTitle_sequence alttitles;
	std::vector<ebucoreAlternativeTitle*> source_alt_titles = source->getalternativeTitle();
	for (std::vector<ebucoreAlternativeTitle*>::iterator it = source_alt_titles.begin(); it != source_alt_titles.end(); it++) {
		std::auto_ptr<dc::elementType> dcp( new dc::elementType() );
		std::auto_ptr<alternativeTitleType> tp( new alternativeTitleType(dcp) );
		mapAlternativeTitle(*it, *tp);
		alttitles.push_back(tp);
	}
	dest.alternativeTitle(alttitles);

	coreMetadataType::description_sequence descs;
	std::vector<ebucoreDescription*> source_descs = source->getdescription();
	for (std::vector<ebucoreDescription*>::iterator it = source_descs.begin(); it != source_descs.end(); it++) {
		std::auto_ptr<dc::elementType> dcp( new dc::elementType() );
		std::auto_ptr<descriptionType> tp( new descriptionType(dcp) );
		mapDescription(*it, *tp);
		descs.push_back(tp);
	}
	dest.description(descs);

	coreMetadataType::publisher_sequence publ;
	std::vector<ebucoreEntity*> source_publ = source->getpublisher();
	for (std::vector<ebucoreEntity*>::iterator it = source_publ.begin(); it != source_publ.end(); it++) {
		std::auto_ptr<entityType> p( new entityType() );
		mapEntity(*it, *p);
		publ.push_back(p);
	}
	dest.publisher(publ);

	coreMetadataType::identifier_sequence idents;
	std::vector<ebucoreIdentifier*> source_ident = source->getidentifier();
	for (std::vector<ebucoreIdentifier*>::iterator it = source_ident.begin(); it != source_ident.end(); it++) {
		std::auto_ptr<dc::elementType> dcp( new dc::elementType() );
		std::auto_ptr<identifierType> p( new identifierType( dcp ) );
		mapIdentifier(*it, *p);
		idents.push_back(p);
	}
	dest.identifier(idents);

	coreMetadataType::subject_sequence subjs;
	std::vector<ebucoreSubject*> source_subj = source->getsubject();
	for (std::vector<ebucoreSubject*>::iterator it = source_subj.begin(); it != source_subj.end(); it++) {
		std::auto_ptr<dc::elementType> dcp( new dc::elementType() );
		std::auto_ptr<subjectType> p( new subjectType(dcp) );
		mapSubject(*it, *p);
		subjs.push_back(p);
	}
	dest.subject(subjs);

	coreMetadataType::type_sequence types;
	std::vector<ebucoreType*> source_types = source->gettype();
	for (std::vector<ebucoreType*>::iterator it = source_types.begin(); it != source_types.end(); it++) {
		std::auto_ptr<typeType> p( new typeType() );
		mapType(*it, *p);
		types.push_back(p);
	}
	dest.type(types);

	std::vector<ebucorePublicationHistoryEvent*> source_events = source->getpublicationHistoryEvent();
	if (source_events.size() > 0) {
		std::auto_ptr<publicationHistoryType> p( new publicationHistoryType() );
		mapPublicationHistory(source_events, *p);
		dest.publicationHistory(p);
	}

	coreMetadataType::date_sequence dates;
	std::vector<ebucoreDate*> source_dates = source->getdate();
	for (std::vector<ebucoreDate*>::iterator it = source_dates.begin(); it != source_dates.end(); it++) {
		std::auto_ptr<dateType> p( new dateType() );
		mapDate(*it, *p);
		dates.push_back(p);
	}
	dest.date(dates);

	coreMetadataType::language_sequence langs;
	std::vector<ebucoreLanguage*> source_langs = source->getlanguage();
	for (std::vector<ebucoreLanguage*>::iterator it = source_langs.begin(); it != source_langs.end(); it++) {
		std::auto_ptr<languageType> p( new languageType() );
		mapLanguage(*it, *p);
		langs.push_back(p);
	}
	dest.language(langs);

	coreMetadataType::coverage_sequence covers;
	std::vector<ebucoreCoverage*> source_covers = source->getcoverage();
	for (std::vector<ebucoreCoverage*>::iterator it = source_covers.begin(); it != source_covers.end(); it++) {
		std::auto_ptr<coverageType> p( new coverageType() );
		mapMetadataCoverage(*it, *p);
		covers.push_back(p);
	}
	dest.coverage(covers);

	if (source->haveversion()) {
		std::auto_ptr<coreMetadataType::version_type> p(new coreMetadataType::version_type( source->getversion()->getversionValue() ));
	}

	coreMetadataType::rights_sequence rights;
	std::vector<ebucoreRights*> source_rights = source->getrights();
	for (std::vector<ebucoreRights*>::iterator it = source_rights.begin(); it != source_rights.end(); it++) {
		std::auto_ptr<rightsType> p( new rightsType() );
		mapRights(*it, *p);
		rights.push_back(p);
	}
	dest.rights(rights);

	coreMetadataType::relation_sequence rels;
	std::vector<ebucoreCustomRelation*> source_rels = source->getcustomRelation();
	for (std::vector<ebucoreCustomRelation*>::iterator it = source_rels.begin(); it != source_rels.end(); it++) {
		std::auto_ptr<relationType> p( new relationType() );
		mapCustomRelation(*it, *p);
		rels.push_back(p);
	}
	dest.relation(rels);
}

DMFramework* Process(std::string location, HeaderMetadata *destination) {
	std::ifstream input(location);
	std::auto_ptr<ebuCoreMainType> ebuCoreMainElementPtr (ebuCoreMain (input, xml_schema::flags::dont_validate | xml_schema::flags::keep_dom));

	//std::wstring version(ebuCoreMainElementPtr->version()._node()->getTextContent());
	//std::wcout << version << std::endl;

	// Generate a new Generation UID if necessary, and provide to each mapping function

	ebucoreMainFramework *framework = new ebucoreMainFramework(destination);
	framework->setdocumentId(location);	// use the file location as document id

	ebucoreCoreMetadata *core = new ebucoreCoreMetadata(destination);
	mapCoreMetadata(ebuCoreMainElementPtr->coreMetadata(), core);

	ebucoreMetadataSchemeInformation *info = new ebucoreMetadataSchemeInformation(destination);
	mapMetadataSchemeInformation(*ebuCoreMainElementPtr, info);

	framework->setcoreMetadata(core);
	framework->setmetadataSchemeInformation(info);

	std::cout << framework->getdocumentId();

	return framework;
}

void RegisterMetadataExtensionsforEBUCore(mxfpp::DataModel *data_model)
{
	EBUCore::RegisterExtensions(data_model);	
}

DMFramework* Process(std::string location) {

	DataModel *mDataModel = new DataModel();
	RegisterMetadataExtensionsforEBUCore(mDataModel);

	HeaderMetadata *md = new HeaderMetadata(mDataModel);

	return Process(location, md);
}

void InsertFramework(HeaderMetadata *header_metadata, uint32_t track_id, std::string track_name, DMFramework *framework)
{
    BMX_ASSERT(header_metadata);

    MaterialPackage *material_package = header_metadata->getPreface()->findMaterialPackage();
    BMX_ASSERT(material_package);

    // Preface - ContentStorage - Package - DM Track
    StaticTrack *dm_track = new StaticTrack(header_metadata);
    material_package->appendTracks(dm_track);
    dm_track->setTrackName(track_name);
    dm_track->setTrackID(track_id);
    dm_track->setTrackNumber(0);

    // Preface - ContentStorage - Package - DM Track - Sequence
    Sequence *sequence = new Sequence(header_metadata);
    dm_track->setSequence(sequence);
    sequence->setDataDefinition(MXF_DDEF_L(DescriptiveMetadata));

    // Preface - ContentStorage - Package - DM Track - Sequence - DMSegment
    DMSegment *dm_segment = new DMSegment(header_metadata);
    sequence->appendStructuralComponents(dm_segment);
    dm_segment->setDataDefinition(MXF_DDEF_L(DescriptiveMetadata));

    // move the framework set after the dm degment set
    mxf_remove_set(header_metadata->getCHeaderMetadata(), framework->getCMetadataSet());
    BMX_CHECK(mxf_add_set(header_metadata->getCHeaderMetadata(), framework->getCMetadataSet()));

    // Preface - ContentStorage - Package - DM Track - Sequence - DMSegment - DMFramework
    dm_segment->setDMFramework(framework);
}

void AppendDMSLabel(HeaderMetadata *header_metadata, mxfUL scheme_label)
{
    BMX_ASSERT(header_metadata);
	Preface *preface = header_metadata->getPreface();

    std::vector<mxfUL> dm_schemes = preface->getDMSchemes();
    size_t i;
    for (i = 0; i < dm_schemes.size(); i++) {
        if (mxf_equals_ul(&dm_schemes[i], &scheme_label))
            break;
    }
	try {
		if (i >= dm_schemes.size())
			preface->appendDMSchemes(scheme_label);
	} catch (const MXFException &ex) {
		// oops, cannot append, maybe something wrong with the array as read from the file
		// try and create a new DMSchemes array if empty now
		if (dm_schemes.size() == 0) {
			preface->setDMSchemes(std::vector<mxfUL>());
			preface->appendDMSchemes(scheme_label);
		}
	}
}

void RegisterFrameworkObjectFactoriesforEBUCore(mxfpp::HeaderMetadata *metadata) {
	EBUCore::RegisterFrameworkObjectFactory(metadata);
}

void InsertEBUCoreFramework(HeaderMetadata *header_metadata, DMFramework *framework) {

	BMX_ASSERT(header_metadata != NULL);

	// Append the EBU Core DMS label to the Preface
	AppendDMSLabel(header_metadata, MXF_DM_L(EBUCoreDescriptiveScheme));
	// Insert the framework
    InsertFramework(header_metadata, 10001, "EBU_Core", framework);
}

static std::vector<DMFramework*> ebu_get_static_frameworks(MaterialPackage *mp)
{
    std::vector<DMFramework*> frameworks;

    // expect to find Static DM Track -> Sequence -> DM Segment -> DM Framework

    std::vector<GenericTrack*> tracks = mp->getTracks();
    size_t i;
    for (i = 0; i < tracks.size(); i++) {
        StaticTrack *st = dynamic_cast<StaticTrack*>(tracks[i]);
        if (!st)
            continue;

        StructuralComponent *sc = st->getSequence();
        if (!sc || sc->getDataDefinition() != MXF_DDEF_L(DescriptiveMetadata))
            continue;

        Sequence *seq = dynamic_cast<Sequence*>(sc);
        DMSegment *seg = dynamic_cast<DMSegment*>(sc);
        if (!seq && !seg)
            continue;

        if (seq) {
            std::vector<StructuralComponent*> scs = seq->getStructuralComponents();
            if (scs.size() != 1)
                continue;

            seg = dynamic_cast<DMSegment*>(scs[0]);
            if (!seg)
                continue;
        }

        if (!seg->haveDMFramework())
            continue;

        DMFramework *framework = seg->getDMFrameworkLight();
        if (framework)
            frameworks.push_back(framework);
    }

    return frameworks;
}

void ReadAndSerializeEBUCore(HeaderMetadata *metadata, const char* outputfilename) {

	MaterialPackage *mp = metadata->getPreface()->findMaterialPackage();
	if (!mp) {
        return;
    }

	ebucoreMainFramework *ebucore = NULL;
	std::vector<DMFramework*> static_frameworks = ebu_get_static_frameworks(mp);
	size_t i;
    for (i = 0; i < static_frameworks.size(); i++) {
		ebucoreMainFramework *p = dynamic_cast<ebucoreMainFramework*>(static_frameworks[i]);
        if (p) {
			ebucore = p;
			break;
		}
    }

	if (ebucore) {

		titleType::title_type dc_title("Berlin Wall 50th");
		titleType title(dc_title);

		ebuCoreMainType::coreMetadata_type main;
		//main.title().push_back(title);

		mapCoreMetadata(ebucore->getcoreMetadata(), main);

		// map the EBU Core KLV framework to the XSD-derived counterpart
		ebuCoreMainType ebuCoreMainElement(main);
		//ebuCoreMainElement.schema(ebuCoreMainElement.schema_default_value());
		//ebuCoreMainElement.version(ebuCoreMainElement.version_default_value());
		//ebuCoreMainElement.version("1.3");

		std::auto_ptr<entityType> p( new entityType() );
		ebucoreMetadataSchemeInformation *info = ebucore->getmetadataSchemeInformation();
		mapEntity(info->getebucoreMetadataProvider(), *(p.get()));
		ebuCoreMainElement.metadataProvider(p);

		xml_schema::namespace_infomap map;
		map[""].name = "urn:ebu:metadata-schema:ebuCore_2011";
		map["dc"].name = "http://purl.org/dc/elements/1.1/";

		// open a file output stream
		std::ofstream out(outputfilename);
		ebuCoreMain (out, ebuCoreMainElement, map);
		out.close();
	}

}

