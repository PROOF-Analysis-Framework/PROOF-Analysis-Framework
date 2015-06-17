#include "GetSizeOfDoubleTestSelector.h"

ClassImp(GetSizeOfDoubleTestSelector);

void GetSizeOfDoubleTestSelector::Initialise() 
{
	sHisto = CreateH1D("histogram", "Sum of values", 100, 0., 200.);
}

void GetSizeOfDoubleTestSelector::InsideLoop() 
{
	TLeaf* leaf = GetLeaf("value");
	long entry = leaf->GetBranch()->GetReadEntry();

	if(GetSizeOf("value") == entry|| 
		GetSizeOf("value") == Get<std::vector<double>*>("value")->size())
	{
		sHisto->Fill(entry, 1);
	}
}
