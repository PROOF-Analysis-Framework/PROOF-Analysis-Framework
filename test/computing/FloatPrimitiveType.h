/**
	@brief PAF test class to test the results of computing with float primitive type.
	@file FloatPrimitiveType.h
	@class FloatPrimitiveType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-03
 */


#pragma once

#include "AbstractPrimitiveType.h"

#include "PAFISettings.h"

class FloatPrimitiveType : public AbstractPrimitiveType
{
	public:
		virtual void Initialise();
		virtual void Test();
};
