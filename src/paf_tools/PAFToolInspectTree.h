#pragma once

#include "PAFITool.h"

#include "TFile.h"
#include "TTree.h"

class PAFToolInspectTree : public PAFITool
{
	public:
		PAFToolInspectTree();
		virtual ~PAFToolInspectTree();
	
		virtual TString GetToolName();
		virtual TString GetHelp();
		virtual TString GetCommandExpression();
	
		virtual void Execute(TList* params);
	
	protected:
		TString GetParam(TList* params, int i);
		void PrintMessage(const char* message);
		void PrintVariable(const char* type, const char* name);
		void PrintVariables(TTree* tree, const char* branchName);
		TTree* GetTree(TFile* rootFile, const char* treeName);
		TTree* GetAutoTree(TFile* rootFile);
	
};