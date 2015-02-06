/**
	@brief Interface to create a composite pattern. Implemented by PAFChainSelector and PAFChainItemSelector. 
	@file PAFISelector.h
	@class PAFISelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#pragma once

#include "TObject.h"

#include "TList.h"
#include "TSelectorList.h"

#include "../variable_container/PAFVariableContainer.h"

class PAFISelector : public TObject
{
	public:
		PAFISelector() {}
		virtual ~PAFISelector() {}
	
		virtual void Initialise() {}
		virtual void InitialiseParameters() {}
		virtual void InsideLoop() {}
		virtual void Summary() {}
		
		virtual void SetStaticData(TList* fInput, TSelectorList* fOutput, PAFVariableContainer* selectorParams) {}
		virtual void SetDynamicData(PAFVariableContainer* variables) {}

	ClassDef(PAFISelector, 1);
};

