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

void PAFChainItemSelector::SetPROOFData(TList* input, TSelectorList* output)
{
	fInput = input;
	fOutput = output;
}

void PAFChainItemSelector::SetPAFData(PAFVariableContainer* variables, PAFVariableContainer* selectorParams)
{
	fVariables = variables;
	fSelectorParams = selectorParams;
}

TBranch* PAFChainItemSelector::GetBranch(const char* key)
{
	TLeaf* leaf = fVariables->Get<TLeaf*>(key);
	return leaf->GetBranch();
}

TBranch* PAFChainItemSelector::GetBranch(TString& key)
{
	return GetBranch(key.Data());
}

void PAFChainItemSelector::GetBranch(TString& key, TBranch*& target)
{
	target = GetBranch(key);
}

void PAFChainItemSelector::GetBranch(const char* key, TBranch*& target)
{
	target = GetBranch(key);
}

bool PAFChainItemSelector::ExistsBranch(TString& key)
{
	return fVariables->Exists(key);
}

bool PAFChainItemSelector::ExistsBranch(const char* key)
{
	TString tkey(key);
	return  ExistsBranch(tkey);
}

bool PAFChainItemSelector::ExistsVariable(TString& key)
{
	return ExistsBranch(key);
}

bool PAFChainItemSelector::ExistsVariable(const char* key)
{
	return ExistsBranch(key);
}

TObject* PAFChainItemSelector::FindInput(TString& name)
{
	return PAFFindHelper::Find<TObject*>(fInput, name);
}

TObject* PAFChainItemSelector::FindOutput(TString& name)
{
	return PAFFindHelper::Find<TObject*>(fOutput, name);
}

TTree* PAFChainItemSelector::CreateTree(const char* name, const char* title) {
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
									  Int_t nbinsx, Double_t* bins){
	TH1F* result = new TH1F(name, title, nbinsx, bins);
	fOutput->Add(result);
	return result;
}

TH1F* PAFChainItemSelector::CreateH1F(const char* name, const char* title,
									  Int_t nbinsx, Axis_t xlow, Axis_t xup) {
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





