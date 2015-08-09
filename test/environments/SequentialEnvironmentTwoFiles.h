/**
	@brief PAF test class to check the sequential environment with two ROOT files.
	@file SequentialEnvironmentTwoFiles.h
	@class SequentialEnvironmentTwoFiles
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-08-9
 */

#pragma once

#include "AbstractEnvironmentTest.h"

class SequentialEnvironmentTwoFiles : public AbstractEnvironmentTest
{
	public:
		virtual void Initialise();
		virtual void Test();

	protected:
		virtual void CreateROOTFiles();
};
