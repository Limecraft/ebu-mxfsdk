
import java.io.File;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;

import javax.xml.parsers.DocumentBuilder; 
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class declarereferences {
	
	private static Map<String, String> setupTypeMap() {
		Map<String, String> m = new HashMap<String, String>();
		
		m.put("Int8", "MXF_INT8_TYPE");
		m.put("Int16" , "MXF_INT16_TYPE");
		m.put("Int32" , "MXF_INT32_TYPE");
		m.put("Int64" , "MXF_INT64_TYPE");
		m.put("UInt8" , "MXF_UINT8_TYPE");
		m.put("UInt16" , "MXF_UINT16_TYPE");
		m.put("UInt32" , "MXF_UINT32_TYPE");
		m.put("UInt64" , "MXF_UINT64_TYPE");
		m.put("Raw" , "MXF_RAW_TYPE");
		m.put("Float32" , "MXF_FLOAT_TYPE");
		m.put("Rational", "MXF_RATIONAL_TYPE");
		m.put("Timestamp", "MXF_TIMESTAMP_TYPE");
		m.put("RGBALayoutComponent", "MXF_RGBALAYOUTCOMPONENT_TYPE");
		m.put("UTF16String" , "MXF_UTF16STRING_TYPE");
		m.put("UTF16StringArray" , "MXF_UTF16STRINGARRAY_TYPE");
		m.put("Int8Array" , "MXF_INT8ARRAY_TYPE");
		m.put("Int16Array" , "MXF_INT16ARRAY_TYPE");
		m.put("Int32Array" , "MXF_INT32ARRAY_TYPE");
		m.put("Int64Array" , "MXF_INT64ARRAY_TYPE");
		m.put("UInt8Array" , "MXF_UINT8ARRAY_TYPE");
		m.put("UInt16Array" , "MXF_UINT16ARRAY_TYPE");
		m.put("UInt32Array" , "MXF_UINT32ARRAY_TYPE");
		m.put("UInt64Array" , "MXF_UINT64ARRAY_TYPE");
		m.put("FloatArray" , "MXF_FLOATARRAY_TYPE");
		m.put("ISO7String" , "MXF_ISO7STRING_TYPE");
		m.put("Int8Batch" , "MXF_INT8BATCH_TYPE");
		m.put("Int16Batch" , "MXF_INT16BATCH_TYPE");
		m.put("Int32Batch" , "MXF_INT32BATCH_TYPE");
		m.put("Int64Batch" , "MXF_INT64BATCH_TYPE");
		m.put("UInt8Batch" , "MXF_UINT8BATCH_TYPE");
		m.put("UInt16Batch" , "MXF_UINT16BATCH_TYPE");
		m.put("UInt32Batch" , "MXF_UINT32BATCH_TYPE");
		m.put("UInt64Batch" , "MXF_UINT64BATCH_TYPE");
		m.put("FloatBatch" , "MXF_FLOATBATCH_TYPE");
		m.put("AUIDArray" , "MXF_AUIDARRAY_TYPE");
		m.put("ULArray" , "MXF_ULARRAY_TYPE");
		m.put("ULBatch" , "MXF_ULBATCH_TYPE");
		m.put("StrongRefArray" , "MXF_STRONGREFARRAY_TYPE");
		m.put("StrongRefBatch" , "MXF_STRONGREFBATCH_TYPE");
		m.put("WeakRefArray" , "MXF_WEAKREFARRAY_TYPE");
		m.put("WeakRefBatch" , "MXF_WEAKREFBATCH_TYPE");
		m.put("RationalArray" , "MXF_RATIONALARRAY_TYPE");
		m.put("RGBALayout" , "MXF_RGBALAYOUT_TYPE");
		m.put("VersionType" , "MXF_VERSIONTYPE_TYPE");
		m.put("UTF16" , "MXF_UTF16_TYPE");
		m.put("Boolean" , "MXF_BOOLEAN_TYPE");
		m.put("ISO7" , "MXF_ISO7_TYPE");
		m.put("LengthType" , "MXF_LENGTH_TYPE");
		m.put("Position" , "MXF_POSITION_TYPE");
		m.put("RGBACode" , "MXF_RGBACODE_TYPE");
		m.put("Stream" , "MXF_STREAM_TYPE");
		m.put("DataValue" , "MXF_DATAVALUE_TYPE");
		m.put("Identifier" , "MXF_IDENTIFIER_TYPE");
		m.put("Opaque" , "MXF_OPAQUE_TYPE");
		m.put("UMID" , "MXF_UMID_TYPE");
		m.put("UID" , "MXF_UID_TYPE");
		m.put("UL" , "MXF_UL_TYPE");
		m.put("UUID" , "MXF_UUID_TYPE");
		m.put("AUID" , "MXF_AUID_TYPE");
		m.put("PackageID" , "MXF_PACKAGEID_TYPE");
		m.put("StrongRef" , "MXF_STRONGREF_TYPE");
		m.put("WeakRef" , "MXF_WEAKREF_TYPE");
		m.put("Orientation" , "MXF_ORIENTATION_TYPE");
		m.put("CodedContentType" , "MXF_CODED_CONTENT_TYPE_TYPE");
		
		return m;
	}
	

	/**
	 * @param args
	 */
	public static void main(String[] args) throws Exception {

		DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
		DocumentBuilder db = dbf.newDocumentBuilder(); 
		Document doc = db.parse(new File(args[0]));
		
		Map typesMap = setupTypeMap();
		
		NodeList top_l = doc.getDocumentElement().getChildNodes();
		for (int i=0;i<top_l.getLength();i++) {
			Node n = top_l.item(i);
			if (n instanceof Element && ((Element) n).hasAttribute("type") && ((Element) n).getAttribute("type").equals("localSet")) {
				Element e = (Element)n;
				
				NodeList n_l = e.getChildNodes();
				for (int j=0;j<top_l.getLength();j++) {
					Node nn = n_l.item(j);
					if (nn instanceof Element && ((Element) nn).hasAttribute("type") &&
							(((Element) nn).getAttribute("type").contains("StrongRef") ||  ((Element) nn).getAttribute("type").contains("WeakRef"))) {
						Element ee = (Element)nn;
						
						System.out.println("{ &MXF_ITEM_K(" + e.getNodeName() + ", " + nn.getNodeName() + "), \"" + ((Element) nn).getAttribute("target") +  "*\" },");
					}
				}
				
			}
		}
	}
	
}
