/**
	@brief PAF tool class to show information about ROOT files.
	@file PAFToolInspectTree.cxx
	@class PAFToolInspectTree
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-30
 */


// Includes
// + PAF
#include "PAFToolInspectTree.h"
#include "PAFExceptionCommandExpression.h"
// + ROOT
#include "TLeaf.h"
#include "TLeafElement.h"
#include "TLeafObject.h"
#include "TRegexp.h"
#include "THashList.h"


static const char* TOOL_NAME = "inspecttree";
static const char* SHORT_DESCRIPTION = "Prints the tree contents in a ROOT file";
static const char* SHORT_NAME = "it";
static const char* COMMAND_EXPRESSION = "inspecttree|it [-t | --tree] [-b | --branch] [-s | --snippet] root_filename";
static const char* PARAMETERS_HELP = "\"-h | --help\" to show command help.\n\t\"-b | --branch branchname\" to retrieve information about specified branch.\n\t\"-t | --tree treename\"  to retrieve information about specified tree.\n\t\"-s | --snippet\" to show a code snippet for each variable.\n\t root_filename: ROOT file name (Mandatory)";



PAFToolInspectTree::PAFToolInspectTree()
  : PAFAbstractTool(TOOL_NAME, SHORT_DESCRIPTION, SHORT_NAME, COMMAND_EXPRESSION, PARAMETERS_HELP)
{

}

PAFToolInspectTree::~PAFToolInspectTree()
{

}

void PAFToolInspectTree::ExecuteTool(TList* params)
{
	if(params->GetSize() == 1)
	{
		throw PAFExceptionCommandExpression(TOOL_NAME);
	}
	
	TString branchName = GetParameter(params, "-b", "--branch");
	TString treeName = GetParameter(params, "-t", "--tree");
	Bool_t snippet = ExistsParam(params, "-s", "--snippet");
	TString file = GetParameter(params, params->GetSize() - 1);
	TFile* rootFile = new TFile(file.Data());
	
	if (!rootFile->IsOpen())
	{
		Exit(TString::Format("File \"%s\" does not exists.", file.Data()), -1);
	}
	TTree* tree = (treeName != "") ? GetTree(rootFile, treeName) : GetAutoTree(rootFile);
	PrintVariables(tree, branchName, snippet);
}

TTree* PAFToolInspectTree::GetTree(TFile* rootFile, const TString& treeName)
{	
	TObject* result = rootFile->Get(treeName.Data());

	if (!result)
	{
		Exit(TString::Format("Tree \"%s\" does not exists in this file.", treeName.Data()), -1);
	}
	
	if(result->IsA() == TTree::Class())
	{
		return (TTree*)result;
	}

	return NULL;
}

void PAFToolInspectTree::GetListOfTrees(TDirectory* directory, TList* resultTrees, const char* path)
{
	THashList* trees = (THashList*)directory->GetListOfKeys();

	TIterator* it = trees->MakeIterator();
	TObject* item = 0;
	while( (item = it->Next()) )
	{
		TObject* obj = directory->Get(item->GetName());
		TString current_item = (directory->IsA() == TFile::Class()) ? 
			TString(item->GetName()) : TString::Format("%s/%s", path, item->GetName());
		
		if(obj->IsA() == TTree::Class())
		{
			resultTrees->Add(new TObjString(current_item.Data()));
		}
		else if (obj->IsA() == TDirectoryFile::Class() ||
				obj->IsA() == TDirectory::Class())
		{
			GetListOfTrees((TDirectory*)obj, resultTrees, current_item.Data());
		}
	}
}

TTree* PAFToolInspectTree::GetAutoTree(TFile* rootFile)
{	
	TList* trees = new TList();
	
	GetListOfTrees(rootFile, trees, "");
	
	TTree* result = NULL;
	
	if(trees->GetSize() == 0)
	{
		PrintMessage("This ROOT file does not contain any Tree");
	}
	else if(trees->GetSize() == 1)
	{
	        TString tree_name(trees->First()->GetName());
		PrintMessage( TString::Format("Selecting the unique Tree: \"%s\"", tree_name.Data()));
		result = GetTree(rootFile, tree_name);
	}
	else
	{
		PrintMessage("Please, the file specified has several Trees. You should choose one with -t param.\nHere is the list of Trees contained in that ROOT file:");
		for(int i = 0; i < trees->GetSize(); i++)
		{
			const char* tree_name = trees->At(i)->GetName();
			PrintMessage( TString::Format("\t -%s", tree_name).Data());
		}
		Exit("Execute again the command specifying the branch desired (Ex: \"-b name_of_branch\").");
	}
	
	delete trees;
	
	return result;
}

void PAFToolInspectTree::PrintVariables(TTree* tree, const TString& branchName, bool snippet)
{
        TRegexp* regex = (branchName != "") ? new TRegexp(branchName.Data(), kTRUE) : new TRegexp("*", kTRUE);
	
	TObjArray* leaves = tree->GetListOfLeaves();
	Int_t nb = leaves->GetEntriesFast();
	for (Int_t i = 0; i < nb; i++)
	{
		TLeaf* leaf = (TLeaf*)leaves->UncheckedAt(i);
		const TString name(leaf->GetTitle());
		Int_t length = 0;
		if(regex->Index(name.Data(), &length) != -1)
		{
			TString type(leaf->GetTypeName());
			if(leaf->IsA() == TLeafElement::Class() || leaf->IsA() == TLeafObject::Class())
			{
				type.Append("*");
			}
			PrintVariable(type.Data(), name.Data());
			PrintDescription(leaf->GetBranch()->GetTitle());
			if(snippet)
			{
				PrintSnippet(type.Data(), name.Data());
			}
		}
	}
	
	delete tree;
	delete regex;
}
void PAFToolInspectTree::PrintDescription(const char* desc)
{
	if (desc)
	{
		PrintMessage(TString::Format("Desc.: %s ", desc));
	}
}

void PAFToolInspectTree::PrintVariable(const char* type, const char* name)
{
	PrintMessage(TString::Format("Type: %s \t\tVariable: %s", type, name));
}

void PAFToolInspectTree::PrintSnippet(const char* type, const char* name)
{
	PrintMessage(TString::Format("Use: \"%s %s = Get<%s>(\"%s\");\".\n", type, name, type, name));
}
