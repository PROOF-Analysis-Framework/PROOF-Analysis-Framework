/**
	@brief Internal PAF class to create the required TSelector in Proof.
	@file PAFBaseSelector.cxx
	@class PAFBaseSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#include "PAFBaseSelector.h"

#include "TLeaf.h"

#include "../computing_helpers/PAFFindHelper.h"

#include "../PAF.h"

ClassImp(PAFBaseSelector);

PAFBaseSelector::~PAFBaseSelector()
{
	delete fVariables;
}

void PAFBaseSelector::SetOutputFile(const TString& outputFile)
{
	fOutputFile = outputFile;
}

TString PAFBaseSelector::GetOutputFile()
{
	return fOutputFile;
}

void PAFBaseSelector::Init(TTree* tree)
{
	delete fVariables;
	fVariables = new PAFVariableContainer();

	fTree = tree;

	//fTree->SetBranchStatus("*", 0);

	TObjArray* leaves = tree->GetListOfLeaves();
	Int_t nb = leaves->GetEntriesFast();
	for (Int_t i = 0; i < nb; ++i) 
	{
		TObject* leaf = leaves->UncheckedAt(i);
		fVariables->Add(leaf->GetName(), leaf);
	}
	fPAFISelector->SetDynamicData(fVariables);
	PAF_DEBUG("PAFBaseSelector", "Successfully ROOT File configuration");
}

void PAFBaseSelector::SlaveBegin(TTree* tree)
{
	PAF_DEBUG("PAFBaseSelector", "Searching for PAFParams");
	fSelectorParams = PAFFindHelper::FindPAFNamed<PAFVariableContainer*>(fInput, "PAFParams");
	
	PAF_DEBUG("PAFBaseSelector", "Searching for PAFSelector");
	fPAFISelector = PAFFindHelper::FindPAFNamed<PAFISelector*>(fInput, "PAFSelector");

	PAF_DEBUG("PAFBaseSelector", "Setting up PROOF data");
	fPAFISelector->SetStaticData(fInput, fOutput, fSelectorParams);

	PAF_DEBUG("PAFBaseSelector", "Launching PAFSelectors initialisers");
	fPAFISelector->Initialise();
}

Bool_t PAFBaseSelector::Process(Long64_t entry)
{
	fTree->GetEntry(entry);
	fPAFISelector->InsideLoop();
	return kTRUE;
}

void PAFBaseSelector::Terminate()
{
	fPAFISelector->SetStaticData(fInput, fOutput, fSelectorParams);
	fPAFISelector->SetDynamicData(fVariables);
	fPAFISelector->Summary();

	PAF_DEBUG("PAFBaseSelector", "Saving output to file");
	fOutput->Add(fInput);
	fOutput->SaveAs(fOutputFile.Data());
}
