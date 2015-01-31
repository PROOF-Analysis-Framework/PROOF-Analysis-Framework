/**
	@brief Interface which defines the default methods for a PAFHelper.
	@file PAFIHelper.h
	@class PAFIHelper
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-01-31
*/

#pragma once

#include "TObject.h"

class PAFIHelper : public TObject {
	public:
		PAFIHelper() {}
		virtual ~PAFIHelper() {}
		
		virtual void SetPROOFData(TList* fInput, TSelectorList* fOutput) {}
		virtual void SetPAFData(PAFVariableContainer* variables, PAFVariableContainer* selectorParams) {}
	
	ClassDef(PAFIHelper, 1);
};