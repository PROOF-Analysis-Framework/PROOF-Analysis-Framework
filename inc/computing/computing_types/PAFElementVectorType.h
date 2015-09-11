/**
	@brief Internal PAF class to holds TLeafElements with pointers to std::vectors.
	@file PAFElementType.h
	@class PAFElementType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-06-17
 */

#pragma once

#include "PAFElementType.h"
#include <vector>

template <class T>
class PAFElementVectorType : public PAFElementType
{
	public:
		PAFElementVectorType();
		PAFElementVectorType(TLeaf* leaf);
		virtual ~PAFElementVectorType();

		virtual void* GetPointer();
		virtual void* GetPointer(Int_t pos);
	
		virtual Int_t GetNData();

	protected:
		T fValue;

	ClassDef(PAFElementVectorType<T>, 1);
};

template <class T>
PAFElementVectorType<T>::PAFElementVectorType()
	: PAFElementType()
{

}

template <class T>
PAFElementVectorType<T>::PAFElementVectorType(TLeaf* leaf)
	: PAFElementType(leaf)
{

}

template <class T>
PAFElementVectorType<T>::~PAFElementVectorType()
{

}

template <class T>
void* PAFElementVectorType<T>::GetPointer()
{
	EnableBranch();
	return fLeaf->GetValuePointer();
}

template <class T>
void* PAFElementVectorType<T>::GetPointer(Int_t pos)
{
	EnableBranch();
	std::vector<T>* values = (std::vector<T>*)fLeaf->GetValuePointer();
	fValue = values->at(pos);
	return &fValue;
}

template <class T>
Int_t PAFElementVectorType<T>::GetNData()
{
	EnableBranch();
	return (int)((std::vector<T>*)fLeaf->GetValuePointer())->size();
}
