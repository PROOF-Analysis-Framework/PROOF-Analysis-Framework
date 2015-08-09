/**
	@brief PAF test class to test the results of computing with a vector of double type.
	@file VectorDoubleType.h
	@class VectorDoubleType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-03
 */


#pragma once

#include "AbstractPrimitiveType.h"

#include "PAFISettings.h"

class VectorDoubleType : public AbstractPrimitiveType
{
	public:
		virtual void Initialise();
		virtual void Test();
};
