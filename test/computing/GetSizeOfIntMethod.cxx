/**
	@brief PAF test class to test the GetSizeOf method with a int vector.
	@file GetSizeOfIntMethod.cxx
	@class GetSizeOfIntMethod
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-09
 */

#include "GetSizeOfIntMethod.h"

#include "PAF/project/PAFProject.h"
#include "PAF/computing_helpers/PAFFindHelper.h"
#include "PAF/environments/PAFSequentialEnvironment.h"

#include "TSystem.h"

int main()
{
	GetSizeOfIntMethod test;
	return PAFTest::Evaluate(&test);
}

void GetSizeOfIntMethod::Initialise()
{
	TFile fileInt("GetSizeOfInt.root", "RECREATE");
	TTree treeInt("tree", "Default tree");
	std::vector<int>* ints = NULL;
	treeInt.Branch("value", &ints);

	for (int i = 0; i < 40; i++)
	{
		ints = new std::vector<int>();

		for(int j = 0; j < i; j++)
		{
			ints->push_back(j);
		}
		treeInt.Fill();
	}
	treeInt.Write();
}

void GetSizeOfIntMethod::Test()
{
	PAFProject project(new PAFSequentialEnvironment());
	PAFISettings* settings = GetPAFISettings();
	project.SetPAFSettings(settings);

	project.AddDataFile(TString::Format("%s/GetSizeOfInt.root", gSystem->pwd()));
	project.AddSelectorPackage("GetSizeOfIntTestSelector");
	
	TList* result = project.Run();

	TH1* histogram = PAFFindHelper::Find<TH1*>(result, "histogram");

	AssertEquals(40., histogram->GetSumOfWeights());

	delete settings;
}
