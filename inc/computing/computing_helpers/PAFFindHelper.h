/**
	@brief Class that provides you different TList searches.
	@file PAFFindHelper.h
	@class PAFFindHelper
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-02-01
 */

#pragma once

#include "TObject.h"
#include "TList.h"

#include "PAFNamedItem.h"

#include "PAF.h"

class PAFFindHelper 
{
	public:
		template <typename T>
		static T Find(TList* list, TString& name);

		template <typename T>
		static T Find(TList* list, const char* name);

		template <typename T>
		static T FindPAFNamed(TList* list, TString& name);

		template <typename T>
		static T FindPAFNamed(TList* list, const char* name);
};

template <typename T>
inline T PAFFindHelper::Find(TList* list, TString& name)
{
	TObject* tmpobj = 0;
	for(Int_t i = 0; i < list->GetEntries(); i++)
	{
		tmpobj = list->At(i);
		if(name.EqualTo(tmpobj->GetName()))
		{
			return (T)tmpobj;
		}
	}
	PAF_ERROR("PAFFinderHelper", "Object not found");
	return NULL;
}

template <typename T>
inline T PAFFindHelper::Find(TList* list, const char* name)
{
	TString tName(name);
	return Find<T>(list, tName);
}

template <typename T>
inline T PAFFindHelper::FindPAFNamed(TList* list, TString& name)
{
	PAFNamedItem* result = Find<PAFNamedItem*>(list, name);

	if(!result)
	{
		return NULL;
	}

	return (T)result->GetObject();
}

template <typename T>
inline T PAFFindHelper::FindPAFNamed(TList* list, const char* name)
{
	TString tName(name);
	return FindPAFNamed<T>(list, tName);
}
