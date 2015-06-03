/**
	@brief Abstract PAF test class to provides some common functionality in primitive type tests.
	@file AbstractPrimitiveType.h
	@class AbstractPrimitiveType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-03
 */

#pragma once

#include "PAFTest.h"

#include "PAF/settings/PAFISettings.h"

class AbstractPrimitiveType : public PAFTest
{
	protected:
		PAFISettings* GetPAFISettings();
};
