#pragma once

#include "PAF/computing/PAFChainItemSelector.h"

class Prueba : public PAFChainItemSelector 
{
	public:
		Prueba() : PAFChainItemSelector() {}
		virtual ~Prueba() {}

		virtual void Initialise();
		virtual void InsideLoop();
		virtual void Summary();

	protected:

   ClassDef(Prueba,0);
};
