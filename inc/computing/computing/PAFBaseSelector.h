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
#include "PAFVariableContainer.h"

#include "PAF.h"

class PAFBaseSelector : public TSelector 
{
	public:
		PAFBaseSelector();
		virtual ~PAFBaseSelector();
		virtual Int_t   Version() const;
		virtual void 	Init(TTree* tree);
		virtual void    SlaveBegin(TTree* tree);
		virtual Bool_t  Process(Long64_t entry);
		virtual void    Terminate();

		void SetPAFSelector(PAFISelector* pafiselector);
		PAFISelector* GetPAFSelector();

		void SetSelectorParams(PAFVariableContainer* selectorparams);
		PAFVariableContainer* GetSelectorParams();

		void SetOutputFile(const TString& fOutputFile);
		TString GetOutputFile();

	protected:
		TTree*			fTree;
		PAFISelector*		fPAFISelector;
		PAFVariableContainer*	fSelectorParams;
		PAFVariableContainer*	fVariables;//!
		TString			fOutputFile;

	ClassDef(PAFBaseSelector, 1);
};
