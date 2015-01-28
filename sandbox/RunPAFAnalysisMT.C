void RunPAFAnalysisMT() 
{
	gSystem->Load("libPAF.so");
	PAFProject* myProject = new PAFProject(new PAFPoDEnvironment());
  	//PAFProject* myProject = new PAFProject(new PAFPROOFLiteEnvironment(4));

	myProject->AddDataFile("/pool/ciencias/MC_Summer12_53X/Legacy/Tree_ZJets_Madgraph_0.root");
	//myProject->AddDataFile("/pool/ciencias/MC_Summer12_53X/Legacy/Tree_ZJets_Madgraph_1.root");
	//myProject->AddDataFile("/pool/ciencias/MC_Summer12_53X/Legacy/Tree_ZJets_Madgraph_2.root");

	//myProject->AddDynamicHistogram("myHistogram");

	//myProject->SetOutputFile("histofile.root");

	//myProject->AddSelectorPackage(new PAFPackageSelector("MyAnalysisMiniTrees"));
	//myProject->AddSelectorPackage(new PAFPackageSelector("PAFSimpleSelector"));
	
	myProject->AddSelectorPackage(new PAFPackageSelector("PAFTestParamsSeed"));
	myProject->AddSelectorPackage(new PAFPackageSelector("PAFTestParamsPrinter"));
	
	myProject->SetInputParam("min", 1);
	
	//myProject->SetCompileOnSlaves(true);
	
	myProject->Run();
}






























