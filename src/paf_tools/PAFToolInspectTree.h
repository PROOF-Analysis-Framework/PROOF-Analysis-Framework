#pragma once

#include "PAFAbstractTool.h"

#include "TFile.h"
#include "TTree.h"

class PAFToolInspectTree : public PAFAbstractTool
{
	public:
		PAFToolInspectTree();
		virtual ~PAFToolInspectTree();
	
		virtual void Execute(TList* params);
	
	protected:
		void PrintVariable(const char* type, const char* name);
		void PrintVariables(TTree* tree, const char* branchName);
		TTree* GetTree(TFile* rootFile, const char* treeName);
		TTree* GetAutoTree(TFile* rootFile);
	
};