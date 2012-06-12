
#include <iostream>
#include <fstream>

#include "EBUcoreProcessor.h"

#include "EBU_CORE_20110915.hxx"

#include <metadata/EBUCoreDMS++.h>

using namespace ebuCore_2011;
using namespace mxfpp;

void Process() {
	std::ifstream input("C:\\code\\EBU-SDK\\Documentation\\EBU-Core\\examples\\ITM504483_EBUcore.XML");
	std::auto_ptr<ebuCoreMainType> ebuCoreMainElementPtr (ebuCoreMain (input, xml_schema::flags::dont_validate | xml_schema::flags::keep_dom));

	DataModel *mDataModel = new DataModel();
	EBUCore::RegisterExtensions(mDataModel);

	HeaderMetadata *md = new HeaderMetadata(mDataModel);

	std::wstring version(ebuCoreMainElementPtr->version()._node()->getTextContent());

	ebucoreMainFramework *framework = new ebucoreMainFramework(md);
	framework->setdocumentId("testtesttest");

	std::cout << framework->getdocumentId();

	//ebuCoreMainType::metadataProvider_type 
	entityType provider = ebuCoreMainElementPtr->metadataProvider().get();
}

#define	SIMPLE_MAP(source, sourceProperty, dest, destProperty)	\
	dest->destProperty(source.sourceProperty().get());
#define	SIMPLE_MAP_NO_GET(source, sourceProperty, dest, destProperty)	\
	dest->destProperty(source.sourceProperty());

#define	SIMPLE_MAP_OPTIONAL(source, sourceProperty, dest, destProperty)	\
	if (source.sourceProperty().present())	\
		dest->destProperty(source.sourceProperty().get());

#define NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, sourceProperty, destType, mapMethod, dest, destProperty) \
	if (source.sourceProperty().present()) {	\
		destType *obj = new destType(dest->getHeaderMetadata());	\
		mapMethod(source.sourceProperty().get(), obj);	\
		dest->destProperty(obj);	\
	}

#define NEW_VECTOR_AND_ASSIGN(source, sourceProperty, destType, iteratorType, mapMethod, dest, destProperty)	\
	std::vector<destType*> vec_dest_destProperty;	\
	for (iteratorType it = source.sourceProperty().begin(); it != source.sourceProperty().end(); it++) {	\
		destType *obj = new destType(dest->getHeaderMetadata());	\
		mapMethod(*it, obj);	\
		vec_dest_destProperty.push_back(obj);	\
	}	\
	dest->destProperty(vec_dest_destProperty);

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

void mapRole(role& source, ebucoreRole *dest) {
	ebucoreTypeGroup *obj = new ebucoreTypeGroup(dest->getHeaderMetadata());
	MAP_TYPE_GROUP(source, obj)
	dest->setroleType(obj);
}

void mapAddress(addressType& source, ebucoreAddress *dest) {
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

	// atm, only a single address line is defined in KLV mapping
	if (source.addressLine().size() > 0) {
		dest->setaddressLine(source.addressLine().front());
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

void mapDetails(detailsType& source, ebucoreContactDetails *dest) {
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

	ebucoreTypeGroup *obj = new ebucoreTypeGroup(dest->getHeaderMetadata());
	MAP_TYPE_GROUP(source, obj)
	dest->setdetailsType(obj);
}

void mapContact(contactDetailsType& source, ebucoreContact *dest) {
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

void mapOrganisation(organisationDetailsType& source, ebucoreOrganisation *dest) {
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

void mapEntity(entityType& source, ebucoreEntity *dest) {
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
		ebucoreContact *obj = new ebucoreContact(dest->getHeaderMetadata());
		mapContact(source.contactDetails().front(), obj);
		dest->setentityContact(obj);
	}

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, organisationDetails, ebucoreOrganisation, mapOrganisation, dest, setentityOrganisation)

	// [TODO] The KLV mapping lists a single role, while the XSD specifies a sequence
	if (source.role().size() > 0) {
		ebucoreRole *obj = new ebucoreRole(dest->getHeaderMetadata());
		mapRole(source.role().front(), obj);
		dest->setentityRole(obj);
	}

	// [TODO] We skip entityId for now, KLV mapping refers to an UID, while the XSD refers to anyURI type
}

void mapMetadataSchemeInformation(ebuCoreMainType& source, ebucoreMetadataSchemeInformation *dest) {
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

}
