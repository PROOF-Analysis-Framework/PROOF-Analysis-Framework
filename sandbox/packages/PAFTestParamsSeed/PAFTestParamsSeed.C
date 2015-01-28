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
	TString t("random");
	SetParam(t, fRandom->Gaus(0.,1.));
}
