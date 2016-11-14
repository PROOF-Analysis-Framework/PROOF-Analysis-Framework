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
		inline PAFVariableContainer();
		inline virtual ~PAFVariableContainer();

		template<typename T>
		void Add(const char* key, T value);

		void Add(const char* key, const char* value);

		template<typename T>
		T Get(const char* key);

		void Add(PAFVariableContainer*);

		TList* GetKeys();

		bool Exists(const char* key);

	protected:
		TMap fPairs;

	ClassDef(PAFVariableContainer, 1);
};



//----------------------------------------------------------------------
// Template methods
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

inline void PAFVariableContainer::Add(const char* key, const char* value)
{
	TObjString* objKey = new TObjString(key);
	TString strvalue(value);

	delete fPairs.Remove(objKey);

	fPairs.Add(objKey,  new PAFGenericItemVariableContainer<TString>(strvalue));
}


//----------------------------------------------------------------------
// Inline methods

PAFVariableContainer::PAFVariableContainer():TObject(), fPairs() {}

PAFVariableContainer::~PAFVariableContainer() {}
