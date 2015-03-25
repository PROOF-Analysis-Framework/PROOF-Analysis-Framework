#pragma once

#include "PAF/computing/PAFChainItemSelector.h"

#include <TH1F.h>

class MyVariablePainter : public PAFChainItemSelector {
	public:
		MyVariablePainter() : PAFChainItemSelector(), myHistogram(0) {}
		virtual ~MyVariablePainter() {}

	protected:
		virtual void Initialise();
		virtual void InsideLoop();
		virtual void Summary();

	protected:
		TH1F* myHistogram;
		
	ClassDef(MyVariablePainter, 1);
};
