#include "PAFInspectTree.h"

#include "TTree.h"
#include "TFile.h"
#include "TLeaf.h"

#include <iostream>

int main(int argc, char* argv[]){
	
	/*TFile* file = new TFile(argv[0]);
	TTree* tree = (TTree*)file->Get("Tree");
	
	TObjArray* leaves = tree->GetListOfLeaves();
	Int_t nb = leaves->GetEntriesFast();
	for (Int_t i = 0; i < nb; ++i) {
		TLeaf* leaf = (TLeaf*)leaves->UncheckedAt(i);
		std::cout << leaf->GetName() << " type:" << leaf->GetTypeName() << std::endl;
	}
	
	delete leaves;
	delete tree;
	delete file;*/
	
	return 0;
}