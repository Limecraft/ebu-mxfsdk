// Analyzer.cpp : Defines the entry point for the console application.
//

#include <sstream>

#include <mxf/mxf.h>
#include <mxf/mxf_macros.h>
#include <libMXF++/MXF.h>
#include <bmx/mxf_reader/MXFFileReader.h>
#include <bmx/BMXException.h>

#include <MXFCustomMetadata.h>
#include <metadata/EBUCoreDMS++.h>
#include <XercesUtils.h>

#if defined(_WIN32)
#include <mxf/mxf_win32_file.h>
#endif

#include <wchar.h>

#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/util/TransService.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include "Analyzer.h"

using namespace xercesc;

using namespace mxfpp;
using namespace bmx;

using namespace EBUSDK::MXFCustomMetadata;
using namespace EBUSDK::Utils;

namespace EBUSDK {
namespace Analyzer {

static XMLCh* s377mTypesNS = L"http://www.smpte-ra.org/schemas/434/2006/types/S377M/2004";
static XMLCh* s335mElementsNS = L"http://www.smpte-ra.org/schemas/434/2006/properties/S335M";
static XMLCh* s377mGroupsNS = L"http://www.smpte-ra.org/schemas/434/2006/groups/S377M/2004";
static XMLCh* s377mMuxNS = L"http://www.smpte-ra.org/schemas/434/2006/multiplex/S377M/2004";

struct st434info {
	XMLCh* namespaceURI;
	XMLCh* elementName;

	st434info(XMLCh* _elementName, XMLCh* _namespaceURI) : 	namespaceURI(_namespaceURI), elementName(_elementName) {}
};

struct KLVPacketRef {
	mxfKey key;
	int64_t len;
	int64_t offset;
	uint8_t llen;
};

class Filter {
	MXFFile *file;
	KLVPacketRef currentSet, currentItem;
	mxfUUID currentSetUID;
	bool setSet, itemSet;
	std::vector<KLVPacketRef> darkItems;
	std::vector<KLVPacketRef>& _darkSets;
	std::map<mxfUUID, std::vector<KLVPacketRef>>& _allDarkItems;
public:
	Filter(MXFFile *f, std::vector<KLVPacketRef>& darkSets, std::map<mxfUUID, std::vector<KLVPacketRef>>& darkItems) : 
		setSet(false), itemSet(false), file(f), _darkSets(darkSets), _allDarkItems(darkItems) {}
    int before_set_read(MXFHeaderMetadata *headerMetadata, const mxfKey *key, uint8_t llen, uint64_t len, int *skip) {
		// clear cache of dark items when beginning this set
		darkItems.clear();
		if (setSet) {
			// currentKey key was begun, but never finished!
			_darkSets.push_back(currentSet);
		}
		currentSet.key = *key;
		currentSet.len = len;
		currentSet.llen = llen;
		currentSet.offset = mxf_file_tell(file);
		setSet = true;
		itemSet = false;
		return true;
	}
    int after_set_read(MXFHeaderMetadata *headerMetadata, MXFMetadataSet *set, int *skip) {
		// all items are surely done when the set has finished reading
		itemDone();
		// we complete reading a complete set with a proper instance UID
		if (darkItems.size() > 0) {
			currentSetUID = set->instanceUID;
			// and add the current list of cached dark items to this set's entry
			_allDarkItems[currentSetUID] = darkItems;
		}

		if (setSet && mxf_equals_key(&currentSet.key, &set->key))
			setSet = false;

		return true;
	}
    int before_item_read(MXFHeaderMetadata *headerMetadata, const mxfKey *key, uint64_t len, int *skip) {
		if (itemSet) {
			// currentKey key was begun, but never finished!
			darkItems.push_back(currentItem);
		}
		currentItem.key = *key;
		currentItem.len = len;
		currentItem.offset = mxf_file_tell(file);
		itemSet = true;
		return true;
	}
	int after_item_read(MXFHeaderMetadata *headerMetadata, MXFMetadataItem *item) {
		if (itemSet && mxf_equals_key(&currentItem.key, &item->key))
			itemSet = false;

		return true;
	}

