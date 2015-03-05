#include "TSelector.h"
#include "TCanvas.h"

void RunPAFAnalysis() {
	gSystem->Load("libPAF.so");
	
	PAFProject* myProject = new PAFProject();
	myProject->AddDataFile("/home/javier/Documents/Tree_ZJets_Madgraph_0.root");
	myProject->AddSelectorPackage("MyAnalysis");
	myProject->Run();
}