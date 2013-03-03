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
 

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <mxf/mxf.h>
#include <mxf/mxf_macros.h>

#include <EBUCore_1_4/metadata/EBUCoreDMS.h>

using namespace EBUSDK::EBUCore;

int EBUCoreDMS::RegisterCExtensions(MXFDataModel *data_model)
{
    // register EBU Core framework set and items in data model

#define MXF_LABEL(d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15) \
    {d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15}

#define MXF_SET_DEFINITION(parentName, name, label) \
    CHK_OFAIL(mxf_register_set_def(data_model, #name, &MXF_SET_K(parentName), &MXF_SET_K(name)));

#define MXF_ITEM_DEFINITION(setName, name, label, tag, typeId, isRequired) \
    CHK_OFAIL(mxf_register_item_def(data_model, #name, &MXF_SET_K(setName), &MXF_ITEM_K(setName, name), tag, \
                                    typeId, isRequired));

#include <EBUCore_1_4/metadata/ebucore_extensions_data_model.h>

    return mxf_finalise_data_model(data_model);

fail:
		;
}

