#include "PrimitiveLongTestSelector.h"

ClassImp(PrimitiveLongTestSelector);

void PrimitiveLongTestSelector::Initialise() 
{
	sHisto = CreateH1D("histogram", "Sum of values", 100, 0., 200.);
}

void PrimitiveLongTestSelector::InsideLoop() 
{
	TLeaf* leaf = GetLeaf("value");
	long entry = leaf->GetBranch()->GetReadEntry();
	sHisto->Fill(entry, Get<long>("value"));
}
