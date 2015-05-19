#pragma once

#include "PAF/computing/PAFChainItemSelector.h"

class VariableGetter : public PAFChainItemSelector 
{
	public:
		VariableGetter() : PAFChainItemSelector() {}
		virtual ~VariableGetter() {}

		virtual void InsideLoop();
		
	ClassDef(VariableGetter, 0);
};
