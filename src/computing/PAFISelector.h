/**
	@brief Interface to create a composite pattern. Implemented by PAFChainSelector and PAFChainItemSelector. 
	@file PAFISelector.h
	@class PAFISelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#pragma once

#include <TList.h>
#include <TSelectorList.h>
#include <TObject.h>

#include "../input_parameters/InputParameters.h"
#include "../variable_container/PAFVariableContainer.h"

class PAFAnalysis;

class PAFISelector : public TObject
{
	public:
		PAFISelector() {}
		virtual ~PAFISelector() {}
	
		virtual void Initialise() {}
		virtual void InitialiseParameters() {}
		virtual void InsideLoop() {}
		virtual void Summary() {}
		
		virtual void SetPROOFData(TList*, TSelectorList* ) {}
		virtual void SetPAFData(InputParameters* inputParameters, PAFAnalysis* data, PAFVariableContainer* selectorParams) {}

	ClassDef(PAFISelector, 1);
};

