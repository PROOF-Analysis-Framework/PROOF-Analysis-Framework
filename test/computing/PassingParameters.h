/**
	@brief PAF test class to check the behaviour of SetParameter and GetParamter method.
	@file PassingParameters.h
	@class PassingParameters
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-28
 */


#pragma once

#include "AbstractPrimitiveType.h"

#include "PAFISettings.h"

class PassingParameters : public AbstractPrimitiveType
{
	public:
		virtual void Initialise();
		virtual void Test();
};
