/**
	@brief Utility class to deal with strings.
	@file PAFStringUtil.cxx
	@class PAFStringUtil
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-02-12
*/

#include "PAFStringUtil.h"

std::vector< TString* >* PAFStringUtil::Split(TString* string, const char* cs)
{
	std::vector<TString*>* result = new std::vector<TString*>();
	
	while(string->Length() > 0)
	{
		int indexnext = string->First(cs);
		indexnext = indexnext > 0 ? indexnext : string->Length();
		TString* dir = new TString(string->Data(), indexnext);
		result->push_back(dir);
		string->Remove(0, indexnext + 1);
	}
	
	return result;
}
