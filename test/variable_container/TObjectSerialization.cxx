/**
	@brief PAF test class to check the behaviour of VariableContainer serialization with TObject type.
	@file TObjectSerialization.cxx
	@class TObjectSerialization
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-02
 */

#include "TObjectSerialization.h"

#include "PAFVariableContainer.h"

#include "TBufferXML.h"
#include "TObjString.h"

int main()
{
	TObjectSerialization test;
	return PAFTest::Evaluate(&test);
}

void TObjectSerialization::Test()
{
	PAFVariableContainer containerSource;

	TObject* obj = new TObjString("This is a test.");

	containerSource.Add("object", obj);

	TString containerSourceString = TBufferXML::ConvertToXML(&containerSource);

	PAFVariableContainer* containerRestored = (PAFVariableContainer*)TBufferXML::ConvertFromXML(containerSourceString.Data());

	AssertEquals(obj, containerRestored->Get<TObjString*>("object"));

	delete containerRestored;
}
