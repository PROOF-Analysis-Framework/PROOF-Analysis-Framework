/**
	@brief PAF test class to test the GetSizeOf method with a double vector.
	@file GetSizeOfDoubleMethod.cxx
	@class GetSizeOfDoubleMethod
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-09
 */

#include "GetSizeOfDoubleMethod.h"

#include "PAFProject.h"
#include "PAFFindHelper.h"
#include "PAFSequentialEnvironment.h"

#include "TSystem.h"

int main()
{
	GetSizeOfDoubleMethod test;
	return PAFTest::Evaluate(&test);
}

void GetSizeOfDoubleMethod::Initialise()
{
	TFile fileDouble("GetSizeOfDouble.root", "RECREATE");
	TTree treeDouble("tree", "Default tree");
	std::vector<double>* doubles = NULL;
	treeDouble.Branch("value", &doubles);

	for (int i = 0; i < 40; i++)
	{
		doubles = new std::vector<double>();

		for(int j = 0; j < i; j++)
		{
			doubles->push_back(j/2);
		}
		treeDouble.Fill();
	}
	treeDouble.Write();
}

void GetSizeOfDoubleMethod::Test()
{
	PAFProject project(new PAFSequentialEnvironment());
	PAFISettings* settings = GetPAFISettings();
	project.SetPAFSettings(settings);

	project.AddDataFile(TString::Format("%s/GetSizeOfDouble.root", gSystem->pwd()));
	project.AddSelectorPackage("GetSizeOfDoubleTestSelector");
	
	TList* result = project.Run();

	TH1* histogram = PAFFindHelper::Find<TH1*>(result, "histogram");

	AssertEquals(40., histogram->GetSumOfWeights());

	delete settings;
}
