#pragma once

#include "PAF/computing/PAFChainItemSelector.h"

#include "PAF/PAF.h"

#include <TH1F.h>

class Benchmark : public PAFChainItemSelector {
	public:
		Benchmark() : PAFChainItemSelector(), etHisto(0), phiHisto(0), sigHisto(0) {}
		virtual ~Benchmark() {}

	protected:
		virtual void Initialise();
		virtual void InsideLoop();
		virtual void Summary() {}

	protected:
		TH1F*		etHisto;
		TH1F*		phiHisto;
		TH1F*		sigHisto;
		
		Float_t     tMetEt;
		Float_t     tMetPhi;
		Float_t     tMetSig;
		Float_t		tMetGenEt;
		Float_t		tMetGenPhi;

   ClassDef(Benchmark,0);
};

