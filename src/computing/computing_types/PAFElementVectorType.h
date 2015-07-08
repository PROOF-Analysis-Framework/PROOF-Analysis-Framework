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
		PAFElementVectorType() : PAFElementType() {}
		PAFElementVectorType(TLeaf* leaf) : PAFElementType(leaf) {}
		virtual ~PAFElementVectorType() {}

		virtual void* GetPointer();
		virtual void* GetPointer(int pos);
	
		virtual int GetNData();

	protected:
		T fValue;

	ClassDef(PAFElementVectorType<T>, 1);
};

template <class T>
inline void* PAFElementVectorType<T>::GetPointer()
{
	return fLeaf->GetValuePointer();
}

template <class T>
inline void* PAFElementVectorType<T>::GetPointer(int pos)
{
	std::vector<T>* values = (std::vector<T>*)fLeaf->GetValuePointer();
	fValue = values->at(pos);
	return &fValue;
}

template <class T>
inline int PAFElementVectorType<T>::GetNData()
{
	return (int)((std::vector<T>*)fLeaf->GetValuePointer())->size();
}

