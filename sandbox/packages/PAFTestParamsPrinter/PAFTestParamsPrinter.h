#pragma once

#include "../PAF/computing/PAFChainItemSelector.h"

#include "TH1F.h"

class PAFTestParamsPrinter : public PAFChainItemSelector {

	public:
		PAFTestParamsPrinter () : fH1F(0) {}
		virtual ~PAFTestParamsPrinter () {}

		void Initialise();
		void InitialiseParameters() {}
		void InsideLoop();
		void Summary();
	protected:
		TH1F* fH1F;

	ClassDef(PAFTestParamsPrinter , 1);
};

