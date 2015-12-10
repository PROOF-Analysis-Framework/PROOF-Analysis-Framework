/**
	@brief Internal PAF class to holds ROOT types (Float_t, Double_t...) TLeafs.
	@file PAFPrimitiveType.h
	@class PAFPrimitiveType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-06-17
 */

#pragma once

#include "PAFAbstractType.h"

template <class T>
class PAFPrimitiveType : public PAFAbstractType
{
	public:
		PAFPrimitiveType();
		PAFPrimitiveType(TLeaf* leaf);
		virtual ~PAFPrimitiveType();

		virtual void* GetPointer();
		virtual void* GetPointer(Int_t pos);

	ClassDef(PAFPrimitiveType<T>, 1);
};

template <class T>
PAFPrimitiveType<T>::PAFPrimitiveType()
	: PAFAbstractType()
{

}

template <class T>
PAFPrimitiveType<T>::PAFPrimitiveType(TLeaf* leaf)
	: PAFAbstractType(leaf)
{

}

template <class T>
PAFPrimitiveType<T>::~PAFPrimitiveType()
{

}

template <class T>
void* PAFPrimitiveType<T>::GetPointer()
{
	EnableBranch();
	T* values = (T*)fLeaf->GetValuePointer();
	return &values[0];
}

template <class T>
void* PAFPrimitiveType<T>::GetPointer(Int_t pos)
{
	EnableBranch();
	T* values = (T*)fLeaf->GetValuePointer();
	return &values[pos];
}
