
#ifndef __EBUSDK_ANALYZEREXTENSIONS_H__
#define __EBUSDK_ANALYZEREXTENSIONS_H__

#define MXF_LABEL(d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15) \
    {d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15}

#define MXF_SET_DEFINITION(parentName, name, label) \
    static const mxfUL MXF_SET_K(name) = label;

#define MXF_ITEM_DEFINITION(setName, name, label, localTag, typeId, isRequired) \
    static const mxfUL MXF_ITEM_K(setName, name) = label;

#include <aes3_descriptor_data_model.h>

#endif
