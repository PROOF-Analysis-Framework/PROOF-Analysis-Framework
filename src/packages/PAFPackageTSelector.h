/**
	@brief Package with PROOF TSelector code to compile and load in environments. This pacakge is only used internaly in PAF.
	@file PAFPackageTSelector.h
	@class PAFPackageTSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#pragma once

#include "PAFPackage.h"

class PAFPackageTSelector : public PAFPackage
{
	public:
		PAFPackageTSelector(const char* name) : PAFPackage(name) {}
	protected:
		virtual TString GetPreparePackageCommand();
		
	ClassDef(PAFPackageTSelector, 1);
};

