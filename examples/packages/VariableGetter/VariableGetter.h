#pragma once

#include "PAFChainItemSelector.h"

class VariableGetter : public PAFChainItemSelector 
{
	public:
		VariableGetter() : PAFChainItemSelector() {}
		virtual ~VariableGetter() {}

		virtual void InsideLoop();
		
	ClassDef(VariableGetter, 0);
};
