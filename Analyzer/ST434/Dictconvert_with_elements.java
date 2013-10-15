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

public class Dictconvert_with_elements {

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

        String targetNameSpace = args[1];
        String targetNameSpaceVar = args[2];

        Map<String, String> namespaces = ImmutableMap.<String, String>of(targetNameSpace, targetNameSpaceVar);

        HashMap<String, String> keys = new HashMap<String, String>();
        DocumentBuilderFactory builderF = DocumentBuilderFactory.newInstance();
        builderF.setNamespaceAware(true);

        DocumentBuilder builder = builderF.newDocumentBuilder();
        Document xmlDictionary = builder.parse(args[0]);

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
            String name = e.getLocalName();
            String keyName = "key_" +  Joiner.on("").join(e.getAttribute("key").split("\\s"));

            System.out.println("mxfKey " + keyName + " = {" +
                    Joiner.on(",").join(Iterables.transform(Arrays.asList(e.getAttribute("key").split("\\s")), new Function<String, String>() {
                        public String apply(String o) {   return "0x" + o;  }
                    })) + "};");
            System.out.println("XMLCh " + keyName + "_name[] = {" +
                    Joiner.on(",").join(Iterables.transform(Lists.charactersOf(name), new Function<Character, String>() {
                        public String apply(Character o) {   return "\'" + o + "\'";  }
                    })) + ",\'\\0\'};");

            System.out.println("st434dict.insert(std::pair<mxfKey, st434info*>(");
            System.out.println('\t' + keyName + ',');
            System.out.println("\tnew st434info(/* " + name + " */ " + keyName + "_name, /* " + targetNameSpace + " */ " + namespaces.get(targetNameSpace) + ")");
            System.out.println("));");


            for (Element ee : getElements(e)) {

                String elemKeyName = "key_" + Joiner.on("").join(ee.getAttribute("globalKey").split("\\s"));
                System.out.println("mxfKey " + elemKeyName + " = {" +
                        Joiner.on(",").join(Iterables.transform(Arrays.asList(ee.getAttribute("globalKey").split("\\s")), new Function<String, String>() {
                            public String apply(String o) {   return "0x" + o;  }
                        })) + "};");
                System.out.println("XMLCh " + elemKeyName + "_name[] = {" +
                        Joiner.on(",").join(Iterables.transform(Lists.charactersOf(ee.getLocalName()), new Function<Character, String>() {
                            public String apply(Character o) {   return "\'" + o + "\'";  }
                        })) + ",\'\\0\'};");

                System.out.println("st434dict.insert(std::pair<mxfKey, st434info*>(");
                System.out.println('\t' + elemKeyName + ',');
                System.out.println("\tnew st434info(/* " + ee.getLocalName() + " */ " + elemKeyName + "_name, /* " + targetNameSpace + " */ " + namespaces.get(targetNameSpace) + ")");
                System.out.println("));");
            }

        }

    }

}
