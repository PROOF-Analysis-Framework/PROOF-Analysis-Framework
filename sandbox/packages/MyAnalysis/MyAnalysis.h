#pragma once

#include "PAF/computing/PAFChainItemSelector.h"

#include <TH1F.h>

class MyAnalysis : public PAFChainItemSelector {
	public:
		MyAnalysis() : PAFChainItemSelector(), myHistogram(0) {}
		virtual ~MyAnalysis() {}

	protected:
		virtual void Initialise();
		virtual void InsideLoop();
		virtual void Summary();

	protected:
		TH1F* myHistogram;
		
	ClassDef(MyAnalysis, 1);
};
