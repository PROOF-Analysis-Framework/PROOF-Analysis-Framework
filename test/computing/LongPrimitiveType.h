/**
	@brief PAF test class to test the results of computing with long primitive type.
	@file LongPrimitiveType.h
	@class LongPrimitiveType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-03
 */

#pragma once

#include "AbstractPrimitiveType.h"

#include "PAF/settings/PAFISettings.h"

class LongPrimitiveType : public AbstractPrimitiveType
{
	public:
		virtual void Initialise();
		virtual void Test();
};
