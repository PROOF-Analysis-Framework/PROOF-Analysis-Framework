/**
	@brief Container class which allows us a dynamic name assignment to any TObject.
	@file PAFNamedItem.cxx
	@class PAFNamedItem
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-01-22
 */

#include "PAFNamedItem.h"

ClassImp(PAFNamedItem);

PAFNamedItem::PAFNamedItem()
	: TNamed(), fObject(0)
{

}

PAFNamedItem::PAFNamedItem(const char* name, TObject* object)
	: TNamed(name, name), fObject(object)
{

}

void PAFNamedItem::SetObject(TObject* object)
{
	fObject = object;
}

TObject* PAFNamedItem::GetObject()
{
	return fObject;
}
