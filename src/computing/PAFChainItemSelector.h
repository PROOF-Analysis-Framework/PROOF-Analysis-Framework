/**
	@brief Abstract class where the users should place his own code using inheritance.
	@file PAFChainItemSelector.h
	@class PAFChainItemSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#pragma once

#include <TH1F.h>

#include <TTree.h>
#include <TObject.h>

#include "PAFISelector.h"

class PAFChainItemSelector : public PAFISelector
{
	public:
		PAFChainItemSelector() : fInput(0), fOutput(0), fInputParameters(0), fData(0), fSelectorParams(0) {}
		virtual ~PAFChainItemSelector() {}
		
		virtual void Initialise() {}
		virtual void InitialiseParameters() {}
		virtual void InsideLoop() {}
		virtual void Summary() {}	

		void SetPROOFData(TList* input, TSelectorList* output);
		void SetPAFData(InputParameters* inputParameters, PAFAnalysis* data, PAFVariableContainer* selectorParams);

	/*	TCounterUI* InitCounterUI(const char* name, const char* title,
                            unsigned int init);
*/
		TTree* CreateTree(const char* name, const char* title);

		TObject* FindOutput(TString name, TString classname = "");
		TObject* FindInput(TString name, TString classname = "");

		TObject* FindOutputByClassName(TString classname);
		
		template<typename T>
		T GetParam(TString& key);
		
		template<typename T>
		void GetParam(TString& key, T& target);
		
		template<typename T>
		void SetParam(TString& key, T object);
		
	protected:		
		TList* fInput;
		TSelectorList* fOutput;
		InputParameters* fInputParameters; //! Do not stream
		PAFAnalysis* fData; //! Do not stream
		PAFVariableContainer* fSelectorParams;
		
		//bool fMergeThroughFile;
		//TCounterUI* fNEventsProcessed;
		//bool fPrintInputParameters;
		TH1F* CreateH1F(const char* name, const char* title,
				Int_t nbinsx, Double_t* bins);
		TH1F* CreateH1F(const char* name, const char* title,
                  Int_t nbinsx, Axis_t xlow, Axis_t xup);

	ClassDef(PAFChainItemSelector, 1);
};

template <typename T>
inline T PAFChainItemSelector::GetParam(TString& key)
{
	return fSelectorParams->Get<T>(key);
}

template <typename T>
inline void PAFChainItemSelector::GetParam(TString& key, T& target)
{
	target = GetParam<T>(key);
}

template <typename T>
inline void PAFChainItemSelector::SetParam(TString& key, T object)
{
	fSelectorParams->Add(key, object);
}
