#pragma once

#include "PAFChainItemSelector.h"

class VectorDoubleTestSelector : public PAFChainItemSelector 
{
	public:
		VectorDoubleTestSelector() : PAFChainItemSelector(), sHisto(0) {}
		virtual ~VectorDoubleTestSelector() {}

		virtual void Initialise();
		virtual void InsideLoop();
		
	protected:
		TH1* sHisto;
		
   ClassDef(VectorDoubleTestSelector, 0);
};
