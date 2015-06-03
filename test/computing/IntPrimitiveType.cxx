/**
	@brief PAF test class to test the results of computing with int primitive type.
	@file IntPrimitiveType.cxx
	@class IntPrimitiveType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-03
 */

#include "IntPrimitiveType.h"

#include "PAF/project/PAFProject.h"
#include "PAF/computing_helpers/PAFFindHelper.h"

#include "TSystem.h"

int main()
{
	IntPrimitiveType test;
	return PAFTest::Evaluate(&test);
}

void IntPrimitiveType::Initialise()
{
	TFile file("PrimitiveInt.root", "RECREATE");

	TTree tree("tree", "Default tree");

	int previous = 1;
	int number = 1;

	tree.Branch("value", &previous, "value/I");

	for (int i = 0; i < 40; i++)
	{
		tree.Fill();
		int tmp = number;
		number = number + previous;
		previous = tmp;
	}
	tree.Write();
}

void IntPrimitiveType::Test()
{
	PAFProject project;
	PAFISettings* settings = GetPAFISettings();
	project.SetPAFSettings(settings);

	project.AddDataFile(TString::Format("%s/PrimitiveInt.root", gSystem->pwd()));
	project.AddSelectorPackage("PrimitiveIntTestSelector");
	
	TList* result = project.Run();

	TH1* histogram = PAFFindHelper::Find<TH1*>(result, "histogram");
	
	//Sum of Fibonacci from 0 to 40.
	AssertEquals(267914295., histogram->GetSumOfWeights());

	delete settings;
}
