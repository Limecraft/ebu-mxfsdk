 /*
  *    Copyright 2012-2013 European Broadcasting Union and Limecraft, NV.
  *
  *    Licensed under the Apache License, Version 2.0 (the "License");
  *    you may not use this file except in compliance with the License.
  *    You may obtain a copy of the License at
  *
  *       http://www.apache.org/licenses/LICENSE-2.0
  *
  *    Unless required by applicable law or agreed to in writing, software
  *    distributed under the License is distributed on an "AS IS" BASIS,
  *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  *    See the License for the specific language governing permissions and
  *    limitations under the License.
  *
  */
  
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <memory>

#include <libMXF++/MXF.h>
#include <EBUCore_1_4/metadata/EBUCoreDMS++.h>


using namespace std;
using namespace mxfpp;
using namespace EBUSDK::EBUCore::EBUCore_1_4::KLV;


const mxfKey ebucoreOrganisationDepartmentBase::setKey = MXF_SET_K(ebucoreOrganisationDepartment);


ebucoreOrganisationDepartmentBase::ebucoreOrganisationDepartmentBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreOrganisationDepartmentBase::ebucoreOrganisationDepartmentBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreOrganisationDepartmentBase::~ebucoreOrganisationDepartmentBase()
{}


bool ebucoreOrganisationDepartmentBase::havedepartmentId() const
{
    return haveItem(&MXF_ITEM_K(ebucoreOrganisationDepartment, departmentId));
}

std::string ebucoreOrganisationDepartmentBase::getdepartmentId() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreOrganisationDepartment, departmentId));
}

bool ebucoreOrganisationDepartmentBase::havedepartmentName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreOrganisationDepartment, departmentName));
}

std::string ebucoreOrganisationDepartmentBase::getdepartmentName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreOrganisationDepartment, departmentName));
}

void ebucoreOrganisationDepartmentBase::setdepartmentId(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreOrganisationDepartment, departmentId), value);
}

void ebucoreOrganisationDepartmentBase::setdepartmentName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreOrganisationDepartment, departmentName), value);
}

