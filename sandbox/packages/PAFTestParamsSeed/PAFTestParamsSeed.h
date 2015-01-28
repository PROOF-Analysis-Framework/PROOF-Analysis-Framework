#pragma once

#include "../PAF/computing/PAFChainItemSelector.h"

#include "TRandom3.h"

class PAFTestParamsSeed : public PAFChainItemSelector {

	public:
		PAFTestParamsSeed() : fRandom(0) {}
		virtual ~PAFTestParamsSeed() {}

		void Initialise();
		void InitialiseParameters() {}
		void InsideLoop();
		void Summary() {}
	protected:
		TRandom3* fRandom;

	ClassDef(PAFTestParamsSeed, 1);
};

