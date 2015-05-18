#pragma once

#include "PAF/computing/PAFChainItemSelector.h"

class VariableGetter : public PAFChainItemSelector 
{
	public:
		VariableGetter() : PAFChainItemSelector() {}
		virtual ~VariableGetter() {}

	protected:
		virtual void InsideLoop();
		
	ClassDef(VariableGetter, 0);
};