	void done() {
		if (setSet)
			// currentKey key was begun, but never finished!
			_darkSets.push_back(currentSet);
	}
	void itemDone() {
		if (itemSet)
			// currentKey key was begun, but never finished!
			darkItems.push_back(currentItem);
	}
};

int filter_before_set_read(void *privateData, MXFHeaderMetadata *headerMetadata,
                            const mxfKey *key, uint8_t llen, uint64_t len, int *skip) {
	return ((Filter*)privateData)->before_set_read(headerMetadata, key, llen, len, skip);
}

int filter_after_set_read(void *privateData, MXFHeaderMetadata *headerMetadata, MXFMetadataSet *set, int *skip) {
	return ((Filter*)privateData)->after_set_read(headerMetadata, set, skip);
}
int filter_before_item_read(void *privateData, MXFHeaderMetadata *headerMetadata,
                            const mxfKey *key, uint64_t len, int *skip) {
	return ((Filter*)privateData)->before_item_read(headerMetadata, key, len, skip);
}
int filter_after_item_read(void *privateData, MXFHeaderMetadata *headerMetadata, MXFMetadataItem *item) {
	return ((Filter*)privateData)->after_item_read(headerMetadata, item);
}

template<class t> const XMLCh* serialize_simple(t value, bool hex = false) {
	std::wstringstream s;
	if (hex) {
		s << L"0x" << std::hex << std::uppercase;
	}
	s << value;

	XMLCh* out = new XMLCh[s.str().length() + 1];
	wcscpy(out, s.str().c_str());
	return out;
}

const XMLCh* serialize_boolean(mxfBoolean value) {
	std::wstringstream s;
	s << (value) ? 1 : 0;

	XMLCh* out = new XMLCh[s.str().length() + 1];
	wcscpy(out, s.str().c_str());
	return out;
}

const XMLCh* serialize_uuid(mxfUUID* uuid) {
#define UUID_STRING_LEN	46
	XMLCh* out = new XMLCh[UUID_STRING_LEN];
	_snwprintf(out, UUID_STRING_LEN,
                 L"urn:uuid:%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
                 uuid->octet0, uuid->octet1, uuid->octet2, uuid->octet3,
                 uuid->octet4, uuid->octet5, uuid->octet6, uuid->octet7,
                 uuid->octet8, uuid->octet9, uuid->octet10, uuid->octet11,
                 uuid->octet12, uuid->octet13, uuid->octet14, uuid->octet15);
	return out;
}

const XMLCh* serialize_ul(mxfUL* ul) {
	std::wstringstream s;
	s << L"urn:oid:1.3.52";
	int b = 4;
	for (int b=4; b < 16 && ((uint8_t*)ul)[b] != 0; b++) {
		s << L"." << ((uint8_t*)ul)[b];
	}

	XMLCh* out = new XMLCh[s.str().length() + 1];
	wcscpy(out, s.str().c_str());
	return out;
}

const XMLCh* serialize_key(mxfKey* key) {
	std::wstringstream s;
	s << L"urn:oid:1.3.52.2";
	int b = 4;
	for (int b=4; b < 16 && ((uint8_t*)key)[b] != 0; b++) {
		s << L"." << ((uint8_t*)key)[b];
	}

	XMLCh* out = new XMLCh[s.str().length() + 1];
	wcscpy(out, s.str().c_str());
	return out;
}

const XMLCh* serialize_umid(mxfUMID *umid) {
	std::wstringstream s;
	s << L"0x" << std::hex << std::uppercase;
	for (int b=0; b < 32; b++) {
		s << ((uint8_t*)umid)[b];
	}

	XMLCh* out = new XMLCh[s.str().length() + 1];
	wcscpy(out, s.str().c_str());
	return out;
}

const XMLCh* serialize_dark_value(MXFFile *file, int64_t offset, int64_t length) {
	uint8_t *buf = new uint8_t[length];
	std::wstringstream s;

	mxf_file_seek(file, offset, SEEK_SET);
	mxf_file_read(file, buf, length);
	for (int64_t i=0;i<length;i++) {
		wchar_t t[3]; t[2] = 0;
		_snwprintf(t, 2, L"%02X", buf[i]);
		s << t;
	}

	XMLCh* out = new XMLCh[s.str().length() + 1];
	wcscpy(out, s.str().c_str());
	return out;
}

class XMLStr {
	TranscodeFromStr _s;
public:
	XMLStr(const char* source, XMLTranscoder *tc) : _s((const XMLByte*)source, strlen(source), tc) {}
	~XMLStr() {}
	const XMLCh* str() {
		return _s.str();
	}
};
typedef XMLStr _X; 

DOMElement *PrepareElement(DOMDocument *doc, DOMElement *parent, const XMLCh* namespaceURI, const XMLCh* elementName) {
	DOMElement *itemElem = doc->createElementNS(namespaceURI, elementName);
	parent->appendChild(itemElem);
	const XMLCh* prefix = itemElem->lookupPrefix(namespaceURI);
	if (prefix != NULL) {
		itemElem->setPrefix(prefix);
	}
	return itemElem;
}

DOMElement *PrepareElement(DOMDocument *doc, DOMElement *parent, const XMLCh* namespaceURI, XMLStr& elementName) {
	return PrepareElement(doc, parent, namespaceURI, elementName.str());
}

DOMElement *PrepareElementWithContent(DOMDocument *doc, DOMElement *parent, XMLCh* namespaceURI, const XMLCh* elementName, const XMLCh* textContent) {
	DOMElement *itemElem = PrepareElement(doc, parent, namespaceURI, elementName);
	itemElem->setTextContent(textContent);
	return itemElem;
}

DOMElement *PrepareElementWithContent(DOMDocument *doc, DOMElement *parent, XMLCh* namespaceURI, XMLStr& elementName, const XMLCh* textContent) {
	return PrepareElementWithContent(doc, parent, namespaceURI, elementName.str(), textContent);
}

DOMAttr *PrepareAttributeWithContent(DOMDocument *doc, DOMElement *parent, XMLCh* namespaceURI, const XMLCh* attrName, const XMLCh* textContent) {
	DOMAttr *attr = doc->createAttributeNS(namespaceURI, attrName);
	parent->setAttributeNode(attr);
	const XMLCh* prefix = attr->lookupPrefix(namespaceURI);
	if (prefix != NULL) {
		attr->setPrefix(prefix);
	}
	attr->setTextContent(textContent);
	return attr;
}

#define GET_AND_SERIALIZE(type, source, getfunction, serializefunction, dest)	\
					type v; \
					getfunction(source, &v); \
					dest->setTextContent(serializefunction(v));
#define GET_AND_SERIALIZE_BY_REF(type, source, getfunction, serializefunction, dest)	\
					type v; \
					getfunction(source, &v); \
					dest->setTextContent(serializefunction(&v));

void serializeMXFValue(unsigned int type, uint8_t *value, DOMElement* elem, DOMDocument *root, XMLTranscoder* tc) {
	if (type == MXF_INT8_TYPE) {
		GET_AND_SERIALIZE(int8_t, value, mxf_get_int8, serialize_simple<int8_t>, elem);
	} else if (type == MXF_UINT8_TYPE) {
		GET_AND_SERIALIZE(uint8_t, value, mxf_get_uint8, serialize_simple<uint8_t>, elem);
	} else if (type == MXF_INT16_TYPE) {
		GET_AND_SERIALIZE(int16_t, value, mxf_get_int16, serialize_simple<int16_t>, elem);
	} else if (type == MXF_UINT16_TYPE) {
		GET_AND_SERIALIZE(uint16_t, value, mxf_get_uint16, serialize_simple<uint16_t>, elem);
	} else if (type == MXF_INT32_TYPE) {
		GET_AND_SERIALIZE(int32_t, value, mxf_get_int32, serialize_simple<int32_t>, elem);
	} else if (type == MXF_UINT32_TYPE) {
		GET_AND_SERIALIZE(uint32_t, value, mxf_get_uint32, serialize_simple<uint32_t>, elem);
	} else if (type == MXF_INT64_TYPE) {
		GET_AND_SERIALIZE(int64_t, value, mxf_get_int64, serialize_simple<int64_t>, elem);
	} else if (type == MXF_UINT64_TYPE) {
		GET_AND_SERIALIZE(uint64_t, value, mxf_get_uint64, serialize_simple<uint64_t>, elem);
	} else if (type == MXF_POSITION_TYPE || type == MXF_LENGTH_TYPE) {
		GET_AND_SERIALIZE(int64_t, value, mxf_get_int64, serialize_simple<int64_t>, elem);
	} else if (type == MXF_BOOLEAN_TYPE) {
		GET_AND_SERIALIZE(mxfBoolean, value, mxf_get_boolean, serialize_boolean, elem);
	} else if (type == MXF_RATIONAL_TYPE) {
		const XMLCh* prefix = elem->lookupPrefix(s377mTypesNS);

		mxfRational v;
		mxf_get_rational(value, &v); 

		DOMElement *elemNum = PrepareElement(root, elem, s377mTypesNS, _X("Numerator", tc));
		elemNum->setTextContent(serialize_simple<int32_t>(v.numerator));
		DOMElement *elemDenom = PrepareElement(root, elem, s377mTypesNS, _X("Denominator", tc));
		elemDenom->setTextContent(serialize_simple<int32_t>(v.denominator));

	} else if (type == MXF_UL_TYPE) {
		GET_AND_SERIALIZE_BY_REF(mxfUL, value, mxf_get_ul, serialize_ul, elem);
	} else if (type == MXF_UMID_TYPE || type == MXF_PACKAGEID_TYPE) {
		GET_AND_SERIALIZE_BY_REF(mxfUMID, value, mxf_get_umid, serialize_umid, elem);
	} else if (type == MXF_UUID_TYPE) {
		GET_AND_SERIALIZE_BY_REF(mxfUUID, value, mxf_get_uuid, serialize_uuid, elem);
	} else if (type == MXF_TIMESTAMP_TYPE) {
		mxfTimestamp v;
		mxf_get_timestamp(value, &v);

		const XMLCh* prefix = elem->lookupPrefix(s377mTypesNS);

		DOMElement *year = PrepareElement(root, elem, s377mTypesNS, _X("Year", tc));
		year->setTextContent(serialize_simple<uint16_t>(v.year));
		DOMElement *month = PrepareElement(root, elem, s377mTypesNS, _X("Month", tc));
		month->setTextContent(serialize_simple<uint8_t>(v.month));
		DOMElement *day = PrepareElement(root, elem, s377mTypesNS, _X("Day", tc));
		day->setTextContent(serialize_simple<uint8_t>(v.day));
		DOMElement *hours = PrepareElement(root, elem, s377mTypesNS, _X("Hour", tc));
		hours->setTextContent(serialize_simple<uint8_t>(v.hour));
		DOMElement *minutes = PrepareElement(root, elem, s377mTypesNS, _X("Minute", tc));
		minutes->setTextContent(serialize_simple<uint8_t>(v.min));
		DOMElement *seconds = PrepareElement(root, elem, s377mTypesNS, _X("Second", tc));
		seconds->setTextContent(serialize_simple<uint8_t>(v.sec));
		DOMElement *qmsec = PrepareElement(root, elem, s377mTypesNS, _X("mSec4", tc));
		qmsec->setTextContent(serialize_simple<uint8_t>(v.qmsec));
	}
}

void AnalyzeShallowStrongReference(DOMElement* parent, MXFMetadataSet *set, DOMDocument* root, MXFHeaderMetadata *header_metadata, std::map<mxfKey, st434info*>& st434dict, XMLTranscoder *tc) {
	// Use the set key to determine the item information that we need to print
	std::map<mxfKey, st434info*>::const_iterator objIter;
	objIter = st434dict.find(set->key);
	// only if we know the definition
	if (objIter != st434dict.end()) {
		st434info* info = (*objIter).second;

		// write out a _REF reference element
		std::wstring ref_elem(info->elementName);
		ref_elem.append(L"_REF");
		DOMElement *refElem = PrepareElement(root, parent, info->namespaceURI, ref_elem.c_str());

		// set the instanceUID attribute
		PrepareAttributeWithContent(root, refElem, s377mTypesNS, _X("TargetInstance", tc).str(), serialize_uuid(&set->instanceUID));
	}
}

void AnalyzeMetadataSet(DOMElement* parent, MXFMetadataSet *set, DOMDocument* root, MXFHeaderMetadata *header_metadata, MXFFile *mxfFile,
	std::map<mxfUUID, std::vector<KLVPacketRef>>& darkItems, bool recurseIntoReferences, std::map<mxfKey, st434info*>& st434dict, XMLTranscoder *tc) {
	
	std::map<mxfKey, st434info*>::const_iterator objIter;
	objIter = st434dict.find(set->key);
	if (objIter != st434dict.end())
    {
		//xercesc::TranscodeFromStr location(L"http://www.smpte-ra.org/schemas/434/2006/properties/S335M", loc.size(), "UTF-8");
		//*outputDocument = ParseXercesDocument(location.str());
		MXFSetDef *setDef;
		mxf_find_set_def(header_metadata->dataModel, &set->key, &setDef);

		st434info* info = (*objIter).second;

		// create an element for this set
		DOMElement *elem = root->createElementNS(info->namespaceURI, info->elementName);
		// add element to our parent
		parent->appendChild(elem);

		// set the instanceUID attribute
		PrepareAttributeWithContent(root, elem, s335mElementsNS, _X("InstanceID", tc).str(), serialize_uuid(&set->instanceUID));

		// are there dark properties to add??? (must be done first, as per ST-434)
		std::map<mxfUUID, std::vector<KLVPacketRef>>::iterator darkIt = darkItems.find(set->instanceUID);
		if (darkIt != darkItems.end()) {
			std::vector<KLVPacketRef>& localDarkItems = (*darkIt).second;
			if (localDarkItems.size() > 0) {
				DOMElement* props = PrepareElement(root, elem, s377mGroupsNS, _X("ExtensionProperties", tc));
				
				for(std::vector<KLVPacketRef>::iterator it = localDarkItems.begin(); it != localDarkItems.end(); it++) {
					KLVPacketRef& ref = *it;
					DOMElement* prop = PrepareElement(root, props, s377mGroupsNS, _X("DarkProperty", tc));
					PrepareAttributeWithContent(root, prop, s377mGroupsNS, _X("UniversalLabel", tc).str(), serialize_ul(&ref.key));
					prop->setTextContent(serialize_dark_value(mxfFile, ref.offset, ref.len));
				}
			}
		}

		// loop through the set and locate strongly referenced children
		MXFListIterator itemIter;
		mxf_initialise_list_iter(&itemIter, &set->items);
		while (mxf_next_list_iter_element(&itemIter))
		{
			MXFItemDef *itemDef;
			MXFMetadataItem *item = (MXFMetadataItem*)mxf_get_iter_element(&itemIter);

			// what is the definition of this item
			if (mxf_find_item_def_in_set_def(&item->key, setDef, &itemDef)) {
				MXFItemType *itemType = mxf_get_item_def_type(header_metadata->dataModel, itemDef->typeId);

				std::map<mxfKey, st434info*>::const_iterator objIter;
				objIter = st434dict.find(itemDef->key);
				// only if we know the definition
				if (objIter != st434dict.end())
				{
					st434info* itemInfo = (*objIter).second;

					// create an element for this item
					DOMElement *itemElem = PrepareElement(root, elem, itemInfo->namespaceURI, itemInfo->elementName);
					
					// .. and a pointer to a possible strongly referenced set
					MXFMetadataSet *referencedSet;

					if (itemDef->typeId == MXF_STRONGREF_TYPE) {

						// item is a single strong reference, follow it
						mxf_get_strongref_item(set, &item->key, &referencedSet);

						// do we follow strong references extensively?
						if (recurseIntoReferences) {
							AnalyzeMetadataSet(itemElem, referencedSet, root, header_metadata, mxfFile, darkItems, recurseIntoReferences, st434dict, tc);
						}
						else {
							AnalyzeShallowStrongReference(itemElem, referencedSet, root, header_metadata, st434dict, tc);
						}

					} else if (itemDef->typeId == MXF_STRONGREFARRAY_TYPE || itemDef->typeId == MXF_STRONGREFBATCH_TYPE) {

						// loop through the array or batch of elements and follow each
						MXFArrayItemIterator arrayIter; uint8_t* _value; uint32_t _length;
						mxf_initialise_array_item_iterator(set, &item->key, &arrayIter);
						while (mxf_next_array_item_element(&arrayIter, &_value, &_length) != 0)
						{
							MXFListIterator setsIter;
							mxf_initialise_sets_iter(header_metadata, &setsIter);

							if (mxf_get_strongref_s(header_metadata, &setsIter, _value, &referencedSet)) {

								// do we follow strong references extensively?
								if (recurseIntoReferences) {
									AnalyzeMetadataSet(itemElem, referencedSet, root, header_metadata, mxfFile, darkItems, recurseIntoReferences, st434dict, tc);
								}
								else {
									AnalyzeShallowStrongReference(itemElem, referencedSet, root, header_metadata, st434dict, tc);
								}
							}
						}
					} else {

						if (itemDef->typeId == MXF_UTF16STRING_TYPE || itemDef->typeId == MXF_ISO7STRING_TYPE) {
							uint16_t utf16Size;
							mxf_get_utf16string_item_size(set, &item->key, &utf16Size);
							mxfUTF16Char *utf16Result = new mxfUTF16Char[utf16Size];
							mxf_get_utf16string(item->value, item->length, utf16Result);
							itemElem->setTextContent(utf16Result);
						} else if (itemType->category == MXF_ARRAY_TYPE_CAT) {
							// this is any array type, loop through the entries
							MXFArrayItemIterator arrIter;
							uint8_t *arrElm;
							uint32_t arrElmLength;

							mxf_initialise_array_item_iterator(set, &item->key, &arrIter);
							while (mxf_next_array_item_element(&arrIter, &arrElm, &arrElmLength))
							{
								if (itemType->typeId != MXF_UTF16STRING_TYPE && itemType->typeId != MXF_ISO7STRING_TYPE) {
									/* There can be no strings in arrays! */
									DOMElement *arrDomElem = PrepareElement(root, itemElem, s335mElementsNS, _X("Element", tc));
									serializeMXFValue(itemType->info.array.elementTypeId, arrElm, arrDomElem, root, tc);
								}
							}

						} else {
							serializeMXFValue(itemDef->typeId, item->value, itemElem, root, tc);
						}
					}
				}
			}
 		}

	}
	else {
		// don't know this!!!
	}
}

void AnalyzeList(DOMElement* parent, MXFList *list, int elementType, DOMDocument* root, XMLTranscoder *tc) {
	MXFListIterator it;
	mxf_initialise_list_iter(&it, list);
	while (mxf_next_list_iter_element(&it)) {
		uint8_t* v = (uint8_t*)mxf_get_iter_element(&it);
		serializeMXFValue(elementType, v, PrepareElement(root, parent, s335mElementsNS, _X("Element", tc)), root, tc);
	}
}

void AnalyzeRIP(DOMElement* parent, DOMDocument* root, MXFRIP *rip, uint32_t rip_size, XMLTranscoder *tc) {
	DOMElement *ripElem = PrepareElement(root, parent, s377mGroupsNS, _X("RandomIndexPack", tc));
	DOMElement *ripEntriesElem = PrepareElement(root, ripElem, s377mGroupsNS, _X("PartitionOffsetPairArray", tc));
		
		MXFListIterator it;
		mxf_initialise_list_iter(&it, &rip->entries);
		while (mxf_next_list_iter_element(&it)) {
			MXFRIPEntry* v = (MXFRIPEntry*)mxf_get_iter_element(&it);
			DOMElement *ripEntry = PrepareElement(root, ripEntriesElem, s377mGroupsNS, _X("PartitionOffsetPair", tc));
			PrepareElementWithContent(root, ripEntry, s335mElementsNS, _X("EssenceStreamID", tc), serialize_simple<uint32_t>(v->bodySID));
			PrepareElementWithContent(root, ripEntry, s335mElementsNS, _X("ByteOffset", tc), serialize_simple<uint64_t>(v->thisPartition));
		}

	PrepareElementWithContent(root, ripElem, s335mElementsNS, _X("PackLength", tc), serialize_simple<uint32_t>(rip_size));

}

void AnalyzePartitionPack(DOMElement* parent, DOMDocument* root, MXFPartition *partition, XMLTranscoder *tc) {
	DOMElement *ppElem = PrepareElement(root, parent, s377mGroupsNS, _X("PartitionPack", tc));
	PrepareElementWithContent(root, ppElem, s335mElementsNS, _X("MajorVersion", tc), serialize_simple<uint16_t>(partition->majorVersion));
	PrepareElementWithContent(root, ppElem, s335mElementsNS, _X("MinorVersion", tc), serialize_simple<uint16_t>(partition->minorVersion));
	PrepareElementWithContent(root, ppElem, s335mElementsNS, _X("KAGSize", tc), serialize_simple<uint32_t>(partition->kagSize));
	PrepareElementWithContent(root, ppElem, s335mElementsNS, _X("ThisPartition", tc), serialize_simple<uint64_t>(partition->thisPartition));
	PrepareElementWithContent(root, ppElem, s335mElementsNS, _X("PreviousPartition", tc), serialize_simple<uint64_t>(partition->previousPartition));
	PrepareElementWithContent(root, ppElem, s335mElementsNS, _X("FooterPartition", tc), serialize_simple<uint64_t>(partition->footerPartition));
	PrepareElementWithContent(root, ppElem, s335mElementsNS, _X("HeaderByteCount", tc), serialize_simple<uint64_t>(partition->headerByteCount));
	PrepareElementWithContent(root, ppElem, s335mElementsNS, _X("IndexByteCount", tc), serialize_simple<uint64_t>(partition->indexByteCount));	
	PrepareElementWithContent(root, ppElem, s335mElementsNS, _X("IndexStreamID", tc), serialize_simple<uint32_t>(partition->indexSID));	
	PrepareElementWithContent(root, ppElem, s335mElementsNS, _X("BodyOffset", tc), serialize_simple<uint64_t>(partition->bodyOffset));	
	PrepareElementWithContent(root, ppElem, s335mElementsNS, _X("EssenceStreamID", tc), serialize_simple<uint32_t>(partition->bodySID));
	PrepareElementWithContent(root, ppElem, s335mElementsNS, _X("OperationalPattern", tc), serialize_ul(&partition->operationalPattern));
	DOMElement *ppEssenceContaines = PrepareElement(root, ppElem, s335mElementsNS, _X("EssenceContainers", tc));
	AnalyzeList(ppEssenceContaines, &partition->essenceContainers, MXF_UL_TYPE, root, tc);
}

void AnalyzePrimerPack(DOMElement* parent, DOMDocument* root, MXFPrimerPack *primer, XMLTranscoder *tc) {
	DOMElement *ppElem = PrepareElement(root, parent, s377mGroupsNS, _X("PrimerPack", tc));
	DOMElement *ppBatch = PrepareElement(root, ppElem, s377mGroupsNS, _X("LocalTagEntryBatch", tc));

	MXFListIterator it;
	mxf_initialise_list_iter(&it, &primer->entries);
	while (mxf_next_list_iter_element(&it)) {
		MXFPrimerPackEntry* v = (MXFPrimerPackEntry*)mxf_get_iter_element(&it);
		DOMElement *ppEntry = PrepareElement(root, ppBatch, s377mGroupsNS, _X("LocalTagEntry", tc));
		PrepareElementWithContent(root, ppEntry, s335mElementsNS, _X("LocalTag", tc), serialize_simple<uint16_t>(v->localTag, true));
		PrepareElementWithContent(root, ppEntry, s335mElementsNS, _X("LocalTagUniqueID", tc), serialize_ul(&v->uid));
	}
}

void AnalyzeDarkSets(DOMElement* parent, DOMDocument* root, MXFHeaderMetadata *header_metadata, MXFFile *mxfFile, std::vector<KLVPacketRef>& darkSets, XMLTranscoder *tc) {
	if (darkSets.size() > 0) {
		DOMElement* floatingGroups = PrepareElement(root, parent, s377mMuxNS, _X("FloatingMetadataGroups", tc));
		for (std::vector<KLVPacketRef>::iterator it = darkSets.begin(); it != darkSets.end(); it++) {
			DOMElement* darkElem = PrepareElement(root, floatingGroups, s377mGroupsNS, _X("UnparsedDarkGroup", tc));
			PrepareAttributeWithContent(root, darkElem, s377mGroupsNS, _X("Key", tc).str(), serialize_key(&(*it).key));
			PrepareAttributeWithContent(root, darkElem, s377mGroupsNS, _X("BEROctetCount", tc).str(), serialize_simple<uint8_t>((*it).llen));
			darkElem->setTextContent(serialize_dark_value(mxfFile, (*it).offset, (*it).len));
		}
	}
}

void AnalyzeIndexTable(DOMElement* parent, DOMDocument* root, MXFFile *mxfFile, uint64_t indexTableLength, bool deepIndexTableAnalysis, XMLTranscoder *tc) {
	MXFIndexTableSegment* idx;
	mxf_read_index_table_segment(mxfFile, indexTableLength, &idx);
	DOMElement *idxElem = PrepareElement(root, parent, s377mGroupsNS, _X("IndexTableSegment", tc));
		DOMElement *rateElem = PrepareElement(root, idxElem, s335mElementsNS, _X("IndexEditRate", tc));
			PrepareElementWithContent(root, rateElem, s377mTypesNS, _X("Numerator", tc), serialize_simple<int32_t>(idx->indexEditRate.numerator));
			PrepareElementWithContent(root, rateElem, s377mTypesNS, _X("Denominator", tc), serialize_simple<int32_t>(idx->indexEditRate.denominator));
		PrepareElementWithContent(root, idxElem, s335mElementsNS, _X("IndexStartPosition", tc), serialize_simple<mxfPosition>(idx->indexStartPosition));
		PrepareElementWithContent(root, idxElem, s335mElementsNS, _X("IndexDuration", tc), serialize_simple<mxfLength>(idx->indexDuration));
		PrepareElementWithContent(root, idxElem, s335mElementsNS, _X("EditUnitByteCount", tc), serialize_simple<uint32_t>(idx->editUnitByteCount));
		PrepareElementWithContent(root, idxElem, s335mElementsNS, _X("IndexStreamID", tc), serialize_simple<uint32_t>(idx->indexSID));
		PrepareElementWithContent(root, idxElem, s335mElementsNS, _X("EssenceStreamID", tc), serialize_simple<uint32_t>(idx->bodySID));
		PrepareElementWithContent(root, idxElem, s335mElementsNS, _X("SliceCount", tc), serialize_simple<uint8_t>(idx->sliceCount));
		PrepareElementWithContent(root, idxElem, s335mElementsNS, _X("PositionTableCount", tc), serialize_simple<uint8_t>(idx->posTableCount));

		if (deepIndexTableAnalysis) {
			DOMElement *deltaArrayElem = PrepareElement(root, idxElem, s335mElementsNS, _X("DeltaEntryArray", tc));
			// loop through the linked list of delta entries
			MXFDeltaEntry *d_entry = idx->deltaEntryArray;
			while (d_entry != NULL) {
				DOMElement *deltaElem = PrepareElement(root, deltaArrayElem, s335mElementsNS, _X("Element", tc));
					PrepareElementWithContent(root, deltaElem, s335mElementsNS, _X("PositionTableIndex", tc), serialize_simple<int8_t>(d_entry->posTableIndex));
					PrepareElementWithContent(root, deltaElem, s335mElementsNS, _X("Slice", tc), serialize_simple<uint8_t>(d_entry->slice));
					PrepareElementWithContent(root, deltaElem, s335mElementsNS, _X("ElementDelta", tc), serialize_simple<uint32_t>(d_entry->elementData));
				d_entry = d_entry->next;
			}

			DOMElement *indexArrayElem = PrepareElement(root, idxElem, s335mElementsNS, _X("IndexEntryArray", tc));
			// loop through the linked list of index entries
			MXFIndexEntry *i_entry = idx->indexEntryArray;
			while (i_entry != NULL) {
				DOMElement *idxEntElem = PrepareElement(root, indexArrayElem, s335mElementsNS, _X("Element", tc));
					PrepareElementWithContent(root, idxEntElem, s335mElementsNS, _X("TemporalOffset", tc), serialize_simple<int8_t>(i_entry->temporalOffset));
					PrepareElementWithContent(root, idxEntElem, s335mElementsNS, _X("KeyFrameOffset", tc), serialize_simple<int8_t>(i_entry->keyFrameOffset));
					PrepareElementWithContent(root, idxEntElem, s335mElementsNS, _X("Flags", tc), serialize_simple<uint8_t>(i_entry->flags));
					PrepareElementWithContent(root, idxEntElem, s335mElementsNS, _X("StreamOffset", tc), serialize_simple<uint64_t>(i_entry->streamOffset));

					// loop through the array of slice offsets
					DOMElement *sliceElem = PrepareElement(root, idxEntElem, s335mElementsNS, _X("SliceOffset", tc));
						for (uint8_t i=0; i<idx->sliceCount; i++) {
							PrepareElementWithContent(root, sliceElem, s335mElementsNS, _X("Element", tc), serialize_simple<uint32_t>(i_entry->sliceOffset[i]));
						}
					// loop through the array of positions
					DOMElement *posElem = PrepareElement(root, idxEntElem, s335mElementsNS, _X("PositionTable", tc));
						for (uint8_t i=0; i<idx->posTableCount; i++) {
							DOMElement *ptElem = PrepareElement(root, posElem, s335mElementsNS, _X("Element", tc));
							PrepareElementWithContent(root, ptElem, s377mTypesNS, _X("Numerator", tc), serialize_simple<int32_t>(i_entry->posTable[i].numerator));
							PrepareElementWithContent(root, ptElem, s377mTypesNS, _X("Denominator", tc), serialize_simple<int32_t>(i_entry->posTable[i].denominator));
						}

				i_entry = i_entry->next;
			}
		}

	mxf_free_index_table_segment(&idx);
}

std::auto_ptr<HeaderMetadata> ReadHeaderMetadata(File* mxfFile, Partition* partition, DataModel* metadataModel, std::vector<KLVPacketRef>& darkSets, std::map<mxfUUID, std::vector<KLVPacketRef>>& darkItems) {

	mxfKey key;
	uint8_t llen;
	uint64_t len;

	std::auto_ptr<HeaderMetadata> mHeaderMetadata ( new HeaderMetadata(metadataModel) );

	mxfFile->seek(partition->getThisPartition(), SEEK_SET);
	mxfFile->readKL(&key, &llen, &len);
	mxfFile->skip(len);
	mxfFile->readNextNonFillerKL(&key, &llen, &len);

	uint64_t pos_start_metadata = mxfFile->tell() - mxfKey_extlen - llen;

	Filter filter(mxfFile->getCFile(), darkSets, darkItems);
	MXFReadFilter cfilter;
	cfilter.before_set_read = filter_before_set_read;
	cfilter.after_set_read = filter_after_set_read;
	cfilter.before_item_read = filter_before_item_read;
	cfilter.after_item_read = filter_after_item_read;
	cfilter.privateData = &filter;

	mHeaderMetadata->readFiltered(&*mxfFile, partition, &cfilter, &key, llen, len);
	filter.done();

	return mHeaderMetadata;
}

void AnalyzeHeaderMetadata(	DOMElement *parent, DOMDocument* root, HeaderMetadata* headerMetadata, MXFFile *file,
	std::vector<KLVPacketRef>& darkSets, std::map<mxfUUID, std::vector<KLVPacketRef>>& darkItems, AnalyzerConfig configuration, std::map<mxfKey, st434info*>& st434dictionary, XMLTranscoder *tc) {

	if (configuration.MetadataAnalysisType == AnalyzerConfig::LOGICAL) {
		// analyze the metadata set
		AnalyzeMetadataSet(parent, headerMetadata->getPreface()->getCMetadataSet(), root, headerMetadata->getCHeaderMetadata(), file, darkItems, true, st434dictionary, tc);
		// the dump dark sets
		AnalyzeDarkSets(parent, root, headerMetadata->getCHeaderMetadata(), file, darkSets, tc);
	} else {
		// do a 'physical' dump of the metadata, iterate over each of the sets
		MXFListIterator setIter;		
		mxf_initialise_list_iter(&setIter, &headerMetadata->getCHeaderMetadata()->sets);
		while (mxf_next_list_iter_element(&setIter))
		{
			MXFMetadataSet *set = (MXFMetadataSet*)mxf_get_iter_element(&setIter);

			// analyze the metadata set
			AnalyzeMetadataSet(parent, set, root, headerMetadata->getCHeaderMetadata(), file, darkItems, false, st434dictionary, tc);
		}
		// the dump dark sets
		AnalyzeDarkSets(parent, root, headerMetadata->getCHeaderMetadata(), file, darkSets, tc);

	}
}

void AddST434PrefixDeclarations(DOMDocument *doc, XMLTranscoder* tc) {
	// add global namespace/prefix declarations
	doc->getDocumentElement()->setAttributeNS(xercesc::XMLUni::fgXMLNSURIName,
		_X("xmlns:s335mElements", tc).str(), s335mElementsNS);
	doc->getDocumentElement()->setAttributeNS(xercesc::XMLUni::fgXMLNSURIName,
		_X("xmlns:s377mTypes", tc).str(), s377mTypesNS);
	doc->getDocumentElement()->setAttributeNS(xercesc::XMLUni::fgXMLNSURIName,
		_X("xmlns:s377mGroups", tc).str(), s377mGroupsNS);
}

bool FindIndexTable(MXFFile *mxfFile, int64_t offset, int64_t *tableOffset, int64_t maxTableLength, int64_t *length) {
	mxfKey key;
    uint8_t llen;
    uint64_t len;
	int64_t skippedBytes = 0;

	mxf_file_seek(mxfFile, offset, SEEK_SET);
	while (skippedBytes <= maxTableLength)
    {
        CHK_ORET(mxf_read_next_nonfiller_kl(mxfFile, &key, &llen, &len));
        if (mxf_is_index_table_segment(&key))
        {
			*length = len;
			*tableOffset = mxf_file_tell(mxfFile);
            return true;
        }
        else
        {
            CHK_ORET(mxf_skip(mxfFile, len));
			// count what we have skipped (Key length, length length and value length)
			skippedBytes += mxfKey_extlen + llen + len;
        }
    }
	return false;
}

void AnalyzePartition(DOMElement *parent, DOMDocument *root, Partition *partition, File *mxfFile, DataModel *dataModel, AnalyzerConfig configuration, std::map<mxfKey, st434info*>& st434dict, XMLTranscoder *tc) {
	std::vector<KLVPacketRef> darkSets;
	std::map<mxfUUID, std::vector<KLVPacketRef>> darkItems;

	// what type of partition is this?
	DOMElement *partElem = 
		mxf_is_header_partition_pack(partition->getKey()) ? 
			PrepareElement(root, parent, s377mMuxNS, _X("HeaderPartition", tc)) : 
			(mxf_is_footer_partition_pack(partition->getKey()) ? 
				PrepareElement(root, parent, s377mMuxNS, _X("FooterPartition", tc)) :
				PrepareElement(root, parent, s377mMuxNS, _X("BodyPartition", tc)));

	AnalyzePartitionPack(partElem, root, partition->getCPartition(), tc);

	if (partition->getHeaderByteCount() > 0) {
		DOMElement *metadataElem = PrepareElement(root, partElem, s377mMuxNS, _X("HeaderMetadata", tc));

		std::auto_ptr<HeaderMetadata> headerMetadata = ReadHeaderMetadata(mxfFile, partition, dataModel, darkSets, darkItems);

		AnalyzePrimerPack(metadataElem, root, headerMetadata->getCHeaderMetadata()->primerPack, tc);

		DOMElement *setsElem = PrepareElement(root, metadataElem, s377mMuxNS, _X("MetadataSets", tc));

		AnalyzeHeaderMetadata(setsElem, root, &*headerMetadata,
			mxfFile->getCFile(), darkSets, darkItems, configuration, st434dict, tc);
	}

	if (partition->getIndexByteCount() > 0) {

		DOMElement *indexElem = PrepareElement(root, partElem, s377mGroupsNS, _X("IndexTable", tc));

		int64_t indexTableOffset=0, indexTableLength=0;
		while (FindIndexTable(mxfFile->getCFile(), indexTableOffset + partition->getThisPartition() + partition->getHeaderByteCount(), &indexTableOffset, partition->getIndexByteCount() - indexTableOffset, &indexTableLength)) {
			indexTableOffset += indexTableLength;
			AnalyzeIndexTable(indexElem, root, mxfFile->getCFile(), indexTableLength, configuration.DeepIndexTableAnalysis, tc);
		}
	}

}

std::auto_ptr<DOMDocument> AnalyzeMXFFile(const char* mxfLocation, AnalyzerConfig configuration) {

	XMLPlatformUtils::Initialize();

	// get a string transcoder for translating local code page strings as written here in source
	// to UTF-16 coded-strings to pass to the Xerces document
	XMLTransService::Codes res;
	XMLTranscoder *tc = XMLPlatformUtils::fgTransService->makeNewTranscoderFor(
		XMLRecognizer::Encodings::UTF_8, res, 2048   /* as used by TranscodeFromStr class */);

	DOMImplementation *pImpl = DOMImplementation::getImplementation();

	std::map<mxfKey, st434info*> st434dict;

#include "group_declarations.inc"

	std::auto_ptr<File> mFile( File::openRead(mxfLocation) );	// throws MXFException if open failed!

	std::auto_ptr<DataModel> mDataModel ( new DataModel() );
	EBUSDK::EBUCore::RegisterExtensions(&*mDataModel);

	// ///////////////////////////////////////
	// / 1. Open MXF File and locate all partitions, using the RIP
	// ///////////

	// read the RIP
	bool validRIP = false;
	MXFRIP rip;
	uint32_t rip_size;
	if (mxf_read_rip_and_size(mFile->getCFile(), &rip, &rip_size)) {
		validRIP = true;
	}

	if (!mFile->readPartitions())
		throw BMXException("Failed to read all partitions. File may be incomplete or invalid");

	const std::vector<Partition*> &partitions = mFile->getPartitions();

	// ///////////////////////////////////////
	// / 1a. Locate the Metadata to use for extension
	/*		We prefer closed footer metadata when available (if the metadata 
			is repeated in the footer, it is likely to be more up-to-date than
			that in the header.																*/
	// ///////////
	Partition *metadata_partition = NULL, *headerPartition = NULL, *footerPartition = NULL;

	metadata_partition = FindPreferredMetadataPartition(partitions, &headerPartition, &footerPartition);

	std::auto_ptr<DOMDocument> out;

	if (configuration.AnalysisType == AnalyzerConfig::METADATA) {

		// only analyze the primary header metadata into a MetadataSets element

		DOMDocument *doc = pImpl->createDocument(s377mMuxNS, _X("MetadataSets", tc).str(), NULL);
		AddST434PrefixDeclarations(doc, tc);

		if (!metadata_partition)
			throw BMXException("No MXF suitable MXF metadata found");

		std::vector<KLVPacketRef> darkSets;
		std::map<mxfUUID, std::vector<KLVPacketRef>> darkItems;

		std::auto_ptr<HeaderMetadata> headerMetadata = ReadHeaderMetadata(&*mFile, metadata_partition, &*mDataModel, darkSets, darkItems);

		AnalyzeHeaderMetadata(doc->getDocumentElement(), doc, &*headerMetadata, 
			mFile->getCFile(), darkSets, darkItems, configuration, st434dict, tc);

		out = std::auto_ptr<DOMDocument>(doc);

	} else {

		// analyze the entire MXF file into an MXFFile element
		DOMDocument *doc = pImpl->createDocument(s377mMuxNS, _X("MXFFile", tc).str(), NULL);
		AddST434PrefixDeclarations(doc, tc);

		// dump each of the partitions, header partition first
		AnalyzePartition(doc->getDocumentElement(), doc, headerPartition, &*mFile, &*mDataModel, configuration, st434dict, tc);

		// ... then body partitions
		for (std::vector<Partition*>::const_iterator it = partitions.begin(); it != partitions.end(); it++) {
			if (mxf_is_body_partition_pack((*it)->getKey())) {
				AnalyzePartition(doc->getDocumentElement(), doc, *it, &*mFile, &*mDataModel, configuration, st434dict, tc);
			}
		}

		// ... finally dump footer partition
		if (footerPartition != NULL)
			AnalyzePartition(doc->getDocumentElement(), doc, footerPartition, &*mFile, &*mDataModel, configuration, st434dict, tc);

		if (validRIP) {
			AnalyzeRIP(doc->getDocumentElement(), doc, &rip, rip_size, tc);
		}

		out = std::auto_ptr<DOMDocument>(doc);
	}

	// cleanup
	mxf_clear_rip(&rip);

	return out;
}

void AnalyzeMXFFile(const char* mxfLocation, const char* reportLocation, AnalyzerConfig configuration) {
	std::auto_ptr<DOMDocument> doc = AnalyzeMXFFile(reportLocation, configuration);
	LocalFileFormatTarget f(reportLocation);
	SerializeXercesDocument(*doc, f);
}

} // namespace Analyzer
} // namespace EBUSDK
