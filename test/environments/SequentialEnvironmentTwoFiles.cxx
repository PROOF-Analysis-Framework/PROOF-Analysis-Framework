/**
	@brief PAF test class to check the sequential environment with two ROOT files.
	@file SequentialEnvironmentTwoFiles.cxx
	@class SequentialEnvironmentTwoFiles
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-08-9
 */


#include "SequentialEnvironmentTwoFiles.h"

#include "PAFManualSettings.h"
#include "PAFProject.h"
#include "PAFSequentialEnvironment.h"

#include "TSystem.h"

int main()
{
	SequentialEnvironmentTwoFiles test;
	return PAFTest::Evaluate(&test);
}

void SequentialEnvironmentTwoFiles::Initialise()
{
	CreateROOTFiles();
}

void SequentialEnvironmentTwoFiles::Test()
{
	PAFProject project(new PAFSequentialEnvironment());
	PAFISettings* settings = GetPAFISettings();
	project.SetPAFSettings(settings);

	project.AddDataFile(TString::Format("%s/SequentialROOTFile1.root", gSystem->pwd()).Data());
	project.AddDataFile(TString::Format("%s/SequentialROOTFile2.root", gSystem->pwd()).Data());
	project.AddSelectorPackage("PrimitiveIntTestSelector");

	TList* result = project.Run();

	TH1* histogram = PAFFindHelper::Find<TH1*>(result, "histogram");
	
	//Sum of Fibonacci from 0 to 40.
	AssertEquals(267914295., histogram->GetSumOfWeights());

	delete settings;
}

void SequentialEnvironmentTwoFiles::CreateROOTFiles()
{
	int previous = 1;
	int number = 1;

	TFile file1("SequentialROOTFile1.root", "RECREATE");
	TTree tree1("tree", "Default tree");
	tree1.Branch("value", &previous, "value/I");

	for (int i = 0; i < 20; i++)
	{
		tree1.Fill();
		int tmp = number;
		number = number + previous;
		previous = tmp;
	}
	tree1.Write();

	TFile file2("SequentialROOTFile2.root", "RECREATE");
	TTree tree2("tree", "Default tree");
	tree2.Branch("value", &previous, "value/I");

	for (int i = 0; i < 20; i++)
	{
		tree2.Fill();
		int tmp = number;
		number = number + previous;
		previous = tmp;
	}

	tree2.Write();
}
