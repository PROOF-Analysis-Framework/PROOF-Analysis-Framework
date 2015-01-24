#pragma once

#include "../PAF/computing/PAFChainItemSelector.h"

#include "TH1F.h"
#include "TRandom3.h"

class PAFSimpleSelector : public PAFChainItemSelector {

	public:
		PAFSimpleSelector() : fH1F(0), fRandom(0) {}
		virtual ~PAFSimpleSelector() {}

		void Initialise();
		void InitialiseParameters() {}
		void InsideLoop();
		void Summary();
	protected:
		TH1F* fH1F;
		TRandom3* fRandom;

	ClassDef(PAFSimpleSelector, 1);
};

