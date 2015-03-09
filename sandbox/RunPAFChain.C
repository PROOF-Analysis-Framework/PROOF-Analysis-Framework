#include "TSelector.h"
#include "TCanvas.h"

void RunPAFChain() 
{
	gSystem->Load("libPAF.so");
	PAFProject* myProject = new PAFProject(new PAFPROOFLiteEnvironment(4));
	
	myProject->AddDataFile("/home/javier/Documents/Tree_ZJets_Madgraph_0.root");

	myProject->SetInputParam("Variable", "T_METPF_ET");
	
	myProject->AddSelectorPackage("MyVariableGetter");
	myProject->AddSelectorPackage("MyVariablePainter");
	
	myProject->Run();
}
