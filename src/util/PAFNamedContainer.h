/**
	@brief Container class which allow us a dynamic name assign to any TObject.
	@file PAFNamedContainer.h
	@class PAFNamedContainer
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-01-22
*/

#pragma once

#include "TNamed.h"

class PAFNamedContainer : public TNamed {
	public:
		PAFNamedContainer() : TNamed(), fName(0), fObject(0) {}
		PAFNamedContainer(const char* name, TObject* object) : TNamed(name, name), fName(name), fObject(object) {}

		void SetName(const char* name) { fName = name; }
		const char* GetName() { return fName; }

		void SetObject(TObject* object) { fObject = object; }
		TObject* GetObject() { return fObject; }

	private:
		const char* fName;
		TObject* fObject;

	ClassDef(PAFNamedContainer, 1);
};

