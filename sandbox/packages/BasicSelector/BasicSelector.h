#pragma once

#include "PAF/computing/PAFChainItemSelector.h"

#include "TH1F.h"

class BasicSelector : public PAFChainItemSelector 
{
	public:
		BasicSelector() : PAFChainItemSelector(), etHisto(0) {}
		virtual ~BasicSelector() {}

	protected:
		virtual void Initialise();
		virtual void InsideLoop();
		virtual void Summary();

	protected:
		TH1F* etHisto;
		
   ClassDef(BasicSelector,0);
};

