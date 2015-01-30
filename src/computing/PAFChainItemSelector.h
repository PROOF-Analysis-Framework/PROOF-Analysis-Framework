/**
	@brief Abstract class where the users should place his own code using inheritance.
	@file PAFChainItemSelector.h
	@class PAFChainItemSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#pragma once

#include "TLeaf.h"
#include "TString.h"

#include "TH1F.h"
#include "TTree.h"

#include "PAFISelector.h"
#include "../PAF.h"

class PAFChainItemSelector : public PAFISelector
{
	public:
		PAFChainItemSelector() : fInput(0), fOutput(0), fVariables(0), fSelectorParams(0) {}
		virtual ~PAFChainItemSelector() {}
		
		virtual void Initialise() {}
		virtual void InitialiseParameters() {}
		virtual void InsideLoop() {}
		virtual void Summary() {}	

		void SetPROOFData(TList* input, TSelectorList* output);
		void SetPAFData(PAFVariableContainer* variables, PAFVariableContainer* selectorParams);

		template<typename T>
		T GetParam(TString& key);
		template<typename T>
		T GetParam(const char* key);
		
		template<typename T>
		void GetParam(TString& key, T& target);	
		template<typename T>
		void GetParam(const char* key, T& target);	
		
		template<typename T>
		void SetParam(TString& key, T object);
		template<typename T>
		void SetParam(const char* key, T object);
		
		template<typename T>
		T GetVariable(TString& key);
		template<typename T>
		T GetVariable(const char* key);
		
		template<typename T>
		void GetVariable(TString& key, T& target);
		template<typename T>
		void GetVariable(const char* key, T& target);
		
		TBranch* GetBranch(TString& key);
		TBranch* GetBranch(const char* key);
		
		void GetBranch(TString& key, TBranch*& branch);
		void GetBranch(const char* key, TBranch*& branch);
		
	protected:		
		TList* 					fInput;
		TSelectorList* 			fOutput;
		PAFVariableContainer* 	fVariables; //! Do not stream
		PAFVariableContainer* 	fSelectorParams;

		TH1F* CreateH1F(const char* name, const char* title,
				Int_t nbinsx, Double_t* bins);
		TH1F* CreateH1F(const char* name, const char* title,
                  Int_t nbinsx, Axis_t xlow, Axis_t xup);
		TTree* CreateTree(const char* name, const char* title);

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
	target = GetParam<T>(key);
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

template <typename T>
T PAFChainItemSelector::GetVariable(TString& key)
{
	return GetVariable<T>(key.Data());
}

template <typename T>
T PAFChainItemSelector::GetVariable(const char* key)
{
	TLeaf* leaf = fVariables->Get<TLeaf*>(key);
	return leaf->GetTypedValue<T>();
}

template <typename T>
inline void PAFChainItemSelector::GetVariable(TString& key, T& target)
{
	target = GetVariable<T>(key.Data());
}

template <typename T>
inline void PAFChainItemSelector::GetVariable(const char* key, T& target)
{
	target = GetVariable<T>(key);
}