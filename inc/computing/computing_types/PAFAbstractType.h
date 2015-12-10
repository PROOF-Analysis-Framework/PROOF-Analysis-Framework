/**
	@brief Internal PAF class to abstract some common implemtation of concretes PAFITypes.
	@file PAFAbstractType.h
	@class PAFAbstractType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-06-17
 */

#pragma once

#include "PAFIType.h"

class PAFAbstractType : public PAFIType
{
	public:
		PAFAbstractType();
		PAFAbstractType(TLeaf* leaf);
		virtual ~PAFAbstractType();

		virtual void SetTLeaf(TLeaf* leaf);
		virtual TLeaf* GetLeaf();

		virtual Int_t GetNData();
		
		virtual void EnableBranch();

	protected:
		TLeaf* fLeaf;
		void* chore;

	ClassDef(PAFAbstractType, 1);
};
