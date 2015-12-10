#include "PassingParametersObjectsSeedTestSelector.h"

#include <vector>

ClassImp(PassingParametersObjectsSeedTestSelector);

void PassingParametersObjectsSeedTestSelector::InsideLoop() 
{
	std::vector<Double_t>* vector = new std::vector<Double_t>();
	vector->push_back(Get<Double_t>("value"));
	SetParam("result_object", vector);
}
