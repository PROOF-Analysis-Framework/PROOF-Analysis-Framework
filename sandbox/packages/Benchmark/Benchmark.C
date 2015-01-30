#include "Benchmark.h"
#include "../PAFAnalysis/PAFAnalysis.h"

void Benchmark::Initialise() {
	etHisto		= CreateH1F("etHistogram","EtHistogram", 100, 0., 200.);
	phiHisto	= CreateH1F("phiHistogram","PhiHistogram", 100, 0., 200.);
	sigHisto	= CreateH1F("sigHistogram","SigHistogram", 100, 0., 200.);
}

void Benchmark::InsideLoop() {
	GetVariable("T_METPF_ET", tMetEt);
	GetVariable("T_METPF_Phi", tMetPhi);
	GetVariable("T_METPF_Sig", tMetSig);
	GetVariable("T_METgen_ET", tMetGenEt);
	GetVariable("T_METgen_Phi", tMetGenPhi);
	
	etHisto->Fill(tMetEt/tMetGenEt);
	phiHisto->Fill(tMetPhi/tMetGenPhi);
	sigHisto->Fill(tMetSig);
}
