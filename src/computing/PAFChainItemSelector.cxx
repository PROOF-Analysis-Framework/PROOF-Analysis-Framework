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

int PAFChainItemSelector::GetParamInt(TString& key)
{
	return GetParam<int>(key);
}

int PAFChainItemSelector::GetParamInt(const char* key)
{
	TString tKey(key);
	return GetParamInt(key);
}


float PAFChainItemSelector::GetParamFloat(TString& key)
{
	return GetParam<float>(key);
}

float PAFChainItemSelector::GetParamFloat(const char* key)
{
	TString tKey(key);
	return GetParamFloat(tKey);
}

double PAFChainItemSelector::GetParamDouble(TString& key)
{
	return GetParam<double>(key);
}

double PAFChainItemSelector::GetParamDouble(const char* key)
{
	TString tKey(key);
	return GetParamDouble(tKey);
}

TString PAFChainItemSelector::GetParamString(TString& key)
{
	return GetParam<TString>(key);
}

TString PAFChainItemSelector::GetParamString(const char* key)
{
	TString tKey(key);
	return GetParamString(tKey);
}

int PAFChainItemSelector::GetInt(TString& key)
{
	return Get<int>(key);
}

int PAFChainItemSelector::GetInt(const char* key)
{
	TString tKey(key);
	return GetInt(tKey);
}

float PAFChainItemSelector::GetFloat(TString& key)
{
	return Get<float>(key);
}

float PAFChainItemSelector::GetFloat(const char* key)
{
	TString tKey(key);
	return GetFloat(tKey);
}

double PAFChainItemSelector::GetDouble(TString& key)
{
	return Get<double>(key);
}

double PAFChainItemSelector::GetDouble(const char* key)
{
	TString tKey(key);
	return Get<double>(tKey);
}

int PAFChainItemSelector::GetInt(TString& key, unsigned int i)
{
	return Get<int>(key, i);
}

int PAFChainItemSelector::GetInt(const char* key, unsigned int i)
{
	TString tKey(key);
	return GetInt(tKey, i);
}

float PAFChainItemSelector::GetFloat(TString& key, unsigned int i)
{
	return Get<float>(key, i);
}

float PAFChainItemSelector::GetFloat(const char* key, unsigned int i)
{
	TString tKey(key);
	return GetFloat(tKey, i);
}

double PAFChainItemSelector::GetDouble(TString& key, unsigned int i)
{
	return Get<double>(key, i);
}

double PAFChainItemSelector::GetDouble(const char* key, unsigned int i)
{
	TString tKey(key);
	return GetDouble(tKey, i);
}

TBranch* PAFChainItemSelector::GetBranch(TString& key)
{
	return GetLeaf(key)->GetBranch();
}

TBranch* PAFChainItemSelector::GetBranch(const char* key)
{
	TString tKey(key);
	return GetBranch(tKey);
}

TLeaf* PAFChainItemSelector::GetLeaf(TString& key)
{
	TLeaf* result = fVariables->Get<TLeaf*>(key);
	TBranch* branch = result->GetBranch();
	
	if(branch->TestBit(kDoNotProcess)){
		PAF_DEBUG("PAFChainItemSelector", TString::Format("Loading variable: %s", key.Data()));
		branch->SetStatus(kTRUE);
		branch->GetEntry(branch->GetReadEntry());
	}
	
	return result;
}

TLeaf* PAFChainItemSelector::GetLeaf(const char* key)
{
	TString tKey(key);
	return GetLeaf(tKey);
}

bool PAFChainItemSelector::Exists(TString& key)
{
	return fVariables->Exists(key);
}

bool PAFChainItemSelector::Exists(const char* key)
{
	TString tkey(key);
	return  Exists(tkey);
}

unsigned int PAFChainItemSelector::GetSizeOf(TString& key)
{
	return Get<std::vector<void*>*>(key)->size();
}

unsigned int PAFChainItemSelector::GetSizeOf(const char* key)
{
	TString tKey(key);
	return GetSizeOf(tKey);
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





