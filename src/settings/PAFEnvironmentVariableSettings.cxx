/**
	@brief PAFEnvironmentVariableSettings class which gets the EnvironmentVariables.
	@file PAFEnvironmentVariableSettings.h
	@class PAFEnvironmentVariableSettings
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-02-07
*/

#include "PAFEnvironmentVariableSettings.h"

#include "TSystem.h"

ClassImp(PAFEnvironmentVariableSettings);

const char* PAFPATH_VARIABLE = "PAFPATH";
const char* PAFPACKAGESDIRECTORIES = "PAFREPOSITORIES";

PAFEnvironmentVariableSettings::~PAFEnvironmentVariableSettings()
{
	delete fPackagesDirectories;
	delete fPAFPATH;
}

TString* PAFEnvironmentVariableSettings::GetPAFPATH()
{
	if(!fPAFPATH)
		fPAFPATH = GetEnvironmentVariable(PAFPATH_VARIABLE);
	return fPAFPATH;
}

std::vector< TString* >* PAFEnvironmentVariableSettings::GetPackagesDirectories()
{
	if(!fPackagesDirectories)
	{
		TString* variables = GetEnvironmentVariable(PAFPACKAGESDIRECTORIES);
		fPackagesDirectories = Split(variables, ":");
	}
	return fPackagesDirectories;
}

TString* PAFEnvironmentVariableSettings::GetEnvironmentVariable(const char* variable)
{
	return new TString(gSystem->Getenv(variable));
}

std::vector< TString* >* PAFEnvironmentVariableSettings::Split(TString* string, const char* cs)
{
	std::vector<TString*>* result = new std::vector<TString*>();
	
	while(string->Length() > 0)
	{
		int indexnext = string->First(cs);
		indexnext = indexnext > 0 ? indexnext : string->Length();
		TString* dir = new TString(string->Data(), indexnext);
		result->push_back(dir);
		string->Remove(0, indexnext + 1);
	}
	
	return result;
}
