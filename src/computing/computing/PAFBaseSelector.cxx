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
	PAF_DEBUG("PAFBaseSelector", "Initializing...");
	delete fVariables;
	fVariables = new PAFVariableContainer();

	fTree = tree;

	if (ROOT::GetROOT()->GetVersionInt() >= 60000)
	{
		fTree->SetBranchStatus("*", 0);
		PAF_INFO("PAFBaseSelector", "Enabling lazy loading of branches.");
	}
	else
	{
		PAF_WARN("PAFBaseSelector", "It was not possible to enable the lazy loading due to a bug in your ROOT version. Please, use ROOT6 or higher.");
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
	PAF_INFO("PAFBaseSelector", "Successfully configured ROOT file");

}

void PAFBaseSelector::Begin(TTree* /*tree*/) {
        // This method is executed only on the master and not on the slaves
        // It is needed to avoid having to retrieve things initialised in Selectors::Initialise() 
        // in Summary()
	PAF_DEBUG("PAFBaseSelector", "Initialising selectors in the master...");
	if (!fPAFISelector)
	  PAF_FATAL("PAFBaseSelector", "Could not find list of selectors.");

	PAF_DEBUG("PAFBaseSelector", "Setting up PROOF parameters in the master");
	fPAFISelector->SetStaticData(fInput, fOutput, fSelectorParams);

	PAF_DEBUG("PAFBaseSelector::Begin()", "Initializing PAFSelectors in the master");
	fPAFISelector->Initialise();

	// This is needed to avoid duplications.
	fOutput = new TSelectorList;
}

void PAFBaseSelector::SlaveBegin(TTree* /*tree*/)
{
	PAF_DEBUG("PAFBaseSelector", "Searching for PAFParams");
	fSelectorParams = PAFFindHelper::FindPAFNamed<PAFVariableContainer*>(fInput, "PAFParams");
	
	PAF_DEBUG("PAFBaseSelector", "Searching for PAFSelector");
	fPAFISelector = PAFFindHelper::FindPAFNamed<PAFISelector*>(fInput, "PAFSelector");
	if (!fPAFISelector)
	  PAF_FATAL("PAFBaseSelector", "Could not find list of selectors.");

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
	PAF_DEBUG("PAFBaseSelector", "Terminating...");
	fPAFISelector->SetStaticData(fInput, fOutput, fSelectorParams);
	fPAFISelector->SetDynamicData(fVariables);
	PAF_DEBUG("PAFBaseSelector", "Going for summary from the selectors...");
	fPAFISelector->Summary();

	PAF_INFO("PAFBaseSelector", Form("Saving output to file %s", fOutputFile.Data()));
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
	PAF_DEBUG("PAFBaseSelector", "Setting selector parameters...");
	fSelectorParams = selectorparams;
}

PAFVariableContainer* PAFBaseSelector::GetSelectorParams()
{
	return fSelectorParams;
}
