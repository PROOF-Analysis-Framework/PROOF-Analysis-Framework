/**
	@brief PAF test class to test the results of computing with arrays of doubles types.
	@file DoublePrimitiveType.cxx
	@class ArrayDoubleType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-24
 */

#include "ArrayDoubleType.h"

#include "PAF/project/PAFProject.h"
#include "PAF/computing_helpers/PAFFindHelper.h"
#include "PAF/environments/PAFSequentialEnvironment.h"

#include "TSystem.h"

int main()
{
	ArrayDoubleType test;
	return PAFTest::Evaluate(&test);
}

void ArrayDoubleType::Initialise()
{
	TFile file("ArrayDouble.root", "RECREATE");

	TTree tree("tree", "Default tree");

	double* number = new double[2];
	
	tree.Branch("value", number, "value[2]/D");

	for (int i = 0; i < 40; i++)
	{
		number[0] = i;
		number[1] = i + 1;

		tree.Fill();
	}
	tree.Write();
}

void ArrayDoubleType::Test()
{
	PAFProject project(new PAFSequentialEnvironment());
	PAFISettings* settings = GetPAFISettings();
	project.SetPAFSettings(settings);

	project.AddDataFile(TString::Format("%s/ArrayDouble.root", gSystem->pwd()));
	project.AddSelectorPackage("ArrayDoubleTestSelector");
	
	TList* result = project.Run();

	TH1* histogram = PAFFindHelper::Find<TH1*>(result, "histogram");

	AssertEquals(1600.0, histogram->GetSumOfWeights());

	delete settings;
}
