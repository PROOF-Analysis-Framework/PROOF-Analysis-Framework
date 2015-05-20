/**
	@brief Internal PAF class to create the required TSelector in Proof.
	@file PAFBaseSelector.h
	@class PAFBaseSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#pragma once

#include "TTree.h"
#include "TSelector.h"
#include "TString.h"

#include "PAFISelector.h"
#include "../variable_container/PAFVariableContainer.h"

#include "../PAF.h"

class PAFBaseSelector : public TSelector {
	public:
		PAFBaseSelector() : fTree(0), fPAFISelector(0), fSelectorParams(0), fVariables(0) { }
		virtual ~PAFBaseSelector();
		virtual Int_t   Version() const { return 2; }
		virtual void 	Init(TTree* tree);
		virtual void    SlaveBegin(TTree* tree);
		virtual Bool_t  Process(Long64_t entry);
		virtual void    Terminate();

		void SetPAFSelector(PAFISelector* pafiselector) { fPAFISelector = pafiselector; }
		PAFISelector* GetPAFSelector() { return fPAFISelector; }
		
		void SetSelectorParams(PAFVariableContainer* selectorparams) { fSelectorParams = selectorparams; }
		PAFVariableContainer* GetSelectorParams() { return fSelectorParams; }

		void SetOutputFile(const TString& fOutputFile);
		TString GetOutputFile();

	protected:
		TTree*			fTree;
		PAFISelector*		fPAFISelector;
		PAFVariableContainer*	fSelectorParams;
		PAFVariableContainer*	fVariables;//!
		TString		fOutputFile;

	ClassDef(PAFBaseSelector, 1);
};
