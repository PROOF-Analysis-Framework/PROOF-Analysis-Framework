#include "VariablePainter.h"

#include "TCanvas.h"

ClassImp(VariablePainter)

void VariablePainter::Initialise() {
	myHistogram = CreateH1F("myHistogram","MyHistogram", 100, 0., 200.);
}

void VariablePainter::InsideLoop() {
	float result = GetParamFloat("Result");
	myHistogram->Fill(result);
}

void VariablePainter::Summary() {
	TCanvas* canvas = new TCanvas("canvas", "Proof ProofFirst canvas", 200, 10, 400, 400);
	TH1F* result = (TH1F*)FindOutput("myHistogram");
	result->Draw();
	canvas->Update();
}