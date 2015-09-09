#pragma once

#include "PAFChainItemSelector.h"

#include "TH1F.h"

class VariablePainter : public PAFChainItemSelector {
	public:
		VariablePainter() : PAFChainItemSelector(), myHistogram(0) {}
		virtual ~VariablePainter() {}

		virtual void Initialise();
		virtual void InsideLoop();
		virtual void Summary();

	protected:
		TH1F* myHistogram;
		
	ClassDef(VariablePainter, 1);
};
