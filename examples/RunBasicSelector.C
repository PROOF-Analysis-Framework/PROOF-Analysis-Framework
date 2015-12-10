
void RunBasicSelector() 
{
	PAFProject* myProject = new PAFProject();
	myProject->AddDataFile("/pool/ciencias/MC_Summer12_53X/Legacy/Tree_ZJets_Madgraph_0.root");
	myProject->AddSelectorPackage("BasicSelector");
	myProject->Run();
}
