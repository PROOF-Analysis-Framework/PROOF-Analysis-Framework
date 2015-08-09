/**
	@brief Internal PAF class to holds ROOT arrays types (Float_t, Double_t...) TLeafs.
	@file PAFArrayPrimitiveType.h
	@class PAFArrayPrimitiveType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-06-17
 */

#pragma once

#include "PAFAbstractType.h"

template <class T>
class PAFArrayPrimitiveType : public PAFAbstractType
{
	public:
		PAFArrayPrimitiveType();
		PAFArrayPrimitiveType(TLeaf* leaf);
		virtual ~PAFArrayPrimitiveType();

		virtual void* GetPointer();
		virtual void* GetPointer(int pos);

		virtual int GetNData();

	protected:
		void* fPointer;

	ClassDef(PAFArrayPrimitiveType<T>, 1);
};

template <class T>
PAFArrayPrimitiveType<T>::PAFArrayPrimitiveType()
	: PAFAbstractType(), fPointer(NULL)
{

}

template <class T>
PAFArrayPrimitiveType<T>::PAFArrayPrimitiveType(TLeaf* leaf)
	: PAFAbstractType(leaf)
{

}

template <class T>
PAFArrayPrimitiveType<T>::~PAFArrayPrimitiveType()
{

}

template <class T>
void* PAFArrayPrimitiveType<T>::GetPointer()
{
	fPointer = fLeaf->GetValuePointer();
	return &fPointer;
}

template <class T>
void* PAFArrayPrimitiveType<T>::GetPointer(int pos)
{
	T* values = (T*)fLeaf->GetValuePointer();
	return &values[pos];
}

template <class T>
int PAFArrayPrimitiveType<T>::GetNData()
{
	return fLeaf->GetNdata();
}
