#include "PAFInspectTree.h"

#include "TTree.h"
#include "TFile.h"
#include "TLeaf.h"

#include <iostream>

void printError(){
	std::cout << "Arguments unrecognized." << std::endl;
}

void printHelp(){
	std::cout << "\"-h | --help\" to show command help." << std::endl;
	std::cout << "\"-b | --branch branchname\" to retrieve information about specified branch." << std::endl;
	std::cout << "\"-t | --tree treename\"  to retrieve information about specified tree." << std::endl;
}

void printVariables(const char* filename, const char* branch, const char* tree){
	if(tree == NULL){
		tree = "Tree";
	}
	
	TFile* file = new TFile(filename);
	TTree* tree = (TTree*)file->Get(tree);
	
	TObjArray* leaves = tree->GetListOfLeaves();
	Int_t nb = leaves->GetEntriesFast();
	for (Int_t i = 0; i < nb; ++i) {
		TLeaf* leaf = (TLeaf*)leaves->UncheckedAt(i);
		if(tree == NULL || leaf->GetName().EqualTo(branch)) {
			std::cout << leaf->GetName() << " type:" << leaf->GetTypeName() << std::endl;
		}
	}
	
	delete leaves;
	delete tree;
	delete file;
}

int main(int argc, char* argv[]){
	if(argc == 0){
		printHelp();
		return 0;
	}
	
	if(argc == 1 && (argv[0] == "-h" || argv[0] == "--help") ){
		printHelp();
		return 0;	
	}
	
	const char* tree = NULL;
	const char* branch = NULL;
	
	for(int i = 0; i < argc; i = i + 2){
		switch(argv[0]){
			case "-b":
			case "--branch":
				branch = argv[i + 1];
				break;
			case "-t":
			case "--tree":
				tree = argv[i + 1];
				break;
			default:
				printError();
		}
	}
	
	printVariables(argv[argc - 1], branch, tree);
	
	return 0;
}