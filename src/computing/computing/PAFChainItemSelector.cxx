/**
	@brief Abstract class where users should place his own code using inheritance.
	@file PAFChainItemSelector.cxx
	@class PAFChainItemSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
 */

#include "PAFChainItemSelector.h"

ClassImp(PAFChainItemSelector);

PAFChainItemSelector::PAFChainItemSelector()
	: fInput(0), fOutput(0), fVariables(0), fSelectorParams(0) 
{

}

PAFChainItemSelector::~PAFChainItemSelector()
{

}

void PAFChainItemSelector::Initialise()
{

}

void PAFChainItemSelector::InitialiseParameters()
{

}

void PAFChainItemSelector::InsideLoop()
{

}

void PAFChainItemSelector::Summary()
{

}

void PAFChainItemSelector::SetStaticData(TList* input, TSelectorList* output,
					 PAFVariableContainer* selectorParams)
{
	fInput = input;
	fOutput = output;
	fSelectorParams = selectorParams;
}

void PAFChainItemSelector::SetDynamicData(PAFVariableContainer* variables)
{
	fVariables = variables;
}

Int_t PAFChainItemSelector::GetParamInt(const char* key)
{
	return GetParam<int>(key);
}

Float_t PAFChainItemSelector::GetParamFloat(const char* key)
{
	return GetParam<float>(key);
}

Double_t PAFChainItemSelector::GetParamDouble(const char* key)
{
	return GetParam<double>(key);
}

TString PAFChainItemSelector::GetParamString(const char* key)
{
	return GetParam<TString>(key);
}

Int_t PAFChainItemSelector::GetInt(const char* key) const
{
	return Get<int>(key);
}

Float_t PAFChainItemSelector::GetFloat(const char* key) const
{
	return Get<float>(key);
}

Double_t PAFChainItemSelector::GetDouble(const char* key) const
{
	return Get<double>(key);
}

Int_t PAFChainItemSelector::GetInt(const char* key, Int_t i) const
{
	return Get<int>(key, i);
}

Float_t PAFChainItemSelector::GetFloat(const char* key, Int_t i) const
{
	return Get<float>(key, i);
}

Double_t PAFChainItemSelector::GetDouble(const char* key, Int_t i) const
{
	return Get<double>(key, i);
}

TBranch* PAFChainItemSelector::GetBranch(const char* key)
{
	return GetLeaf(key)->GetBranch();
}

TLeaf* PAFChainItemSelector::GetLeaf(const char* key)
{
	PAFIType* variable = fVariables->Get<PAFIType*>(key);
	return variable->GetLeaf();
}

Bool_t PAFChainItemSelector::Exists(const char* key)
{
	return fVariables->Exists(key);
}

Int_t PAFChainItemSelector::GetSizeOf(const char* key)
{
	PAFIType* variable = fVariables->Get<PAFIType*>(key);
	return variable->GetNData();
}

TTree* PAFChainItemSelector::CreateTree(const char* name, const char* title) 
{
	TTree* h = new TTree(name, title);
	fOutput->Add(h);
	return h;
}

TH1F* PAFChainItemSelector::CreateH1F(const char* name, const char* title, 
					Int_t nbinsx, Float_t* bins)
{
	TH1F* result = new TH1F(name, title, nbinsx, bins);
	fOutput->Add(result);
	return result;
}


TH1F* PAFChainItemSelector::CreateH1F(const char* name, const char* title,
					Int_t nbinsx, Double_t* bins)
{
	TH1F* result = new TH1F(name, title, nbinsx, bins);
	fOutput->Add(result);
	return result;
}

TH1F* PAFChainItemSelector::CreateH1F(const char* name, const char* title,
					Int_t nbinsx, Axis_t xlow, Axis_t xup) 
{
	TH1F* result = new TH1F(name, title, nbinsx, xlow, xup);
	fOutput->Add(result);
	return result;
}

TH1D* PAFChainItemSelector::CreateH1D(const char* name, const char* title,
					Int_t nbinsx, Double_t* bins)
{
	TH1D* result = new TH1D(name, title, nbinsx, bins);
	fOutput->Add(result);
	return result;
}

TH1D* PAFChainItemSelector::CreateH1D(const char* name, const char* title, 
					Int_t nbinsx, Axis_t xlow, Axis_t xup)
{
	TH1D* result = new TH1D(name, title, nbinsx, xlow, xup);
	fOutput->Add(result);
	return result;
}

TH2F* PAFChainItemSelector::CreateH2F(const char* name, const char* title,
					Int_t nbinsx, Float_t* xbins, 
					Int_t nbinsy, Float_t* ybins)
{
	TH2F* result = new TH2F(name, title, nbinsx, xbins,nbinsy, ybins);
	fOutput->Add(result);
	return result;
}

TH2F* PAFChainItemSelector::CreateH2F(const char* name, const char* title,
					Int_t nbinsx, Double_t* xbins, 
					Int_t nbinsy, Double_t* ybins)
{
	TH2F* result = new TH2F(name, title, nbinsx, xbins, nbinsy, ybins);
	fOutput->Add(result);
	return result;
}

TH2F* PAFChainItemSelector::CreateH2F(const char* name, const char* title,
					Int_t nbinsx, Double_t* xbins, 
					Int_t nbinsy, Axis_t ylow, Axis_t yup)
{
	TH2F* result = new TH2F(name, title, nbinsx, xbins, nbinsy, ylow, yup);
	fOutput->Add(result);
	return result;
}

TH2F* PAFChainItemSelector::CreateH2F(const char* name, const char* title,
					Int_t nbinsx, Axis_t xlow, Axis_t xup, 
					Int_t nbinsy, Axis_t ylow, Axis_t yup)
{
	TH2F* result = new TH2F(name, title, nbinsx, xlow, xup, nbinsy, ylow, yup);
	fOutput->Add(result);
	return result;
}

TProfile* PAFChainItemSelector::CreateProfile(const char* name, 
						const char* title, Int_t nbinsx, 
						Axis_t xlow, Axis_t xup, 
						Axis_t ylow, Axis_t yup)
{
	TProfile* result = new TProfile(name, title, nbinsx, xlow, xup, ylow, yup);
	fOutput->Add(result);
	return result;
}
