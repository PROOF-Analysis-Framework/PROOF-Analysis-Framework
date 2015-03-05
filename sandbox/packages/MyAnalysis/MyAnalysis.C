#include "MyAnalysis.h"

#include "TCanvas.h"

ClassImp(MyAnalysis)

void MyAnalysis::Initialise() {
	myHistogram = CreateH1F("myHistogram","#slash{E}_{T}", 100, 0., 200.);
}

void MyAnalysis::InsideLoop() {
	myHistogram->Fill( GetFloat("T_METPF_ET") );
}

void MyAnalysis::Summary() {
    TCanvas* c1 = new TCanvas("c1", "myHistogram canvas",200,10,400,400);
    myHistogram = dynamic_cast<TH1F*>(fOutput->FindObject("myHistogram"));
    if (myHistogram) myHistogram->Draw();
    c1->Update();
}