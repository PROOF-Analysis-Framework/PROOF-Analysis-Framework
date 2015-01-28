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
		PAFChainItemSelector() : fInput(0), fOutput(0), fData(0), fSelectorParams(0) {}
		virtual ~PAFChainItemSelector() {}
		
		virtual void Initialise() {}
		virtual void InitialiseParameters() {}
		virtual void InsideLoop() {}
		virtual void Summary() {}	

		void SetPROOFData(TList* input, TSelectorList* output);
		void SetPAFData(PAFAnalysis* data, PAFVariableContainer* selectorParams);

		TTree* CreateTree(const char* name, const char* title);

		TObject* FindOutput(TString name, TString classname = "");
		TObject* FindInput(TString name, TString classname = "");

		TObject* FindOutputByClassName(TString classname);
		
		template<typename T>
		T GetParam(TString& key);
		
		template<typename T>
		void GetParam(const char* key, T& target);
		
		template<typename T>
		void GetParam(TString& key, T& target);
		
		template<typename T>
		T GetParam(const char* key);
		
		template<typename T>
		void SetParam(TString& key, T object);

		template<typename T>
		void SetParam(const char* key, T object);
		
	protected:		
		TList* fInput;
		TSelectorList* fOutput;
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
inline T PAFChainItemSelector::GetParam(const char* key)
{
	TString tkey(key);
	return GetParam<T>(tkey);
}

template <typename T>
inline void PAFChainItemSelector::GetParam(TString& key, T& target)
{
	target = GetParam<T>(key);
}

template <typename T>
inline void PAFChainItemSelector::GetParam(const char* key, T& target)
{
	TString tkey(key);
	GetParam(tkey, target);
}


template <typename T>
inline void PAFChainItemSelector::SetParam(TString& key, T object)
{
	fSelectorParams->Add(key, object);
}

template <typename T>
inline void PAFChainItemSelector::SetParam(const char* key, T object)
{
	TString tkey(key);
	SetParam(tkey, object);
}
