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

int PAFChainItemSelector::GetParamInt(const char* key)
{
	return GetParam<int>(key);
}

float PAFChainItemSelector::GetParamFloat(const char* key)
{
	return GetParam<float>(key);
}

double PAFChainItemSelector::GetParamDouble(const char* key)
{
	return GetParam<double>(key);
}

TString PAFChainItemSelector::GetParamString(const char* key)
{
	return GetParam<TString>(key);
}
int PAFChainItemSelector::GetInt(const char* key)
{
	return Get<int>(key);
}

float PAFChainItemSelector::GetFloat(const char* key)
{
	return Get<float>(key);
}

double PAFChainItemSelector::GetDouble(const char* key)
{
	return Get<double>(key);
}

int PAFChainItemSelector::GetInt(const char* key, int i)
{
	return Get<int>(key, i);
}

float PAFChainItemSelector::GetFloat(const char* key, int i)
{
	return Get<float>(key, i);
}

double PAFChainItemSelector::GetDouble(const char* key, int i)
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

bool PAFChainItemSelector::Exists(const char* key)
{
	return fVariables->Exists(key);
}

int PAFChainItemSelector::GetSizeOf(const char* key)
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
