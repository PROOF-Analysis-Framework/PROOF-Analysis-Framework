/**
	@brief PAF test class to test the results of computing with a vector of TLorentVectors.
	@file VectorTLorentzType.cxx
	@class VectorTLorentzType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-10
 */


#include "VectorTLorentzType.h"

#include "PAF/project/PAFProject.h"
#include "PAF/computing_helpers/PAFFindHelper.h"
#include "PAF/environments/PAFSequentialEnvironment.h"

#include "TSystem.h"
#include "TLorentzVector.h"

int main()
{
	VectorTLorentzType test;
	return PAFTest::Evaluate(&test);
}

void VectorTLorentzType::Initialise()
{
	TFile file("VectorTLorentz.root", "RECREATE");

	TTree tree("tree", "Default tree");

	TLorentzVector value;

	tree.Branch("value", &value);

	for (int i = 0; i < 40; i++)
	{
		value = TLorentzVector(i, i+1, i+2, i+3);
		tree.Fill();
	}
	tree.Write();
}

void VectorTLorentzType::Test()
{
	PAFProject project(new PAFSequentialEnvironment());
	PAFISettings* settings = GetPAFISettings();
	project.SetPAFSettings(settings);

	project.AddDataFile(TString::Format("%s/VectorTLorentz.root", gSystem->pwd()));
	project.AddSelectorPackage("VectorTLorentzTestSelector");

	TList* result = project.Run();

	TH1* histogram = PAFFindHelper::Find<TH1*>(result, "histogram");

	AssertEquals(3360., histogram->GetSumOfWeights());

	delete settings;
}
