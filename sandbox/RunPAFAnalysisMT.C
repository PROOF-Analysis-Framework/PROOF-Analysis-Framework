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
	myProject->AddDynamicHistogram("sigHistogram");

	myProject->AddDataFile("/home/javier/Documents/Tree_ZJets_Madgraph_0.root");
	//myProject->AddDataFile("/pool/ciencias/MC_Summer12_53X/Legacy/Tree_ZJets_Madgraph_0.root");
	//myProject->AddDataFile("/pool/ciencias/MC_Summer12_53X/Legacy/Tree_ZJets_Madgraph_1.root");
	//myProject->AddDataFile("/pool/ciencias/MC_Summer12_53X/Legacy/Tree_ZJets_Madgraph_2.root");

	//TString sample("sample");
	//myProject->SetInputParam("sample", sample);
	//myProject->SetInputParam("luminosity", 5311.0);
	//myProject->SetInputParam("xs_weight", 1);
	
	//myProject->AddPackage(new PAFPackage("LeptonSF"));
	//myProject->AddPackage(new PAFPackage("PUWeight"));
	//myProject->AddSelectorPackage(new PAFPackageSelector("MyAnalysisWZ"));
	myProject->AddSelectorPackage(new PAFPackageSelector("Benchmark"));
	
	myProject->Run();
}
