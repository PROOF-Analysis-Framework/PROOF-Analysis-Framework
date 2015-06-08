/**
	@brief Abstract PAF test class to provides some common functionality to environments tests.
	@file AbstractEnvironmentTest.cxx
	@class AbstractEnvironmentTest
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-08
 */

#include "AbstractEnvironmentTest.h"

#include "PAF/settings/PAFManualSettings.h"

#include "TSystem.h"
#include "TFile.h"
#include "TTree.h"

PAFISettings* AbstractEnvironmentTest::GetPAFISettings()
{
	TString* pafPath = new TString("$PAFPATH");
	
	std::vector< TString* >* repositories = new std::vector< TString* >();
	repositories->push_back(new TString(TString::Format("%s/test/selectors_testing", gSystem->Getenv("PAFPATH"))));
	
	return new PAFManualSettings(pafPath, repositories);
}

void AbstractEnvironmentTest::CreateROOTFile(const char* fileName)
{
	TFile file(fileName, "RECREATE");

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
