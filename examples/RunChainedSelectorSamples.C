class Try;

void RunChainedSelectorSamples() {
	PAFProject *myProject = new PAFProject();

	PAFBasicSample *sample1 = new PAFBasicSample();
	sample1->SetSampleName("Prueba 1");
	sample1->AddDataFile("/pub/example.root","Tree");

	PAFBasicSample *sample2 = new PAFBasicSample();
	sample2->SetSampleName("Prueba 2");
	sample2->AddDataFile("/pub/example.root","Tree");



	myProject->AddSample(sample1);
	myProject->AddSample(sample2);


	myProject->SetInputParam("Variable", "T_METPF_ET");
	myProject->SetInputParam("Prueba", 1.2);
	myProject->AddSelectorPackage("VariableGetter");
	myProject->AddSelectorPackage("VariablePainter");
	
	myProject->Run();
}
