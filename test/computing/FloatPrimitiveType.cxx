/**
	@brief PAF test class to test the results of computing with float primitive type.
	@file FloatPrimitiveType.cxx
	@class FloatPrimitiveType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-03
 */

#include "FloatPrimitiveType.h"

#include "PAFProject.h"
#include "PAFFindHelper.h"

#include "TSystem.h"
#include "TROOT.h"

int main()
{
	FloatPrimitiveType test;
	gROOT->SetBatch();
	return PAFTest::Evaluate(&test);
}

void FloatPrimitiveType::Initialise()
{
	TFile file("PrimitiveFloat.root", "RECREATE");

	TTree tree("tree", "Default tree");

	int current = 1;
	float number = 0;

	tree.Branch("value", &number, "value/F");

	for (int i = 0; i < 40; i++)
	{
		number = (4.f / current) - (4.f / (current + 2));
		current += 4;
		tree.Fill();
	}
	tree.Write();
}

void FloatPrimitiveType::Test()
{
	PAFProject project;
	PAFISettings* settings = GetPAFISettings();
	project.SetPAFSettings(settings);

	project.AddDataFile(TString::Format("%s/PrimitiveFloat.root", gSystem->pwd()));
	project.AddSelectorPackage("PrimitiveFloatTestSelector");
	
	TList* result = project.Run();

	TH1* histogram = PAFFindHelper::Find<TH1*>(result, "histogram");
	
	AssertEquals(3.129093f, (float)histogram->GetSumOfWeights());

	delete settings;
}
