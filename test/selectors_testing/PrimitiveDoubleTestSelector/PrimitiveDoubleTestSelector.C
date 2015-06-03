#include "PrimitiveDoubleTestSelector.h"

ClassImp(PrimitiveDoubleTestSelector);

void PrimitiveDoubleTestSelector::Initialise() 
{
	sHisto = CreateH1D("histogram", "Sum of values", 100, 0., 200.);
}

void PrimitiveDoubleTestSelector::InsideLoop() 
{
	TLeaf* leaf = GetLeaf("value");
	long entry = leaf->GetBranch()->GetReadEntry();
	sHisto->Fill(entry, Get<double>("value"));
}
