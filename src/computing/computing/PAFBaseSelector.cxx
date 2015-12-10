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
#include "TROOT.h"

#include "PAF.h"
#include "PAFFindHelper.h"
#include "PAFTypesFactory.h"

ClassImp(PAFBaseSelector);

PAFBaseSelector::PAFBaseSelector()
	: fTree(0), fPAFISelector(0), fSelectorParams(0), fVariables(0)
{

}

PAFBaseSelector::~PAFBaseSelector()
{
	delete fVariables;
}

Int_t PAFBaseSelector::Version() const
{
	return 2;
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

	if (ROOT::GetROOT()->GetVersionInt() >= 60000)
	{
		fTree->SetBranchStatus("*", 0);
		PAF_DEBUG("PAFBaseSelector", "Enabling lazy loading of branches.");
	}
	else
	{
		PAF_DEBUG("PAFBaseSelector", "It was not possible to enable the lazy loading due to a bug in your ROOT version. Please, use ROOT6 or higher.");
	}
	
	TObjArray* leaves = tree->GetListOfLeaves();
	PAFTypesFactory factory;
	Int_t nb = leaves->GetEntriesFast();
	for (Int_t i = 0; i < nb; ++i) 
	{
		TLeaf* leaf = (TLeaf*)leaves->UncheckedAt(i);
		fVariables->Add(leaf->GetName(), (TObject*)factory.GetPAFType(leaf));
	}
	fPAFISelector->SetDynamicData(fVariables);
	PAF_DEBUG("PAFBaseSelector", "Successfully configured ROOT file");
}

void PAFBaseSelector::SlaveBegin(TTree* /*tree*/)
{
	PAF_DEBUG("PAFBaseSelector", "Searching for PAFParams");
	fSelectorParams = PAFFindHelper::FindPAFNamed<PAFVariableContainer*>(fInput, "PAFParams");
	
	PAF_DEBUG("PAFBaseSelector", "Searching for PAFSelector");
	fPAFISelector = PAFFindHelper::FindPAFNamed<PAFISelector*>(fInput, "PAFSelector");

	PAF_DEBUG("PAFBaseSelector", "Setting up PROOF data");
	fPAFISelector->SetStaticData(fInput, fOutput, fSelectorParams);

	PAF_DEBUG("PAFBaseSelector", "Initializing PAFSelectors");
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

void PAFBaseSelector::SetPAFSelector(PAFISelector* pafiselector)
{
	fPAFISelector = pafiselector;
}

PAFISelector* PAFBaseSelector::GetPAFSelector()
{
	return fPAFISelector;
}

void PAFBaseSelector::SetSelectorParams(PAFVariableContainer* selectorparams)
{
	fSelectorParams = selectorparams;
}

PAFVariableContainer* PAFBaseSelector::GetSelectorParams()
{
	return fSelectorParams;
}
