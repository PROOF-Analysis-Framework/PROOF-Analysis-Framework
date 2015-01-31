/**
	@brief Container class which allow us a dynamic name assign to any TObject.
	@file PAFNamedItem.h
	@class PAFNamedItem
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-01-22
*/

#pragma once

#include "TNamed.h"

class PAFNamedItem : public TNamed {
	public:
		PAFNamedItem() : TNamed(), fObject(0) {}
		PAFNamedItem(const char* name, TObject* object) : TNamed(name, name), fObject(object) {}

		void SetObject(TObject* object) { fObject = object; }
		TObject* GetObject() { return fObject; }

	private:
		TObject* fObject;

	ClassDef(PAFNamedItem, 1);
};

