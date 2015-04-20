/**
	@brief Class to create a PAFProject which should be configured (although it has default values) and launched to get results. 
	@file PAFProject.cxx
	@class PAFProject
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#include "PAFProject.h"

#include "TSystem.h"

#include "../util/PAFNamedItem.h"
#include "../settings/PAFEnvironmentVariableSettings.h"
#include "../util/PAFStopWatch.h"

#include "../PAF.h"

#include "../environments/PAFPROOFLiteEnvironment.h"

ClassImp(PAFProject);

PAFProject::PAFProject()
	: PAFAbstractProject()
{
	fDataFiles = new TFileCollection("PAFFiles");
}

PAFProject::PAFProject(PAFIExecutionEnvironment* executionEnvironment) 
	: PAFAbstractProject(executionEnvironment)
{
	fDataFiles = new TFileCollection("PAFFiles");
}

PAFProject::~PAFProject()
{
	delete fDataFiles;
}

void PAFProject::AddDataFile(TString& fileName)
{
	//TFileInfo* result = new TFileInfo(fileName);
	//AddDataFile(result);
	fDataFiles->Add(fileName);
}

void PAFProject::AddDataFile(const char* fileName)
{
	TString tFileName(fileName);
	AddDataFile(tFileName);
}

void PAFProject::AddDataFile(TFileInfo* dataFile)
{
	fDataFiles->Add(dataFile);
}

void PAFProject::doRun(PAFBaseSelector* selector)
{
	fExecutionEnvironment->Process(selector, fDataFiles);
}


