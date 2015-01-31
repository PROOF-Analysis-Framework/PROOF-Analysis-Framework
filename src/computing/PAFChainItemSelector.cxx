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

TTree* PAFChainItemSelector::CreateTree(const char* name, const char* title) {
	TTree* h = new TTree(name, title);
	fOutput->Add(h);
	return h;
}

TH1F* PAFChainItemSelector::CreateH1F(const char* name, const char* title,
					Int_t nbinsx, Double_t* bins){
	TH1F* result = new TH1F(name, title, nbinsx, bins);
	fOutput->Add(result);
	return result;
}

TH1F* PAFChainItemSelector::CreateH1F(const char* name, const char* title,
                                     Int_t nbinsx, Axis_t xlow, Axis_t xup) {
	TH1F* h = new TH1F(name, title, nbinsx, xlow, xup);
	fOutput->Add(h);
	return h;
}

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
