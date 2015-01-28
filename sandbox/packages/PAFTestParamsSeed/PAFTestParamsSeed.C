#include "PAFTestParamsSeed.h"

#include "TString.h"

#include "../PAF/PAF.h"

ClassImp(PAFTestParamsSeed);

void PAFTestParamsSeed::Initialise()
{
	fRandom = new TRandom3(0);
}

void PAFTestParamsSeed::InsideLoop()
{
	SetParam("random", fRandom->Gaus(0.,1.));
}
