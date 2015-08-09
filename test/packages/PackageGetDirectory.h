/**
	@brief PAF test class to test the get directory method of packages.
	@file PackageGetDirectory.h
	@class PackageGetDirectory
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-05
 */

#pragma once

#include "PAFTest.h"

#include "PAFPackage.h"

class PackageGetDirectory : public PAFTest, public PAFPackage
{
	public:
		virtual void Initialise();
		virtual void Test();
};
