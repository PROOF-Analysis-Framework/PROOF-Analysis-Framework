/**
	@brief PAF test class to check the behaviour of SetParameter and GetParamter method.
	@file PassingParameters.cxx
	@class PassingParameters
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-28
 */

#include "PassingParameters.h"

#include "PAF/project/PAFProject.h"
#include "PAF/computing_helpers/PAFFindHelper.h"
#include "PAF/environments/PAFSequentialEnvironment.h"

#include "TSystem.h"

int main()
{
	PassingParameters test;
	return PAFTest::Evaluate(&test);
}

void PassingParameters::Initialise()
{
	TFile file("PassingParameters.root", "RECREATE");

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

void PassingParameters::Test()
{
	PAFProject project(new PAFSequentialEnvironment(50));
	PAFISettings* settings = GetPAFISettings();
	project.SetPAFSettings(settings);

	project.AddDataFile(TString::Format("%s/PassingParameters.root", gSystem->pwd()));
	project.AddSelectorPackage("PassingParametersSeedTestSelector");
	project.AddSelectorPackage("PassingParametersConsumerTestSelector");
	
	TList* result = project.Run();

	TH1* histogram = PAFFindHelper::Find<TH1*>(result, "histogram");

	AssertEquals(3.1290931418, histogram->GetSumOfWeights());

	delete settings;
}
