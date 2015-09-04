/**
	@brief PAF test class to test the results of computing with double primitive type.
	@file DoublePrimitiveType.cxx
	@class DoublePrimitiveType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-03
 */

#include "DoublePrimitiveType.h"

#include "PAFProject.h"
#include "PAFFindHelper.h"

#include "TSystem.h"
#include "TROOT.h"

int main()
{
	gROOT->SetBatch();
	
	DoublePrimitiveType test;
	return PAFTest::Evaluate(&test);
}

void DoublePrimitiveType::Initialise()
{
	TFile file("PrimitiveDouble.root", "RECREATE");

	TTree tree("tree", "Default tree");

	int current = 1;
	double number = 0;

	tree.Branch("value", &number, "value/D");

	for (int i = 0; i < 40; i++)
	{
		number = (4. / current) - (4. / (current + 2));
		current += 4;
		tree.Fill();
	}
	tree.Write();
}

void DoublePrimitiveType::Test()
{
	PAFProject project;
	PAFISettings* settings = GetPAFISettings();
	project.SetPAFSettings(settings);

	project.AddDataFile(TString::Format("%s/PrimitiveDouble.root", gSystem->pwd()));
	project.AddSelectorPackage("PrimitiveDoubleTestSelector");
	
	TList* result = project.Run();

	TH1* histogram = PAFFindHelper::Find<TH1*>(result, "histogram");

	AssertEquals(3.1290931418, histogram->GetSumOfWeights());

	delete settings;
}
