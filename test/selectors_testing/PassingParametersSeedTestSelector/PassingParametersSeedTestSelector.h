#pragma once

#include "PAFChainItemSelector.h"

class PassingParametersSeedTestSelector : public PAFChainItemSelector 
{
	public:
		PassingParametersSeedTestSelector() : PAFChainItemSelector() {}
		virtual ~PassingParametersSeedTestSelector() {}

		virtual void InsideLoop();

	ClassDef(PassingParametersSeedTestSelector, 0);
};
