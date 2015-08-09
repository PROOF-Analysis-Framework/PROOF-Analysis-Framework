/**
	@brief PAF test class to check the behaviour of SetParameter and GetParamter method with objects.
	@file PassingParametersObjects.cxx
	@class PassingParametersObjects
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-07-16
 */

#include "PassingParametersObjects.h"

#include "PAFProject.h"
#include "PAFFindHelper.h"
#include "PAFSequentialEnvironment.h"

#include "TSystem.h"

int main()
{
	PassingParametersObjects test;
	return PAFTest::Evaluate(&test);
}

void PassingParametersObjects::Initialise()
{
	TFile file("PassingParametersObjects.root", "RECREATE");

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

void PassingParametersObjects::Test()
{
	PAFProject project(new PAFSequentialEnvironment(50));
	PAFISettings* settings = GetPAFISettings();
	project.SetPAFSettings(settings);

	project.AddDataFile(TString::Format("%s/PassingParametersObjects.root", gSystem->pwd()));
	project.AddSelectorPackage("PassingParametersObjectsSeedTestSelector");
	project.AddSelectorPackage("PassingParametersObjectsConsumerTestSelector");
	
	TList* result = project.Run();

	TH1* histogram = PAFFindHelper::Find<TH1*>(result, "histogram");

	AssertEquals(3.1290931418, histogram->GetSumOfWeights());

	delete settings;
}
