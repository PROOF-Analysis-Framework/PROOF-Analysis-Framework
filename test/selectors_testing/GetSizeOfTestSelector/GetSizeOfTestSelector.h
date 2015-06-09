#pragma once

#include "PAF/computing/PAFChainItemSelector.h"

class GetSizeOfTestSelector : public PAFChainItemSelector
{
	public:
		GetSizeOfTestSelector() : PAFChainItemSelector(), sHisto(0) {}
		virtual ~GetSizeOfTestSelector() {}

		virtual void Initialise();
		virtual void InsideLoop();

	protected:
		TH1* sHisto;

   ClassDef(GetSizeOfTestSelector, 0);
};
