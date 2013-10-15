/*
 *	Copyright 2012-2013 European Broadcasting Union and Limecraft, NV.
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *	   http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *	See the License for the specific language governing permissions and
 *	limitations under the License.
 *
 */

import com.google.common.base.Function;
import com.google.common.base.Joiner;
import com.google.common.base.Predicate;
import com.google.common.collect.ImmutableMap;
import com.google.common.collect.Iterables;
import com.google.common.collect.Lists;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.util.*;

public class Dictconvert {

    public static List<Element> getElements(Element src, String nameSpace, String elementName) {
        List<Element> l = new ArrayList<Element>();
        Node n = src.getFirstChild();
        while (n != null) {
            if (n instanceof Element && n.getLocalName().equals(elementName) && n.getNamespaceURI().equals(nameSpace))
                l.add((Element)n);
            n = n.getNextSibling();
        }
        return l;
    }

    public static List<Element> getElements(Element src) {
        List<Element> l = new ArrayList<Element>();
        Node n = src.getFirstChild();
        while (n != null) {
            if (n instanceof Element)
                l.add((Element)n);
            n = n.getNextSibling();
        }
        return l;
    }


    public static void main(String args[]) throws Exception {

        final ImmutableMap<String, String> nameMap =
                new ImmutableMap.Builder<String, String>()
                        .put("ebucoreMainFramework" , "ebucoreMainFramework")
                        .put("ebucorePartFramework" , "ebucorePartFramework")
                        .put("ebucoreMetadataSchemeInformation","ebucoreMetadataSchemeInformation")
                        /* List mainly generated using AWK:
                        	awk '{t=$2; gsub(/ebucore/, "", t); print "\x27"$2"\x27:\x27" tolower(substr(t, 1, 1))substr(t, 2)"\x27," }' < tmp.txt > tmpout.txt
                        */
                        .put("ebucoreEntity","entity")
                        .put("ebucoreContact","contact")
                        .put("ebucoreContactDetails","details")
                        .put("ebucoreAddress","address")
                        .put("ebucoreRegion","region")
                        .put("ebucoreCompoundName","compoundName")
                        .put("ebucoreRole","role")
                        .put("ebucoreCountry","country")
                        .put("ebucoreTextualAnnotation","textualAnnotation")
                        .put("ebucoreBasicLink","basicLink")
                        .put("ebucoreTypeGroup","typeGroup")
                        .put("ebucoreOrganisation","organisation")
                        .put("ebucoreOrganisationDepartment","organisationDepartment")
                        .put("ebucoreCoreMetadata","coreMetadata")
                        .put("ebucoreIdentifier","identifier")
                        .put("ebucoreTitle","title")
                        .put("ebucoreAlternativeTitle","alternativeTitle")
                        .put("ebucoreFormatGroup","formatGroup")
                        .put("ebucoreStatusGroup","statusGroup")
                        .put("ebucoreSubject","subject")
                        .put("ebucoreDescription","description")
                        .put("ebucoreDate","date")
                        .put("ebucoreDateType","dateType")
                        .put("ebucoreType","type")
                        .put("ebucoreObjectType","objectType")
                        .put("ebucoreGenre","genre")
                        .put("ebucoreTargetAudience","targetAudience")
                        .put("ebucoreLanguage","language")
                        .put("ebucoreCoverage","coverage")
                        .put("ebucoreSpatial","spatial")
                        .put("ebucoreLocation","location")
                        .put("ebucoreCoordinates","coordinates")
                        .put("ebucoreTemporal","temporal")
                        .put("ebucorePeriodOfTime","periodOfTime")
                        .put("ebucoreRights","rights")
                        .put("ebucoreVersion","version")
                        .put("ebucoreRating","rating")
                        .put("ebucorePublicationHistoryEvent","publicationHistoryEvent")
                        .put("ebucorePublicationHistory","publicationHistory")
                        .put("ebucorePublicationChannel","publicationChannel")
                        .put("ebucorePublicationMedium","publicationMedium")
                        .put("ebucorePublicationService","publicationService")
                        .put("ebucoreCustomRelation","customRelation")
                        .put("ebucoreBasicRelation","basicRelation")
                        .put("ebucorePartMetadata","partMetadata")
                        .put("ebucoreFormat","format")
                        .put("ebucoreVideoFormat","videoFormat")
                        .put("ebucoreImageFormat","imageFormat")
                        .put("ebucoreAudioFormat","audioFormat")
                        .put("ebucoreTrack","track")
                        .put("ebucoreDataFormat","dataFormat")
                        .put("ebucoreCaptioning","captioning")
                        .put("ebucoreSubtitling","subtitling")
                        .put("ebucoreAncillaryData","ancillaryData")
                        .put("ebucoreSigningFormat","signingFormat")
                        .put("ebucoreTechnicalAttributeString","technicalAttributeString")
                        .put("ebucoreTechnicalAttributeInt8","technicalAttributeInt8")
                        .put("ebucoreTechnicalAttributeInt16","technicalAttributeInt16")
                        .put("ebucoreTechnicalAttributeInt32","technicalAttributeInt32")
                        .put("ebucoreTechnicalAttributeInt64","technicalAttributeInt64")
                        .put("ebucoreTechnicalAttributeUInt8","technicalAttributeUInt8")
                        .put("ebucoreTechnicalAttributeUInt16","technicalAttributeUInt16")
                        .put("ebucoreTechnicalAttributeUInt32","technicalAttributeUInt32")
                        .put("ebucoreTechnicalAttributeUInt64","technicalAttributeUInt64")
                        .put("ebucoreTechnicalAttributeFloat","technicalAttributeFloat")
                        .put("ebucoreTechnicalAttributeRational","technicalAttributeRational")
                        .put("ebucoreTechnicalAttributeAnyURI","technicalAttributeAnyURI")
                        .put("ebucoreTechnicalAttributeBoolean","technicalAttributeBoolean")
                        .put("ebucoreDimension","dimension")
                        .put("ebucoreWidth","width")
                        .put("ebucoreHeight","height")
                        .put("ebucorePackageInfo","packageInfo")
                        .put("ebucoreMedium","medium")
                        .put("ebucoreCodec","codec")
                        .put("ebucoreRational","rational")
                        .put("ebucoreAspectRatio","aspectRatio").build();

        String key_ns_ebucore_1 = "urn:ebu:metadata-schema:smpteclass13/groups/ebucore_2013";
        Map<String, String> namespaces = ImmutableMap.<String, String>of(key_ns_ebucore_1, "key_ns_ebucore_1");

        HashMap<String, String> keys = new HashMap<String, String>();
        DocumentBuilderFactory builderF = DocumentBuilderFactory.newInstance();
        builderF.setNamespaceAware(true);

        DocumentBuilder builder = builderF.newDocumentBuilder();
        Document xmlDictionary = builder.parse(args[0]);

        Map<String, String> localKeys = new HashMap<String, String>();

        for (Map.Entry<String, String> e : namespaces.entrySet()) {
            System.out.println("XMLCh " + e.getValue() + "[] = {" + Joiner.on(",").join(Iterables.transform(Lists.charactersOf(e.getKey()), new Function<Character, String>() {
                public String apply(Character o) {   return "\'" + o + "\'";  }
            })) + ",\'\\0\'};");
        }

        for (Element e: Iterables.filter(getElements(xmlDictionary.getDocumentElement()), new Predicate<Element>() {
            public boolean apply(Element element) {
                return element.getAttribute("type").equals("localSet");
            }}))
        {
            String name = nameMap.get(e.getLocalName());
            String keyName = "key_" +  Joiner.on("").join(e.getAttribute("key").split("\\s"));

            localKeys.put(keyName, keyName + "_name");

            System.out.println("const mxfKey " + keyName + " = {" +
                    Joiner.on(",").join(Iterables.transform(Arrays.asList(e.getAttribute("key").split("\\s")), new Function<String, String>() {
                        public String apply(String o) {   return "0x" + o;  }
                    })) + "};");
            System.out.println("const XMLCh " + keyName + "_name[] = {" +
                    Joiner.on(",").join(Iterables.transform(Lists.charactersOf(name), new Function<Character, String>() {
                        public String apply(Character o) {   return "\'" + o + "\'";  }
                    })) + ",\'\\0\'};");

            //System.out.println("st434dict.insert(std::pair<const mxfKey, st434info*>(");
            //System.out.println('\t' + keyName + ',');
            //System.out.println("\tnew st434info(/* " + e.getLocalName() + " */ " + keyName + "_name, /* " + key_ns_ebucore_1 + " */ " + namespaces.get(key_ns_ebucore_1) + ")");
            //System.out.println("));");

        }

        if (localKeys.size() > 0) {
            String arrayName = "arr_ebucore_elems";
            System.out.println("const void* " + arrayName + "[][2] = {");

            System.out.println(Joiner.on(", \n").join(Iterables.transform(localKeys.entrySet(), new Function<Map.Entry<String, String>, String>() {
                @Override
                public String apply(java.util.Map.Entry<String, String> e) {
                    return "{ &" + e.getKey() + ", " + e.getValue() + " }";
                }
            })));
            System.out.println("};");

            System.out.println("for (int i=0; i<" + localKeys.size() + ";i++) {");
            System.out.println("\tst434dict.insert(std::pair<const mxfKey, st434info*>(");
            System.out.println("\t*(const mxfKey*)" + arrayName + "[i][0], ");
            System.out.println("\tnew st434info((const XMLCh*)" + arrayName + "[i][1], key_ns_ebucore_1)");
            System.out.println("));");
            System.out.println("}");
        }

    }

}
