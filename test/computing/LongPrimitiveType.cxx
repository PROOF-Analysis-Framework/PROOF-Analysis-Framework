/**
	@brief PAF test class to test the results of computing with long primitive type.
	@file LongPrimitiveType.h
	@class LongPrimitiveType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-03
 */

#include "LongPrimitiveType.h"

#include "PAFProject.h"
#include "PAFFindHelper.h"

#include "TSystem.h"
#include "TROOT.h"

int main()
{
	gROOT->SetBatch();

	LongPrimitiveType test;
	return PAFTest::Evaluate(&test);
}

void LongPrimitiveType::Initialise()
{
	TFile file("PrimitiveLong.root", "RECREATE");

	TTree tree("tree", "Default tree");

	long previous = 1;
	long number = 1;

	tree.Branch("value", &previous, "value/L");

	for (int i = 0; i < 70; i++)
	{
		tree.Fill();
		long tmp = number;
		number = number + previous;
		previous = tmp;
	}
	tree.Write();
}

void LongPrimitiveType::Test()
{
	PAFProject project;
	PAFISettings* settings = GetPAFISettings();
	project.SetPAFSettings(settings);

	project.AddDataFile(TString::Format("%s/PrimitiveLong.root", gSystem->pwd()));
	project.AddSelectorPackage("PrimitiveLongTestSelector");
	
	TList* result = project.Run();

	TH1* histogram = PAFFindHelper::Find<TH1*>(result, "histogram");
	
	//Sum of Fibonacci from 0 to 60.
	AssertEquals(498454011879263, (long)histogram->GetSumOfWeights());

	delete settings;
}
