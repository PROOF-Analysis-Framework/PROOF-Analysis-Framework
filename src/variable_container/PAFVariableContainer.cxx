/**
	@brief Internal PAF class to store variables of any type.
	@file PAFVariableContainer.cpp
	@class PAFVariableContainer
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-01-26
 */

#include "PAFVariableContainer.h"

#include "PAF.h"

ClassImp(PAFVariableContainer);

void PAFVariableContainer::Add(PAFVariableContainer* other) {
  if (other) {
	const THashTable* table = other->fPairs.GetTable();
	
	TIterator* it = table->MakeIterator();
	TObject* current = 0;
	while( (current = it->Next()) )
	{
		TPair* item = (TPair*)current;
		fPairs.Add(item->Key()->Clone(), item->Value()->Clone());
	}
  }

}



TList* PAFVariableContainer::GetKeys()
{
	TList* result = new TList();
	
	const THashTable* table = fPairs.GetTable();
	
	TIterator* it = table->MakeIterator();
	TObject* current = NULL;
	while( (current = it->Next()) )
	{
		TPair* item = (TPair*)current;
		result->Add(item->Key()->Clone());
	}
	
	return result;
}

bool PAFVariableContainer::Exists(const char* key)
{
	TString tkey (key);
	return Exists(tkey);
}

