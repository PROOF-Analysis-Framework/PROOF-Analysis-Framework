#pragma once

#include "PAF/computing/PAFChainItemSelector.h"

class PassingParametersObjectsSeedTestSelector : public PAFChainItemSelector 
{
	public:
		PassingParametersObjectsSeedTestSelector() : PAFChainItemSelector() {}
		virtual ~PassingParametersObjectsSeedTestSelector() {}

		virtual void InsideLoop();

	ClassDef(PassingParametersObjectsSeedTestSelector, 0);
};
