#include "PAFInspectTree.h"

#include "TLeaf.h"
#include "TRegexp.h"
#include "TString.h"
#include "THashList.h"

#include <iostream>

void PrintMessage(const char* message)
{
	std::cout << message << std::endl;
}

void PrintVariable(const char* type, const char* name)
{
	std::cout << "Type: " << type << " \t\tVariable: " << name <<  std::endl;
}

void PrintHelp()
{
	PrintMessage("\t\"-h | --help\" to show command help.");
	PrintMessage("\t\"-b | --branch branchname\" to retrieve information about specified branch.");
	PrintMessage("\t\"-t | --tree treename\"  to retrieve information about specified tree.");
	
	PrintMessage("\t ROOT file name. Mandatory.");
}

void PrintVariables(TTree* tree, const char* branchName)
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
			PrintVariable(leaf->GetTypeName(), name.Data());
		}
	}
	
	delete tree;
	delete regex;
}

TTree* GetTree(TFile* rootFile, const char* treeName)
{
	return (TTree*)rootFile->Get(treeName);
}

TTree* GetAutoTree(TFile* rootFile)
{
	THashList* trees = (THashList*)rootFile->GetListOfKeys();
	TTree* result = NULL;
	
	if(trees->GetSize() == 1)
	{
		TObject* uniqueTree = trees->First();
		PrintMessage( TString::Format("Selecting the unique Tree: \"%s\"", uniqueTree->GetName()).Data() );
		result = (TTree*)rootFile->Get(uniqueTree->GetName());
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

int main(int argc, const char* argv[])
{
	if(argc == 1)
	{
		PrintHelp();
		return 1;
	}
	
	if(argc == 2 && (TString(argv[1]).EqualTo("-h") || TString(argv[1]).EqualTo("--help")) )
	{
		PrintHelp();
		return 0;	
	}
	
	const char* branchName = NULL;
	const char* treeName = NULL;
	TFile* rootFile = new TFile(argv[argc - 1]);
	
	for(int i = 1; i < argc; i = i + 2)
	{
		TString item = argv[i];		
		if(item.EqualTo("-b") || item.EqualTo("--branch")){
			branchName = argv[i + 1];
		} else if (item.EqualTo("-t") || item.EqualTo("--tree")) {
			treeName = argv[i + 1];
		}
	}
	
	TTree* tree = treeName ? GetTree(rootFile, treeName) : GetAutoTree(rootFile);
	
	if(tree)
	{
		PrintVariables(tree, branchName);
	}
	
	return 0;
}
