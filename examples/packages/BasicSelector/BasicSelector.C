#include "BasicSelector.h"

#include "TCanvas.h"

ClassImp(BasicSelector);

void BasicSelector::Initialise() 
{
	etHisto = CreateH1F("etHistogram","#slash{E}_{T}", 100, 0., 200.);
}

void BasicSelector::InsideLoop() 
{
	float t_metpf_et = Get<float>("T_METgen_ET");
	etHisto->Fill(t_metpf_et);
}

void BasicSelector::Summary()
{
	TCanvas* canvas = new TCanvas("canvas", "Proof ProofFirst canvas", 200, 10, 400, 400);
	TH1F* result = FindOutput<TH1F*>("etHistogram");
	result->Draw();
	canvas->Update();
}
