#pragma once

#include "PAFChainItemSelector.h"

class PrimitiveFloatTestSelector : public PAFChainItemSelector 
{
	public:
		PrimitiveFloatTestSelector() : PAFChainItemSelector(), sHisto(0) {}
		virtual ~PrimitiveFloatTestSelector() {}

		virtual void Initialise();
		virtual void InsideLoop();
		
	protected:
		TH1* sHisto;
		
   ClassDef(PrimitiveFloatTestSelector, 0);
};
