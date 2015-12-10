#include "PassingParametersSeedTestSelector.h"

ClassImp(PassingParametersSeedTestSelector);

void PassingParametersSeedTestSelector::InsideLoop() 
{
	SetParam("result_double", Get<Double_t>("value"));
}
