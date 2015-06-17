/**
	@brief Internal PAF class to hold TLeafs of a TTree in order to be used by PAF.
	@file PAFIType.cxx
	@class PAFIType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-06-17
*/

#include "PAFIType.h"

ClassImp(PAFIType);

void* PAFIType::GetPointer(int pos)
{
	return NULL;
}

TLeaf* PAFIType::GetLeaf()
{
	return NULL;
}

int PAFIType::GetNData()
{
	return -1;
}

