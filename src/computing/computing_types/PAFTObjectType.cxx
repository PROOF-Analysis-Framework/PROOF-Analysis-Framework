/**
	@brief Internal PAF class to holds TObjects based on TLeafObject.
	@file PAFTObjectType.cxx
	@class PAFTObjectType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-06-17
 */

#include "PAFTObjectType.h"

ClassImp(PAFTObjectType);

PAFTObjectType::PAFTObjectType()
	: PAFAbstractType()
{

}

PAFTObjectType::PAFTObjectType(TLeaf* leaf)
	: PAFAbstractType(leaf)
{

}

PAFTObjectType::~PAFTObjectType()
{

}

void* PAFTObjectType::GetPointer()
{
	return fLeaf->GetValuePointer();
}


void* PAFTObjectType::GetPointer(int /*pos*/)
{
	return fLeaf->GetValuePointer();
}
