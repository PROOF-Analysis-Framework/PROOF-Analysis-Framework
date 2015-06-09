/**
	@brief PAF test class to test the GetSizeOf method with a int vector.
	@file GetSizeOfIntMethod.h
	@class GetSizeOfIntMethod
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-09
 */

#pragma once

#include "AbstractPrimitiveType.h"

class GetSizeOfIntMethod : public AbstractPrimitiveType
{
	public:
		virtual void Initialise();
		virtual void Test();
};
