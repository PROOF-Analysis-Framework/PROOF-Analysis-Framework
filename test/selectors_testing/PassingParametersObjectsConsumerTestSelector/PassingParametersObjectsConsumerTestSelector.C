#include "PassingParametersObjectsConsumerTestSelector.h"

#include <vector>

ClassImp(PassingParametersObjectsConsumerTestSelector);

void PassingParametersObjectsConsumerTestSelector::Initialise() 
{
	sHisto = CreateH1D("histogram", "Sum of values", 100, 0., 200.);
}

void PassingParametersObjectsConsumerTestSelector::InsideLoop() 
{
	TLeaf* leaf = GetLeaf("value");
	long entry = leaf->GetBranch()->GetReadEntry();
	std::vector<Double_t>* result = GetParam<std::vector<Double_t>*>("result_object");
	sHisto->Fill(entry, result->at(0));
}
