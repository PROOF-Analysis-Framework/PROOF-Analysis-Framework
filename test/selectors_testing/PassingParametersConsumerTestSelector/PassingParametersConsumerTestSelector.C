#include "PassingParametersConsumerTestSelector.h"

ClassImp(PassingParametersConsumerTestSelector);

void PassingParametersConsumerTestSelector::Initialise() 
{
	sHisto = CreateH1D("histogram", "Sum of values", 100, 0., 200.);
}

void PassingParametersConsumerTestSelector::InsideLoop() 
{
	TLeaf* leaf = GetLeaf("value");
	long entry = leaf->GetBranch()->GetReadEntry();
	sHisto->Fill(entry, GetParam<Double_t>("result_double"));
}
