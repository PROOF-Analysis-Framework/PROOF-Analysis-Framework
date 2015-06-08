/**
	@brief Abstract PAF test class to provides some common functionality to environments tests.
	@file AbstractEnvironmentTest.h
	@class AbstractEnvironmentTest
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-08
 */

#pragma once

#include "PAFTest.h"

#include "PAF/settings/PAFISettings.h"

class AbstractEnvironmentTest : public PAFTest
{
	protected:
		PAFISettings* GetPAFISettings();
		void CreateROOTFile(const char* fileName);
};
