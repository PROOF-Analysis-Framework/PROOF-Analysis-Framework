/**
	@brief Internal PAF class to hold TLeafs of a TTree in order to be used by PAF.
	@file PAFIType.h
	@class PAFIType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-06-17
 */

#pragma once

#include "TObject.h"

#include "TLeaf.h"

class PAFIType : public TObject
{
	public:
		virtual void* GetPointer();
		virtual void* GetPointer(Int_t pos);

		virtual TLeaf* GetLeaf();
		
		virtual Int_t GetNData();

	ClassDef(PAFIType, 1);
};
