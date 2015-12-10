#pragma once

#include "PAFChainItemSelector.h"

class GetSizeOfBoolTestSelector : public PAFChainItemSelector
{
	public:
		GetSizeOfBoolTestSelector() : PAFChainItemSelector(), sHisto(0) {}
		virtual ~GetSizeOfBoolTestSelector() {}

		virtual void Initialise();
		virtual void InsideLoop();

	protected:
		TH1* sHisto;

   ClassDef(GetSizeOfBoolTestSelector, 0);
};
