/**
	@brief Abstract class where users should place his own code using inheritance.
	@file PAFChainItemSelector.h
	@class PAFChainItemSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#pragma once

#include "PAFISelector.h"

#include <vector>

#include "TLeaf.h"
#include "TString.h"

#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TTree.h"

#include "../computing_helpers/PAFFindHelper.h"

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

		void SetStaticData(TList* fInput, TSelectorList* fOutput, PAFVariableContainer* selectorParams);
		void SetDynamicData(PAFVariableContainer* variables);

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
		
		template<typename T>
		T GetVariableAt(TString& key, unsigned int i);
		template<typename T>
		T GetVariableAt(const char* key, unsigned int i);
		
		template<typename T>
		void GetVariableAt(TString& key, unsigned int i, T& target);
		template<typename T>
		void GetVariableAt(const char* key, unsigned int i, T& target);
		
		
		TBranch* GetBranch(TString& key);
		TBranch* GetBranch(const char* key);
		
		void GetBranch(TString& key, TBranch*& branch);
		void GetBranch(const char* key, TBranch*& branch);
		
		bool ExistsVariable(TString& key);
		bool ExistsVariable(const char* key);
		
		bool ExistsBranch(TString& key);
		bool ExistsBranch(const char* key);

		//Helpers methods
		
		TObject* FindInput(TString& name);
		TObject* FindOutput(TString& name);
		
		TTree* CreateTree(const char* name, const char* title);

		TH1F* CreateH1F(const char* name, const char* title, 
						Int_t nbinsx, Axis_t xlow, Axis_t xup);
		TH1F* CreateH1F(const char* name, const char* title,
						Int_t nbinsx, Float_t* bins);
		TH1F* CreateH1F(const char* name, const char* title,
						Int_t nbinsx, Double_t* bins);

		TH1D* CreateH1D(const char* name, const char* title,
						Int_t nbinsx, Axis_t xlow, Axis_t xup);
		TH1D* CreateH1D(const char* name, const char* title,
						Int_t nbinsx, Double_t* bins);

		TH2F* CreateH2F(const char* name, const char* title,
						Int_t nbinsx, Float_t* xbins,
						Int_t nbinsy, Float_t* ybins);
		TH2F* CreateH2F(const char* name, const char* title,
						Int_t nbinsx, Double_t* xbins,
						Int_t nbinsy, Double_t* ybins);
		TH2F* CreateH2F(const char* name, const char* title,
						Int_t nbinsx, Double_t* xbins,
						Int_t nbinsy, Axis_t ylow, Axis_t yup);
		TH2F* CreateH2F(const char* name, const char* title,
						Int_t nbinsx, Axis_t xlow, Axis_t xup,
						Int_t nbinsy, Axis_t ylow, Axis_t yup);
  
		TProfile* CreateProfile(const char* name, const char* title,
						Int_t nbinsx, Axis_t xlow, Axis_t xup,
						Axis_t ylow, Axis_t yup);
		
	protected:		
		TList* 					fInput;
		TSelectorList* 			fOutput;
		PAFVariableContainer* 	fVariables; //! Do not stream
		PAFVariableContainer* 	fSelectorParams;

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
	TBranch* branch = leaf->GetBranch();
	
	if(branch->TestBit(kDoNotProcess)){
		PAF_DEBUG("PAFChainItemSelector", TString::Format("Loading variable: %s", key));
		branch->SetStatus(kTRUE);
		branch->GetEntry(branch->GetReadEntry());
	}

	void* result = branch->GetAddress() ? branch->GetAddress() : leaf->GetValuePointer();
	return *((T*)result);
}

template <typename T>
T PAFChainItemSelector::GetVariableAt(TString& key, unsigned int i)
{
	return GetVariable<T>(key.Data(), i);
}

template <typename T>
T PAFChainItemSelector::GetVariableAt(const char* key, unsigned int i)
{
	std::vector<T>* vector_result = GetVariable<std::vector<T>*>(key);
	return vector_result->at(i);
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

template <typename T>
void PAFChainItemSelector::GetVariableAt(TString& key, unsigned int i, T& target)
{
	target = GetVariable<T>(key, i);
}

template <typename T>
void PAFChainItemSelector::GetVariableAt(const char* key, unsigned int i, T& target)
{
	target = GetVariable<T>(key, i);
}
