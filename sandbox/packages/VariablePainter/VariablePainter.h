#pragma once

#include "PAF/computing/PAFChainItemSelector.h"

#include <TH1F.h>

class VariablePainter : public PAFChainItemSelector {
	public:
		VariablePainter() : PAFChainItemSelector(), myHistogram(0) {}
		virtual ~VariablePainter() {}

	protected:
		virtual void Initialise();
		virtual void InsideLoop();
		virtual void Summary();

	protected:
		TH1F* myHistogram;
		
	ClassDef(VariablePainter, 1);
};
