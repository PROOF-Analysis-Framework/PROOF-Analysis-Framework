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

	PAF_DEBUG("AddDataFiles","Initial check of empty Data project...");
	AssertEquals((void*) 0, project.GetDataFiles());

	PAF_DEBUG("AddDataFiles","Working with first root file (ROOT1)...");
	project.AddDataFile("ROOT1.root");
	elements = project.GetDataFiles()->GetListOfElements();
	AssertEquals(1, elements->GetEntries());
	AssertEquals("ROOT1.root", ((TDSetElement*)elements->At(0))->GetFileName());
	AssertEquals("", ((TDSetElement*)elements->At(0))->GetObjName());

	PAF_DEBUG("AddDataFiles","Working with second root file (ROOT2)...");
	project.AddDataFile("ROOT2.root", "none");
	elements = project.GetDataFiles()->GetListOfElements();
	AssertEquals(2, elements->GetEntries());
	AssertEquals("ROOT2.root", ((TDSetElement*)elements->At(1))->GetFileName());
	AssertEquals("none", ((TDSetElement*)elements->At(1))->GetObjName());


	PAF_DEBUG("AddDataFiles","Set default tree name...");
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
