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
		Double_t x = 0;
		GetParam("random", x);
		if(x > GetParam<int>("min") )
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


