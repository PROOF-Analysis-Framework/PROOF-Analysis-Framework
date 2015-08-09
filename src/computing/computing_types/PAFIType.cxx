/**
	@brief Internal PAF class to hold TLeafs of a TTree in order to be used by PAF.
	@file PAFIType.cxx
	@class PAFIType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-06-17
 */

#include "PAFIType.h"

#include "PAF.h"

ClassImp(PAFIType);

void* PAFIType::GetPointer()
{
	PAF_FATAL("PAFIType", "It is being executed an interface method.");
	return NULL;
}

void* PAFIType::GetPointer(int /*pos*/)
{
	PAF_FATAL("PAFIType", "It is being executed an interface method.");
	return NULL;
}

TLeaf* PAFIType::GetLeaf()
{
	PAF_FATAL("PAFIType", "It is being executed an interface method.");
	return NULL;
}

int PAFIType::GetNData()
{
	PAF_FATAL("PAFIType", "It is being executed an interface method.");
	return -1;
}
