#include "GetSizeOfBoolTestSelector.h"

ClassImp(GetSizeOfBoolTestSelector);

void GetSizeOfBoolTestSelector::Initialise() 
{
	sHisto = CreateH1D("histogram", "Sum of values", 100, 0., 200.);
}

void GetSizeOfBoolTestSelector::InsideLoop() 
{
	TLeaf* leaf = GetLeaf("value");
	long entry = leaf->GetBranch()->GetReadEntry();

	if(GetSizeOf("value") == entry || 
		GetSizeOf("value") == Get<std::vector<int>*>("value")->size())
	{
		sHisto->Fill(entry, 1);
	}
}
