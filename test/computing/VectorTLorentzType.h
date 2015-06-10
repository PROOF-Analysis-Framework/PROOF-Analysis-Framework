/**
	@brief PAF test class to test the results of computing with a vector of TLorentVectors.
	@file VectorTLorentzType.h
	@class VectorTLorentzType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-10
 */


#pragma once

#include "AbstractPrimitiveType.h"

#include "PAF/settings/PAFISettings.h"

class VectorTLorentzType : public AbstractPrimitiveType
{
	public:
		virtual void Initialise();
		virtual void Test();
};
