/**
	@brief PAF test class to check the sequential environment.
	@file SequentialEnvironment.cxx
	@class SequentialEnvironment
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-08
 */

#include "SequentialEnvironment.h"

#include "PAFManualSettings.h"
#include "PAFProject.h"
#include "PAFSequentialEnvironment.h"

#include "TSystem.h"

int main()
{
	SequentialEnvironment test;
	return PAFTest::Evaluate(&test);
}

void SequentialEnvironment::Initialise()
{
	CreateROOTFile("SequentialROOTFile.root");
}

void SequentialEnvironment::Test()
{
	PAFProject project(new PAFSequentialEnvironment());
	PAFISettings* settings = GetPAFISettings();
	project.SetPAFSettings(settings);

	project.AddDataFile(TString::Format("%s/SequentialROOTFile.root", gSystem->pwd()).Data());
	project.AddSelectorPackage("PrimitiveIntTestSelector");
	
	TList* result = project.Run();

	TH1* histogram = PAFFindHelper::Find<TH1*>(result, "histogram");
	
	//Sum of Fibonacci from 0 to 40.
	AssertEquals(267914295., histogram->GetSumOfWeights());

	delete settings;
}
