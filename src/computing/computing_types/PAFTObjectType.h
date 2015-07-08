/**
	@brief Internal PAF class to holds TObjects based on TLeafObject.
	@file PAFTObjectType.h
	@class PAFTObjectType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-06-17
*/

#pragma once

#include "PAFAbstractType.h"

class PAFTObjectType : public PAFAbstractType
{
	public:
		PAFTObjectType();
		PAFTObjectType(TLeaf* leaf);
		virtual ~PAFTObjectType();

		virtual void* GetPointer();
		virtual void* GetPointer(int pos);

	ClassDef(PAFTObjectType, 1);
};

