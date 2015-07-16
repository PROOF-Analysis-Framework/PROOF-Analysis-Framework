/**
	@brief PAF test class to check the behaviour of SetParameter and GetParamter method with objects.
	@file PassingParametersObjects.h
	@class PassingParametersObjects
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-07-16
 */


#pragma once

#include "AbstractPrimitiveType.h"

#include "PAF/settings/PAFISettings.h"

class PassingParametersObjects : public AbstractPrimitiveType
{
	public:
		virtual void Initialise();
		virtual void Test();
};
