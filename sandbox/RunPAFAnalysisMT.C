#include "TSelector.h"
#include "TCanvas.h"

void RunPAFAnalysisMT() 
{
	gSystem->Load("libPAF.so");
	//PAFProject* myProject = new PAFProject(new PAFPoDEnvironment());
	PAFProject* myProject = new PAFProject(new PAFPROOFLiteEnvironment(4));
	//PAFProject* myProject = new PAFProject(new PAFSequentialEnvironment());

	//myProject->AddDynamicHistogram("etHistogram");
	//myProject->AddDynamicHistogram("phiHistogram");
	//myProject->AddDynamicHistogram("sigHistogram");

	myProject->AddDataFile("/Users/javier/Documents/Tree_ZJets_Madgraph_0.root");
	//myProject->AddDataFile("/pool/ciencias/MC_Summer12_53X/Legacy/Tree_ZJets_Madgraph_0.root");
	//myProject->AddDataFile("/pool/ciencias/MC_Summer12_53X/Legacy/Tree_ZJets_Madgraph_1.root");
	//myProject->AddDataFile("/pool/ciencias/MC_Summer12_53X/Legacy/Tree_ZJets_Madgraph_2.root");

	myProject->AddSelectorPackage("Benchmark");
	
	myProject->Run();
}
