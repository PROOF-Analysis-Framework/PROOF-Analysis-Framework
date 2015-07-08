#include "ArrayDoubleTestSelector.h"

ClassImp(ArrayDoubleTestSelector);

void ArrayDoubleTestSelector::Initialise() 
{
	sHisto = CreateH1D("histogram", "Sum of values", 100, 0., 200.);
}

void ArrayDoubleTestSelector::InsideLoop() 
{
	TLeaf* leaf = GetLeaf("value");
	long entry = leaf->GetBranch()->GetReadEntry();
	double result = Get<double>("value", 0) + Get<double>("value", 1);
	double resultArray = Get<double*>("value")[0] + Get<double*>("value")[1];
	if(result == resultArray)
	{
		sHisto->Fill(entry, result);
	}
}
