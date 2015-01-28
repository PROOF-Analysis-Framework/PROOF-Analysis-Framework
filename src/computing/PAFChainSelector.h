/**
	@brief Class which allows us to create a chain of selectors. 
	@file PAFChainSelector.h
	@class PAFChainSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#pragma once

#include "PAFISelector.h"

class PAFChainSelector : public PAFISelector
{
	public:
                PAFChainSelector() : fSelectors () { }
		PAFChainSelector(std::vector<PAFISelector*>* selectors) { fSelectors = *selectors; } 
		virtual ~PAFChainSelector() {}

		virtual void Initialise();
		virtual void InitialiseParameters();
		virtual void InsideLoop();
		virtual void Summary();
		
		virtual void SetPROOFData(TList* input, TSelectorList* output);
		virtual void SetPAFData(InputParameters* inputParameters, PAFAnalysis* data, PAFVariableContainer* selectorParams);

	private:
		std::vector<PAFISelector*> fSelectors;

	ClassDef(PAFChainSelector, 1);
};
