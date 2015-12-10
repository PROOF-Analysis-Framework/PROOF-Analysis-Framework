/**
	@brief PAF test class to test the AddDataFiles method of PAFProject.
	@file AddDataFiles.cxx
	@class AddDataFiles
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-02
 */

#include "AddDataFiles.h"

#include "PAFProject.h"


int main()
{
	AddDataFiles test;
	return PAFTest::Evaluate(&test);
}

void AddDataFiles::Initialise()
{
	CreateROOTFile("ROOT1.root", "tree");
	CreateROOTFile("ROOT2.root", "tree");
}

void AddDataFiles::Test()
{
	TList* elements = NULL;
	PAFProject project;

	AssertEquals(0, project.GetDataFiles()->GetNumOfFiles());

	project.AddDataFile("ROOT1.root");
	elements = project.GetDataFiles()->GetListOfElements();
	AssertEquals(1, elements->GetEntries());
	AssertEquals("ROOT1.root", ((TDSetElement*)elements->At(0))->GetFileName());
	AssertEquals("", ((TDSetElement*)elements->At(0))->GetObjName());

	project.AddDataFile("ROOT2.root", "none");
	elements = project.GetDataFiles()->GetListOfElements();
	AssertEquals(2, elements->GetEntries());
	AssertEquals("ROOT2.root", ((TDSetElement*)elements->At(1))->GetFileName());
	AssertEquals("none", ((TDSetElement*)elements->At(1))->GetObjName());

	project.SetDefaultTreeName("tree");
	elements = project.GetDataFiles()->GetListOfElements();
	AssertEquals(2, elements->GetEntries());
	AssertEquals("ROOT1.root", ((TDSetElement*)elements->At(0))->GetFileName());
	AssertEquals("tree", ((TDSetElement*)elements->At(0))->GetObjName());
	AssertEquals("ROOT2.root", ((TDSetElement*)elements->At(1))->GetFileName());
	AssertEquals("none", ((TDSetElement*)elements->At(1))->GetObjName());
}

void AddDataFiles::CreateROOTFile(const char* fileName, const char* treeName)
{
	TFile file(fileName, "RECREATE");

	TTree tree(treeName, "Default tree");

	tree.Write();
}
