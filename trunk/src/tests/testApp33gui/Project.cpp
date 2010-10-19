#include "Project.h"

CProject::CProject(void)
{
	this->xml_proj_file = string();
}

CProject::CProject(string xmlfile)
{
	xml_proj_file = xmlfile;
}

CProject::~CProject(void)
{
}

int CProject::Load(){
	if (this->xml_proj_file.empty())
		return -1;

	//cargar estructura

	return 1;
}

int CProject::Load(string xmlfile)
{
	this->xml_proj_file = xmlfile;
	return this->Load();
}

int CProject::AddObject(string objfilename)
{
	this->objects.push_back(objfilename);
	return 1;
}
