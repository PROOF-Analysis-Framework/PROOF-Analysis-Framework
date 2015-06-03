/**
	@brief PAFManualSettings class which holds the variables the user specifies.
	@file PAFManualSettings.h
	@class PAFManualSettings
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-03
 */

#include "PAFManualSettings.h"

PAFManualSettings::PAFManualSettings(TString* pafPath, std::vector< TString* >* packagesDirectories)
	: PAFISettings(), fPAFPath(pafPath->Copy()), fPackagesDirectories(*packagesDirectories)
{

}

TString* PAFManualSettings::GetPAFPATH()
{
	return &fPAFPath;
}

std::vector< TString* >* PAFManualSettings::GetPackagesDirectories()
{
	return &fPackagesDirectories;
}
