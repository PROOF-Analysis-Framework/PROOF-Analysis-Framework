#include "Benchmark.h"

void Benchmark::Initialise() {
	etHisto		= CreateH1F("etHistogram","EtHistogram", 100, 0., 200.);
	phiHisto	= CreateH1F("phiHistogram","PhiHistogram", 100, 0., 200.);
	sigHisto	= CreateH1F("sigHistogram","SigHistogram", 100, 0., 200.);
}

void Benchmark::InsideLoop() {
	Assign("T_METPF_ET", tMetEt);
	Assign("T_METPF_Phi", tMetPhi);
	Assign("T_METPF_Sig", tMetSig);
	Assign("T_METgen_ET", tMetGenEt);
	Assign("T_METgen_Phi", tMetGenPhi);
	
	etHisto->Fill(tMetEt/tMetGenEt);
	phiHisto->Fill(tMetPhi/tMetGenPhi);
	sigHisto->Fill(tMetSig);
}
