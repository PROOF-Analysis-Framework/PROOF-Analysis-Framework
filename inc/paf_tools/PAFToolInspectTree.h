/**
	@brief PAF tool class to show information about ROOT files.
	@file PAFToolInspectTree.h
	@class PAFToolInspectTree
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-30
 */

#pragma once

// Includes
// + PAF
#include "PAFAbstractTool.h"
// + ROOT
#include "TFile.h"
#include "TTree.h"

class PAFToolInspectTree : public PAFAbstractTool
{
	public:
		PAFToolInspectTree();
		virtual ~PAFToolInspectTree();

		virtual void ExecuteTool(TList* params);

	protected:
		void PrintDescription(const char* desc);
		void PrintVariable(const char* type, const char* name);
		void PrintSnippet(const char* type, const char* name);
		void PrintVariables(TTree* tree, const TString& branchName, bool snippet);

		TTree* GetTree(TFile* rootFile, const TString& treeName);
		TTree* GetAutoTree(TFile* rootFile);
		void GetListOfTrees(TDirectory* directory, TList* resultTrees, const char* path);

};
