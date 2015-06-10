#pragma once

#include "PAF/computing/PAFChainItemSelector.h"

class VectorTLorentzTestSelector : public PAFChainItemSelector 
{
	public:
		VectorTLorentzTestSelector() : PAFChainItemSelector(), sHisto(0) {}
		virtual ~VectorTLorentzTestSelector() {}

		virtual void Initialise();
		virtual void InsideLoop();
		
	protected:
		TH1* sHisto;
		
   ClassDef(VectorTLorentzTestSelector, 0);
};
