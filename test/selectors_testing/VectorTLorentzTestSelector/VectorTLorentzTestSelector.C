#include "VectorTLorentzTestSelector.h"

#include "TLorentzVector.h"

#include <iostream>

ClassImp(VectorTLorentzTestSelector);

void VectorTLorentzTestSelector::Initialise() 
{
	sHisto = CreateH1D("histogram", "Sum of values", 100, 0., 200.);
}

void VectorTLorentzTestSelector::InsideLoop() 
{
	TLeaf* leaf = GetLeaf("value");
	long entry = leaf->GetBranch()->GetReadEntry();

	TLorentzVector* v = Get<TLorentzVector*>("value");

	sHisto->Fill(entry + 1, v->X() + v->Y() + v->Z() + v->T());
}
