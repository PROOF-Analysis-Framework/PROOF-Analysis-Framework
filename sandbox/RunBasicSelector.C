
void RunBasicSelector() 
{
	PAFProject* myProject = new PAFProject();
	myProject->AddDataFile("/home/javier/Documents/Tree_ZJets_Madgraph_0.root");
	myProject->AddSelectorPackage("BasicSelector");
	myProject->Run();
}
