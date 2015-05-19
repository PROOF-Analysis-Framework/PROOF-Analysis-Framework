
void RunChainedSelector() 
{
	PAFProject* myProject = new PAFProject();
	
	myProject->AddDataFile("/pool/ciencias/MC_Summer12_53X/Legacy/Tree_ZJets_Madgraph_0.root");

	myProject->SetInputParam("Variable", "T_METPF_ET");
	
	myProject->SetInputParam("Prueba", 1.2);

	myProject->AddSelectorPackage("VariableGetter");
	myProject->AddSelectorPackage("VariablePainter");
	
	myProject->Run();
}
