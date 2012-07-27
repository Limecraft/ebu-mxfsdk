/*#include <iostream>
#include <fstream>
#include <memory>

#include <bmx/BMXException.h>
#include <bmx/Logging.h>*/

#include "EBUCoreMapping.h"

#include <xercesc/util/TransService.hpp>

using namespace ebuCore_2011;
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
	// [FIX?] Updated to entityType
	contactDetailsType::relatedContacts_sequence rels;
	std::vector<ebucoreEntity*> source_rels = source->getcontactRelatedContacts();
	for (std::vector<ebucoreEntity*>::iterator it = source_rels.begin(); it != source_rels.end(); it++) {
		std::auto_ptr<entityType> p( new entityType() );
		mapEntity(*it, *(p.get()));
		rels.push_back(p);
	}
	dest.relatedContacts(rels);
	
	// [TODO] We skip contactId for now, KLV mapping refers to an UID, while the XSD refers to anyURI type

}

void mapOrganisation(ebucoreOrganisation *source, organisationDetailsType& dest) {

	dest.organisationName() = source->getorganisationName();
	if (source->haveorganisationDepartment())
		dest.organisationDepartment() = source->getorganisationDepartment();

	organisationDetailsType::contacts_sequence seq_conts;
	std::vector<ebucoreEntity*> source_conts = source->getorganisationRelatedContacts();
	for (std::vector<ebucoreEntity*>::iterator it = source_conts.begin(); it != source_conts.end(); it++) {
		std::auto_ptr<entityType> p( new entityType() );
		mapEntity(*it, *(p.get()));
		seq_conts.push_back(p);
	}
	dest.contacts(seq_conts);

	organisationDetailsType::details_sequence seq;
	std::vector<ebucoreContactDetails*> source_vec = source->getorganisationDetails();
	for (std::vector<ebucoreContactDetails*>::iterator it = source_vec.begin(); it != source_vec.end(); it++) {
		std::auto_ptr<detailsType> p( new detailsType() );
		mapDetails(*it, *(p.get()));
		seq.push_back(p);
	}
	dest.details(seq);
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
	// [FIX?] Updated cardinality
	if (source->haveentityContact()) {
		entityType::contactDetails_sequence seq;
		std::vector<ebucoreContact*> source_conts = source->getentityContact();
		for (std::vector<ebucoreContact*>::iterator it = source_conts.begin(); it != source_conts.end(); it++) {
			std::auto_ptr<entityType::contactDetails_type> p( new entityType::contactDetails_type() );
			mapContact((*it), *(p.get()));
			seq.push_back(p);
		}
		dest.contactDetails(seq);
	}

	if (source->haveentityOrganisation()) {
		std::auto_ptr<entityType::organisationDetails_type> p( new entityType::organisationDetails_type("") );
		mapOrganisation(source->getentityOrganisation(), *(p.get()) );
		dest.organisationDetails(p);
	}

	// [TODO] The KLV mapping lists a single role, while the XSD specifies a sequence
	// [FIX?] Updated cardinality
	if (source->haveentityRole()) {
		entityType::role_sequence seq;
		std::vector<ebucoreRole*> source_roles = source->getentityRole();
		for (std::vector<ebucoreRole*>::iterator it = source_roles.begin(); it != source_roles.end(); it++) {
			ebucoreTypeGroup *tg = (*it)->getroleType();
			std::auto_ptr<entityType::role_type> p( new entityType::role_type() );
			RMAP_TYPE_GROUP(tg, (*(p.get())), role::typeDefinition_type, role::typeLabel_type, role::typeLink_type)
			seq.push_back(p);			
		}
		dest.role(seq);
	}

	// [TODO] We skip entityId for now, KLV mapping refers to an UID, while the XSD refers to anyURI type
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

void mapTitle(ebucoreTitle *source, titleType& dest) {
	dest.title() = source->gettitleValue();
	dest.title().lang() = source->gettitleLanguage();
	if (source->havetitleAttributionDate()) {
		std::auto_ptr<ebuCoreMainType::dateLastModified_type> dp( convert_timestamp_date(source->gettitleAttributionDate()));
		dest.attributiondate().set(dp);
	}
}

void mapAlternativeTitle(ebucoreAlternativeTitle *source, alternativeTitleType& dest) {
	dest.title() = source->getalternativeTitleValue();
	dest.title().lang() = source->getalternativeTitleLanguage();

	ebucoreTypeGroup* tg = source->getalternativeTitleTypeGroup();
	ebucoreStatusGroup* sg = source->getalternativeTitleStatusGroup();
	RMAP_TYPE_GROUP(tg, dest, alternativeTitleType::typeDefinition_type, alternativeTitleType::typeLabel_type, alternativeTitleType::typeLink_type)
	RMAP_STATUS_GROUP(sg, dest, alternativeTitleType::statusDefinition_type, alternativeTitleType::statusLabel_type, alternativeTitleType::statusLink_type)
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

void mapDescription(ebucoreDescription *source, descriptionType& dest) {
	dest.description() = source->getdescriptionValue();
	dest.description().lang() = source->getdescriptionLanguage();
	RMAP_TYPE_GROUP(source->getdescriptionTypeGroup(), dest, descriptionType::typeDefinition_type, descriptionType::typeLabel_type, descriptionType::typeLink_type)
}

void mapSubject(ebucoreSubject *source, subjectType& dest) {
	// [TODO] KLV Subject defines batch multiple attributors, XSD (0..1), used a single one in dictionary
	// [FIX?] Updated cardinality

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

void mapVersion(ebucoreVersion *source, coreMetadataType::version_type& dest) {
	dest = source->getversionValue();
}

void mapLanguage(ebucoreLanguage *source, languageType& dest) {
	dest.language() = source->getlanguageName();
	dest.language().get().lang() = source->getlanguageCode();

	RMAP_TYPE_GROUP( source->getlanguagePurposeSet()->getlanguagePurposeTypeGroup(), 
		dest, languageType::typeDefinition_type, languageType::typeLabel_type, languageType::typeLink_type)
}

void mapType(ebucoreType *source, typeType& dest) {
	typeType::objectType_sequence obtyps;
	std::vector<ebucoreObjectType*> source_obtyps = source->getobjectType();
	for (std::vector<ebucoreObjectType*>::iterator it = source_obtyps.begin(); it != source_obtyps.end(); it++) {
		std::auto_ptr<objectType> p( new objectType() );
		RMAP_TYPE_GROUP((*it)->getobjectTypeGroup(), (*p), objectType::typeDefinition_type, objectType::typeLabel_type, objectType::typeLink_type)
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

void mapTemporal(ebucoreTemporal *source, temporal& dest) {
	// if there is more that a single period of time, we only use the first one
	// [FIX?] Updated cardinality, source has only max 1 periodoftime
	if (source->haveperiodOfTime()) {
		ebucorePeriodOfTime *pot = source->getperiodOfTime();
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

void mapMetadataCoverage(ebucoreCoverage *source, coverageType& dest) {
	// [Fix?] Updated cardinality
	if (source->havespatial()) {
		std::auto_ptr<spatial> lp( new spatial() );
		mapSpatial(source->getspatial(), *lp);
		dest.spatial(lp);
	}
	// [Fix?] Updated cardinality
	if (source->havetemporal()) {
		std::auto_ptr<temporal> tp( new temporal() );
		mapTemporal(source->gettemporal(), *tp);
		dest.temporal(tp);
	}
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

	// [FIX?] Updated cardinality
	if (source->haverightsCoverage()) {
		std::auto_ptr<coverageType> p( new coverageType() );
		mapMetadataCoverage(source->getrightsCoverage(), *p); 
		dest.coverage(p);
	}

	// [FIX?] Updated cardinality
	if (source->haverightsHolderEntity()) {
		std::auto_ptr<entityType> p( new entityType() );
		mapEntity(source->getrightsHolderEntity(), *p);
		dest.rightsHolder(p);
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

}