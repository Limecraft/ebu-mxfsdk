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
import com.google.common.collect.Iterables;
import com.google.common.collect.Lists;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.util.*;

public class Convert {

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

    public static void main(String args[]) throws Exception {

        HashMap<String, String> namespaces = new HashMap<String, String>();
        HashMap<String, String> keys = new HashMap<String, String>();
        DocumentBuilderFactory builderF = DocumentBuilderFactory.newInstance();
        builderF.setNamespaceAware(true);

        Iterable<String> nsArgs = Iterables.<String>skip(Arrays.asList(args), 1);

        int i=1;
        for (String arg : nsArgs) {
            System.err.println(arg);
            DocumentBuilder builder = builderF.newDocumentBuilder();
            Document doc = builder.parse(arg);
            //NamedNodeMap n = doc.getDocumentElement().getAttributes();
            namespaces.put(doc.getDocumentElement().getAttributes().getNamedItem("targetNamespace").getNodeValue(), "key_ns_" + args[0] + "_" + (i++));
        }

        for (Map.Entry<String, String> e : namespaces.entrySet()) {
            System.out.println("XMLCh " + e.getValue() + "[] = {" + Joiner.on(",").join(Iterables.transform(Lists.charactersOf(e.getKey()), new Function<Character, String>() {
                    public String apply(Character o) {   return "\'" + o + "\'";  }
                })) + ",\'\\0\'};");
        }

        for (String arg : nsArgs) {

            DocumentBuilder builder = builderF.newDocumentBuilder();
            Document xmlSchema = builder.parse(arg);

            Map<String, String> localKeys = new HashMap<String, String>();

            for (Element e : getElements(xmlSchema.getDocumentElement(), "http://www.w3.org/2001/XMLSchema", "element")) {

                Element keyElem = null;

                List<Element> annotations = getElements(e, "http://www.w3.org/2001/XMLSchema", "annotation");
                if (annotations.size() > 0) {
                    List<Element> appinfo = getElements(annotations.iterator().next(),"http://www.w3.org/2001/XMLSchema", "appinfo");
                    if (appinfo.size() > 0) {
                        keyElem = Iterables.find(appinfo, new Predicate<Element>() {
                                public boolean apply(Element element) {
                                    if (element.hasAttribute("source")) {
                                        String source = element.getAttribute("source");
                                        return source.equals("http://www.smpte-ra.org/schemas/434/Dictionary/ElementUL") || source.equals("http://www.smpte-ra.org/schemas/434/Groups/Key") || source.equals("urn:ebu:metadata-schema:smpteclass13/properties/ebucore_2012/ElementUL");
                                    } else return false;
                                }
                            }, null);
                    }
                }

                if (keyElem != null) {
                    String key = keyElem.getTextContent().trim();
                    String keyName = "key_" + key.replace(".", "");
                    if (!keys.containsKey(keyName)) {
                        keys.put(keyName, keyName);
                        localKeys.put(keyName, keyName + "_name");
                        key = "{0x" + key.replace(".", ",0x") + "}";
                        System.out.println("const mxfKey " + keyName + " = " + key + ";");
                        System.out.println("const XMLCh " + keyName + "_name[] = {" +
                                Joiner.on(",").join(Iterables.transform(Lists.charactersOf(e.getAttribute("name")), new Function<Character, String>() {
                                    public String apply(Character o) {   return "\'" + o + "\'";  }
                                })) +
                                ",\'\\0\'};");

                        //System.out.println("st434dict.insert(std::pair<const mxfKey, st434info*>(");
                        //System.out.println('\t' + keyName + ',');
                        //System.out.println("\tnew st434info(/* " + e.getAttribute("name") + " */ " + keyName + "_name, /* " + xmlSchema.getDocumentElement().getAttribute("targetNamespace") + " */ " + namespaces.get(xmlSchema.getDocumentElement().getAttribute("targetNamespace")) + ")");
                        //System.out.println("));");

                    } else {
                        System.out.println("// Skipped duplicate: " + e.getAttribute("name"));
                    }
                }
                else
                {
                    System.out.println("// No UL found for element: " + e.getAttribute("name"));
                }

            }

            String targetNamespace = xmlSchema.getDocumentElement().getAttributes().getNamedItem("targetNamespace").getNodeValue();
            if (localKeys.size() > 0) {
                String arrayName = "arr_st434_elems_" + namespaces.get(targetNamespace) + "_" + (i++);
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
                System.out.println("\tnew st434info((const XMLCh*)" + arrayName + "[i][1], " + namespaces.get(targetNamespace) + ")");
                System.out.println("));");
                System.out.println("}");


            }

        }


    }

}
