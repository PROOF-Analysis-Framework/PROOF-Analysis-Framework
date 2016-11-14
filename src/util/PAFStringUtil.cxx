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
		indexnext = indexnext >= 0 ? indexnext : string->Length();
		TString* dir = new TString(string->Data(), indexnext);
		if(!dir->IsNull())
		{
			result->push_back(dir);
		}
		string->Remove(0, indexnext + 1);
	}

	return result;
}


TString PAFStringUtil::GetDirectoryFromObjName(const TString& objName)
{
	TString tObjName = objName;
	std::vector<TString*>* parts = PAFStringUtil::Split(&tObjName, "/");
	
	TString result;
	
	if(parts->size() > 0)
	{
		for(unsigned int i = 0; i < parts->size() - 1; i++)
		{
			result.Append(parts->at(i)->Data());
		}
	}
	
	parts->clear();
	delete parts;
	
	return result;
}


TString PAFStringUtil::GetNameFromObjName(const TString& objName)
{
	TString tObjName = objName;
	std::vector<TString*>* parts = PAFStringUtil::Split(&tObjName, "/");
	
	TString result;
	
	if(parts->size() > 0)
	{
		result = (parts->at(parts->size() - 1))->Copy();
	}
	
	parts->clear();
	delete parts;
	
	return result;
}
