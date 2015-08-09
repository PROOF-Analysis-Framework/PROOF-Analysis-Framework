#pragma once

#include "PAFChainItemSelector.h"

class PrimitiveDoubleTestSelector : public PAFChainItemSelector 
{
	public:
		PrimitiveDoubleTestSelector() : PAFChainItemSelector(), sHisto(0) {}
		virtual ~PrimitiveDoubleTestSelector() {}

		virtual void Initialise();
		virtual void InsideLoop();
		
	protected:
		TH1* sHisto;
		
   ClassDef(PrimitiveDoubleTestSelector, 0);
};
