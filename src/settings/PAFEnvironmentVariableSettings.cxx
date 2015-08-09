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

#include "PAFStringUtil.h"

ClassImp(PAFEnvironmentVariableSettings);

const char* PAFPATH_VARIABLE = "PAFPATH";
const char* PAFPACKAGESDIRECTORIES = "PAFREPOSITORIES";

PAFEnvironmentVariableSettings::PAFEnvironmentVariableSettings()
	: fPAFPATH(0), fPackagesDirectories(0)
{

}

PAFEnvironmentVariableSettings::~PAFEnvironmentVariableSettings()
{
	delete fPackagesDirectories;
	delete fPAFPATH;
}

TString* PAFEnvironmentVariableSettings::GetPAFPATH()
{
	if(!fPAFPATH)
	{
		fPAFPATH = GetEnvironmentVariable(PAFPATH_VARIABLE);
	}
	return fPAFPATH;
}

std::vector< TString* >* PAFEnvironmentVariableSettings::GetPackagesDirectories()
{
	if(!fPackagesDirectories)
	{
		TString* variables = GetEnvironmentVariable(PAFPACKAGESDIRECTORIES);
		fPackagesDirectories = PAFStringUtil::Split(variables, ":");
	}
	return fPackagesDirectories;
}

TString* PAFEnvironmentVariableSettings::GetEnvironmentVariable(const char* variable)
{
	return new TString(gSystem->Getenv(variable));
}
