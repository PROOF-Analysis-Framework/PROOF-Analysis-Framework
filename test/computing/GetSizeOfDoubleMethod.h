/**
	@brief PAF test class to test the GetSizeOf method with a double vector.
	@file GetSizeOfDoubleMethod.h
	@class GetSizeOfDoubleMethod
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-09
 */

#pragma once

#include "AbstractPrimitiveType.h"

class GetSizeOfDoubleMethod : public AbstractPrimitiveType
{
	public:
		virtual void Initialise();
		virtual void Test();
};
