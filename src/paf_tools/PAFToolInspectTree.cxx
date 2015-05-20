/**
	@brief PAF tool class to show information about ROOT files.
	@file PAFToolInspectTree.cxx
	@class PAFToolInspectTree
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-30
 */

#include "PAFToolInspectTree.h"

#include "TLeaf.h"
#include "TLeafElement.h"
#include "TLeafObject.h"

#include "TRegexp.h"
#include "THashList.h"

#include "../exceptions/PAFExceptionCommandExpression.h"

const char* PAFToolInspectTree::TOOL_NAME = "inspecttree";

const char* PAFToolInspectTree::HELP_MESSAGE = "\t\"-h | --help\" to show command help.\n\t\"-b | --branch branchname\" to retrieve information about specified branch.\n\t\"-t | --tree treename\"  to retrieve information about specified tree.\n\t ROOT file name. Mandatory.";

const char* PAFToolInspectTree::COMMAND_EXPRESSION = "inspecttree [-t | --tree] [-b | --branch] root_filename";


PAFToolInspectTree::PAFToolInspectTree()
	: PAFAbstractTool(TOOL_NAME, HELP_MESSAGE, COMMAND_EXPRESSION)
{

}

PAFToolInspectTree::~PAFToolInspectTree()
{

}

void PAFToolInspectTree::Execute(TList* params)
{
	if(params->GetSize() == 1)
	{
		throw PAFExceptionCommandExpression(TOOL_NAME);
	}
	
	const char* branchName = NULL;
	const char* treeName = NULL;
	TFile* rootFile = new TFile(GetParam(params, params->GetSize() - 1));
	
	for(int i = 1; i < params->GetSize(); i = i + 2)
	{
		TString item = GetParam(params, i);
		if(item.EqualTo("-b") || item.EqualTo("--branch")){
			branchName = GetParam(params, i + 1);
		} else if (item.EqualTo("-t") || item.EqualTo("--tree")) {
			treeName = GetParam(params, i + 1);
		}
	}
	
	TTree* tree = treeName ? GetTree(rootFile, treeName) : GetAutoTree(rootFile);
	
	if(tree)
	{
		PrintVariables(tree, branchName);
	}
}

TTree* PAFToolInspectTree::GetTree(TFile* rootFile, const char* treeName)
{
	return (TTree*)rootFile->Get(treeName);
}

TTree* PAFToolInspectTree::GetAutoTree(TFile* rootFile)
{
	THashList* trees = (THashList*)rootFile->GetListOfKeys();
	TTree* result = NULL;
	
	if(trees->GetSize() == 1)
	{
		TObject* uniqueTree = trees->First();
		PrintMessage( TString::Format("Selecting the unique Tree: \"%s\"", uniqueTree->GetName()));
		result = GetTree(rootFile, uniqueTree->GetName());
	}
	else
	{
		PrintMessage("Please, the file specified has several Trees. You should choose one with -t param.\nHere is the list of Trees contained in that ROOT file:");
		for(int i = 0; i < trees->GetSize(); i++)
		{
			TObject* tree = trees->At(i);
			PrintMessage( TString::Format("\t -%s", tree->GetName()).Data() );
		}
	}
	return result;
}

void PAFToolInspectTree::PrintVariables(TTree* tree, const char* branchName)
{
	TString tBranchName = branchName ? TString(branchName) : TString("*");
	TRegexp* regex = new TRegexp(tBranchName, kTRUE);
	
	TObjArray* leaves = tree->GetListOfLeaves();
	Int_t nb = leaves->GetEntriesFast();
	for (Int_t i = 0; i < nb; ++i)
	{
		TLeaf* leaf = (TLeaf*)leaves->UncheckedAt(i);
		const TString name(leaf->GetName());
		int length;
		if(regex->Index(name, &length) != -1)
		{
			TString type(leaf->GetTypeName());
			if(leaf->IsA() == TLeafElement::Class() || leaf->IsA() == TLeafObject::Class())
			{
				type.Append("*");
			}
			PrintVariable(type.Data(), name.Data());
		}
	}
	
	delete tree;
	delete regex;
}

void PAFToolInspectTree::PrintVariable(const char* type, const char* name)
{
	PrintMessage(TString::Format("Type: %s \t\tVariable: %s\n", type, name));
}

