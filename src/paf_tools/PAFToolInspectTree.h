/**
	@brief PAF tool class to show information about ROOT files.
	@file PAFToolInspectTree.h
	@class PAFToolInspectTree
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-30
 */

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
	
		static const char* TOOL_NAME;
		static const char* HELP_MESSAGE;
		static const char* COMMAND_EXPRESSION;
};