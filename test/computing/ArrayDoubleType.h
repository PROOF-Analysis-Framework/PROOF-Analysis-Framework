/**
	@brief PAF test class to test the results of computing with arrays of doubles types.
	@file DoublePrimitiveType.cxx
	@class ArrayDoubleType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-24
 */


#pragma once

#include "AbstractPrimitiveType.h"

#include "PAFISettings.h"

class ArrayDoubleType : public AbstractPrimitiveType
{
	public:
		virtual void Initialise();
		virtual void Test();
};
