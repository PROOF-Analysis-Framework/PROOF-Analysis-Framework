#include "PrimitiveIntTestSelector.h"

ClassImp(PrimitiveIntTestSelector);

void PrimitiveIntTestSelector::Initialise() 
{
	sHisto = CreateH1D("histogram", "Sum of values", 100, 0., 200.);
}

void PrimitiveIntTestSelector::InsideLoop() 
{
	TLeaf* leaf = GetLeaf("value");
	long entry = leaf->GetBranch()->GetReadEntry();
	sHisto->Fill(entry, Get<int>("value"));
}
