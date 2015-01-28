InputParameters* GetInputParameters()
{
	InputParameters* ip = new InputParameters();
	ip->SetString("selection");
  	ip->SetInt(1);
  	ip->SetFloat(1.);
  	ip->SetDouble(1.);
  	ip->SetBool(0);
  	ip->SetNamedString("sel1", "cut1"); ip->SetNamedString("sel2", "cut2");
  	ip->SetNamedInt("i1", 1); ip->SetNamedInt("i2", 2); ip->SetNamedInt("i3", 3);
  	ip->SetNamedBool("b1", 0);
  	ip->SetNamedFloat("d1", 1.); ip->SetNamedFloat("d2", 2.);
  	ip->SetNamedDouble("db1", 1.); ip->SetNamedDouble("db2", 2.);
	return ip;
}

void RunPAFAnalysisMT() 
{
	//PAFProject* myProject = new PAFProject(new PAFPoDEnvironment());
  	PAFProject* myProject = new PAFProject(new PAFPROOFLiteEnvironment(4));

	//myProject->SetInputParameters(GetInputParameters());

	myProject->AddDataFile("/pool/ciencias/MC_Summer12_53X/Legacy/Tree_ZJets_Madgraph_0.root");
	//myProject->AddDataFile("/pool/ciencias/MC_Summer12_53X/Legacy/Tree_ZJets_Madgraph_1.root");
	//myProject->AddDataFile("/pool/ciencias/MC_Summer12_53X/Legacy/Tree_ZJets_Madgraph_2.root");

	//myProject->AddDynamicHistogram("myHistogram");

	//myProject->SetOutputFile("histofile.root");

	myProject->AddSelectorPackage(new PAFPackageSelector("MyAnalysisMiniTrees"));
	myProject->AddSelectorPackage(new PAFPackageSelector("PAFSimpleSelector"));
	
	//myProject->SetCompileOnSlaves(true);
	
	myProject->Run();
}






























