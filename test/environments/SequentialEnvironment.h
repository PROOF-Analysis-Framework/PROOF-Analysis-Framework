/**
	@brief PAF test class to check the sequential environment.
	@file SequentialEnvironment.h
	@class SequentialEnvironment
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-08
 */

#pragma once

#include "AbstractEnvironmentTest.h"

class SequentialEnvironment : public AbstractEnvironmentTest
{
	public:
		virtual void Initialise();
		virtual void Test();
};
