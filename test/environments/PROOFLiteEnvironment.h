/**
	@brief PAF test class to check the PROOFLite environment.
	@file PROOFLiteEnvironment.h
	@class PROOFLiteEnvironment
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-08
 */

#pragma once

#include "AbstractEnvironmentTest.h"

class PROOFLiteEnvironment : public AbstractEnvironmentTest
{
	public:
		virtual void Initialise();
		virtual void Test();
};
