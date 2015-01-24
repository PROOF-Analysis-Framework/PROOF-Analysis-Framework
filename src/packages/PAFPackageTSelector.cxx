/**
	@brief Package with PROOF TSelector code to compile and load in environments. This pacakge is only used internaly in PAF.
	@file PAFPackageTSelector.cxx
	@class PAFPackageTSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#include "PAFPackageTSelector.h"

ClassImp(PAFPackageTSelector);

TString PAFPackageTSelector::GetPreparePackageCommand()
{
	return TString::Format("$PAFPATH/bin/PreparePackage.sh -s -d %s -r %s %s", GetPackagesDir().Data(), GetBuildDir().Data(), GetName().Data());
}
