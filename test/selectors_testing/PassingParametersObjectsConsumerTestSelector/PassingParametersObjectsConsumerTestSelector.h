#pragma once

#include "PAFChainItemSelector.h"

class PassingParametersObjectsConsumerTestSelector : public PAFChainItemSelector 
{
	public:
		PassingParametersObjectsConsumerTestSelector() : PAFChainItemSelector(), sHisto(0) {}
		virtual ~PassingParametersObjectsConsumerTestSelector() {}

		virtual void Initialise();
		virtual void InsideLoop();
		
	protected:
		TH1* sHisto;
		
   ClassDef(PassingParametersObjectsConsumerTestSelector, 0);
};
