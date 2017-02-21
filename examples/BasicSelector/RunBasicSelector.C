
void RunBasicSelector() 
{
	PAFProject* myProject = new PAFProject();
	myProject->AddDataFile("/path/to/file.root");
	myProject->AddSelectorPackage("BasicSelector");
	myProject->Run();
}
