/**
	@brief Internal generic PAF class to store a variable of any type.
	@file PAFGenericItemVariableContainer.h
	@class PAFGenericItemVariableContainer
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-01-26
 */

#pragma once

#include "TObject.h"

#include <iostream>

template <class T>
class PAFGenericItemVariableContainer : public TObject
{
	public:
		PAFGenericItemVariableContainer() : TObject() {}
		PAFGenericItemVariableContainer(const T& object) : TObject(), fObject(object) {}
		virtual ~PAFGenericItemVariableContainer() {}

		void Set(const T& object) { fObject = object; }
		T Get() const { return fObject; }

		//TODO Maybe an "IsType" function could facilitate the evolution.
	private:
		T fObject;

	ClassDef(PAFGenericItemVariableContainer<T>, 1);
};
