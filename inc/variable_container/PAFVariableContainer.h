/**;
	@brief Internal PAF class to store variables of any type.
	@file PAFVariableContainer.h
	@class PAFVariableContainer
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-01-26
 */

#pragma once

#include "TMap.h"
#include "TList.h"
#include "TObject.h"
#include "TObjString.h"
#include "TString.h"

#include "PAFGenericItemVariableContainer.h"

class PAFVariableContainer : public TObject
{
	public:
		PAFVariableContainer();
		virtual ~PAFVariableContainer();

		template<typename T>
		void Add(const char* key, T value);

		template<typename T>
		T Get(const char* key);

		TList* GetKeys();

		bool Exists(const char* key);

	protected:
		TMap fPairs;

	ClassDef(PAFVariableContainer, 1);
};

template <typename T>
inline void PAFVariableContainer::Add(const char* key, T value)
{
	TObjString* objKey = new TObjString(key);

	delete fPairs.Remove(objKey);

	fPairs.Add(objKey, new PAFGenericItemVariableContainer<T>(value));
}

template <typename T>
inline T PAFVariableContainer::Get(const char* key)
{
	TObjString tKey(key);
	PAFGenericItemVariableContainer<T>* result = (PAFGenericItemVariableContainer<T>*)fPairs.GetValue(&tKey);
	return result->Get();
}
