#pragma once

#include "PAFChainItemSelector.h"

class PrimitiveLongTestSelector : public PAFChainItemSelector 
{
	public:
		PrimitiveLongTestSelector() : PAFChainItemSelector(), sHisto(0) {}
		virtual ~PrimitiveLongTestSelector() {}

		virtual void Initialise();
		virtual void InsideLoop();
		
	protected:
		TH1* sHisto;
		
   ClassDef(PrimitiveLongTestSelector, 0);
};
