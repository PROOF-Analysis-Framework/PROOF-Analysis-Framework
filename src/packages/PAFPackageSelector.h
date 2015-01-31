/**
	@brief Package with users code to compile and load in environments.
	@file PAFPackageSelector.h
	@class PAFPackageSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#pragma once

#include "PAFPackage.h"

class PAFPackageSelector : public PAFPackage {
	public:
		PAFPackageSelector() : PAFPackage() {}
		PAFPackageSelector(const char* name) : PAFPackage(name) {}
	
	ClassDef(PAFPackageSelector, 1);
};

