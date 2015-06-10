#pragma once

#include "PAF/computing/PAFChainItemSelector.h"

class GetSizeOfIntTestSelector : public PAFChainItemSelector
{
	public:
		GetSizeOfIntTestSelector() : PAFChainItemSelector(), sHisto(0) {}
		virtual ~GetSizeOfIntTestSelector() {}

		virtual void Initialise();
		virtual void InsideLoop();

	protected:
		TH1* sHisto;

   ClassDef(GetSizeOfIntTestSelector, 0);
};
