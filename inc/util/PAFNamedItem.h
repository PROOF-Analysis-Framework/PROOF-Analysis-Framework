/**
	@brief Container class which allows us a dynamic name assignment to any TObject.
	@file PAFNamedItem.h
	@class PAFNamedItem
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-01-22
 */

#pragma once

#include "TNamed.h"

class PAFNamedItem : public TNamed 
{
	public:
		PAFNamedItem();
		PAFNamedItem(const char* name, TObject* object);

		void SetObject(TObject* object);
		TObject* GetObject();

	private:
		TObject* fObject;

	ClassDef(PAFNamedItem, 1);
};
