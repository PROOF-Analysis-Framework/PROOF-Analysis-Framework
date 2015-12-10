#pragma once

#include "PAFChainItemSelector.h"

class GetSizeOfDoubleTestSelector : public PAFChainItemSelector
{
	public:
		GetSizeOfDoubleTestSelector() : PAFChainItemSelector(), sHisto(0) {}
		virtual ~GetSizeOfDoubleTestSelector() {}

		virtual void Initialise();
		virtual void InsideLoop();

	protected:
		TH1* sHisto;

   ClassDef(GetSizeOfDoubleTestSelector, 0);
};
