#include "GetSizeOfTestSelector.h"

ClassImp(GetSizeOfTestSelector);

#include <iostream>

void GetSizeOfTestSelector::Initialise() 
{
	sHisto = CreateH1D("histogram", "Sum of values", 100, 0., 200.);
}

void GetSizeOfTestSelector::InsideLoop() 
{
	TLeaf* leaf = GetLeaf("value");
	long entry = leaf->GetBranch()->GetReadEntry();

	if(GetSizeOf("value") == entry)
	{
		sHisto->Fill(entry, 1);
	}
}
