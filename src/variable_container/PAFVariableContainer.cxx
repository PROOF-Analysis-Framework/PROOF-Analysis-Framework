/**
	@brief Internal PAF class to store variables of any type.
	@file PAFVariableContainer.cpp
	@class PAFVariableContainer
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-01-26
*/

#include "PAFVariableContainer.h"

ClassImp(PAFVariableContainer);

bool PAFVariableContainer::Exists(TString& key)
{
	return fPairs[key] != NULL;
}

bool PAFVariableContainer::Exists(const char* key)
{
	TString tkey (key);
	return Exists(tkey);
}

std::vector< TString >* PAFVariableContainer::GetKeys()
{
	std::vector<TString>* result = new std::vector<TString>();
	
	for (std::map<TString,PAFItemVariableContainer*>::iterator it=fPairs.begin();
		 it!=fPairs.end(); ++it)
		 result->push_back(it->first);
    
    return result;
}
