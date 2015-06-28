#pragma once

#include "PAF/computing/PAFChainItemSelector.h"

class PassingParametersConsumerTestSelector : public PAFChainItemSelector 
{
	public:
		PassingParametersConsumerTestSelector() : PAFChainItemSelector(), sHisto(0) {}
		virtual ~PassingParametersConsumerTestSelector() {}

		virtual void Initialise();
		virtual void InsideLoop();
		
	protected:
		TH1* sHisto;
		
   ClassDef(PassingParametersConsumerTestSelector, 0);
};
