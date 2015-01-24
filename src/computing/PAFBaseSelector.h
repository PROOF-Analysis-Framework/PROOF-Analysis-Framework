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

#include "PAFISelector.h"
#include "../input_parameters/InputParameters.h"

class PAFAnalysis;

class PAFBaseSelector : public TSelector {
	public:
		PAFBaseSelector() : fChain(0), fInputParameters(0), fPAFISelector(0)  { }
		virtual ~PAFBaseSelector() { }
		virtual Int_t   Version() const { return 2; }
		virtual void    SlaveBegin(TTree* tree);
		virtual Bool_t  Notify() { return kTRUE; }
		virtual Bool_t  Process(Long64_t entry);
		virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
		virtual void    Terminate();

		PAFISelector* GetPAFSelector() { return fPAFISelector; }
		void SetPAFSelector(PAFISelector* selector) { fPAFISelector = selector; }

		InputParameters* GetInputParameters() { return fInputParameters; }
		void SetInputParameters(InputParameters* inputparameters) { fInputParameters = inputparameters; }

		TObject* FindInput(TString name, TString classname = "");

		TTree* 	        fChain; //!
	
	protected:
		InputParameters*	fInputParameters;
		PAFISelector* 		fPAFISelector;

	ClassDef(PAFBaseSelector, 1);
};

