#include "PAFTestParamsPrinter.h"
#include "TCanvas.h"

ClassImp(PAFTestParamsPrinter);

void PAFTestParamsPrinter::Initialise()
{
	fH1F = new TH1F("FirstH1F", "First TH1F in PROOF", 100, -10., 10.);
   	fOutput->Add(fH1F);
}

void PAFTestParamsPrinter::InsideLoop()
{
   if (fH1F) {
		TString t("random");
		Double_t x = GetParam<Double_t>(t);
		if(x > 0.4)
			fH1F->Fill(x);
   }
}

void PAFTestParamsPrinter::Summary()
{
	TCanvas* c1 = new TCanvas("c1", "Proof ProofFirst canvas",200,10,400,400);
	fH1F = dynamic_cast<TH1F *>(fOutput->FindObject("FirstH1F"));
	if (fH1F) fH1F->Draw();
	c1->Update();
}


