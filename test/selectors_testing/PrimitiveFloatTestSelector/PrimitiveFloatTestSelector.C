#include "PrimitiveFloatTestSelector.h"

ClassImp(PrimitiveFloatTestSelector);

void PrimitiveFloatTestSelector::Initialise() 
{
	sHisto = CreateH1D("histogram", "Sum of values", 100, 0., 200.);
}

void PrimitiveFloatTestSelector::InsideLoop() 
{
	TLeaf* leaf = GetLeaf("value");
	long entry = leaf->GetBranch()->GetReadEntry();
	sHisto->Fill(entry, Get<float>("value"));
}
