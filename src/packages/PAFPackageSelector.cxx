/**
	@brief Package with users code to compile and load in environments.
	@file PAFPackageSelector.cxx
	@class PAFPackageSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#include "PAFPackageSelector.h"

ClassImp(PAFPackageSelector);

PAFPackageSelector::PAFPackageSelector(PAFISettings* pafsettings, const char* name)
	: PAFPackage(pafsettings, name)
{

}
