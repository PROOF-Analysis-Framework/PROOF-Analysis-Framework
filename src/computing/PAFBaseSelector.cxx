/**
	@brief Internal PAF class to create the required TSelector in Proof.
	@file PAFBaseSelector.cxx
	@class PAFBaseSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#include "PAFBaseSelector.h"
#include "../util/PAFNamedContainer.h"

#include "../PAF.h"
#include "TString.h"

ClassImp(PAFBaseSelector);

void PAFBaseSelector::SlaveBegin(TTree* tree)
{
	PAF_DEBUG("PAFBaseSelector", "Searching for PAFParams");
	fSelectorParams = FindPAFInput<PAFVariableContainer*>("PAFParams");
	
	PAF_DEBUG("PAFBaseSelector", "Searching for PAFSelector");
	fPAFISelector = FindPAFInput<PAFISelector*>("PAFSelector");

	PAF_DEBUG("PAFBaseSelector", "Setting up PROOF data");
	fPAFISelector->SetPROOFData(fInput, fOutput);
	
	PAF_DEBUG("PAFBaseSelector", "Setting up PAF data");
	fPAFISelector->SetPAFData((PAFAnalysis*)this, fSelectorParams);

	PAF_DEBUG("PAFBaseSelector", "Launching PAFSelectors initialisers");
	fPAFISelector->Initialise();
}

Bool_t PAFBaseSelector::Process(Long64_t entry)
{
	fChain->GetTree()->GetEntry(entry);

	fPAFISelector->InsideLoop();
	return kTRUE;
}

void PAFBaseSelector::Terminate()
{	
	fPAFISelector->SetPROOFData(fInput, fOutput);	
	fPAFISelector->SetPAFData((PAFAnalysis*)this, fSelectorParams);
  	fPAFISelector->Summary();
}
