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

#include "PAF.h"
#include "PAFFindHelper.h"
#include "PAFIType.h"

class PAFChainItemSelector : public PAFISelector
{
	public:
		PAFChainItemSelector();
		virtual ~PAFChainItemSelector();

		virtual void Initialise();
		virtual void InitialiseParameters();
		virtual void InsideLoop();
		virtual void Summary();

		void SetStaticData(TList* fInput, TSelectorList* fOutput, PAFVariableContainer* selectorParams);
		void SetDynamicData(PAFVariableContainer* variables);

		template<typename T>
		void SetParam(const char* key, T object);

		template<typename T>
		T GetParam(const char* key);
		Int_t GetParamInt(const char* key);
		Float_t GetParamFloat(const char* key);
		Double_t GetParamDouble(const char* key);
		TString GetParamString(const char* key);

		template<typename T>
		void AssignParam(const char* key, T& target);

		template<typename T>
		T Get(const char* key) const;
		Int_t GetInt(const char* key) const;
		Float_t GetFloat(const char* key) const;
		Double_t GetDouble(const char* key) const;

		
		template<typename T>
		T Get(const char* key, Int_t i) const;
		Int_t GetInt(const char* key, Int_t i) const;
		Float_t GetFloat(const char* key, Int_t i) const;
		Double_t GetDouble(const char* key, Int_t i) const;
		
		template<typename T>
		void Assign(const char* key, T& target);
		template<typename T>
		void Assign(const char* key, T& target, Int_t i);
		
		TLeaf* GetLeaf(const char* key);
		TBranch* GetBranch(const char* key);
		Bool_t Exists(const char* key);
		Int_t GetSizeOf(const char* key);

		//Helpers methods

		template<typename T>
		T FindInput(const char* name);

		template<typename T>
		T FindOutput(const char* name);

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
		TList* 			fInput;
		TSelectorList* 		fOutput;
		PAFVariableContainer* 	fVariables; //! Do not stream
		PAFVariableContainer* 	fSelectorParams;

	ClassDef(PAFChainItemSelector, 1);
};

template <typename T>
inline void PAFChainItemSelector::SetParam(const char* key, T object)
{
	fSelectorParams->Add(key, object);
}

template <typename T>
T PAFChainItemSelector::GetParam(const char* key)
{
	return fSelectorParams->Get<T>(key);
}

template <typename T>
void PAFChainItemSelector::AssignParam(const char* key, T& target)
{
	target = GetParam<T>(key);
}

template <typename T>
T PAFChainItemSelector::Get(const char* key) const
{
	T* value = (T*)fVariables->Get<PAFIType*>(key)->GetPointer();
	return *value;
}

template <typename T>
T PAFChainItemSelector::Get(const char* key, Int_t i) const
{
	T* value = (T*)fVariables->Get<PAFIType*>(key)->GetPointer(i);
	return *value;
}

template <typename T>
void PAFChainItemSelector::Assign(const char* key, T& target)
{
	target = Get<T>(key);
}

template <typename T>
void PAFChainItemSelector::Assign(const char* key, T& target, Int_t i)
{
	target = Get<T>(key, i);
}

template <typename T>
T PAFChainItemSelector::FindInput(const char* name)
{
	return PAFFindHelper::Find<T>(fInput, name);
}

template <typename T>
T PAFChainItemSelector::FindOutput(const char* name)
{
	return PAFFindHelper::Find<T>(fOutput, name);
}
