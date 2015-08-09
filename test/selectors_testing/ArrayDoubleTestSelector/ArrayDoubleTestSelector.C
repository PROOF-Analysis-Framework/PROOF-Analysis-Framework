#include "ArrayDoubleTestSelector.h"

#include "PAF.h"

ClassImp(ArrayDoubleTestSelector);

void ArrayDoubleTestSelector::Initialise() 
{
	sHisto = CreateH1D("histogram", "Sum of values", 100, 0., 200.);
}

void ArrayDoubleTestSelector::InsideLoop() 
{
	PAF_DEBUG("Selector", "Reading with syntactic sugar.");
	double result = Get<double>("value", 0) + Get<double>("value", 1);
	PAF_DEBUG("Selector", "Bare metal reading.");
	double resultArray = Get<double*>("value")[0] + Get<double*>("value")[1];
	TLeaf* leaf = GetLeaf("value");
	long entry = leaf->GetBranch()->GetReadEntry();
	if(result == resultArray)
	{
		sHisto->Fill(entry, result);
	}
}
