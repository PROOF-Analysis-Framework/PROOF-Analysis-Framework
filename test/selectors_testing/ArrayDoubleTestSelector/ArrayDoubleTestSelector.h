#pragma once

#include "PAF/computing/PAFChainItemSelector.h"

class ArrayDoubleTestSelector : public PAFChainItemSelector 
{
	public:
		ArrayDoubleTestSelector() : PAFChainItemSelector(), sHisto(0) {}
		virtual ~ArrayDoubleTestSelector() {}

		virtual void Initialise();
		virtual void InsideLoop();
		
	protected:
		TH1* sHisto;
		
   ClassDef(ArrayDoubleTestSelector, 0);
};
