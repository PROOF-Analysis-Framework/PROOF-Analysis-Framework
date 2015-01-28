/**
	@brief Internal PAF class to create the required TSelector in Proof.
	@file PAFBaseSelector.h
	@class PAFBaseSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#pragma once

#include <TROOT.h>
#include <TChain.h>
#include <TSelector.h>
#include "TString.h"

#include "PAFISelector.h"
#include "../util/PAFNamedContainer.h"
#include "../variable_container/PAFVariableContainer.h"

#include "../PAF.h"

class PAFAnalysis;

class PAFBaseSelector : public TSelector {
	public:
		PAFBaseSelector() : fChain(0), fPAFISelector(0), fSelectorParams(0) { }
		virtual ~PAFBaseSelector() { }
		virtual Int_t   Version() const { return 2; }
		virtual void    SlaveBegin(TTree* tree);
		virtual Bool_t  Notify() { return kTRUE; }
		virtual Bool_t  Process(Long64_t entry);
		virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
		virtual void    Terminate();

		void SetPAFSelector(PAFISelector* pafiselector) { fPAFISelector = pafiselector; }
		PAFISelector* GetPAFSelector() { return fPAFISelector; }
		
		void SetSelectorParams(PAFVariableContainer* selectorparams) { fSelectorParams = selectorparams; }
		PAFVariableContainer* GetSelectorParams() { return fSelectorParams; }
		
		template <typename T>
		T FindInput(TString& name);
		
		template <typename T>
		T FindPAFInput(TString& name);
		
		template <typename T>
		T FindPAFInput(const char* name);
		
		TTree* 	        fChain; //!
	
	protected:
		PAFISelector* 			fPAFISelector;
		PAFVariableContainer* 	fSelectorParams;

	ClassDef(PAFBaseSelector, 1);
};

template <typename T>
inline T PAFBaseSelector::FindInput(TString& name)
{
	TObject* tmpobj = 0;
	for(int i = 0; i < fInput->GetEntries(); i++)
	{
		tmpobj = fInput->At(i);
		PAF_DEBUG("PAFBaseSelector", TString::Format("Checking: %s", tmpobj->GetName()).Data());
		if(name.EqualTo(tmpobj->GetName()))
			return (T)tmpobj;
	}
	PAF_ERROR("PAFBaseSelector", "Object not found");
	return NULL;
}

template <typename T>
inline T PAFBaseSelector::FindPAFInput(TString& name)
{
	PAFNamedContainer* result = FindInput<PAFNamedContainer*>(name);
	
	if(!result)
		return NULL;
	
	return (T)result->GetObject();
}

template <typename T>
inline T PAFBaseSelector::FindPAFInput(const char* name)
{
	TString tname(name);
	return FindPAFInput<T>(tname);
}
