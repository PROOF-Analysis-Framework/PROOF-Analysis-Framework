/**
	@brief Interface to create a composite pattern. Implemented by PAFChainSelector and PAFChainItemSelector. 
	@file PAFISelector.cxx
	@class PAFISelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
 */

#include "PAFISelector.h"

#include "PAF.h"

ClassImp(PAFISelector);

PAFISelector::PAFISelector()
{

}

PAFISelector::~PAFISelector()
{

}

void PAFISelector::Initialise()
{
	PAF_FATAL("PAFISelector", "It is being executed an interface method.");
}

void PAFISelector::InitialiseParameters()
{
	PAF_FATAL("PAFISelector", "It is being executed an interface method.");
}

void PAFISelector::InsideLoop()
{
	PAF_FATAL("PAFISelector", "It is being executed an interface method.");
}

void PAFISelector::Summary()
{
	PAF_FATAL("PAFISelector", "It is being executed an interface method.");
}

void PAFISelector::SetStaticData(TList* /*fInput*/, TSelectorList* /*fOutput*/, PAFVariableContainer* /*selectorParams*/)
{
	PAF_FATAL("PAFISelector", "It is being executed an interface method.");
}

void PAFISelector::SetDynamicData(PAFVariableContainer* /*variables*/)
{
	PAF_FATAL("PAFISelector", "It is being executed an interface method.");
}
