#pragma once

#include "PAF/computing/PAFChainItemSelector.h"

class MyVariableGetter : public PAFChainItemSelector {
	public:
		MyVariableGetter() : PAFChainItemSelector() {}
		virtual ~MyVariableGetter() {}

	protected:
		virtual void InsideLoop();
		
	ClassDef(MyVariableGetter, 1);
};
