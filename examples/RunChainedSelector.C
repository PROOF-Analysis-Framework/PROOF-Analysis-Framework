
void RunChainedSelector() 
{
	PAFProject* myProject = new PAFProject();
	
	myProject->AddDataFile("/home/nofernan/TFG/rootfiles/example.root");

	myProject->SetInputParam("Variable", "T_METPF_ET");
	
	myProject->SetInputParam("Prueba", 1.2);

	myProject->AddSelectorPackage("VariableGetter");
	myProject->AddSelectorPackage("VariablePainter");
	
	myProject->Run();
}
