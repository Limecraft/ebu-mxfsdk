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
#define	SIMPLE_MAP_OPTIONAL_CONVERT(source, sourceProperty, dest, destProperty, convertFunction)	\
	if (source.sourceProperty().present())	\
		dest->destProperty(convertFunction(source.sourceProperty().get()));

#define NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, haveSourceProperty, getSourceProperty, destType, mapMethod, dest, destProperty) \
	if (source->haveSourceProperty()) {	\
		std::auto_ptr<destType> p( new destType() );	\
		mapMethod(source->getSourceProperty(), *p);	\
		dest.destProperty(p);	\
	}
#define NEW_OBJECT_AND_RASSIGN_OPTIONAL_GETPOINTER(source, haveSourceProperty, getSourceProperty, destType, mapMethod, dest, destProperty) \
	if (source->haveSourceProperty()) {	\
		std::auto_ptr<destType> p( new destType() );	\
		mapMethod(source->getSourceProperty(), *(p.get()));	\
		dest.destProperty(p);	\
	}

#define NEW_VECTOR_AND_RASSIGN(source, sourceProperty, destType, destSequenceType, iteratorType, mapMethod, dest, destProperty)	\
	{ destSequenceType vec_##dest##destProperty; \
	for (iteratorType it = source->sourceProperty().begin(); it != source->sourceProperty().end(); it++) { \
		std::auto_ptr<destType> p( new destType() ); \
		mapMethod(*it, *p); \
		vec_##dest##destProperty.push_back(p); \
	} \
	dest.destProperty(vec_##dest##destProperty); }

#define NEW_VECTOR_AND_RASSIGN_WITH_DC(source, sourceProperty, destType, destSequenceType, iteratorType, mapMethod, dest, destProperty)	\
	{ destSequenceType vec_##dest##destProperty; \
	for (iteratorType it = source->sourceProperty().begin(); it != source->sourceProperty().end(); it++) { \
		std::auto_ptr<dc::elementType> dcp( new dc::elementType() ); \
		std::auto_ptr<destType> p( new destType(dcp) ); \
		mapMethod(*it, *p); \
		vec_##dest##destProperty.push_back(p); \
	} \
	dest.destProperty(vec_##dest##destProperty); }

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

	SIMPLE_RMAP_OPTIONAL(source, haveemailAddress, getemailAddress, dest, emailAddress)
	SIMPLE_RMAP_OPTIONAL(source, havewebAddress, getwebAddress, dest, webAddress)

	// map address
	NEW_OBJECT_AND_RASSIGN_OPTIONAL_GETPOINTER(source, haveaddress, getaddress, addressType, mapAddress, dest, address)

	SIMPLE_RMAP_OPTIONAL(source, havetelephoneNumber, gettelephoneNumber, dest, telephoneNumber)
	SIMPLE_RMAP_OPTIONAL(source, havemobileTelephoneNumber, getmobileTelephoneNumber, dest, mobileTelephoneNumber)

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

	SIMPLE_RMAP_OPTIONAL(source, haveotherGivenName, getotherGivenName, dest, username)
	SIMPLE_RMAP_OPTIONAL(source, haveoccupation, getoccupation, dest, occupation)

	// map contactdetails
	NEW_VECTOR_AND_RASSIGN(source, getcontactDetails, detailsType, contactDetailsType::details_sequence, std::vector<ebucoreContactDetails*>::iterator, mapDetails, dest, details)

	if (source->havestageName()) {
		contactDetailsType::stageName_sequence seq;
		seq.push_back( source->getstageName() );
		dest.stageName(seq);
	}

	// [TODO] We skip RelatedContacts for now, KLV mapping refers to Contacts, while the XSD refers to entities
	// [FIX?] Updated to entityType
	NEW_VECTOR_AND_RASSIGN(source, getcontactRelatedContacts, entityType, contactDetailsType::relatedContacts_sequence, std::vector<ebucoreEntity*>::iterator, mapEntity, dest, relatedContacts)
	
	// [TODO] We skip contactId for now, KLV mapping refers to an UID, while the XSD refers to anyURI type

}

void mapOrganisation(ebucoreOrganisation *source, organisationDetailsType& dest) {

	SIMPLE_RMAP(source, getorganisationName, dest, organisationName)
	SIMPLE_RMAP_OPTIONAL(source, haveorganisationDepartment, getorganisationDepartment, dest, organisationDepartment)

	NEW_VECTOR_AND_RASSIGN(source, getorganisationRelatedContacts, entityType, organisationDetailsType::contacts_sequence, std::vector<ebucoreEntity*>::iterator, mapEntity, dest, contacts)
	NEW_VECTOR_AND_RASSIGN(source, getorganisationDetails, detailsType, organisationDetailsType::details_sequence, std::vector<ebucoreContactDetails*>::iterator, mapDetails, dest, details)
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
		NEW_VECTOR_AND_RASSIGN(source, getentityContact, contactDetailsType, entityType::contactDetails_sequence, std::vector<ebucoreContact*>::iterator, mapContact, dest, contactDetails)
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
	SIMPLE_RMAP(source, gettitleValue, dest, title)
	SIMPLE_RMAP(source, gettitleLanguage, dest, title().lang)
	if (source->havetitleAttributionDate()) {
		std::auto_ptr<ebuCoreMainType::dateLastModified_type> dp( convert_timestamp_date(source->gettitleAttributionDate()));
		dest.attributiondate().set(dp);
	}
}

void mapAlternativeTitle(ebucoreAlternativeTitle *source, alternativeTitleType& dest) {
	SIMPLE_RMAP(source, getalternativeTitleValue, dest, title)
	SIMPLE_RMAP(source, getalternativeTitleLanguage, dest, title().lang)

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

	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, haveidentifierAttributorEntity, getidentifierAttributorEntity, entityType, mapEntity, dest, attributor)
}

void mapDescription(ebucoreDescription *source, descriptionType& dest) {
	SIMPLE_RMAP(source, getdescriptionValue, dest, description)
	SIMPLE_RMAP(source, getdescriptionLanguage, dest, description().lang)

	RMAP_TYPE_GROUP(source->getdescriptionTypeGroup(), dest, descriptionType::typeDefinition_type, descriptionType::typeLabel_type, descriptionType::typeLink_type)
}

void mapSubject(ebucoreSubject *source, subjectType& dest) {
	// [TODO] KLV Subject defines batch multiple attributors, XSD (0..1), used a single one in dictionary
	// [FIX?] Updated cardinality

	SIMPLE_RMAP(source, getsubjectValue, dest, subject)
	SIMPLE_RMAP(source, getsubjectLanguage, dest, subject().lang)
	SIMPLE_RMAP_OPTIONAL(source, havesubjectCode, getsubjectCode, dest, subjectCode)
	SIMPLE_RMAP_OPTIONAL(source, havesubjectDefinition, getsubjectDefinition, dest, subjectDefinition)

	RMAP_TYPE_GROUP(source->getsubjectTypeGroup(), dest, subjectType::typeDefinition_type, subjectType::typeLabel_type, subjectType::typeLink_type)

	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havesubjectAttributorEntity, getsubjectAttributorEntity, entityType, mapEntity, dest, attributor)
}

void mapRating(ebucoreRating *source, ratingType& dest) {
	SIMPLE_RMAP(source, getratingValue, dest, ratingValue)
	SIMPLE_RMAP(source, getratingScaleMinValue, dest, ratingScaleMinValue)
	SIMPLE_RMAP(source, getratingScaleMaxValue, dest, ratingScaleMaxValue)

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
	SIMPLE_RMAP(source, getlanguageName, dest, language)
	SIMPLE_RMAP(source, getlanguageCode, dest, language().get().lang)
	
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

		SIMPLE_RMAP_OPTIONAL(pot, haveperiodId, getperiodId, dest, periodId)
		SIMPLE_RMAP_OPTIONAL_POINTER(pot, haveperiodName, getperiodName, p, period)
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
		
		SIMPLE_RMAP_OPTIONAL_POINTER(loc, havelocationId, getlocationId, p, locationId)
		SIMPLE_RMAP_OPTIONAL_POINTER(loc, havelocationName, getlocationName, p, name)
		SIMPLE_RMAP_OPTIONAL_POINTER(loc, havelocationCode, getlocationCode, p, code)
		RMAP_TYPE_GROUP(loc->getlocationKindGroup(), (*p), location::typeDefinition_type, location::typeLabel_type, location::typeLink_type)

		dest.location().push_back(p);
	}
}

