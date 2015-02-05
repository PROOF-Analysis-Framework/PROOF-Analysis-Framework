#include "MyAnalysisMiniTrees.h"

#include <iostream>

void MyAnalysisMiniTrees::Initialise() {
	GetParam("ss", ss);
	GetParam("ii", ii);
	GetParam("dd", dd);
	GetParam("db", db);
	GetParam("bb", bb);
	GetParam("sel1", sss);
	GetParam("i1", iii);
	GetParam("d1", ddd);
	GetParam("db1", ddb);
	GetParam("b1", bb);
	
	std::cout << ss << ", " << ii << ", " << dd << ", " << db << ", " << bb << ", " << sss << ", " << iii << ", " << ddd << ", " << ddb << ", " << bb << std::endl;
	
	myHistogram = CreateH1F("myHistogram","#slash{E}_{T}", 100, 0., 200.);
	myTree = CreateTree("Tree","my Tree");
	myTree->Branch("METET",&tMetEt,"tMetEt/D");
}

void MyAnalysisMiniTrees::InsideLoop() {
	myHistogram->Fill(fData->T_METPF_ET);

	tMetEt = fData->T_METPF_ET;
	myTree->Fill();
}
