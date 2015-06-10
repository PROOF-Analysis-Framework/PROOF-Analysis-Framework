/**
	@brief PAF test class to test the GetSizeOf method with a bool vector.
	@file GetSizeOfBoolMethod.h
	@class GetSizeOfBoolMethod
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-09
 */


#include "GetSizeOfBoolMethod.h"

#include "PAF/project/PAFProject.h"
#include "PAF/computing_helpers/PAFFindHelper.h"
#include "PAF/environments/PAFSequentialEnvironment.h"

#include "TSystem.h"

int main()
{
	GetSizeOfBoolMethod test;
	return PAFTest::Evaluate(&test);
}

void GetSizeOfBoolMethod::Initialise()
{
	TFile fileBool("GetSizeOfBool.root", "RECREATE");
	TTree treeBool("tree", "Default tree");
	std::vector<bool>* bools = NULL;
	treeBool.Branch("value", &bools);

	for (int i = 0; i < 40; i++)
	{
		bools = new std::vector<bool>();

		for(int j = 0; j < i; j++)
		{
			bools->push_back(j % 2 == 0);
		}

		treeBool.Fill();
	}
	treeBool.Write();
}

void GetSizeOfBoolMethod::Test()
{
	PAFProject project(new PAFSequentialEnvironment());
	PAFISettings* settings = GetPAFISettings();
	project.SetPAFSettings(settings);

	project.AddDataFile(TString::Format("%s/GetSizeOfBool.root", gSystem->pwd()));
	project.AddSelectorPackage("GetSizeOfBoolTestSelector");
	
	TList* result = project.Run();

	TH1* histogram = PAFFindHelper::Find<TH1*>(result, "histogram");

	AssertEquals(40., histogram->GetSumOfWeights());

	delete settings;
}
