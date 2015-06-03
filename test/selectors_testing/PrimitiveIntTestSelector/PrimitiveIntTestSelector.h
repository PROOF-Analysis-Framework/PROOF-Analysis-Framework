#pragma once

#include "PAF/computing/PAFChainItemSelector.h"

class PrimitiveIntTestSelector : public PAFChainItemSelector 
{
	public:
		PrimitiveIntTestSelector() : PAFChainItemSelector(), sHisto(0) {}
		virtual ~PrimitiveIntTestSelector() {}

		virtual void Initialise();
		virtual void InsideLoop();
		
	protected:
		TH1* sHisto;
		
   ClassDef(PrimitiveIntTestSelector, 0);
};
