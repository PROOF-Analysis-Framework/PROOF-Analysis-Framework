#include "VectorDoubleTestSelector.h"

ClassImp(VectorDoubleTestSelector);

void VectorDoubleTestSelector::Initialise() 
{
	sHisto = CreateH1D("histogram", "Sum of values", 100, 0., 200.);
}

void VectorDoubleTestSelector::InsideLoop() 
{
	TLeaf* leaf = GetLeaf("value");
	long entry = leaf->GetBranch()->GetReadEntry();
	sHisto->Fill(entry, Get<double>("value", 0));
}
