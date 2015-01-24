/**
	@brief Class which allows us to create a chain of selectors. 
	@file PAFChainSelector.cxx
	@class PAFChainSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/


#include "PAFChainSelector.h"

ClassImp(PAFChainSelector);

void PAFChainSelector::Initialise()
{
	for(unsigned int i = 0; i < fSelectors.size(); i++)
		fSelectors[i]->Initialise();
}

void PAFChainSelector::InitialiseParameters()
{
	for(unsigned int i = 0; i < fSelectors.size(); i++)
		fSelectors[i]->InitialiseParameters();
}

void PAFChainSelector::InsideLoop()
{
	for(unsigned int i = 0; i < fSelectors.size(); i++)
		fSelectors[i]->InsideLoop();
}

void PAFChainSelector::Summary()
{
	for(unsigned int i = 0; i < fSelectors.size(); i++)
		fSelectors[i]->Summary();
}

void PAFChainSelector::SetPROOFData(TList* fInput, TSelectorList* fOutput)
{
	for(unsigned int i = 0; i < fSelectors.size(); i++)
		fSelectors[i]->SetPROOFData(fInput, fOutput);
}


void PAFChainSelector::SetPAFData(InputParameters* fInputParameters, PAFAnalysis* fData)
{
	for(unsigned int i = 0; i < fSelectors.size(); i++)
		fSelectors[i]->SetPAFData(fInputParameters, fData);
}