void mapMetadataCoverage(ebucoreCoverage *source, coverageType& dest) {
	// [Fix?] Updated cardinality
	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havespatial, getspatial, spatial, mapSpatial, dest, spatial)
	// [Fix?] Updated cardinality
	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, havetemporal, gettemporal, temporal, mapTemporal, dest, temporal)
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
	
	SIMPLE_RMAP_OPTIONAL(source, haverightsValue, getrightsValue, dest, rights)
	SIMPLE_RMAP_OPTIONAL(source, haverightsLanguage, getrightsLanguage, dest, rights().get().lang)
	SIMPLE_RMAP_OPTIONAL(source, haverightsClearanceFlag, getrightsClearanceFlag, dest, rightsClearanceFlag)

	if (source->haverightsFormatIDRef())
		dest.formatIDRefs( std::auto_ptr<rightsType::formatIDRefs_type>( convert_idrefs(source->getrightsFormatIDRef())));

	SIMPLE_RMAP_OPTIONAL(source, haveexploitationIssues, getexploitationIssues, dest, exploitationIssues)
	SIMPLE_RMAP_OPTIONAL(source, haverightsLink, getrightsLink, dest, rightsLink)

	// [FIX?] Updated cardinality
	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, haverightsCoverage, getrightsCoverage, coverageType, mapMetadataCoverage, dest, coverage)

	// [FIX?] Updated cardinality
	NEW_OBJECT_AND_RASSIGN_OPTIONAL(source, haverightsHolderEntity, getrightsHolderEntity, entityType, mapEntity, dest, rightsHolder)

	if (source->haverightsContacts()) {
		NEW_VECTOR_AND_RASSIGN(source, getrightsContacts, contactDetailsType, rightsType::contactDetails_sequence, std::vector<ebucoreContact*>::iterator, mapContact, dest, contactDetails)
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
				SIMPLE_RMAP_OPTIONAL(event, havepublicationChannel, getpublicationChannel, dest, firstPublicationChannel)
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
				SIMPLE_RMAP_OPTIONAL_POINTER(event, havepublicationFormatIDRef, getpublicationFormatIDRef, p, formatIdRef)
				dest.repeatChannel().push_back(p);
			}
		}
	}
}

