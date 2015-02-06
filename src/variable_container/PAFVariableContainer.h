/**
	@brief Internal PAF class to store variables of any type.
	@file PAFVariableContainer.h
	@class PAFVariableContainer
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-01-26
*/

#pragma once

#include <map>
#include <vector>

#include "TObject.h"
#include "TString.h"

#include "PAFItemVariableContainer.h"
#include "PAFGenericItemVariableContainer.h"

class PAFVariableContainer : public TObject
{
	public:
		PAFVariableContainer() : TObject(), fPairs() {}		
		virtual ~PAFVariableContainer();
		
		template<typename T>
		void Add(TString& key, T value);
		
		template<typename T>
		void Add(const char* key, T value);
		
		template<typename T>
		T Get(TString& key);
		
		template<typename T>
		T Get(const char* key);
		
		bool Exists(TString& key);
		bool Exists(const char* key);
		
		std::vector<TString>* GetKeys();
		
	private:
		std::map<TString, PAFItemVariableContainer*> fPairs;
		
	ClassDef(PAFVariableContainer, 1);
};

template <typename T>
inline void PAFVariableContainer::Add(TString& key, T value)
{
	fPairs[key] = new PAFGenericItemVariableContainer<T>(value);
}

template <typename T>
inline void PAFVariableContainer::Add(const char* key, T value)
{
	TString tkey(key);
	Add(tkey, value);
}

template <typename T>
inline T PAFVariableContainer::Get(TString& key)
{
	PAFItemVariableContainer* result = fPairs[key];
	return ((PAFGenericItemVariableContainer<T>*)result)->Get();
}

template <typename T>
inline T PAFVariableContainer::Get(const char* key)
{
	TString tkey(key);
	return Get<T>(tkey);
}
