#include "PAFSimpleSelector.h"
#include "TCanvas.h"

ClassImp(PAFSimpleSelector);

void PAFSimpleSelector::Initialise()
{
	fH1F = new TH1F("FirstH1F", "First TH1F in PROOF", 100, -10., 10.);
   	fOutput->Add(fH1F);

	fRandom = new TRandom3(0);
}

void PAFSimpleSelector::InsideLoop()
{
   if (fRandom && fH1F) {
		Double_t x = fRandom->Gaus(0.,1.);
		fH1F->Fill(x);
   }
}

void PAFSimpleSelector::Summary()
{
	TCanvas* c1 = new TCanvas("c1", "Proof ProofFirst canvas",200,10,400,400);
	fH1F = dynamic_cast<TH1F *>(fOutput->FindObject("FirstH1F"));
	if (fH1F) fH1F->Draw();
	c1->Update();
}


