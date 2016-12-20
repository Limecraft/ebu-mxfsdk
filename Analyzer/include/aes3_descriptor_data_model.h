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
 
#if !defined (MXF_LABEL)
#define MXF_LABEL(d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15)
#endif
#if !defined (MXF_SET_DEFINITION)
#define MXF_SET_DEFINITION(parentName, name, label)
#endif
#if !defined (MXF_ITEM_DEFINITION)
#define MXF_ITEM_DEFINITION(setName, name, label, localTag, typeId, isRequired)
#endif

/*MXF_SET_DEFINITION(WaveAudioDescriptor, AES3AudioDescriptor,
    MXF_LABEL(0x06,0x0e,0x2b,0x34,0x02,0x53,0x01,0x01,0x0d,0x01,0x01,0x01,0x01,0x01,0x47,0x00)
);*/

	/*MXF_ITEM_DEFINITION(AES3AudioDescriptor, Emphasis,
        MXF_LABEL(0x06,0x0e,0x2b,0x34,0x01,0x01,0x01,0x05,0x04,0x02,0x05,0x01,0x06,0x00,0x00,0x00),
        0x3d0d,
        MXF_UINT8_TYPE,
        0
    );

	MXF_ITEM_DEFINITION(AES3AudioDescriptor, BlockStartOffset,
        MXF_LABEL(0x06,0x0e,0x2b,0x34,0x01,0x01,0x01,0x05,0x04,0x02,0x03,0x02,0x03,0x00,0x00,0x00),
        0x3d0f,
        MXF_UINT16_TYPE,
        0
    );

	MXF_ITEM_DEFINITION(AES3AudioDescriptor, AuxBitsMode,
        MXF_LABEL(0x06,0x0e,0x2b,0x34,0x01,0x01,0x01,0x05,0x04,0x02,0x05,0x01,0x01,0x00,0x00,0x00),
        0x3d08,
        MXF_UINT8_TYPE,
        0
    );

	MXF_ITEM_DEFINITION(AES3AudioDescriptor, ChannelStatusMode,
        MXF_LABEL(0x06,0x0e,0x2b,0x34,0x01,0x01,0x01,0x05,0x04,0x02,0x05,0x01,0x02,0x00,0x00,0x00),
        0x3d10,
        MXF_UINT8ARRAY_TYPE,
        0
    );

	MXF_ITEM_DEFINITION(AES3AudioDescriptor, FixedChannelStatusData,
        MXF_LABEL(0x06,0x0e,0x2b,0x34,0x01,0x01,0x01,0x05,0x04,0x02,0x05,0x01,0x03,0x00,0x00,0x00),
        0x3d11,
        MXF_UINT8ARRAY_TYPE,
        0
    );

	MXF_ITEM_DEFINITION(AES3AudioDescriptor, UserDataMode,
        MXF_LABEL(0x06,0x0e,0x2b,0x34,0x01,0x01,0x01,0x05,0x04,0x02,0x05,0x01,0x04,0x00,0x00,0x00),
        0x3d12,
        MXF_UINT8ARRAY_TYPE,
        0
    );

	MXF_ITEM_DEFINITION(AES3AudioDescriptor, FixedUserData,
        MXF_LABEL(0x06,0x0e,0x2b,0x34,0x01,0x01,0x01,0x05,0x04,0x02,0x05,0x01,0x05,0x00,0x00,0x00),
        0x3d13,
        MXF_UINT8ARRAY_TYPE,
        0
    );
*/
#if !defined(KEEP_DATA_MODEL_DEFS)
#undef MXF_BASIC_TYPE_DEF
#undef MXF_ARRAY_TYPE_DEF
#undef MXF_COMPOUND_TYPE_DEF
#undef MXF_COMPOUND_TYPE_MEMBER
#undef MXF_INTERPRETED_TYPE_DEF
#undef MXF_LABEL
#undef MXF_SET_DEFINITION
#undef MXF_ITEM_DEFINITION
#endif

