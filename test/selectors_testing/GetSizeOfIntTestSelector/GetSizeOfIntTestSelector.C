#include "GetSizeOfIntTestSelector.h"

ClassImp(GetSizeOfIntTestSelector);

void GetSizeOfIntTestSelector::Initialise() 
{
	sHisto = CreateH1D("histogram", "Sum of values", 100, 0., 200.);
}

void GetSizeOfIntTestSelector::InsideLoop() 
{
	TLeaf* leaf = GetLeaf("value");
	long entry = leaf->GetBranch()->GetReadEntry();

	if(GetSizeOf<int>("value") == entry || 
		GetSizeOf<int>("value") == Get<std::vector<int>*>("value")->size())
	{
		sHisto->Fill(entry, 1);
	}
}