void mapCustomRelation(ebucoreCustomRelation *source, relationType& dest) {
	SIMPLE_RMAP_OPTIONAL(source, haverelationByName, getrelationByName, dest, relation)
	SIMPLE_RMAP_OPTIONAL(source, haverelationLink, getrelationLink, dest, relationLink)
	SIMPLE_RMAP_OPTIONAL(source, haverunningOrderNumber, getrunningOrderNumber, dest, runningOrderNumber)
	if (source->havecustomRelationTypeGroup()) { // make this field required just like other typegroups??
		RMAP_TYPE_GROUP(source->getcustomRelationTypeGroup(), dest, relationType::typeDefinition_type, relationType::typeLabel_type, relationType::typeLink_type)
	}
}

void mapCoreMetadata(ebucoreCoreMetadata *source, coreMetadataType& dest) {

	NEW_VECTOR_AND_RASSIGN_WITH_DC(source, gettitle, titleType, coreMetadataType::title_sequence, std::vector<ebucoreTitle*>::iterator, mapTitle, dest, title)
	NEW_VECTOR_AND_RASSIGN_WITH_DC(source, getalternativeTitle, alternativeTitleType, coreMetadataType::alternativeTitle_sequence, 
		std::vector<ebucoreAlternativeTitle*>::iterator, mapAlternativeTitle, dest, alternativeTitle)
	NEW_VECTOR_AND_RASSIGN_WITH_DC(source, getdescription, descriptionType, coreMetadataType::description_sequence, std::vector<ebucoreDescription*>::iterator, mapDescription, dest, description)

	NEW_VECTOR_AND_RASSIGN(source, getpublisher, entityType, coreMetadataType::publisher_sequence, std::vector<ebucoreEntity*>::iterator, mapEntity, dest, publisher)

	NEW_VECTOR_AND_RASSIGN_WITH_DC(source, getidentifier, identifierType, coreMetadataType::identifier_sequence, std::vector<ebucoreIdentifier*>::iterator, mapIdentifier, dest, identifier)
	NEW_VECTOR_AND_RASSIGN_WITH_DC(source, getsubject, subjectType, coreMetadataType::subject_sequence, std::vector<ebucoreSubject*>::iterator, mapSubject, dest, subject)
	
	NEW_VECTOR_AND_RASSIGN(source, gettype, typeType, coreMetadataType::type_sequence, std::vector<ebucoreType*>::iterator, mapType, dest, type)

	std::vector<ebucorePublicationHistoryEvent*> source_events = source->getpublicationHistoryEvent();
	if (source_events.size() > 0) {
		std::auto_ptr<publicationHistoryType> p( new publicationHistoryType() );
		mapPublicationHistory(source_events, *p);
		dest.publicationHistory(p);
	}

	NEW_VECTOR_AND_RASSIGN(source, getdate, dateType, coreMetadataType::date_sequence, std::vector<ebucoreDate*>::iterator, mapDate, dest, date)
	NEW_VECTOR_AND_RASSIGN(source, getlanguage, languageType, coreMetadataType::language_sequence, std::vector<ebucoreLanguage*>::iterator, mapLanguage, dest, language)
	NEW_VECTOR_AND_RASSIGN(source, getcoverage, coverageType, coreMetadataType::coverage_sequence, std::vector<ebucoreCoverage*>::iterator, mapMetadataCoverage, dest, coverage)

	if (source->haveversion()) {
		std::auto_ptr<coreMetadataType::version_type> p(new coreMetadataType::version_type( source->getversion()->getversionValue() ));
	}

	NEW_VECTOR_AND_RASSIGN(source, getrights, rightsType, coreMetadataType::rights_sequence, std::vector<ebucoreRights*>::iterator, mapRights, dest, rights)
	NEW_VECTOR_AND_RASSIGN(source, getcustomRelation, relationType, coreMetadataType::relation_sequence, std::vector<ebucoreCustomRelation*>::iterator, mapCustomRelation, dest, relation)

}

}