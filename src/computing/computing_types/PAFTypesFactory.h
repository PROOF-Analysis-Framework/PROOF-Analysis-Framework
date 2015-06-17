/**
	@brief Factory method pattern to create PAF types from TLeafs.
	@file PAFTypesFactory.h
	@class PAFTypesFactory
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-06-17
*/

#pragma once

#include "TObject.h"

#include "PAFIType.h"
#include "TLeaf.h"

class PAFTypesFactory : public TObject
{
	public:
		PAFIType* GetPAFType(TLeaf* leaf);
		
	ClassDef(PAFTypesFactory, 1);
};

