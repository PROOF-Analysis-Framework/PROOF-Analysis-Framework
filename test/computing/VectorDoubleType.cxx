/**
	@brief PAF test class to test the results of computing with a vector of double type.
	@file VectorDoubleType.h
	@class VectorDoubleType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-03
 */


#include "VectorDoubleType.h"

#include "PAFProject.h"
#include "PAFFindHelper.h"

#include "TSystem.h"

int main()
{
	VectorDoubleType test;
	return PAFTest::Evaluate(&test);
}

void VectorDoubleType::Initialise()
{
	TFile file("VectorDouble.root", "RECREATE");

	TTree tree("tree", "Default tree");

	int current = 1;
	double number = 0;
	std::vector<double>* numbers = NULL;

	tree.Branch("value", &numbers);

	for (int i = 0; i < 40; i++)
	{
		number = (4. / current) - (4. / (current + 2));
		current += 4;

		numbers = new std::vector<double>();
		numbers->push_back(number);
		tree.Fill();
	}
	tree.Write();
}

void VectorDoubleType::Test()
{
	PAFProject project;
	PAFISettings* settings = GetPAFISettings();
	project.SetPAFSettings(settings);

	project.AddDataFile(TString::Format("%s/VectorDouble.root", gSystem->pwd()));
	project.AddSelectorPackage("VectorDoubleTestSelector");
	
	TList* result = project.Run();

	TH1* histogram = PAFFindHelper::Find<TH1*>(result, "histogram");

	AssertEquals(3.1290931418, histogram->GetSumOfWeights());

	delete settings;
}
