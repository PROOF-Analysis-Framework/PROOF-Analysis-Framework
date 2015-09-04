/**
	@brief PAF test class to check the PROOFLite environment.
	@file PROOFLiteEnvironment.h
	@class PROOFLiteEnvironment
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-08
 */

#include "PROOFLiteEnvironment.h"

#include "PAFManualSettings.h"
#include "PAFProject.h"
#include "PAFPROOFLiteEnvironment.h"

#include "TSystem.h"
#include "TROOT.h"

int main()
{
	gROOT->SetBatch();

	PROOFLiteEnvironment test;
	return PAFTest::Evaluate(&test);
}

void PROOFLiteEnvironment::Initialise()
{
	CreateROOTFile("PROOFLiteROOTFile.root");
}

void PROOFLiteEnvironment::Test()
{
	PAFProject project(new PAFPROOFLiteEnvironment(4));
	PAFISettings* settings = GetPAFISettings();
	project.SetPAFSettings(settings);

	project.AddDataFile(TString::Format("%s/PROOFLiteROOTFile.root", gSystem->pwd()).Data());
	project.AddSelectorPackage("PrimitiveIntTestSelector");
	
	TList* result = project.Run();

	TH1* histogram = PAFFindHelper::Find<TH1*>(result, "histogram");
	
	//Sum of Fibonacci from 0 to 40.
	AssertEquals(267914295., histogram->GetSumOfWeights());

	delete settings;
}
