/**
	@brief PAF test class to test the results of computing with double primitive type.
	@file DoublePrimitiveType.h
	@class DoublePrimitiveType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-03
 */


#pragma once

#include "AbstractPrimitiveType.h"

#include "PAFISettings.h"

class DoublePrimitiveType : public AbstractPrimitiveType
{
	public:
		virtual void Initialise();
		virtual void Test();
};
