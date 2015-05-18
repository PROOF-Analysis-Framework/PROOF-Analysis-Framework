/**
	@brief Class to create a PAFProject which should be configured (although it has default values) and launched to get results. 
	@file PAFProject.cxx
	@class PAFProject
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#include "PAFProject.h"

ClassImp(PAFProject);

PAFProject::PAFProject()
	: PAFAbstractProject()
{
	InitMembers();
}

PAFProject::PAFProject(PAFIExecutionEnvironment* executionEnvironment) 
	: PAFAbstractProject(executionEnvironment)
{
	InitMembers();
}

void PAFProject::InitMembers()
{
	fDataFiles = new TDSet("PAFFiles", "Tree");
}

PAFProject::~PAFProject()
{
	delete fDataFiles;
}

TString PAFProject::GetDefaultTreeName()
{
	return TString(fDataFiles->GetObjName());
}

void PAFProject::SetDefaultTreeName(TString& defualtTreeName)
{
	SetDefaultTreeName(defualtTreeName.Data());
}

void PAFProject::SetDefaultTreeName(const char* defaultTreeName)
{
	fDataFiles->SetObjName(defaultTreeName);
}

TDSet* PAFProject::GetDataFiles()
{
	return fDataFiles;
}

void PAFProject::SetDataFiles(TDSet* dataFiles)
{
	fDataFiles = dataFiles;
}

void PAFProject::AddDataFile(TString& fileName, const char* objname)
{
	AddDataFile(fileName.Data(), objname);
}

void PAFProject::AddDataFile(const char* fileName, const char* objname)
{
	fDataFiles->Add(fileName, objname);
}

void PAFProject::AddDataFile(TFileInfo* dataFile)
{
	fDataFiles->Add(dataFile);
}

void PAFProject::doRun(PAFBaseSelector* selector)
{
	fExecutionEnvironment->Process(selector, fDataFiles);
}
