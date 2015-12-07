

void RunChainedSelectorSamples() {
	PAFProject *myProject = new PAFProject();

	PAFBasicSample *sample = new PAFBasicSample();
	sample->SetSampleName("Sample name");
	sample->AddDataFile("/pub/example.root", "Tree");

	myProject->AddSample(sample);



	myProject->AddDataFile("/pub/example.root","");

	myProject->SetInputParam("Variable", "T_METPF_ET");
	
	myProject->SetInputParam("Prueba", 1.2);

	myProject->AddSelectorPackage("VariableGetter");
	myProject->AddSelectorPackage("VariablePainter");
	
	myProject->Run();
}
